;/*****************************************************************************
; *
; *  XVID MPEG-4 VIDEO CODEC
; *  mmx sum of absolute difference
; *
; *  Copyright(C) 2002 Peter Ross <pross@xvid.org>
; *
; *  This file is part of XviD, a free MPEG-4 video encoder/decoder
; *
; *  XviD is free software; you can redistribute it and/or modify it
; *  under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License
; *  along with this program; if not, write to the Free Software
; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
; *
; *  Under section 8 of the GNU General Public License, the copyright
; *  holders of XVID explicitly forbid distribution in the following
; *  countries:
; *
; *    - Japan
; *    - United States of America
; *
; *  Linking XviD statically or dynamically with other modules is making a
; *  combined work based on XviD.  Thus, the terms and conditions of the
; *  GNU General Public License cover the whole combination.
; *
; *  As a special exception, the copyright holders of XviD give you
; *  permission to link XviD with independent modules that communicate with
; *  XviD solely through the VFW1.1 and DShow interfaces, regardless of the
; *  license terms of these independent modules, and to copy and distribute
; *  the resulting combined work under terms of your choice, provided that
; *  every copy of the combined work is accompanied by a complete copy of
; *  the source code of XviD (the version of XviD used to produce the
; *  combined work), being distributed under the terms of the GNU General
; *  Public License plus this exception.  An independent module is a module
; *  which is not derived from or based on XviD.
; *
; *  Note that people who make modified versions of XviD are not obligated
; *  to grant this special exception for their modified versions; it is
; *  their choice whether to do so.  The GNU General Public License gives
; *  permission to release a modified version without this exception; this
; *  exception also makes it possible to release a modified version which
; *  carries forward this exception.
; *
; * $Id: sad_mmx.asm,v 1.1.1.1.2.2 2005/06/03 05:48:10 lixq Exp $
; *
; ****************************************************************************/

bits 32

%macro cglobal 1 
	%ifdef PREFIX
		global _%1 
		%define %1 _%1
	%else
		global %1
	%endif
%endmacro

section .data

align 16
mmx_one	times 4	dw 1

section .text

cglobal  sad16_h261_mmx
cglobal  sad8_h261_mmx
cglobal  sad16bi_h261_mmx
cglobal  sad8bi_h261_mmx
cglobal  dev16_h261_mmx

;===========================================================================
;
; uint32_t sad16_h261_mmx(const uint8_t * const cur,
;					 const uint8_t * const ref,
;					 const uint32_t stride,
;					 const uint32_t best_sad);
;
; (early termination ignore; slows this down)
;
;===========================================================================

%macro SAD_16x16_MMX 0
    movq mm0, [eax]
    movq mm1, [edx]

    movq mm2, [eax+8]
    movq mm3, [edx+8]

    movq mm4, mm0
    psubusb mm0, mm1
    lea eax,[eax+ecx]
    movq mm5, mm2
    psubusb mm2, mm3
    lea edx,[edx+ecx]

    psubusb mm1, mm4
    por mm0, mm1
    psubusb mm3, mm5
    por mm2, mm3

    movq mm1,mm0
    movq mm3,mm2

    punpcklbw mm0,mm7
    punpckhbw mm1,mm7
    punpcklbw mm2,mm7
    punpckhbw mm3,mm7

    paddusw mm0,mm1
    paddusw mm6,mm0
    paddusw mm2,mm3
    paddusw mm6,mm2
%endmacro

align 16
sad16_h261_mmx:

    mov eax, [esp+ 4] ; Src1
    mov edx, [esp+ 8] ; Src2
    mov ecx, [esp+12] ; Stride
    
    pxor mm6, mm6 ; accum
    pxor mm7, mm7 ; zero

    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX

    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX
    SAD_16x16_MMX

    pmaddwd mm6, [mmx_one] ; collapse
    movq mm7, mm6
    psrlq mm7, 32 
    paddd mm6, mm7

    movd eax, mm6
	emms
    ret


