//IMXEC_H323.h
#ifndef __IMXEC_H323_H__
#define __IMXEC_H323_H__

#include <AVCONMP/IMXEC_Export.h>
#include <AVCONMP/IMXEC_VideoSetting.h>
#include <AVCONMP/IMXEC_AudioSetting.h>

//H323协议
class IMXEC_API IMXEC_H323
{
public:
	IMXEC_H323(void);
	virtual~IMXEC_H323(void);
public:
	//注册状态
	typedef enum
	{
		REG_IDLE=0,				//没有注册
		REG_OK,					//注册成功
		REG_ERR_ID,				//注册失败，帐号错误
		REG_ERR_PASSWORD,		//注册失败，密码错误
		REG_ERR_UNKOWN_HOST		//注册失败，无法连接服务器
	}REG_STATE;


public:
	/******************************************************************************
	* SetH323ID
	*描述：设置注册帐号
	*输入：	cszH323ID		-注册帐号
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetH323ID(const char*cszH323ID);

	/******************************************************************************
	* SetTelNumber
	*描述：设置电话号码
	*输入：	cszTelNumber		-电话号码
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetTelNumber(const char*cszTelNumber);

	/******************************************************************************
	* SetRegPassword
	*描述：设置注册密码
	*输入：	cszRegPassword	-注册帐号
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetRegPassword(const char*cszRegPassword);

	/******************************************************************************
	* SetUserName
	*描述：设置用户名称
	*输入：	cszUserName		-用户名称
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetUserName(const char*cszUserName);

	/******************************************************************************
	* SetRegHost
	*描述：设置用户名称
	*输入：	cszHost			-注册服务器
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetRegHost(const char*cszHost);

	/******************************************************************************
	* Register
	*描述：注册
	*输入：nType			-注册类型【0:自动查找GK服务器，非0:注册到指定的GK服务器】
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Register(int nType=1);

	/******************************************************************************
	* UnRegister
	*描述：注销
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int UnRegister(void);

	/******************************************************************************
	* GetRegState
	*描述：获取注册状态
	*输入：无
	*输出：	nRegState			-注册状态
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int GetRegState(REG_STATE&nRegState);

	/******************************************************************************
	* SetH323ListenPort
	*描述：设置侦听端口
	*输入：	nH323ListenPort			-侦听端口
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetH323ListenPort(unsigned short nH323ListenPort);

	/******************************************************************************
	* SetLocalIP
	*描述：设置注册帐号
	*输入：	cszH323ID		-注册帐号
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetLocalIP(const char*cszLocalIP);

	/******************************************************************************
	* SetRTPBasePort
	*描述：设置侦听端口
	*输入：	nRTPBasePort			-RTP开始端口
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetRTPBasePort(unsigned short nRTPBasePort);

	/******************************************************************************
	* SetSupportH239
	*描述：设置是否支持H239
	*输入：nFlag		-是否支持H239
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetSupportH239(int nSupportH239);

	/******************************************************************************
	* SetAudioDevParam
	*描述：设置主流视频设备参数
	*输入： nAudioCodecID		-音频编码
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetAudioDevParam(X_AUDIO_CODEC_ID nAudioCodecID);

	/******************************************************************************
	* SetMainVideoDevParam
	*描述：设置主流视频设备参数
	*输入： nDevID				-设备标识
			nFrameRate			-帧率
			nBitrate			-码流
			nVideoCodecType		-视频编码
			nVideoFormatType	-视频格式
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetMainVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);

	/******************************************************************************
	* SetSecondVideoDevParam
	*描述：设置辅流视频设备参数
	*输入： nDevID				-设备标识
			nFrameRate			-帧率
			nBitrate			-码流
			nVideoCodecType		-视频编码
			nVideoFormatType	-视频格式
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetSecondVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);

	/******************************************************************************
	* Start
	*描述：启动H323服务
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Start(void);

	/******************************************************************************
	* Stop
	*描述：停止H323服务
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Stop(void);




	
	//use H235 Media
	
	/******************************************************************************
	* H235SecuritySettingInitialize
	*描述：	H235安全选项初始化
	*输入：	
	*****************************************************************************/
	static void H235SecuritySettingInitialize();

