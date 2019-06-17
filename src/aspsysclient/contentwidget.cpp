#include "contentwidget.h"
#include "ui_contentwidget.h"
#include "loginwidget.h"
#include "JVSDKP.h"
#include "VideoPlayer.h"
#include "moniter.h"
#include "common.h"

#include <QPalette>
#include <QTimerEvent>
#include <QListView>
#include <QDateTimeEdit>
#include <QDateTime>
#include <QSignalMapper>
#include <QDomDocument>
#include <QDebug>

static int SCREEN_COUNT_TIMER = 3000;    //进入全屏的时间，单位为毫秒
static int PRESET_POINT_RETURN = 5;      //返回预置点时间，单位为分钟
int RETCODE_RESTART = 773;  //重启指令

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent), m_ipcStatus(1), m_lightStatus(1),
    ui(new Ui::ContentWidget), m_iCameraPos(1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint); //设置窗体无边框
    //添加背景图片
    QPalette mypalette = palette();
    mypalette.setBrush(QPalette::Background, QBrush(QPixmap(":/myimages/images/background.png")));
    setPalette(mypalette);

    ui->widget_2->setContentsMargins(0,0,0,0);
    ui->widget_3->setContentsMargins(0,0,0,0);

    m_timerId = startTimer(SCREEN_COUNT_TIMER);
    initSlots();

    moniter = new MoniterClient(this);
    {
        connect(moniter, SIGNAL(signalDevicesInfosNVR(QByteArray&)), this, SLOT(slotCurrInfosNVR(QByteArray&)));
        connect(moniter, SIGNAL(signalDevicesInfosIPC(QByteArray&)), this, SLOT(slotCurrInfosIPC(QByteArray&)));
        connect(moniter, SIGNAL(signalSearchRecords(QString)), this, SLOT(slotHandleSearch(QString)));
    }

    QStringList strList;
    //录像回放
    strList << QString::fromLocal8Bit("选中") << QString::fromLocal8Bit("序号") << QString::fromLocal8Bit("文件名");
    ui->videoFileWidget->setColumnCount(3);
    ui->videoFileWidget->setHorizontalHeaderLabels(strList);
    ui->videoFileWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image:url(:/myimages/images/editGround.png);}");
    ui->videoFileWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //录像回放，使下拉列表样式生效代码
    ui->coachListCB->setView(new QListView());
    for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
    {
        bool flag = false;
        for (int j = 0; j < ui->coachListCB->count(); ++j)
        {
            if (QString::number(g_deviceInfo.m_devices[i].coach) == ui->coachListCB->itemText(j))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ui->coachListCB->addItem(QString::number(g_deviceInfo.m_devices[i].coach));
    }
    ui->ipcIndexCB->setView(new QListView());
    for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
    {
        bool flag = false;
        for (int j = 0; j < ui->ipcIndexCB->count(); j++)
        {
            if (QString::number(g_deviceInfo.m_devices[i].index) == ui->ipcIndexCB->itemText(j))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ui->ipcIndexCB->addItem(QString::number(g_deviceInfo.m_devices[i].index));
    }
    ui->widget->setLayout(ui->horizontalLayout_23);

    //设备管理
    strList.clear();
    strList << QString::fromLocal8Bit("序号") << QString::fromLocal8Bit("设备名称") << QString::fromLocal8Bit("设备位置")
            << QString::fromLocal8Bit("设备IP") << QString::fromLocal8Bit("设备版本") << QString::fromLocal8Bit("设备状态")
            << QString::fromLocal8Bit("设备供应商");
    ui->deviceStatusTW->setColumnCount(7);
    ui->deviceStatusTW->setHorizontalHeaderLabels(strList);
    //ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#36648B;}");
    ui->deviceStatusTW->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image:url(:/myimages/images/editGround.png);}");
    ui->deviceStatusTW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->customSecCB->setView(new QListView());
    ui->customeMinuteCB->setView(new QListView());
    ui->cxCB->setView(new QListView());
    ui->comboBox_8->setView(new QListView());

    strList.clear();
    strList << QString::fromLocal8Bit("序号") << QString::fromLocal8Bit("设备名称") << QString::fromLocal8Bit("设备位置")
            << QString::fromLocal8Bit("设备IP") << QString::fromLocal8Bit("硬盘容量") << QString::fromLocal8Bit("硬盘使用量")
            << QString::fromLocal8Bit("硬盘状态");
    ui->ccTW->setColumnCount(7);
    ui->ccTW->setHorizontalHeaderLabels(strList);
    ui->ccTW->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image:url(:/myimages/images/editGround.png);}");
    ui->ccTW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    getCurrInfo(); //獲取當前設備狀態

    //维护更新
    strList.clear();
    strList << QString::fromLocal8Bit("设备名称") << QString::fromLocal8Bit("设备时间");
    ui->tableWidget_4->setColumnCount(2);
    ui->tableWidget_4->setHorizontalHeaderLabels(strList);
    ui->tableWidget_4->horizontalHeader()->setStyleSheet("QHeaderView::section{border-image:url(:/myimages/images/editGround.png);}");
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setRowCount(2);
    ui->tableWidget_4->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    strList.clear();
    strList << "" << "";
    ui->tableWidget_4->setVerticalHeaderLabels(strList);
    ui->tableWidget_4->verticalHeader()->setStyleSheet("QHeaderView::section{border-image:url(:/myimages/images/editGround.png);}");
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget_4->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    for (int i = 0; i < cxList.size(); ++i)
        ui->cxCB->insertItem(i, cxList[i]);
    ui->cxCB->setCurrentText(g_crhtype);

    QRadioButton *pItemRow0Col0 = new QRadioButton(QString::fromLocal8Bit("监控屏校时"), this);
    pItemRow0Col0->setChecked(true);
    QRadioButton *pItemRow1Col0 = new QRadioButton(QString::fromLocal8Bit("手动校时"), this);
    ui->tableWidget_4->setCellWidget(0, 0, pItemRow0Col0);
    ui->tableWidget_4->setCellWidget(1, 0, pItemRow1Col0);

    ui->coachnoCB->setView(new QListView());
    for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
    {
        bool flag = false;
        for (int j = 0; j < ui->coachnoCB->count(); ++j)
        {
            if (QString::number(g_deviceInfo.m_devices[i].coach) == ui->coachnoCB->itemText(j))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ui->coachnoCB->addItem(QString::number(g_deviceInfo.m_devices[i].coach));
    }
    ui->ipcIndesCB->setView(new QListView());
    for (int i = 0; i < g_deviceInfo.deviceCount; ++i)
    {
        bool flag = false;
        for (int j = 0; j < ui->ipcIndesCB->count(); j++)
        {
            if (QString::number(g_deviceInfo.m_devices[i].index) == ui->ipcIndesCB->itemText(j))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
            ui->ipcIndesCB->addItem(QString::number(g_deviceInfo.m_devices[i].index));
    }
    ui->ldCB->setView(new QListView());
    ui->bhCB->setView(new QListView());
    ui->dbCB->setView(new QListView());


//    QTableWidgetItem *pItemRow0Col1 = new QTableWidgetItem(QString::fromLocal8Bit("监控屏校时"));
//    pItemRow0Col1->setTextAlignment(Qt::AlignCenter);
//    pItemRow0Col1->setFlags(pItemRow0Col1->flags() & (~Qt::ItemIsEditable));
//    pItemRow0Col1->setFlags(pItemRow0Col1->flags() & (~Qt::ItemIsSelectable));
//    ui->tableWidget_4->setItem(0, 1, pItemRow0Col1);
//    QTableWidgetItem *pItemRow1Col1 = new QTableWidgetItem(QString::fromLocal8Bit("手动校时"));
//    pItemRow1Col1->setTextAlignment(Qt::AlignCenter);
//    pItemRow1Col1->setFlags(pItemRow0Col1->flags() & (~Qt::ItemIsEditable));
//    pItemRow0Col1->setFlags(pItemRow0Col1->flags() & (~Qt::ItemIsSelectable));
//    ui->tableWidget_4->setItem(1, 1, pItemRow1Col1);
    pMonitorTime = new QDateTimeEdit(this);
    pMonitorTime->setEnabled(false);
    QDateTimeEdit *pAutoTime = new QDateTimeEdit;
    ui->tableWidget_4->setCellWidget(0, 1, pMonitorTime);
    ui->tableWidget_4->setCellWidget(1, 1, pAutoTime);
    pMonitorTime->setDisplayFormat("yyyy/MM/dd HH:mm:ss");
    timer.setInterval(1000);
    timer.start();
    connect(&timer, SIGNAL(timeout()), SLOT(timerOuttime()));
    pAutoTime->setDisplayFormat("yyyy/MM/dd HH:mm:ss");
    pAutoTime->setDate(QDate(2019, 6, 1));
    pAutoTime->setTime(QTime(0, 0, 0));
    qApp->installNativeEventFilter(this);

    //初始化视频控件
    Player_Init((HWND)winId());
    Player_SetLanguage("zh-CN");
	connect(ui->stackedWidget_2, SIGNAL(signalPrepareConnect(int)), this, SLOT(slotPrepareConnect(int)));
	connect(ui->stackedWidget_2, SIGNAL(signalExitFullView()), this, SLOT(slotFullViewEvent()));
	connect(ui->stackedWidget_2, SIGNAL(signalToggleMainSubView()), this, SLOT(slotToggleMainSubView()));
	ui->stackedWidget_2->init(); //初始化视频组件
    ui->stackedWidget_2->startPreview();

}

ContentWidget::~ContentWidget()
{
    Player_Release();
    delete ui;
}

void ContentWidget::slotPrepareConnect(int coach)
{
	qDebug() << "slotPrepareConnect:" << coach;
	moniter->prepare(coach);
}

void ContentWidget::setCC(QString cc)
{
    ui->ccMngLineEdit->setText(cc);
    slotSetTrainNo();
}

void ContentWidget::timerEvent(QTimerEvent *evt)
{
    if (evt->timerId() == m_timerId)
    {
        //全屏显示并清除倒计时
		ui->horizontalLayout_16->setMargin(0);
		ui->widget_2->hide();
        ui->widget_3->hide();
        ui->widget_5->hide();
		killTimer(m_timerId);
    }
    else if (evt->timerId() == m_searchTimer)
    {
        ui->searchBtn->setEnabled(true);
        ui->searchBtn->setStyleSheet("QPushButton#searchBtn{border-image:url(:/myimages/images/pbtnQuery.png);}");
        killTimer(m_searchTimer);
        m_searchTimer = -1;
    }
}

//实时画面还原
void ContentWidget::slotFullViewEvent()
{
	if (m_timerId != 0)
	{
		killTimer(m_timerId);
		m_timerId = 0;
	}
	ui->horizontalLayout_16->setContentsMargins(10, 0, 10, 0);
	ui->widget_2->show();
	ui->widget_3->show();
	ui->widget_5->show();
	m_timerId = startTimer(SCREEN_COUNT_TIMER);
}

//大小画面切换信号触发槽函数，重置全屏计时
void ContentWidget::slotToggleMainSubView()
{
	if (m_timerId != 0)
	{
		killTimer(m_timerId);
		m_timerId = startTimer(SCREEN_COUNT_TIMER);
	}
}

//void ContentWidget::mousePressEvent(QMouseEvent *evt)
//{
//    if (ui->stackedWidget->currentIndex() == 0)
//    {
//		//实时画面还原
//        if (m_timerId != 0)
//        {
//            killTimer(m_timerId);
//            m_timerId = 0;
//        }
//        ui->widget_2->show();
//        ui->widget_3->show();
//        ui->widget_5->show();
//		ui->horizontalLayout_16->setContentsMargins(10, 0, 10, 0);
//        m_timerId = startTimer(SCREEN_COUNT_TIMER);
//    }
//}

#include <Windows.h>
#include <Dbt.h>

bool ContentWidget::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType == WM_DEVICECHANGE)
    {
        qDebug() << "Recv Event " ;
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch(msg->wParam)
        {
            case DBT_DEVICETYPESPECIFIC:
                qDebug() << "DBT_DEVICETYPESPECIFIC " ;
                break;
            case DBT_DEVICEARRIVAL:
                if (lpdb -> dbch_devicetype == DBT_DEVTYP_VOLUME)
                {
                    PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                    if (lpdbv -> dbcv_flags == 0)
                    {
                        // 插入U盘，此处可以做你想做的事
                        // lpdbv->dbcv_unitmask 即盘符标志位，1bit，0为A，1为B，10为C，11为D…以此类推
                        QString USBDisk = QString(this->FirstDriveFromMask(lpdbv->dbcv_unitmask));
                        qDebug() << "USB_Arrived and The USBDisk is: "<<USBDisk ;
                        m_udiskpath = USBDisk/*+":\\test\\"*/;
                        ui->updateStatTextEdit->clear();
                        ui->updateStatTextEdit->append(QString::fromLocal8Bit("已检测到U盘，请确保U盘中已拷贝待更新的程序和配置文件!"));
                        ui->updateProBtn->setEnabled(true);
                        ui->updateProBtn->setStyleSheet("QPushButton#updateProBtn{border-image: url(:/myimages/images/pbtnstartupdate.png);}");
                        ui->updateThenRestart->setEnabled(false);
                    }
                }
                qDebug() << "DBT_DEVICEARRIVAL" ;
                break;
            case DBT_DEVICEREMOVECOMPLETE:
                if (lpdb -> dbch_devicetype == DBT_DEVTYP_VOLUME)
                {
                    PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                    if (lpdbv -> dbcv_flags == 0)
                    {
                        qDebug() << "USB_delete";
                        m_udiskpath.clear();
                        ui->updateStatTextEdit->clear();
                        ui->updateStatTextEdit->setText(QString::fromLocal8Bit("请重新插入U盘!"));
                        ui->updateProBtn->setEnabled(false);
                        ui->updateProBtn->setStyleSheet("QPushButton#updateProBtn{border-image: url(:/myimages/images/pbtnstartupdateFalse.png);}");
                        ui->updateThenRestart->setEnabled(false);
                    }
                }
                qDebug() << "DBT_DEVICEREMOVECOMPLETE" ;
                break;
        }
    }
    return false;
}

