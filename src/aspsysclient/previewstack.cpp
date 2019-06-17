#include "previewstack.h"
#include "common.h"
#include "previewwidget.h"
#include "JVSDKP.h"
#include "playworker.h"
#include "startconnectwork.h"
#include <QThread>
#include <QHBoxLayout>
#include <QEvent>

PreviewStack::PreviewStack(QWidget *parent):QStackedWidget(parent), m_currIndex(0), m_iPollingTime(30)
{
    setGeometry(0, 0, 0, 0);
    if (g_deviceInfo.deviceCount > 2) //长编组
    {
        m_type = 1;

        if ((g_deviceInfo.deviceCount % 2) == 0) //摄像机个数为偶数
        {
            int *ids = new int[g_deviceInfo.deviceCount];
            for (int i = 0; i < (g_deviceInfo.deviceCount / 2); i++)
            {
                PreviewWidget *p = new PreviewWidget(1, g_deviceInfo.m_devices[i].coach, g_deviceInfo.m_devices[i].index,
                                                     g_deviceInfo.m_devices[i+g_deviceInfo.deviceCount/2].coach,
                                                     g_deviceInfo.m_devices[i+g_deviceInfo.deviceCount/2].index);
                insertWidget(i, p);
                m_dispMap.insert(i, QPair<int, int>(i, i+g_deviceInfo.deviceCount/2));
                //connect(this, SIGNAL(sigVideoChanged(QWidget*)), p, SLOT(slotVideoChanged(QWidget*)));

                CurrPlayWork[i] = new PlayWorker(i, p->m_pMainPreviewWidget);
                CurrPlayWork[i+g_deviceInfo.deviceCount/2] = new PlayWorker(i+g_deviceInfo.deviceCount/2, p->m_pSubPreviewWidget);
                ids[i] = p->m_pMainPreviewWidget->winId();
                ids[i+g_deviceInfo.deviceCount/2] = p->m_pSubPreviewWidget->winId();
//                urlList[i] = QString("rtsp://%1:554/%2").arg(g_deviceInfo.m_devices[i].ip).arg(g_deviceInfo.m_devices[i].index);
//                urlList[i+g_deviceInfo.deviceCount/2] = QString("rtsp://%1:554/%2").arg(g_deviceInfo.m_devices[i+g_deviceInfo.deviceCount/2].ip)
//                        .arg(g_deviceInfo.m_devices[i+g_deviceInfo.deviceCount/2].index);

				connect(p, SIGNAL(signalMainViewClicked()), this, SIGNAL(signalExitFullView()));
				connect(p, SIGNAL(signalToggleMainSubView()), this, SIGNAL(signalToggleMainSubView()));
				connect(CurrPlayWork[i+g_deviceInfo.deviceCount/2], SIGNAL(signalChnPlayState(int, bool)), this, SLOT(slotChnPlayState(int, bool)));
				connect(CurrPlayWork[i+g_deviceInfo.deviceCount/2], SIGNAL(signalChnStateChanged(int, int)), this, SLOT(slotChnStateChanged(int, int)));
				connect(CurrPlayWork[i+g_deviceInfo.deviceCount/2], SIGNAL(signalPrepareConnect(int)), this, SIGNAL(signalPrepareConnect(int)));
            }
            for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
            {
                m_winIdList << QString::number(ids[i], 10);
                m_urlList << QString("rtsp://%1:554/%2").arg(g_deviceInfo.m_devices[i].NvrIp).arg(g_deviceInfo.m_devices[i].index);
            }
        }
        else //摄像机个数为奇数
        {

        }
    }
    else if (g_deviceInfo.deviceCount == 2) //短编组
    {
        m_type = 0;
        for (int i = 0; i != g_deviceInfo.deviceCount; ++i)
        {
            PreviewWidget *p = new PreviewWidget(0, g_deviceInfo.m_devices[i].coach, g_deviceInfo.m_devices[i].index);
            //connect(this, SIGNAL(sigVideoChanged(QWidget*)), p, SLOT(slotVideoChanged(QWidget*)));
            m_winIdList << QString::number(p->winId());
            CurrPlayWork[i] = new PlayWorker(i, p);
            insertWidget(i, p);
            QString url = QString("rtsp://%1:554/%2").arg(g_deviceInfo.m_devices[i].NvrIp).arg(g_deviceInfo.m_devices[i].index);
            m_urlList << url;
        }
    }
	m_currcoach = ((PreviewWidget *)currentWidget())->m_iCurCoach;
	m_currindex = ((PreviewWidget *)currentWidget())->m_iCurIndex;
    installEventFilter(this);
}

