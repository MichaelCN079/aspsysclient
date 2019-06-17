/****************************************************

	Copyright (C), 2014-2015, Jovision Tech. Co., Ltd. 
	File name		:	VideoPlayer.h
	Author			:	��ѵ��   
	Version			:	3.1.0.0
	Date			:	2014-11-25
	Description		:	��Ƶ�ؼ������ӿ�
	
	Export Function List:
	  1.Player_Init					:	��ʼ����Ƶ�ؼ�
	  2.Player_Release				:	�ͷ���Ƶ�ؼ�
	  3.Player_SetLanguage			��  ����ʹ�õ�����
	  4.Player_SetStorePath			��	����¼���ļ��Ĵ洢Ŀ¼
	  5.Player_SetPicPath			:	����ͼƬ�Ĵ洢Ŀ¼
	  6.Player_SetRecConfig			:	����¼����������
	  7.Player_GetLanDevice			:	��ȡ�������豸
	  8.Player_Command				:	����
	  9.Player_GetDeviceInfo		:	��ȡ�豸��Ϣ
	  10.Player_RegDeviceCall		:	ע���ȡ�豸��Ϣ�Ļص�
		 
	Export Class��
	 CVideoPlayer Function List:
	  1.SetDisplayRect				:	���õ�ǰ����������ʾ����
	  2.RegisterCallback			��	ע��ص�
	  2.1RegisterRecordCallBack		:	ע��¼��ص�
	  3.EnablePlayBar				:	���ûطſ�����
	  4.Paint						:	���Ʊ���
	  5.DividWindow					:	����
	  6.WindowMoved					:	�����ƶ�
	  7.MouseEvent					:	����¼�
	  8.MouseZoom					:	��Ƶ����
	  9.Connect						:	������Ƶ
	  10.Disconnect					:	�Ͽ�����
	  11.DisconnectAll				:	�Ͽ���������
	  12.CleanChnInfo				:	����ͨ����Ϣ
	  13.RemoteVideoCheck			:	Զ�̼���
	  14.RemoteVideoPlay			:	Զ�̻ط�
	  15.LocalVideoCheck			:	����¼�����
	  15.LocalVideoPlay				:	�����ļ�����
	  16.PlayBackCtrl				:	�طſ���
	  17.PlayBackSeekToFrame		:	�ط� ��λ��ĳһ�ؼ�֡
	  18.PlayStepForward			:	���ػطŵ�֡����
	  19.GetPlaySpeed				:	��ȡ���ػطŵĲ����ٶ�
	  20.CanDownLoadFile			:	��֤�Ƿ���������ļ�
	  21.DownLoadFile				:	����Զ���ļ�
	  22.StopDownFile				:	ֹͣ�����ļ�
	  23.ChannelCtrl				:	ͨ�����ƣ�����¼�񡢶Խ�������������
	  24.VideoCapture				:	��Ƶץ��
	  25.RemoteConfig				:	Զ������
	  26.CameraCtrl					:	��ͷ����
	  27.RecordAll					:	ȫ��ͨ��¼�����
	  28.GetChannelState			:	��ȡͨ���ĵ�ǰ״̬
	  29.GetSelectedIndex			:	��ȡ��ǰѡ��Ĵ���
	  30.GetWindowNum				:	��ȡ��ǰ������
	  31.GetCurrentChnInfos			:	��ȡ��ǰ����������ͨ����Ϣ
	  31.GetCurrentRects			:	��ȡ��ǰ������λ����Ϣ
	  32.PtzConfig					:	������̨����״̬
	  33.AddPreset					:	����Ԥ��λ
	  34.DelPreset					:	ɾ��Ԥ��λ
	  35.CallPreset					:	����Ԥ��λ
	  36.AddPatrol					:	����Ԥ��λ��Ѳ����
	  37.DelPatrol					:	ɾ��Ѳ�����е�Ԥ��λ
	  38.StartPatrol				:	��ʼѲ��
	  39.StopPatrol					:	ֹͣѲ��
	  40.ConnectPollChn				:	����������Ƶ
	  41.SetPollingState			:	��������״̬
	  42.SetBorderStyle				:	���ñ߿���ʽ
	  43.SetChannelBitmap			:	����ͨ������
	  44.SetFontSize				:	����ͨ�������С
	  45.SetAlarmVideoMode			:	����Ϊ������Ƶģʽ
	  46.GetRecordFileName			:	��ȡ��ǰ¼�������
	  47.SetRecordTimerMode			:	���ö�ʱ¼��ģʽ
		 
	 History:	 
	  1.Date		:	2013-12-31
	    Author		:	��ѵ��
	    Modification:	������Ƶ�ؼ������ӿ�
	  2.Date		:	2014-05-19
	    Author		:	��ѵ��
	    Modification:	1.�Ż��ӿ�
						2.����Ԥ��λ�Ĺ��ܽӿ�
	  3.Date		:	2014-05-22
	    Author		:	��ѵ��
	    Modification:	1.��ȡ�����豸ʱ�������豸Э��Ĺ���
	  4.Date		:	2014-05-26
	    Author		:	��ѵ��
	    Modification:	1.��������ͨ����Ϣ�Ľӿ�CleanChnInfo
						2.���ӱ��ػطŵĵ�֡���Ź��ܽӿ� PlayStepForward
	  5.Date		:	2014-07-03
	    Author		:	��ѵ��
	    Modification:	1.������Ƶ���ԵĽӿ� ConnectPollChn SetPollingState
						2.�Ż��Ͽ�����ͨ�����ӵĽӿڣ�ɾ���˽ӿڲ���
						3.��������ͨ���߿�ͱ����Լ����Ӷ�����ʽ�Ľӿڹ���
	  6.Date		:	2014-07-16
	    Author		:	��ѵ��
	    Modification:	1.���ӻ�ȡ���ػط��ٶ� GetPlaySpeed�Ľӿ�
	  7.Date		:	2014-07-31
	    Author		:	��ѵ��
	    Modification:	1.�����ֶ�����onvif�豸�Ľӿ�(Player_AddOnvifDevice)
						2.���������Զ�����ͨ���Ľӿڣ�Player_EnableReconnect��
	  8.Date		:	2014-09-23
	    Author		:	��ѵ��
	    Modification:	1.���ӽ�����Ƶת���Ľӿ�(Player_DisableTurn)
	  9.Date		:	2014-11-18
	    Author		:	��ѵ��
	    Modification:	1.���ӻ�ȡ�豸��Ϣ�Ľӿ�(Player_GetDeviceInfo)
	  10.Date		:	2014-11-25
	    Author		:	��ѵ��
	    Modification:	1.ȥ�����ֵ���ؽӿ�
						2.�Ż�ͨ���Ľṹ����Ϣ(ST_ChnInfo)
						3.�Ż���Ƶ���ӵĽӿڲ���
						4.ȥ������onvif�豸�Ľӿ�
						5.������ת���������Զ������ӿںϲ�������ӿ���
	  11.Date		:	2015-01-08
	    Author		:	��ѵ��
	    Modification:	1.���������� CMD_ENABLENETSCAN���������þ������㲥�ķ�������Ҫ��ȡ������
						���豸��Ϣ�������ȵ��ô�����
	  12.Date		:	2015-02-05
	    Author		:	��ѵ��
	    Modification:	1.��������ͨ����ӡ��Ϣ�����С�Ľӿ�SetFontSize
	  13.Date		:	2015-06-02
	    Author		:	��ѵ��
	    Modification:	1.���ӽ�һ������ģ������Ϊ������Ƶģʽ�Ĺ���
	  13.Date		:	2015-06-24
	    Author		:	��ѵ��
	    Modification:	1.�Ż�¼��洢����ؽӿ�(Player_SetStorePath��Player_SetPicPath��Player_SetRecConfig),
						�����Ӷ�ʱ¼��Ľӿ�(SetRecordTimerMode)
	  14.Data		:	2015-07-10
	    Author		:	��ѵ��
		Modification:	1.Player_Command ������CMD_HIDEVIDEOICON����������Ƶ��״̬ͼ��
						2.����GetCurrentRects�ӿڣ��ɻ�ȡ��ǰ����������λ����Ϣ
						
						
	
****************************************************/ 

