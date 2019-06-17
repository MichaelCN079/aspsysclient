#ifndef STARTCONNECTWORK_H
#define STARTCONNECTWORK_H

#include <QObject>
#include <QStringList>

#include "playworker.h"

class StartConnectWork : public QObject
{
    Q_OBJECT
public:
    explicit StartConnectWork(QObject *parent = 0);
    ~StartConnectWork();

public:
    void init(QStringList palyWindList, QStringList urllist){
        m_palyWindList = palyWindList;
        m_playURLList = urllist;
    }
public slots:
    void doWork() {
        int winid;
        for (int i=0; ((i < m_palyWindList.size())&& (i < m_playURLList.size())); i++)
        {
            PlayWorker *playworker = CurrPlayWork[i];
            winid = m_palyWindList.at(i).toInt();
            playworker->readyToPlay(winid,m_playURLList.at(i));
            playworker->start();
            qDebug() << "winid:" << winid <<", "<< m_playURLList.at(i);
            //QThread::msleep(3000);
        }
}
private:
    QStringList m_palyWindList;
    QStringList m_playURLList;
};

#endif // STARTCONNECTWORK_H
