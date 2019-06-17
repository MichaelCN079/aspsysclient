/****************************************************

	Copyright (C), 2014-2015, Jovision Tech. Co., Ltd. 
	File name		:	VideoPlayer.h
	Author			:	刘训凯   
	Version			:	3.1.0.0
	Date			:	2014-11-25
	Description		:	视频控件导出接口
	
	Export Function List:
	  1.Player_Init					:	初始化视频控件
	  2.Player_Release				:	释放视频控件
	  3.Player_SetLanguage			：  设置使用的语言
	  4.Player_SetStorePath			：	设置录像文件的存储目录
	  5.Player_SetPicPath			:	设置图片的存储目录
	  6.Player_SetRecConfig			:	设置录像的相关配置
	  7.Player_GetLanDevice			:	获取局域网设备
	  8.Player_Command				:	命令
	  9.Player_GetDeviceInfo		:	获取设备信息
	  10.Player_RegDeviceCall		:	注册获取设备信息的回调
		 
	Export Class：
	 CVideoPlayer Function List:
	  1.SetDisplayRect				:	设置当前播放器的显示区域
	  2.RegisterCallback			：	注册回调
	  2.1RegisterRecordCallBack		:	注册录像回调
	  3.EnablePlayBar				:	启用回放控制条
	  4.Paint						:	绘制背景
	  5.DividWindow					:	分屏
	  6.WindowMoved					:	窗体移动
	  7.MouseEvent					:	鼠标事件
	  8.MouseZoom					:	视频缩放
	  9.Connect						:	连接视频
	  10.Disconnect					:	断开连接
	  11.DisconnectAll				:	断开所有连接
	  12.CleanChnInfo				:	清理通道信息
	  13.RemoteVideoCheck			:	远程检索
	  14.RemoteVideoPlay			:	远程回放
	  15.LocalVideoCheck			:	本地录像检索
	  15.LocalVideoPlay				:	本地文件播放
	  16.PlayBackCtrl				:	回放控制
	  17.PlayBackSeekToFrame		:	回放 定位到某一关键帧
	  18.PlayStepForward			:	本地回放单帧播放
	  19.GetPlaySpeed				:	获取本地回放的播放速度
	  20.CanDownLoadFile			:	验证是否可以下载文件
	  21.DownLoadFile				:	下载远程文件
	  22.StopDownFile				:	停止下载文件
	  23.ChannelCtrl				:	通道控制，包含录像、对讲、声音、报警
	  24.VideoCapture				:	视频抓拍
	  25.RemoteConfig				:	远程设置
	  26.CameraCtrl					:	镜头控制
	  27.RecordAll					:	全部通道录像控制
	  28.GetChannelState			:	获取通道的当前状态
	  29.GetSelectedIndex			:	获取当前选择的窗口
	  30.GetWindowNum				:	获取当前分屏数
	  31.GetCurrentChnInfos			:	获取当前分屏的所有通道信息
	  31.GetCurrentRects			:	获取当前分屏的位置信息
	  32.PtzConfig					:	设置云台设置状态
	  33.AddPreset					:	增加预置位
	  34.DelPreset					:	删除预置位
	  35.CallPreset					:	调用预置位
	  36.AddPatrol					:	增加预置位到巡航线
	  37.DelPatrol					:	删除巡航线中的预置位
	  38.StartPatrol				:	开始巡航
	  39.StopPatrol					:	停止巡航
	  40.ConnectPollChn				:	连接轮显视频
	  41.SetPollingState			:	设置轮显状态
	  42.SetBorderStyle				:	设置边框样式
	  43.SetChannelBitmap			:	设置通道背景
	  44.SetFontSize				:	设置通道字体大小
	  45.SetAlarmVideoMode			:	设置为报警视频模式
	  46.GetRecordFileName			:	获取当前录像的名称
	  47.SetRecordTimerMode			:	设置定时录像模式
		 
	 History:	 
	  1.Date		:	2013-12-31
	    Author		:	刘训凯
	    Modification:	创建视频控件导出接口
	  2.Date		:	2014-05-19
	    Author		:	刘训凯
	    Modification:	1.优化接口
						2.增加预置位的功能接口
	  3.Date		:	2014-05-22
	    Author		:	刘训凯
	    Modification:	1.获取本地设备时，增加设备协议的过滤
	  4.Date		:	2014-05-26
	    Author		:	刘训凯
	    Modification:	1.增加清理通道信息的接口CleanChnInfo
						2.增加本地回放的单帧播放功能接口 PlayStepForward
	  5.Date		:	2014-07-03
	    Author		:	刘训凯
	    Modification:	1.增加视频轮显的接口 ConnectPollChn SetPollingState
						2.优化断开所有通道连接的接口，删除了接口参数
						3.增加设置通道边框和背景以及连接动画样式的接口功能
	  6.Date		:	2014-07-16
	    Author		:	刘训凯
	    Modification:	1.增加获取本地回放速度 GetPlaySpeed的接口
	  7.Date		:	2014-07-31
	    Author		:	刘训凯
	    Modification:	1.增加手动增加onvif设备的接口(Player_AddOnvifDevice)
						2.增加启用自动重连通道的接口（Player_EnableReconnect）
	  8.Date		:	2014-09-23
	    Author		:	刘训凯
	    Modification:	1.增加禁用视频转发的接口(Player_DisableTurn)
	  9.Date		:	2014-11-18
	    Author		:	刘训凯
	    Modification:	1.增加获取设备信息的接口(Player_GetDeviceInfo)
	  10.Date		:	2014-11-25
	    Author		:	刘训凯
	    Modification:	1.去掉助手的相关接口
						2.优化通道的结构体信息(ST_ChnInfo)
						3.优化视频连接的接口参数
						4.去掉增加onvif设备的接口
						5.将禁用转发和启用自动重连接口合并到命令接口中
	  11.Date		:	2015-01-08
	    Author		:	刘训凯
	    Modification:	1.命令中增加 CMD_ENABLENETSCAN，用来启用局域网广播的服务，如需要获取局域网
						的设备信息，必须先调用此命令
	  12.Date		:	2015-02-05
	    Author		:	刘训凯
	    Modification:	1.增加设置通道打印信息字体大小的接口SetFontSize
	  13.Date		:	2015-06-02
	    Author		:	刘训凯
	    Modification:	1.增加将一个播放模块设置为报警视频模式的功能
	  13.Date		:	2015-06-24
	    Author		:	刘训凯
	    Modification:	1.优化录像存储的相关接口(Player_SetStorePath、Player_SetPicPath、Player_SetRecConfig),
						并增加定时录像的接口(SetRecordTimerMode)
	  14.Data		:	2015-07-10
	    Author		:	刘训凯
		Modification:	1.Player_Command 中增加CMD_HIDEVIDEOICON用来隐藏视频的状态图标
						2.增加GetCurrentRects接口，可获取当前各个分屏的位置信息
						
						
	
****************************************************/ 

