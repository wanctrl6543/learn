/***********************************************************************
Copyright (c) 2006-2011, Skype Limited. All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, (subject to the limitations in the disclaimer below)
are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
- Neither the name of Skype Limited, nor the names of specific
contributors, may be used to endorse or promote products derived from
this software without specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED
BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************/

#if  1
#include "../win32/config.h"
#endif
#ifdef FIXED_POINT
#include "main_FIX.h"
#define silk_encoder_state_Fxx      silk_encoder_state_FIX
#else
#include "./float/main_FLP.h"
#define silk_encoder_state_Fxx      silk_encoder_state_FLP
#endif
#include "tuning_parameters.h"

opus_int silk_setup_resamplers(
    silk_encoder_state_Fxx          *psEnc,             /* I/O                      */
    opus_int                         fs_kHz              /* I                        */
);

opus_int silk_setup_fs(
    silk_encoder_state_Fxx          *psEnc,             /* I/O                      */
    opus_int                         fs_kHz,             /* I                        */
    opus_int                         PacketSize_ms       /* I                        */
);

opus_int silk_setup_complexity(
    silk_encoder_state              *psEncC,            /* I/O                      */
    opus_int                         Complexity          /* I                        */
);

static inline opus_int silk_setup_LBRR(
    silk_encoder_state              *psEncC,            /* I/O                      */
    const opus_int32                 TargetRate_bps      /* I                        */
);


/* Control encoder */
opus_int silk_control_encoder(
    silk_encoder_state_Fxx          *psEnc,             /* I/O  Pointer to Silk encoder state           */
    silk_EncControlStruct           *encControl,        /* I:   Control structure                       */
    const opus_int32                 TargetRate_bps,     /* I    Target max bitrate (bps)                */
    const opus_int                   allow_bw_switch,    /* I    Flag to allow switching audio bandwidth */
    const opus_int                   channelNb,           /* I    Channel number                          */
    const opus_int                   force_fs_kHz
)
{
    opus_int   fs_kHz, ret = 0;

    psEnc->sCmn.useDTX                 = encControl->useDTX;
    psEnc->sCmn.useCBR                 = encControl->useCBR;
    psEnc->sCmn.API_fs_Hz              = encControl->API_sampleRate;
    psEnc->sCmn.maxInternal_fs_Hz      = encControl->maxInternalSampleRate;
    psEnc->sCmn.minInternal_fs_Hz      = encControl->minInternalSampleRate;
    psEnc->sCmn.desiredInternal_fs_Hz  = encControl->desiredInternalSampleRate;
    psEnc->sCmn.useInBandFEC           = encControl->useInBandFEC;
    psEnc->sCmn.nChannelsAPI           = encControl->nChannelsAPI;
    psEnc->sCmn.nChannelsInternal      = encControl->nChannelsInternal;
    psEnc->sCmn.allow_bandwidth_switch = allow_bw_switch;
    psEnc->sCmn.channelNb              = channelNb;

    if( psEnc->sCmn.controlled_since_last_payload != 0 && psEnc->sCmn.prefillFlag == 0 ) {
        if( psEnc->sCmn.API_fs_Hz != psEnc->sCmn.prev_API_fs_Hz && psEnc->sCmn.fs_kHz > 0 ) {
            /* Change in API sampling rate in the middle of encoding a packet */
            ret += silk_setup_resamplers( psEnc, psEnc->sCmn.fs_kHz );
        }
        return ret;
    }

    /* Beyond this point we know that there are no previously coded frames in the payload buffer */

    /********************************************/
    /* Determine internal sampling rate         */
    /********************************************/
    fs_kHz = silk_control_audio_bandwidth( &psEnc->sCmn );
    if (force_fs_kHz)
       fs_kHz = force_fs_kHz;
    /********************************************/
    /* Prepare resampler and buffered data      */
    /********************************************/
    ret += silk_setup_resamplers( psEnc, fs_kHz );

    /********************************************/
    /* Set internal sampling frequency          */
    /********************************************/
    ret += silk_setup_fs( psEnc, fs_kHz, encControl->payloadSize_ms );

    /********************************************/
    /* Set encoding complexity                  */
    /********************************************/
    ret += silk_setup_complexity( &psEnc->sCmn, encControl->complexity  );

    /********************************************/
    /* Set packet loss rate measured by farend  */
    /********************************************/
    psEnc->sCmn.PacketLoss_perc = encControl->packetLossPercentage;

    /********************************************/
    /* Set LBRR usage                           */
    /********************************************/
    ret += silk_setup_LBRR( &psEnc->sCmn, TargetRate_bps );

    psEnc->sCmn.controlled_since_last_payload = 1;

    return ret;
}