#pragma once

#define Player_C_API extern "C" __declspec(dllexport)

#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif
	
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include <Windows.h>

/*��������*/
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

/*��������*/
enum LinkType
{
	LT_NONE = -1,
	LT_NORMAL,
	LT_SLIDESHOW
};

/*�豸Э������*/
enum DeviceProtocolType
{
	DPT_CLOUD,
	DPT_ONVIF,
	DPT_EXTERNAL
};

/*�豸����*/
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

/*�طſ�������*/
enum PlayBackCtrlType
{
	PBCT_PLAY,
	PBCT_PAUSE,
	PBCT_STOP,
	PBCT_SLOW,
	PBCT_SPEED
};

/*���ӷ���״̬*/
enum ConnectState
{
	CS_NOCONN = 0,		//û������
	CS_CONNECTING,		//������
	CS_CONNOK,			//���ӳɹ�
	CONNERR,			//����ʧ��
	DISOK,				//�Ͽ����ӳɹ�
	CS_DISCON,			//�����쳣�Ͽ�
	CS_SSTOP,			//����ֹͣ
	CS_OTHER,
	CS_DISCONNECTING	//��ʼ�Ͽ�
};

/*ͨ����������*/
enum ChannelCtrlType
{
	CC_RECORD,			/*ͨ��¼�����*/
	CC_TALKBACK,		/*ͨ���Խ�����*/
	CC_AUDIO,			/*ͨ����������*/
	CC_ALARMSOUND,		/*ͨ����������*/
	CC_ALARMSIGNAL,		/*����ͨ�������źſ���*/
	CC_COUNT
};

/*����״̬*/
#ifndef POLLINGSTATE_DEF
#define POLLINGSTATE_DEF
typedef enum PollingState
{
	POLL_STOP = 0,
	POLL_START,
	POLL_PAUSE
} PollingState_t;
#endif;


/*ͨ��״̬*/
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

/*����¼�����*/
enum MouseEventType
{
	MET_LBUTTONDOWN,
	MET_LBUTTONUP,
	MET_LBUTTONDBLCLK,
	MET_RBUTTONUP
};	  

/*��������*/
enum CommandType
{
	CMD_RESETPLAYSDK = 1,		/*���³�ʼ������sdk*/
	CMD_DISABLETURN,			/*����ת��*/
	CMD_ENABLERECONNECT,		/*�����Զ���������*/
	CMD_ENABLENETSCAN,			/*���þ������㲥����Ӱ���ȡ�������豸�Ĺ���*/
	CMD_HIDEVIDEOICON,			/*������Ƶ�ϵ�״̬ͼ��*/
	CMD_COUNT
};

#pragma region Ԥ�õ���ض���

