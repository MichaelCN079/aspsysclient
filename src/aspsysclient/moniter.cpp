//#include "StdAfx.h"
#include "moniter.h"
#include "common.h"
#include <QSignalMapper>
#include <QMessageBox>

MoniterClient *Moniter = NULL;

MoniterClient::MoniterClient(QObject *parent)
    :QObject(parent)
{
    msgId=0;
    heartbeat=0;
	checkheart = 0;
    connectOK = false;
	m_timeouttime = 3;
    Moniter = this;
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));  
    m_timer.setInterval(10000); 
	
    QSignalMapper *signalMap = new QSignalMapper;
    for(int i = 0; i < 4; i++)
    {
		m_timerlight[i].setInterval(1000*60*10);
        connect(&m_timerlight[i], SIGNAL(timeout()), signalMap, SLOT(map()));
        signalMap->setMapping(&m_timerlight[i], QString::number(i, 10));
    }
    connect(signalMap, SIGNAL(mapped(QString)), this, SIGNAL(slotLightTimeout(QString)));
	
    QSignalMapper *socketReadSignalMap = new QSignalMapper;
    QSignalMapper *socketConnectSignalMap = new QSignalMapper;
    QSignalMapper *socketDisConnSignalMap = new QSignalMapper;
	for(int i = 0; i < MAX_DEVICE_CNT; i++)
	{
        if((/*g_deviceInfo.m_devices[i].type==DEVICE_PIS||*/g_deviceInfo.m_devices[i].type==DEVICE_NVR)&&!g_deviceInfo.m_devices[i].socket)
		{
			QTcpSocket *socket = new QTcpSocket(this);
            g_deviceInfo.m_devices[i].socket = socket;
            if(g_deviceInfo.m_devices[i].type==DEVICE_PIS)
                g_deviceInfo.m_devices[i].coach = 0;
			connect(socket, SIGNAL(readyRead()), socketReadSignalMap, SLOT(map()));
            socketReadSignalMap->setMapping(socket, QString::number(g_deviceInfo.m_devices[i].coach, 10));
				
			connect(socket, SIGNAL(connected()), socketConnectSignalMap, SLOT(map()));
            socketConnectSignalMap->setMapping(socket, QString::number(g_deviceInfo.m_devices[i].coach, 10));
				
			connect(socket, SIGNAL(disconnected()), socketDisConnSignalMap, SLOT(map()));
            socketDisConnSignalMap->setMapping(socket, QString::number(g_deviceInfo.m_devices[i].coach, 10));
		}
	}
	connect(socketReadSignalMap, SIGNAL(mapped(QString)), this, SLOT(slotReadSocket(QString)));
	connect(socketConnectSignalMap, SIGNAL(mapped(QString)), this, SLOT(slotSocketConnected(QString)));
	connect(socketDisConnSignalMap, SIGNAL(mapped(QString)), this, SLOT(slotSocketDisconnected(QString)));

	progressDialog = new QProgressDialog;
	progressDialog->setVisible(false);
	progressDialog->setWindowModality(Qt::WindowModal);
    //connect(progressDialog, SIGNAL(canceled()), this, SLOT(slotCancelDownload()));
	progressDialog->reset();//setVisible 对QProgressDialog没用，
}
MoniterClient::~MoniterClient()
{

}

void MoniterClient::prepare(int coach){
	//for(int i = 0; i < MAX_DEVICE_CNT; i++)
	//{
 //       if((g_deviceInfo.m_devices[i].type==DEVICE_PIS)||(g_deviceInfo.m_devices[i].type==DEVICE_NVR&&coach==g_deviceInfo.m_devices[i].coach))
	//	{
 //           QTcpSocket *socket = g_deviceInfo.m_devices[i].socket;
	//		if(socket && socket->state()!=QTcpSocket::ConnectedState)
	//		{
 //               socket->connectToHost(g_deviceInfo.m_devices[i].ip, g_deviceInfo.m_devices[i].port);
 //               qDebug()<<"coach:"<<coach<<"connect : "<<g_deviceInfo.m_devices[i].ip, g_deviceInfo.m_devices[i].port;
	//			qDebug()<<"socket["<<coach<<"]:"<<socket;
	//		}
	//	}
	//}
	for (int i = 0; i < g_deviceInfo.deviceCount; i++)
	{
		if ((coach == g_deviceInfo.m_devices[i].coach))
		{
			QTcpSocket *socket = g_deviceInfo.m_devices[i].socket;
			if (NULL != socket && socket->state() == QTcpSocket::UnconnectedState)
			{
				socket->connectToHost(g_deviceInfo.m_devices[i].NvrIp, g_deviceInfo.m_devices[i].port);
			}
		}
	}
}

