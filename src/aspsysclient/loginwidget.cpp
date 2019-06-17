#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "customelineedit.h"
#include "ui_contentwidget.h"
#include "contentwidget.h"

#include <QPalette>
#include <QPushButton>
#include <QThread>
#include <QDebug>

UsrInfo LoginWidget::m_usrInfo;

LoginWidget::LoginWidget(QWidget *parent, int type, ContentWidget *pLastWidget) :
    QWidget(parent), m_type(type),m_pLastWidget(pLastWidget),
    ui(new Ui::LoginWidget),
    bUsrEditFlag(true), bPasswdEditFlag(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    //添加背景图片
    QPalette mypalette = palette();
    mypalette.setBrush(QPalette::Background, QBrush(QPixmap(":/myimages/images/background.png")));
    setPalette(mypalette);

    initSlots();

    if (m_type == 1) //车次设置
    {
        ui->horizontalLayout->removeWidget(ui->groupBox);
        ui->groupBox->close();
        QLabel *pLabel = new QLabel(this);
        pLabel->setObjectName("pCCLabel");
        pLabel->setText(tr("请输入车次："));
        pLabel->setStyleSheet("QLabel#pCCLabel{color:white}");
        m_pCCMngEdit = new QLineEdit(this);
        m_pCCMngEdit->setObjectName("pCCEdit");
        m_pCCMngEdit->setStyleSheet("QLineEdit#pCCEdit{color:white}");
        m_pCCMngEdit->setMinimumSize(100, 40);
        m_pCCMngEdit->setMaximumSize(150, 40);
        m_pCCMngEdit->setStyleSheet("QLineEdit{border-image: url(:/myimages/images/editGround.png);color:white;}");
        ui->horizontalLayout->insertWidget(1, pLabel);
        ui->horizontalLayout->insertWidget(2, m_pCCMngEdit);

    }
    else if (m_type == 2) //维护更新
    {
        ui->horizontalLayout->removeWidget(ui->groupBox);
        ui->groupBox->close();
        QLabel *pLabel = new QLabel(this);
        pLabel->setObjectName("pPassLabel");
        pLabel->setText(tr("请输入密码："));
        pLabel->setStyleSheet("QLabel#pPassLabel{color:white}");
        m_pPassEdit = new QLineEdit(this);
        m_pPassEdit->setMinimumSize(100, 40);
        m_pPassEdit->setMaximumSize(150, 40);
        m_pPassEdit->setStyleSheet("QLineEdit{border-image: url(:/myimages/images/editGround.png);color:white}");
        ui->horizontalLayout->insertWidget(1, pLabel);
        ui->horizontalLayout->insertWidget(2, m_pPassEdit);
    }

	int msec = 1000;
	{
		QTime dieTime = QTime::currentTime().addMSecs(msec);

		while (QTime::currentTime() < dieTime)

			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::slotKb0Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("0");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("0");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("0");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("0");
        m_pPassEdit->setText(str);
    }

}

void LoginWidget::slotKb1Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("1");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("1");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("1");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("1");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb2Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("2");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("2");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("2");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("2");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb3Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("3");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("3");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("3");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("3");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb4Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("4");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("4");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("4");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("4");
        m_pPassEdit->setText(str);
    }



}

void LoginWidget::slotKb5Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("5");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("5");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("5");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("5");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb6Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("6");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("6");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("6");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("6");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb7Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("7");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("7");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("7");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("7");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKb8Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("8");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("8");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("8");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("8");
        m_pPassEdit->setText(str);
    }

}

void LoginWidget::slotKb9Clicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("9");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("9");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("9");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("9");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbaClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("a");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("a");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("A");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("a");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbbClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("b");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("b");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("B");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("b");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbcClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("c");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("c");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("C");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("c");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbdClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("d");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("d");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("D");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("d");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbeClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("e");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("e");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("E");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("e");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbfClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("f");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("f");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("F");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("f");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbgClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("g");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("g");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("G");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("g");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbhClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("h");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("h");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("H");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("h");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbiClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("i");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("i");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("I");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("i");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbjClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("j");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("j");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("J");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("j");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbkClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("k");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("k");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("K");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("k");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKblClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("l");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("l");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("L");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("l");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbmClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("m");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("m");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("M");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("m");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbnClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("n");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("n");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("N");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("n");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKboClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("o");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("o");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("O");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("o");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbpClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("p");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("p");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("P");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("p");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbqClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("q");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("q");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("Q");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("q");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbrClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("r");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("r");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("R");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("r");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbsClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("s");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("s");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("S");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("s");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbtClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("t");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("t");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("T");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("t");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbuClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("u");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("u");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("U");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("u");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbvClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("v");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("v");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("V");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("v");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbwClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("w");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("w");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("W");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("w");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbxClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("x");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("x");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("X");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("x");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbyClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("y");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("y");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("Y");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("y");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotKbzClicked()
{
    QString str;
    if (m_type == 0)
    {
        if (CustomeLineEdit::bUsrNameFocus)
        {
            str = ui->usrNameEdit->text();
            str.append("z");
            ui->usrNameEdit->setText(str);
        }
        else if (CustomeLineEdit::bPasswdFocus)
        {
            str = ui->passwdEdit->text();
            str.append("z");
            ui->passwdEdit->setText(str);
        }
    }
    else if (m_type == 1)
    {
        str = m_pCCMngEdit->text();
        str.append("Z");
        m_pCCMngEdit->setText(str);
    }
    else if (m_type == 2)
    {
        str = m_pPassEdit->text();
        str.append("z");
        m_pPassEdit->setText(str);
    }


}

