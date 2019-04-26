// HPATC_G711ACodec.cpp: implementation of the HPATC_G711ACodec class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "HPATC_G711ACodec.h"


#ifdef __cplusplus
extern "C" {
#endif
#include "g711common.h"
#ifdef __cplusplus
}
#endif


HPATCDecoder*HPATCDecoder::CreateG711ADecoder(HPATCDecoderNotify&rHPATCDecoderNotify)
{
	return new HPATC_G711ADecoder(rHPATCDecoderNotify);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
HPATC_G711AEncoder::HPATC_G711AEncoder(HPATCEncoderNotify&rHPATCEncoderNotify)
:m_rHPATCEncoderNotify(rHPATCEncoderNotify)
,m_nSampleRate(0)
,m_nSamplesPerFrame(0)
,m_nBitrate(0)
,m_nBytesPerFrame(0)

,m_pEncoded(NULL)
{

}

HPATC_G711AEncoder::~HPATC_G711AEncoder(void)
{

}

int HPATC_G711AEncoder::Connect(int nSampleRate,int nSamplesPerFrame,int nBitrate,int nParam)
{
	m_nSampleRate=nSampleRate;
	m_nSamplesPerFrame=nSamplesPerFrame;
	m_nBitrate=nBitrate;
	m_nBytesPerFrame=m_nSamplesPerFrame;

	if (m_nBitrate!=64000)
	{
		return -1;
	}

	return 0;
}

void HPATC_G711AEncoder::ReleaseConnections(void)
{
	if (m_pEncoded!=NULL)
	{
		free(m_pEncoded);
		m_pEncoded=NULL;
	}
}

int HPATC_G711AEncoder::InputSamples(short*pSamples,int nSamples,unsigned long ulTimestamp)
{
	if (pSamples!=NULL && nSamples )
	{
		if (m_pEncoded==NULL ||
			m_nSamplesPerFrame<nSamples)
		{
			if (m_pEncoded!=NULL)
			{
				free(m_pEncoded);
				m_pEncoded=NULL;
			}

			m_nSamplesPerFrame=nSamples;

			m_pEncoded=(unsigned char*)malloc(m_nSamplesPerFrame);
			if (m_pEncoded==NULL)
			{
				return -1;
			}
		}

		if (m_pEncoded!=NULL)
		{
			for (int i=0;i<nSamples;i++)
			{
				m_pEncoded[i]=s16_to_alaw(pSamples[i]);
			}

			m_rHPATCEncoderNotify.OnHPATCEncoderNotifyOutput(m_pEncoded,nSamples,ulTimestamp);
			return 0;
		}
	}

	return -1;
}

HPATC_G711ADecoder::HPATC_G711ADecoder(HPATCDecoderNotify&rHPATCDecoderNotify)
:m_rHPATCDecoderNotify(rHPATCDecoderNotify)
,m_nSampleRate(0)
,m_nSamplesPerFrame(0)
,m_nBitrate(0)
,m_nBytesPerFrame(0)

,m_pSamples(NULL)
,m_ptr_plc(NULL)
{

}

HPATC_G711ADecoder::~HPATC_G711ADecoder(void)
{

}

int HPATC_G711ADecoder::Connect(int nSampleRate,int nSamplesPerFrame,int nBitrate,int nParam)
{
	m_nSampleRate=nSampleRate;
	m_nSamplesPerFrame=nSamplesPerFrame;
	m_nBitrate=nBitrate;
	m_nBytesPerFrame=m_nSamplesPerFrame;

	if (m_nBitrate!=64000)
	{
		return -1;
	}

	m_ptr_plc=new AUDEC_plc();
	if (0!=m_ptr_plc->Open(m_nSampleRate,m_nSamplesPerFrame))
	{
		m_ptr_plc->Close();
		delete m_ptr_plc;
		m_ptr_plc=NULL;
	}
	
	return 0;
}

void HPATC_G711ADecoder::ReleaseConnections(void)
{
	if (m_pSamples!=NULL)
	{
		free(m_pSamples);
		m_pSamples=NULL;
	}
	if (m_ptr_plc!=NULL)
	{
		m_ptr_plc->Close();
		delete m_ptr_plc;
		m_ptr_plc=NULL;
	}
}

int HPATC_G711ADecoder::InputStream(unsigned char*pEncoded,int nLen,bool bDiscontinious,unsigned long ulTimestamp)
{
	if (pEncoded!=NULL && nLen)
	{
		if (m_pSamples==NULL ||
			m_nSamplesPerFrame<nLen)
		{
			m_nSamplesPerFrame=nLen;

			if (m_pSamples!=NULL)
			{
				free(m_pSamples);
				m_pSamples=NULL;
			}

			m_pSamples=(short*)malloc(m_nSamplesPerFrame*sizeof(short));
			if (m_pSamples==NULL)
			{
				return -1;
			}
		}

		if (m_pSamples!=NULL)
		{
			if (bDiscontinious)
			{
				bDiscontinious=false;
				if (m_ptr_plc!=NULL)
				{
					m_ptr_plc->Recover(m_pSamples);
					m_rHPATCDecoderNotify.OnHPATCDecoderNotifyOutput(m_pSamples,nLen,m_nSampleRate,bDiscontinious,ulTimestamp-10);
				}
			}

			for (int i=0;i<nLen;i++)
			{
				m_pSamples[i]=(short)alaw_to_s16(pEncoded[i]);
			}

			if (m_ptr_plc!=NULL)
			{
				m_ptr_plc->Save(m_pSamples);
			}

			m_rHPATCDecoderNotify.OnHPATCDecoderNotifyOutput(m_pSamples,nLen,m_nSampleRate,bDiscontinious,ulTimestamp);
			return 0;
		}
	}

	return -1;
}


HPATCEncoder*CreateHPATC_G711AEncoder(HPATCEncoderNotify&rHPATCEncoderNotify)
{
	return new HPATC_G711AEncoder(rHPATCEncoderNotify);
}
