/******************************************************************************

  Copyright (c) 2012-2015 Jovision Technology Co., Ltd. All rights reserved.

  File Name     : comman.h
  Version       : 
  Author        : 
  Created       : 2015-3-31
  Description   : 定义界面大小、字符串等; LunarConvert 转换阴历
  History       : 
  3.Date        : 2015-7-2 
    Author      : cy
    Modification: change tr to QT_TRANSLATE_NOOP
                  example:lupdate -verbose comman.h -codecfortr utf-8 -ts qt_english.ts
  2.Date        : 2015-6-17 
    Author      : tgh
    Modification: fix header file
  1.Date        : 2015-3-31 
    Author      : tgh
    Modification: Created file
******************************************************************************/

#ifndef COMMON_H
#define COMMON_H

#include <QtNetwork/QTcpSocket>
#include <QRect>


#define WINDOWS 1

#define SCREEN_WIDTH 1280//1024//720/*1200*/
#define SCREEN_HEIGHT 1024//768//576/*900*/
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 480
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 100
#define TITLE_WIDTH WINDOW_WIDTH
#define TITLE_HEIGHT 50
#define TITLE_HEIGHT_ 32
#define STATE_HEIGHT 62
#define STATE_WIDTH (WINDOW_WIDTH-BUTTON_WIDTH)
#define VIEW_HEIGHT (WINDOW_HEIGHT-TITLE_HEIGHT_)
#define VIEW_WIDTH (WINDOW_WIDTH-BUTTON_WIDTH)

#define UPDATE_TEMPNAME   "/tmp/update.bin"     	//临时文件名
#define VERSION_TEMPNAME  "/tmp/version.bin"        //版本文件名称

#define VERSION_NAME "nd6008-h3-1.0-CRH-ver.bin"
#define UPDATE_NAME "nd6008-h3-1.0-CRH.bin"


#define NVR_RTSP_FMT "rtsp://%s:%s@%s:%d/%s" //rtsp://username:pwd@ip:port/name





#ifdef Q_OS_WIN
#define RES_IMAGE_PATH ":/images/images/"
#else
#define INIT_PATH "/progs/conf.d/calibtate.dat"
#define RES_IMAGE_PATH "/progs/res/images/"
#endif
#define CLOUDSEE_ANDROID "http://webapp.yoosee.cc/downloadApp/cloudSee.html"

#define PUSHBTN_STYLE "QPushButton{background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                                 stop: 0 #747c94,\
                                                                 stop:0.48 #747c94,\
                                                                 stop:0.5 #133d76, \
                                                                 stop:0.7 #008af7, \
                                                                 stop: 1 #0cb0d4);\
                                          border:1px solid  blue;\
                                          border-radius: 6px;\
                                          color:white;} QPushButton:hover{border:1px solid  green;}"
 
