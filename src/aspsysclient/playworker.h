/******************************************************************************

  Copyright (c) 2012-2015 Jovision Technology Co., Ltd. All rights reserved.

  File Name     : Playbackdialog.h
  Version       :
  Author        : tgh
  Created       : 2015-3-31
  Description   : 回放界面
  History       :
  2.Date        : 2015-6-17
    Author      : tgh
    Modification: fix header file
  1.Date        : 2015-3-31
    Author      : tgh
    Modification: Created file
******************************************************************************/

#ifndef PLAYBACK_DIALOG_H
#define PLAYBACK_DIALOG_H

#include <QThread>
#include "common.h"
#include "moniter.h"
#include "JVSDKP.h"
#include "jvlive-client.h"
#include "stdint.h"

#define NOCACHE 0
#include "bitstream.h"
#include <stdio.h>
#include <stdarg.h>
#if 0
#define LOGDBG printf
#else
//#define LOGDBG(fmt...) do{}while(0)
#endif
#define NAL_SPS     0x07 /* Sequence Parameter Set */
#define NAL_AUD     0x09 /* Access Unit Delimiter */
#define NAL_END_SEQ 0x0a /* End of Sequence */


#if defined(__i386__) || defined(__x86_64__)
#  define IS_NAL_SPS(buf)     (*(const uint32_t *)(buf) == 0x07010000U)
#  define IS_NAL_AUD(buf)     (*(const uint32_t *)(buf) == 0x09010000U)
#  define IS_NAL_END_SEQ(buf) (*(const uint32_t *)(buf) == 0x0a010000U)
#else
#  define IS_NAL_SPS(buf)     ((buf)[0] == 0 && (buf)[1] == 0 && (buf)[2] == 1 && (buf)[3] == NAL_SPS)
#  define IS_NAL_AUD(buf)     ((buf)[0] == 0 && (buf)[1] == 0 && (buf)[2] == 1 && (buf)[3] == NAL_AUD)
#  define IS_NAL_END_SEQ(buf) ((buf)[0] == 0 && (buf)[1] == 0 && (buf)[2] == 1 && (buf)[3] == NAL_END_SEQ)
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct tagJVS_FILE_HEADER
{
	int	nFlag;				//中维录像文件标识
	int	nFrameWidth;		//图像宽度
	int	nFrameHeight;		//图像高度
	int	nTotalFrames;		//总帧数
	int	nVideoFormat;		//视频制式:0,PAL 1,NTSC
	uint8_t	nFrameRates;		//帧率
	uint8_t  nNoUse1;
	uint8_t  nNoUse2;
	uint8_t  nNoUse3;
	uint32_t	u32IIndexAddr;		//关键帧索引地址
	uint32_t	u32Reserved2;
}JVS_FILE_HEADER,*PJVS_FILE_HEADER;
typedef struct _JVS_FILE_HEADER_EX
{
	//老文件头，为兼容以前版本分控，保证其能正常预览
	uint8_t			ucOldHeader[32];//JVS_FILE_HEADER	oldHeader; //此处定义不可直接定义为JVS_FILE_HEADER类型，否则会有结构体成员对齐问题

	//结构体信息
	uint8_t			ucHeader[3];		//结构体识别码，设置为‘J','F','H'
	uint8_t			ucVersion;			//结构体版本号，当前版本为1

	//设备相关
	uint16_t		wDeviceType;		//设备类型

	//视频部分
	uint16_t		wVideoCodecID;		//视频编码类型
	uint16_t		wVideoDataType;		//数据类型
	uint16_t		wVideoFormat;		//视频模式
	uint16_t		wVideoWidth;		//视频宽
	uint16_t		wVideoHeight;		//视频高
	uint16_t		wFrameRateNum;		//帧率分子
	uint16_t		wFrameRateDen;		//帧率分母

	//音频部分
	uint16_t		wAudioCodecID;		//音频编码格式
	uint16_t		wAudioSampleRate;	//音频采样率
	uint16_t		wAudioChannels;		//音频声道数
	uint16_t		wAudioBits;			//音频采样位数

	//录像相关
	uint32_t		dwRecFileTotalFrames;	//录像总帧数
	uint16_t		wRecFileType;		//录像类型

	uint8_t 		   ucGrpcVersion; //GRPC版本号，非0表示支持GRPC
	uint8_t 		   ucReserved1[1]; //对齐用

	//保留位
	uint8_t 		   ucReserved[28];		  //请全部置0

} JVS_FILE_HEADER_EX, *PJVS_FILE_HEADER_EX;

