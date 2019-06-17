#ifndef _MONITER_H_
#define _MONITER_H_

//必须加以下内容,否则编译不能通过,为了兼容C和C99标准
#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif


/*
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
}*/
//#include "qffmpeg.h"
//#include "rtspthread.h"
#include <qtimer.h>
#include <QTcpSocket.h>
#include <QProgressDialog>
#include <QTextEdit>

#define AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000

#define MAX_AUDIOQ_SIZE (5 * 16 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 256 * 1024)

#define VIDEO_PICTURE_QUEUE_SIZE 1

// 定义360号技术规范协议标识
#define  PVMS_PROTOCOL_HEADER_SC       (0xFF)
#define  PVMS_PROTOCOL_HEATER_CLIENT   (0x01)
#define  PVMS_PROTOCOL_HEATER_NVR      (0x51)
#define  PVMS_PROTOCOL_SET_IPCOSD      (0x02)
#define  PVMS_PROTOCOL_PIS_2_CLIENT    (0x04)
#define  PVMS_PROTOCOL_OVERLAY_OSD     (0x05)
#define  PVMS_PROTOCOL_NTP             (0x06)
#define  PVMS_PROTOCOL_CHECK_NVR_INFO      (0x07)
#define  PVMS_PROTOCOL_CHECK_NVR_INFO_ACK  (0x57)
#define  PVMS_PROTOCOL_CHECK_IPC_INFO      (0x08)
#define  PVMS_PROTOCOL_CHECK_IPC_INFO_ACK  (0x58)
#define  PVMS_PROTOCOL_VIDEO_FAULT         (0x09)
#define  PVMS_PROTOCOL_HD_FAULT            (0x10)
#define  PVMS_PROTOCOL_REMOTE_SEACH_FILE   (0x11)
#define  PVMS_PROTOCOL_REMOTE_SEACH_FILE_ACK (0x61)
#define  PVMS_PROTOCOL_PTZ                   (0x12)
#define  PVMS_PROTOCOL_PTZ_ACK				 (0x62)
#define  PVMS_PROTOCOL_PTZ_PRESET            (0x13)
#define  PVMS_PROTOCOL_PTZ_PRESET_ACK        (0x63)
#define  PVMS_PROTOCOL_IPC_CTL               (0x14)
#define  PVMS_PROTOCOL_IPC_CTL_ACK           (0x64)
#define  PVMS_PROTOCOL_LIGHT_CTL             (0x15)
#define  PVMS_PROTOCOL_LIGHT_CTL_ACK         (0x65)
#define  PVMS_PROTOCOL_SDG_INFO              (0x16)
#define  PVMS_PROTOCOL_SDG_INFO_ACK          (0x66)
#define  PVMS_PROTOCOL_REMOTE_SEACH_PHOTO    (0x17)
#define  PVMS_PROTOCOL_REMOTE_SEACH_PHOTO_ACK    (0x67)
#define  PVMS_PROTOCOL_GET_FAULT_PARAM            (0x18)
#define  PVMS_PROTOCOL_GET_FAULT_PARAM_ACK        (0x68)
#define  PVMS_PROTOCOL_SET_FAULT_PARAM_ACK        (0x19)
#define  PVMS_PROTOCOL_SET_FAULT_PARAM_ACK        (0x69)
#define  PVMS_PROTOCOL_SDG_FAULT_ALARM        (0x20)
#define  PVMS_PROTOCOL_SDG_GPS_PACKAGE        (0x21)
#define  PVMS_PROTOCOL_PIS_SDG_INFO           (0x22)
#define  PVMS_PROTOCOL_GET_PLAYBACK_TOTAL_TIME           (0x42)
#define  PVMS_PROTOCOL_GET_PLAYBACK_TOTAL_TIME_ACK       (0x82)
#define  PVMS_PROTOCOL_GET_SDG_COACH_NO       (0x43)
#define  PVMS_PROTOCOL_GET_SDG_COACH_NO       (0x83)

class MoniterClient:public QObject
{
    Q_OBJECT
public:
    struct CMD_HEAD{
        unsigned char flag;
        unsigned char id;
        unsigned short len;
    };
    static unsigned char crc_sum(unsigned char *buf, int len)
    {
        int i;
        unsigned char crc_;

        if(buf)
        {
            for(crc_ = buf[0], i=1; i<len; i++)
                crc_^=buf[i];
            return crc_;
        }
        return -1;
    }
    explicit MoniterClient(QObject *parent);
    ~MoniterClient();
    void sendMessage(const QByteArray &msg);
    void sendCmd(int coach, const QByteArray &msg);
	void prepare(int);
signals:
    void signalSearchRecords(QString);
    void signalDevicesInfosNVR(QByteArray&);
    void signalDevicesInfosIPC(QByteArray&);
	void signalNVRLog(QByteArray&);
	void signalIPCLog(QByteArray&);
	void signalDeviceNeedUpdate(int);
	void signalImportCfg(QByteArray&);
	void signalDownload();
	void signalGetIPCColorPara(QByteArray&);
	void signalGetIPCStreamPara(QByteArray&);

	void signalAlarmPushed();
	void signalNtpResult();
	void signalIPCYstNo(QByteArray&);

	void signalSetOsdResult();
	void signalNewAlarm(int&,QByteArray&);
public slots:
    QString slotReadSocket(QString);
	void slotTimeout();
	void slotLightTimeout(QString);
	void slotSocketConnected(QString);
	void slotSocketDisconnected(QString);

private:
	int m_timeouttime;
	int checkheart;
	QTimer m_timer;
	QTimer m_timerlight[4];//根据升降弓控制补光灯关的定时器
    QMutex mutex;
    QMutex pis_mutex;
    int m_coachid;
    QStringList urls;
    bool connectOK;
    int msgId;
    int heartbeat;
    QTextEdit *dumpedit;
	QString m_recordfiles;

	QProgressDialog *progressDialog;
	QMap<int,bool> nvrconnectmap;
};

extern MoniterClient *Moniter;
#endif
