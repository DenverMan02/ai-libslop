/*
 * ShareDriverMgr.h
 *
 *  Created on: 2022-8-9
 *      Author: admin
 */

#ifndef SHAREDRIVERMGR_H_
#define SHAREDRIVERMGR_H_

#include "core.h"
#include "IShareDriver.h"
#include "Singleton.h"

class ShareDriverMgr : public LazySingleton<ShareDriverMgr>
{
public:
	ShareDriverMgr();
	~ShareDriverMgr();

    void InitializeSDK();

    void Share(SharePlatform i_platform, ScreenInfo i_info);

    bool IsClientInstalled(SharePlatform i_platform);

    void SaveScreenImageToGallery(ScreenInfo i_info);

    void SaveScreenImageToLocal(ScreenInfo i_info);

    bool DeleteLocalImage(ScreenInfo i_info);

private:
    IShareDriver* m_shareDriverMgr;
};


#endif /* SHAREDRIVERMGR_H_ */
