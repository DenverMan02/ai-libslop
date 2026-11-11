//
//  ConsumptionRewardInfo.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-5-26.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ConsumptionRewardInfo_h
#define PlantsVersusZombies2_ConsumptionRewardInfo_h

#include "Precompile.h"
#include "RtObject.h"

struct RewardItem
{
    std::string strRewardItemName;
    std::string strItemDesc;
    int         iCount;
    int         iLevel;
    int         iDesValue;
    int         iExtra;
    
    RewardItem()
    : iCount(1)
    , iLevel(1)
    {
        
    }
};

struct TopicItem
{
    std::string strTopic;
    std::string strLawnStringNotify;
    std::string strImageButton;
    std::string strImageTitle;
    std::string strPrefix;
    std::vector<RewardItem> vRewardItem;
    
    TopicItem()
    : strTopic("act_1")
    , strLawnStringNotify("[CONSUMPTION_NOTIFY]")
    , strImageButton("IMAGE_UI_HUD_WORLDMAP_BIG_ICON_CONSUMPTION_1")
    {
        
    }
};

class ConsumptionRewardInfo : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(ConsumptionRewardInfo, Sexy::RtObject, RtClass);
    
    ConsumptionRewardInfo();
    
    void InitDate();
    TopicItem SetCurrentTopicItemFromServer(std::string avatarName);
    TopicItem GetCurrentTopicItem();
    
    int GetCurrentTopicIndex();
    
private:
    
    bool IsExsit(std::string& strPrefix, std::string& strPlantName);
    
    std::string GetMainPlantName(TopicItem& item);
    
    void RepalceReward(TopicItem& item, std::string& strNew);
    
    std::vector<RewardItem>::iterator GetReplaceItem(TopicItem &item);
    
    void ReplaceExtra(TopicItem& item);
    
private:
    
    std::vector<TopicItem> m_vTopicItem;
    std::vector<std::string> m_vExtraPlantList;
};

#endif
