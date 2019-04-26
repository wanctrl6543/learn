/*
    Copyright (C) 2001-2003 Michael Niedermayer (michaelni@gmx.at)

    AltiVec optimizations (C) 2004 Romain Dolbeau <romain@dolbeau.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @file postprocess.c
 * postprocessing.
 */
 
/*
			C	MMX	MMX2	3DNow	AltiVec
isVertDC		Ec	Ec			Ec
isVertMinMaxOk		Ec	Ec			Ec
doVertLowPass		E		e	e	Ec
doVertDefFilter		Ec	Ec	e	e	Ec
isHorizDC		Ec	Ec			Ec
isHorizMinMaxOk		a	E			Ec
doHorizLowPass		E		e	e	Ec
doHorizDefFilter	Ec	Ec	e	e	Ec
do_a_deblock		Ec	E	Ec	E
deRing			E		e	e*	Ecp
Vertical RKAlgo1        E               a       a
Horizontal RKAlgo1                      a       a
Vertical X1#            a               E       E
Horizontal X1#          a               E       E
LinIpolDeinterlace      e               E       E*
CubicIpolDeinterlace    a               e       e*
LinBlendDeinterlace     e               E       E*
MedianDeinterlace#	E	Ec	Ec
TempDeNoiser#		E		e	e	Ec

* i dont have a 3dnow CPU -> its untested, but noone said it doesnt work so it seems to work
# more or less selfinvented filters so the exactness isnt too meaningfull
E = Exact implementation
e = allmost exact implementation (slightly different rounding,...)
a = alternative / approximate impl
c = checked against the other implementations (-vo md5)
p = partially optimized, still some work to do
*/

/*
TODO:
reduce the time wasted on the mem transfer
unroll stuff if instructions depend too much on the prior one
move YScale thing to the end instead of fixing QP
write a faster and higher quality deblocking filter :)
make the mainloop more flexible (variable number of blocks at once
        (the if/else stuff per block is slowing things down)
compare the quality & speed of all filters
split this huge file
optimize c versions
try to unroll inner for(x=0 ... loop to avoid these damn if(x ... checks
...
*/

//Changelog: use the CVS log

#include "config_postproc.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
//#undef HAVE_MMX2
//#define HAVE_3DNOW
//#undef HAVE_MMX
//#undef ARCH_X86
//#define DEBUG_BRIGHTNESS
#ifdef USE_FASTMEMCPY
#include "fastmemcpy.h"
#endif
#include "postprocess.h"
#include "postprocess_internal.h"
#include "cpudetect.h"

#include "mangle.h" //FIXME should be supressed

#ifdef HAVE_ALTIVEC_H
#include <altivec.h>
#endif

#ifndef HAVE_MEMALIGN
#define memalign(a,b) malloc(b)
#endif

#define MIN(a,b) ((a) > (b) ? (b) : (a))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define ABS(a) ((a) > 0 ? (a) : (-(a)))
#define SIGN(a) ((a) > 0 ? 1 : -1)

#define GET_MODE_BUFFER_SIZE 500
#define OPTIONS_ARRAY_SIZE 10
#define BLOCK_SIZE 8
#define TEMP_STRIDE 8
//#define NUM_BLOCKS_AT_ONCE 16 //not used yet

#if defined(ARCH_X86) || defined(ARCH_X86_64)
static uint64_t __attribute__((aligned(8))) attribute_used w05=		0x0005000500050005LL;
static uint64_t __attribute__((aligned(8))) attribute_used w04=		0x0004000400040004LL;
static uint64_t __attribute__((aligned(8))) attribute_used w20=		0x0020002000200020LL;
static uint64_t __attribute__((aligned(8))) attribute_used b00= 		0x0000000000000000LL;
static uint64_t __attribute__((aligned(8))) attribute_used b01= 		0x0101010101010101LL;
static uint64_t __attribute__((aligned(8))) attribute_used b02= 		0x0202020202020202LL;
static uint64_t __attribute__((aligned(8))) attribute_used b08= 		0x0808080808080808LL;
static uint64_t __attribute__((aligned(8))) attribute_used b80= 		0x8080808080808080LL;
#endif