typedef enum{
	PLAY_LINK_ID_1,
	PLAY_LINK_ID_2,
	PLAY_LINK_ID_3,
	PLAY_LINK_ID_4,
	PLAY_LINK_ID_1_,
	PLAY_LINK_ID_2_,
	PLAY_LINK_ID_3_,
	PLAY_LINK_ID_4_,
	PLAYBACK_LINK_ID,
	PLAY_LINK_ID_MAX,
}PLAY_LINK_ID;
typedef enum{
    NVC_LIVE_ERR_OK,
    NVC_LIVE_ERR_OVER,//播放完成
    NVC_LIVE_ERR_UNKNOWN,
    NVC_LIVE_ERR_TIMEOUT,
    NVC_LIVE_ERR_BAD_REQUEST,
    NVC_LIVE_ERR_WRONG_PASSWD,
    NVC_LIVE_ERR_NOT_FOUND,

}NvcLiveErr_e;

typedef enum
{
	CHN_STATE_NO_VIDEO,
	CHN_STATE_CONNECTING,
	CHN_STATE_RECONNECTING,
	CHN_STATE_LOSE_VIDEO,
	CHN_STATE_CONNECTED, 
}CHN_STATE;

class PlayWorker;
extern FILE *xxxx;
extern PlayWorker* CurrPlayWork[PLAY_LINK_ID_MAX];
void rtsp_stream_getted_func(void* param, void *channelHandle, unsigned char* buffer,unsigned frameSize, struct timeval presentationTime,unsigned durationInMicroseconds);
void rtsp_stream_after_playing_func(void* param, NvcLiveErr_e errCode, const char *errMsg, int extradata);
class PlayWorker : public QThread
{
    Q_OBJECT
public:
	typedef struct mpeg_rational_s {
		int num;
		int den;
	} mpeg_rational_t;
	typedef struct video_size_s {
		uint16_t        width;
		uint16_t        height;
		mpeg_rational_t pixel_aspect;
	} video_size_t;
	typedef struct {
	  uint16_t        width;
	  uint16_t        height;
	  mpeg_rational_t pixel_aspect;
	} h264_sps_data_t;

	PlayWorker(int id, QObject *parent = 0)
            :QThread(parent),m_linkid(id)
    {

		m_hwnd = 0;
		bConnected = false;
		bEverConncected = false;
		m_isFirst = true;
		timeout = 0;
		timer.setInterval(1000);
		connect(this, SIGNAL(signalTimerstart()), this, SLOT(slotTimerstart()));
		connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimerout()));
		m_Handle = NULL;
		m_playerId = -1;
		memset(&streamID, 0, sizeof(m_streamID_t));
		out_buffer=NULL;
		CurrPlayWork[id] = this;
		qRegisterMetaType<QPixmap>("QPixmap");
		qRegisterMetaType<QPixmap>("NvcLiveErr_e");

    }

    ~PlayWorker()
    {
		delete out_buffer;
		out_buffer = NULL;
	}

	/*
	* 开始工作之前必须调用 否则不会解码显示
	*/
	void readyToPlay(int hwnd,QString url)
	{
		if (m_isFirst)
		{
			emit signalChnStateChanged(m_linkid, CHN_STATE_CONNECTING);
			m_isFirst = false;
		}
		if(m_hwnd==0)
			m_hwnd = hwnd;

		isInited = 0;
		timeout = 0;
		bConnected = false;
		curr_playurl = url;

		char *urlstr;
		int tmp1, tmp2;
		QByteArray ba = curr_playurl.toLatin1();
		urlstr = ba.data();
		//根据NVR的IP地址规则获取车厢号
		sscanf(urlstr, "rtsp://%d.%d.%d.*", &tmp1, &tmp2, &curr_coach);
		curr_coach -= 100;
		m_playerId = JVSP_CreatePlayer();
		qDebug() << "PlayWork:JVSP_CreatePlayer, player id=" << m_playerId;
	}
	void clearTimeout(){
		emit signalChnPlayState(m_linkid, true);
		//bConnected = true;
		bEverConncected = true;
		timeout = 0;
	}
