#include "previewwidget.h"
#include "ui_previewwidget.h"
#include "JVSDKP.h"
#include "common.h"
#include "startconnectwork.h"


#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QRect>

PreviewWidget::PreviewWidget(int type, int coach, int index, int subCoach, int subIndex, QWidget *parent) :
    QWidget(parent), m_type(type),m_coach(coach), m_index(index), m_subCoach(subCoach), m_subIndex(subIndex),
    ui(new Ui::PreviewWidget), m_iCurCoach(coach), m_iCurIndex(index),
	m_pSubPreviewWidget(nullptr), m_pMainPreviewWidget(nullptr), m_iSubViewPos(3), m_bViewToggle(false)
{
    ui->setupUi(this);

	//主画面
	m_pMainPreviewWidget = new QWidget(this);
	m_pMainPreviewWidget->setGeometry(rect());
	m_pMainPreviewWidget->setStyleSheet("border-image: url(:/myimages/images/videoConnetting.png);");

	//画中画
    if (m_type) //长编组画中画
    {
        //QHBoxLayout *pHLayout = new QHBoxLayout;
        //pHLayout->addItem(new QSpacerItem(50, 1, QSizePolicy::Expanding, QSizePolicy::Fixed));
        //m_pSubPreviewWidget = new QWidget(this);
        //m_pSubPreviewWidget->setFixedSize(200, 200);
        //m_pSubPreviewWidget->setStyleSheet("border-image: url(:/myimages/images/videoConnetting.png);");
        //pHLayout->addWidget(m_pSubPreviewWidget);
        //QVBoxLayout *pVLayout = new QVBoxLayout;
        //pVLayout->addLayout(pHLayout);
        //pVLayout->addItem(new QSpacerItem(1, 50, QSizePolicy::Fixed, QSizePolicy::Expanding));
        //setLayout(pVLayout);

		m_pSubPreviewWidget = new QWidget(this);
		m_pSubPreviewWidget->setGeometry(width() * (m_iSubViewPos % 4) / 4, height() * (m_iSubViewPos / 4) / 4, width() / 4, height() / 4);
		m_pSubPreviewWidget->setStyleSheet("border-image: url(:/myimages/images/videoConnetting.png);");
    }
    //installEventFilter(this);
}

PreviewWidget::~PreviewWidget()
{
    delete ui;
}

void PreviewWidget::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PreviewWidget::mousePressEvent(QMouseEvent *evt)
{
	if ((!m_bViewToggle && m_pSubPreviewWidget->geometry().contains(evt->pos())) 
		|| (m_bViewToggle && m_pMainPreviewWidget->geometry().contains(evt->pos())))
	{
		ToggleMainSubView();
	}
	else
	{
		emit signalMainViewClicked();
	}
	QWidget::mousePressEvent(evt);
}

void PreviewWidget::SetSubViewPos(int iSubViewPos)
{
	m_iSubViewPos = iSubViewPos;
	if (0 > m_iSubViewPos || 15 < m_iSubViewPos)
	{
		m_iSubViewPos = 3;
	}
	if (NULL != m_pSubPreviewWidget)
	{
		m_pSubPreviewWidget->setGeometry(width() * (m_iSubViewPos % 4) / 4, height() * (m_iSubViewPos / 4) / 4, width() / 4, height() / 4);
	}
}

int PreviewWidget::GetSubViewPos()
{
	if (0 > m_iSubViewPos || 15 < m_iSubViewPos)
	{
		m_iSubViewPos = 3;
	}
	return m_iSubViewPos;
}

//大小画面切换
void PreviewWidget::ToggleMainSubView()
{
	m_bViewToggle = !m_bViewToggle;
	if (m_bViewToggle)
	{
		m_iCurCoach = m_subCoach;
		m_iCurIndex = m_subIndex;
		m_pMainPreviewWidget->raise();
	}
	else
	{
		m_iCurCoach = m_coach;
		m_iCurIndex = m_index;
		m_pSubPreviewWidget->raise();
	}
	m_currcoach = m_iCurCoach;
	m_currindex = m_iCurIndex;
	emit signalToggleMainSubView();
}

bool PreviewWidget::GetViewToggleFlag()
{
	return m_bViewToggle;
}

/*
bool PreviewWidget::eventFilter(QObject *obj, QEvent *evt)
{
    if (obj == this)
    {
        if (evt->type() == QEvent::Resize)
        {
            QRect rect;
            rect = geometry();
            //更新视频显示位置--将smalldispArea的位置转化为在dispArea中的位置
            QPoint topleft = mapToGlobal(rect.topLeft());
            QPoint bottomright = mapToGlobal(rect.bottomRight());
            g_chnInfo[m_index].location.setTopLeft(topleft);
            g_chnInfo[m_index].location.setBottomRight(bottomright);
            PlayWorker *playworker = CurrPlayWork[m_index];
            if (playworker) playworker->changePlayRect();
			if (m_type)
			{
				QRect subRect;
				subRect = m_pSubPreviewWidget->geometry();
				//更新视频显示位置--将smalldispArea的位置转化为在dispArea中的位置
				QPoint subTopleft = mapToGlobal(subRect.topLeft());
				QPoint subBottomright = mapToGlobal(subRect.bottomRight());
                g_chnInfo[m_subIndex].location.setTopLeft(subTopleft);
                g_chnInfo[m_subIndex].location.setBottomRight(subBottomright);
                PlayWorker *subPlayworker=CurrPlayWork[m_subIndex];
				if (subPlayworker) subPlayworker->changePlayRect();
			}
        }
    }
    return QWidget::eventFilter(obj, evt);
}
*/
//
//void PreviewWidget::slotVideoChanged(int index)
//{
//    m_index = index;
//
//}
//
//void PreviewWidget::slotVideoChanged(QWidget *pWidget)
//{
////    if (pWidget == this)
////        eventFilter(this, new QEvent(QEvent::Resize));
//}

void PreviewWidget::startPreview()
{
    m_pWorkThread->start();
    //m_pWorkThread->startTimer();
}