#pragma once

#define Player_C_API extern "C" __declspec(dllexport)

#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif
	
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include <Windows.h>

/*分屏类型*/
#ifndef SPLITNUM_DEF
#define SPLITNUM_DEF
enum SplitNum
{
	SN_1 = 1,
	SN_4 = 4,
	SN_9 = 9,
	SN_16 = 16,
	SN_25 = 25,
	SN_36 = 36,
	SN_64 = 64,
};
#endif;

/*连接类型*/
enum LinkType
{
	LT_NONE = -1,
	LT_NORMAL,
	LT_SLIDESHOW
};

/*设备协议类型*/
enum DeviceProtocolType
{
	DPT_CLOUD,
	DPT_ONVIF,
	DPT_EXTERNAL
};

/*设备类型*/
#ifndef DEVICETYPE_DEF
#define DEVICETYPE_DEF
enum DeviceType
{
	DT_Unknown = -1,
	DT_CARD,
	DT_HARDCARD,
	DT_DVR,
	DT_IPC,
	DT_NVR,
	DT_JNVR
};
#endif;

/*回放控制类型*/
enum PlayBackCtrlType
{
	PBCT_PLAY,
	PBCT_PAUSE,
	PBCT_STOP,
	PBCT_SLOW,
	PBCT_SPEED
};

/*连接返回状态*/
enum ConnectState
{
	CS_NOCONN = 0,		//没有连接
	CS_CONNECTING,		//连接中
	CS_CONNOK,			//连接成功
	CONNERR,			//连接失败
	DISOK,				//断开连接成功
	CS_DISCON,			//连接异常断开
	CS_SSTOP,			//服务停止
	CS_OTHER,
	CS_DISCONNECTING	//开始断开
};

/*通道控制类型*/
enum ChannelCtrlType
{
	CC_RECORD,			/*通道录像控制*/
	CC_TALKBACK,		/*通道对讲控制*/
	CC_AUDIO,			/*通道声音控制*/
	CC_ALARMSOUND,		/*通道报警控制*/
	CC_ALARMSIGNAL,		/*所有通道报警信号控制*/
	CC_COUNT
};

/*轮显状态*/
#ifndef POLLINGSTATE_DEF
#define POLLINGSTATE_DEF
typedef enum PollingState
{
	POLL_STOP = 0,
	POLL_START,
	POLL_PAUSE
} PollingState_t;
#endif;


/*通道状态*/
enum ChannelState
{
	CHS_NOUSE = 0,
	CHS_PREVIWING = 1,
	CHS_REMOTING = 2,
	CHS_LOCALPLAYING = 4,
	CHS_RECORDING = 8,
	CHS_ALARMING = 16,
	CHS_SOUNDING = 32,
	CHS_TALKING = 64,
	CHS_ENABLEALARM = 128
};

/*鼠标事件类型*/
enum MouseEventType
{
	MET_LBUTTONDOWN,
	MET_LBUTTONUP,
	MET_LBUTTONDBLCLK,
	MET_RBUTTONUP
};	  

/*命令类型*/
enum CommandType
{
	CMD_RESETPLAYSDK = 1,		/*重新初始化播放sdk*/
	CMD_DISABLETURN,			/*禁用转发*/
	CMD_ENABLERECONNECT,		/*启用自动重连机制*/
	CMD_ENABLENETSCAN,			/*启用局域网广播，将影响获取局域网设备的功能*/
	CMD_HIDEVIDEOICON,			/*隐藏视频上的状态图标*/
	CMD_COUNT
};

#pragma region 预置点相关定义

#define MAX_PATROL_NOD	256
#define MAX_PRESET_CT	256	//预置点最大个数

typedef enum PARITYBIT_ENUM
{
	PAR_NONE = 0,
	PAR_EVEN,
	PAR_ODD
} tParityBit_e;