#define MAX_PATROL_NOD	256
#define MAX_PRESET_CT	256	//Ԥ�õ�������

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
//��̨�ṹ��
typedef struct _PATROL_NOD
{
	UINT nPreset;      //Ԥ�õ������±�
	UINT nStayTime;    //ͣ��ʱ��
}PATROL_NOD, *PPATROL_NOD;

//��̨�ṹ��
typedef struct _PTZ
{
	UINT          nAddr;                      //��ַ
	UINT          nProtocol;                  //Э��
	UINT          nBaudRate;                  //������,����λ,ֹͣλ��
	NC_PORTPARAMS nHwParams;
	BOOL            bLeftRightSwitch;           //���һ���
	BOOL            bUpDownSwitch;              //���»���
	BOOL            bIrisZoomSwitch;            //��Ȧ�䱶����
	BOOL            bFocusZoomSwitch;           //�佹�䱶����
	BOOL            bZoomSwitch;                //�䱶����
	UINT		scanSpeed;	//��ɨ�ٶ�
}PTZ, *PPTZ;

//Ԥ�õ���Ϣ
typedef struct
{
	UINT			nPresetCt;						//Ԥ�õ����
	UINT			pPreset[MAX_PRESET_CT];			//Ԥ�õ�����
	char			name[MAX_PRESET_CT][32];		//Ԥ�õ�����
}PTZ_PRESET_INFO;

//Ѳ����Ϣ
typedef struct
{
	UINT         nPatrolSize;                //Ѳ��������Ԥ�õ���
	PATROL_NOD  aPatrol[MAX_PATROL_NOD];    //Ѳ��
}PTZ_PATROL_INFO;

typedef enum
{
	GUARD_NO,
	GUARD_PRESET,
	GUARD_PATROL,
	GUARD_TRAIL,
	GUARD_SCAN,
}PTZ_GUARD_TYPE_E;

//������Ϣ
typedef struct
{
	UINT guardTime;		//����ʱ�䡣0��ʾ�����ر�
	PTZ_GUARD_TYPE_E guardType;
	union
	{
		UINT nRreset;
		UINT nPatrol;;
		UINT nTrail;
		UINT nScan;
	};
}PTZ_GUARD_T;

//��̨����״̬
typedef struct
{
	UINT 		bootItem;			//����������

}PTZ_STATUS;

typedef struct
{
	PTZ stPtz[PTZ_CNT];//ÿ��ͨ������̨�ṹ
	PTZ_PRESET_INFO stPreInf[PTZ_CNT]; 	//Ԥ�õ���Ϣ
	PTZ_PATROL_INFO stPatrolInf[PTZ_CNT];	//Ѳ����Ϣ
	PTZ_GUARD_T stGuard[PTZ_CNT];
	PTZ_STATUS stPtzStatus[PTZ_CNT];
} PTZ_INFO_T;

#pragma endregion


/*�豸��Ϣ*/
#ifndef ST_DEVICE_DEF
#define ST_DEVICE_DEF
typedef struct _ST_Device
{
	char szDeviceName[100];
	char szServerIP[17];
	int nServerPort;
	char szCloudNum[17];		//����ͨ���룬 �翪ͷ��ĸΪ'N'����onvifЭ����豸
	char szNetUser[32];
	char szNetPwd[32];
	int nChnCount;
	DeviceType type;
	BOOL bHasWifi;
	BOOL bUseWifi;
	BOOL bOnline;
}ST_Device, *PST_Device;
#endif;

/*����ͨ��*/
#ifndef ST_CHNINFO_DEF
#define ST_CHNINFO_DEF
typedef struct _ST_ChnInfo
{
	char szDeviceName[100];
	char szServerIP[17];
	int nServerPort;
	char szCloudNum[17];		//����ͨ���룬 �翪ͷ��ĸΪ'N'����onvifЭ����豸
	char szNetUser[32];
	char szNetPwd[32];
	int nChnIndex;
	int nLocalIndex;
}ST_ChnInfo, *PST_ChnInfo;
#endif;

/*Զ��¼���ļ�*/
typedef struct _ST_RemoteVideo	
{
	char			szCloudNum[17];	//����ͨ�Ż�ip��ַ
	char			acSecuCh[3];	//ͨ����
	char			acRedDay[9];	//¼������
	char			acRecTimeS[7];	//¼��ʱ��
	char			acRecTimeE[7];	//¼��ʱ��
	char			cDisk;			//�����̷�
	char			cRecType;		//¼������
}ST_RemoteVideo, *PST_RemoteVideo;

/*����¼��*/
typedef struct _RecordConfig
{
	char	devid[20];		//�豸��
	int		chnid;			//ͨ����
	char	day[20];		//���� ��ʽ��yyyyMMdd
	char	time[20];		//ʱ�� ��ʽ: hh:mm:ss
	char	path[256];		//��Ƶ
	char	pic[256];		//����ͼ
	char	type[50];		//���ͣ�normal,alarm,timer
	int		frate;			//֡��
	char	endtime[20];	//����ʱ�� ��ʽ��hh:mm:ss
} RecordConfig, *PRecordConfig;


/*���ؽ���*/
typedef struct _ST_DOWNLOADRATE
{
	char	szFile[MAX_PATH];
	long	nFileLen;
	long	nDownLen;
}ST_DOWNLOADRATE, *PST_DOWNLOADRATE;

