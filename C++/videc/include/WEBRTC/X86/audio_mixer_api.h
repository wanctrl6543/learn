#ifndef _AUDIO_MIXER_API_H
#define _AUDIO_MIXER_API_H

#ifdef _WIN32
#ifdef AUDIO_MIXER_EXPORT
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif // VOICE_ENGINE_EXPORT
#else //_WIN32
#define API __attribute__ ((visibility("default")))
#endif

#include "audio_mixer_api_types.h"

class API AudioMixerAPI {
public:

	/* 创建音频混音器
	 * @return: AudioMixer Instance
	 */
	static AudioMixerAPI* CreateMixer ();
	
	/* 销毁音频混音器
	 * @param mixer: AudioMixer Instance
	 */
	static void Destroy (AudioMixerAPI* mixer);
	
	/* 通过|codec_id|获取codec详细信息
	 * @param codec_id: 音频格式
	 * @param info: 格式详细信息
	 */
	static void GetCodecInfo (AUDIO_CODEC_ID codec_id, CodecInfo& info);

	/* 初始化音频混音器
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int Init () = 0;

	/* 创建一路输出通道
	 * @param codec_id: 混音后编码格式
	 * @param callback: 混音编码后回调函数
	 * @return out_channel: | out_channel>=0 输出通道号 | out_channel<0 创建失败 |
	 */
	virtual int CreateOutputChannel (AUDIO_CODEC_ID codec_id, AudioMixer_Callback* callback) = 0;
	
	/* 移除一路输出通道
	 * @param out_channel： 输出通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int RemoveOutputChannel (int out_channel) = 0;
	
	/* 混音一路输出
	 * @param out_channel: 输出通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int StartOutputMixing (int out_channel) = 0;
	
	/* 停止混音一路输出
	 * @param out_channel: 输出通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int StopOutputMixing (int out_channel) = 0;
	
	/* 创建一路输入通道
	 * @return in_channel: | in_channel>=0 输入通道号 | in_channel<0 失败 |
	 */
	virtual int CreateInputChannel () = 0;

	/* 移除一路输入通道
	 * @param in_channel: 输入通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int RemoveInputChannel (int in_channel) = 0;

	/* 将一路输入加入混音器中
	 * @param in_channel: 输入通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int StartInputMixing (int in_channel) = 0;

	/* 将一路输入从混音器中移除
	 * @param in_channel: 输入通道号
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int StopInputMixing (int in_channel) = 0;

	/* 向输入通道中添加rtp头数据
	 * @param in_channel: 输入通道号
	 * @param rtp_data: rtp音频数据
	 * @param len: rtp_data长度
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int AddRtpData (int in_channel, const char* rtp_data, int len) = 0;

	/* 向输入通道中添加Audec头数据
	* @param in_channel: 输入通道号
	* @param rtp_data: rtp音频数据
	* @param len: rtp_data长度
	* @return ret: | ret=0 成功 | ret=-1 失败 |
	*/
	virtual int AddAudecData (int in_channel, const char* audec_data, int len) = 0;

	/* 设置输入通道线性增益值(DB)
	 * @param in_channel: 输入通道号
	 * @param gain_db: 增益值(-96db ~ 96db) | gain_db>0 增大增益 | gain_db<0 减小增益 |
	 * @return ret: | ret=0 成功 | ret=-1 失败 |
	 */
	virtual int SetInputChannelGainDB (int in_channel, float gain_db) = 0;

protected:
	virtual ~AudioMixerAPI () {};

};

#endif // !_AUDIO_MIXER_API_H