void ContentWidget::initSlots()
{
    //主界面上部导航按钮
    connect(ui->monitorBtn, SIGNAL(clicked()), this, SLOT(slotMonitorBtnClicked()));
    connect(ui->videoBtn, SIGNAL(clicked()), this, SLOT(slotVideoBtnClicked()));
    connect(ui->inteliBtn, SIGNAL(clicked()), this, SLOT(slotInteliBtnClicked()));
    connect(ui->devmngBtn, SIGNAL(clicked()), this, SLOT(slotDevMngBtnClicked()));
    connect(ui->maintainBtn, SIGNAL(clicked()), this, SLOT(slotMaintainBtnClicked()));

    //云台控制
    initPtzControl();

    //预置点
    initPreset();

    connect(ui->cameraSwitch, SIGNAL(clicked()), this, SLOT(slotCameraSwitchBtnClicked()));
    connect(ui->cameraLight, SIGNAL(clicked()), this, SLOT(slotCameraLightBtnClicked()));
    connect(ui->videoPauseBtn, SIGNAL(clicked(bool)), this, SLOT(slotVideoPauseBtnClicked(bool)));
    connect(ui->videoPlayBtn, SIGNAL(clicked(bool)), this, SLOT(slotVideoPlayBtnClicked(bool)));
    connect(ui->stackedWidget_2, SIGNAL(sigVideoPauseBtnClicked(bool)), this, SLOT(slotVideoPauseResult(bool)));

    connect(ui->videoNextBtn, SIGNAL(clicked()), this, SLOT(slotVideoNextBtnClicked()));
    connect(ui->stackedWidget_2, SIGNAL(sigSwitchSunccess(bool)), this, SLOT(slotSwitchSuccess(bool)));
    connect(ui->videoPreBtn, SIGNAL(clicked()), this, SLOT(slotVideoPreBtnClicked()));
    connect(ui->videoAheadBtn, SIGNAL(clicked()), this, SLOT(slotvideoAheadBtnClicked()));
    connect(ui->videoSaveBtn, SIGNAL(clicked()), this, SLOT(slotVideoSaveBtnClicked()));

    //回放
    connect(ui->searchBtn, SIGNAL(clicked()), this, SLOT(slotSearchBtnClicked()));

    //设备管理 车次设置
    connect(ui->ccmngBtn, SIGNAL(clicked()), this, SLOT(slotCCMNGBtnClicked()));

    //维护更新
    connect(ui->tenSecR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp1Clicked(bool)));
    connect(ui->twentySecR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp1Clicked(bool)));
    connect(ui->thirtySecR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp1Clicked(bool)));
    connect(ui->customSecR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp1Clicked(bool)));
    connect(ui->fiveMinuteR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp2Clicked(bool)));
    connect(ui->tenMinuteR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp2Clicked(bool)));
    connect(ui->fifteenMinuteR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp2Clicked(bool)));
    connect(ui->custimeMinuteR, SIGNAL(clicked(bool)), this, SLOT(slotRadioBtnGrp2Clicked(bool)));
    connect(ui->cxTypeBtn, SIGNAL(clicked()), this, SLOT(slotCxTypeBtnClicked()));
    connect(ui->timeAdjustBtn, SIGNAL(clicked()), this, SLOT(slotTimeAdjustBtnClicked()));
    connect(ui->paramSetBtn, SIGNAL(clicked()), this, SLOT(slotParamBtnClicked()));
    connect(ui->updateProBtn, SIGNAL(clicked()), this, SLOT(slotUpdateProBtnClicked()));
    connect(ui->updateThenRestart, SIGNAL(clicked()), this, SLOT(slotUpdateThenRestart()));


    //底部注销报警按钮处理
    connect(ui->exitBtn, SIGNAL(clicked()), this, SLOT(slotExitBtnClicked()));
}

