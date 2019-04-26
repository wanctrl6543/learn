//IMXEC_MediaChannel.h
#ifndef __IMXEC_MEDIACHANNEL_H__
#define __IMXEC_MEDIACHANNEL_H__

#include <IMXEC/IMXEC_Export.h>
#include <IMXEC/IMXEC_Call.h>
#include <VIDEC/VIDEC.h>
#include <AUDEC/AUDEC_CodecID.h>
#include <NETEC/NETEC.h>
#include <VIDECVQD/VIDECVQDAPI.h>

class IMXEC_CapChanCallback
{
public:
	IMXEC_CapChanCallback(void){};
	virtual~IMXEC_CapChanCallback(void){};
public:
	//音频数据回调函数
	virtual void OnIMXEC_CapChanCallbackAudioData(unsigned char*pData,int nLen,bool&bLoop){};
	virtual void OnIMXEC_CapChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp){};
	//视频数据回调函数
	//nKeyFrame,0:非关键帧 1:关键帧
	virtual void OnIMXEC_CapChanCallbackVideoData(unsigned char*pData,int nLen,int nKeyFrame){};
	virtual void OnIMXEC_CapChanCallbackMotionDetected(int*pResultList,int nResultCount){};//pResultList[i]==0,没有动，否则在动

	virtual void OnIMXEC_CapChanCallbackFilePositionChanged(unsigned long ulSeconds){};
	virtual void OnIMXEC_CapChanCallbackFilePause(void){};
	virtual void OnIMXEC_CapChanCallbackFilePlay(void){};
	virtual void OnIMXEC_CapChanCallbackFileEnd(void){};
	virtual void OnIMXEC_CapChanCallbackRecvdCtrlData(void*pData,int nLen){};

	virtual void OnIMXEC_CapChanCallbackAudioIDChanged(unsigned long nAudioID){};
	virtual void OnIMXEC_CapChanCallbackVideoDevOpen(void){};

	virtual void OnIMXEC_CapChanCallbackVideoSignalChanged(void){};
	virtual void OnIMXEC_CapChanCallbackVQDResult(unsigned long nResult){};

	/*实施回调D3D9渲染视频图像后的DC，可对DC进行绘制，仅本地有用不影响远程或录制*/
	virtual void OnIMXEC_CapChanCallbackDrawD3D9DC(void* hDC/*HDC*/){};
};

class IMXEC_API IMXEC_CapChanDev
{
public:
	IMXEC_CapChanDev(void){};
	virtual~IMXEC_CapChanDev(void){};
public:
	//打开通道
	virtual int Open(HWND hwndParent,int nOnlyPreview)=0;
	//关闭通道
	virtual void Close(void)=0;

	virtual void EnablePreview(int nPreview)=0;

	//取视频窗口
	virtual HWND GetVideoWnd(void)=0;
	//取视频宽度
	virtual int GetVideoWidth(void)=0;
	//取视频高度
	virtual int GetVideoHeight(void)=0;

	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 
	//保持当前图象到BMP文件
	virtual bool CaptureToBMPFile(const char*cszFile)=0;