opus_int silk_setup_resamplers(
    silk_encoder_state_Fxx          *psEnc,             /* I/O                      */
    opus_int                         fs_kHz              /* I                        */
)
{
    opus_int   ret = SILK_NO_ERROR;
    opus_int32 nSamples_temp;

    if( psEnc->sCmn.fs_kHz != fs_kHz || psEnc->sCmn.prev_API_fs_Hz != psEnc->sCmn.API_fs_Hz )
    {
        if( psEnc->sCmn.fs_kHz == 0 ) {
            /* Initialize the resampler for enc_API.c preparing resampling from API_fs_Hz to fs_kHz */
            ret += silk_resampler_init( &psEnc->sCmn.resampler_state, psEnc->sCmn.API_fs_Hz, fs_kHz * 1000 );
        } else {
            /* Allocate worst case space for temporary upsampling, 8 to 48 kHz, so a factor 6 */
            opus_int16 x_buf_API_fs_Hz[ ( 2 * MAX_FRAME_LENGTH_MS + LA_SHAPE_MS ) * MAX_API_FS_KHZ ];
#ifdef FIXED_POINT
            opus_int16 *x_bufFIX = psEnc->x_buf;
#else
            opus_int16 x_bufFIX[ 2 * MAX_FRAME_LENGTH + LA_SHAPE_MAX ];
#endif

            nSamples_temp = silk_LSHIFT( psEnc->sCmn.frame_length, 1 ) + LA_SHAPE_MS * psEnc->sCmn.fs_kHz;

#ifndef FIXED_POINT
            silk_float2short_array( x_bufFIX, psEnc->x_buf, nSamples_temp );
#endif

            if( silk_SMULBB( fs_kHz, 1000 ) < psEnc->sCmn.API_fs_Hz && psEnc->sCmn.fs_kHz != 0 ) {
                /* Resample buffered data in x_buf to API_fs_Hz */

                silk_resampler_state_struct  temp_resampler_state;

                /* Initialize resampler for temporary resampling of x_buf data to API_fs_Hz */
                ret += silk_resampler_init( &temp_resampler_state, silk_SMULBB( psEnc->sCmn.fs_kHz, 1000 ), psEnc->sCmn.API_fs_Hz );

                /* Temporary resampling of x_buf data to API_fs_Hz */
                ret += silk_resampler( &temp_resampler_state, x_buf_API_fs_Hz, x_bufFIX, nSamples_temp );

                /* Calculate number of samples that has been temporarily upsampled */
                nSamples_temp = silk_DIV32_16( nSamples_temp * psEnc->sCmn.API_fs_Hz, silk_SMULBB( psEnc->sCmn.fs_kHz, 1000 ) );

                /* Initialize the resampler for enc_API.c preparing resampling from API_fs_Hz to fs_kHz */
                ret += silk_resampler_init( &psEnc->sCmn.resampler_state, psEnc->sCmn.API_fs_Hz, silk_SMULBB( fs_kHz, 1000 ) );

            } else {
                /* Copy data */
                silk_memcpy( x_buf_API_fs_Hz, x_bufFIX, nSamples_temp * sizeof( opus_int16 ) );
            }

            if( 1000 * fs_kHz != psEnc->sCmn.API_fs_Hz ) {
                /* Correct resampler state (unless resampling by a factor 1) by resampling buffered data from API_fs_Hz to fs_kHz */
                ret += silk_resampler( &psEnc->sCmn.resampler_state, x_bufFIX, x_buf_API_fs_Hz, nSamples_temp );
            }
#ifndef FIXED_POINT
            silk_short2float_array( psEnc->x_buf, x_bufFIX, ( 2 * MAX_FRAME_LENGTH_MS + LA_SHAPE_MS ) * fs_kHz );
#endif
        }
    }

    psEnc->sCmn.prev_API_fs_Hz = psEnc->sCmn.API_fs_Hz;

    return ret;
}