void ContentWidget::initPtzControl()
{
    QSignalMapper *signalMap = new QSignalMapper;
    {
        connect(ui->upBtn, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->leftBtn, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->rightBtn, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->downBtn, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->videoSmall, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->videoBig, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->videoZoomIn, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->videoZoomOut, SIGNAL(pressed()), signalMap, SLOT(map()));
        connect(ui->upBtn, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->leftBtn, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->rightBtn, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->downBtn, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->videoSmall, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->videoBig, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->videoZoomIn, SIGNAL(released()), this, SLOT(slotPtzStop()));
        connect(ui->videoZoomOut, SIGNAL(released()), this, SLOT(slotPtzStop()));
        signalMap->setMapping(ui->upBtn, QString::number(PTZ_UP, 10));
        signalMap->setMapping(ui->leftBtn, QString::number(PTZ_LEFT, 10));
        signalMap->setMapping(ui->rightBtn, QString::number(PTZ_RIGHT, 10));
        signalMap->setMapping(ui->downBtn, QString::number(PTZ_DOWN, 10));
        signalMap->setMapping(ui->videoSmall, QString::number(ZOOM_NEAR, 10));
        signalMap->setMapping(ui->videoBig, QString::number(ZOOM_FAR, 10));
        signalMap->setMapping(ui->videoZoomIn, QString::number(FOCUS_NEAR, 10));
        signalMap->setMapping(ui->videoZoomOut, QString::number(FOCUS_FAR, 10));
    }
    connect(signalMap, SIGNAL(mapped(QString)), this, SLOT(slotptzStart(QString)));
}

void ContentWidget::initPreset()
{
	m_pbtCameraPos[0] = ui->oneBtn;
	m_pbtCameraPos[1] = ui->twoBtn;
	m_pbtCameraPos[2] = ui->threeBtn;
	m_pbtCameraPos[3] = ui->fourBtn;
	m_pbtCameraPos[4] = ui->fiveBtn;
	m_pbtCameraPos[5] = ui->sixBtn;
	m_pbtCameraPos[6] = ui->sevenBtn;
	m_pbtCameraPos[7] = ui->eightBtn;
	m_pbtCameraPos[m_iCameraPos - 1]->setProperty("CurrCameraPos", QString::number(m_iCameraPos));
	m_pbtCameraPos[m_iCameraPos - 1]->style()->unpolish(m_pbtCameraPos[m_iCameraPos - 1]);
	m_pbtCameraPos[m_iCameraPos - 1]->style()->polish(m_pbtCameraPos[m_iCameraPos - 1]);
	m_pbtCameraPos[m_iCameraPos - 1]->update();

	QSignalMapper *signalMap = new QSignalMapper;
	for (int i = 0; i < 8; i++)
	{
		connect(m_pbtCameraPos[i], SIGNAL(clicked()), signalMap, SLOT(map()));
		signalMap->setMapping(m_pbtCameraPos[i], i + 1);
	}
	connect(signalMap, SIGNAL(mapped(int)), this, SLOT(slotCameraPosSet(int)));
	connect(ui->viedoSetBtn, SIGNAL(clicked()), this, SLOT(slotVideoSetBtnClicked()));
    connect(ui->videoGetBtn, SIGNAL(clicked()), this, SLOT(slotVideoGetBtnClicked()));
}

