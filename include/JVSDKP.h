/**
* @file JVSDKP.h
* @brief 播放SDK接口头文件
* @author 程行通
* @date 2013-09-23
* @version 1.1.0
* @copyright Copyright (C) Jovision 2013
*/

#include <Windows.h>
#pragma once

//宏定义------------------------------------------------------------------------------------
#ifdef __cplusplus
#  define JVSDKP_API extern "C" __declspec(dllexport)
#else
#  define JVSDKP_API __declspec(dllexport)
#endif

#define JVSDKP_CALL __stdcall

//类型定义-----------------------------------------------------------------------------------------
//SDK通知事件的lParam
#define	WM_LPARAM_BITMAP	0x01			//抓图
#define	WM_LPARAM_STOP		0x02			//回放停止

//中维公司自定义帧类型
#define JVS_TYPE_P			0x00			//前向预测帧
#define JVS_TYPE_IDR		0x01			//关键帧
#define JVS_TYPE_AUD		0x02			//音频帧
#define JVS_TYPE_SKIP		0x03			//SKIP帧，可忽略
#define JVS_TYPE_D			0x04			//可丢弃帧
#define JVS_TYPE_B			JVS_TYPE_D		//双向预测帧

//帧率控制模式
#define JVS_PLAYCTRL_AUTO			0x00	//自适应模式，默认设置
#define JVS_PLAYCTRL_MINDELAY		0x10	//最小延迟模式，不做帧率控制
#define JVS_PLAYCTRL_MIDDELEFFECT	0x21	//中等效果模式，适应于低网络延迟局域网，会照成100ms左右延迟
#define JVS_PLAYCTRL_BESTEFFECT		0x22	//最佳效果模式，适应于大多数情况，会照成200ms左右延迟

//OSD类型
#define JVS_OSDTYPE_TEXT				0	//文本类型
#define JVS_OSDTYPE_IMAGE				1	//图像类型(暂不支持)

//位置坐标类型
#define JVS_OSDTEXTPOSTYPE_LEFTTOP		0	//矩形左上点坐标
#define JVS_OSDTEXTPOSTYPE_RIGHTTOP		1	//矩形又上点坐标
#define JVS_OSDTEXTPOSTYPE_RIGHTBOTTOM	2	//矩形右下点坐标
#define JVS_OSDTEXTPOSTYPE_LEFTBOTTOM	3	//矩形左下点坐标

//像素格式
#define JVS_PIXELFORMAT_ARGB			0
#define JVS_PIXELFORMAT_YV12			1
#define JVS_PIXELFORMAT_YUV				2

//像素混合方式
#define JVS_COLORBLEND_NONE				0	//禁用混合
#define JVS_COLORBLEND_SRCALPHA			1	//使用图像Alpha混合
#define JVS_COLORBLEND_FIXEDALPHA		2	//使用固定Alpha值混合

//ARGB函数
#define JVS_ARGB(a, r, g, b) (((DWORD)(UCHAR)(r)) | (((DWORD)(UCHAR)(g)) << 8) | (((DWORD)(UCHAR)(b)) << 16) | (((DWORD)(UCHAR)(a)) << 24))
#define JVS_RGB(r, g, b) JVS_ARGB(0xFF, r, g, b)
#define JVS_GETRVALUE(c) (UCHAR)((c) & 0xFF)
#define JVS_GETGVALUE(c) (UCHAR)(((c) >> 8) & 0xFF)
#define JVS_GETBVALUE(c) (UCHAR)(((c) >> 16) & 0xFF)
#define JVS_GETAVALUE(c) (UCHAR)(((c) >> 24) & 0xFF)

typedef struct _JVS_SCREENINFO
{
	RECT	rtScreenRect;
	RECT	rtWorkRect;
	
} JVS_SCREENINFO, *PJVS_SCREENINFO;

typedef struct _JVSMediaFileInfo
{
	DWORD dwTotalFrame;
	DWORD dwWidth;
	DWORD dwHeight;
	DWORD dwFrameRateNum;
	DWORD dwFrameRateDen;
} JVSMediaFileInfo_t;