public slots:
	void slotTimerstart(){
		if(!timer.isActive())
			timer.start();
	};
	void slotTimerout();

protected:
    void run()
    {
        char rtsp_url[128];
        memset(rtsp_url,0,sizeof(char)*128);
		qDebug()<<curr_playurl;
		QByteArray ba = curr_playurl.toLatin1();
		sprintf(rtsp_url, ba.data());
#if 1		
		m_Handle = jvlive_client_create((const char *)rtsp_url, 
											512*1024, 
											"abc",
											"123",
											(afterPlayingFunc_t *)rtsp_stream_after_playing_func, 
											(afterGettingFrame_t *)rtsp_stream_getted_func, 
											(void *)m_linkid);
		if (!m_Handle)
		{
			printf("Failed create rtsp client\n");
			return ;
		}
		printf("%s, %d\n", __FILE__, __LINE__);
		jvlive_client_run(m_Handle);
		printf("%s, %d\n", __FILE__, __LINE__);
#else
		memset(&streamID, 0, sizeof(m_streamID_t));
        streamID.m_LinkID = m_linkid;
        sprintf(streamID.m_streamID, "stream:%x", m_linkid);
        sprintf(streamID.acManufacture, "%s", "CRH Video Recoder");
        jvlive_client_run(
                                        &streamID,
                                        rtsp_url,
                                        1024*1024*2,
										m_nvr_info_s.username,
										m_nvr_info_s.password,
                                        (afterPlayingFunc_t *)rtsp_stream_after_playing_func,
                                        (afterGettingFrame_t *)rtsp_stream_getted_func,
                                         (void*)m_linkid);
#endif
		qDebug()<<"PlayWorker Over\n";
        //emit playReady();
    }

signals:
	void signalReadyPlay(int duration);
	void signalFinishPaly(NvcLiveErr_e errCode);
    void playGetReady(const /**/QPixmap& pix ,int);
	void signalPlayProgress(double ntp);
	void signalTimerstart();
	void signalChnPlayState(int chn, bool state);
	void signalPlayTimeOut();
	void signalPrepareConnect(int coach);

	void signalChnStateChanged(int chn, int state);