void ContentWidget::getCurrInfo()
{
    m_nvr_status_cnt = 0;
    while (ui->deviceStatusTW->rowCount() > 0)
        ui->deviceStatusTW->removeRow(0);
    ui->deviceStatusTW->setRowCount(0);
    while (ui->ccTW->rowCount() > 0)
        ui->ccTW->removeRow(0);
    ui->ccTW->setRowCount(0);

    QByteArray ba;

    ba[0]=0xff;
    ba[1]=0x07;
    ba[2]=0;
    ba[3]=0;
    ba[4]=MoniterClient::crc_sum((unsigned char *)ba.data(),4);
    for(int i=0; i<MAX_DEVICE_CNT; i++)
    {
        if(g_deviceInfo.m_devices[i].type == DEVICE_NVR)
            Moniter->sendCmd(g_deviceInfo.m_devices[i].coach, ba);
    }

}

char ContentWidget::FirstDriveFromMask(ULONG unitmask)
{
    char i;

    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');

}

void ContentWidget::slotMonitorBtnClicked()
{
    if (ui->stackedWidget->currentIndex() != 0)
    {
        if (m_timerId != 0)
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
        ui->stackedWidget->setCurrentIndex(0);
        m_timerId = startTimer(SCREEN_COUNT_TIMER); //重新计时
        ui->alarmBtn->setEnabled(true);
        ui->alarmBtn->setStyleSheet("QPushButton#alarmBtn{border-image:url(:/myimages/images/pbtnAlarm.png)}");
    }
}

void ContentWidget::slotVideoBtnClicked()
{
    if (ui->stackedWidget->currentIndex() != 1)
    {
        if (m_timerId != 0)
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
        ui->stackedWidget->setCurrentIndex(1);
        ui->alarmBtn->setEnabled(false);
        ui->alarmBtn->setStyleSheet("QPushButton#alarmBtn{border-image:url(:/myimages/images/pbtnAlarmFalse.png)}");

    }
}

void ContentWidget::slotInteliBtnClicked()
{
    //该函数需先判断按钮状态 若未使能，则不执行任何操作
	return;
    if (ui->stackedWidget->currentIndex() != 2)
    {
        if (m_timerId != 0)
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
        ui->alarmBtn->setEnabled(false);
        ui->alarmBtn->setStyleSheet("QPushButton#alarmBtn{border-image:url(:/myimages/images/pbtnAlarmFalse.png)}");
    }
}

void ContentWidget::slotDevMngBtnClicked()
{
    if (ui->stackedWidget->currentIndex() != 3)
    {
        if (m_timerId != 0)
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
        ui->stackedWidget->setCurrentIndex(3);
        ui->alarmBtn->setEnabled(false);
        ui->alarmBtn->setStyleSheet("QPushButton#alarmBtn{border-image:url(:/myimages/images/pbtnAlarmFalse.png)}");

    }
}

void ContentWidget::slotMaintainBtnClicked()
{
    if (ui->stackedWidget->currentIndex() != 4)
    {
        if (m_timerId != 0)
        {
            killTimer(m_timerId);
            m_timerId = 0;
        }
        LoginWidget *pLogin = new LoginWidget(nullptr, 2, this);
        pLogin->showMaximized();
        ui->alarmBtn->setEnabled(false);
        ui->alarmBtn->setStyleSheet("QPushButton#alarmBtn{border-image:url(:/myimages/images/pbtnAlarmFalse.png)}");
    }
}

void ContentWidget::slotptzStart(QString itemIndex)
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }

    int index;
    bool ok;

    index = itemIndex.toInt(&ok, 10);
    QByteArray ba;
    ba[0]=PVMS_PROTOCOL_HEADER_SC;
    ba[1]=PVMS_PROTOCOL_PTZ;
    ba[2]=0;//
    ba[3]=3;//
    ba[4]=index;//
    ba[5]=PTZ_START;//
    ba[6]= m_currindex;
    ba[7] =MoniterClient::crc_sum((unsigned char *)ba.data(),7);
    Moniter->sendCmd(m_currcoach, ba);
    m_lastCmd = index;
    //Preset_timeout = 0;
    //emit signalTestsignal(ba);

}

void ContentWidget::slotPtzStop()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    QByteArray ba;
    ba[0]=PVMS_PROTOCOL_HEADER_SC;
    ba[1]=PVMS_PROTOCOL_PTZ;
    ba[2]=0;//
    ba[3]=3;//
    ba[4]=m_lastCmd;//
    ba[5]=PTZ_STOP;//
    ba[6]= m_currindex;
    ba[7] =MoniterClient::crc_sum((unsigned char *)ba.data(),7);
    Moniter->sendCmd(m_currcoach, ba);
    //Preset_timeout = 0;
}

void ContentWidget::slotCameraPosSet(int iPos)
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
	m_iCameraPos = iPos;

	for (int i = 0; i < 8; i++)
	{
		m_pbtCameraPos[i]->setProperty("CurrCameraPos", QString::number(iPos));
		m_pbtCameraPos[i]->style()->unpolish(m_pbtCameraPos[i]);
		m_pbtCameraPos[i]->style()->polish(m_pbtCameraPos[i]);
		m_pbtCameraPos[i]->update();
	}
}

void ContentWidget::slotVideoSetBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }

	QByteArray ba;
	ba[0] = PVMS_PROTOCOL_HEADER_SC;
	ba[1] = PVMS_PROTOCOL_PTZ_PRESET;
	//长度
	ba[2] = 0;//
	ba[3] = 3;//
	//数据
	ba[4] = 01;//预置点设置01，预置点调用02
	ba[5] = m_iCameraPos;//预置点编号
	ba[6] = m_currindex;//受电弓摄像机位置号
	ba[7] = MoniterClient::crc_sum((unsigned char *)ba.data(), 7);
	Moniter->sendCmd(m_currcoach, ba);
}

void ContentWidget::slotVideoGetBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }

	QByteArray ba;
	ba[0] = PVMS_PROTOCOL_HEADER_SC;
	ba[1] = PVMS_PROTOCOL_PTZ_PRESET;
	//长度
	ba[2] = 0;//
	ba[3] = 3;//
	//数据
	ba[4] = 02;//预置点设置01，预置点调用02
	ba[5] = m_iCameraPos;//预置点编号
	ba[6] = m_currindex;//受电弓摄像机位置号
	ba[7] = MoniterClient::crc_sum((unsigned char *)ba.data(), 7);
	Moniter->sendCmd(m_currcoach, ba);
}