typedef struct _JVSTextOsdInfo
{
	char* szText;		//文本内容
	DWORD dwPosType;	//位置坐标类型
	int nPosX;			//位置坐标X
	int nPosY;			//位置坐标Y
	DWORD dwColor;		//文本颜色(支持通明通道)
}
JVSTextOsdInfo_t, *PJVSTEXTOSDINFO;

typedef struct _JVSImageOsdInfo
{
	PUCHAR pImageData;	//图像数据
	DWORD dwDataType;	//图像像素格式
	int nWidth;			//图像宽度
	int nHeight;		//图像高度
	int nPosX;			//位置坐标X
	int nPosY;			//位置坐标Y
	DWORD dwBlendType;	//像素混合方式
	BYTE ucBlendAlpha;	//像素混合不透明度(固定Alpha混合模式下有效)
}
JVSImageOsdInfo_t, *PJVSIMAGEOSDINFO;

typedef struct _JVSOsdInfo
{
	WORD wOsdType;
	union
	{
		JVSTextOsdInfo_t textInfo;
		JVSImageOsdInfo_t imageInfo;
	};
}
JVSOsdInfo_t, *PJVSOSDINFO;

typedef void (*CALLBACK_YV12_DATA)(int nPlayer, PUCHAR pY, PUCHAR pU, PUCHAR pV, DWORD dwStrideY, DWORD dwStrideUV);
typedef void (*CALLBACK_DRAW)(int nPlayer, int nViewer, void *lpDD, void *lpDDS, RECT *lpRectShow, RECT *lpRectImage);
typedef void (*JVSDKPEventCallback_t)(int nPlayer, DWORD dwEventType);

//全局函数-----------------------------------------------------------------------------------------
/**
 @brief 初始化SDK
 @return 返回初始化结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_InitSDK();

/**
 @brief 释放SDK
*/
JVSDKP_API void JVSDKP_CALL JVSP_ReleaseSDK();

/**
 @brief 创建播放器
 @return 成功返回播放器ID，失败返回-1
*/
JVSDKP_API int JVSDKP_CALL JVSP_CreatePlayer();

/**
 @brief 释放播放器
 @param nPlayer 播放器ID
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_ReleasePlayer(int nPlayer);

/**
 @brief 注册SDK消息
 @param hWnd 接收消息的窗口句柄
 @param dwNotifyMsg 窗口消息
*/
JVSDKP_API void JVSDKP_CALL JVSP_RegisterNotify(HWND hWnd, DWORD dwNotifyMsg);

/**
 @brief 注册回调
 @param funYv12DataCallback yuv数据回调，NULL使用默认
 @param funEventCallBack 事件回调，NULL使用默认
 @param funPreDecodeCallback 解码前绘制回调，NULL使用默认(不推荐使用)
 @param funOnDecodeCallback 解码后绘制回调，NULL使用默认(不推荐使用)
*/
JVSDKP_API void JVSDKP_CALL JVSP_SetCallBack(
	CALLBACK_YV12_DATA funYv12DataCallback, JVSDKPEventCallback_t funEventCallBack, 
	CALLBACK_DRAW funPreDecodeCallback, CALLBACK_DRAW funOnDecodeCallback);

//流模式-------------------------------------------------------------------------------------------
/**
 @brief 打开视频流
 @param nPlayer 播放器ID
 @param pHeaderBuf 文件头结构体
 @param nSize 头结构体大小
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_OpenStream(int nPlayer, PUCHAR pHeaderBuf, int nSize);

/**
 @brief 关闭视频流
 @param nPlayer 播放器ID
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_CloseStream(int nPlayer);

/**
 @brief 向视频流中写入一帧
 @param nPlayer 播放器ID
 @param pBuffer 帧数据
 @param nSize 帧数据大小
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_WriteToStreamOneFrame(int nPlayer, PUCHAR pBuffer, int nSize);

/**
 @brief 获取文件头
 @param nPlayer 播放器ID
 @param pHeaderBuf 文件头结构体
 @param nSize 头结构体大小
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_GetHeaderData(int nPlayer, PUCHAR pHeaderBuf, int nSize);

/**
 @brief 设置默认帧率控制模式
 @param nMode 帧率控制模式，默认为JVS_PLAYCTRL_AUTO
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetDefaultFrameControlMode(int nMode);

/**
 @brief 设置帧率控制模式
 @param nPlayer 播放器ID
 @param nMode 帧率控制模式
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetFrameControlMode(int nPlayer, int nMode);

//文件模式-----------------------------------------------------------------------------------------
/**
 @brief 打开录像文件
 @param nPlayer 播放器ID
 @param szFilename 录像文件名
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_OpenFile(int nPlayer, char *szFilename);

/**
 @brief 开始录像文件播放
 @param nPlayer 播放器ID
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_Play(int nPlayer);

/**
 @brief 暂停录像文件播放
 @param nPlayer 播放器ID
*/
JVSDKP_API void JVSDKP_CALL JVSP_Pause(int nPlayer);