	/******************************************************************************
	* SetScreenWnd
	*描述：设置所在屏幕窗口位置
	*输入：	nScreenIndex	-屏幕号
			nWndIndex		-窗口号
			nFullScreen		-是否全屏显示【0：普通显示，非0：全屏显示】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;

	/******************************************************************************
	* SetVideoWndBk
	*描述：设置视频窗口没有码流时的背景
	*输入：	szBkImage	- 背景图片的全路径（只支持bmp图片）
	        nVideoWnBkR,nVideoWnBkG,nVideoWnBkB  背景颜色
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetVideoWndBk(const char* szBkImage = NULL, int nVideoWnBkR = -1, int nVideoWnBkG = -1, int nVideoWnBkB = -1)=0;

	//设置音量
	virtual int SetVolume(int nVolume)=0;
	//设置音量
	virtual int GetVolume()=0;
	//取当前音值
	virtual int GetLevel(int&nLevel)=0;

	virtual unsigned long GetAudioID(void)=0;
	virtual unsigned long GetVideoID(void)=0;

	//打开视频设备
	virtual int OpenVideoDev(int nDevID,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0,const char*cszDCIP=NULL,unsigned short nDVCPort=4222,const char*cszDVCPassword=NULL,int nSubWidth=0,int nSubHeight=0,int nSubBitrate=0,int nQSubWidth=0,int nQSubHeight=0,int nQSubBitrate=0)=0;
	virtual int OpenVideoDev(int x,int y,int cx,int cy,int nBitCount,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0,HDC hDC=NULL,int nSubWidth=0,int nSubHeight=0,int nSubBitrate=0,int nQSubWidth=0,int nQSubHeight=0,int nQSubBitrate=0)=0;
	virtual int OpenVideoDev(const char*cszMediaFile,int nLoop,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0,int nSubWidth=0,int nSubHeight=0,int nSubBitrate=0,int nQSubWidth=0,int nQSubHeight=0,int nQSubBitrate=0)=0;
	//nScreenType[0:本地视频混合,1:屏幕模版区域混合（本地+远程+白板+共享文档）]
	virtual int OpenVideoDev(int nScreenIndex,int nScreenType,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub,int nQSub,int nSubWidth=0,int nSubHeight=0,int nSubBitrate=0,int nQSubWidth=0,int nQSubHeight=0,int nQSubBitrate=0)=0;

	/******************************************************************************
	* IsVideoDevOpen
	*描述：获取是否已经打开视频设备
	*输入：无
	*输出：	无
	*返回值：为true时已经打开视频设备，否则没有打开
	*****************************************************************************/
	virtual bool IsVideoDevOpen(void)=0;

	//关闭视频设备
	virtual void CloseVideoDev(void)=0;
 	
