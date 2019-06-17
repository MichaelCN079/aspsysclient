#ifndef PREVIEWSTACK_H
#define PREVIEWSTACK_H

#include <QStackedWidget>
#include <QTimer>
#include <QMap>
#include <QPair>

class QThread;
class PreviewStack : public QStackedWidget
{
    Q_OBJECT

public:
    PreviewStack(QWidget *parent = nullptr);
    ~PreviewStack();

    void init();
	void startPreview();
	void SetPollingTime(int iPollingTime);
	void ToggleSubViewPos();
	int GetCurrentIPCIndex();

signals:
    void sigVideoPauseBtnClicked(bool bPause);
    void sigVideoChanged(QWidget *); //播放画面改变
	void signalPrepareConnect(int);
	void signalExitFullView();
	void signalToggleMainSubView();

public slots:
    void slotCameraSwitchBtnClicked(bool bFlag);
    void slotCameraLightBtnClicked(bool bFlag);
    void slotVideoPauseBtnClicked(bool bFlag);
    void slotVideoPlayBtnClicked(bool bFlag);
    void slotVideoNextBtnClicked();
    void slotVideoPreBtnClicked();
    void slotvideoAheadBtnClicked();
    void slotVideoSaveBtnClicked();


protected:
    void timerEvent(QTimerEvent *);
    bool eventFilter(QObject *, QEvent *);

private:
    QStringList m_urlList;
    QStringList m_winIdList;
    QThread *m_pWorkThread;
    int m_timerId;
    int m_currIndex; //当前画面
    int m_type; //0:短编组，1:长编组
    QMap<int, QPair<int, int>> m_dispMap; //长编组画面与装置对应关系 画面序号:(主画面编号:小画面编号)
	int m_iPollingTime;	//轮询时间（秒）
};

#endif // PREVIEWSTACK_H