/**
 @brief 停止录像文件播放
 @param nPlayer 播放器ID
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_Stop(int nPlayer);

/**
 @brief 手动设置播放帧率
 @param nPlayer 播放器ID
 @param nSpeed 播放速度，播放速度为正常速度的2^nSpeed倍，即0为原速，1为2倍速，2为4倍速，-1为二分之一倍速，-2为四分之一倍速
 @param bOnlyKeyFrame 是否只播放关键帧(推荐播放速度8倍及以上时开启)
 @return 返回操作结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetPlaySpeed(int nPlayer, int nSpeed, BOOL bOnlyKeyFrame);

/**
 @brief 获取录像总帧数
 @param nPlayer 播放器ID
 @return 返回录像总帧数
 @node 对于未正常结束的录像文件返回值为0
*/
JVSDKP_API ULONG JVSDKP_CALL JVSP_GetTotalFrames(int nPlayer);

/**
 @brief 获取当前播放帧
 @param nPlayer 播放器ID
 @return 返回当前帧
*/
JVSDKP_API ULONG JVSDKP_CALL JVSP_GetCurFrameNum(int nPlayer);

/**
 @brief 单步播放一帧视频
 @param nPlayer 播放器ID
*/
JVSDKP_API void JVSDKP_CALL JVSP_StepForward(int nPlayer);

/**
 @brief 获取关键帧文件位置
 @param nPlayer 播放器ID
 @param ulKeyFramePos 返回关键帧文件位置
 @param ulFrameNum 输入查找的帧，返回对应关键帧
 @return 返回执行结果
 @node 仅SVX格式录像文件使用，即将被淘汰，不推荐使用
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_GetKeyFramePos(int nPlayer, ULONG *ulKeyFramePos, ULONG *ulFrameNum);

/**
 @brief 跳转至关键帧
 @param nPlayer 播放器ID
 @param ulFrame 跳转至帧数
 @param bPause 跳转后是否暂停播放
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_GotoKeyFrame(int nPlayer, ULONG ulFrame, BOOL bPause);

//预览相关-----------------------------------------------------------------------------------------
/**
 @brief 设置视频预览
 @param nPlayer 播放器ID
 @param hWnd 播放窗口句柄
 @param pRect 播放区域(相对于屏幕坐标系)
 @param bVideoPreview 是否开启预览
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetVideoPreview(int nPlayer, HWND hWnd, RECT *pRect, BOOL bVideoPreview);

/**
 @brief 设置视频子预览
 @param nPlayer 播放器ID
 @param hWnd 播放窗口句柄
 @param pRect 播放区域(相对于屏幕坐标系)
 @param bVideoPreview 是否开启预览
 @return 返回执行结果
*/
JVSDKP_API BOOL	JVSDKP_CALL JVSP_SetVideoSubPreview(int nPlayer, HWND hWnd, RECT *pRect, BOOL bVideoPreview);

/**
 @brief 获取视频输出设备信息
 @param pInfo 屏幕信息数组指针
 @param lpdwInfoCount 输入屏幕信息数组元素数，返回输出设备数
*/
JVSDKP_API void	JVSDKP_CALL JVSP_GetScreenInfo(PJVS_SCREENINFO pInfo, DWORD *lpdwInfoCount);