/*���ӷ���״̬�ص�*/
typedef void (*FUNC_CONNECT_CALLBACK)(void* param, PST_ChnInfo pChnInfo, ConnectState connState); 
/*ͨ��״̬�ص�*/
typedef void (*FUNC_CHNSTATE_CALLBACK)(void* param, PST_ChnInfo pChnInfo, DWORD state);	
/*��־��Ϣ*/
typedef void (*FUNC_LOGINFO_CALLBACK)(void* param,int msgType, char* pMsg);	//
/*Զ�̼����ص�*/
typedef void (*FUNC_GETREMOTEVIDEO_CALLBACK)(void* param, const PST_RemoteVideo pRemoteVideo, int nSize);
/*���ػطŽ���*/
typedef void (*FUNC_PLAYBACKRATE_CALLBACK)(void* param, int nLocalIndex, ULONG ulFrame, ULONG ulTotalFrame,ULONG ulMiliSec, ULONG ulTotalMiliSec);	
/*Զ�����ؽ���*/
typedef void (*FUNC_DOWNLOADRATE_CALLBACK)(void* param, PST_DOWNLOADRATE downRate);	
/*Ԥ��λ�����ص�*/
typedef void (*FUNC_GETYTPARA_CALLBACK)(void* param, PTZ_INFO_T* pData);
/*��ѯ�豸��Ϣ�ص�*/
typedef void (*FUNC_GETDEVICEINFO_CALLBACK)(void* param, PST_Device pDevice);
/*��ȡ��metadata��ص�*/
typedef void (*FUNC_METADATA_CALLBACK)(void* param,int nTotalMiliSec);
/*rtmp�ط�ʱ�յ��豸ready֡��ص�*/
typedef void (*FUNC_CUSTOMFRAME_CALLBACK)(void* param,const char* pData,int nSize);
/*¼����Ϣ�ص�*/
typedef void (*FUNC_RECORDINFO_CALLBACK)(void *param, int nLocalIndex, PST_ChnInfo pChnInfo, char *recname);

/************************************************* 

	Function		:	Player_Init 
	Description		:	��ʼ����Ƶ�ؼ�
	Input:       
		1.[HWND]		hwnd ������ľ�� 
	Output			:	��
	Return			:	��
	Others			:	��
	
*************************************************/ 
Player_C_API void __stdcall Player_Init(HWND hwnd);

/************************************************* 

	Function		:	Player_Release 
	Description		:	�ͷ���Ƶ�ؼ�
	Input			:	��			
	Output			:	��
	Return			:	��
	Others			:	��
	
*************************************************/ 
Player_C_API void __stdcall Player_Release(void);

/************************************************* 

	Function		:	Player_SetLanguage 
	Description		:	����ʹ�õ�����
	Input:       
		1.[char*]		pLanguage ����ǰʹ�õ����� ������Ϊ:zh-CN,Ӣ��Ϊ��en-US
	Output			:	��
	Return			:	��
	Others			:	��
	
*************************************************/ 
Player_C_API void __stdcall Player_SetLanguage(char* pLanguage);

/************************************************* 

	Function		:	Player_SetStorePath 
	Description		:	����¼���ļ��Ĵ洢Ŀ¼
	Input:       
		1.[char*]		pPath1	Ŀ¼����
	Output			:	��
	Return			:	��
	Others			:	���·��ʱ������ÿ����ȡһ��·������ʵ��¼��·��Ϊ��pPath1/recordfiles/
	
*************************************************/ 
Player_C_API void __stdcall Player_SetStorePath(char *pPath1, 
	char *pPath2 = NULL, 
	char *pPath3 = NULL, 
	char *pPath4 = NULL, 
	char *pPath5 = NULL);

/************************************************* 

	Function		:	Player_SetPicPath 
	Description		:	����ͼƬ�Ĵ洢Ŀ¼
	Input:       
		1.[char*]		pPath	Ŀ¼����
		1.[BOOL]		bJPEG	�Ƿ�洢ΪJPG��ʽ
	Output			:	��
	Return			:	��
	Others			:	��
	
*************************************************/ 
Player_C_API void __stdcall Player_SetPicPath(char *pPath, BOOL bJPEG); 

/************************************************* 

	Function		:	Player_SetRecConfig 
	Description		:	����¼����������
	Input:       
		1.[int]			nDuration	¼��ʱ��
		2.[BOOL]		bCover		�������Ƿ񸲸�
		3.[int]			nDelDays	������ʱ��ɾ�����缸���¼��bCoverΪTRUEʱ��������
		3.[int]			headspace	����Ԥ���ռ䣬Ĭ��Ϊ1000m
	Output			:	��
	Return			:	��
	Others			:	headspace��СΪ1000m
	
*************************************************/ 
Player_C_API void __stdcall Player_SetRecConfig(int nDuration, BOOL bCover, int nDelDays, int headspace = 1000);


/************************************************* 

	Function		:	Player_GetLanDevice 
	Description		:	��ȡ�������豸
	Input:       
		1.[int&]				nCount		�豸������
		2.[DeviceProtocolType]	devProtType �豸Э������
	Output			:	���ز��ҵ��豸����Ŀ
	Return			:	ST_Device�����׵�ַ
	Others			:	�����ȡ�������豸�����������ʱ�������þ������㲥���� CMD_ENABLENETSCAN
	
*************************************************/ 
Player_C_API PST_Device __stdcall Player_GetLanDevice(int &nCount, DeviceProtocolType devProtType= DPT_CLOUD);

/************************************************* 

	Function		:	Player_Command 
	Description		:	���Ϳ�������
	Input:       
		1.[CommandType]		cmdType		��������
	Output			:	��
	Return			:	��
	Others			:	��
	
*************************************************/ 
Player_C_API void __stdcall Player_Command(CommandType cmdType);

