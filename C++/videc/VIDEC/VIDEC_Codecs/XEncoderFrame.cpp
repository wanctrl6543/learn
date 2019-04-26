#include <stdlib.h>
#include <memory.h>

#include "VIDEC_Header.h"
#include "XEncoderFrame.h"
#include "XEncoderFrameH263.h"
#include "XEncoderFrameH263P.h"
#include "XEncoderFrameH264.h"
#include "XEncoderFrameI264.h"
#include "XEncoderFrameMPEG4.h"

#include "XUtil.h"

#include "AVCONH264Header.h"

#include "../VIDEC_FRE/RTTimer.h"//??


bool TryH264HardwareEncoding(int nWidth,int nHeight)
{
	return (IntelEncoderTry(nWidth,nHeight)==0?true:false);

	return false;
}


VIDEC_API VIDEC_Encoder*VIDEC_EncoderCreate(VIDEC_EncoderCallback&rCallback,int nWidth,int nHeight,int nFrameRate,VIDEC_CODEC_TYPE codecType,bool bDoubleField,int nBitrate,int nMinQP,int nMaxQP,int nBitrateControlType,bool bRTPPacket)
{
	DebugOutput( logcallstack ,"VIDEC_EncoderCreate  int nWidth=%d,int nHeight=%d,int nFrameRate=%d,VIDEC_CODEC_TYPE codecType=%d,bool bDoubleField=%d,int nBitrate=%d,int nMinQP=%d,int nMaxQP =%d,int nBitrateControlType =%d,bool bRTPPacket =%d \n",
		 nWidth, nHeight, nFrameRate, codecType, bDoubleField, nBitrate, nMinQP, nMaxQP, nBitrateControlType, bRTPPacket);//??

	XEncoderFrame*pXEncoderFrame=NULL;
	bool bHardwareEncoding=false;
	switch (codecType)
	{
	case VIDEC_CODEC_H263:
		{
			NEWRECORD( pXEncoderFrame,new XEncoderFrameH263(rCallback,bRTPPacket) )
		}
		break;
	case VIDEC_CODEC_MPEG4:
		{
			NEWRECORD( pXEncoderFrame,new XEncoderFrameMPEG4(rCallback,bRTPPacket) )
		}
		break;
	case VIDEC_CODEC_H263P:
		{
			NEWRECORD( pXEncoderFrame,new XEncoderFrameH263P(rCallback,bRTPPacket) )
		}
		break;
	case VIDEC_CODEC_H264:
	case VIDEC_CODEC_H264_SVC:
	default:
		{
			if (TryH264HardwareEncoding(nWidth,nHeight))
			{
				DebugOutput( logcallstack ,"VIDEC_EncoderCreate TryH264HardwareEncoding\n");//??
				bHardwareEncoding=true;
				NEWRECORD( pXEncoderFrame,new XEncoderFrameI264(rCallback,bRTPPacket,codecType) )
			}
			else
			{
				DebugOutput( logcallstack ,"VIDEC_EncoderCreate Not TryH264HardwareEncoding \n");//??
				NEWRECORD( pXEncoderFrame,new XEncoderFrameH264(rCallback,bRTPPacket,codecType) )
			}
		}
		break;
	}
//NULLReturnRet( pXEncoderFrame , pXEncoderFrame )  
	if (pXEncoderFrame!=NULL)
	{
		if (0!=pXEncoderFrame->Open(nWidth,nHeight,nFrameRate,bDoubleField,nBitrate,nMinQP,nMaxQP,nBitrateControlType))
		{
			pXEncoderFrame->Close();
			delete pXEncoderFrame;
			pXEncoderFrame=NULL;

			if (bHardwareEncoding)
			{
				bHardwareEncoding=false;
				NEWRECORD( pXEncoderFrame,new XEncoderFrameH264(rCallback,bRTPPacket,codecType) )
				NULLReturnRet( pXEncoderFrame , pXEncoderFrame )  
				if (0!=pXEncoderFrame->Open(nWidth,nHeight,nFrameRate,bDoubleField,nBitrate,nMinQP,nMaxQP,nBitrateControlType))
				{
					pXEncoderFrame->Close();
					delete pXEncoderFrame;
					pXEncoderFrame=NULL;
				}
			}
		}
	}
	
	if (pXEncoderFrame)
	{
		pXEncoderFrame->m_bHardwareEncoding = bHardwareEncoding;
	}

	return pXEncoderFrame;
}


XEncoderFrame::XEncoderFrame(VIDEC_EncoderCallback&rCallback,bool bRTPPacket)
:m_rCallback(rCallback)
,m_bRTPPacket(bRTPPacket)

