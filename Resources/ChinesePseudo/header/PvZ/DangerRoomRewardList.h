//
//  DangerRoomRewardList.h
//  PlantsVersusZombies2
//
//  Created by Li, Jie (Jeffty) on 15/9/15.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomRewardList__
#define __PlantsVersusZombies2__DangerRoomRewardList__

#include "PVZDB.h"
#include "ProfileMgr.h"
#include "Color.h"
#include "UIHelper.h"

struct DangerRoomRewardItems
{
    std::vector<int> plantPiecesCount;
    int coins;
    int gems;
};

class DangerRoomRewardList: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(DangerRoomRewardList, Sexy::RtObject, Sexy::RtClass);
    
    std::vector<DangerRoomRewardItems> m_ItemList;
    
    DangerRoomRewardItems m_DefaultItem;
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomRewardList__) */
