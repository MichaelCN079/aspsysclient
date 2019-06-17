#ifndef _JVLIVE_CLIENT_H_
#define _JVLIVE_CLIENT_H_

typedef enum{
	JVLIVE_ERR_OK,
	JVLIVE_ERR_OVER,//�������
	JVLIVE_ERR_UNKNOWN,
	JVLIVE_ERR_TIMEOUT,
	JVLIVE_ERR_BAD_REQUEST,
	JVLIVE_ERR_WRONG_PASSWD,
	JVLIVE_ERR_NOT_FOUND,

}jvlive_err_e;
typedef struct
{
	char m_streamID[32];
	int m_LinkID;
	char acManufacture[32];

}m_streamID_t;

#ifdef __cplusplus
extern "C" {
#endif

typedef void *CRTSPHandle_t;

/**
 * ���Ž������������ض˽����˲���
 */
typedef void (afterPlayingFunc_t)(void* param, jvlive_err_e errcode, const char *errStr, int extradata);

/**
 * ���ݻص�
 *
 *@param param �û�����
 *@param channelHandle ͨ������������ڻ�ȡͨ����ص���Ϣ����Ҫ���ǵ����п����ж�·��Ƶ������Ƶ���Լ����ǵ�����
 *@param codecName ���뷽ʽ��H264, PCMU, PCMA��
 *@param buffer ֡λ��
 *@param frameSize ֡����
 *@param presentationTime ��ǰ֡ʱ��
 *@param durationInMicroseconds ��δʹ��
 */
typedef void (afterGettingFrame_t)(void* param,
								void *channelHandle,
								unsigned char *buffer,
								unsigned frameSize,
								struct timeval presentationTime,
								unsigned durationInMicroseconds);

/**
 * ����һ·����
 *
 *@param streamID �����ƣ�Ψһ��ʶ�򿪵���
 *@param url Ҫ�򿪵��������ĵ�ַ�����ƣ�rtsp://192.168.11.192:8554/live0.264
 *@param maxVideoStreamSize ��Ƶ���֡��֡��С
 *@param user �û���������ΪNULL
 *@param passwd ���룬����ΪNULL
 *@param afterPlaying ���ؽ�������������ԭ����ֹͣʱ�Ļص�
 *@param afterGetting �յ����ݺ�Ļص�����
 *@param param �û����ݣ�����afterPlaying��afterGettingʱ����
 */
CRTSPHandle_t jvlive_client_create(
		const char *url,
		int maxVideoStreamSize,
		const char *user,
		const char *passwd,
		afterPlayingFunc_t *afterPlaying,
		afterGettingFrame_t *afterGetting,
		void *param);

/**
 *@brief �̵߳�����
 * ע�⣺�����������أ���������ֱ������jvlive_client_stop
 *   �����;���أ���һ���ǳ�����
 *@param handle value of #jvlive_client_create return.
 *
 */
int jvlive_client_run(CRTSPHandle_t handle);

/**
 * �ر�֮ǰ�򿪵�����
 */
int jvlive_client_destroy(CRTSPHandle_t handle);

typedef struct {
	char mediaName[32];	//video  audio
	char codecName[32]; //H264 PCMA PCMU ...
	char protocolName[32]; //RTP
} jvliveChannelInfo_t;

/**
 * ��ȡRTSP���ŵ�ĳ�� ��������Ϣ
 *
 *@param channelHandle #afterGettingFrame_t �Ĳ���֮һ
 *@param info ��ȡ������Ϣ
 */
int jvlive_client_get_channel_info(void *channelHandle, jvliveChannelInfo_t *info);

int jvlive_client_getparam_session(CRTSPHandle_t handle, char const* parameterName);

int jvlive_client_setparam_session(CRTSPHandle_t handle, char const* parameterValue) ;

char *jvlive_client_getparam_string();

int jvlive_client_setscale(CRTSPHandle_t handle, float scale, double seekNPT);

int jvlive_client_seek(CRTSPHandle_t handle, double seekNPT);

int jvlive_client_pause(CRTSPHandle_t handle);

int jvlive_client_resume(CRTSPHandle_t handle);


#define GetParameter_session(handle,parameterName,user,passwd) 	jvlive_client_getparam_session(handle,parameterName)

#define SetParameter_session(handle,parameterValue,user,passwd) jvlive_client_setparam_session(handle, parameterValue)

#define GetParameter_String jvlive_client_getparam_string

#define SetPlayScale(handle,scale,seekNPT,user,passwd) jvlive_client_setscale(handle, scale, seekNPT)

#define SetSeekNPT(handle,seekNPT,user,passwd) jvlive_client_seek(handle, seekNPT)

#define PauseStream(handle,user,passwd)	  jvlive_client_pause(handle)

#define ResumeStream( handle,user,passwd) jvlive_client_resume(handle)


#ifdef __cplusplus
}
#endif



#endif
