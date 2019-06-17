#ifndef PLAYBACKWIDGET_H
#define PLAYBACKWIDGET_H

#include <QWidget>

namespace Ui {
class PlayBackWidget;
}

class PlayBackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayBackWidget(QWidget *parent = 0);
    ~PlayBackWidget();

private:
    Ui::PlayBackWidget *ui;
};

#endif // PLAYBACKWIDGET_H