typedef enum
{
	PTZ_DATAFLOW_NONE = 0,
	PTZ_DATAFLOW_HW,
	PTZ_DATAFLOW_SF

}tPtzDataFlow_e;

typedef struct tagPORTPARAMS
{
	int		nBaudRate;      // BAUDRATE_ENUM
	int		nCharSize;      // CHARSIZE_ENUM
	int		nStopBit;       // STOPBIT_ENUM
	tParityBit_e	nParityBit;     // PARITYBIT_ENUM
	tPtzDataFlow_e	nFlowCtl;       // Flow Control type(1/0)
} NC_PORTPARAMS, *PNC_PORTPARAMS;

typedef enum
{
	PTZ_PROTOCOL_HUIXUN = 1,
	PTZ_PROTOCOL_STD_PELCOP = 4,
	PTZ_PROTOCOL_YAAN = 28,
	PTZ_PROTOCOL_STD_PELCOD = 29,
	PTZ_PROTOCOL_SHUER_PELCOD=30 ,
	PTZ_PROTOCOL_MAX
}PtzProtocol_e;

typedef struct tagPTZinfo
{
	PtzProtocol_e nProtocol;
	int			  naddress;
	NC_PORTPARAMS nHwParams;
}tPTZhwinfo;

#define PTZ_CNT	1
//云台结构体
typedef struct _PATROL_NOD
{
	UINT nPreset;      //预置点数组下标
	UINT nStayTime;    //停留时间
}PATROL_NOD, *PPATROL_NOD;

//云台结构体
typedef struct _PTZ
{
	UINT          nAddr;                      //地址
	UINT          nProtocol;                  //协议
	UINT          nBaudRate;                  //波特率,数据位,停止位等
	NC_PORTPARAMS nHwParams;
	BOOL            bLeftRightSwitch;           //左右互换
	BOOL            bUpDownSwitch;              //上下互换
	BOOL            bIrisZoomSwitch;            //光圈变倍互换
	BOOL            bFocusZoomSwitch;           //变焦变倍互换
	BOOL            bZoomSwitch;                //变倍互换
	UINT		scanSpeed;	//线扫速度
}PTZ, *PPTZ;

//预置点信息
typedef struct
{
	UINT			nPresetCt;						//预置点个数
	UINT			pPreset[MAX_PRESET_CT];			//预置点数组
	char			name[MAX_PRESET_CT][32];		//预置点名称
}PTZ_PRESET_INFO;

//巡航信息
typedef struct
{
	UINT         nPatrolSize;                //巡航包含的预置点数
	PATROL_NOD  aPatrol[MAX_PATROL_NOD];    //巡航
}PTZ_PATROL_INFO;

typedef enum
{
	GUARD_NO,
	GUARD_PRESET,
	GUARD_PATROL,
	GUARD_TRAIL,
	GUARD_SCAN,
}PTZ_GUARD_TYPE_E;

//守望信息
typedef struct
{
	UINT guardTime;		//守望时间。0表示守望关闭
	PTZ_GUARD_TYPE_E guardType;
	union
	{
		UINT nRreset;
		UINT nPatrol;;
		UINT nTrail;
		UINT nScan;
	};
}PTZ_GUARD_T;

//云台控制状态
typedef struct
{
	UINT 		bootItem;			//开机启动项

}PTZ_STATUS;

typedef struct
{
	PTZ stPtz[PTZ_CNT];//每个通道的云台结构
	PTZ_PRESET_INFO stPreInf[PTZ_CNT]; 	//预置点信息
	PTZ_PATROL_INFO stPatrolInf[PTZ_CNT];	//巡航信息
	PTZ_GUARD_T stGuard[PTZ_CNT];
	PTZ_STATUS stPtzStatus[PTZ_CNT];
} PTZ_INFO_T;

#pragma endregion


/*设备信息*/
#ifndef ST_DEVICE_DEF
#define ST_DEVICE_DEF
typedef struct _ST_Device
{
	char szDeviceName[100];
	char szServerIP[17];
	int nServerPort;
	char szCloudNum[17];		//云视通号码， 如开头字母为'N'则是onvif协议的设备
	char szNetUser[32];
	char szNetPwd[32];
	int nChnCount;
	DeviceType type;
	BOOL bHasWifi;
	BOOL bUseWifi;
	BOOL bOnline;
}ST_Device, *PST_Device;
#endif;

/*连接通道*/
#ifndef ST_CHNINFO_DEF
#define ST_CHNINFO_DEF
typedef struct _ST_ChnInfo
{
	char szDeviceName[100];
	char szServerIP[17];
	int nServerPort;
	char szCloudNum[17];		//云视通号码， 如开头字母为'N'则是onvif协议的设备
	char szNetUser[32];
	char szNetPwd[32];
	int nChnIndex;
	int nLocalIndex;
}ST_ChnInfo, *PST_ChnInfo;
#endif;

/*远程录像文件*/
typedef struct _ST_RemoteVideo	
{
	char			szCloudNum[17];	//云视通号或ip地址
	char			acSecuCh[3];	//通道号
	char			acRedDay[9];	//录像日期
	char			acRecTimeS[7];	//录像时间
	char			acRecTimeE[7];	//录像时间
	char			cDisk;			//所在盘符
	char			cRecType;		//录像类型
}ST_RemoteVideo, *PST_RemoteVideo;