	/******************************************************************************
	* SetForceEncodeVideo
	*描述：设置是否强制压缩视频【录像时或者本地环回测试时，设置为非0，其他时候请设置为0，以节省资源】
	*输入：nForceEncodeVideo	-是否强制压缩视频【0:有人接收的时候压缩视频,非0：任何时候都压缩视频】
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetForceEncodeVideo(int nForceEncodeVideo)=0;

	/******************************************************************************
	* RequestKeyFrame
	*描述：请求关键帧
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void RequestKeyFrame(void)=0;

	virtual void SetInvert(int nInvert)=0;
	virtual int GetInvert(void)=0;
	virtual void SetDenoise(int nDenoise)=0;
	virtual int GetDenoise(void)=0;

	//设置遮掩并启动遮掩
	virtual int SetupMask(RECT *RectList, int iRectCount)=0;
	//停止遮掩
	virtual int StopMask(void)=0;
	virtual int StartMotionDetect(void)=0;
	virtual int StopMotionDetect(void)=0;
	virtual int SetupMotionDetect(int iGrade/*灵敏度等级0-6*/,RECT *RectList, int iRectCount)=0;
	virtual bool GetMotionImageSize(int&nWidth,int&nHeight)=0;
 	
	/******************************************************************************
	* EnableOSD
	*描述：设置是否显示OSD
	*输入：	bEnable			-是否显示OSD,为true时显示，否则不显示
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void EnableOSD(bool bEnable)=0;

	/******************************************************************************
	* IsOSDEnable
	*描述：获取是否显示OSD
	*输入：无
	*输出：无
	*返回值：为true时显示，否则不显示
	*****************************************************************************/
	virtual bool IsOSDEnable(void)=0;

	/******************************************************************************
	* SetOSDText
	*描述：设置OSD的文本
	*输入：	cszText			-要显示的文本
			nAlign			-对齐方式，参考VIDEC.h中的VIDEC_OSD_ALIGN_TOP_LEFT的定义
			nTop,nLeft		OSD位置坐标，如果都 >= 0，那么 nAlign设置无效，以nTop,nLeft位置为准。
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetOSDText(const char*cszText,int nAlign=VIDEC_OSD_ALIGN_TOP_LEFT,int nTop=-1,int nLeft=-1)=0;//Align==0 TOP_LEFT 1:BOTOM_LEFT,2:TOP_CENTER,3:BOTTOM_CENTER,4:TOP_RIGHT,5:BOTTOM_RIGHT

	/******************************************************************************
	* SetOSDFont
	*描述：设置OSD的字体
	*输入：	logfont			-OSD的字体
			crText			-OSD的文本的颜色
			crBk			-OSD的文本的背景颜色
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetOSDFont(LOGFONTA logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255))=0;
	//设置视频属性
	virtual int SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/,bool bSharpenLocalOnly=true)=0;
	
	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
	
	virtual bool HasVideoAdjustWnd(void)=0;
	virtual void ShowAdjustVideoWnd(void)=0;
	virtual void ShowVideoInputWnd(void)=0;
	virtual bool HasVideoInputWnd(void)=0;
	virtual int TVTunerPutChannel(long lChannel)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*描述：获取视频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
			nBitrate			-码流【bps】
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	//打开音频通道
	//nDevID:音频采集设备号，-2从采集卡中采集音频，>=-1从声卡中采集音频
	//CodecType:编码类型
	virtual int OpenAudio(int nDevID,X_AUDIO_CODEC_ID CodecType)=0;

	/******************************************************************************
	* IsAudioOpen
	*描述：获取是否已经打开音频
	*输入：无
	*输出：	nDevID		-音频采集设备号，-2从采集卡中采集音频，>=-1从声卡中采集音频
			CodecType	-编码类型
	*返回值：为true时已经打开音频，否则没有打开
	*****************************************************************************/
	virtual bool IsAudioOpen(int&nDevID,X_AUDIO_CODEC_ID&CodecType)=0;

	//关闭音频通道
	virtual void CloseAudio(void)=0;
 	
	/******************************************************************************
	* SetForceEncodeAudio
	*描述：设置是否强制压缩音频【录像时或者本地环回测试时，设置为非0，其他时候请设置为0，以节省资源】
	*输入：nForceEncodeAudio	-是否强制压缩音频【0:有人接收的时候压缩音频,非0：任何时候都压缩音频】
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetForceEncodeAudio(int nForceEncodeAudio)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*描述：获取音频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
			nBitrate			-码流【bps】
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;
	virtual void Seek(unsigned long ulSeconds)=0;
	virtual void Pause(void)=0;
	virtual void Play(void)=0;
	virtual void SetMute(bool bMute=true)=0;
	virtual bool IsMute()=0;

	/******************************************************************************
	* StartRecordToAVI
	*描述：开始辅流录像
	*输入：	cszPathName			-录像文件名称
			nStandardFormat		-是否录制成标准文件格式
			nCacheTimeMS        -视频等待音频的时间
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartRecordToAVI(const char*cszPathName,int nStandardFormat=1, int nCacheTimeMS = 10000)=0;
	
	/******************************************************************************
	* StopRecordToAVI
	*描述：停止辅流录像
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void StopRecordToAVI(void)=0;

	/******************************************************************************
	* SendPTZ
	*描述：发送PTZ【发送云台控制命令】
	*输入：	nPTZAction		-云台动作
			nSpeed			-动作的速度
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SendPTZ (PTZ_ACTION nPTZAction,int nSpeed)=0;

	virtual VIDEC_Image*GetImage(void)=0;

	static IMXEC_CapChanDev*Create(IMXEC_CapChanCallback&rCallback);

	//取设备个数
	static int GetDevCount(void);
	//取设备名称
	static int GetDevName(int nDevID,char*szName,int nMaxCount);
	
	//取设备类型
	static int GetDevType(int nDevID,VIDEC_DEV_TYPE&nDevType);

	//列出格式的个数
	static int GetFormatCount(VIDEC_DEV_TYPE nDevType);
	//取格式名称
	static int GetFormatName(VIDEC_DEV_TYPE nDevType,int nIndex,char*szName,int nMaxCount);
	//取格式大小
	static int GetFormatSize(VIDEC_DEV_TYPE nDevType,int nIndex,int&nWidth,int&nHeight);
	//判断视频设备是否有音频输入
	static bool HasAudioInput(int nDevID);

	//获取音频输入设备
	static int GetMicDevNum();
	static int GetMicDevName(int nIndex, char* szName, int nMaxCount);
	static int SetMicDev(int nIndex);

	static void EnableAudioSend(bool bEnable);
	static bool IsEnableAudioSend(void);
	static void EnableVideoSend(bool bEnable);
	static bool IsEnableVideoSend(void);

	static unsigned long GetTotalBytes(void);
	static int GetBitrate(void);
	static void ClearTotalBytes(void);

	virtual void SetLevelFixer(int nLevelFixer)=0;
	virtual int GetLevelFixer(void)=0;

	virtual int GetDVCStatus(void)=0;

	virtual int HasVideoSignal(void)=0;
	virtual int DVCSendData(const char*pData,int nLen)=0;

	virtual int StartVQD(unsigned long nDetectFlags=VQDS_SIGNALLOST|VQDS_COLORCAST|VQDS_BLUR|VQDS_BRIGHT|VQDS_FREEZE|VQDS_NOISE|VQDS_JITTER)=0;
	virtual void StopVQD(void)=0;

	static void SetVideoAutoFormat(int nFlagAuto);
	static int GetVideoAutoFormat(void);

	virtual void SetRecording(int nFlagRecording)=0;

	static void SetSpeakerMute(int nMute);

	//设置录音是否混音
	static void SetAudioRecordAll(bool bRecordAll);

	//设置是否静音
	static void SetMicphoneMute(bool bMute);
	
	/* 获取编码类型：0:Unknown; 1:SoftWare; 2:Intel HardWare; 3:NV HardWare*/
	virtual int GetEncoderType(void)=0;

	/*获取视频显示类型 0：Unknow;1：DirectShow;2：D3D9;3：D3D11;4：D3D12*/
	virtual int GetVideoShowType(void)=0;

	/*获取视频显示帧率*/
	virtual int GetVideoShowFrameRate(void)=0;

	/*获取视频采集帧率*/
	virtual int GetVideoCaptureFrameRate(void)=0;//未实现	

	/*获取视频编码帧率*/
	virtual int GetVideoEncodeFrameRate(void)=0;//未实现

	/*获取视频发送帧率*/
	virtual int GetVideoSendFrameRate(void)=0;
};