opus_int silk_setup_fs(
    silk_encoder_state_Fxx          *psEnc,             /* I/O                      */
    opus_int                         fs_kHz,             /* I                        */
    opus_int                         PacketSize_ms       /* I                        */
)
{
    opus_int ret = SILK_NO_ERROR;

    /* Set packet size */
    if( PacketSize_ms != psEnc->sCmn.PacketSize_ms ) {
        if( ( PacketSize_ms !=  10 ) &&
            ( PacketSize_ms !=  20 ) &&
            ( PacketSize_ms !=  40 ) &&
            ( PacketSize_ms !=  60 ) ) {
            ret = SILK_ENC_PACKET_SIZE_NOT_SUPPORTED;
        }
        if( PacketSize_ms <= 10 ) {
            psEnc->sCmn.nFramesPerPacket = 1;
            psEnc->sCmn.nb_subfr = PacketSize_ms == 10 ? 2 : 1;
            psEnc->sCmn.frame_length = silk_SMULBB( PacketSize_ms, fs_kHz );
            psEnc->sCmn.pitch_LPC_win_length = silk_SMULBB( FIND_PITCH_LPC_WIN_MS_2_SF, fs_kHz );
            if( psEnc->sCmn.fs_kHz == 8 ) {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_10_ms_NB_iCDF;
            } else {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_10_ms_iCDF;
            }
        } else {
            psEnc->sCmn.nFramesPerPacket = silk_DIV32_16( PacketSize_ms, MAX_FRAME_LENGTH_MS );
            psEnc->sCmn.nb_subfr = MAX_NB_SUBFR;
            psEnc->sCmn.frame_length = silk_SMULBB( 20, fs_kHz );
            psEnc->sCmn.pitch_LPC_win_length = silk_SMULBB( FIND_PITCH_LPC_WIN_MS, fs_kHz );
            if( psEnc->sCmn.fs_kHz == 8 ) {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_NB_iCDF;
            } else {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_iCDF;
            }
        }
        psEnc->sCmn.PacketSize_ms  = PacketSize_ms;
        psEnc->sCmn.TargetRate_bps = 0;         /* trigger new SNR computation */
    }

    /* Set internal sampling frequency */
    silk_assert( fs_kHz == 8 || fs_kHz == 12 || fs_kHz == 16 );
    silk_assert( psEnc->sCmn.nb_subfr == 2 || psEnc->sCmn.nb_subfr == 4 );
    if( psEnc->sCmn.fs_kHz != fs_kHz ) {
        /* reset part of the state */
#ifdef FIXED_POINT
        silk_memset( &psEnc->sShape,               0, sizeof( silk_shape_state_FIX ) );
        silk_memset( &psEnc->sPrefilt,             0, sizeof( silk_prefilter_state_FIX ) );
#else
        silk_memset( &psEnc->sShape,               0, sizeof( silk_shape_state_FLP ) );
        silk_memset( &psEnc->sPrefilt,             0, sizeof( silk_prefilter_state_FLP ) );
#endif
        silk_memset( &psEnc->sCmn.sNSQ,            0, sizeof( silk_nsq_state ) );
        silk_memset( psEnc->sCmn.prev_NLSFq_Q15,   0, sizeof( psEnc->sCmn.prev_NLSFq_Q15 ) );
        silk_memset( &psEnc->sCmn.sLP.In_LP_State, 0, sizeof( psEnc->sCmn.sLP.In_LP_State ) );
        psEnc->sCmn.inputBufIx                  = 0;
        psEnc->sCmn.nFramesEncoded              = 0;
        psEnc->sCmn.TargetRate_bps              = 0;     /* trigger new SNR computation */

        /* Initialize non-zero parameters */
        psEnc->sCmn.prevLag                     = 100;
        psEnc->sCmn.first_frame_after_reset     = 1;
        psEnc->sPrefilt.lagPrev                 = 100;
        psEnc->sShape.LastGainIndex             = 10;
        psEnc->sCmn.sNSQ.lagPrev                = 100;
        psEnc->sCmn.sNSQ.prev_inv_gain_Q16      = 65536;

        psEnc->sCmn.fs_kHz = fs_kHz;
        if( psEnc->sCmn.fs_kHz == 8 ) {
            if( psEnc->sCmn.nb_subfr == MAX_NB_SUBFR ) {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_NB_iCDF;
            } else {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_10_ms_NB_iCDF;
            }
        } else {
            if( psEnc->sCmn.nb_subfr == MAX_NB_SUBFR ) {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_iCDF;
            } else {
                psEnc->sCmn.pitch_contour_iCDF = silk_pitch_contour_10_ms_iCDF;
            }
        }
        if( psEnc->sCmn.fs_kHz == 8 || psEnc->sCmn.fs_kHz == 12 ) {
            psEnc->sCmn.predictLPCOrder = MIN_LPC_ORDER;
            psEnc->sCmn.psNLSF_CB  = &silk_NLSF_CB_NB_MB;
        } else {
            psEnc->sCmn.predictLPCOrder = MAX_LPC_ORDER;
            psEnc->sCmn.psNLSF_CB  = &silk_NLSF_CB_WB;
        }
        psEnc->sCmn.subfr_length   = SUB_FRAME_LENGTH_MS * fs_kHz;
        psEnc->sCmn.frame_length   = silk_SMULBB( psEnc->sCmn.subfr_length, psEnc->sCmn.nb_subfr );
        psEnc->sCmn.ltp_mem_length = silk_SMULBB( LTP_MEM_LENGTH_MS, fs_kHz );
        psEnc->sCmn.la_pitch       = silk_SMULBB( LA_PITCH_MS, fs_kHz );
        psEnc->sCmn.max_pitch_lag  = silk_SMULBB( 18, fs_kHz );
        if( psEnc->sCmn.nb_subfr == MAX_NB_SUBFR ) {
            psEnc->sCmn.pitch_LPC_win_length = silk_SMULBB( FIND_PITCH_LPC_WIN_MS, fs_kHz );
        } else {
            psEnc->sCmn.pitch_LPC_win_length = silk_SMULBB( FIND_PITCH_LPC_WIN_MS_2_SF, fs_kHz );
        }
        if( psEnc->sCmn.fs_kHz == 16 ) {
            psEnc->sCmn.mu_LTP_Q9 = SILK_FIX_CONST( MU_LTP_QUANT_WB, 9 );
            psEnc->sCmn.pitch_lag_low_bits_iCDF = silk_uniform8_iCDF;
        } else if( psEnc->sCmn.fs_kHz == 12 ) {
            psEnc->sCmn.mu_LTP_Q9 = SILK_FIX_CONST( MU_LTP_QUANT_MB, 9 );
            psEnc->sCmn.pitch_lag_low_bits_iCDF = silk_uniform6_iCDF;
        } else {
            psEnc->sCmn.mu_LTP_Q9 = SILK_FIX_CONST( MU_LTP_QUANT_NB, 9 );
            psEnc->sCmn.pitch_lag_low_bits_iCDF = silk_uniform4_iCDF;
        }
    }

    /* Check that settings are valid */
    silk_assert( ( psEnc->sCmn.subfr_length * psEnc->sCmn.nb_subfr ) == psEnc->sCmn.frame_length );

    return ret;
}