	/******************************************************************************
	* SetH235SecurityAuthOption
	*描述：	设置使用H235验证选项
	*输入：	option 0为不使用，1为使用
	*****************************************************************************/
	static void SetH235SecurityAuthOption(int option);

	/******************************************************************************
	* SetH235MediaSecurityOption
	*描述：	设置使用媒体流加密选项
	*输入：	option 0为不使用，1为可选使用，2为强制使用H235媒体流加密
	*****************************************************************************/
	static void SetH235MediaSecurityOption(int option);


	/******************************************************************************
	* SetH235SecurityAuth
	*描述：	设置H235验证信息 本端用senderId来检查对方发来的generalID 本端用generalID来检查对方发来的senderId
	*输入：	senderId 发送标识即本端标识 长度小于256字节
			generalId接收标识即对端标识 长度小于256字节
			password 验证密码 长度小于64字节
	*****************************************************************************/
	static void SetH235SecurityAuth(char * senderId,char * generalId,char * password);


	/******************************************************************************
	* SetH235SecurityAnnexIEnable
	*描述：	设置安全验证模式可用状态，H235 AnnexD I规程消息完整性及密码认证
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityAnnexIEnable(bool enable);


	/******************************************************************************
	* SetH235SecurityAnnexIAEnable
	*描述：	设置安全验证模式可用状态，H235 AnnexD IA 规程仅密码认证
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityAnnexIAEnable(bool enable);


	/******************************************************************************
	* SetH235SecurityAnnexIIEnable
	*描述：	设置安全验证模式可用状态，H235 AnnexE II 规程采用公钥/私钥对的数字签名
			不用于网守注册
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityAnnexIIEnable(bool enable);


	/******************************************************************************
	* SetH235SecurityAnnexIIIEnable
	*描述：	设置安全验证模式可用状态，H235 AnnexE III 规程端到端认证
			不用于网守注册
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityAnnexIIIEnable(bool enable);


	/******************************************************************************
	* SetH235SecurityMediaDH512Enable
	*描述：	设置安全验证模式可用状态，用于媒体流加密，使用512-bit Diffie-Hellman group生成7字节共享密钥
			仅用于DES加密等使用7字节以内的密码加密的算法
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityMediaDH512Enable(bool enable);


	/******************************************************************************
	* SetH235SecurityMediaDH1024Enable
	*描述：	设置安全验证模式可用状态，用于媒体流加密，使用1024-bit Diffie-Hellman group生成21字节共享密钥
			用于DES 3DES加密等
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityMediaDH1024Enable(bool enable);


	/******************************************************************************
	* SetH235SecurityMediaDH1536Enable
	*描述：	设置安全验证模式可用状态，用于媒体流加密，使用1536-bit Diffie-Hellman group生成21字节共享密钥
			用于DES 3DES加密等
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityMediaDH1536Enable(bool enable);


	/******************************************************************************
	* SetH235SecurityUserPrimeEnable
	*描述：	设置可用状态，预定义素数是否用于媒体加密共享密钥协商
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityUserPrimeEnable(bool enable);


	/******************************************************************************
	* SetH235SecurityCheckIncomingMsgEnable
	*描述：	设置对接收呼叫等消息进行验证检查状态
	*输入：	enable 可用状态 true 设为可用 false不可用
	*****************************************************************************/
	static void SetH235SecurityCheckIncomingMsgEnable(bool enable);


	/******************************************************************************
	* SetH235MediaEncryptionAlogrithmFirst
	*描述：	设置媒体流优先加密算法
	*输入：	alogrimId 算法ID 2为DES CBC模式，5为3DES CBC模式
	*****************************************************************************/
	static void SetH235MediaEncryptionAlogrithmFirst(int alogrimId);

	/******************************************************************************
	* SetH235MediaSecurityEncryptionPWD
	*描述：	设置媒体流加密密码
	*输入：	type 0 为不使用指定密码(自动协商) 1 为使用指定密码
			encrypPwd 使用指定密码时设置的加密密码  长度小于64字节
	*****************************************************************************/
	static void SetH235MediaSecurityEncryptionPWD(int type=0,char * encrypPwd=NULL);


};




#endif