static uint8_t clip_table[3*256];
static uint8_t * const clip_tab= clip_table + 256;

static const int verbose= 0;

static const int attribute_used deringThreshold= 20;

CpuCaps gCpuCaps;



#if defined(ARCH_X86) || defined(ARCH_X86_64)
static inline void prefetchnta(void *p)
{
        asm volatile(   "prefetchnta (%0)\n\t"
                : : "r" (p)
        );
}

static inline void prefetcht0(void *p)
{
        asm volatile(   "prefetcht0 (%0)\n\t"
                : : "r" (p)
        );
}

static inline void prefetcht1(void *p)
{
        asm volatile(   "prefetcht1 (%0)\n\t"
                : : "r" (p)
        );
}

static inline void prefetcht2(void *p)
{
        asm volatile(   "prefetcht2 (%0)\n\t"
                : : "r" (p)
        );
}
#endif

// The horizontal Functions exist only in C cuz the MMX code is faster with vertical filters and transposing

/**
 * Check if the given 8x8 Block is mostly "flat"
 */
static inline int isHorizDC_C(uint8_t src[], stride_t stride, PPContext *c)
{
        int numEq= 0;
        int y;
	const int dcOffset= ((c->nonBQP*c->ppMode.baseDcDiff)>>8) + 1;
	const int dcThreshold= dcOffset*2 + 1;

        for(y=0; y<BLOCK_SIZE; y++)
        {
		if(((unsigned)(src[0] - src[1] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[1] - src[2] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[2] - src[3] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[3] - src[4] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[4] - src[5] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[5] - src[6] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[6] - src[7] + dcOffset)) < dcThreshold) numEq++;
                src+= stride;
        }
	return numEq > c->ppMode.flatnessThreshold;
}

/**
 * Check if the middle 8x8 Block in the given 8x16 block is flat
 */
