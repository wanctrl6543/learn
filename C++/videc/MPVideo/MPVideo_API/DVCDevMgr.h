//DVCDevMgr.h
#ifndef __DVCDEVMGR_H__
#define __DVCDEVMGR_H__

#include "VIDEC_Config.h"

#ifdef SUPPORT_DVC

#include <winsock2.h>
#include <windows.h>

#include "VIDEC.h"
 
class DVCDevMgr
{
public:
	static int Init(void);
	static void Terminate(void);

	static int GetFormatCount(void);
	static int GetFormatName(int nIndex,char*szName,int nMaxCount);
	static int GetFormatSize(int nIndex,int&nWidth,int&nHeight);
	static bool IsValidFormatSize(int&nWidth,int&nHeight);

	static int GetDevCount(void);
	static int GetDevName(unsigned int nDevIndex,char*szName,int nMaxCount);
	static int GetDevType(unsigned int nDevIndex,VIDEC_DEV_TYPE&nDevType);
	static bool HasAudioInput(unsigned int nDevIndex);
	static bool SupportHardwareEncoding(unsigned int nDevIndex);

	static int SetDevCap(unsigned int nDevIndex,int nFrameRate,int nBitrate,int nBitrateControlType,int nResolusion);
	static int SetVideoParam(unsigned int nDevIndex,int nBrightness/*����ֵ0-255*/, int nContrast/*�Աȶ�0-127*/, int nSaturation/*���Ͷ�0-127*/, int nHue/*ɫ��0-255*/,int nGamma/*٤��1-400*/,int nSharpen/*��0-127*/);
 	static int SetVideoGammaRGB(unsigned int nDevIndex,int nGammaR,int nGammaG,int nGammaB);
  	
	static int StartVideoStream(unsigned int nDevIndex,int nBitrate,int nQuant,int qmin,int qmax);
	static int RequestKeyFrame(unsigned int nDevIndex);
	static int StopVideoStream(unsigned int nDevIndex);

	static int AddImageSink(unsigned int nDevIndex,VIDEC_ImageSink*pImageSink);
	static void RemoveImageSink(unsigned int nDevIndex,VIDEC_ImageSink*pImageSink);

	static int AddStreamSink(unsigned int nDevIndex,VIDEC_StreamSink*pStreamSink);
	static void RemoveStreamSink(unsigned int nDevIndex,VIDEC_StreamSink*pStreamSink);

	static void SetInvert(unsigned int nDevIndex,int nInvert);
	static int GetInvert(unsigned int nDevIndex);
	static void SetDenoise(unsigned int nDevIndex,int nDenoise);
	static int GetDenoise(unsigned int nDevIndex);
	static void SetLevelFixer(unsigned int nDevIndex,int nLevelFixer);
	static int GetLevelFixer(unsigned int nDevIndex);
	
	static void EnableOSD(unsigned int nDevIndex,bool bEnable);
	static bool IsOSDEnable(unsigned int nDevIndex);
	static void SetOSDText(unsigned int nDevIndex,const char*cszText,int nAlign);
	static void SetOSDFont(unsigned int nDevIndex,LOGFONTA fontOSD,COLORREF crText,COLORREF crBk);
};

#endif

#endif