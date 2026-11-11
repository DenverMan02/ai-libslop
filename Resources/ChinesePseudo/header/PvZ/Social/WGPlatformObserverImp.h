/*
 * WGPlatformObserverImp.h
 *
 *  Created on: 2013-7-29
 *      Author: wuxj
 */

#ifndef __WGPLATFORMOBSERVERIMP_H__
#define __WGPLATFORMOBSERVERIMP_H__

#include "Common.h"
#if SEXY_IS_WECHAT_ENABLED

#include "WGPlatformObserver.h"

class WGPlatformObserverImp : public WGPlatformObserver
{
	public:
		WGPlatformObserverImp();
		virtual ~WGPlatformObserverImp();

		virtual void OnLoginNotify(LoginRet& loginRet);
		virtual void OnShareNotify(ShareRet& shareRet);
		virtual void OnWakeupNotify(WakeupRet& wakeupRet);
};

#endif
#endif /* __WGPLATFORMOBSERVERIMP_H__ */