/************************************************* 

	Function		:	Player_GetDeviceInfo 
	Description		:	��ȡ�豸��Ϣ
	Input			:   ��    
	Output			:	��
	Return			:	��
	Others			:	�����ȡ�������豸�����������ʱ�������þ������㲥���� CMD_ENABLENETSCAN
	
*************************************************/ 
Player_C_API ST_Device __stdcall Player_GetDeviceInfo(char *szCloudNum, BOOL bSync = TRUE);

/*
*	ע���ȡ�豸��Ϣ�Ļص�
*/
Player_C_API void __stdcall Player_RegDeviceCall(void *param, FUNC_GETDEVICEINFO_CALLBACK event);








/*��Ƶ��ʾ������*/
class PLAYER_API CVideoPlayer
{
public:
	CVideoPlayer(void);
	~CVideoPlayer(void);

public:	
	
	/************************************************* 

		Function		:	SetDisplayRect 
		Description		:	���õ�ǰ����������ʾ����
		Input:       
			1.[HWND]		hwndParent ��ǰ�������ľ�� 
			2.[LPRECT]		lpRect ��ʾ����
		Output			:	��
		Return			:	��
		Others			:	�������
	
	*************************************************/ 			
	void SetDisplayRect(HWND hwndParent, LPRECT lpRect);
	
	/************************************************* 

		Function		:	SetBorderStyle 
		Description		:	���ñ߿���ʽ
		Input:       
			1.[COLORREF]		clrNormal	δѡ�����ɫ
			2.[COLORREF]		clrSelected ѡ������ɫ
            3.[int]             nBorderLineWidth  �߿��� ��λ:����
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	void SetBorderStyle(COLORREF clrNormal, COLORREF clrSelected,int nBorderLineWidth);
	
	/************************************************* 

		Function		:	SetChannelBitmap 
		Description		:	����ͨ������
		Input:       
			1.[HMODULE]		hModule			ͼƬ��Դ����ģ��
			2.[UINT]		nbitmap			ͼƬ����Դ���
			2.[UINT]		nLoadingResID	���Ӷ�������ԴID��png��ʽ
			2.[int]			nSize			���Ӷ����Ĵ�С���߶ȺͿ�ȵ�ֵ
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	
	void SetChannelBitmap(HMODULE hModule, UINT nbitmap, UINT nLoadingResID = 0, int nSize = 0);
	
    /************************************************* 

		Function		:	SetChannelColor 
		Description		:	����ͨ��������ɫ
		Input:       
			1.[COLORREF]	clrBackGround	ͨ������ɫ
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	void SetChannelColor(COLORREF clrBackGround);

	/************************************************* 

		Function		:	SetFontSize 
		Description		:	����ͨ�������С
		Input:       
			1.[int]			nFontSize		ͨ����ʾ�������С
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	void SetFontSize(int nFontSize = 14);


	/************************************************* 

		Function		:	RegisterCallback 
		Description		:	ע��ص�����
		Input:       
			1.[void*]							param ����Ĳ������ص�ʱ���� 
			2.[FUNC_CONNECT_CALLBACK]			connectCallBack		����״̬�ص�
			3.[FUNC_CHNSTATE_CALLBACK]			chnStateCallBack	ͨ��״̬�ص�
			4.[FUNC_LOGINFO_CALLBACK]			logInfoCallBack		��־��Ϣ�ص�
			5.[FUNC_GETREMOTEVIDEO_CALLBACK]	remoteVideoCallback		Զ����Ƶ�����ص�
			6.[FUNC_PLAYBACKRATE_CALLBACK]		playBackRateCallBack	�طŽ��Ȼص�
			7.[FUNC_DOWNLOADRATE_CALLBACK]		downRateCallBack		���ؽ��Ȼص�
			8.[FUNC_GETYTPARA_CALLBACK]			func_GetYtPara_CallBack	
		Output			:	��
		Return			:	��
		Others			:	��
	
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
		Description		:	���ûطſ�����
		Input			:   ��    
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 	
	void EnablePlayBar(void);

	/************************************************* 

		Function		:	Paint 
		Description		:	���Ʊ���
		Input:   
			1.[HDC]			hdc ��ǰ������������������豸����
		Output			:	��
		Return			:	��
		Others			:	�ڲ����������������OnPaint�¼��е���
	
	*************************************************/ 
	void Paint(HDC hdc);

	/************************************************* 

		Function		:	DividWindow 
		Description		:	�ָ���Ļ
		Input:   
			1.[SplitNum]	num ������Ļ����Ŀ
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	void DividWindow(SplitNum num);

	/************************************************* 

		Function		:	WindowMoved 
		Description		:	�����ƶ��¼�
		Input			:   ��
		Output			:	��
		Return			:	��
		Others			:	��������ָ����Ƶ��ʾ���򣬴����ƶ�ʱ���������
	
	*************************************************/ 
	void WindowMoved(void);

	/************************************************* 

		Function		:	MouseEvent 
		Description		:	����¼�
		Input:   
			1.[MouseEventType]	meType ����¼�����
			2.[POINT&]			point ��������
		Output			:	��
		Return			:	��
		Others			:	��굥���¼� ��������ѡ�� ˫���¼����������ĵ�����ʾ�� 
							�Ҽ�����Ĭ�ϵ�ͨ���˵�
	
	*************************************************/ 
	void MouseEvent(MouseEventType meType, POINT &point);