/*本地录像*/
typedef struct _RecordConfig
{
	char	devid[20];		//设备号
	int		chnid;			//通道号
	char	day[20];		//日期 格式：yyyyMMdd
	char	time[20];		//时间 格式: hh:mm:ss
	char	path[256];		//视频
	char	pic[256];		//缩略图
	char	type[50];		//类型：normal,alarm,timer
	int		frate;			//帧率
	char	endtime[20];	//结束时间 格式：hh:mm:ss
} RecordConfig, *PRecordConfig;


/*下载进度*/
typedef struct _ST_DOWNLOADRATE
{
	char	szFile[MAX_PATH];
	long	nFileLen;
	long	nDownLen;
}ST_DOWNLOADRATE, *PST_DOWNLOADRATE;

/*连接返回状态回调*/
typedef void (*FUNC_CONNECT_CALLBACK)(void* param, PST_ChnInfo pChnInfo, ConnectState connState); 
/*通道状态回调*/
typedef void (*FUNC_CHNSTATE_CALLBACK)(void* param, PST_ChnInfo pChnInfo, DWORD state);	
/*日志信息*/
typedef void (*FUNC_LOGINFO_CALLBACK)(void* param,int msgType, char* pMsg);	//
/*远程检索回调*/
typedef void (*FUNC_GETREMOTEVIDEO_CALLBACK)(void* param, const PST_RemoteVideo pRemoteVideo, int nSize);
/*返回回放进度*/
typedef void (*FUNC_PLAYBACKRATE_CALLBACK)(void* param, int nLocalIndex, ULONG ulFrame, ULONG ulTotalFrame,ULONG ulMiliSec, ULONG ulTotalMiliSec);	
/*远程下载进度*/
typedef void (*FUNC_DOWNLOADRATE_CALLBACK)(void* param, PST_DOWNLOADRATE downRate);	
/*预置位参数回调*/
typedef void (*FUNC_GETYTPARA_CALLBACK)(void* param, PTZ_INFO_T* pData);
/*查询设备信息回调*/
typedef void (*FUNC_GETDEVICEINFO_CALLBACK)(void* param, PST_Device pDevice);
/*获取到metadata后回调*/
typedef void (*FUNC_METADATA_CALLBACK)(void* param,int nTotalMiliSec);
/*rtmp回放时收到设备ready帧后回调*/
typedef void (*FUNC_CUSTOMFRAME_CALLBACK)(void* param,const char* pData,int nSize);
/*录像信息回调*/
typedef void (*FUNC_RECORDINFO_CALLBACK)(void *param, int nLocalIndex, PST_ChnInfo pChnInfo, char *recname);

/************************************************* 

	Function		:	Player_Init 
	Description		:	初始化视频控件
	Input:       
		1.[HWND]		hwnd 主程序的句柄 
	Output			:	无
	Return			:	无
	Others			:	无
	
*************************************************/ 
Player_C_API void __stdcall Player_Init(HWND hwnd);

/************************************************* 

	Function		:	Player_Release 
	Description		:	释放视频控件
	Input			:	无			
	Output			:	无
	Return			:	无
	Others			:	无
	
*************************************************/ 
Player_C_API void __stdcall Player_Release(void);

/************************************************* 

	Function		:	Player_SetLanguage 
	Description		:	设置使用的语言
	Input:       
		1.[char*]		pLanguage 程序当前使用的语言 如中文为:zh-CN,英文为：en-US
	Output			:	无
	Return			:	无
	Others			:	无
	
*************************************************/ 
Player_C_API void __stdcall Player_SetLanguage(char* pLanguage);

/************************************************* 

	Function		:	Player_SetStorePath 
	Description		:	设置录像文件的存储目录
	Input:       
		1.[char*]		pPath1	目录名称
	Output			:	无
	Return			:	无
	Others			:	多个路径时，建议每个盘取一个路径，真实的录像路径为：pPath1/recordfiles/
	
*************************************************/ 
Player_C_API void __stdcall Player_SetStorePath(char *pPath1, 
	char *pPath2 = NULL, 
	char *pPath3 = NULL, 
	char *pPath4 = NULL, 
	char *pPath5 = NULL);

/************************************************* 

	Function		:	Player_SetPicPath 
	Description		:	设置图片的存储目录
	Input:       
		1.[char*]		pPath	目录名称
		1.[BOOL]		bJPEG	是否存储为JPG格式
	Output			:	无
	Return			:	无
	Others			:	无
	
*************************************************/ 
Player_C_API void __stdcall Player_SetPicPath(char *pPath, BOOL bJPEG); 

/************************************************* 

	Function		:	Player_SetRecConfig 
	Description		:	设置录像的相关配置
	Input:       
		1.[int]			nDuration	录像时长
		2.[BOOL]		bCover		磁盘满是否覆盖
		3.[int]			nDelDays	磁盘满时，删除最早几天的录像，bCover为TRUE时，起作用
		3.[int]			headspace	磁盘预留空间，默认为1000m
	Output			:	无
	Return			:	无
	Others			:	headspace最小为1000m
	
*************************************************/ 
Player_C_API void __stdcall Player_SetRecConfig(int nDuration, BOOL bCover, int nDelDays, int headspace = 1000);


