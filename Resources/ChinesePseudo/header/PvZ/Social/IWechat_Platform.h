//
//  IWechat_Platform.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-9-28.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_IWechat_Platform_h
#define PlantsVersusZombies2_IWechat_Platform_h

class IWechatPlatform
{
public:
    static IWechatPlatform* CreateWechatPlatform();
    
    virtual void Initialize() = 0;
    
    virtual void DoShare(const std::string& i_url, bool toTimeLine) = 0;
    
    virtual bool IsWeChatInstalled() = 0;
};

#endif