PreviewStack::~PreviewStack()
{

}

void PreviewStack::init()
{
    JVSP_InitSDK();
    StartConnectWork *conn = new StartConnectWork();
    conn->init(m_winIdList, m_urlList);
    m_pWorkThread = new QThread;
    conn->moveToThread(m_pWorkThread);
    connect(m_pWorkThread, SIGNAL(started()), conn, SLOT(doWork()));
    connect(m_pWorkThread, SIGNAL(finished()), conn, SLOT(deleteLater()));
}

void PreviewStack::startPreview()
{
    m_pWorkThread->start();
    m_timerId = startTimer(30*1000);
}

bool PreviewStack::eventFilter(QObject *obj, QEvent *evt)
{
    //if (obj == this)
    {
        if (evt->type() == QEvent::Paint)
        {
            if (m_type == 0)
            {
                //for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
                {
                    QRect rect;
                    rect = widget(currentIndex())->geometry();
                    //更新视频显示位置--将smalldispArea的位置转化为在dispArea中的位置
                    QPoint topleft = mapToGlobal(rect.topLeft());
                    QPoint bottomright = mapToGlobal(rect.bottomRight());
                    g_chnInfo[currentIndex()].location.setTopLeft(topleft);
                    g_chnInfo[currentIndex()].location.setBottomRight(bottomright);
                    PlayWorker *playworker = CurrPlayWork[currentIndex()];
                    if (playworker) playworker->changePlayRect();
                }
            }
            else if (m_type == 1)
            {
                //for (int i = 0; i < (g_deviceInfo.deviceCount/2); ++i)
                {
					QRect rectBig = widget(currentIndex())->geometry();
					QRect rectSmall;
					int iSubViewPos = ((PreviewWidget*)widget(currentIndex()))->GetSubViewPos();
					rectSmall.setX(rectBig.width() * (iSubViewPos % 4) / 4);
					rectSmall.setY(rectBig.height() * (iSubViewPos / 4) / 4);
					rectSmall.setWidth(rectBig.width() / 4);
					rectSmall.setHeight(rectBig.height() / 4);

					QRect rectMain = rectBig;
					QRect rectSub = rectSmall;
					if (((PreviewWidget*)widget(currentIndex()))->GetViewToggleFlag())
					{
						rectMain = rectSmall;
						rectSub = rectBig;
					}

					QWidget *pMainWidget = ((PreviewWidget*)widget(currentIndex()))->m_pMainPreviewWidget;
					pMainWidget->setGeometry(rectMain);
                    g_chnInfo[currentIndex()].location.setTopLeft(mapToGlobal(rectMain.topLeft()));
                    g_chnInfo[currentIndex()].location.setBottomRight(mapToGlobal(rectMain.bottomRight()));
                    PlayWorker *playworker = CurrPlayWork[currentIndex()];
                    if (playworker) playworker->changePlayRect();

					QWidget *pSubWidget = ((PreviewWidget*)widget(currentIndex()))->m_pSubPreviewWidget;
					pSubWidget->setGeometry(rectSub);
                    g_chnInfo[currentIndex()+g_deviceInfo.deviceCount/2].location.setTopLeft(mapToGlobal(rectSub.topLeft()));
                    g_chnInfo[currentIndex()+g_deviceInfo.deviceCount/2].location.setBottomRight(mapToGlobal(rectSub.bottomRight()));
                    PlayWorker *subPlayworker=CurrPlayWork[currentIndex()+g_deviceInfo.deviceCount/2];
                    if (subPlayworker) subPlayworker->changePlayRect();
                }
            }
        }
    }
    return QWidget::eventFilter(obj, evt);
}