/************************************************* 

	Function		:	Player_GetLanDevice 
	Description		:	获取局域网设备
	Input:       
		1.[int&]				nCount		设备的数量
		2.[DeviceProtocolType]	devProtType 设备协议类型
	Output			:	返回查找到设备的数目
	Return			:	ST_Device数组首地址
	Others			:	如需获取局域网设备，则程序启动时，需启用局域网广播服务 CMD_ENABLENETSCAN
	
*************************************************/ 
Player_C_API PST_Device __stdcall Player_GetLanDevice(int &nCount, DeviceProtocolType devProtType= DPT_CLOUD);

/************************************************* 

	Function		:	Player_Command 
	Description		:	发送控制命令
	Input:       
		1.[CommandType]		cmdType		命令类型
	Output			:	无
	Return			:	无
	Others			:	无
	
*************************************************/ 
Player_C_API void __stdcall Player_Command(CommandType cmdType);

/************************************************* 

	Function		:	Player_GetDeviceInfo 
	Description		:	获取设备信息
	Input			:   无    
	Output			:	无
	Return			:	无
	Others			:	如需获取局域网设备，则程序启动时，需启用局域网广播服务 CMD_ENABLENETSCAN
	
*************************************************/ 
Player_C_API ST_Device __stdcall Player_GetDeviceInfo(char *szCloudNum, BOOL bSync = TRUE);

/*
*	注册获取设备信息的回调
*/
Player_C_API void __stdcall Player_RegDeviceCall(void *param, FUNC_GETDEVICEINFO_CALLBACK event);








/*视频显示控制类*/
class PLAYER_API CVideoPlayer
{
public:
	CVideoPlayer(void);
	~CVideoPlayer(void);

public:	
	
	/************************************************* 

		Function		:	SetDisplayRect 
		Description		:	设置当前播放器的显示区域
		Input:       
			1.[HWND]		hwndParent 当前播放器的句柄 
			2.[LPRECT]		lpRect 显示区域
		Output			:	无
		Return			:	无
		Others			:	必须调用
	
	*************************************************/ 			
	void SetDisplayRect(HWND hwndParent, LPRECT lpRect);
	
	/************************************************* 

		Function		:	SetBorderStyle 
		Description		:	设置边框样式
		Input:       
			1.[COLORREF]		clrNormal	未选择的颜色
			2.[COLORREF]		clrSelected 选择后的颜色
            3.[int]             nBorderLineWidth  边框宽度 单位:像素
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void SetBorderStyle(COLORREF clrNormal, COLORREF clrSelected,int nBorderLineWidth);
	
	/************************************************* 

		Function		:	SetChannelBitmap 
		Description		:	设置通道背景
		Input:       
			1.[HMODULE]		hModule			图片资源所在模块
			2.[UINT]		nbitmap			图片的资源编号
			2.[UINT]		nLoadingResID	连接动画的资源ID，png格式
			2.[int]			nSize			连接动画的大小，高度和宽度的值
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	
	void SetChannelBitmap(HMODULE hModule, UINT nbitmap, UINT nLoadingResID = 0, int nSize = 0);
	
    /************************************************* 

		Function		:	SetChannelColor 
		Description		:	设置通道背景颜色
		Input:       
			1.[COLORREF]	clrBackGround	通道背景色
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void SetChannelColor(COLORREF clrBackGround);

	/************************************************* 

		Function		:	SetFontSize 
		Description		:	设置通道字体大小
		Input:       
			1.[int]			nFontSize		通道显示的字体大小
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void SetFontSize(int nFontSize = 14);


	/************************************************* 

		Function		:	RegisterCallback 
		Description		:	注册回调函数
		Input:       
			1.[void*]							param 保存的参数，回调时传出 
			2.[FUNC_CONNECT_CALLBACK]			connectCallBack		连接状态回调
			3.[FUNC_CHNSTATE_CALLBACK]			chnStateCallBack	通道状态回调
			4.[FUNC_LOGINFO_CALLBACK]			logInfoCallBack		日志信息回调
			5.[FUNC_GETREMOTEVIDEO_CALLBACK]	remoteVideoCallback		远程视频检索回调
			6.[FUNC_PLAYBACKRATE_CALLBACK]		playBackRateCallBack	回放进度回调
			7.[FUNC_DOWNLOADRATE_CALLBACK]		downRateCallBack		下载进度回调
			8.[FUNC_GETYTPARA_CALLBACK]			func_GetYtPara_CallBack	
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void RegisterCallback(void* param, FUNC_CONNECT_CALLBACK connectCallBack,
										FUNC_CHNSTATE_CALLBACK chnStateCallBack,
										FUNC_LOGINFO_CALLBACK logInfoCallBack,
										FUNC_GETREMOTEVIDEO_CALLBACK remoteVideoCallback, 
										FUNC_PLAYBACKRATE_CALLBACK playBackRateCallBack,
										FUNC_DOWNLOADRATE_CALLBACK downRateCallBack,
                                        FUNC_METADATA_CALLBACK metadataCallBack=NULL,
                                        FUNC_CUSTOMFRAME_CALLBACK customFrameCallBack=NULL,
										FUNC_GETYTPARA_CALLBACK func_GetYtPara_CallBack = NULL,
										FUNC_RECORDINFO_CALLBACK recordCallBack = NULL);
	

	/************************************************* 

		Function		:	EnablePlayBar 
		Description		:	启用回放控制条
		Input			:   无    
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 	
	void EnablePlayBar(void);

	/************************************************* 

		Function		:	Paint 
		Description		:	绘制背景
		Input:   
			1.[HDC]			hdc 当前播放器所依赖句柄的设备环境
		Output			:	无
		Return			:	无
		Others			:	在播放器所依赖窗体的OnPaint事件中调用
	
	*************************************************/ 
	void Paint(HDC hdc);