	/************************************************* 

		Function		:	MouseZoom 
		Description		:	��Ƶ����
		Input:   
			1.[POINT]		pt		�������¼�������
			2.[BOOL]		bZoomIn	�����С �����������¼�����
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/ 
	void MouseZoom(POINT pt, BOOL bZoomIn);


	/************************************************* 

		Function		:	Connect 
		Description		:	������Ƶͨ��
		Input:   
			1.[ST_ChnInfo&] chnInfo ͨ����Ϣ
		Output			:	��
		Return			:	�Ƿ�����������ɹ�
		Others			:	���ӽ����ͨ��FUNC_CONNECT_CALLBACK �ص���֪Ӧ�ò�
	
	*************************************************/
	bool Connect(ST_ChnInfo & chnInfo, char* strURL = NULL);

	/************************************************* 

		Function		:	Disconnect 
		Description		:	�Ͽ�ͨ������
		Input:   
			1.[int]			nLocalIndex �Ͽ��ı���ͨ���� ��Ϊ0�����ǵ�ǰѡ��ͨ��
		Output			:	��
		Return			:	��
		Others			:	����ͨ���Ŵ�1��ʼ
	
	*************************************************/
	void Disconnect(int nLocalIndex = 0);

	/************************************************* 

		Function		:	DisconnectAll 
		Description		:	�Ͽ���������
		Input			
			1.[BOOL]		bClear �Ƿ����ͨ����Ϣ
		Output			:	��
		Return			:	��
		Others			:	�˽ӿ�ֻ��Ԥ����Ƶ��Ч��
	
	*************************************************/
	void DisconnectAll(BOOL bClear = TRUE);
	
	/************************************************* 

		Function		:	CleanChnInfo 
		Description		:	����ͨ����Ϣ
		Input:   
			1.[int]				nLocalIndex ���ش��ںţ���1��ʼ
		Output			:	��
		Return			:	��
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	void CleanChnInfo(int nLocalIndex = 0);

    /************************************************* 

		Function		:	EnablePreDecode 
		Description		:	����Ԥ����(Ĭ�Ͽ�����Ԥ��������ͼ�񲥷��Ӻ�һ֡���Դ˴��������ȵ�����)
                            ��Ҫ���ڻط�ģʽ֡��λͼ��ˢ������ �򿪲�������ĵ�һ�ζ�λĳ�ؼ�֡ʱ ͼ��᲻ˢ�� ��ʱ�ɽ���Ԥ������
		Input:   
			1.[int]				nLocalIndex ���ش��ںţ���1��ʼ
            2.[BOOL]            bEnable TRUEΪ����Ԥ����
		Output			:	��
		Return			:	��
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	void EnablePreDecode(BOOL bEnable,int nLocalIndex = 0);

	/************************************************* 

		Function		:	RemoteVideoCheck 
		Description		:	Զ�̼���
		Input:   
			1.[char*]		pDay ���������� �磺20131231
			2.[PST_ChnInfo] pChnInfo Զ�̼�����ͨ����Ϣ���粻ΪNULL, ����ȥ���Ӵ�ͨ����Ȼ���ټ���
		Output			:	��
		Return			:	��
		Others			:	pChnInfo��ΪNULLʱ����FUNC_CONNECT_CALLBACK��������״̬��
							��FUNC_GETREMOTEVIDEO_CALLBACK���ؼ������
	
	*************************************************/
	void RemoteVideoCheck(char* pDay, PST_ChnInfo pChnInfo = NULL);	

	/************************************************* 

		Function		:	RemoteVideoPlay 
		Description		:	Զ�̻ط�
		Input:   
			1.[PST_RemoteVideo]		pRemoteVideo��Ҫ�طŵ�Զ���ļ���Ϣ
			2.[BOOL]				bConnect ���δTRUEʱ���򵱵�ǰѡ��ķ����Ǵ��豸������ͨ��ʱ��
											����ȥ���ӣ�Ȼ��ط�
			3.[PST_ChnInfo]			pChnInfo Զ���ļ���Ӧ��ͨ����Ϣ
		Output			:	��
		Return			:	��
		Others			:	������ʱ���᷵������״̬�ص����ͻط���־��Ϣ
							pChnInfo ֻ�� bConnect ΪTRUEʱ��Ч
	
	*************************************************/
	void RemoteVideoPlay(PST_RemoteVideo pRemoteVideo, BOOL bConnect = FALSE, PST_ChnInfo pChnInfo = NULL);	

	/************************************************* 

		Function		:	LocalVideoPlay 
		Description		:	�����ļ��ط�
		Input:   
			1.[char*]		pFileName������Ƶ�ļ���ȫ·����
			2.[int]				nLocalIndex ���ش��ںţ���1��ʼ
		Output			:	��
		Return			:	�Ƿ񲥷ųɹ�
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	bool LocalVideoPlay(char* pFileName, int nLocalIndex = 0);

	/*
	*	����¼�����
	*	���ڸ�ʽΪ:yyyyMMdd
	*	typeΪ��normal,alarm,timer ,NULLΪ����
	*/
	PRecordConfig LocalVideoCheck(char *devid, int chnid, char *day, char *type, int &count);