void PreviewStack::slotCameraSwitchBtnClicked(bool bFlag)
{

}

void PreviewStack::slotCameraLightBtnClicked(bool bFlag)
{

}

void PreviewStack::slotVideoPauseBtnClicked(bool bFlag)
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = 0;
    }
    emit sigVideoPauseBtnClicked(true);
}

void PreviewStack::slotVideoPlayBtnClicked(bool bFlag)
{
    m_timerId = startTimer(30*1000);
    emit sigVideoPauseBtnClicked(false);
}

void PreviewStack::slotVideoNextBtnClicked()
{

}

void PreviewStack::slotVideoPreBtnClicked()
{
    int currIndex = currentIndex();
    if (currentIndex() != 0)
        setCurrentIndex(currIndex - 1);
    else
        setCurrentIndex(count() - 1);
	m_currcoach = ((PreviewWidget *)currentWidget())->m_iCurCoach;
	m_currindex = ((PreviewWidget *)currentWidget())->m_iCurIndex;
    eventFilter(this, new QEvent(QEvent::Paint));
    emit sigVideoChanged(currentWidget());
}

void PreviewStack::slotvideoAheadBtnClicked()
{
    int currIndex = currentIndex();
    if (currIndex != (count()-1))
    {
        setCurrentIndex(currIndex+1);
    }
    else
    {
        setCurrentIndex(0);
    }
	m_currcoach = ((PreviewWidget *)currentWidget())->m_iCurCoach;
	m_currindex = ((PreviewWidget *)currentWidget())->m_iCurIndex;

    eventFilter(this, new QEvent(QEvent::Paint));
    emit sigVideoChanged(currentWidget());

}

//切换小画面位置
void PreviewStack::ToggleSubViewPos()
{
	int iSubViewPos = ((PreviewWidget *)currentWidget())->GetSubViewPos();
	switch(iSubViewPos)
	{
	case 0:
		iSubViewPos = 3;
		break;
	case 3:
		iSubViewPos = 15;
		break;
	case 15:
		iSubViewPos = 12;
		break;
	case 12:
		iSubViewPos = 0;
		break;
	default:
		iSubViewPos = 3;
		break;
	}
	((PreviewWidget *)currentWidget())->SetSubViewPos(iSubViewPos);
	eventFilter(this, new QEvent(QEvent::Paint));
}

void PreviewStack::slotVideoSaveBtnClicked()
{

}

void PreviewStack::SetPollingTime(int iPollingTime)
{
	m_iPollingTime = iPollingTime;
	if (m_timerId != 0)
	{
		killTimer(m_timerId);
		m_timerId = startTimer(m_iPollingTime * 1000);
	}
}

int PreviewStack::GetCurrentIPCIndex()
{
	int iStackIndex = currentIndex();
	if (((PreviewWidget *)currentWidget())->GetViewToggleFlag())
	{
		iStackIndex += g_deviceInfo.deviceCount / 2;
	}
	return iStackIndex;
}

void PreviewStack::timerEvent(QTimerEvent *)
{
    if (currentIndex() == (count() - 1))
        setCurrentIndex(0);
    else
        setCurrentIndex(currentIndex()+1);
	m_currcoach = ((PreviewWidget *)currentWidget())->m_iCurCoach;
	m_currindex = ((PreviewWidget *)currentWidget())->m_iCurIndex;
    eventFilter(this, new QEvent(QEvent::Paint));

    qDebug() << "Current Index " << currentIndex();
}