class IMXEC_PlayChanCallback
{
public:
	IMXEC_PlayChanCallback(void){};
	virtual~IMXEC_PlayChanCallback(void){};
public:
	//音频数据回调函数
	virtual void OnIMXEC_PlayChanCallbackAudChanData(unsigned char*pData,int nLen,bool&bLoop)=0;
	virtual void OnIMXEC_PlayChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp)=0;
	//视频数据回调函数
	//nKeyFrame,0:非关键帧 1:关键帧
	virtual void OnIMXEC_PlayChanCallbackVidChanData(unsigned char*pData,int nLen,int nKeyFrame,int& nFlagDontDecode)=0;

	//无法解码的回调，nHardwareError不等于0时，表示解码超出范围，nHardwareError等于0时，表示恢复正常；
	//此函数为线程中回调出来的函数，操作窗口时请转为Windows消息
	virtual void OnIMXEC_PlayChanCallbackHardwareError(int nHardwareError){};
	virtual void OnIMXEC_PlayChanCallbackVQDResult(unsigned long nResult){};

	/*实施回调D3D9渲染视频图像后的DC，可对DC进行绘制，仅本地有用不影响远程或录制*/
	virtual void OnIMXEC_PlayChanCallbackDrawD3D9DC(void* hDC/*HDC*/){};
};

class IMXEC_API IMXEC_PlayChan
{
public:
	IMXEC_PlayChan(void){};
	virtual~IMXEC_PlayChan(void){};
public:
	//A7 add
	//virtual int Open(HWND hwndParent,unsigned long nAudChanID,unsigned long nVidChanID,const char*cszPeerNodeID,const char*cszPeerNATIP,unsigned short nPeerNATPort,const char*cszPeerLocalIP,unsigned short nPeerLocalPort,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,int nForceUseMCU=0)=0;
	virtual int Open(HWND hwndParent,unsigned long nAudChanID,unsigned long nVidChanID,const char*cszPeerNodeID,const char*cszPeerNATIP,unsigned short nPeerNATPort,const char*cszPeerLocalIP,unsigned short nPeerLocalPort,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,int nForceUseMCU=0,unsigned long nEnableMulticast=0)=0;