	/************************************************* 

		Function		:	PlayBackCtrl 
		Description		:	�طſ���
		Input:   
			1.[PlayBackCtrlType]	ctrlType�طſ������ͣ�����ͣ�����š�ֹͣ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void PlayBackCtrl(PlayBackCtrlType ctrlType);

	/************************************************* 

		Function		:	PlayBackSeekToFrame 
		Description		:	��λ��ĳһ�ؼ�֡
		Input:   
			1.[ULONG]		ulCurrentFrame �ؼ�֡����
		Output			:	��
		Return			:	��ǰ֡
		Others			:	��
	
	*************************************************/
	ULONG PlayBackSeekToFrame(ULONG ulCurrentFrame);
	
	/************************************************* 

		Function		:	PlayStepForward 
		Description		:	���ػطŵ�֡����
		Input:
			1.[int]				nLocalIndex ���ش��ںţ���1��ʼ
		Output			:	��
		Return			:	���óɹ���ʧ��
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	BOOL PlayStepForward(int nLocalIndex = 0);
	
	/************************************************* 

		Function		:	GetPlaySpeed 
		Description		:	��ȡ���ػطŵ��ٶ�
		Input:
			1.[int]				nLocalIndex ���ش��ںţ���1��ʼ
		Output			:	��
		Return			:	�ط��ٶ� = 2^(����ֵ)
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	int GetPlaySpeed(int nLocalIndex = 0);

	/************************************************* 

		Function		:	CanDownLoadFile 
		Description		:	��֤�Ƿ���������ļ�
		Input:   
			1.[char *]			pExtName �ļ���չ����
			2.[PST_RemoteVideo] pRemoteVideo Զ���ļ�
		Output			:	��
		Return			:	�Ƿ��������
		Others			:	��
	
	*************************************************/
	bool CanDownLoadFile(char *pExtName, PST_RemoteVideo pRemoteVideo);

	/************************************************* 

		Function		:	DownLoadFile 
		Description		:	����Զ���ļ�
		Input:   
			1.[LPCSTR]			lpszFileName �����ļ�����
			2.[PST_RemoteVideo] pRemoteVideo Զ���ļ�
		Output			:	��
		Return			:	�Ƿ��������
		Others			:	��
	
	*************************************************/
	bool DownLoadFile(LPCSTR lpszFileName);

	/************************************************* 

		Function		:	StopDownFile 
		Description		:	ֹͣ�����ļ�
		Input			:   ��
		Output			:	��
		Return			:	�Ƿ��������
		Others			:	��
	
	*************************************************/
	void StopDownFile(void);

	/************************************************* 

		Function		:	ChannelCtrl 
		Description		:	�طſ���
		Input:
			1.[ChannelCtrlType] ccType�طſ������ͣ�����ͣ�����š�ֹͣ��
			2.[BOOL]			bEnable
			3.[int]				nLocalIndex ���ش��ںţ���1��ʼ
		Output			:	��
		Return			:	��
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	void ChannelCtrl(ChannelCtrlType ccType, BOOL bEnable, int nLocalIndex = 0);

	/************************************************* 

		Function		:	VideoCapture 
		Description		:	��Ƶץ��
		Input:
			1.[int] nLocalIndex ����ͨ��
		Output			:	��
		Return			:	ץͼ·����
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	char* VideoCapture(int nLocalIndex = 0);

	/************************************************* 

		Function		:	RemoteConfig 
		Description		:	Զ������
		Input:
			1.[int]			nLocalIndex ����ͨ��
		Output			:	��
		Return			:	��
		Others			:	���ں�Ϊ0ʱ����Ե�ǰ����
	
	*************************************************/
	void RemoteConfig(int nLocalIndex = 0);

	/************************************************* 

		Function		:	CameraCtrl 
		Description		:	��ͷ����
		Input:
			1.[UINT]		nType 1,2,3,4,5,6 �ֱ��ʾ��Ȧ,���࣬����,��̨, ����1,����2
			2.[BOOL]		bFlags  TRUE��ʾ���£� FALSE��ʾ̧��
			3.[UINT]		nKind 1,2�ֱ��ʾ -��+
			4.[BYTE]		bSpeed ת���ٶ�
		Output			:	��
		Return			:	��
		Others			:	��������̨ʱ�� nKinkȡֵΪ1,2,3,4,5�ֱ��ʾ��,��,��,��,�Զ�
							��Ϊ��������ʱ��bFlags ��������رգ� nKind ��Ч
							��Ե�ǰѡ��ͨ��
	
	*************************************************/
	void CameraCtrl(UINT nType, BOOL bFlags, UINT nKind, BYTE bSpeed = 0, int nLocalIndex = 0);

	/************************************************* 

		Function		:	RecordAll 
		Description		:	ȫ��ͨ����¼��
		Input:
			1.[BOOL]		bStart �Ƿ�ȫ��¼��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void RecordAll(BOOL bStart);

    /************************************************* 

		Function		:	PausePlayBackRateCallBack 
		Description		:	��ͣ��ǰ�طŽ��Ȼص�
		Input:
			1.[int]			nLocalIndex	   ����ͨ��
		Output			:	��
		Return			:	��
	
	*************************************************/
	void PausePlayBackRateCallBack(int nLocalIndex = 0);

    /************************************************* 

		Function		:	SetChannelInfo 
		Description		:	���õ�ǰͨ����Ϣ
		Input:
			1.[ST_ChnInfo]	chnInfo		   ��ǰͨ�����ӵ�ͨ����Ϣ
			2.[int]			nLocalIndex	   ����ͨ��
		Output			:	��
		Return			:	��
	
	*************************************************/
	void SetChannelInfo(ST_ChnInfo& chnInfo, int nLocalIndex = 0);