	/************************************************* 

		Function		:	DividWindow 
		Description		:	分割屏幕
		Input:   
			1.[SplitNum]	num 分屏屏幕的数目
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void DividWindow(SplitNum num);

	/************************************************* 

		Function		:	WindowMoved 
		Description		:	窗体移动事件
		Input			:   无
		Output			:	无
		Return			:	无
		Others			:	用于重新指定视频显示区域，窗体移动时，必须调用
	
	*************************************************/ 
	void WindowMoved(void);

	/************************************************* 

		Function		:	MouseEvent 
		Description		:	鼠标事件
		Input:   
			1.[MouseEventType]	meType 鼠标事件类型
			2.[POINT&]			point 鼠标的坐标
		Output			:	无
		Return			:	无
		Others			:	鼠标单击事件 触发分屏选择， 双击事件触发分屏的单屏显示， 
							右键触发默认的通道菜单
	
	*************************************************/ 
	void MouseEvent(MouseEventType meType, POINT &point);

	/************************************************* 

		Function		:	MouseZoom 
		Description		:	视频缩放
		Input:   
			1.[POINT]		pt		鼠标滚动事件的坐标
			2.[BOOL]		bZoomIn	变大或变小 依据鼠标滚动事件而定
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/ 
	void MouseZoom(POINT pt, BOOL bZoomIn);


	/************************************************* 

		Function		:	Connect 
		Description		:	连接视频通道
		Input:   
			1.[ST_ChnInfo&] chnInfo 通道信息
		Output			:	无
		Return			:	是否发生连接请求成功
		Others			:	连接结果会通过FUNC_CONNECT_CALLBACK 回调告知应用层
	
	*************************************************/
	bool Connect(ST_ChnInfo & chnInfo, char* strURL = NULL);

	/************************************************* 

		Function		:	Disconnect 
		Description		:	断开通道连接
		Input:   
			1.[int]			nLocalIndex 断开的本地通道， 如为0，则是当前选择通道
		Output			:	无
		Return			:	无
		Others			:	本地通道号从1开始
	
	*************************************************/
	void Disconnect(int nLocalIndex = 0);

	/************************************************* 

		Function		:	DisconnectAll 
		Description		:	断开所有连接
		Input			
			1.[BOOL]		bClear 是否清除通道信息
		Output			:	无
		Return			:	无
		Others			:	此接口只对预览视频有效。
	
	*************************************************/
	void DisconnectAll(BOOL bClear = TRUE);
	
	/************************************************* 

		Function		:	CleanChnInfo 
		Description		:	清理通道信息
		Input:   
			1.[int]				nLocalIndex 本地窗口号，从1开始
		Output			:	无
		Return			:	无
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	void CleanChnInfo(int nLocalIndex = 0);

    /************************************************* 

		Function		:	EnablePreDecode 
		Description		:	启用预解码(默认开启，预解码会造成图像播放延后一帧，以此带来流畅度的提升)
                            主要用于回放模式帧定位图像刷新问题 打开播放器后的第一次定位某关键帧时 图像会不刷新 此时可禁用预解码解决
		Input:   
			1.[int]				nLocalIndex 本地窗口号，从1开始
            2.[BOOL]            bEnable TRUE为启用预解码
		Output			:	无
		Return			:	无
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	void EnablePreDecode(BOOL bEnable,int nLocalIndex = 0);

	/************************************************* 

		Function		:	RemoteVideoCheck 
		Description		:	远程检索
		Input:   
			1.[char*]		pDay 检索的日期 如：20131231
			2.[PST_ChnInfo] pChnInfo 远程检索的通道信息，如不为NULL, 则先去连接此通道，然后再检索
		Output			:	无
		Return			:	无
		Others			:	pChnInfo不为NULL时，由FUNC_CONNECT_CALLBACK返回连接状态，
							由FUNC_GETREMOTEVIDEO_CALLBACK返回检索结果
	
	*************************************************/
	void RemoteVideoCheck(char* pDay, PST_ChnInfo pChnInfo = NULL);	

	/************************************************* 

		Function		:	RemoteVideoPlay 
		Description		:	远程回放
		Input:   
			1.[PST_RemoteVideo]		pRemoteVideo需要回放的远程文件信息
			2.[BOOL]				bConnect 如果未TRUE时，则当当前选择的分屏非此设备的连接通道时，
											则先去连接，然后回放
			3.[PST_ChnInfo]			pChnInfo 远程文件对应的通道信息
		Output			:	无
		Return			:	无
		Others			:	如连接时，会返回连接状态回调，和回放日志信息
							pChnInfo 只在 bConnect 为TRUE时有效
	
	*************************************************/
	void RemoteVideoPlay(PST_RemoteVideo pRemoteVideo, BOOL bConnect = FALSE, PST_ChnInfo pChnInfo = NULL);	