void ContentWidget::slotCameraSwitchBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    m_ipcStatus = (m_ipcStatus==1) ? 2 : 1; //切换摄像头状态
    QByteArray ba;
    ba[0]=PVMS_PROTOCOL_HEADER_SC;
    ba[1]=PVMS_PROTOCOL_IPC_CTL;
    ba[2]=0;//
    ba[3]=2;//
    ba[4]=m_ipcStatus;//
    ba[5]=m_currindex;
    ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
    Moniter->sendCmd(m_currcoach, ba);
    if(m_ipcStatus == 1)
    {
        ui->cameraSwitch->setStyleSheet("QPushButton#cameraSwitch{border-image:url(:/myimages/images/pbtnIPCclose.png);}");
    }
    else if (m_ipcStatus == 2)
    {
        ui->cameraSwitch->setStyleSheet("QPushButton#cameraSwitch{border-image:url(:/myimages/images/pbtnIPCopen.png);}");
    }

}

void ContentWidget::slotCameraLightBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    QByteArray ba;
    m_lightStatus = (m_lightStatus==1)?2:1;
    ba[0]=PVMS_PROTOCOL_HEADER_SC;
    ba[1]=PVMS_PROTOCOL_LIGHT_CTL;
    ba[2]=0;//
    ba[3]=2;//
    ba[4]=m_lightStatus;//
    ba[5]=m_currindex;
    ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
    Moniter->sendCmd(m_currcoach, ba);
    if(m_lightStatus == 1)
        ui->cameraLight->setStyleSheet("QPushButton#cameraLight{border-image:url(:/myimages/images/pbtnLightClose.png);}");
    else
        ui->cameraLight->setStyleSheet("QPushButton#cameraLight{border-image:url(:/myimages/images/pbtnLightOpen.png);}");

}


void ContentWidget::slotRadioBtnGrp1Clicked(bool bFlag)
{
    if (ui->tenSecR->isChecked()
            || ui->twentySecR->isChecked()
            || ui->thirtySecR->isChecked())
    {
		if (ui->tenSecR->isChecked())
            //SCREEN_COUNT_TIMER = 10 * 1000; //10s
			ui->stackedWidget_2->SetPollingTime(10);
		else if (ui->twentySecR->isChecked())
            //SCREEN_COUNT_TIMER = 20 * 1000; //20s
			ui->stackedWidget_2->SetPollingTime(20);
		else if (ui->thirtySecR->isChecked())
            //SCREEN_COUNT_TIMER = 30 * 1000; //30s
			ui->stackedWidget_2->SetPollingTime(30);
		ui->customSecCB->setEnabled(false);
    }
    else if (ui->customSecR->isChecked())
    {
        ui->customSecCB->setEnabled(true);
    }
}

void ContentWidget::slotRadioBtnGrp2Clicked(bool bFlag)
{
    if (ui->fiveMinuteR->isChecked()
            || ui->tenMinuteR->isChecked()
            || ui->fifteenMinuteR->isChecked())
    {
        ui->customeMinuteCB->setEnabled(false);
        if (ui->fiveMinuteR->isChecked())
            PRESET_POINT_RETURN = 5;
        else if (ui->tenMinuteR->isChecked())
            PRESET_POINT_RETURN = 10;
        else if (ui->fifteenMinuteR->isChecked())
            PRESET_POINT_RETURN = 15;
    }
    else if (ui->custimeMinuteR->isChecked())
    {
        ui->customeMinuteCB->setEnabled(true);
    }
}

#include <QFile>
void ContentWidget::slotCxTypeBtnClicked()
{
    if (ui->cxCB->currentText() != "")
    {
        QFile file("railway.cfg");
        QDomDocument doc;
        QString errorStr;
        int errorLine;
        int errorColumn;
        int index = 0;

		if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            qDebug()<<"open config file "<< "railway.cfg" <<"failed"<< ": " << (file.errorString());
            return;
        }

        if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
        {
            qDebug()<< "Error: Parse error at line " << errorLine << ", "<< "column " << errorColumn << ": " << (errorStr);
            file.close();
            return;
        }

        QDomElement root = doc.documentElement();
        if (root.tagName() != "RAILWAYCFG")
        {
            file.close();
            return;
        }

        QDomNode child = root.firstChild();
        while(!child.isNull())
        {
            if(child.toElement().tagName()=="Type")
            {
                QString cxType = ui->cxCB->currentText();
                QDomElement newnode = doc.createElement("Type");
                QDomText text = doc.createTextNode(cxType);
                newnode.appendChild(text);
                root.replaceChild(newnode,child);
                break;
            }
            child = child.nextSibling();
        }
        file.close();

		if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text))
        {
            qDebug()<<"open config file "<< "railway.cfg" <<"failed"<< ": " << (file.errorString());
            return;
        }

		QTextStream out(&file);
        QString xml = doc.toString();
        out << xml;
        file.close();

        qApp->exit(RETCODE_RESTART);
    }
}

void ContentWidget::timerOuttime()
{
    QDateTime time = QDateTime::currentDateTime();
    pMonitorTime->setDateTime(time);
}

#include <QMessageBox>
#include <QProcess>
#include <Windows.h>
void ContentWidget::slotTimeAdjustBtnClicked()
{
    QDateTime datetime;
    QString time;
    if (((QRadioButton *)(ui->tableWidget_4->cellWidget(0, 0)))->isChecked())
    {
        datetime = ((QDateTimeEdit*)ui->tableWidget_4->cellWidget(0, 1))->dateTime();
    }
    else if (((QRadioButton *)(ui->tableWidget_4->cellWidget(1, 0)))->isChecked())
    {
        datetime = ((QDateTimeEdit*)ui->tableWidget_4->cellWidget(1, 1))->dateTime();
        //QDateTime datetime = QDateTime::currentDateTime();
    }
    time = datetime.toString("yyyy-MM-dd hh:mm:ss");
    QString s1 = time.split(" ").at(0);
    QString s2 = time.split(" ").at(1);

    QByteArray ba;
    unsigned short year;
    unsigned char mon;
    unsigned char day;
    unsigned char h;
    unsigned char m;
    unsigned char s;
    ba[0]=0xff;
    ba[1]=0x06;
    ba[2]=0;//
    ba[3]=0x07;//
    year=s1.section('-', 0, 0).toInt();
    mon =s1.section('-', 1, 1).toInt();
    day =s1.section('-', 2, 2).toInt();
    h=s2.section(':', 0, 0).toInt();
    m =s2.section(':', 1, 1).toInt();
    s =s2.section(':', 2, 2).toInt();
    ba[4]=(unsigned char)(year>>8);
    ba[5]=(unsigned char)year;
    ba[6] = (unsigned char)mon;
    ba[7] = (unsigned char)day;
    ba[8] = (unsigned char)h;
    ba[9] = (unsigned char)m;
    ba[10] = (unsigned char)s;
    ba[11] =MoniterClient::crc_sum((unsigned char *)ba.data(),11);
    for(int i=0; i<MAX_DEVICE_CNT; i++)
    {
        if(g_deviceInfo.m_devices[i].type==DEVICE_NVR)
            Moniter->sendCmd(g_deviceInfo.m_devices[i].coach, ba);
    }
}

