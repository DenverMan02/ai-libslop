//
//  WechatMgr.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-9-28.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WechatMgr_h
#define PlantsVersusZombies2_WechatMgr_h

#include "core.h"

class IWechatPlatform;

class WechatMgr : public LazySingleton<WechatMgr>
{
public:
    WechatMgr();
    
    void InitializeSDK();
    
    void DoWechatShare(const std::string& i_url, bool toTimeLine);
    
    bool IsWechatInstalled();
    
private:
    IWechatPlatform* m_wechat;
};

#endif