void MoniterClient::slotSocketConnected(QString index)
{
	bool ok;
	int coach;
    coach = index.toInt(&ok, 10);
	nvrconnectmap[coach] = true;
    connectOK = true;
}
void MoniterClient::slotSocketDisconnected(QString index)
{
	bool ok;
	int coach;
    coach = index.toInt(&ok, 10);
	nvrconnectmap[coach] = false;
    connectOK = false;
	prepare(coach);
	//for(int i = 0; i < MAX_DEVICE_CNT; i++)
	//{
 //       if(((g_deviceInfo.m_devices[i].type==DEVICE_PIS&&coach==0)||(g_deviceInfo.m_devices[i].type==DEVICE_NVR && g_deviceInfo.m_devices[i].coach==coach)) && g_deviceInfo.m_devices[i].socket)
	//	{
 //           g_deviceInfo.m_devices[i].socket->connectToHost(g_deviceInfo.m_devices[i].ip, g_deviceInfo.m_devices[i].port);
	//		break;
	//	}
	//}
}

void MoniterClient::slotTimeout()
{
	if(checkheart++ >=m_timeouttime){
//		prepare();
		checkheart=0;
		m_timeouttime = 3;
	}
}

void MoniterClient::slotLightTimeout(QString pos)
{
    int index;
    bool ok;
    
    index = pos.toInt(&ok, 10);
	QByteArray ba;
	ba[0]=PVMS_PROTOCOL_HEADER_SC;
	ba[1]=PVMS_PROTOCOL_LIGHT_CTL;
	ba[2]=0;//
	ba[3]=2;//
	ba[4]=0x2;//
	ba[5]=index;
	ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
	Moniter->sendCmd(m_currcoach, ba);
}

void MoniterClient::sendCmd(int coach, const QByteArray &msg)
{
    mutex.lock();
    msgId++;
	
	for(int i = 0; i < MAX_DEVICE_CNT; i++)
	{
        if((g_deviceInfo.m_devices[i].type==DEVICE_PIS&&coach==0)||(g_deviceInfo.m_devices[i].type==DEVICE_NVR&&g_deviceInfo.m_devices[i].coach==coach))
		{
			if(nvrconnectmap[coach])
			{
                g_deviceInfo.m_devices[i].socket->write(msg);
                qDebug()<<"g_deviceInfo.m_devices["<<i<<"]:"<<g_deviceInfo.m_devices[i].socket;
				break;
			}
		}
	}

    mutex.unlock();
    qDebug()<<">>>>"<<msgId<<msg.toHex();
}

