//NETEC_File.h
#ifndef __NETEC_FILE_H__
#define __NETEC_FILE_H__

#include <NETEC/NETEC_Export.h>

//文件发送类
class NETEC_API NETEC_FileNodeTX
{
public:
	NETEC_FileNodeTX(void){};
	virtual~NETEC_FileNodeTX(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开文件发送
	*输入：	cszPathName		-要发送的文件的全路径
			cszPeerNodeID	-接收方的节点标识
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int32_t Open(const char*cszPathName,const char*cszPeerNodeID)=0;
	
	/******************************************************************************
	* Open
	*描述：关闭文件发送
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;
	
	/******************************************************************************
	* GetFileID
	*描述：获取文件标识
	*输入：无
	*输出：无
	*返回值：文件标识
	*****************************************************************************/
	virtual uint32_t GetFileID(void)=0;
	
	/******************************************************************************
	* GetFileLength
	*描述：获取文件长度
	*输入：无
	*输出：无
	*返回值：文件长度
	*****************************************************************************/
	virtual uint32_t GetFileLength(void)=0;
	
	/******************************************************************************
	* GetFileTransferredBytes
	*描述：获取文件已经传输的字节数
	*输入：无
	*输出：无
	*返回值：文件已经传输的字节数
	*****************************************************************************/
	virtual uint32_t GetFileTransferredBytes(void)=0;
	
	/******************************************************************************
	* GetBitrate
	*描述：获取传输码流
	*输入：无
	*输出：无
	*返回值：文件传输码流
	*****************************************************************************/
	virtual int32_t GetBitrate(void)=0;
	
	/******************************************************************************
	* GetPercent
	*描述：获取传输进度【0-100】
	*输入：无
	*输出：无
	*返回值：文件传输进度
	*****************************************************************************/
	virtual int32_t GetPercent(void)=0;
	
	/******************************************************************************
	* GetNetworkState
	*描述：获取网络状态
	*输入：无
	*输出：无
	*返回值：网络状态,0:正在连接;1:连接成功;2:连接断开
	*****************************************************************************/
	virtual int32_t GetNetworkState(void)=0;
	
	/******************************************************************************
	* Create
	*描述：创建文件发送实例
	*输入：无
	*输出：无
	*返回值：文件发送实例
	*****************************************************************************/
	static NETEC_FileNodeTX*Create(void);
};

//文件接收类
class NETEC_API NETEC_FileNodeRX
{
public:
	NETEC_FileNodeRX(void){};
	virtual~NETEC_FileNodeRX(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开文件接收
	*输入：	nFileID			-文件标识【来自文件发送实例】
			nFileLength		-文件长度【来自文件发送实例】
			cszPathName		-要保存的文件的全路径
			cszPeerNodeID	-发送方的节点标识
			cszPeerMCUID	-对方MCU的标识
			cszPeerMCUIP	-对方MCU的IP地址
			nPeerMCUPort	-对方MCU的端口
			cszPeerMCUType	-对方MCU的地址类型
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int32_t Open(uint32_t nFileID,uint32_t nFileLength,const char*cszPathName,const char*cszPeerNodeID,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,const char*cszPeerMCUType)=0;
	
	/******************************************************************************
	* Open
	*描述：关闭文件接收
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;
	
	/******************************************************************************
	* GetFileID
	*描述：获取文件标识
	*输入：无
	*输出：无
	*返回值：文件标识
	*****************************************************************************/
	virtual uint32_t GetFileID(void)=0;
	
	/******************************************************************************
	* GetFileLength
	*描述：获取文件长度
	*输入：无
	*输出：无
	*返回值：文件长度
	*****************************************************************************/
	virtual uint32_t GetFileLength(void)=0;
	
	/******************************************************************************
	* GetFileTransferredBytes
	*描述：获取文件已经传输的字节数
	*输入：无
	*输出：无
	*返回值：文件已经传输的字节数
	*****************************************************************************/
	virtual uint32_t GetFileTransferredBytes(void)=0;
	
	/******************************************************************************
	* GetBitrate
	*描述：获取传输码流
	*输入：无
	*输出：无
	*返回值：文件传输码流
	*****************************************************************************/
	virtual int32_t GetBitrate(void)=0;
	
	/******************************************************************************
	* GetPercent
	*描述：获取传输进度【0-100】
	*输入：无
	*输出：无
	*返回值：文件传输进度
	*****************************************************************************/
	virtual int32_t GetPercent(void)=0;
	
	/******************************************************************************
	* GetNetworkState
	*描述：获取网络状态
	*输入：无
	*输出：无
	*返回值：网络状态,0:正在连接;1:连接成功;2:连接断开
	*****************************************************************************/
	virtual int32_t GetNetworkState(void)=0;
	
	/******************************************************************************
	* Create
	*描述：创建文件接收实例
	*输入：无
	*输出：无
	*返回值：文件接收实例
	*****************************************************************************/
	static NETEC_FileNodeRX*Create(void);
};


//文件发送类
class NETEC_FileStreamNodeTXCallback
{
public:
	virtual int32_t OnNETEC_FileStreamNodeTXCallbackSeekTo(uint32_t nPos)=0;
	virtual int32_t OnNETEC_FileStreamNodeTXCallbackReadNextFrame(void)=0;
};

class NETEC_API NETEC_FileStreamNodeTX
{
public:
	NETEC_FileStreamNodeTX(void){};
	virtual~NETEC_FileStreamNodeTX(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开文件发送
	*输入：	cszPeerNodeID	-接收方的节点标识
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int32_t Open(const char*cszPeerNodeID)=0;
	
	/******************************************************************************
	* Open
	*描述：关闭文件发送
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;
	
	/******************************************************************************
	* GetFileID
	*描述：获取文件标识
	*输入：无
	*输出：无
	*返回值：文件标识
	*****************************************************************************/
	virtual uint32_t GetFileID(void)=0;
	
	/******************************************************************************
	* GetNetworkState
	*描述：获取网络状态
	*输入：无
	*输出：无
	*返回值：网络状态,0:正在连接;1:连接成功;2:连接断开
	*****************************************************************************/
	virtual int32_t GetNetworkState(void)=0;

	virtual int32_t SendFrameData(const char*pFrameData,int32_t nFrameLen)=0;
	
	/******************************************************************************
	* Create
	*描述：创建文件发送实例
	*输入：无
	*输出：无
	*返回值：文件发送实例
	*****************************************************************************/
	static NETEC_FileStreamNodeTX*Create(NETEC_FileStreamNodeTXCallback&rCallback);
};

//文件接收类
class NETEC_FileStreamNodeRXCallback
{
public:
	virtual void OnNETEC_FileStreamNodeRXCallbackWriteFrame(const char*pFrameData,int32_t nFrameLen)=0;
};

class NETEC_API NETEC_FileStreamNodeRX
{
public:
	NETEC_FileStreamNodeRX(void){};
	virtual~NETEC_FileStreamNodeRX(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开文件接收
	*输入：	nFileID			-文件标识【来自文件发送实例】
			cszPeerNodeID	-发送方的节点标识
			cszPeerMCUID	-对方MCU的标识
			cszPeerMCUIP	-对方MCU的IP地址
			nPeerMCUPort	-对方MCU的端口
			cszPeerMCUType	-对方MCU的地址类型
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int32_t Open(uint32_t nFileID,const char*cszPeerNodeID,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,const char*cszPeerMCUType)=0;
	
	/******************************************************************************
	* Open
	*描述：关闭文件接收
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;
	
	/******************************************************************************
	* GetFileID
	*描述：获取文件标识
	*输入：无
	*输出：无
	*返回值：文件标识
	*****************************************************************************/
	virtual uint32_t GetFileID(void)=0;
	
	/******************************************************************************
	* GetBitrate
	*描述：获取传输码流
	*输入：无
	*输出：无
	*返回值：文件传输码流
	*****************************************************************************/
	virtual int32_t GetBitrate(void)=0;
	
	/******************************************************************************
	* GetNetworkState
	*描述：获取网络状态
	*输入：无
	*输出：无
	*返回值：网络状态,0:正在连接;1:连接成功;2:连接断开
	*****************************************************************************/
	virtual int32_t GetNetworkState(void)=0;
	
	virtual int32_t SeekTo(uint32_t nPos)=0;
	virtual int32_t Pause(int32_t nPause)=0;

	/******************************************************************************
	* Create
	*描述：创建文件接收实例
	*输入：无
	*输出：无
	*返回值：文件接收实例
	*****************************************************************************/
	static NETEC_FileStreamNodeRX*Create(NETEC_FileStreamNodeRXCallback&rCallback);
};

#endif