	/************************************************* 

		Function		:	LocalVideoPlay 
		Description		:	本地文件回放
		Input:   
			1.[char*]		pFileName本地视频文件的全路径名
			2.[int]				nLocalIndex 本地窗口号，从1开始
		Output			:	无
		Return			:	是否播放成功
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	bool LocalVideoPlay(char* pFileName, int nLocalIndex = 0);

	/*
	*	本地录像检索
	*	日期格式为:yyyyMMdd
	*	type为：normal,alarm,timer ,NULL为所有
	*/
	PRecordConfig LocalVideoCheck(char *devid, int chnid, char *day, char *type, int &count);

	/************************************************* 

		Function		:	PlayBackCtrl 
		Description		:	回放控制
		Input:   
			1.[PlayBackCtrlType]	ctrlType回放控制类型，如暂停、播放、停止等
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void PlayBackCtrl(PlayBackCtrlType ctrlType);

	/************************************************* 

		Function		:	PlayBackSeekToFrame 
		Description		:	定位到某一关键帧
		Input:   
			1.[ULONG]		ulCurrentFrame 关键帧数字
		Output			:	无
		Return			:	当前帧
		Others			:	无
	
	*************************************************/
	ULONG PlayBackSeekToFrame(ULONG ulCurrentFrame);
	
	/************************************************* 

		Function		:	PlayStepForward 
		Description		:	本地回放单帧播放
		Input:
			1.[int]				nLocalIndex 本地窗口号，从1开始
		Output			:	无
		Return			:	调用成功或失败
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	BOOL PlayStepForward(int nLocalIndex = 0);
	
	/************************************************* 

		Function		:	GetPlaySpeed 
		Description		:	获取本地回放的速度
		Input:
			1.[int]				nLocalIndex 本地窗口号，从1开始
		Output			:	无
		Return			:	回放速度 = 2^(返回值)
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	int GetPlaySpeed(int nLocalIndex = 0);

	/************************************************* 

		Function		:	CanDownLoadFile 
		Description		:	验证是否可以下载文件
		Input:   
			1.[char *]			pExtName 文件扩展名称
			2.[PST_RemoteVideo] pRemoteVideo 远程文件
		Output			:	无
		Return			:	是否可以下载
		Others			:	无
	
	*************************************************/
	bool CanDownLoadFile(char *pExtName, PST_RemoteVideo pRemoteVideo);

	/************************************************* 

		Function		:	DownLoadFile 
		Description		:	下载远程文件
		Input:   
			1.[LPCSTR]			lpszFileName 本地文件名称
			2.[PST_RemoteVideo] pRemoteVideo 远程文件
		Output			:	无
		Return			:	是否可以下载
		Others			:	无
	
	*************************************************/
	bool DownLoadFile(LPCSTR lpszFileName);

	/************************************************* 

		Function		:	StopDownFile 
		Description		:	停止下载文件
		Input			:   无
		Output			:	无
		Return			:	是否可以下载
		Others			:	无
	
	*************************************************/
	void StopDownFile(void);

	/************************************************* 

		Function		:	ChannelCtrl 
		Description		:	回放控制
		Input:
			1.[ChannelCtrlType] ccType回放控制类型，如暂停、播放、停止等
			2.[BOOL]			bEnable
			3.[int]				nLocalIndex 本地窗口号，从1开始
		Output			:	无
		Return			:	无
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	void ChannelCtrl(ChannelCtrlType ccType, BOOL bEnable, int nLocalIndex = 0);

	/************************************************* 

		Function		:	VideoCapture 
		Description		:	视频抓拍
		Input:
			1.[int] nLocalIndex 本地通道
		Output			:	无
		Return			:	抓图路径名
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	char* VideoCapture(int nLocalIndex = 0);

	/************************************************* 

		Function		:	RemoteConfig 
		Description		:	远程设置
		Input:
			1.[int]			nLocalIndex 本地通道
		Output			:	无
		Return			:	无
		Others			:	窗口号为0时，针对当前窗口
	
	*************************************************/
	void RemoteConfig(int nLocalIndex = 0);

	/************************************************* 

		Function		:	CameraCtrl 
		Description		:	镜头控制
		Input:
			1.[UINT]		nType 1,2,3,4,5,6 分表标示光圈,焦距，倍数,云台, 辅助1,辅助2
			2.[BOOL]		bFlags  TRUE标示按下， FALSE标示抬起
			3.[UINT]		nKind 1,2分表标示 -，+
			4.[BYTE]		bSpeed 转动速度
		Output			:	无
		Return			:	无
		Others			:	当控制云台时， nKink取值为1,2,3,4,5分别表示上,下,左,右,自动
							当为辅助功能时，bFlags 代表开启或关闭， nKind 无效
							针对当前选择通道
	
	*************************************************/
	void CameraCtrl(UINT nType, BOOL bFlags, UINT nKind, BYTE bSpeed = 0, int nLocalIndex = 0);

	/************************************************* 

		Function		:	RecordAll 
		Description		:	全部通道的录像
		Input:
			1.[BOOL]		bStart 是否全部录像
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void RecordAll(BOOL bStart);

    /************************************************* 

		Function		:	PausePlayBackRateCallBack 
		Description		:	暂停当前回放进度回调
		Input:
			1.[int]			nLocalIndex	   本地通道
		Output			:	无
		Return			:	无
	
	*************************************************/
	void PausePlayBackRateCallBack(int nLocalIndex = 0);