opus_int silk_setup_complexity(
    silk_encoder_state              *psEncC,            /* I/O                      */
    opus_int                         Complexity          /* I                        */
)
{
    opus_int ret = 0;

    /* Set encoding complexity */
    silk_assert( Complexity >= 0 && Complexity <= 10 );
    if( Complexity < 2 ) {
        psEncC->pitchEstimationComplexity       = SILK_PE_MIN_COMPLEX;
        psEncC->pitchEstimationThreshold_Q16    = SILK_FIX_CONST( 0.8, 16 );
        psEncC->pitchEstimationLPCOrder         = 6;
        psEncC->shapingLPCOrder                 = 8;
        psEncC->la_shape                        = 3 * psEncC->fs_kHz;
        psEncC->nStatesDelayedDecision          = 1;
        psEncC->useInterpolatedNLSFs            = 0;
        psEncC->LTPQuantLowComplexity           = 1;
        psEncC->NLSF_MSVQ_Survivors             = 2;
        psEncC->warping_Q16                     = 0;
    } else if( Complexity < 4 ) {
        psEncC->pitchEstimationComplexity       = SILK_PE_MID_COMPLEX;
        psEncC->pitchEstimationThreshold_Q16    = SILK_FIX_CONST( 0.76, 16 );
        psEncC->pitchEstimationLPCOrder         = 8;
        psEncC->shapingLPCOrder                 = 10;
        psEncC->la_shape                        = 5 * psEncC->fs_kHz;
        psEncC->nStatesDelayedDecision          = 1;
        psEncC->useInterpolatedNLSFs            = 1;
        psEncC->LTPQuantLowComplexity           = 0;
        psEncC->NLSF_MSVQ_Survivors             = 4;
        psEncC->warping_Q16                     = 0;
    } else if( Complexity < 6 ) {
        psEncC->pitchEstimationComplexity       = SILK_PE_MID_COMPLEX;
        psEncC->pitchEstimationThreshold_Q16    = SILK_FIX_CONST( 0.74, 16 );
        psEncC->pitchEstimationLPCOrder         = 10;
        psEncC->shapingLPCOrder                 = 12;
        psEncC->la_shape                        = 5 * psEncC->fs_kHz;
        psEncC->nStatesDelayedDecision          = 2;
        psEncC->useInterpolatedNLSFs            = 0;
        psEncC->LTPQuantLowComplexity           = 0;
        psEncC->NLSF_MSVQ_Survivors             = 8;
        psEncC->warping_Q16                     = psEncC->fs_kHz * SILK_FIX_CONST( WARPING_MULTIPLIER, 16 );
    } else if( Complexity < 8 ) {
        psEncC->pitchEstimationComplexity       = SILK_PE_MID_COMPLEX;
        psEncC->pitchEstimationThreshold_Q16    = SILK_FIX_CONST( 0.72, 16 );
        psEncC->pitchEstimationLPCOrder         = 12;
        psEncC->shapingLPCOrder                 = 14;
        psEncC->la_shape                        = 5 * psEncC->fs_kHz;
        psEncC->nStatesDelayedDecision          = 3;
        psEncC->useInterpolatedNLSFs            = 0;
        psEncC->LTPQuantLowComplexity           = 0;
        psEncC->NLSF_MSVQ_Survivors             = 16;
        psEncC->warping_Q16                     = psEncC->fs_kHz * SILK_FIX_CONST( WARPING_MULTIPLIER, 16 );
    } else {
        psEncC->pitchEstimationComplexity       = SILK_PE_MAX_COMPLEX;
        psEncC->pitchEstimationThreshold_Q16    = SILK_FIX_CONST( 0.7, 16 );
        psEncC->pitchEstimationLPCOrder         = 16;
        psEncC->shapingLPCOrder                 = 16;
        psEncC->la_shape                        = 5 * psEncC->fs_kHz;
        psEncC->nStatesDelayedDecision          = MAX_DEL_DEC_STATES;
        psEncC->useInterpolatedNLSFs            = 1;
        psEncC->LTPQuantLowComplexity           = 0;
        psEncC->NLSF_MSVQ_Survivors             = 32;
        psEncC->warping_Q16                     = psEncC->fs_kHz * SILK_FIX_CONST( WARPING_MULTIPLIER, 16 );
    }

    /* Do not allow higher pitch estimation LPC order than predict LPC order */
    psEncC->pitchEstimationLPCOrder = silk_min_int( psEncC->pitchEstimationLPCOrder, psEncC->predictLPCOrder );
    psEncC->shapeWinLength          = SUB_FRAME_LENGTH_MS * psEncC->fs_kHz + 2 * psEncC->la_shape;
    psEncC->Complexity              = Complexity;

    silk_assert( psEncC->pitchEstimationLPCOrder <= MAX_FIND_PITCH_LPC_ORDER );
    silk_assert( psEncC->shapingLPCOrder         <= MAX_SHAPE_LPC_ORDER      );
    silk_assert( psEncC->nStatesDelayedDecision  <= MAX_DEL_DEC_STATES       );
    silk_assert( psEncC->warping_Q16             <= 32767                    );
    silk_assert( psEncC->la_shape                <= LA_SHAPE_MAX             );
    silk_assert( psEncC->shapeWinLength          <= SHAPE_LPC_WIN_MAX        );
    silk_assert( psEncC->NLSF_MSVQ_Survivors     <= NLSF_VQ_MAX_SURVIVORS    );

    return ret;
}