void ContentWidget::slotParamBtnClicked()
{
    QByteArray ba;
    ba[0]=0xff;
    ba[1]=0x02;
    ba[2]=0;//
    ba[3]=0x04;//
    ba[4]=ui->ldCB->currentText().toInt();
    ba[5]=ui->bhCB->currentText().toInt();
    ba[6]=ui->dbCB->currentText().toInt();
    ba[7]=0;
    ba[8] =MoniterClient::crc_sum((unsigned char *)ba.data(),8);
    int coach = ui->coachnoCB->currentText().toInt();
    Moniter->sendCmd(coach, ba);
}

void ContentWidget::slotUpdateProBtnClicked()
{
    bool bok = updateFile(m_udiskpath);
    if(bok)
    {
        ui->updateStatTextEdit->append(QString(tr("Update succeed, click \"Restart\" to continue.")));
        ui->updateThenRestart->setEnabled(true);
        ui->updateThenRestart->setStyleSheet("QPushButton#updateThenRestart{border-image: url(:/myimages/images/pbtnrestart.png);}");
    }
}

//重启应用
void ContentWidget::slotUpdateThenRestart()
{
    qApp->exit(RETCODE_RESTART); //程序更新后单击重启按钮重启应用
}

#include <QDir>
#include <QFileInfo>
bool ContentWidget::updateFile(QString path)
{
    QDir dir(path);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            QString suffix = mfi.suffix();
            if(suffix=="dll"||suffix=="exe"||suffix=="lib"||suffix=="ini")
            {
                QString localpath = qApp->applicationDirPath();
                QString localfile = localpath+"/"+mfi.fileName();
                QString sourcefile = mfi.absoluteFilePath();
                bool _ok = QFile::remove(localfile);
                bool ok = QFile::copy(sourcefile, localfile);
                if(ok)
                {
                    ui->updateStatTextEdit->append(QString(tr("Copy file:"))+localfile);
                }
                else
                    return false;
            }
        }
        else
        {
            if(mfi.fileName()=="." || mfi.fileName() == "..")
                continue;
            updateFile(mfi.absoluteFilePath());
        }
    }
}

#include <QCheckBox>
void ContentWidget::insertRow(QTableWidget *tableWidget, QStringList strList)
{
    tableWidget->insertRow(tableWidget->rowCount());
    int beginColumn = 0;
    //if(m_hasCheckBox)
    {
        QCheckBox *checkBox = new QCheckBox;
        //checkBox->setFixedSize(22,22);
        checkBox->setObjectName("checkBox");
        QWidget *widget = new QWidget(this);
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->setMargin(0);
        layout->addSpacing(26);
        layout->addWidget(checkBox);

        checkBox->setProperty("CRH_Combobox", true);
        //checkBox->setStyleSheet("QCheckBox::indicator{pandding-left:10px;}");
        checkBox->setCheckState(Qt::Unchecked);
        checkBox->installEventFilter(this);
        tableWidget->setCellWidget(tableWidget->rowCount(), beginColumn, widget);
        ++beginColumn;

        //connect(checkBox, SIGNAL(stateChanged(int)),
            //this, SLOT(slotCheckBoxStateChanged(int)));
    }

    foreach(QString value, strList)
    {
        QTableWidgetItem *item = new QTableWidgetItem(value);
        item->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(tableWidget->rowCount(), beginColumn, item);
        ++beginColumn;
    }
}

void ContentWidget::deleteAllRows(QTableWidget *tableWidget)
{
    while (tableWidget->rowCount() > 0)
        tableWidget->removeRow(0);
    tableWidget->setRowCount(0);
}

void ContentWidget::slotCCMNGBtnClicked()
{
    LoginWidget *pLogin = new LoginWidget(nullptr, 1, this);
    if (ui->ccmngBtn->isEnabled())
    {
        pLogin->showMaximized();
    }
    hide();
}

void ContentWidget::slotExitBtnClicked()
{
    close();
}

void ContentWidget::slotVideoPauseBtnClicked(bool bPause)
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    if (ui->videoPauseBtn->isEnabled())
    {
        ui->stackedWidget_2->slotVideoPauseBtnClicked(true);
    }
}

void ContentWidget::slotVideoPlayBtnClicked(bool bFlag)
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    if (ui->videoPlayBtn->isEnabled())
    {
        ui->stackedWidget_2->slotVideoPlayBtnClicked(true);
    }
}

void ContentWidget::slotVideoPauseResult(bool bFlag)
{
    if (bFlag)
    {
        ui->videoPauseBtn->setEnabled(false);
        ui->videoPauseBtn->setStyleSheet("QPushButton#videoPauseBtn{border-image:url(:/myimages/images/pbtnPauseFalse.png);}");
        ui->videoPlayBtn->setEnabled(true);
        ui->videoPlayBtn->setStyleSheet("QPushButton#videoPlayBtn{border-image:url(:/myimages/images/pbtnPlay.png);}");
    }
    else
    {
        ui->videoPauseBtn->setEnabled(true);
        ui->videoPauseBtn->setStyleSheet("QPushButton#videoPauseBtn{border-image:url(:/myimages/images/pbtnPause.png);}");
        ui->videoPlayBtn->setEnabled(false);
        ui->videoPlayBtn->setStyleSheet("QPushButton#videoPlayBtn{border-image:url(:/myimages/images/pbtnPlayFalse.png);}");
    }
}


//小画面位置切换
void ContentWidget::slotVideoNextBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
	ui->stackedWidget_2->ToggleSubViewPos();
}

void ContentWidget::slotSwitchSuccess(bool bFlag)
{

}

void ContentWidget::slotVideoPreBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    ui->stackedWidget_2->slotVideoPreBtnClicked();
}

void ContentWidget::slotvideoAheadBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    ui->stackedWidget_2->slotvideoAheadBtnClicked();
}

void ContentWidget::slotVideoSaveBtnClicked()
{
    if (m_timerId != 0)
    {
        killTimer(m_timerId);
        m_timerId = startTimer(SCREEN_COUNT_TIMER);
    }
    QByteArray ba;
    ba[0]=0xff;
    ba[1]=0x45;
    ba[2]=0;
    ba[3]=2;
    for(int i=0; i<MAX_DEVICE_CNT; i++)
    {
        //if(m_devices[i].type == DEVICE_NVR)
        {
            ba[4]=g_deviceInfo.m_devices[i].coach;
            ba[5]=g_deviceInfo.m_devices[i].index;
            ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
            Moniter->sendCmd(g_deviceInfo.m_devices[i].coach, ba);
        }
    }
//    ui->->setEnabled(false);
    //    savenowtimeout = 0;
}

