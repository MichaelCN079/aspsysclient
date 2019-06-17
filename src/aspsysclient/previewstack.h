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
    void sigVideoChanged(QWidget *); //���Ż���ı�
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
    int m_currIndex; //��ǰ����
    int m_type; //0:�̱��飬1:������
    QMap<int, QPair<int, int>> m_dispMap; //�����黭����װ�ö�Ӧ��ϵ �������:(��������:С������)
	int m_iPollingTime;	//��ѯʱ�䣨�룩
};

#endif // PREVIEWSTACK_H