static inline opus_int silk_setup_LBRR(
    silk_encoder_state          *psEncC,            /* I/O                      */
    const opus_int32                 TargetRate_bps      /* I                        */
)
{
    opus_int   ret = SILK_NO_ERROR;
    opus_int32 LBRR_rate_thres_bps;

    psEncC->LBRR_enabled = 0;
    if( psEncC->useInBandFEC && psEncC->PacketLoss_perc > 0 ) {
        if( psEncC->fs_kHz == 8 ) {
            LBRR_rate_thres_bps = LBRR_NB_MIN_RATE_BPS;
        } else if( psEncC->fs_kHz == 12 ) {
            LBRR_rate_thres_bps = LBRR_MB_MIN_RATE_BPS;
        } else {
            LBRR_rate_thres_bps = LBRR_WB_MIN_RATE_BPS;
        }
        LBRR_rate_thres_bps = silk_SMULWB( silk_MUL( LBRR_rate_thres_bps, 125 - silk_min( psEncC->PacketLoss_perc, 25 ) ), SILK_FIX_CONST( 0.01, 16 ) );

        if( TargetRate_bps > LBRR_rate_thres_bps ) {
            /* Set gain increase for coding LBRR excitation */
            psEncC->LBRR_enabled = 1;
            psEncC->LBRR_GainIncreases = silk_max_int( 7 - silk_SMULWB( psEncC->PacketLoss_perc, SILK_FIX_CONST( 0.4, 16 ) ), 2 );
        }
    }

    return ret;
}
