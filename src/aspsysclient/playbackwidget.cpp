#include "playbackwidget.h"
#include "ui_playbackwidget.h"

PlayBackWidget::PlayBackWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayBackWidget)
{
    ui->setupUi(this);
}

PlayBackWidget::~PlayBackWidget()
{
    delete ui;
}
