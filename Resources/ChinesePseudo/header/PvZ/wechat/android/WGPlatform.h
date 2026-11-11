//
//  WGPlatform.h
//  WGPlatform
//
//  Created by fly chen on 2/21/13.
//  Copyright (c) 2013 tencent.com. All rights reserved.
//
#ifndef __WGPLATFORM_H__
#define __WGPLATFORM_H__

#include "WGCommon.h"
#include <string>

#if defined ANDROID
#include <jni.h>
#endif

JNIEXPORT void JNICALL Java_com_tencent_msdk_api_WGPlatformObserverForSO_OnWakeupNotify(JNIEnv *env, jclass jc,
		jobject ret);

class WGPlatformObserver;

/*! @brief WeGame接口函数
 *
 * 该类封装了WeGame的外部接口
 */
class WGPlatform {
	friend JNIEXPORT void JNICALL ::Java_com_tencent_msdk_api_WGPlatformObserverForSO_OnWakeupNotify(JNIEnv *, jclass,
			jobject);
	friend JNIEXPORT void JNICALL ::Java_com_tencent_msdk_api_WGPlatformObserverForSO_OnLoginNotify(JNIEnv *, jclass,
				jobject);

public:
#if defined ANDROID
	void init(JavaVM* pVM, WGPlatformObserver* pNotify);
	void setVM(JavaVM* pVM);
#endif

	/*! @brief 设置Observer
	 *
	 * 初始化时调用
	 * @param pObserver 回调指针
	 * @return void
	 */
	void WGSetObserver(WGPlatformObserver* pNotify);

	/*! @brief 获取登录纪录
	 *
	 * 启动时调用
	 * @return 成功返回纪录类型，失败返回NO。
	 */
	int WGGetLoginRecord(LoginRet& lr);

	/*! @brief 登录指定平台
	 *
	 * 用户选择平台后调用
	 * @param platform 平台类型
	 * @param pNotify 回调
	 * @return void。
	 */
	void WGLogin(int platform);

	/*! @brief 登出当前已登录平台
	 *
	 * 切换帐号时调用
	 * @param clean 是否删除本地已保存的token
	 * @return 成功返回YES，失败返回NO。
	 */
	bool WGLogout(bool clean);

	/*! @brief 设置QZone的权限
	 *
	 * 切换帐号或者首次登录时调用
	 * @param permissions 权限
	 * @return void
	 */
	void WGSetPermission(unsigned int permissions);

	/* WGSendToWeixin	发消息到微信
	 * scene			发给哪里，朋友圈还是会话
	 * title			标题
	 * desc				描述
	 * url				分享url
	 * mediaTagName mediatagname 消息类型 游戏传入
	 * thumbImgData,thumbImgDataLen	图片信息
	 * 返回值: 			void
	 * */
	void WGSendToWeixin(const int& scene, unsigned char* title, unsigned char* desc, unsigned char* url,
			unsigned char* mediaTagName, unsigned char* thumbImgData, const int& thumbImgDataLen);

	/* WGSendToWeixinWithPhoto	发消息到微信
	 * scene			发给哪里，朋友圈还是会话
	 * mediaTagName mediatagname 消息类型 游戏传入
	 * imgData,imgDataLen	图片信息
	 * 返回值: 			void
	 * */
	void WGSendToWeixinWithPhoto(const int& scene, unsigned char* mediaTagName, unsigned char* imgData,
			const int& imgDataLen);

	/*! @brief 分享内容到QQ
	 *
	 * 分享时调用
	 * @param title 分享的标题
	 * @param desc 分享的消息摘要，最长50个字
	 * @param targetUrl 这条分享消息被好友点击后的跳转URL
	 * @param imgUrl 分享的图片URL
	 * @param imgUrlLen 数据长度
	 * @return void
	 */
	void WGSendToQQ(unsigned char* title, unsigned char* desc, unsigned char* url, unsigned char* imgUrl,
			const int& imgUrlLen);

	/* FeedBack			用户反馈
	 * game: 			游戏名
	 * txt: 			反馈内容
	 * 返回值: 			0成功 1失败
	 * */
	int WGFeedback(unsigned char* game, unsigned char* txt);

	/*! @brief 打开数据上报
	 *
	 * 初始化调用
	 * @param isRdmEnable Rdm(灯塔)崩溃上报开关
	 * @param isMtaEnable MTA崩溃上报开关
	 * @return void
	 */
	void WGEnableCrashReport(bool isRdmEnable, bool isMtaEnable);

	/*! @brief 数据上报
	 *
	 * 自定义数据上报
	 * @param name 事件名称
	 * @param body 事件内容
	 * @param isRealTime 是否实时上报
	 * @return void
	 */
	void WGReportEvent(unsigned char* name, unsigned char * body, bool isRealTime);

	/*!
	 * 传入需要测速的地址(或IP)列表, 测速后测试结果上报到灯塔,
     *     地址形如: http://180.153.81.37/monitor/monitor.jsp, IP如: 119.147.19.241:80 (需要端口号)
     * @param 需要测速的地址(IP)列表
	 */
	void WGTestSpeed(std::vector<std::string> &addrList);

	/*! @brief SDK版本
	 *
	 *返回sdk版本
	 * @return const char* 版本字符串
	 */
	const std::string WGGetVersion();

	const std::string WGGetChannelId();
	/*!
	 * 检查平台是否安装(手Q或者微信)
	 */
	bool WGIsPlatformInstalled(int platform);

	/*!
	 * 检查平台是否支持SDK API接口
	 */
	bool WGIsPlatformSupportApi(int platform);
	
	const std::string WGGetRegisterChannelId();
	void WGRefreshWXToken();

	const std::string WGGetPf();
	const std::string WGGetPfKey();

	/*!
	 * 获取最优的访问IP
	 */
	const int WGGetBestSchedulingIp(SchedulingInfo & ipPort, std::vector<std::string> &denyIpList);

	void WGChangeEnv(int env);
	static WGPlatform* GetInstance();
	WGPlatformObserver* GetObserver() const;

protected:

	WGPlatform() :
			m_pNotify(0) {

	}
	;

	void setWakeup(WakeupRet& wakeup);
	WakeupRet& getWakeup();

	void setLoginRet(LoginRet& lr);
	LoginRet& getLoginRet();

private:
#if defined ANDROID
	JavaVM* m_pVM;
#endif
	static WGPlatform m_Instance;
	WGPlatformObserver* m_pNotify;
	WakeupRet m_lastWakeup;
	LoginRet m_lastLoginRet;
	bool needDelayWakeupNotify;
	bool needDelayLoginNotify;
};

#endif