	/******************************************************************************
	* Open
	*描述：打开本地播放
	*输入：	hwndParent		-视频父窗口句柄
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(HWND hwndParent)=0;

	virtual void Close(void)=0;

	//取视频窗口
	virtual HWND GetVideoWnd(void)=0;
	//取视频宽度
	virtual int GetVideoWidth(void)=0;
	//取视频高度
	virtual int GetVideoHeight(void)=0;

	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 
	//保持当前图象到BMP文件
	virtual bool CaptureToBMPFile(const char*cszFile)=0;

	//设置视频属性
	virtual int SetVideoParam(int nBrightness=128/*亮度值0-255*/, int nContrast=64/*对比度0-127*/, int nSaturation=64/*饱和度0-127*/, int nHue=0/*色调0-255*/,int nGamma=100/*伽马1-400*/,int nSharpen=0/*锐化0-127*/)=0;

	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;

	/******************************************************************************
	* SetScreenWnd
	*描述：设置所在屏幕窗口位置
	*输入：	nScreenIndex	-屏幕号
			nWndIndex		-窗口号
			nFullScreen		-是否全屏显示【0：普通显示，非0：全屏显示】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;

	/******************************************************************************
	* SetVideoWndBk
	*描述：设置视频窗口没有码流时的背景
	*输入：	szBkImage	- 背景图片的全路径（只支持bmp图片）
	        nVideoWnBkR,nVideoWnBkG,nVideoWnBkB  背景颜色
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetVideoWndBk(const char* szBkImage = NULL, int nVideoWnBkR = -1, int nVideoWnBkG = -1, int nVideoWnBkB = -1)=0;

	virtual int SetVolume(int nVolume)=0;
	virtual int GetVolume()=0;
	virtual int GetLevel(int&nLevel)=0;
	virtual void SetMute(bool bMute)=0;
	virtual bool IsMute()=0;

	virtual int StartAudio(void)=0;
	virtual int EnableAudio(int nEnable/*0:不接收，1:接收*/)=0;
	virtual int SetAudioID(unsigned long nAudioID)=0;
	virtual int StopAudio(void)=0;
	virtual int StartVideo(void)=0;
	virtual int EnableVideo(int nEnable/*0:不接收，1:接收*/)=0;
	virtual int StopVideo(void)=0;
	virtual int SetAudioCast(bool bAudioCast)=0;
	virtual int SetVideoCast(bool bVideoCast)=0;

	/******************************************************************************
	* RequestKeyFrame
	*描述：请求关键帧
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int RequestKeyFrame(void)=0;

	/******************************************************************************
	* SetFrameRateControlMode
	*描述：设置帧率控制模式
	*输入：	nMode			-帧率控制模式
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetFrameRateControlMode(FRAME_RATE_CONTROL_MODE nMode)=0;

	/******************************************************************************
	* SetFrameTypeControlMode
	*描述：设置帧类型控制模式
	*输入：	nMode			-帧类型控制模式
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetFrameTypeControlMode(FRAME_TYPE_CONTROL_MODE nMode)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*描述：获取音频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
			nBitrate			-码流【bps】
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*描述：获取视频的包的统计数据
	*输入：	无
	*输出： ulTotalPackets		-总共发送了多少个包
			ulLostPackets		-总共丢弃了多少个包
			AvgPacketLossRate	-平均丢包率
			CurPacketLossRate	-当前丢包率
			nBitrate			-码流【bps】
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	/******************************************************************************
	* PlayAudioData
	*描述：播放音频数据
	*输入：	pData			-数据指针
			nLen			-数据长度
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int PlayAudioData(const void*pData,int nLen)=0;

	/******************************************************************************
	* PlayVideoData
	*描述：播放视频数据
	*输入：	pData			-数据指针
			nLen			-数据长度
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int PlayVideoData(const void*pData,int nLen)=0;

	/******************************************************************************
	* StartRecordToAVI
	*描述：开始辅流录像
	*输入：	cszPathName			-录像文件名称
			nStandardFormat		-是否录制成标准文件格式
			nCacheTimeMS        -视频等待音频的时间
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int StartRecordToAVI(const char*cszPathName,int nStandardFormat=1, int nCacheTimeMS = 10000)=0;
	
	/******************************************************************************
	* StopRecordToAVI
	*描述：停止辅流录像
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void StopRecordToAVI(void)=0;

	/******************************************************************************
	* SendCtrlData
	*描述：发送控制数据
	*输入：	pData			-控制数据
			nLen			-控制数据长度
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SendCtrlData(void*pData,int nLen)=0;

	/******************************************************************************
	* SetSynFlag
	*描述：设置视频音频同步标记
	*输入：	nSynFlag		-视频音频同步标记【0：视频音频不同步，非0：视频音频同步】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetSynFlag(int nSynFlag)=0;

	virtual void SetImage(VIDEC_Image*pImage)=0;


	static IMXEC_PlayChan*Create(IMXEC_PlayChanCallback&rCallback);

	static unsigned long GetTotalBytes(void);
	static int GetBitrate(void);
	static void ClearTotalBytes(void);
	static void SetForcibleReceiving(bool bForcible);
	static bool GetForcibleReceiving(void);

	virtual int StartMixingAudio(X_AUDIO_CODEC_ID nCodecID)=0;
	virtual void StopMixingAudio(void)=0;
	virtual int GetMixingAudioID(unsigned long&nAudioID)=0;

	virtual int StartVQD(unsigned long nDetectFlags=VQDS_SIGNALLOST|VQDS_COLORCAST|VQDS_BLUR|VQDS_BRIGHT|VQDS_FREEZE|VQDS_NOISE|VQDS_JITTER)=0;
	virtual void StopVQD(void)=0;

	virtual void SetRecording(int nFlagRecording)=0;

	//获取音频输出设备
	static int GetSpeakerDevNum();
	static int GetSpeakerDevName(int nIndex, char* szName, int nMaxCount);
	static int SetSpeakerDev(int nIndex);

	static int StartPlayLocalWAVFile (const char* filename, bool loop);
	static int StopPlayLocalWAVFile ();

public:
	//notice netec send ptz 
	virtual int SendCtrl(void*pData,int nLen) {return 0; };
	virtual int SendPTZ(void*pData,int nLen) {return 0; };

	/* 获取解码类型：0:Unknown; 1:SoftWare; 2:Intel HardWare; 3:NV HardWare*/
	virtual int GetDecoderType(void)=0;
	
	/*设置视频延时播放，注意：启用延时后，会出现音视频不同步问题
	 *nMilliSecond：毫秒为单位，取值范围（0，60000）*/
	virtual void SetVideoDelay(int nMilliSecond)=0;

	/*视频跳帧，用于快速播放解码图像，一旦调用此接口，内部将改用软解+DirectShow渲染，需要在创建Player对象后先调用一次，中途也可以修改参数。
	 *nInterval：跳帧间隔数，必须大于1，
	 *nSkip：每次跳帧数，必须大于1 
	 *返回-1为失败，请关闭Player对象重新创建尝试，返回0为成功*/
	virtual int SetVideoSkipFrame(int nInterval,int nSkip)=0;
	
	/*获取视频显示类型 0：Unknow;1：DirectShow;2：D3D9;3：D3D11;4：D3D12*/
	virtual int GetVideoShowType(void)=0;

	/*获取视频显示帧率*/
	virtual int GetVideoShowFrameRate(void)=0;

	/*获取视频解码帧率*/
	virtual int GetVideoDecodeFrameRate(void)=0;//未实现

	/*获取视频接收帧率*/
	virtual int GetVideoRecvFrameRate(void)=0;

	/*启用视频轮询机制，仅适用于轮询Player，需要在创建Player对象并Open后调用，中途调用无效（有针对轮询优化内存管理等）*/
	virtual int SetVideoPolledMode(void)=0;

