#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QStringList>
#include <Windows.h>
#include <QAbstractNativeEventFilter>
#include "moniter.h"

namespace Ui {
class ContentWidget;
}



class QTimerEvent;
class QMouseEvent;
class ContentWidget : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit ContentWidget(QWidget *parent = nullptr);
    ~ContentWidget();
    void setCC(QString cc);
    void slotSetTrainNo();

protected:
    void timerEvent(QTimerEvent *evt);
    //void mousePressEvent(QMouseEvent *evt);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    void initSlots();
    void initPtzControl();
    void initPreset();
    void getCurrInfo(); //�@ȡ��ǰ�O����Ϣ
    char FirstDriveFromMask (ULONG unitmask);
    bool updateFile(QString path);
    void insertRow(QTableWidget *tableWidget, QStringList strList);
    void deleteAllRows(QTableWidget *tableWidget);

public:
    enum {
        PTZ_UP = 1,
        PTZ_DOWN,
        PTZ_LEFT,
        PTZ_RIGHT,
        ZOOM_FAR,
        ZOOM_NEAR,
        FOCUS_FAR,
        FOCUS_NEAR,
        IPC_ON,
        IPC_OFF,
        LIGHT_ON,
        LIGHT_OFF
    };
    enum{
        PTZ_START = 1,
        PTZ_STOP
    };

private slots:
    void slotMonitorBtnClicked();
    void slotVideoBtnClicked();
    void slotInteliBtnClicked();
    void slotDevMngBtnClicked();
    void slotMaintainBtnClicked();
	void slotFullViewEvent();
	void slotToggleMainSubView();

    void slotptzStart(QString);
    void slotPtzStop();

    void slotCameraPosSet(int iPos);
    void slotVideoSetBtnClicked();
    void slotVideoGetBtnClicked();
    void slotCameraSwitchBtnClicked();
    void slotCameraLightBtnClicked();
    void slotVideoPlayBtnClicked(bool bFlag);
    void slotVideoPauseBtnClicked(bool bFlag);
    void slotVideoPauseResult(bool bFlag);
    void slotVideoNextBtnClicked();
    void slotSwitchSuccess(bool bFlag);
    void slotVideoPreBtnClicked();
    void slotvideoAheadBtnClicked();
    void slotVideoSaveBtnClicked();

    void slotSearchBtnClicked();
    void slotHandleSearch(QString s);

    void slotCurrInfosNVR(QByteArray&);
    void slotCurrInfosIPC(QByteArray&);

    void slotRadioBtnGrp1Clicked(bool bFlag);
    void slotRadioBtnGrp2Clicked(bool bFlag);
    void slotCxTypeBtnClicked(); //����ѡ��ȷ�ϲۺ���
    void timerOuttime(); //�����ʱ�����
    void slotTimeAdjustBtnClicked(); //���Уʱ��ť����
    void slotParamBtnClicked();  //������ò�����ť
    void slotUpdateProBtnClicked(); //�������°�ť
    void slotUpdateThenRestart();   //���³ɹ���������ť


    void slotCCMNGBtnClicked(); //�������ι���ť

    void slotExitBtnClicked();
	void slotPrepareConnect(int coach);

public:
    Ui::ContentWidget *ui;

private:
    int m_timerId;
    int m_searchTimer;
    int m_lastCmd;
    int m_ipcStatus; //0:�� 1:��
    int m_lightStatus; // 0:�� 1����
    MoniterClient *moniter;
    QDateTimeEdit *pMonitorTime;
    QTimer timer;
    QString m_udiskpath;
    int m_nvr_status_cnt;
    int m_currentVideoIndex;
	int m_iCameraPos;
	QPushButton * m_pbtCameraPos[8];
};

#endif // CONTENTWIDGET_H