void ContentWidget::slotSearchBtnClicked()
{
    //ui->searchBt->setText(QObject::tr("Please Wait"));
    m_searchTimer = startTimer(10000);
    ui->searchBtn->setEnabled(false);
    ui->searchBtn->setStyleSheet("QPushButton{border-image:url(:/myimages/images/pbtnQueryFalse.png);}");
    deleteAllRows(ui->videoFileWidget);
    m_currentVideoIndex = -1;
    QStringList para;
    QString para_date_s;
    QString para_time_s;
    QString para_date_e;
    QString para_time_e;
    int para_coach;
    int para_ipcid;
    para<<ui->coachListCB->currentText();
    para<<ui->ipcIndexCB->currentText();
    para<<ui->startdateEdit->date().toString("yyyy/MM/dd");
    para<<ui->starttimeEdit->text();
    para<<ui->enddateEdit->date().toString("yyyy/MM/dd");
    para<<ui->endtimeEdit->text();
    for(int i=0; i<para.length();i++)
    {
        if(i==0)
            if(para[i].toInt()<1||para[i].toInt()>16)
				//;goto invalid;
        if(i==1)
            if(para[i].toInt()<1||para[i].toInt()>6)
				//;goto invalid;
        if(para[i].length()<=0)
            goto invalid;
    }

    para_coach=para[0].toInt();
    para_ipcid = para[1].toInt();
    para_date_s = para[2];
    para_time_s = para[3];
    para_date_e = para[4];
    para_time_e = para[5];
    {
        qDebug()<<para_coach<<","<<para_ipcid<<", "<<para_date_s<<","<<para_time_s<<","<<para_date_e<<","<<para_time_e;
        QByteArray ba;
        unsigned short year;
        unsigned char mon;
        unsigned char day;
        unsigned char h;
        unsigned char m;
        unsigned char s;
        ba[0]=PVMS_PROTOCOL_HEADER_SC;
        ba[1]=PVMS_PROTOCOL_REMOTE_SEACH_FILE;
        ba[2]=0;//
        ba[3]=0x10;//
        QStringList date_start_list = para_date_s.split("/");
        year=date_start_list[0].toShort();
        mon =date_start_list[1].toInt();
        day =date_start_list[2].toInt();
        QStringList time_start_list = para_time_s.split(":");
        h=time_start_list[0].toInt();
        m =time_start_list[1].toInt();
        s =time_start_list[2].toInt();
        ba[4]=(unsigned char)(year>>8);
        ba[5]=(unsigned char)year;
        ba[6] = (unsigned char)mon;
        ba[7] = (unsigned char)day;
        ba[8] = (unsigned char)h;
        ba[9] = (unsigned char)m;
        ba[10] = (unsigned char)s;
        date_start_list = para_date_e.split("/");
        year=date_start_list[0].toShort();
        mon =date_start_list[1].toInt();
        day =date_start_list[2].toInt();
        time_start_list = para_time_e.split(":");
        h=time_start_list[0].toInt();
        m =time_start_list[1].toInt();
        s =time_start_list[2].toInt();
        ba[11]=(unsigned char)(year>>8);
        ba[12]=(unsigned char)year;
        ba[13] = (unsigned char)mon;
        ba[14] = (unsigned char)day;
        ba[15] = (unsigned char)h;
        ba[16] = (unsigned char)m;
        ba[17] = (unsigned char)s;
        ba[18] = (unsigned char)para_coach;
        ba[19] = (unsigned char)para_ipcid;
        ba[20] =MoniterClient::crc_sum((unsigned char *)ba.data(),20);
        Moniter->sendCmd(para_coach, ba);
        //WaitDialog::_instance().showWaitDialog(QObject::tr("Searching Video Files..."));
    }
    return;
invalid:
    ui->searchBtn->setEnabled(true);
    ui->searchBtn->setStyleSheet("QPushButton#searchBtn{border-image: url(:/myimages/images/pbtnQuery.png);}");

}

void ContentWidget::slotHandleSearch(QString s)
{
    //WaitDialog::_instance().hideWaitDialog();
    QStringList records;
    QStringList record;
    QString fullName;
    bool temp;
    int rowcnt = ui->videoFileWidget->rowCount();

    records = s.split(".MP4");
    for(int i=0; i < records.length()-1; i++)
    {
        record.clear();
        fullName = records[i]+".MP4";
        record << QString::number(rowcnt+1+i) << fullName.section('/', -1);
        insertRow(ui->videoFileWidget, record);
#if 0
        if(fullName.contains("tmp",Qt::CaseSensitive))
        {
            //设置该行文件名列字符颜色为红色
            QColor colorRed("red");
            rowcnt = ui->tableWidget->rowCount();
            QTableWidgetItem *item = ui->tableWidget->item(rowcnt-1,2);
            item->setTextColor(colorRed);
            ui->tableWidget->setItem(rowcnt-1,2,item);
        }
#else
#if 1
        if (fullName.contains("tmp"))
        {
            //ui->tableWidget->item(i, 2)->setForeground(Qt::red);
            ui->videoFileWidget->item(rowcnt+i, 2)->setText("");
            QLabel *lable = new QLabel;
            lable->setObjectName("lable_item");
            QWidget *widget = new QWidget(this);
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->setMargin(0);
            layout->addSpacing(20);
            layout->addWidget(lable);
            lable->setStyleSheet("font-family:microsoft yahei; font-size:14px; height:40px; color:red;");
            lable->setAlignment(Qt::AlignCenter);
            lable->setText(fullName.section('/', -1));
            ui->videoFileWidget->setCellWidget(rowcnt+i, 2, widget);
        }
#endif
#endif
    }
    if (m_searchTimer != -1)
    {
        killTimer(m_searchTimer);
        m_searchTimer = -1;
    }
    ui->searchBtn->setEnabled(true);
    ui->searchBtn->setStyleSheet("QPushButton#searchBtn{border-image:url(:/myimages/images/pbtnQuery.png);}");

}