static inline int isVertDC_C(uint8_t src[], stride_t stride, PPContext *c){
	int numEq= 0;
	int y;
	const int dcOffset= ((c->nonBQP*c->ppMode.baseDcDiff)>>8) + 1;
	const int dcThreshold= dcOffset*2 + 1;

	src+= stride*4; // src points to begin of the 8x8 Block
	for(y=0; y<BLOCK_SIZE-1; y++)
	{
		if(((unsigned)(src[0] - src[0+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[1] - src[1+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[2] - src[2+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[3] - src[3+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[4] - src[4+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[5] - src[5+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[6] - src[6+stride] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[7] - src[7+stride] + dcOffset)) < dcThreshold) numEq++;
		src+= stride;
	}
	return numEq > c->ppMode.flatnessThreshold;
}

static inline int isHorizMinMaxOk_C(uint8_t src[], stride_t stride, int QP)
{
	int i;
#if 1
	for(i=0; i<2; i++){
		if((unsigned)(src[0] - src[5] + 2*QP) > 4*QP) return 0;
		src += stride;
		if((unsigned)(src[2] - src[7] + 2*QP) > 4*QP) return 0;
		src += stride;
		if((unsigned)(src[4] - src[1] + 2*QP) > 4*QP) return 0;
		src += stride;
		if((unsigned)(src[6] - src[3] + 2*QP) > 4*QP) return 0;
		src += stride;
	}
#else        
	for(i=0; i<8; i++){
		if((unsigned)(src[0] - src[7] + 2*QP) > 4*QP) return 0;
		src += stride;
	}
#endif
	return 1;
}

static inline int isVertMinMaxOk_C(uint8_t src[], stride_t stride, int QP)
{
#if 1
#if 1
	int x;
	src+= stride*4;
	for(x=0; x<BLOCK_SIZE; x+=4)
	{
		if((unsigned)(src[  x + 0*stride] - src[  x + 5*stride] + 2*QP) > 4*QP) return 0;
		if((unsigned)(src[1+x + 2*stride] - src[1+x + 7*stride] + 2*QP) > 4*QP) return 0;
		if((unsigned)(src[2+x + 4*stride] - src[2+x + 1*stride] + 2*QP) > 4*QP) return 0;
		if((unsigned)(src[3+x + 6*stride] - src[3+x + 3*stride] + 2*QP) > 4*QP) return 0;
	}
#else
	int x;
	src+= stride*3;
	for(x=0; x<BLOCK_SIZE; x++)
	{
		if((unsigned)(src[x + stride] - src[x + (stride<<3)] + 2*QP) > 4*QP) return 0;
	}
#endif
	return 1;
#else
	int x;
	src+= stride*4;
	for(x=0; x<BLOCK_SIZE; x++)
	{
		int min=255;
		int max=0;
		int y;
		for(y=0; y<8; y++){
			int v= src[x + y*stride];
			if(v>max) max=v;
			if(v<min) min=v;
		}
		if(max-min > 2*QP) return 0;
	}
	return 1;
#endif
}

static inline int horizClassify_C(uint8_t src[], stride_t stride, PPContext *c){
	if( isHorizDC_C(src, stride, c) ){
		if( isHorizMinMaxOk_C(src, stride, c->QP) )
			return 1;
		else
			return 0;
	}else{
		return 2;
	}
}

static inline int vertClassify_C(uint8_t src[], stride_t stride, PPContext *c){
	if( isVertDC_C(src, stride, c) ){
		if( isVertMinMaxOk_C(src, stride, c->QP) )
        return 1;
		else
			return 0;
	}else{
		return 2;
	}
}

static inline void doHorizDefFilter_C(uint8_t dst[], stride_t stride, PPContext *c)
{
        int y;
        for(y=0; y<BLOCK_SIZE; y++)
        {
		const int middleEnergy= 5*(dst[4] - dst[3]) + 2*(dst[2] - dst[5]);

		if(ABS(middleEnergy) < 8*c->QP)
                {
                        const int q=(dst[3] - dst[4])/2;
                        const int leftEnergy=  5*(dst[2] - dst[1]) + 2*(dst[0] - dst[3]);
                        const int rightEnergy= 5*(dst[6] - dst[5]) + 2*(dst[4] - dst[7]);

                        int d= ABS(middleEnergy) - MIN( ABS(leftEnergy), ABS(rightEnergy) );
                        d= MAX(d, 0);

                        d= (5*d + 32) >> 6;
                        d*= SIGN(-middleEnergy);

                        if(q>0)
                        {
                                d= d<0 ? 0 : d;
                                d= d>q ? q : d;
                        }
                        else
                        {
                                d= d>0 ? 0 : d;
                                d= d<q ? q : d;
                        }

                        dst[3]-= d;
                        dst[4]+= d;
                }
                dst+= stride;
        }
}

/**
 * Do a horizontal low pass filter on the 10x8 block (dst points to middle 8x8 Block)
 * using the 9-Tap Filter (1,1,2,2,4,2,2,1,1)/16 (C version)
 */
static inline void doHorizLowPass_C(uint8_t dst[], stride_t stride, PPContext *c)
{
        int y;
        for(y=0; y<BLOCK_SIZE; y++)
        {
		const int first= ABS(dst[-1] - dst[0]) < c->QP ? dst[-1] : dst[0];
		const int last= ABS(dst[8] - dst[7]) < c->QP ? dst[8] : dst[7];

		int sums[10];
		sums[0] = 4*first + dst[0] + dst[1] + dst[2] + 4;
		sums[1] = sums[0] - first  + dst[3];
		sums[2] = sums[1] - first  + dst[4];
		sums[3] = sums[2] - first  + dst[5];
		sums[4] = sums[3] - first  + dst[6];
		sums[5] = sums[4] - dst[0] + dst[7];
		sums[6] = sums[5] - dst[1] + last;
		sums[7] = sums[6] - dst[2] + last;
		sums[8] = sums[7] - dst[3] + last;
		sums[9] = sums[8] - dst[4] + last;

		dst[0]= (sums[0] + sums[2] + 2*dst[0])>>4;
		dst[1]= (sums[1] + sums[3] + 2*dst[1])>>4;
		dst[2]= (sums[2] + sums[4] + 2*dst[2])>>4;
		dst[3]= (sums[3] + sums[5] + 2*dst[3])>>4;
		dst[4]= (sums[4] + sums[6] + 2*dst[4])>>4;
		dst[5]= (sums[5] + sums[7] + 2*dst[5])>>4;
		dst[6]= (sums[6] + sums[8] + 2*dst[6])>>4;
		dst[7]= (sums[7] + sums[9] + 2*dst[7])>>4;

                dst+= stride;
        }
}

/**
 * Experimental Filter 1 (Horizontal)
 * will not damage linear gradients
 * Flat blocks should look like they where passed through the (1,1,2,2,4,2,2,1,1) 9-Tap filter
 * can only smooth blocks at the expected locations (it cant smooth them if they did move)
 * MMX2 version does correct clipping C version doesnt
 * not identical with the vertical one
 */
static inline void horizX1Filter(uint8_t *src, stride_t stride, int QP)
{
        int y;
        static uint64_t *lut= NULL;
        if(lut==NULL)
        {
                int i;
                lut= (uint64_t*)memalign(8, 256*8);
                for(i=0; i<256; i++)
                {
                        int v= i < 128 ? 2*i : 2*(i-256);
/*
//Simulate 112242211 9-Tap filter
                        uint64_t a= (v/16) & 0xFF;
                        uint64_t b= (v/8) & 0xFF;
                        uint64_t c= (v/4) & 0xFF;
                        uint64_t d= (3*v/8) & 0xFF;
*/
//Simulate piecewise linear interpolation
                        uint64_t a= (v/16) & 0xFF;
                        uint64_t b= (v*3/16) & 0xFF;
                        uint64_t c= (v*5/16) & 0xFF;
                        uint64_t d= (7*v/16) & 0xFF;
                        uint64_t A= (0x100 - a)&0xFF;
                        uint64_t B= (0x100 - b)&0xFF;
                        uint64_t C= (0x100 - c)&0xFF;
                        uint64_t D= (0x100 - c)&0xFF;

                        lut[i]   = (a<<56) | (b<<48) | (c<<40) | (d<<32) |
                                (D<<24) | (C<<16) | (B<<8) | (A);
                        //lut[i] = (v<<32) | (v<<24);
                }
        }

        for(y=0; y<BLOCK_SIZE; y++)
        {
                int a= src[1] - src[2];
                int b= src[3] - src[4];
                int c= src[5] - src[6];

                int d= MAX(ABS(b) - (ABS(a) + ABS(c))/2, 0);

                if(d < QP)
                {
                        int v = d * SIGN(-b);

                        src[1] +=v/8;
                        src[2] +=v/4;
                        src[3] +=3*v/8;
                        src[4] -=3*v/8;
                        src[5] -=v/4;
                        src[6] -=v/8;

                }
                src+=stride;
        }
}

/**
 * accurate deblock filter
 */
static always_inline void do_a_deblock_C(uint8_t *src, stride_t step, stride_t stride, PPContext *c){
	int y;
	const int QP= c->QP;
	const int dcOffset= ((c->nonBQP*c->ppMode.baseDcDiff)>>8) + 1;
	const int dcThreshold= dcOffset*2 + 1;
//START_TIMER
	src+= step*4; // src points to begin of the 8x8 Block
	for(y=0; y<8; y++){
		int numEq= 0;

		if(((unsigned)(src[-1*step] - src[0*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 0*step] - src[1*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 1*step] - src[2*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 2*step] - src[3*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 3*step] - src[4*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 4*step] - src[5*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 5*step] - src[6*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 6*step] - src[7*step] + dcOffset)) < dcThreshold) numEq++;
		if(((unsigned)(src[ 7*step] - src[8*step] + dcOffset)) < dcThreshold) numEq++;
		if(numEq > c->ppMode.flatnessThreshold){
			int min, max, x;
			
			if(src[0] > src[step]){
			    max= src[0];
			    min= src[step];
			}else{
			    max= src[step];
			    min= src[0];
			}
			for(x=2; x<8; x+=2){
				if(src[x*step] > src[(x+1)*step]){
					if(src[x    *step] > max) max= src[ x   *step];
					if(src[(x+1)*step] < min) min= src[(x+1)*step];
				}else{
					if(src[(x+1)*step] > max) max= src[(x+1)*step];
					if(src[ x   *step] < min) min= src[ x   *step];
				}
			}
			if(max-min < 2*QP){
				const int first= ABS(src[-1*step] - src[0]) < QP ? src[-1*step] : src[0];
				const int last= ABS(src[8*step] - src[7*step]) < QP ? src[8*step] : src[7*step];
				
				int sums[10];
				sums[0] = 4*first + src[0*step] + src[1*step] + src[2*step] + 4;
				sums[1] = sums[0] - first       + src[3*step];
				sums[2] = sums[1] - first       + src[4*step];
				sums[3] = sums[2] - first       + src[5*step];
				sums[4] = sums[3] - first       + src[6*step];
				sums[5] = sums[4] - src[0*step] + src[7*step];
				sums[6] = sums[5] - src[1*step] + last;
				sums[7] = sums[6] - src[2*step] + last;
				sums[8] = sums[7] - src[3*step] + last;
				sums[9] = sums[8] - src[4*step] + last;

				src[0*step]= (sums[0] + sums[2] + 2*src[0*step])>>4;
				src[1*step]= (sums[1] + sums[3] + 2*src[1*step])>>4;
				src[2*step]= (sums[2] + sums[4] + 2*src[2*step])>>4;
				src[3*step]= (sums[3] + sums[5] + 2*src[3*step])>>4;
				src[4*step]= (sums[4] + sums[6] + 2*src[4*step])>>4;
				src[5*step]= (sums[5] + sums[7] + 2*src[5*step])>>4;
				src[6*step]= (sums[6] + sums[8] + 2*src[6*step])>>4;
				src[7*step]= (sums[7] + sums[9] + 2*src[7*step])>>4;
			}
		}else{
			const int middleEnergy= 5*(src[4*step] - src[3*step]) + 2*(src[2*step] - src[5*step]);

			if(ABS(middleEnergy) < 8*QP)
			{
				const int q=(src[3*step] - src[4*step])/2;
				const int leftEnergy=  5*(src[2*step] - src[1*step]) + 2*(src[0*step] - src[3*step]);
				const int rightEnergy= 5*(src[6*step] - src[5*step]) + 2*(src[4*step] - src[7*step]);

				int d= ABS(middleEnergy) - MIN( ABS(leftEnergy), ABS(rightEnergy) );
				d= MAX(d, 0);
	
				d= (5*d + 32) >> 6;
				d*= SIGN(-middleEnergy);
	
				if(q>0)
				{
					d= d<0 ? 0 : d;
					d= d>q ? q : d;
				}
				else
				{
					d= d>0 ? 0 : d;
					d= d<q ? q : d;
				}
	
				src[3*step]-= d;
				src[4*step]+= d;
			}
		}

		src += stride;
	}
/*if(step==16){
    STOP_TIMER("step16")
}else{
    STOP_TIMER("stepX")
}*/
}

//Note: we have C, MMX, MMX2, 3DNOW version there is no 3DNOW+MMX2 one
//Plain C versions
#if !defined (HAVE_MMX) || defined (RUNTIME_CPUDETECT)
#define COMPILE_C
#endif

#ifdef ARCH_POWERPC
#ifdef HAVE_ALTIVEC
#define COMPILE_ALTIVEC
#endif //HAVE_ALTIVEC
#endif //ARCH_POWERPC

#if defined(ARCH_X86) || defined(ARCH_X86_64)

#if (defined (HAVE_MMX) && !defined (HAVE_3DNOW) && !defined (HAVE_MMX2)) || defined (RUNTIME_CPUDETECT)
#define COMPILE_MMX
#endif

#if defined (HAVE_MMX2) || defined (RUNTIME_CPUDETECT)
#define COMPILE_MMX2
#endif

#if (defined (HAVE_3DNOW) && !defined (HAVE_MMX2)) || defined (RUNTIME_CPUDETECT)
#define COMPILE_3DNOW
#endif
#endif //ARCH_X86

#undef HAVE_MMX
#undef HAVE_MMX2
#undef HAVE_3DNOW
#undef HAVE_ALTIVEC

#ifdef COMPILE_C
#undef HAVE_MMX
#undef HAVE_MMX2
#undef HAVE_3DNOW
#define RENAME(a) a ## _C
#include "postprocess_template.c"
#endif

#ifdef ARCH_POWERPC
#ifdef COMPILE_ALTIVEC
#undef RENAME
#define HAVE_ALTIVEC
#define RENAME(a) a ## _altivec
#include "postprocess_altivec_template.c"
#include "postprocess_template.c"
#endif
#endif //ARCH_POWERPC

//MMX versions
#ifdef COMPILE_MMX
#undef RENAME
#define HAVE_MMX
#undef HAVE_MMX2
#undef HAVE_3DNOW
#define RENAME(a) a ## _MMX
#include "postprocess_template.c"
#endif

//MMX2 versions
#ifdef COMPILE_MMX2
#undef RENAME
#define HAVE_MMX
#define HAVE_MMX2
#undef HAVE_3DNOW
#define RENAME(a) a ## _MMX2
#include "postprocess_template.c"
#endif

//3DNOW versions
#ifdef COMPILE_3DNOW
#undef RENAME
#define HAVE_MMX
#undef HAVE_MMX2
#define HAVE_3DNOW
#define RENAME(a) a ## _3DNow
#include "postprocess_template.c"
#endif

// minor note: the HAVE_xyz is messed up after that line so dont use it

static inline void postProcess(uint8_t src[], stride_t srcStride, uint8_t dst[], stride_t dstStride, int width, int height,
	QP_STORE_T QPs[], int QPStride, int isColor, pp_mode_t *vm, pp_context_t *vc)
{
	PPContext *c= (PPContext *)vc;
	PPMode *ppMode= (PPMode *)vm;
	c->ppMode= *ppMode; //FIXME

        // useing ifs here as they are faster than function pointers allthough the
        // difference wouldnt be messureable here but its much better because
        // someone might exchange the cpu whithout restarting mplayer ;)
#ifdef RUNTIME_CPUDETECT
#if defined(ARCH_X86) || defined(ARCH_X86_64)
        // ordered per speed fasterst first
	if(c->cpuCaps & PP_CPU_CAPS_MMX2)
		postProcess_MMX2(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
	else if(c->cpuCaps & PP_CPU_CAPS_3DNOW)
		postProcess_3DNow(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
	else if(c->cpuCaps & PP_CPU_CAPS_MMX)
		postProcess_MMX(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
        else
		postProcess_C(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#else
#ifdef ARCH_POWERPC
#ifdef HAVE_ALTIVEC
        if(c->cpuCaps & PP_CPU_CAPS_ALTIVEC)
		postProcess_altivec(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
        else
#endif
#endif
		postProcess_C(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#endif
#else //RUNTIME_CPUDETECT
#ifdef HAVE_MMX2
		postProcess_MMX2(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#elif defined (HAVE_3DNOW)
		postProcess_3DNow(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#elif defined (HAVE_MMX)
		postProcess_MMX(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#elif defined (HAVE_ALTIVEC)
		postProcess_altivec(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#else
		postProcess_C(src, srcStride, dst, dstStride, width, height, QPs, QPStride, isColor, c);
#endif
#endif //!RUNTIME_CPUDETECT
}

static void reallocAlign(void **p, int alignment, stride_t size){
	if(*p) free(*p);
	*p= memalign(alignment, size);
	memset(*p, 0, size);
}

static void reallocBuffers(PPContext *c, int width, int height, stride_t stride, int qpStride){
	int mbWidth = (width+15)>>4;
	int mbHeight= (height+15)>>4;
	int i;

	c->stride= stride;
	c->qpStride= qpStride;

	reallocAlign((void **)&c->tempDst, 8, stride*24*2);
	reallocAlign((void **)&c->tempSrc, 8, stride*24*2);
	reallocAlign((void **)&c->tempBlocks, 8, 2*16*8);
	reallocAlign((void **)&c->yHistogram, 8, 256*sizeof(uint64_t));
	for(i=0; i<256; i++)
		c->yHistogram[i]= width*height/64*15/256;

	for(i=0; i<3; i++)
	{
		//Note:the +17*1024 is just there so i dont have to worry about r/w over te end
		reallocAlign((void **)&c->tempBlured[i], 8, stride*mbHeight*16 + 17*1024+256);
		reallocAlign((void **)&c->tempBluredPast[i], 8, 256*((height+7)&(~7))/2 + 17*1024+256);//FIXME size
	}

	reallocAlign((void **)&c->deintTemp, 8, 2*width+32);
	reallocAlign((void **)&c->nonBQPTable, 8, qpStride*mbHeight*sizeof(QP_STORE_T));
	reallocAlign((void **)&c->stdQPTable, 8, qpStride*mbHeight*sizeof(QP_STORE_T));
	reallocAlign((void **)&c->forcedQPTable, 8, mbWidth*sizeof(QP_STORE_T));
}

static void global_init(void){
	int i;
	memset(clip_table, 0, 256);
	for(i=256; i<512; i++)
		clip_table[i]= i;
	memset(clip_table+512, 0, 256);
}

pp_context_t *rave_pp_open(int width, int height, int cpuCaps){
	PPContext *c= memalign(32, sizeof(PPContext));
	int stride= (width+15)&(~15); //assumed / will realloc if needed
	int qpStride= (width+15)/16 + 2; //assumed / will realloc if needed

	global_init();

	memset(c, 0, sizeof(PPContext));
	c->cpuCaps= cpuCaps;
	if(cpuCaps&PP_FORMAT){
		c->hChromaSubSample= cpuCaps&0x3;
		c->vChromaSubSample= (cpuCaps>>4)&0x3;
	}else{
		c->hChromaSubSample= 1;
		c->vChromaSubSample= 1;
	}

	reallocBuffers(c, width, height, stride, qpStride);

	c->frameNum=-1;

	return c;
}

void rave_pp_close(void *vc){
	PPContext *c = (PPContext*)vc;
	int i;
	
	for(i=0; i<3; i++) free(c->tempBlured[i]);
	for(i=0; i<3; i++) free(c->tempBluredPast[i]);
	
	free(c->tempBlocks);
	free(c->yHistogram);
	free(c->tempDst);
	free(c->tempSrc);
	free(c->deintTemp);
	free(c->stdQPTable);
	free(c->nonBQPTable);
	free(c->forcedQPTable);
        
	memset(c, 0, sizeof(PPContext));
	
	free(c);
}

void  rave_pp_process(uint8_t * src[3], stride_t srcStride[3],
                 uint8_t * dst[3], stride_t dstStride[3],
                 int width, int height,
                 QP_STORE_T *QP_store,  int QPStride,
		 pp_mode_t *vm,  void *vc, int pict_type)
{
	int mbWidth = (width+15)>>4;
	int mbHeight= (height+15)>>4;
	PPMode *mode = (PPMode*)vm;
	PPContext *c = (PPContext*)vc;
        stride_t minStride= MAX(srcStride[0], dstStride[0]);
	
	if(c->stride < minStride || c->qpStride < QPStride)
		reallocBuffers(c, width, height, 
				MAX(minStride, c->stride), 
				MAX(c->qpStride, QPStride));
        
        if(QP_store==NULL || (mode->lumMode & FORCE_QUANT)) 
        {
                int i;
		QP_store= c->forcedQPTable;
		QPStride= 0;
                if(mode->lumMode & FORCE_QUANT)
			for(i=0; i<mbWidth; i++) QP_store[i]= mode->forcedQuant;
                else
			for(i=0; i<mbWidth; i++) QP_store[i]= 1;
        }
//printf("pict_type:%d\n", pict_type);

	if(pict_type & PP_PICT_TYPE_QP2){
		int i;
		const int count= mbHeight * QPStride;
		for(i=0; i<(count>>2); i++){
			((uint32_t*)c->stdQPTable)[i] = (((uint32_t*)QP_store)[i]>>1) & 0x7F7F7F7F;
		}
		for(i<<=2; i<count; i++){
			c->stdQPTable[i] = QP_store[i]>>1;
		}
                QP_store= c->stdQPTable;
	}

if(0){
int x,y;
for(y=0; y<mbHeight; y++){
	for(x=0; x<mbWidth; x++){
		;//printf("%2d ", QP_store[x + y*QPStride]);
	}
	//printf("\n");
}
	//printf("\n");
}

	if((pict_type&7)!=3)
        {
		int i;
		const int count= mbHeight * QPStride;
		for(i=0; i<(count>>2); i++){
			((uint32_t*)c->nonBQPTable)[i] = ((uint32_t*)QP_store)[i] & 0x3F3F3F3F;
			}
		for(i<<=2; i<count; i++){
			c->nonBQPTable[i] = QP_store[i] & 0x3F;
		}
		}

	if(verbose>2)
	{
		//printf("using npp filters 0x%X/0x%X\n", mode->lumMode, mode->chromMode);
        }

	postProcess(src[0], srcStride[0], dst[0], dstStride[0],
		width, height, QP_store, QPStride, 0, mode, c);

	width  = (width )>>c->hChromaSubSample;
	height = (height)>>c->vChromaSubSample;

        if(mode->chromMode)
        {
		postProcess(src[1], srcStride[1], dst[1], dstStride[1],
			width, height, QP_store, QPStride, 1, mode, c);
		postProcess(src[2], srcStride[2], dst[2], dstStride[2],
			width, height, QP_store, QPStride, 2, mode, c);
        }/*
	else if(srcStride[1] == dstStride[1] && srcStride[1]>0 && srcStride[2] == dstStride[2] && srcStride[2]>0)
        {
		memcpy(dst[1], src[1], srcStride[1]*height);
		memcpy(dst[2], src[2], srcStride[2]*height);
        }*/
        else
        {
                int y;
		for(y=0; y<height; y++)
                {
			memcpy(&(dst[1][y*dstStride[1]]), &(src[1][y*srcStride[1]]), width);
			memcpy(&(dst[2][y*dstStride[2]]), &(src[2][y*srcStride[2]]), width);
                }
        }
}

 
void rave_pp_init(int mmx,int mmx2,int _3dnow,int _3dnowExt,int sse,int sse2)
{
	gCpuCaps.hasMMX=mmx;
	gCpuCaps.hasMMX2=mmx2;
	gCpuCaps.has3DNow=_3dnow;
	gCpuCaps.has3DNowExt=_3dnowExt;
	gCpuCaps.hasSSE=sse;
	gCpuCaps.hasSSE2=sse2;
	init_fast_memcpy();
}