void LoginWidget::slotOkBtnClicked()
{
    ContentWidget *pContent = nullptr;
    switch (m_type)
    {
    case 0:
        pContent = new ContentWidget;
        pContent->show();
        break;
    case 1:
        m_pLastWidget->show();
        m_pLastWidget->setCC(m_pCCMngEdit->text());
        break;
    case 2:
        m_pLastWidget->show();
        m_pLastWidget->ui->stackedWidget->setCurrentIndex(4);
        break;
    default:
        break;
    }
    close();

}

void LoginWidget::slotCancelBtnClicked()
{
    switch (m_type)
    {
    case 0:
        break;
    case 1:
    case 2:
        m_pLastWidget->show();
        break;
    default:
        break;
    }
    close();
}

void LoginWidget::slotRetryBtnClicked()
{
    if (m_type == 0)
    {
        ui->usrNameEdit->setText("");
        ui->passwdEdit->setText("");
    }
    else if (m_type == 1)
    {
        m_pCCMngEdit->setText("");
    }
    else if (m_type == 2)
    {
        m_pPassEdit->setText("");
    }
}

void LoginWidget::initSlots()
{
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(slotKb0Clicked()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(slotKb1Clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(slotKb2Clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(slotKb3Clicked()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(slotKb4Clicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(slotKb5Clicked()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(slotKb6Clicked()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(slotKb7Clicked()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(slotKb8Clicked()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(slotKb9Clicked()));
    connect(ui->pushButton_a, SIGNAL(clicked()), this, SLOT(slotKbaClicked()));
    connect(ui->pushButton_b, SIGNAL(clicked()), this, SLOT(slotKbbClicked()));
    connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(slotKbcClicked()));
    connect(ui->pushButton_d, SIGNAL(clicked()), this, SLOT(slotKbdClicked()));
    connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(slotKbeClicked()));
    connect(ui->pushButton_f, SIGNAL(clicked()), this, SLOT(slotKbfClicked()));
    connect(ui->pushButton_g, SIGNAL(clicked()), this, SLOT(slotKbgClicked()));
    connect(ui->pushButton_h, SIGNAL(clicked()), this, SLOT(slotKbhClicked()));
    connect(ui->pushButton_i, SIGNAL(clicked()), this, SLOT(slotKbiClicked()));
    connect(ui->pushButton_j, SIGNAL(clicked()), this, SLOT(slotKbjClicked()));
    connect(ui->pushButton_k, SIGNAL(clicked()), this, SLOT(slotKbkClicked()));
    connect(ui->pushButton_l, SIGNAL(clicked()), this, SLOT(slotKblClicked()));
    connect(ui->pushButton_m, SIGNAL(clicked()), this, SLOT(slotKbmClicked()));
    connect(ui->pushButton_n, SIGNAL(clicked()), this, SLOT(slotKbnClicked()));
    connect(ui->pushButton_o, SIGNAL(clicked()), this, SLOT(slotKboClicked()));
    connect(ui->pushButton_p, SIGNAL(clicked()), this, SLOT(slotKbpClicked()));
    connect(ui->pushButton_q, SIGNAL(clicked()), this, SLOT(slotKbqClicked()));
    connect(ui->pushButton_r, SIGNAL(clicked()), this, SLOT(slotKbrClicked()));
    connect(ui->pushButton_s, SIGNAL(clicked()), this, SLOT(slotKbsClicked()));
    connect(ui->pushButton_t, SIGNAL(clicked()), this, SLOT(slotKbtClicked()));
    connect(ui->pushButton_u, SIGNAL(clicked()), this, SLOT(slotKbuClicked()));
    connect(ui->pushButton_v, SIGNAL(clicked()), this, SLOT(slotKbvClicked()));
    connect(ui->pushButton_w, SIGNAL(clicked()), this, SLOT(slotKbwClicked()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(slotKbxClicked()));
    connect(ui->pushButton_y, SIGNAL(clicked()), this, SLOT(slotKbyClicked()));
    connect(ui->pushButton_z, SIGNAL(clicked()), this, SLOT(slotKbzClicked()));

    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(slotOkBtnClicked()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancelBtnClicked()));
    connect(ui->retryBtn, SIGNAL(clicked()), this, SLOT(slotRetryBtnClicked()));
}