void ContentWidget::slotCurrInfosNVR(QByteArray &ba)
{
    QByteArray sendba;
    char str[100];
    QStringList stringList, stringList2;
    {
        int i;

        for(i=0;i<ba.size();i++)
            str[i] = ba[i];
    }
    m_nvr_status_cnt++;
    stringList.append(QString::number(ui->deviceStatusTW->rowCount()+1));
    int coach = ba[0];
    switch(ba[1])
    {
    case 0x01:
        stringList.append(QObject::tr("CRH Network Video Recoder"));
        break;
    case 0x02:
        stringList.append(QObject::tr("Intelligent alarm host"));
        break;
    default:
        stringList.append(QObject::tr("Unknow device"));
        break;
    }
    stringList << (QObject::tr("%1coach").arg(coach));
    stringList.append(QString("192.168.%1.81").arg(100+coach));
    //stringList.append(QString::number((unsigned short)(ba[12]<<8)+(unsigned char)ba[13],10));
    {
        unsigned short version = (unsigned short)(ba[12]<<8)+(unsigned char)ba[13];
        stringList << (QString("V%1.%2.%3").arg(version/100).arg((version%100)/10).arg((version%100)%10));
    }
    stringList.append(QObject::tr("Nomal Online"));
    stringList.append(ba.mid(2,9));
    qDebug()<<stringList;
    insertRow(ui->deviceStatusTW, stringList);

    stringList.clear();
    stringList.append(QString::number(ui->ccTW->rowCount()+1));
    switch(ba[1])
    {
    case 0x01:
        stringList.append(QObject::tr("CRH Network Video Recoder"));
        break;
    case 0x02:
        stringList.append(QObject::tr("Intelligent alarm host"));
        break;
    default:
        stringList.append(QObject::tr("Unknow device"));
        break;
    }
    stringList << (QObject::tr("%1coach").arg(coach));
    int diskSize;
    int diskUsed;
    diskSize = ((unsigned short)(ba[14]<<8))+(unsigned char)ba[15];
    diskUsed = ((unsigned short)(ba[16]<<8))+(unsigned char)ba[17];
    stringList.append(QString("192.168.%1.81").arg(100+coach));
    stringList.append(QString::number(diskSize,10)+"G");
    stringList.append(QString::number(diskUsed,10)+"G");
    if(diskSize>0)
        stringList.append(QObject::tr("Nomal Online"));
    else
        stringList.append(QObject::tr("NotFound"));
    //stringList.append(ba.mid(2,10));
    qDebug()<<stringList;
    insertRow(ui->ccTW, stringList);

    QByteArray bsent;

    bsent[0]=0xff;
    bsent[1]=0x08;
    bsent[2]=0;
    bsent[3]=0;
    bsent[4]=MoniterClient::crc_sum((unsigned char *)bsent.data(),4);
    for(int i=0; i<MAX_DEVICE_CNT; i++)
    {
        if(g_deviceInfo.m_devices[i].type==DEVICE_NVR)
            Moniter->sendCmd(m_devices[i].coach, bsent);
    }

}

void ContentWidget::slotCurrInfosIPC(QByteArray &ba)
{
    QByteArray sendba;
    QString s, s1;

    QStringList stringList;
    /*
    unsigned char str[200]={0};
    {
        int i;

        for(i=0;i<ba.size();i++)
            str[i] = ba[i];
    }*/
    int coach = ba[0];
    int ipcid = ba[1];
    if(ipcid<0||ipcid>11)return;
    //stringList << (QString::number(ipcid,10));
    stringList << (QString::number(ui->deviceStatusTW->rowCount()+1));
    switch(ba[3])
    {
    case 0x01:
        stringList << (QObject::tr("Dome Network Camera"));
        return;
        break;
    case 0x02:
        stringList << (QObject::tr("Panoramic camera"));
        return;
        break;
    case 0x03:
        stringList << (QObject::tr("Pantograph camera"));
        break;
    default:
        stringList << (QObject::tr("Other camera"));
        break;
    }
    stringList << (QObject::tr("%1coach%2site").arg(coach).arg(ipcid));

    if(ipcid >= 8)
        stringList << (QString("192.168.%1.%2").arg(100+coach).arg(200+ipcid-8));
    else
        stringList << (QString("192.168.%1.%2").arg(100+coach).arg(70+ipcid));
    {
        unsigned short version = (unsigned short)(ba[14]<<8)+(unsigned char)ba[15];
        stringList << (QString("V%1.%2.%3").arg(version/100).arg((version%100)/10).arg((version%100)%10));
    }
    //stringList << (QString::number((unsigned short)(ba[14]<<8)+(unsigned char)ba[15],10));

    switch(ba[2])
    {
    case 0x01:
        stringList << (QObject::tr("Normal Online"));
        break;
    case 0x00:
        stringList << (QObject::tr("Error Offline"));
        break;
    default:
        stringList << (QObject::tr("Error Offline"));
        break;
    }
    stringList << (ba.mid(4,10));
    qDebug()<< stringList;

    for(int i = 0; i < ui->deviceStatusTW->rowCount(); i++)
    {
        QString str = ui->deviceStatusTW->item(i,3)->text();
        if(stringList.contains(str))
        {//有重复项（设备类型相同且IP地址相同）不再添加直接退出
            return;
        }
        /*else
        {
            qDebug()<<stringList;
            qDebug()<<stringList.at(3);
            qDebug()<<str;
        }*/
    }
    insertRow(ui->deviceStatusTW, stringList);
}

void ContentWidget::slotSetTrainNo()
{
    QString trainNoStr = ui->ccMngLineEdit->text();
    if(trainNoStr.isEmpty())
        return;

    QByteArray block;
    char *temp;
    char trainNo[11];
    char *tmp;
    QByteArray ba = trainNoStr.toLatin1();
    tmp = ba.data();
    memcpy(trainNo, tmp, 11);

    if(memcmp(trainNo, m_pis_info.trainNo, sizeof(trainNo)))
    {
        int i,j,m;
        memcpy(m_pis_info.trainNo, trainNo, sizeof(trainNo));
        //发送视频叠加信息给NVR
        // ...
        for(j=0;j<MAX_DEVICE_CNT;j++)
        {
            if(m_devices[j].type==DEVICE_NVR)
            {
                for(m=0;m<2;m++)
                {
                    block[0] = PVMS_PROTOCOL_HEADER_SC;
                    block[1] = PVMS_PROTOCOL_OVERLAY_OSD;
                    block[2] = 0;
                    block[3] = 50;
                    //发送视频叠加信息给NVR
                    block[4] = m_pis_info.year>>8;
                    block[5] = m_pis_info.year&0xff;
                    block[6] = m_pis_info.month;
                    block[7] = m_pis_info.day;
                    block[8] = m_pis_info.hour;
                    block[9] = m_pis_info.min;
                    block[10] = m_pis_info.sec;
                    block[11] = m_pis_info.speed>>8;
                    block[12] = m_pis_info.speed&0xff;
                    for(i=0;i<7;i++)
                    {
                        block[13+i] = m_pis_info.trainNo[i];
                    }
                    block[20] = m_devices[j].coach;
                    block[21] = m+8;
                    block[22] = m_pis_info.mileage>>8;
                    block[23] = m_pis_info.mileage&0xff;
                    for(i = 0;i < sizeof(m_pis_info.info);i ++)
                    {
                        block[24+i] = m_pis_info.info[i];
                    }
                    block[54] =MoniterClient::crc_sum((unsigned char*)block.data(),54);

                    Moniter->sendCmd(m_devices[j].coach, block);
                }
            }
        }
    }
}
