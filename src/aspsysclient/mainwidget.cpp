#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QTimerEvent>
#include <QPalette>
#include <QThread>

static int MAX_TIMER_COUNT = 60;

MainWidget::MainWidget(QWidget *parent) :
    ui(new Ui::MainWidget),
    m_count(MAX_TIMER_COUNT)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint); //设置窗体无边框
    m_timerId = startTimer(1000);

    //添加背景图片
    QPalette mypalette = palette();
    mypalette.setBrush(QPalette::Background, QBrush(QPixmap(":/myimages/images/background.png")));
    setPalette(mypalette);
}

MainWidget::~MainWidget()
{
    delete ui;
}

//定时器超时处理函数
void MainWidget::timerEvent(QTimerEvent *evt)
{
	QString countingInfoStr = QString::fromLocal8Bit("监控程序正在启动，请稍候...%1秒").arg(--m_count);
    if (evt->timerId() == m_timerId)
        ui->countingInfoLabel->setText(countingInfoStr);


    //倒计时结束，停止计时，并进入登陆界面
    if (!m_count)
    {
        killTimer(m_timerId);

        close();
    }
}