;===========================================================================
;
; uint32_t sad8_h261_mmx(const uint8_t * const cur,
;					const uint8_t * const ref,
;					const uint32_t stride);
;
;===========================================================================

%macro SAD_8x8_MMX  0
    movq mm0, [eax]
    movq mm1, [edx]

    movq mm2, [eax+ecx]
    movq mm3, [edx+ecx]

    lea eax,[eax+2*ecx]
    lea edx,[edx+2*ecx]

    movq mm4, mm0 
    psubusb mm0, mm1
    movq mm5, mm2
    psubusb mm2, mm3

    psubusb mm1, mm4
    por mm0, mm1
    psubusb mm3, mm5
    por mm2, mm3

    movq mm1,mm0
    movq mm3,mm2

    punpcklbw mm0,mm7
    punpckhbw mm1,mm7
    punpcklbw mm2,mm7
    punpckhbw mm3,mm7

    paddusw mm0,mm1
    paddusw mm6,mm0
    paddusw mm2,mm3
    paddusw mm6,mm2
%endmacro

align 16
sad8_h261_mmx:

    mov eax, [esp+ 4] ; Src1
    mov edx, [esp+ 8] ; Src2
    mov ecx, [esp+12] ; Stride
    
    pxor mm6, mm6 ; accum
    pxor mm7, mm7 ; zero

    SAD_8x8_MMX
    SAD_8x8_MMX
    SAD_8x8_MMX
    SAD_8x8_MMX

    pmaddwd mm6, [mmx_one] ; collapse
    movq mm7, mm6
    psrlq mm7, 32 
    paddd mm6, mm7

    movd eax, mm6

    ret





;=========================================================================== 
; 
; uint32_t sad16bi_h261_mmx(const uint8_t * const cur, 
; const uint8_t * const ref1, 
; const uint8_t * const ref2, 
; const uint32_t stride); 
; 
;=========================================================================== 
%macro SADBI_16x16_MMX 2    ; SADBI_16x16_MMX( int_ptr_offset, bool_increment_ptr ); 

   movq mm0, [edx+%1] 
   movq mm2, [ebx+%1] 
   movq mm1, mm0 
   movq mm3, mm2 

%if %2 != 0 
   add edx, ecx 
%endif 

   punpcklbw mm0, mm7 
   punpckhbw mm1, mm7 
punpcklbw mm2, mm7 
punpckhbw mm3, mm7 

%if %2 != 0 
   add ebx, ecx 
%endif 

paddusw mm0, mm2    ; mm01 = ref1 + ref2 
paddusw mm1, mm3 
paddusw mm0, [mmx_one] ; mm01 += 1 
paddusw mm1, [mmx_one] 
psrlw mm0, 1     ; mm01 >>= 1 
psrlw mm1, 1 

   movq mm2, [eax+%1] 
   movq mm3, mm2 
   punpcklbw mm2, mm7          ; mm23 = src 
   punpckhbw mm3, mm7 

%if %2 != 0 
   add eax, ecx 
%endif 

   movq mm4, mm0 
   movq mm5, mm1 
   psubusw mm0, mm2 
   psubusw mm1, mm3 
   psubusw mm2, mm4 
   psubusw mm3, mm5 
   por mm0, mm2                ; mm01 = ABS(mm01 - mm23) 
   por mm1, mm3 

   paddusw mm6,mm0             ; mm6 += mm01 
   paddusw mm6,mm1 

%endmacro 

align 16 
sad16bi_h261_mmx: 
   push ebx 
   mov eax, [esp+4+ 4] ; Src 
   mov edx, [esp+4+ 8] ; Ref1 
   mov ebx, [esp+4+12] ; Ref2 
   mov ecx, [esp+4+16] ; Stride 

   pxor mm6, mm6 ; accum2 
