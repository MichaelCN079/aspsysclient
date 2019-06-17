#ifndef _JVLIVE_H_
#define _JVLIVE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	JVLIVE_CMD_TYPE_CONNECTED,
	JVLIVE_CMD_TYPE_DISCONNECTED,
}JVLiveCmdType_e;

typedef struct{
	JVLiveCmdType_e type;
	struct{
		char addr[16];
		unsigned int sessionID;
	}connect;
}jvlive_info_t;

typedef struct{
	void (*callback)(jvlive_info_t *info);
	int max_frame_len;
}jvliveParam_t;

void jvlive_rtsp_init(jvliveParam_t *param);

//׼��RTSP����
//param nameFmt ����live%d.264
//cnt �ṩ����Ƶ��·����
void jvlive_rtsp_start(char *nameFmt, unsigned short port, int *bufferSizeList, int *frameList, int cnt);

//audioType: "g726-40"/"PCMU"/"PCMA" ...
//PCMU��PCMA����Ӧ��G711-U,-A. Ŀǰ����8K,16BIT����£����Կ���
void jvlive_rtsp_start_ex(char *nameFmt, unsigned short port, int *bufferSizeList, int *frameList, int cnt, char *audioType, int timeStampFrequency);

typedef struct{
	char audioType[32];
	int timeStampFrequency;
}JVLiveAudioInfo_t;

//�޸���Ƶ����
int jvlive_rtsp_set_audio_info(int channelid, JVLiveAudioInfo_t *audioInfo);

//��ȡ��Ƶ����
int jvlive_rtsp_get_audio_info(int channelid, JVLiveAudioInfo_t *audioInfo);

//���õ�ǰ֡��
int jvlive_rtsp_set_framerate(int index, int framerate);

//д������
int jvlive_rtsp_write(int index, char *data, int len);

//д����Ƶ����
int jvlive_rtsp_write_audio(int index, char *data, int len);


//����û���������
//�������jvlive_rtsp_user_add_finished ������Ч
void jvlive_rtsp_user_add_start(char *user, char *passwd);

//�������û�
void jvlive_rtsp_user_add_finished(void);

#ifdef __cplusplus
}
#endif

#endif