#ifdef _TIANZHU_CACHE_
	/*设置远端视播放的缓冲帧数,缓冲的帧数范围（0 - 60）*/
	virtual int SetRemoteVideoCache(int nCacheFrameCount)=0;
#endif
};

class IMXEC_AudioMixerCapChanCallback
{
public:
	void OnIMXEC_AudioMixerCapChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp){};
};

class IMXEC_API IMXEC_AudioMixerCapChan
{
public:
	IMXEC_AudioMixerCapChan(void){};
	virtual~IMXEC_AudioMixerCapChan(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual unsigned long GetAudioID(void)=0;
	virtual void ExcludePlayChan(IMXEC_PlayChan*pPlayChan)=0;

	static IMXEC_AudioMixerCapChan*Create(IMXEC_AudioMixerCapChanCallback&rCallback);
};


class IMXEC_BackgroundMusicCallback
{
public:
	virtual void OnIMXEC_BackgroundMusicCallbackPositionChanged(unsigned long ulSeconds)=0;
	virtual void OnIMXEC_BackgroundMusicCallbackEnd(void)=0;
};

class IMXEC_API IMXEC_BackgroundMusic
{
public:
	IMXEC_BackgroundMusic(void){};
	virtual~IMXEC_BackgroundMusic(void){};
public:
	virtual int Open(const char*cszFileName,bool bLoop)=0;
	virtual void Close(void)=0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;
	virtual int Seek(unsigned long ulSeconds)=0;
	virtual int Pause(void)=0;
	virtual int Play(void)=0;
	virtual bool IsPlaying(void)=0;

	virtual int SetVolume(int nVolume)=0;
	virtual int SetMute(int nMute)=0;


	static IMXEC_BackgroundMusic*Create(IMXEC_BackgroundMusicCallback&rCallback);
};

#endif