pxor mm7, mm7 
.Loop 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 

   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 
   SADBI_16x16_MMX 0, 0 
   SADBI_16x16_MMX 8, 1 

   pmaddwd mm6, [mmx_one] ; collapse 
   movq mm7, mm6 
   psrlq mm7, 32 
   paddd mm6, mm7 

   movd eax, mm6 
   pop ebx 
   ret 

;=========================================================================== 
; 
; uint32_t sad8bi_h261_mmx(const uint8_t * const cur, 
; const uint8_t * const ref1, 
; const uint8_t * const ref2, 
; const uint32_t stride); 
; 
;=========================================================================== 
align 16 
sad8bi_h261_mmx: 
   push ebx 
   mov eax, [esp+4+ 4] ; Src 
   mov edx, [esp+4+ 8] ; Ref1 
   mov ebx, [esp+4+12] ; Ref2 
   mov ecx, [esp+4+16] ; Stride 

   pxor mm6, mm6 ; accum2 
pxor mm7, mm7 
.Loop 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 
   SADBI_16x16_MMX 0, 1 

   pmaddwd mm6, [mmx_one] ; collapse 
   movq mm7, mm6 
   psrlq mm7, 32 
   paddd mm6, mm7 

   movd eax, mm6 
   pop ebx 
   ret 




;===========================================================================
;
; uint32_t dev16_h261_mmx(const uint8_t * const cur,
;					const uint32_t stride);
;
;===========================================================================

%macro MEAN_16x16_MMX 0
    movq mm0, [eax]
    movq mm2, [eax+8]
    lea eax,[eax+ecx]    
    movq mm1, mm0
    movq mm3, mm2
    punpcklbw mm0,mm7
    punpcklbw mm2,mm7
    punpckhbw mm1,mm7
    punpckhbw mm3,mm7 
    paddw mm5, mm0 
    paddw mm6, mm1 
    paddw mm5, mm2
    paddw mm6, mm3   
%endmacro

%macro ABS_16x16_MMX 0
    movq mm0, [eax]
    movq mm2, [eax+8]
    lea eax,[eax+ecx]
    movq mm1, mm0
    movq mm3, mm2
    punpcklbw mm0, mm7
    punpcklbw mm2, mm7
    punpckhbw mm1, mm7
    punpckhbw mm3, mm7
    movq mm4, mm6
	psubusw mm4, mm0
		
	psubusw mm0, mm6
	por mm0, mm4
	movq mm4, mm6
	psubusw mm4, mm1
	psubusw mm1, mm6
	por mm1, mm4

    movq mm4, mm6
	psubusw mm4, mm2
	psubusw mm2, mm6
	por mm2, mm4
	movq mm4, mm6
	psubusw mm4, mm3
	psubusw mm3, mm6
	por mm3, mm4

	paddw mm0, mm1
	paddw mm2, mm3
	paddw mm5, mm0
	paddw mm5, mm2
%endmacro

align 16
dev16_h261_mmx:
    mov eax, [esp+ 4] ; Src
    mov ecx, [esp+ 8] ; Stride
    
    pxor mm7, mm7 ; zero
    pxor mm5, mm5 ; accum1
    pxor mm6, mm6 ; accum2

    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX

    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX
    MEAN_16x16_MMX

    paddusw mm6, mm5
    pmaddwd mm6, [mmx_one] ; collapse
    movq mm5, mm6
    psrlq mm5, 32 
    paddd mm6, mm5

    psllq mm6, 32			; blank upper dword
	psrlq mm6, 32 + 8 ;  /= (16*16)

	punpckldq mm6, mm6
	packssdw mm6, mm6

    ; mm6 contains the mean
    ; mm5 is the new accum

    pxor mm5, mm5
    mov eax, [esp+ 4] ; Src

    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX

    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX
    ABS_16x16_MMX

    pmaddwd mm5, [mmx_one] ; collapse
    movq mm6, mm5
    psrlq mm6, 32
    paddd mm6, mm5

    movd eax, mm6
	emms
    ret
	
