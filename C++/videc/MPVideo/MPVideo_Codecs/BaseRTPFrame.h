//BaseRTPFrame.h
#ifndef __BASERTPFRAME_H__
#define __BASERTPFRAME_H__

#include "XListPtr.h"
#include "XAutoLock.h"
#include "XBitrateRTP.h"


#ifdef RTP_VERSION
#undef RTP_VERSION
#endif
#define RTP_VERSION			0x02

#ifdef RTP_HEADER_LEN
#undef RTP_HEADER_LEN
#endif
#define RTP_HEADER_LEN		0x0C

/// RTP packet header
typedef struct tagRTP_HEADER
{
#if (1)
    unsigned short count:4;              // csrc count
    unsigned short extension:1;          // header extension flag
    unsigned short padding:1;            // padding flag - for encryption
    unsigned short version:2;            // protocol version


    unsigned short type:7;               // payload type
    unsigned short marker:1;             // marker bit - for profile
#else

    unsigned char version:2;             // protocol version
    unsigned char padding:1;             // padding flag - for encryption
    unsigned char extension:1;           // header extension flag
    unsigned char count:4;               // csrc count

    unsigned char marker:1;              // marker bit - for profile
    unsigned char type:7;                // payload type


#endif

    unsigned short sequence;          // sequence number of this packet 
                                    // (needs endian conversion here, 
                                    // done in the access methods )

    /// timestamp of this packet
    unsigned long timestamp;
    /// source of packet
    unsigned long ssrc;
}RTP_HEADER,*PRTP_HEADER;

class BaseRTPFrame;
class BaseRTPFrameCallback
{
public:
	BaseRTPFrameCallback(void){};
	virtual~BaseRTPFrameCallback(void){};
public:
	virtual void OnBaseRTPFrameCallbackRTPPacket(void*pPacketData,int nPacketLen){};
	virtual void OnBaseRTPFrameCallbackFramePacket(BaseRTPFrame*pBaseRTPFrame,void*pPacketData,int nPacketLen,int nKeyFrame){};
};

class BaseRTPFrame
	: public XBitrateRTP
{
public:
	BaseRTPFrame(BaseRTPFrameCallback&rCallback,int nMaxBitrate=6144);
	virtual~BaseRTPFrame(void);
public:
	virtual int Open(int nPayloadType,int nMaxRTPFrameSize,int nHeaderMargin=0);
	virtual void Close(void);
	virtual void SendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp);
	virtual void SendFrameHeader(unsigned char*pRTPPacket,int nPacketLen);
	virtual void DoSendFrame(const unsigned char*pFrameData,int nFrameLen,int nWidth,int nHeight,int nKeyFrame,unsigned long ulTimestamp)=0;
	virtual int GetFrame(unsigned char*pFrameBuf,int nBufLen);
	virtual void OnRecvdRTPPacket(void*pPacketData,int nPacketLen);
	virtual bool DoSendData(void);

	virtual int GetFrameTestOnly(unsigned char*pFrameBuf,int nBufLen);
	virtual int GetPacketCount(void);

	virtual void RunRTPThread(void);
protected:
	virtual void FlushRTPPackets(void);
	virtual int CalculateFrameSize(void);
	virtual void set_rtp_header(unsigned char*pHeader,bool bMarker);
	virtual int handle_rtp_packet(unsigned char*pPayloadData,int nPayloadLen,unsigned char*pFrameBuf,int nBufLen)=0;
	virtual int get_codec_header_len(void)=0;
protected:
	int						m_nPayloadType;
	int						m_nMaxRTPFrameSize;
	int						m_nMaxRTPPayloadBufLen;
	unsigned long			m_nRTPTimestamp;
	unsigned long			m_ulSSRC;
	unsigned short			m_usSeqNo; 

	BaseRTPFrameCallback&	m_rCallback;

	unsigned char*			m_pFrameBuf;
	int						m_nFrameBufLen;

	int						m_nHeaderMargin;

	unsigned long			m_nLastRecvdRTPTime;
	bool					m_bGotFrame;
	int						m_nKeyFrame;

	int						m_nMaxBitrate;
protected:
	class RTPFrame
	{
	public:
		RTPFrame(void)
			: pBuffer(NULL)
			, nLen(0)
			, bFirstPacket(false)
		{
		}
		virtual~RTPFrame(void)
		{
			if(pBuffer)
			{
				free(pBuffer);
				pBuffer=NULL;
			}
		}
	public:
		void Release(void)
		{
			if(pBuffer)
			{
				free(pBuffer);
				pBuffer=NULL;
			}

			delete this;
		}

		void*	pBuffer;
		int		nLen;
		bool	bFirstPacket;
	};

	XListPtr		m_ListRTPPacket;
	XCritSec		m_csListRTPPacket;
	int				m_nBufferedFrameCount;
	int				m_nMaxPacketsToSend;
	unsigned long	m_nLastSentPacketTimestamp;
protected:
	virtual void SendRTPPacket(RTPFrame*pRTPFrame);
	virtual void PacketsToFrame(void);
};

#endif