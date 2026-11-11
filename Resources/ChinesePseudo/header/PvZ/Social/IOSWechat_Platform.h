//
//  WechatPlatform.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-9-28.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WechatPlatform_h
#define PlantsVersusZombies2_WechatPlatform_h

//#include "Precompile.h"
#include "core.h"
#include "IWechat_Platform.h"

class IOSWechatPlatform : public IWechatPlatform
{
public:
    IOSWechatPlatform();
    
    void Initialize();
    
    void DoShare(const std::string& i_url, bool toTimeLine);
    
    bool IsWeChatInstalled();
};

#endif
