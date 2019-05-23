//NETEC_MediaSender.h
#ifndef __NETEC_MEDIASENDER_H__
#define __NETEC_MEDIASENDER_H__

#include <NETEC/NETEC_Export.h>

#define MEDIA_SENDER_NOT_STARTED		0x00000001
#define MEDIA_SENDER_CONNECTING			0x00000002
#define MEDIA_SENDER_CONNECTED			0x00000004
#define MEDIA_SENDER_DISCONNECTED		0x00000008

class NETEC_MediaSenderCallback
{
public:
	NETEC_MediaSenderCallback(void){};
	virtual~NETEC_MediaSenderCallback(void){};
public:
	virtual void OnNETEC_MediaSenderCallbackRecvdPTZ(void*pData,int32_t nLen){};
	virtual void OnNETEC_MediaSenderCallbackRecvdCtrl(void*pData,int32_t nLen){};

	virtual void OnNETEC_MediaSenderCallbackBitrateChanged(uint32_t nBitrate,uint32_t nFrameRate){};
};

//ý�巢����
class NETEC_API NETEC_MediaSender
{
public:
	NETEC_MediaSender(void){};
	virtual~NETEC_MediaSender(void){};
public:
	/******************************************************************************
	* Open
	*��������
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t Open(void)=0;

	/******************************************************************************
	* Close
	*�������ر�
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* StartAudio
	*������������Ƶ
	*���룺	ulAudioID	-��Ƶ��ʶ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t StartAudio(uint32_t ulAudioID)=0;

	/******************************************************************************
	* IsAudioStarted
	*��������ȡ�Ƿ���������Ƶ
	*���룺	��
	*����� ��
	*����ֵ���Ƿ���������Ƶ,��0Ϊ��,0Ϊ��
	*****************************************************************************/
	virtual int32_t IsAudioStarted(void)=0;

	/******************************************************************************
	* StopAudio
	*������ֹͣ��Ƶ
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void StopAudio(void)=0;

	/******************************************************************************
	* GetAudioID
	*��������ȡ��Ƶ��ʶ
	*���룺	��
	*����� ulAudioID	-��Ƶ��ʶ
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetAudioID(uint32_t&ulAudioID)=0;

	/******************************************************************************
	* IsAudioEnable
	*��������ȡ��Ƶ�Ƿ����˽���
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����>=0��0:���˽��գ��������˽��ա���ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t IsAudioEnable(void)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetAudioPacketStatistics(uint32_t&ulTotalPackets,uint32_t&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetAudioNetworkStatus
	*��������ȡ��Ƶ������״̬
	*���룺	��
	*����� nNetworkStatus	-������[0-100]
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetAudioNetworkStatus(uint32_t&nNetworkStatus)=0;

	/******************************************************************************
	* SendAudio
	*������������Ƶ���ݰ�
	*���룺	pData			-���ݰ�ָ��
			nLen			-���ݰ�����
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t SendAudio(unsigned char*pData,int32_t nLen)=0;

	/******************************************************************************
	* StartVideo
	*����������������Ƶ
	*���룺	ulVideoID	-������Ƶ��ʶ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t StartVideo(uint32_t ulVideoID)=0;

	/******************************************************************************
	* IsVideoStarted
	*��������ȡ�Ƿ�������������Ƶ
	*���룺	��
	*����� ��
	*����ֵ���Ƿ�������������Ƶ��0Ϊ��,0Ϊ��
	*****************************************************************************/
	virtual int32_t IsVideoStarted(void)=0;

	/******************************************************************************
	* StopVideo
	*������ֹͣ������Ƶ
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void StopVideo(void)=0;

	/******************************************************************************
	* GetVideoID
	*��������ȡ������Ƶ��ʶ
	*���룺	��
	*����� ulVideoID	-������Ƶ��ʶ
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetVideoID(uint32_t&ulVideoID)=0;

	/******************************************************************************
	* IsVideoRequestKeyFrame
	*��������ȡ������Ƶ�Ƿ���������ؼ�֡
	*���룺	nFrameType	-֡����[Main:0 Sub:1 QSub:2]
	*����� ��
	*����ֵ���ɹ�����>=0��0:��������ؼ�֡��������������ؼ�֡����ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t IsVideoRequestKeyFrame(int32_t nFrameType)=0;

	/******************************************************************************
	* IsVideoBlocking
	*��������ȡ������Ƶ�����Ƿ�����
	*���룺	nFrameType	-֡����[Main:0 Sub:1 QSub:2]
	*����� ��
	*����ֵ���ɹ�����>=0��0:���Ͳ�����������������������������ʱ����Բ�ѹ����Ƶ����ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t IsVideoBlocking(int32_t nFrameType)=0;

	/******************************************************************************
	* IsVideoEnable
	*��������ȡ��Ƶ�Ƿ����˽���
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����>=0��0:���˽��գ��������˽��ա���ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t IsVideoEnable(void)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*��������ȡ������Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetVideoPacketStatistics(uint32_t&ulTotalPackets,uint32_t&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate)=0;

	/******************************************************************************
	* GetVideoNetworkStatus
	*��������ȡ������Ƶ������״̬
	*���룺	��
	*����� nNetworkStatus	-������[0-100]
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t GetVideoNetworkStatus(uint32_t&nNetworkStatus)=0;

	/******************************************************************************
	* SendVideo
	*������������Ƶ���ݰ�
	*���룺	pData			-���ݰ�ָ��
			nLen			-���ݰ�����
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int32_t SendVideo(unsigned char*pData,int32_t nLen)=0;

	virtual void SetMaxBitrate(int32_t nMaxBitrate)=0;

	/******************************************************************************
	* Create
	*����������NETEC_MediaSender
	*���룺	��
	*����� ��
	*����ֵ��NETEC_MediaSender����ָ��
	*****************************************************************************/
	static NETEC_MediaSender*Create(NETEC_MediaSenderCallback&rCallback);
};

#endif