private:
public:
	int h264_parse_sps(const uint8_t *buf, int len, h264_sps_data_t *sps)
	{
	  br_state br = BR_INIT(buf, len);
	  int profile_idc, pic_order_cnt_type;
	  int frame_mbs_only;
	  int i, j;

	  profile_idc = br_get_u8(&br);
	  //LOGDBG("H.264 SPS: profile_idc %d\n", profile_idc);
	  /* constraint_set0_flag = br_get_bit(br);    */
	  /* constraint_set1_flag = br_get_bit(br);    */
	  /* constraint_set2_flag = br_get_bit(br);    */
	  /* constraint_set3_flag = br_get_bit(br);    */
	  /* reserved             = br_get_bits(br,4); */
	  /* level_idc            = br_get_u8(br);     */
	  br_skip_bits(&br, 16);
	  br_skip_ue_golomb(&br);   /* seq_parameter_set_id */
	  if (profile_idc >= 100) {
		if (br_get_ue_golomb(&br) == 3) /* chroma_format_idc      */
		  br_skip_bit(&br);     /* residual_colour_transform_flag */
		br_skip_ue_golomb(&br); /* bit_depth_luma - 8             */
		br_skip_ue_golomb(&br); /* bit_depth_chroma - 8           */
		br_skip_bit(&br);       /* transform_bypass               */
		if (br_get_bit(&br))    /* seq_scaling_matrix_present     */
		  for (i = 0; i < 8; i++)
		if (br_get_bit(&br)) { /* seq_scaling_list_present    */
		  int last = 8, next = 8, size = (i<6) ? 16 : 64;
		  for (j = 0; j < size; j++) {
			if (next)
			  next = (last + br_get_se_golomb(&br)) & 0xff;
			last = next ? next : last;
		  }
		}
	  }

	  br_skip_ue_golomb(&br);      /* log2_max_frame_num - 4 */
	  pic_order_cnt_type = br_get_ue_golomb(&br);
	  if (pic_order_cnt_type == 0)
		br_skip_ue_golomb(&br);    /* log2_max_poc_lsb - 4 */
	  else if (pic_order_cnt_type == 1) {
		br_skip_bit(&br);          /* delta_pic_order_always_zero     */
		br_skip_se_golomb(&br);    /* offset_for_non_ref_pic          */
		br_skip_se_golomb(&br);    /* offset_for_top_to_bottom_field  */
		j = br_get_ue_golomb(&br); /* num_ref_frames_in_pic_order_cnt_cycle */
		for (i = 0; i < j; i++)
		  br_skip_se_golomb(&br);  /* offset_for_ref_frame[i]         */
	  }
	  br_skip_ue_golomb(&br);      /* ref_frames                      */
	  br_skip_bit(&br);            /* gaps_in_frame_num_allowed       */
	  sps->width  /* mbs */ = br_get_ue_golomb(&br) + 1;
	  sps->height /* mbs */ = br_get_ue_golomb(&br) + 1;
	  frame_mbs_only        = br_get_bit(&br);
	  //LOGDBG("H.264 SPS: pic_width:  %u mbs\n", (unsigned) sps->width);
	  //LOGDBG("H.264 SPS: pic_height: %u mbs\n", (unsigned) sps->height);
	  //LOGDBG("H.264 SPS: frame only flag: %d\n", frame_mbs_only);

	  sps->width  *= 16;
	  sps->height *= 16 * (2-frame_mbs_only);

	  if (!frame_mbs_only)
		if (br_get_bit(&br)) /* mb_adaptive_frame_field_flag */
		  ;//LOGDBG("H.264 SPS: MBAFF");
	  br_skip_bit(&br);      /* direct_8x8_inference_flag    */
	  if (br_get_bit(&br)) { /* frame_cropping_flag */
		uint32_t crop_left   = br_get_ue_golomb(&br);
		uint32_t crop_right  = br_get_ue_golomb(&br);
		uint32_t crop_top    = br_get_ue_golomb(&br);
		uint32_t crop_bottom = br_get_ue_golomb(&br);
		//LOGDBG("H.264 SPS: cropping %d %d %d %d\n",
		//   crop_left, crop_top, crop_right, crop_bottom);

		sps->width -= 2*(crop_left + crop_right);
		if (frame_mbs_only)
		  sps->height -= 2*(crop_top + crop_bottom);
		else
		  sps->height -= 4*(crop_top + crop_bottom);
	  }

	  return 1;
	}
	void EmitReadyPlay(int duration){
		bConnected = true;
		emit signalTimerstart();
		if(m_linkid==PLAYBACK_LINK_ID)
			emit signalReadyPlay(duration);
		else
		{
			qDebug()<<"emit 1 signalPrepareConnect:"<<curr_coach;
			emit signalPrepareConnect(curr_coach);
		}
	}
	void EmitFinishPlay(NvcLiveErr_e errCode){
		bConnected = false;
		emit signalFinishPaly(errCode);
	}

	void EmitPlayProgress(double ntp)
	{
		emit signalPlayProgress(ntp);
	}

	void EmitChnPlayState()
	{
		emit signalChnPlayState(m_linkid, true);
	}

	CRTSPHandle_t handle(){
		return m_Handle;
	}
	void ConvertImage(unsigned char* buffer,unsigned frameSize){
		int needHead = 0;
		int skitnum = 4;
		uint8_t *tmp;
		uint8_t *tmpbuff;
		//qDebug()<<"size = "<<frameSize<<",  "<<buffer[0]<<","<<buffer[1]<<","<<buffer[2]<<","<<buffer[3]<<","<<buffer[4]<<","<<buffer[5]<<","<<buffer[6]<<","<<buffer[7]<<","<<buffer[8]<<","<<buffer[9];
		if(buffer[0]==0&&buffer[1]==0&&buffer[2]==0&&buffer[3]==1)
		{
			skitnum = 4;
			tmp = buffer;//这里填入一个指向完整H264数据帧的指针
			//packet.size = frameSize;//这个填入H264数据帧的大小
		}
		else if(buffer[0]==0&&buffer[1]==0&&buffer[2]==1)
		{
			skitnum = 3;
			tmp = buffer;//这里填入一个指向完整H264数据帧的指针
			//packet.size = frameSize;//这个填入H264数据帧的大小
		}
		else
		{
			needHead = 1;
			tmpbuff = new uint8_t[frameSize+4];
			tmpbuff[0]=tmpbuff[1]=tmpbuff[2]=0;tmpbuff[3]=1;
			memcpy(tmpbuff+4, buffer, frameSize);
			tmp = tmpbuff;//这里填入一个指向完整H264数据帧的指针
			frameSize = frameSize+4;
			//packet.size = frameSize+4;//这个填入H264数据帧的大小
		}
		//packet.data = tmp;

		unsigned frameType = tmp[4] & 0x1F;
		if(frameType == 0x7){
			if(!isInited){
				isInited = 1;
				h264_sps_data_t sps;

				h264_parse_sps(tmp+skitnum+1,frameSize-skitnum-1,&sps);
				frameH = sps.height;
				if(m_linkid == PLAYBACK_LINK_ID)
				qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>"<<sps.width<<"  "<<sps.height;

				JVS_FILE_HEADER_EX jHeaderEx;
				JVS_FILE_HEADER	jHeader = {0};
				jHeader.nFlag			= 0x2053564A;
				jHeader.nVideoFormat	= 0;
				jHeader.nTotalFrames	= 0;
				jHeader.nFrameWidth 	= sps.width;
				jHeader.nFrameHeight 	= sps.height;
				jHeader.u32IIndexAddr = 0;
				memset(&jHeaderEx, 0, sizeof(JVS_FILE_HEADER_EX));
				memcpy(jHeaderEx.ucOldHeader, &jHeader, sizeof(JVS_FILE_HEADER));

				//结构体信息
				strcpy((char*)jHeaderEx.ucHeader, "JFH");	//结构体识别码，设置为‘J','F','H'
				jHeaderEx.ucVersion = 1;			//结构体版本号，当前版本为1
				//设备相关
				jHeaderEx.wDeviceType 			= 0x0004;		//设备类型
				//视频部分
				jHeaderEx.wVideoCodecID 		= 1;	//视频编码类型
				jHeaderEx.wVideoDataType 		= 1;			//数据类型
				jHeaderEx.wVideoFormat 			= 1;				//视频模式
				jHeaderEx.wVideoWidth 			= sps.width;						//视频宽
				jHeaderEx.wVideoHeight 			= sps.height;						//视频高
				jHeaderEx.wFrameRateNum 		= 25;				//帧率分子
				jHeaderEx.wFrameRateDen 		= 1;						//帧率分母
				//音频部分
				jHeaderEx.wAudioCodecID 		= 0;	//音频编码格式
				jHeaderEx.wAudioSampleRate 		= 8000;						//音频采样率
				jHeaderEx.wAudioChannels 		= 1;						//音频声道数
				jHeaderEx.wAudioBits 			= 16;						//音频采样位数
				//录像相关
				jHeaderEx.dwRecFileTotalFrames 	= 0;						//录像总帧数
				jHeaderEx.wRecFileType 			= 3;		//录像类型
				RECT r;
				if (m_linkid == 6)
				{
					qDebug() << 0;
				}
				r.top=g_chnInfo[m_linkid].location.top();
				r.left=g_chnInfo[m_linkid].location.left();
				r.right=g_chnInfo[m_linkid].location.right();
				r.bottom=g_chnInfo[m_linkid].location.bottom();
				qDebug()<<m_linkid<<", "<<m_playerId<<", "
					<<"["<<r.left<<","<<r.top<<","<<r.right-r.left<<","<<r.bottom-r.top<<"]"
					<<",  "<<m_hwnd;
				JVSP_OpenStream(m_playerId, (PUCHAR)&jHeaderEx, sizeof(JVS_FILE_HEADER_EX));
				JVSP_SetVideoPreview(m_playerId, (HWND)m_hwnd, &r, 1);
			}
		}

		if(isInited && bConnected){
			//if(m_linkid==2)
				//qDebug()<<m_playerId<<", "<<frameSize<<", "<<packet.data[0]<<", "<<packet.data[1]<<", "<<packet.data[2]<<", "<<packet.data[3]<<", "<<packet.data[4]<<", "<<packet.data[5]<<", "<<packet.data[6];
			//	qDebug()<<m_playerId<<", "<<frameSize<<", "<<packet.data[0]<<", "<<packet.data[1]<<", "<<packet.data[2]<<", "<<packet.data[3]<<", "<<packet.data[4]<<", "<<packet.data[5]<<", "<<packet.data[6];

			//qDebug()<<m_playerId<<","<<frameSize<<" :"<<tmp[0]<<","<<tmp[1]<<","<<tmp[2]<<","<<tmp[3]<<","<<tmp[4]<<","<<tmp[5]<<","<<tmp[6]<<","<<tmp[7]<<","<<tmp[8]<<","<<tmp[9]<<",";
			if(m_playerId>=0)
				JVSP_WriteToStreamOneFrame(m_playerId, tmp, frameSize);
		}

		if(needHead)
		{
			delete tmpbuff;
			tmpbuff = NULL;
			tmp = NULL;
		}
	}
	void stopplay(){
		//isInited = 0;
		m_chnState[m_linkid] = false;
		bConnected = false;
		if(m_linkid==PLAYBACK_LINK_ID)
			if(timer.isActive())
				timer.stop();
#if 1
		jvlive_client_destroy(m_Handle);
		m_Handle = NULL;
#else
		jvlive_client_stop(&streamID);
		//memset(&streamID, 0, sizeof(m_streamID_t));
#endif
		JVSP_CloseStream(m_playerId);
		JVSP_ReleasePlayer(m_playerId);
		m_playerId = -1;
		EmitFinishPlay(NVC_LIVE_ERR_OVER);
	}

	void changePlayRect()
	{
		RECT r;
		r.top=g_chnInfo[m_linkid].location.top();
		r.left=g_chnInfo[m_linkid].location.left();
		r.right=g_chnInfo[m_linkid].location.right();
		r.bottom=g_chnInfo[m_linkid].location.bottom();
		qDebug()<<"changePlayRect"<<m_linkid<<", "<<m_playerId<<", "
					<<"["<<r.left<<","<<r.top<<","<<r.right-r.left<<","<<r.bottom-r.top<<"]"
					<<",  "<<m_hwnd;
		JVSP_SetVideoPreview(m_playerId, (HWND)m_hwnd, &r, 1);
	}

public:
	bool bConnected;
	bool bEverConncected;
	int timeout;
	int m_playerId;
	int m_linkid;
	int isInited;
	int frameH;
	int m_hwnd;
	CRTSPHandle_t m_Handle;
	m_streamID_t streamID;
	QString curr_playurl;
	uint8_t *out_buffer;
	QTimer timer;
	bool m_isFirst;
	int curr_coach;
};


#endif