    /************************************************* 

		Function		:	SetChannelInfo 
		Description		:	设置当前通道信息
		Input:
			1.[ST_ChnInfo]	chnInfo		   当前通道连接的通道信息
			2.[int]			nLocalIndex	   本地通道
		Output			:	无
		Return			:	无
	
	*************************************************/
	void SetChannelInfo(ST_ChnInfo& chnInfo, int nLocalIndex = 0);

	/************************************************* 

		Function		:	GetChannelState 
		Description		:	获取当前通道的状态
		Input:
			1.[PST_ChnInfo]	pChnInfo		当前通道连接的通道信息
			2.[int]			nLocalIndex		本地通道
		Output			:	无
		Return			:	通道的当前状态 dw, dw和ChannelState中的每一项进行相与，验证是否有此状态，
							如：是否正在预览为 CHS_PREVIWING == (CHS_PREVIWING & dw)
		Others			:	nLocalIndex 为0时，针对当前选择通道
	
	*************************************************/
	DWORD GetChannelState(PST_ChnInfo pChnInfo, int nLocalIndex = 0);

	/************************************************* 

		Function		:	GetSelectedIndex 
		Description		:	获取当前选择的窗口
		Input			:	无
		Output			:	当前选择窗口的区域
		Return			:	无
		Others			:	无
	
	*************************************************/
	int GetSelectedIndex(LPRECT lpRect = NULL);
	

	/************************************************* 

		Function		:	GetWindowNum 
		Description		:	获取当前选择的窗口
		Input			:	无
		Output			:	无
		Return			:	分屏数目
		Others			:	无
	
	*************************************************/
	int GetWindowNum(void);
	
	/************************************************* 

		Function		:	GetCurrentChnInfos 
		Description		:	获取当前分屏的所有通道信息
		Input:
			1.[PST_ChnInfo]	pChnInfo		通道信息数组的指针
		Output			:	无
		Return			:	分屏数目
		Others			:	获取当前所有分屏的数目
	
	*************************************************/
	void GetCurrentChnInfos(PST_ChnInfo pChnInfo);

	/*
	*	获取当前分屏的位置信息
	*	nLocalIndex返回值>0时，代表是某个窗口最大化显示
	*/
	RECT *GetCurrentRects(int &nLocalIndex);

	/************************************************* 

		Function		:	PtzConfig 
		Description		:	设置云台设置状态
		Input:
			1.[int]			nLocalIndex		本地通道
		Output			:	无
		Return			:	无
		Others			:	nLocalIndex 为0时，针对当前选择通道
	
	*************************************************/
	BOOL PtzConfig(int nLocalIndex = 0);

	/************************************************* 

		Function		:	AddPreset 
		Description		:	增加预置位
		Input:
			1.[int]			nPreset 预置位号
			2.[char*]		szName  预置位的名字
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void AddPreset(int nPreset,char* szName);

	/************************************************* 

		Function		:	DelPreset 
		Description		:	删除预置位
		Input:
			1.[int]			nPreset 预置位号
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void DelPreset(int nPreset);

	/************************************************* 

		Function		:	CallPreset 
		Description		:	调用预置位
		Input:
			1.[int]			nPreset 预置位号
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void CallPreset(int nPreset);

	/************************************************* 

		Function		:	AddPatrol 
		Description		:	增加预置位到巡航线
		Input:
			1.[int]			nPreset 预置位号
			2.[int]			nStayTime 在该预置位的停留时间 单位秒
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/	
	void AddPatrol(int nPreset,int nStayTime);

	/************************************************* 

		Function		:	DelPatrol 
		Description		:	删除巡航线中的预置位
		Input:
			1.[int] nPresetIndex 巡航线中预置位的索引而非预置位号
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void DelPatrol(int nPresetIndex);

	/************************************************* 

		Function		:	StartPatrol 
		Description		:	开始巡航
		Input			:	无
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void StartPatrol();

	/************************************************* 

		Function		:	StopPatrol 
		Description		:	停止巡航
		Input			:	无
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void StopPatrol();
	
	/************************************************* 

		Function		:	ConnectPollChn 
		Description		:	连接轮显视频
		Input			
			1.[PST_ChnInfo *]		pChnInfo	通道信息指针
			2.[int]					count		通道数量
			2.[int]					nElapse		轮显时间
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void ConnectPollChn(PST_ChnInfo pChnInfo, int count, int nElapse);
	
	/************************************************* 

		Function		:	SetPollingState 
		Description		:	设置轮显状态
		Input			
			1.[PollingState_t]		pollState 轮显状态
		Output			:	无
		Return			:	无
		Others			:	无
	
	*************************************************/
	void SetPollingState(PollingState_t pollState);

	/*
	*	设置为报警视频模式
	*/
	void SetAlarmVideoMode(BOOL bAutoAlarmVideo);	

	/*
	*	获取当前录像的名称
	*/
	char* GetRecordFileName(int nLocalIndex = 0);

	/*
	*	设置定时录像
	*	sTime和eTime格式为："hh:mm",且时间间隔最少为10分钟
	*	hh为24小时制
	*/
	void SetRecordTimerMode(BOOL bEnable, char *sTime, char *eTime, int nLocalIndex = 0);
	
	/*
	*	设置提示信息
	*/
	void SetMessage(char *msg, int nLocalIndex = 0);
private:
	LPVOID m_pHandle;
};