,m_nWidth(0)
,m_nHeight(0)
,m_pPacketBuf(NULL)
,m_nFrameSize(0)
,m_nYImageSize(0)

,m_usSeqNo(0)

,m_nRequestKeyFrame(1)

,m_bDoubleField(false)
,m_bEventFirst(true)

,m_nBitrate(384)
,m_nMinQP(4)
,m_nMaxQP(51)
,m_nBitrateControlType(VIDEC_NETWORK_INTERNET)

,m_nFrameRate(30)
,m_bHardwareEncoding(false)
,m_nLastKeyFrameTimestamp(XGetTimestamp())
{
	m_nVirtualWidth=0;
	m_nVirtualHeight=0;

	srand(XGetTimestamp());
	m_usSeqNo=rand();

	m_bHardware=false;
	m_nTimestamp=0;
}

XEncoderFrame::~XEncoderFrame(void)
{
}

int XEncoderFrame::Open(int nWidth,int nHeight,int nFrameRate,bool bDoubleField,int nBitrate,int nMinQP,int nMaxQP,int nBitrateControlType)
{
	m_nWidth=nWidth;
	m_nHeight=nHeight;
	m_nYImageSize=m_nWidth*m_nHeight;
	m_nFrameSize=m_nYImageSize*3/2;

	m_nStride[0]=m_nWidth;
	m_nStride[1]=m_nWidth>>1;
	m_nStride[2]=m_nWidth>>1;

	m_bDoubleField=bDoubleField;//=false;

	m_nBitrate=nBitrate;
	m_nMinQP=nMinQP;
	m_nMaxQP=nMaxQP;
	m_nFrameRate=nFrameRate;
	m_nBitrateControlType=nBitrateControlType;

	//m_bWaitStop = false;
	//StartThread();

	return 0;
}

void XEncoderFrame::Close(void)
{
	if (m_pPacketBuf)
	{
		FREEMSG(m_pPacketBuf);
		m_pPacketBuf=NULL;
	}

	//m_bWaitStop = true;
	//WaitForStop();

	{
		XAutoLock l(m_csListPacketData);
		while (m_listPacketData.size())
		{
			XEncodDataBuffer*pXPacketBuffer=(XEncodDataBuffer*)m_listPacketData.front();
			m_listPacketData.pop_front();
			if (pXPacketBuffer)
			{			
				delete pXPacketBuffer;
				pXPacketBuffer=NULL;
			}
		}
	}
}



int XEncoderFrame::EncodeFrame(void*pFrameData,int nFrameSize,int nVirtualWidth,int nVirtualHeight,bool bEventFieldFirst,bool bHardware,unsigned long nTimestamp)
{
	if (m_pPacketBuf==NULL)
	{
		m_pPacketBuf=(unsigned char*)MALLOCMSG(m_nFrameSize);
		if (m_pPacketBuf==NULL)
			return -1;
	}

	m_bHardware=bHardware;
	m_nTimestamp=nTimestamp;

	m_bEventFirst=bEventFieldFirst;
	m_nVirtualWidth=nVirtualWidth;
	m_nVirtualHeight=nVirtualHeight;

	unsigned char*pData[3];
	unsigned char*pPacketData=NULL;

	pData[0]=(unsigned char*)pFrameData;
	pData[1]=pData[0]+m_nYImageSize;
	pData[2]=pData[1]+(m_nYImageSize>>2);

	pPacketData=m_pPacketBuf+4+VIDEC_HEADER_EXT_KEY_FRAME_LEN;
	int nPacketLen=m_nFrameSize;
	int nKeyFrame=0;

	if (m_nRequestKeyFrame)
	{
		m_nRequestKeyFrame=0;
		nKeyFrame=1;

		m_nLastKeyFrameTimestamp=XGetTimestamp();
	}
	else
	{
		unsigned long nTempTimestamp=XGetTimestamp();
		if (nTempTimestamp-m_nLastKeyFrameTimestamp>=VIDEC_GetMaxKeyFrameInterval())
		{
			m_nLastKeyFrameTimestamp=nTempTimestamp;
			//?? why
			if (GetCodecType()!=VIDEC_CODEC_H264 &&
				GetCodecType()!=VIDEC_CODEC_H264_SVC)
			{
				nKeyFrame=1;
			}
		}
	}

	int nBFrame=0;
	if (0!=DoEncodeFrame(pData,m_nStride,pPacketData,nPacketLen,nKeyFrame,nBFrame))
	{
		nPacketLen=0;
		return -1;
	}

	if (AsyncEncoding())
	{
		return 0;
	}

	if (nPacketLen>0)
	{
		int nHeaderLen=(nKeyFrame!=0)?VIDEC_HEADER_EXT_KEY_FRAME_LEN:VIDEC_HEADER_EXT_LEN;
		if (nKeyFrame && bHardware)
		{
			unsigned char*pFrameHeader=(unsigned char*)pPacketData-4;
			memset(pFrameHeader,0,4);
			PAVCON_H264_HEADER pAVCONH264Header=(PAVCON_H264_HEADER)pFrameHeader;
			pAVCONH264Header->ID=0xFFFF;
			pAVCONH264Header->framerate=m_nFrameRate;
			nHeaderLen+=4;
		}
		pPacketData-=nHeaderLen;

		OnPacketData(pPacketData,nPacketLen,nKeyFrame,nBFrame,bHardware,nTimestamp);

		return 0;
	}

	return -1;
}