#define PUSHBTN_CLOSE "QPushButton{background-color:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                                 stop: 0 #747c94,\
                                                                 stop:0.48 #747c94,\
                                                                 stop:0.5 #133d76, \
                                                                 stop:0.7 #008af7, \
                                                                 stop: 1 #0cb0d4);\
                                          border:1px solid  #8d8d8d;\
                                          border-radius: 6px;\
                                          color:white;\
                                          background-image: url(./imgs/close1.png);} QPushButton:hover{border-left:2px solid #070707;border-top:2px solid #070707;}"                            
/*top:0.5 #3a89c8, \
                                    747c94                             stop: 0 #c7d7e7,\
                                                                 stop:0.48 #74a4cd,\
                                                                 stop:0.5 #393939, \
#37526a                                                                 stop:0.8 #4bb7ef, \
                                                                 stop: 1 #2c689f);

*/

#define STORAGE 1
#define STORAGE_PLABACK 2
#define STORAGE_DISK 3
#define STORAGE_PLAN 4

#define BASICINFO 5

#define NETSET 6
#define NETSET_LOCAL 7
#define NETSET_PPPOE 8
#define NETSET_WIFI 9
#define NETSET_3G 10

#define MEDIASET 11

#define OSDSET 12

#define ALARMSET 13

#define DDNSSEt 14

#define SERIALSET 15

#define VIDEOPREVIEW 16

#define FILEMNG 17

#define RESTARTDEV 18

#define SYSTEMSET 19

#define STYTLESHEET_TEXTHIDDEN "border:transparent;color:transparent"
#define STYTLESHEET_TEXTSHOW "border:transparent;color:white"

typedef enum 
{
    DIALOG_PREVIEW = 0,
    DIALOG_PLAYBACK = 1,
    DIALOG_DEVICES = 2,
    DIALOG_UPDATE = 3,
}DIALOG_E;

#define COLOR_STATE "#50000000"
#define WEATHER_TEST "http://api.map.baidu.com/telematics/v3/weather?location=北京&output=json&ak=E4805d16520de693a3fe707cdc962045"


#define MAX_IPC_CLIENT 6

#define MAX_PIS_CNT 1
#define MAX_NVR_CNT 4
#define MAX_IPC_CNT 4
#define MAX_DEVICE_CNT (MAX_PIS_CNT+MAX_NVR_CNT+MAX_IPC_CNT)

typedef struct
{
    char *path;
    char *name;
    char *info;
}ICON_SHOW_INFO;

enum PREVIEW_MODE_E
{
    PREVIEW_MODE_1,
    PREVIEW_MODE_2,//pip
    PREVIEW_MODE_4,
    PREVIEW_MODE_6,
    PREVIEW_MODE_8,
    PREVIEW_MODE_9,
    PREVIEW_MODE_16,
    PREVIEW_MODE_25,
    PREVIEW_MODE_33,
    PREVIEW_MODE_36,
    PREVIEW_MODE_TOTAL
};

enum CRH_TYPE_E
{
    CRH_1A,
    CRH_1A_1169,	//CRH1A-(1169~1228)
    CRH_1A_WOPU,	//CRH1A卧铺
    CRH_1B,
    CRH_1E,
    CRH_2A,
	CRH_2B,
	CRH_2C,
	CRH_2E,
	CRH_3C,
	CRH_380A,
	CRH_380AL,
	CRH_380B,
	CRH_380BL,
	CRH_380CL,
	CRH_380D,
	CRH_5A,
	CRH_5G,
	CRH_250,		//时速250卧铺
	CRH_350,		//时速350卧铺
	CRH_MAX
};

enum DEVICE_TYPE_E
{
	DEVICE_PIS = 1,
	DEVICE_NVR,
	DEVICE_IPC
};

typedef struct{
	int type;		//CRH_TYPE_E
	int subtype;	//
}CRH_TYPE;

typedef struct{
	DEVICE_TYPE_E type;	//设备类型
	char name[64];		//设备名称
    char NvrIp[16];		//服务器IP(服务器):当无服务器时认为时摄像机IP,devip字段无效
    char IpcIp[16];     //摄像机IP
	int port;			//命令端口
	int coach;			//所在车厢号
	int index;			//摄像机位置号，对IPC设备有效，0 1 ...
	char rtspname[128];	//rtsp流
	int rtspport;		//rtsp端口
	int iCameraPos;		//相机角度（1-8）
	bool bLightState;	//补光灯状态（开/关）
	bool bCameraState;	//IPC状态（开/关）
	QTcpSocket *socket;
}DEVICE_S;

//车型信息
typedef struct
{
    int deviceCount;     //装置个数(受电弓摄像机)
    DEVICE_S m_devices[MAX_DEVICE_CNT]; //每个装置信息

}CHRDeviceInfo_S;

typedef struct{
	int rtsp_port_live;
	int rtsp_port_vod;
	char ip[16];
	char username[64];
	char password[64];
	char rtsp_name[MAX_IPC_CLIENT][256];
}NVR_INFO_S;

typedef struct{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	unsigned short speed;
	unsigned char trainNo[11];
	unsigned short mileage; 
	unsigned char info[30];
}PIS_INFO_S;

extern char RTSP_PLAYBACK_TEST[256];
extern unsigned int LunarCalendarTable[199];
extern int MonthAdd[12];
extern const char *ChDay[];
extern const char *ChMonth[];
extern unsigned int LunarCalendarDay;
extern PIS_INFO_S m_pis_info;
extern QString g_crhtype;
extern DEVICE_S m_devices[MAX_DEVICE_CNT];
extern CHRDeviceInfo_S g_deviceInfo;
extern int m_currcoach;//当前车厢号
extern int m_currindex;//当前摄像机位置号
extern QStringList cxList; //车型列表
extern int RETCODE_RESTART;  //重启指令
class MyConv : public QObject
{
public:
	static QString unicodeToString(QString str)
{
    //例如 str="4F60597D";
    int temp[1024*256];
    QChar qchar[1024*256];
    QString strOut;
    bool ok;
    int count=str.count();
    int len=count/4;
    for(int i=0;i<count;i+=4)
    {
     temp[i]=str.mid(i,4).toInt(&ok,16);//每四位转化为16进制整型
     qchar[i/4]=temp[i];
     QString str0(qchar, len);
     strOut=str0;
    }
    return strOut;
}
};
class LunarConvert : public QObject
{
public:
    static int LunarCalendar(unsigned int year,unsigned int month,unsigned int day)
    {
        int Spring_NY,Sun_NY,StaticDayCount;
        int index,flag;
        //Spring_NY 记录春节离当年元旦的天数。
        //Sun_NY 记录阳历日离当年元旦的天数。
        if ( ((LunarCalendarTable[year-1901] & 0x0060) >> 5) == 1)
            Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1;
        else
            Spring_NY = (LunarCalendarTable[year-1901] & 0x001F) - 1 + 31;
        Sun_NY = MonthAdd[month-1] + day - 1;
        if ( (!(year % 4)) && (month > 2))
            Sun_NY++;
        //StaticDayCount记录大小月的天数 29 或30
        //index 记录从哪个月开始来计算。
        //flag 是用来对闰月的特殊处理。
        //判断阳历日在春节前还是春节后
        if (Sun_NY >= Spring_NY)//阳历日在春节后（含春节那天）
        {
            Sun_NY -= Spring_NY;
            month = 1;
            index = 1;
            flag = 0;
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
            while (Sun_NY >= StaticDayCount)
            {
                Sun_NY -= StaticDayCount;
                index++;
                if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) )
                {
                    flag = ~flag;
                    if (flag == 0)
                        month++;
                }
                else
                    month++;
                if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                    StaticDayCount=29;
                else
                    StaticDayCount=30;
            }
            day = Sun_NY + 1;
        }
        else //阳历日在春节前
        {
            Spring_NY -= Sun_NY;
            year--;
            month = 12;
            if ( ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20) == 0)
                index = 12;
            else
                index = 13;
            flag = 0;
            if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                StaticDayCount = 29;
            else
                StaticDayCount = 30;
            while (Spring_NY > StaticDayCount)
            {
                Spring_NY -= StaticDayCount;
                index--;
                if (flag == 0)
                    month--;
                if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
                    flag = ~flag;
                if ( ( LunarCalendarTable[year - 1901] & (0x80000 >> (index-1)) ) ==0)
                    StaticDayCount = 29;
                else
                    StaticDayCount = 30;
            }
            day = StaticDayCount - Spring_NY + 1;
        }
        LunarCalendarDay |= day;
        LunarCalendarDay |= (month << 6);
        if (month == ((LunarCalendarTable[year - 1901] & 0xF00000) >> 20))
            return 1;
        else
            return 0;
    }
    static QString Lunar(int year,int month,int day)
    {
        QString str = "";
        if (LunarCalendar(year,month,day))
        {
            str+="闰";
        }
        str+=ChMonth[(LunarCalendarDay & 0x3C0) >> 6];
        str+="月";
        str+=ChDay[LunarCalendarDay & 0x3F];


        return str;
    }
    static unsigned int LunarDay(int year,int month,int day)
    {
        LunarCalendarDay = 0;
        LunarCalendar(year,month,day);
        return (LunarCalendarDay & 0x3F);
    }

};
struct Chn_Info
{
	QString devceId;
	QString netUser;
	QString pwd;

	bool state;
	QRect location;
	char ystGroup;
	unsigned ystNo;
	Chn_Info():state(false){}

};
#endif

extern int m_width;
extern int m_height;
extern int m_userlevel;
extern QString m_curruser;
extern int m_poiilingtime;
extern int m_presetpolltime;
extern bool m_isPoiiling;
extern bool m_chnState[8];



extern Chn_Info g_chnInfo[8];
