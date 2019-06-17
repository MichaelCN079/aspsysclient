#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QSplashScreen>

/**
  * MainWidget类：程序初始化界面，从60s开始倒计时，倒计时结束后进入登陆界面
  * Added by YangJL 2019.5.14
  */

#include <QWidget>

namespace Ui {
class MainWidget;
}

class QTimerEvent;
class LoginWidget;
class MainWidget : public QSplashScreen
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

protected:
    void timerEvent(QTimerEvent *evt);

private:
    Ui::MainWidget *ui;
    int m_timerId;
    int m_count;
    LoginWidget *m_pLoginWidget;

};

#endif // MAINWIDGET_H