void XEncoderFrame::OnPacketData(unsigned char*pPacketData,int nPacketLen,int nKeyFrame,int nBFrame,bool bHardware,unsigned long nTimestamp)
{
	int nHeaderLen=(nKeyFrame!=0)?VIDEC_HEADER_EXT_KEY_FRAME_LEN:VIDEC_HEADER_EXT_LEN;

	if (nKeyFrame && bHardware)
	{
		nHeaderLen+=4;
	}

	VIDEC_HEADER_EXT_RESET(pPacketData);
	VIDEC_HEADER_EXT_SET_CODEC_ID(pPacketData,GetCodecType());
	VIDEC_HEADER_EXT_SET_EVEN_FIELD_FIRST(pPacketData,m_bEventFirst?1:0);
	VIDEC_HEADER_EXT_SET_DOUBLE_FIELD(pPacketData,m_bDoubleField?1:0);
	VIDEC_HEADER_EXT_SET_HARDWARE(pPacketData,bHardware?1:0);
	VIDEC_HEADER_EXT_SET_KEYFRAME(pPacketData,(nKeyFrame!=0?1:0));
	VIDEC_HEADER_EXT_SET_BFRAME(pPacketData,(nBFrame!=0?1:0));

	VIDEC_HEADER_EXT_SET_SEQUENCE(pPacketData,m_usSeqNo++);
	VIDEC_HEADER_EXT_SET_TIMESTAMP(pPacketData,nTimestamp);
	if (nKeyFrame)
	{
		VIDEC_HEADER_EXT_SET_ACTUAL_WIDTH(pPacketData,m_nWidth);
		VIDEC_HEADER_EXT_SET_ACTUAL_HEIGHT(pPacketData,m_nHeight);
		VIDEC_HEADER_EXT_SET_VIRTUAL_WIDTH(pPacketData,m_nVirtualWidth);
		VIDEC_HEADER_EXT_SET_VIRTUAL_HEIGHT(pPacketData,m_nVirtualHeight);
	}
	//XEncodDataBuffer*pXPacketBuffer=new XEncodDataBuffer;
	//if (pXPacketBuffer)
	//{
	//	pXPacketBuffer->pData=MALLOCMSG(nHeaderLen+nPacketLen);
	//	if (pXPacketBuffer->pData)
	//	{
	//		memcpy((char*)pXPacketBuffer->pData,(char*)pPacketData,nHeaderLen+nPacketLen);
	//		pXPacketBuffer->nDatalen=nHeaderLen+nPacketLen;
	//	}
	//	else
	//	{
	//		delete pXPacketBuffer;
	//		pXPacketBuffer=NULL;
	//	}
	//}
	//if (pXPacketBuffer)
	//{
	//	XAutoLock l(m_csListPacketData);
	//	m_listPacketData.push_back(pXPacketBuffer);
	//}
	m_rCallback.OnVIDEC_EncoderCallbackFramePacket(pPacketData,nHeaderLen+nPacketLen,m_bHardwareEncoding);
}


void XEncoderFrame::ThreadProcMain(void)
{
	while(!m_bWaitStop)
	{
		XEncodDataBuffer*pXSurfaceBuffer=NULL;
		{
			XAutoLock l(m_csListPacketData);
			if (m_listPacketData.size())
			{
				pXSurfaceBuffer=(XEncodDataBuffer*)m_listPacketData.front();
				m_listPacketData.pop_front();	
			}
		}
		if (pXSurfaceBuffer!=NULL)
		{			
			m_rCallback.OnVIDEC_EncoderCallbackFramePacket(pXSurfaceBuffer->pData,pXSurfaceBuffer->nDatalen,m_bHardwareEncoding);
			delete pXSurfaceBuffer;
			pXSurfaceBuffer=NULL;
		}
		else
		{
			Sleep(1);
		}
	}
}

void XEncoderFrame::RequestKeyFrame(void)
{
	m_nRequestKeyFrame=1;
}
