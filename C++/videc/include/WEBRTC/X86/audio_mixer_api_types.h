#ifndef _AUDIO_MIXER_API_TYPES_H
#define _AUDIO_MIXER_API_TYPES_H


enum AUDIO_CODEC_ID
{
							// CodecInfo:	pltype     plname	     plfreq pacsize channels rate	
	MIX_CODEC_PCMU = 0,			//				   0        PCMU		   8000   160      1     64000
	MIX_CODEC_PCMA,				//				   8        PCMA           8000   160      1     64000
	MIX_CODEC_G722,				//				   9        G722          16000   320      1     64000

	// aac lc adts for output
	MIX_CODEC_AACLC_ADTS_64K,	//				  80	 aaclc_adts_64    48000  1024	   1	 64000

	// aac ld eld eldsbr not support now
	MIX_CODEC_AACLD_LOAS_64K,	//				  81	 aacld_loas_64    48000   480	   1	 64000
	MIX_CODEC_AACELD_LOAS_64K,	//				  82	aaceld_loas_64    48000   960	   1	 64000
	MIX_CODEC_AACELDSBR_LOAS_64K,//				  83   aaceldsbr_loas_64  48000   480	   1	 64000

	MIX_CODEC_OPUS,				//				 120       opus           48000   960      1     64000	
	MIX_CODEC_G7221_24K,		//				 121     G722.1_24        16000   320      1     24000
	MIX_CODEC_G7221_32K,		//				 122     G722.1_32        16000   320      1     32000
	MIX_CODEC_G7221C_24K,		//				 123     G722.1C_24       32000   640      1     24000
	MIX_CODEC_G7221C_32K,		//				 124     G722.1C_32       32000   640      1     32000
	MIX_CODEC_G7221C_48K,		//               125     G722.1C_48       32000   640      1     48000
	
	// PCM data for output
	CODEC_PCM_48K,			//				   1       PCM_48K		  48000	  960	   1	384000

	MIX_CODEC_INVALID
};

struct CodecInfo {
	int pltype;			// rtp payload type
	char plname[32];	// codec name
	int plfreq;			// frequency
	int pacsize;		// 1 frame packet pcm samples 
						// (pcma pcmu g722 g7221c opus aac_eld):20ms samples
						// (aac_lc):1024 samples
						// (aac_ld aac_eld_sbr): 10ms samples
	int channels;		// codec channels
	int rate;			// bitrate
};

class AudioMixer_Callback {
public:
	/* 混音编码后的数据
	 * @param out_channel: 输出通道号
	 * @param data: 混音编码后数据
	 * @param len:  data长度
	 * @return ret: no need
	 */
	virtual int OnMixedData (int out_channel, const char* data, int len) = 0;
protected:
	~AudioMixer_Callback () {};
};

#endif // !_AUDIO_MIXER_API_TYPES_H