QString MoniterClient::slotReadSocket(QString itemIndex)
{
    int coach;
    bool ok;
	int curr;
    QString string;
	QTcpSocket *socket = NULL;
	int i;
	QByteArray block;
    
    coach = itemIndex.toInt(&ok, 10);
	for(i = 0; i < MAX_DEVICE_CNT; i++)
	{
        if((/*(g_deviceInfo.m_devices[i].type==DEVICE_PIS&&coach==0)||*/((g_deviceInfo.m_devices[i].type==DEVICE_NVR)&&(g_deviceInfo.m_devices[i].coach==coach)))&& g_deviceInfo.m_devices[i].socket )
		{
            socket = g_deviceInfo.m_devices[i].socket;
			block = socket->readAll();
			qDebug()<<"<<<<<<<<<<"<<block.length();
			msgId++;
			break;
		}
	}
	if(i == MAX_DEVICE_CNT)
		return string;
//    qDebug()<<"<<<<"<<msgId<<block.toHex();
	unsigned char *data = (unsigned char*)block.data();
	CMD_HEAD *cmd;
	cmd = (CMD_HEAD*)data;
	QByteArray s;
	s[0]=PVMS_PROTOCOL_HEADER_SC;
	s[1]=PVMS_PROTOCOL_HEATER_NVR;
	s[2]=0;
	s[3]=0;
	s[4]=crc_sum((unsigned char *)s.data(),4);

	int v;
	unsigned int a, b;
	int packNum;
	int packId;

	if(cmd->flag==PVMS_PROTOCOL_HEADER_SC)
	{
		switch(cmd->id)
		{
		case PVMS_PROTOCOL_HEATER_CLIENT://心跳
			mutex.lock();
			socket->write(s);//回复心跳
			mutex.unlock();
			heartbeat++;
			checkheart = 0;
			if(heartbeat==1)
				m_timer.start();//
			break;
		case PVMS_PROTOCOL_PIS_2_CLIENT://PIS 发送给授权终端的信息，日期时间，速度，车次，里程数等
			{
				int ii,j,m;
				//解析视频叠加信息
				PIS_INFO_S pis_info;
				pis_info.year = block[4]<<8 + block[5];
				pis_info.month= block[6];
				pis_info.day  = block[7];
				pis_info.hour = block[8];
				pis_info.min  = block[9];
				pis_info.sec  = block[10];
				pis_info.speed= block[11]<<8 + block[12];
				for(ii=0;ii<sizeof(pis_info.trainNo);ii++)
				{
					pis_info.trainNo[ii] = block[13+ii];
				}
				pis_info.mileage = block[24]<<8 + block[25];
				for(ii=0;ii<sizeof(pis_info.info);ii++)
				{
					pis_info.info[ii] = block[26+ii];
				}
				if(memcmp(&pis_info, &m_pis_info, sizeof(PIS_INFO_S)))
				{
					memcpy(&m_pis_info, &pis_info, sizeof(PIS_INFO_S));
					//发送视频叠加信息给NVR
					// ...
					for(j = 0;j<MAX_DEVICE_CNT; j++)
					{
                        if(g_deviceInfo.m_devices[j].type==DEVICE_NVR)
						{
							for(m=0; m<2; m++)
							{
								//发送视频叠加信息给NVR
								block[0] = PVMS_PROTOCOL_HEADER_SC;
								block[1] = PVMS_PROTOCOL_OVERLAY_OSD;
								block[2] = 0;
								block[3] = 50;
								block[4] = m_pis_info.year>>8;
								block[5] = m_pis_info.year&0xff;
								block[6] = m_pis_info.month;
								block[7] = m_pis_info.day;
								block[8] = m_pis_info.hour;
								block[9] = m_pis_info.min;
								block[10] = m_pis_info.sec;
								block[11] = m_pis_info.speed>>8;
								block[12] = m_pis_info.speed&0xff;

								//pis信息和显示终端发给NVR的trainNo长度不一样，注意一下
								for(ii=0;ii<7;ii++)
								{
									block[13+ii] = m_pis_info.trainNo[ii];
								}
                                block[20] = g_deviceInfo.m_devices[j].coach;
								block[21] = m + 8;
								block[22] = m_pis_info.mileage>>8;
								block[23] = m_pis_info.mileage&0xff; 
								for(ii=0;ii<sizeof(m_pis_info.info); ii++)
								{
									block[24+i] = m_pis_info.info[i];
								}
								block[54] =MoniterClient::crc_sum((unsigned char*)block.data(),54);
	
                                Moniter->sendCmd(g_deviceInfo.m_devices[j].coach, block);
							}
						}
					}
				}
				string = block;
				qDebug()<<string;
			}
			break;
		case PVMS_PROTOCOL_VIDEO_FAULT:// NVR发送给客户端的视频故障报文
			{
				int co = block[4];
				int nnn = block[5];
				int over = block[6];
				int lost = block[7];
				if((7<block[5])&&(10>block[5]))//过滤掉非受电弓摄像机的视频丢失报警
				{
					if(0!=block[6]&&0!=block[7])
					{
						emit signalAlarmPushed();
                        emit signalNewAlarm(g_deviceInfo.m_devices[i].coach,block);
					}
				}
			}
			break;
		case PVMS_PROTOCOL_HD_FAULT://硬盘报警消息
			if((0!=block[5])&&(0!=block[6]))//过滤掉正常的硬盘状态信息
			{
				emit signalAlarmPushed();
                emit signalNewAlarm(g_deviceInfo.m_devices[i].coach,block);
			}
			break;
		case 0x15://osd设置消息回复
			emit signalSetOsdResult();
			break;
		case PVMS_PROTOCOL_SDG_INFO:// NVR发给客户端的受电弓升降弓报文
			{
				//收到降弓信号，需要在10分钟后自动关闭补光灯，需要添加对应的超时函数和关闭补光灯的动作
				//收到升弓信号，立即打开补光灯
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(block.length()-1, block.length());
				if(1 == block[0]) //降弓信号
				{
					//降弓，10分钟后关闭补光灯
					m_timerlight[i].start();
				}
				else if(2 == block[0])//升弓信号
				{
					//升弓，开补光灯；
					QByteArray ba;
					ba[0]=0xff;
					ba[1]=0x15;
					ba[2]=0;
					ba[3]=2;
					ba[4]=0x1;
					ba[5]=i+1;
					ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
                    Moniter->sendCmd(g_deviceInfo.m_devices[i].coach, ba);
				}
				s[0]=PVMS_PROTOCOL_HEADER_SC;
				s[1]=PVMS_PROTOCOL_SDG_INFO_ACK;
				s[2]=0;
				s[3]=1;
				s[4]=1;
				s[5]=crc_sum((unsigned char *)s.data(),5);
				socket->write(s);
			}
			break;
		case PVMS_PROTOCOL_REMOTE_SEACH_PHOTO:// 远程搜索故障图片的回复信息
			break;
		case PVMS_PROTOCOL_SDG_FAULT_ALARM: // 受电弓故障报警信息
			emit signalAlarmPushed();
            emit signalNewAlarm(g_deviceInfo.m_devices[i].coach,block);
			break;
		case PVMS_PROTOCOL_SDG_GPS_PACKAGE: // NVR发送给客户端的GPS报文
			{
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(block.length()-1, block.length());
				//emit signalGetGPSPara(block);
			}
			break;
		case PVMS_PROTOCOL_PIS_SDG_INFO: // PIS发送给客户端的升降弓信息
			//升降弓协议不明确 暂时屏蔽掉
			for(int i=0; i < 4; i++)
			{
				if(data[4+i]==1)
				{
					//升弓，开补光灯；
					QByteArray ba;
					ba[0]=0xff;
					ba[1]=0x15;
					ba[2]=0;
					ba[3]=2;
					ba[4]=0x1;
					ba[5]=i+1;
					ba[6] =MoniterClient::crc_sum((unsigned char *)ba.data(),6);
                    Moniter->sendCmd(g_deviceInfo.m_devices[i].coach, ba);
				}
				else if(data[4+i]==0)
				{
					//降弓，10分钟后关闭补光灯
					m_timerlight[i].start();
				}
			}
			break;
		case PVMS_PROTOCOL_REMOTE_SEACH_FILE_ACK://录像查询回复
			do
			{
				unsigned short len;
				unsigned short len1 = (unsigned short)block[2];
				unsigned char len2 = (unsigned char)block[3];
				len = ((len1<<8)&0xff00)+len2;
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(0, 2);
				string = block;
				m_recordfiles.append(string);
				emit signalSearchRecords(m_recordfiles);
				m_recordfiles.clear();
				block.remove(0,len-2+1);
			}while(block.length()>0);
			break;
		case PVMS_PROTOCOL_CHECK_NVR_INFO_ACK://NVR状态回复
			block.remove(0,sizeof(CMD_HEAD));
			block.remove(block.length()-1, block.length());
			emit signalDevicesInfosNVR(block);
			break;
		case PVMS_PROTOCOL_CHECK_IPC_INFO_ACK://IPC状态回复
			{
				int ii,n;
				n = block.size();
				n = n/21; // 21是一个ipc状态信息的长度
				for(ii=0;ii<n;ii++)
				{
					block.remove(0,sizeof(CMD_HEAD));
					emit signalDevicesInfosIPC(block);
					block.remove(0,17);
				}
			}
			break;
		case PVMS_PROTOCOL_PTZ_ACK://云台控制消息回复
			block.remove(0,sizeof(CMD_HEAD));
			block.remove(block.length()-1, block.length());
			{
				int result = block[0];
                //if(result == 0)
                    //int ok = QMessageBox::warning(0,QObject::tr("Alarm"),QObject::tr("PTZ control failed,please do it again!"),
                    //MSG_YES);
			}
			break;
		case PVMS_PROTOCOL_PTZ_PRESET_ACK: // 设置受电弓IPC云台预置位的回复信息
			block.remove(0,sizeof(CMD_HEAD));
			block.remove(block.length()-1, block.length());
			{
				int result = block[0];
//				if(result == 0)
//					int ok = MessageBox::warning(0,QObject::tr("Alarm"),QObject::tr("PTZ preset control failed,please do it again!"),
//					MSG_YES);
			}
			break;
		case PVMS_PROTOCOL_IPC_CTL_ACK:// 控制受电弓IPC开关的消息回复
			block.remove(0,sizeof(CMD_HEAD));
			block.remove(block.length()-1, block.length());
			{
				int result = block[0];
//				if(result == 0)
//					int ok = MessageBox::warning(0,QObject::tr("Alarm"),QObject::tr("IPC control failed,please do it again!"),
//					MSG_YES);
			}
			break;
		case PVMS_PROTOCOL_LIGHT_CTL_ACK: // 控制受电弓IPC补光灯开关的消息回复
			block.remove(0,sizeof(CMD_HEAD));
			block.remove(block.length()-1, block.length());
			{
				int result = block[0];
//				if(result == 0)
//					int ok = MessageBox::warning(0,QObject::tr("Alarm"),QObject::tr("Fill-in light control failed,please do it again!"),
//					MSG_YES);
			}
			break;
		case PVMS_PROTOCOL_SDG_INFO_ACK: // 受电弓升弓降弓回复信息
			break;
		case PVMS_PROTOCOL_REMOTE_SEACH_PHOTO_ACK:// 搜索故障图片的回复信息
			break;
		case PVMS_PROTOCOL_GET_FAULT_PARAM_ACK:// 获取故障识别参数的回复信息
			break;
		case PVMS_PROTOCOL_SET_FAULT_PARAM_ACK: // 设置故障识别参数的回复信息
			break;
		case PVMS_PROTOCOL_GET_PLAYBACK_TOTAL_TIME_ACK://获取回放文件总时间回复信息
			{
				unsigned short total_time;
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(block.length()-1, block.length());
				total_time = (unsigned short)block[0]<<8 + (unsigned short)block[1];
				//emit signalPlaybackTotalTime(block);
			}
			break;
		case PVMS_PROTOCOL_GET_SDG_COACH_NO://获取受电弓车厢消息回复,个人感觉这个协议存在问题，不知是什么意思
			{
				unsigned short result;
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(block.length()-1, block.length());
				result = block[0];
				//emit signalGetSDGCoachState(block);
			}
			break;
		case 0x85://立即保存命令回复结果
			{
				block.remove(0,sizeof(CMD_HEAD));
				block.remove(block.length()-1, block.length());
				int coach = block[0];
				int site  = block[1];
				if(block[2])
				{
//					MessageBox::information((QWidget*)parent(), QObject::tr("Save now"),
//						QObject::tr("Coach:%1 Index:%2 Save Success .").arg(coach).arg(site));
				}
				else
				{
//					MessageBox::information((QWidget*)parent(), QObject::tr("Save now"),
//						QObject::tr("Coach:%1 Index:%2 Save Fail .").arg(coach).arg(site));
				}
			}
			break;
		}
	}
	else
	{
		//qDebug()<<"invalid message!!!";
	}
		
    qDebug()<<"\n";
    return string;
}
