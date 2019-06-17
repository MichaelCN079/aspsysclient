//#include "StdAfx.h"
#include "playworker.h"
#include <sys\types.h>
#include <sys\stat.h>
#include <fcntl.h>

#define PLAY_USING_JV

#if 0
由于Qt Creator使用的是mingW进行程序编译，该编译方式无法识别#pragma comment(lib,"xxx.lib")引用
#pragma comment(lib,"libBasicUsageEnvironment.lib")
#pragma comment(lib,"libgroupsock.lib")
#pragma comment(lib,"libjvlive.lib")
#pragma comment(lib,"libUsageEnvironment.lib")
#pragma comment(lib,"libliveMedia.lib")
#endif

int xxxxx_fd=-1;
FILE *xxxx = NULL;
double ntp_now = -1;
double ntp_last = -1;
PlayWorker* CurrPlayWork[PLAY_LINK_ID_MAX] = { NULL };

void rtsp_stream_getted_func(void* param, void *channelHandle, unsigned char* buffer,unsigned frameSize, struct timeval presentationTime,unsigned durationInMicroseconds){
	//PlayWorker* playwork = (PlayWorker*)param;
	int id = (int)param;
	CurrPlayWork[id]->ConvertImage(buffer, frameSize);
	//qDebug() << "---------------:" << id;
	//if (id != PLAYBACK_LINK_ID)
		CurrPlayWork[id]->clearTimeout();

	if(id == PLAYBACK_LINK_ID)
	{
		ntp_now = presentationTime.tv_sec+(double)presentationTime.tv_usec/1000000;
		if(ntp_last==-1)ntp_last = ntp_now;
		double d = ntp_now-ntp_last;
		if(d>=0.0 && d <0.5)
		{
			CurrPlayWork[PLAYBACK_LINK_ID]->EmitPlayProgress(d);
			//qDebug()<<"----------ntp="<<ntp_now-ntp_last<<",   "<<presentationTime.tv_sec;
		}
		ntp_last = ntp_now;
	}

	if (!m_chnState[id])
		m_chnState[id] = true;
}

void rtsp_stream_after_playing_func(void* param, NvcLiveErr_e errCode, const char *errMsg, int extradata){
	int duration;
	int id = (int)param;
	
	if(id == PLAYBACK_LINK_ID)
	{
		ntp_now = -1;
		ntp_last = -1;
	}

//	m_streamID_t *streamID = CurrPlayWork[id]->streamId();
    switch(errCode)
    {
        //default:
        case NVC_LIVE_ERR_OK:		//播放ok,rtsp库播放ok，会回调一次
            qDebug()<<errMsg<<"Play VCONNECTED...";
			if(extradata<1)
				duration = 600;//默认10分钟
			else
				duration = extradata;
			CurrPlayWork[id]->EmitReadyPlay(duration);
            break;
        case NVC_LIVE_ERR_OVER:		//播放完成
			qDebug()<<errMsg<<" Play OK OK OK....";
			//jvlive库更新：播放前会计算一个正常速度下的播放时长，时间到了会回调到此，原先的逻辑是结束播放，但如果是慢放就不对了。
			//下面做了一下区分,手动停止时回调到此的extradata==0；播放时间到了回调到此的extradata==1；
			//extradata==1在此不做处理，2s没有数据到来slotTimerout函数停止播放。
			if(extradata==0){
				CurrPlayWork[id]->stopplay();
			}
            break;
        case NVC_LIVE_ERR_TIMEOUT:
            qDebug()<<"VCONNTIMEOUT....................";
			CurrPlayWork[id]->stopplay();
            break;
        case NVC_LIVE_ERR_WRONG_PASSWD:
            qDebug()<<"VPASSWORDERR...................";
			CurrPlayWork[id]->stopplay();
            break;
        case NVC_LIVE_ERR_UNKNOWN:
			CurrPlayWork[id]->stopplay();
			duration = 10;
			CurrPlayWork[id]->EmitReadyPlay(duration);
			break;
        case NVC_LIVE_ERR_BAD_REQUEST:
        case NVC_LIVE_ERR_NOT_FOUND:
        default:
            qDebug()<<"VCONNBREAK....................";
			CurrPlayWork[id]->stopplay();
        break;
    }
}
void PlayWorker::slotTimerout(){
	timeout++;
	if (timeout/5)
		if (bEverConncected)
			emit signalChnPlayState(m_linkid, false);
		else
			emit signalChnStateChanged(m_linkid, CHN_STATE_NO_VIDEO);

	if(!(timeout%2)){
		qDebug()<<"PlayWorker::slotTimerout     "<<m_linkid;
		if (m_linkid==PLAYBACK_LINK_ID)
		{
			emit signalPlayTimeOut();
			return;
		}
	}

	if(!(timeout%10)){
		if (bEverConncected)
			emit signalChnStateChanged(m_linkid, CHN_STATE_RECONNECTING);
		else
			emit signalChnStateChanged(m_linkid, CHN_STATE_NO_VIDEO);
		qDebug()<<"PlayWorker::slotTimerout     "<<m_linkid;
		PlayWorker *playworker=CurrPlayWork[m_linkid];
		playworker->stopplay();
		if(m_linkid!=PLAYBACK_LINK_ID)
			playworker->exit();
			/*while(1){
				if(playworker->isRunning()){
					QThread::msleep(100);
					continue;
				}
				break;
			}*/

		if(m_linkid!=PLAYBACK_LINK_ID){
			playworker->readyToPlay(m_hwnd, curr_playurl);
			playworker->start();
			//QThread::msleep(500);
		}
	}
}