	/************************************************* 

		Function		:	GetChannelState 
		Description		:	��ȡ��ǰͨ����״̬
		Input:
			1.[PST_ChnInfo]	pChnInfo		��ǰͨ�����ӵ�ͨ����Ϣ
			2.[int]			nLocalIndex		����ͨ��
		Output			:	��
		Return			:	ͨ���ĵ�ǰ״̬ dw, dw��ChannelState�е�ÿһ��������룬��֤�Ƿ��д�״̬��
							�磺�Ƿ�����Ԥ��Ϊ CHS_PREVIWING == (CHS_PREVIWING & dw)
		Others			:	nLocalIndex Ϊ0ʱ����Ե�ǰѡ��ͨ��
	
	*************************************************/
	DWORD GetChannelState(PST_ChnInfo pChnInfo, int nLocalIndex = 0);

	/************************************************* 

		Function		:	GetSelectedIndex 
		Description		:	��ȡ��ǰѡ��Ĵ���
		Input			:	��
		Output			:	��ǰѡ�񴰿ڵ�����
		Return			:	��
		Others			:	��
	
	*************************************************/
	int GetSelectedIndex(LPRECT lpRect = NULL);
	

	/************************************************* 

		Function		:	GetWindowNum 
		Description		:	��ȡ��ǰѡ��Ĵ���
		Input			:	��
		Output			:	��
		Return			:	������Ŀ
		Others			:	��
	
	*************************************************/
	int GetWindowNum(void);
	
	/************************************************* 

		Function		:	GetCurrentChnInfos 
		Description		:	��ȡ��ǰ����������ͨ����Ϣ
		Input:
			1.[PST_ChnInfo]	pChnInfo		ͨ����Ϣ�����ָ��
		Output			:	��
		Return			:	������Ŀ
		Others			:	��ȡ��ǰ���з�������Ŀ
	
	*************************************************/
	void GetCurrentChnInfos(PST_ChnInfo pChnInfo);

	/*
	*	��ȡ��ǰ������λ����Ϣ
	*	nLocalIndex����ֵ>0ʱ��������ĳ�����������ʾ
	*/
	RECT *GetCurrentRects(int &nLocalIndex);

	/************************************************* 

		Function		:	PtzConfig 
		Description		:	������̨����״̬
		Input:
			1.[int]			nLocalIndex		����ͨ��
		Output			:	��
		Return			:	��
		Others			:	nLocalIndex Ϊ0ʱ����Ե�ǰѡ��ͨ��
	
	*************************************************/
	BOOL PtzConfig(int nLocalIndex = 0);

	/************************************************* 

		Function		:	AddPreset 
		Description		:	����Ԥ��λ
		Input:
			1.[int]			nPreset Ԥ��λ��
			2.[char*]		szName  Ԥ��λ������
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void AddPreset(int nPreset,char* szName);

	/************************************************* 

		Function		:	DelPreset 
		Description		:	ɾ��Ԥ��λ
		Input:
			1.[int]			nPreset Ԥ��λ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void DelPreset(int nPreset);

	/************************************************* 

		Function		:	CallPreset 
		Description		:	����Ԥ��λ
		Input:
			1.[int]			nPreset Ԥ��λ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void CallPreset(int nPreset);

	/************************************************* 

		Function		:	AddPatrol 
		Description		:	����Ԥ��λ��Ѳ����
		Input:
			1.[int]			nPreset Ԥ��λ��
			2.[int]			nStayTime �ڸ�Ԥ��λ��ͣ��ʱ�� ��λ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/	
	void AddPatrol(int nPreset,int nStayTime);

	/************************************************* 

		Function		:	DelPatrol 
		Description		:	ɾ��Ѳ�����е�Ԥ��λ
		Input:
			1.[int] nPresetIndex Ѳ������Ԥ��λ����������Ԥ��λ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void DelPatrol(int nPresetIndex);

	/************************************************* 

		Function		:	StartPatrol 
		Description		:	��ʼѲ��
		Input			:	��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void StartPatrol();

	/************************************************* 

		Function		:	StopPatrol 
		Description		:	ֹͣѲ��
		Input			:	��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void StopPatrol();
	
	/************************************************* 

		Function		:	ConnectPollChn 
		Description		:	����������Ƶ
		Input			
			1.[PST_ChnInfo *]		pChnInfo	ͨ����Ϣָ��
			2.[int]					count		ͨ������
			2.[int]					nElapse		����ʱ��
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void ConnectPollChn(PST_ChnInfo pChnInfo, int count, int nElapse);
	
	/************************************************* 

		Function		:	SetPollingState 
		Description		:	��������״̬
		Input			
			1.[PollingState_t]		pollState ����״̬
		Output			:	��
		Return			:	��
		Others			:	��
	
	*************************************************/
	void SetPollingState(PollingState_t pollState);

	/*
	*	����Ϊ������Ƶģʽ
	*/
	void SetAlarmVideoMode(BOOL bAutoAlarmVideo);	

	/*
	*	��ȡ��ǰ¼�������
	*/
	char* GetRecordFileName(int nLocalIndex = 0);

	/*
	*	���ö�ʱ¼��
	*	sTime��eTime��ʽΪ��"hh:mm",��ʱ��������Ϊ10����
	*	hhΪ24Сʱ��
	*/
	void SetRecordTimerMode(BOOL bEnable, char *sTime, char *eTime, int nLocalIndex = 0);
	
	/*
	*	������ʾ��Ϣ
	*/
	void SetMessage(char *msg, int nLocalIndex = 0);
private:
	LPVOID m_pHandle;
};