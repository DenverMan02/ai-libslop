//
//  RedPacketRewardInfo.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-2-3.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_RedPacketRewardInfo_h
#define PlantsVersusZombies2_RedPacketRewardInfo_h

#include "RtObject.h"
#include "RedPackOpenUI.h"
#include "Utils.h"

struct RewardElementInfo
{
    std::string strRewardName;
    int         iCount;
    int         iWeight;
    
    RewardElementInfo() {}
};

struct RankRewardEntity
{
    std::string strRewardName;
    int         iCount;
};

struct RedPacketRankRewardInfo
{
    ValueRange  valueRange;
    std::vector<RankRewardEntity> vRankReward;
};

enum LaternRiddleType
{
    NewYear,
    DragonBoat
};

struct LaternRiddleDisplayConfig
{
    std::string strTopicName;
    std::string strImageLaternRiddleTitle;
    std::string strImageLaternRiddleTitleStr;
    std::string strAnimZongzi;
    std::string strAnimZongziOpen;
    std::string strImageBuy1;
    std::string strImageBuy10;
    std::string strImageLittleIcon;
    std::string strImageBigIcon;
    std::string strImageRewardTitleStr;
    std::string strImageRewardAvatar;
    std::string strImagePlant;
    std::string strRewardPlant;
};

#define GETLRD() gLawnApp->GetRedPacketRewardInfo().GetCurrentDisplayConfig()

/*
#define WEAKIMAGE(__VarName__, __strImageName__)    \
RtWeakPtr<Image> __VarName__ = gLawnApp \
->mResourceManager  \
->GetResourceForStringIdT<Image>    \
(__strImageName__);
*/

#define WEAKIMAGE(__VarName__, __strImageName__)    \
CachedUIResourcePtr<Image> __VarName__(__strImageName__);

class RedPacketRewardInfo : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(RedPacketRewardInfo, Sexy::RtObject, RtClass);
    
    RedPacketRewardInfo();
    
    std::vector<RewardElementInfo>& GetConfig()      { return m_vRewardElementInfo;      }
    
    std::vector<RewardElementInfo>& GetExtraConfig() { return m_vExtraRewardElementInfo; }
    
    std::vector<RedPacketRankRewardInfo>& GetRedPacketRankRewardConfig() { return m_vRedPacketRankRewardInfo; }
    
    std::vector<LaternRiddleDisplayConfig>& GetRiddleDisplayConfig() { return m_vLaternRiddleDisplayConfig; }
    
    LaternRiddleType& GetCurrentType() { return m_eCurrentType; }
    
    LaternRiddleDisplayConfig& GetCurrentDisplayConfig() { return m_vLaternRiddleDisplayConfig[m_eCurrentType]; }
    
    std::vector< std::vector<RedPackContent> > GetPrizePool(int iOpenNum);
    
    RedPacketRankRewardInfo* GetRankRewardInfo(int iRank);
    
    void InitDate();
    
private:
    
    int GetTotalWeight();
    
    RewardElementInfo* GetReward();
    
    bool UseExtraElement();
    
    int DropCount();
    
private:
    
	std::vector<RewardElementInfo> m_vRewardElementInfo;
    std::vector<RewardElementInfo> m_vExtraRewardElementInfo;
    std::vector<RedPacketRankRewardInfo> m_vRedPacketRankRewardInfo;
    std::vector<LaternRiddleDisplayConfig> m_vLaternRiddleDisplayConfig;
    LaternRiddleType               m_eCurrentType;
};

#endif
