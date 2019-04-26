//VIDEC_CodecDef.h
#ifndef __VIDEC_CODECDEF_H__
#define __VIDEC_CODECDEF_H__


typedef enum {
	VIDEC_CODEC_H261=0,		//unsupport	
	VIDEC_CODEC_H263,		
	VIDEC_CODEC_H263P,		
	VIDEC_CODEC_H263PP,		//same to H263P		
	VIDEC_CODEC_H264,
	VIDEC_CODEC_LSCC,		//unsupport
	VIDEC_CODEC_AH400,
	VIDEC_CODEC_MPEG4,		//unsupport
	VIDEC_CODEC_DH264,
	VIDEC_CODEC_HIKH,
	VIDEC_CODEC_H264_SVC,
	VIDEC_CODEC_HIKC,
	VIDEC_CODEC_MJPG,
	VIDEC_CODEC_COUNT
}VIDEC_CODEC_TYPE;

#define ENABLE_VIDEC_CODEC_H263		1
#define ENABLE_VIDEC_CODEC_H263P	1
#define ENABLE_VIDEC_CODEC_H264		1
#define ENALBE_VIDEC_CODEC_AH400	1
#define ENABLE_VIDEC_CODEC_DH264	1
#define ENABLE_VIDEC_CODEC_HIKH		1
#define ENABLE_VIDEC_CODEC_H264_SVC	1


#endif
