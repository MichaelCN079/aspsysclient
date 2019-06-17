#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class PreviewWidget;
}

class QPaintEvent;
class QRect;
class Thread;
class PreviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviewWidget(int type, int coach = 0, int index = 0, int subCoach= 0, int subIndex = 0, QWidget *parent = 0);
    ~PreviewWidget();

    void startPreview();
	void SetSubViewPos(int iSubViewPos);
	int GetSubViewPos();
	void ToggleMainSubView();
	bool GetViewToggleFlag();

signals:
	void signalMainViewClicked();
	void signalToggleMainSubView();

protected:
    void paintEvent(QPaintEvent *evt);
	void mousePressEvent(QMouseEvent *evt);
	//bool eventFilter(QObject *, QEvent *);

//public slots:
//    void slotVideoChanged(int index);
//    void slotVideoChanged(QWidget *);

public:
	QWidget *m_pMainPreviewWidget;
	QWidget *m_pSubPreviewWidget;
    int m_coach, m_subCoach;
    int m_index, m_subIndex;
	int m_iCurIndex;
	int m_iCurCoach;

private:
    Ui::PreviewWidget *ui;
    QRect *m_pSingleRect;
    QThread *m_pWorkThread;
    int m_type; //0:短编组 非0:长编组
    //int m_index;
    //int m_subIndex;
	int m_iSubViewPos;	//子画面位置（0~15）
	bool m_bViewToggle;
};

#endif // PREVIEWWIDGET_H
