#include "mainwidget.h"
#include "common.h"
#include "loginwidget.h"

#include <QApplication>
#include <QFile>
#include <QProcess>
#include <QDomDocument>

int m_width;
int m_height;
NVR_INFO_S m_nvr_info_s;
char RTSP_PLAYBACK_TEST[256];
PIS_INFO_S m_pis_info;

int m_currcoach;//当前车厢号
int m_currindex;//当前摄像机位置号
QString g_crhtype; //当前车型

int m_poiilingtime;
int m_presetpolltime;
bool m_isPoiiling;
bool m_chnState[8] = {false};
Chn_Info g_chnInfo[8];
QStringList cxList;   //车型列表

DEVICE_S m_devices[MAX_DEVICE_CNT];
CHRDeviceInfo_S g_deviceInfo;

void loadQss();
bool parseConfigurefile(QString fileName);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载样式表文件
    loadQss();

    //加载配置文件
    parseConfigurefile("railway.cfg");

    MainWidget w;
	w.show();
	LoginWidget objLoginWidget;
	objLoginWidget.show();
	w.finish(&objLoginWidget);

    int  ret= a.exec();
    if(ret == RETCODE_RESTART)
    {
        // 传入 qApp->applicationFilePath()，启动自己
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }
    return ret;
}

void loadQss()
{
    QFile qss(":/myimages/qss/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}

//配置文件解析
bool parseConfigurefile(QString fileName)
{
    QFile file(fileName);
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;
    int index = 0;

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"open config file "<<fileName<<"failed"<< ": " << (file.errorString());
        return false;
    }

    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
    {
        qDebug()<< "Error: Parse error at line " << errorLine << ", "<< "column " << errorColumn << ": " << (errorStr);
        file.close();
        return false;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName() != "RAILWAYCFG")
    {
        file.close();
        return false;
    }

    QDomNode child = root.firstChild();
    while(!child.isNull())
    {
        if(child.toElement().tagName()=="Type")
        {
            g_crhtype = child.toElement().text();
        }
        else if(child.toElement().tagName() == "TypeList")
        {
            QDomNode typeNode = child.toElement().firstChild();
            while (!typeNode.isNull())
            {
                cxList << typeNode.toElement().tagName();
                typeNode = typeNode.nextSibling();
            }
            index = 0;
            QDomNode child_ = child.toElement().firstChild();
            while (!child_.isNull())
            {
                if (child_.toElement().tagName() == g_crhtype)
                {
                    QDomNode child__1 = child_.toElement().firstChild();
                    g_deviceInfo.deviceCount = child__1.toElement().text().toInt();
                    QDomNode child__2 = child__1.nextSibling();
                    if (child__2.toElement().tagName() == "DeviceList")
                    {
                        child__2 = child__2.toElement().firstChild();
                        int i = 0;
                        while (!child__2.isNull())
                        {
                            if (child__2.toElement().tagName() == "Device")
                            {
                                QDomNodeList deviceItems = child__2.toElement().childNodes();
                                int itemCount = deviceItems.count();
                                for (int j = 0; j < itemCount; ++j)
                                {
                                    QDomElement deviceItem = deviceItems.at(j).toElement();
                                    if ("Type" == deviceItem.tagName())
                                    {
                                        QString s = deviceItem.text();
                                        if(s=="PIS")
                                            g_deviceInfo.m_devices[i].type = DEVICE_PIS;
                                        else if(s=="NVR")
                                            g_deviceInfo.m_devices[i].type = DEVICE_NVR;
                                        else if(s=="IPC")
                                            g_deviceInfo.m_devices[i].type = DEVICE_IPC;
                                    }
                                    else if ("ServerIP" == deviceItem.tagName())
                                    {
                                        QString serverIp = deviceItem.text();
                                        QByteArray ba = serverIp.toLatin1();
                                        memcpy(g_deviceInfo.m_devices[i].NvrIp, ba.data(), 16);
                                    }
                                    else if ("CoachNo" == deviceItem.tagName())
                                    {
                                        g_deviceInfo.m_devices[i].coach = deviceItem.text().toInt();
                                    }
                                    else if ("IndexNo" == deviceItem.tagName())
                                    {
                                        g_deviceInfo.m_devices[i].index = deviceItem.text().toInt();
                                    }
                                    else if ("RTSPPort" == deviceItem.tagName())
                                    {
                                        g_deviceInfo.m_devices[i].rtspport = deviceItem.text().toInt();
                                    }
									else if ("CtlPort" == deviceItem.tagName())
									{
										g_deviceInfo.m_devices[i].port = deviceItem.text().toInt();
									}
                                    else if ("CameraIP" == deviceItem.tagName())
                                    {
										QString serverIp = deviceItem.text();
										QByteArray ba = serverIp.toLatin1();
										memcpy(g_deviceInfo.m_devices[i].IpcIp, ba.data(), 16);
                                    }
                                }
								g_deviceInfo.m_devices[i].iCameraPos = 1;
								g_deviceInfo.m_devices[i].bCameraState = false;
								g_deviceInfo.m_devices[i].bLightState = false;
                            }
                            child__2 = child__2.nextSibling();
                            i++;
                            if (i == MAX_DEVICE_CNT)
                                break;
                        }
                    }
                    break;
                }
                child_ = child_.nextSibling();
            }
        }
        child = child.nextSibling();
    }
    file.close();
    return true;
}