/**
 @brief 设置电子放大
 @param nPlayer 播放器ID
 @param bZoomIn 是否放大
 @param x 放大区域位置x坐标
 @param y 放大区域位置y坐标
 @return 返回执行结果
 @node 该接口用法不易理解，放大区域不准确、不灵活，即将淘汰，不推荐使用。请用JVSP_ZoomView代替
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_ZoomIn(int nPlayer, BOOL bZoomIn, int x, int y);

/**
 @brief 设置电子放大区域
 @param nPlayer 播放器ID
 @param pRect 电子放大区域
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_ZoomView(int nPlayer, RECT *pRect);

/**
 @brief 设置电子放大区域
 @param nPlayer 播放器ID
 @param nViewer 视图索引，0为主视图，1为子视图
 @param pRect 电子放大区域
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_ZoomViewEx(int nPlayer, int nViewer, RECT *pRect);

/**
 @brief 设置视频裁减
 @param nPlayer 播放器ID
 @param dwPixelCroped 裁剪像素数
 @node 暂只支持裁剪右侧区域
*/
JVSDKP_API void JVSDKP_CALL JVSP_SetVideoCrop(int nPlayer, DWORD dwPixelCroped);

/**
 @brief 刷新窗口
 @param nPlayer 播放器ID
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_RefreshWindow(int nPlayer);

/**
 @brief 设置视频显示区域
 @param nPlayer 播放器ID
 @param lpImageRect 视频显示区域(相对于播放区域)
 @node 接口设计不合理，不推荐使用
*/
JVSDKP_API void JVSDKP_CALL JVSP_SetImageRect(int nPlayer, RECT *lpImageRect);

/**
 @brief 设置音频预览
 @param nPlayer 播放器ID
 @param hWnd 播放窗口句柄
 @param bPreview 是否开启预览
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetAudioPreview(int nPlayer, HWND hWnd, BOOL bPreview);

/**
 @brief 设置OSD
 @param nPlayer 播放器ID
 @param pOsdInfos OSD信息,为NULL则关闭OSD
 @param dwOsdInfoCount OSD信息数,为0则关闭OSD
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetOSD(int nPlayer, PJVSOSDINFO pOsdInfos, DWORD dwOsdInfoCount);

/**
 @brief 开启调试信息(该功能与OSD功能不能同时开启)
 @param nPlayer 播放器ID
 @param bEnable 是否开启调试信息
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_EnableDebugOSD(int nPlayer, BOOL bEnable);

//其他操作-----------------------------------------------------------------------------------------
/**
 @brief 获取截图尺寸
 @param nPlayer 播放器ID
 @param dwWidth 输出截图像素宽度
 @param dwHeight 输出截图像素高度
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_GetBitmapSize(int nPlayer, DWORD *dwWidth, DWORD *dwHeight);

/**
 @brief 截图
 @param nPlayer 播放器ID
 @param pBuffer 数据缓冲指针
 @param dwBufferSize 数据缓冲大小
 @return 返回执行结果
 @node 异步操作，完成截图后由窗口消息或消息回调通知
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_GetBitmap(int nPlayer, PUCHAR pBuffer, DWORD dwBufferSize);

/**
 @brief 设置图像处理
 @param nPlayer 播放器ID
 @param bEnable 是否开启图像处理(暂只支持去雾)
 @param pParam 图像处理参数(未使用，填充NULL)
 @return 返回执行结果
*/
JVSDKP_API BOOL JVSDKP_CALL JVSP_SetImageProc(int nPlayer, BOOL bEnable, void* pParam);

//多媒体文件截图接口-------------------------------------------------------------------------------
//打开媒体文件
JVSDKP_API LPVOID JVSDKP_CALL JVSP_MediaFileOpen(char *szFilename, JVSMediaFileInfo_t* pInfo);

//截取一帧图像
JVSDKP_API BOOL JVSDKP_CALL JVSP_MediaFileGetOneFrame(LPVOID hHandle, DWORD dwFrameID, PUCHAR pBuffer, DWORD dwSize);

//关闭媒体文件
JVSDKP_API void JVSDKP_CALL JVSP_MediaFileClose(LPVOID hHandle);
