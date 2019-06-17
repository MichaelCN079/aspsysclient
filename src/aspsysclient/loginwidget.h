#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

typedef struct SUsrInfo
{
    QString usrName;
    QString passwd;
    int type; //0:admin 1:user
} UsrInfo;

namespace Ui {
class LoginWidget;
}

class QLineEdit;
class ContentWidget;
class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr, int type = 0, ContentWidget *lastWidget = nullptr);
    ~LoginWidget();

private slots:
    void slotKb0Clicked();
    void slotKb1Clicked();
    void slotKb2Clicked();
    void slotKb3Clicked();
    void slotKb4Clicked();
    void slotKb5Clicked();
    void slotKb6Clicked();
    void slotKb7Clicked();
    void slotKb8Clicked();
    void slotKb9Clicked();
    void slotKbaClicked();
    void slotKbbClicked();
    void slotKbcClicked();
    void slotKbdClicked();
    void slotKbeClicked();
    void slotKbfClicked();
    void slotKbgClicked();
    void slotKbhClicked();
    void slotKbiClicked();
    void slotKbjClicked();
    void slotKbkClicked();
    void slotKblClicked();
    void slotKbmClicked();
    void slotKbnClicked();
    void slotKboClicked();
    void slotKbpClicked();
    void slotKbqClicked();
    void slotKbrClicked();
    void slotKbsClicked();
    void slotKbtClicked();
    void slotKbuClicked();
    void slotKbvClicked();
    void slotKbwClicked();
    void slotKbxClicked();
    void slotKbyClicked();
    void slotKbzClicked();

    void slotOkBtnClicked();
    void slotCancelBtnClicked();
    void slotRetryBtnClicked();

private:

    void initSlots();

public:
    static UsrInfo m_usrInfo;

private:
    Ui::LoginWidget *ui;
    bool bUsrEditFlag;
    bool bPasswdEditFlag;
    int  m_type; //0:登陆, 1:车次设置 2:维护更新 3:权限设置
    QLineEdit *m_pCCMngEdit;
    QLineEdit *m_pPassEdit;
    ContentWidget *m_pLastWidget;
};

#endif // LOGINWIDGET_H
