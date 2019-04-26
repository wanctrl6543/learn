/*****************************************************************************
 *
 *  XVID MPEG-4 VIDEO CODEC
 *  - fast disrete cosine transformation - Header file
 *
 *  This file is part of XviD, a free MPEG-4 video encoder/decoder
 *
 *  XviD is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *  Under section 8 of the GNU General Public License, the copyright
 *  holders of XVID explicitly forbid distribution in the following
 *  countries:
 *
 *    - Japan
 *    - United States of America
 *
 *  Linking XviD statically or dynamically with other modules is making a
 *  combined work based on XviD.  Thus, the terms and conditions of the
 *  GNU General Public License cover the whole combination.
 *
 *  As a special exception, the copyright holders of XviD give you
 *  permission to link XviD with independent modules that communicate with
 *  XviD solely through the VFW1.1 and DShow interfaces, regardless of the
 *  license terms of these independent modules, and to copy and distribute
 *  the resulting combined work under terms of your choice, provided that
 *  every copy of the combined work is accompanied by a complete copy of
 *  the source code of XviD (the version of XviD used to produce the
 *  combined work), being distributed under the terms of the GNU General
 *  Public License plus this exception.  An independent module is a module
 *  which is not derived from or based on XviD.
 *
 *  Note that people who make modified versions of XviD are not obligated
 *  to grant this special exception for their modified versions; it is
 *  their choice whether to do so.  The GNU General Public License gives
 *  permission to release a modified version without this exception; this
 *  exception also makes it possible to release a modified version which
 *  carries forward this exception.
 *
 * $Id: idct.h,v 1.1.1.1.2.1 2005/06/03 05:48:10 lixq Exp $
 *
 *************************************************************************/

#ifndef _IDCT_H_
#define _IDCT_H_
#ifdef __cplusplus
extern "C" {
#endif
extern void idct_h261_int32_init(void);
extern void idct_h261_ia64_init(void);
extern void IDCT_Block(short *blk_in);
extern void simple_idct_h261_c(short * const block);

typedef void (idctFunc) (short *const block);
typedef idctFunc *idctFuncPtr;

extern idctFuncPtr xvid_idct;

idctFunc idct_h261_int32;
idctFunc idct_h261_mmx;
idctFunc idct_h261_xmm;
idctFunc idct_h261_sse2;
idctFunc idct_h261_altivec;
idctFunc idct_h261_ia64;
idctFunc simple_idct_h261_mmx;
idctFunc simple_idct_h261_mmx_P;
#ifdef __cplusplus
}
#endif
#endif							/* _IDCT_H_ */
