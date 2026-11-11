//
//  BossChallengeInfo.h
//  PlantsVersusZombies2
//
//  Created by xiao on 16/8/31.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef BossChallengeInfo_h
#define BossChallengeInfo_h

#include "Widget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "Common.h"
#include "UIBossMedalLottery.h"

class PVZ2UIScrollingWidget;

//struct BossChallengeRankDetail
//{
//    int iBeginRank;
//    int iEndRank;
//    int iDiamond;
//    int iCoin;
//    int iHeadFrameID;
//    int iHeadImageId;
//};


class BossChallengeInfoRankItem : public Sexy::Widget
{
public:
    static BossChallengeInfoRankItem* Create(const BossChallengeRankServerData& pRankDetail, bool bIsLastItem);
    
    void Init(const BossChallengeRankServerData& pRankDetail, bool bIsLastItem);
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    
private:
    SexyString GetRankString() const;
    SexyString GetRankDesc() const;
    
private:
    BossChallengeRankServerData rankDetail;
    bool m_bIsLastItem = false;
};


class BossChallengeInfo : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    BossChallengeInfo();
    virtual ~BossChallengeInfo();
    
    void InitRankList(const std::vector<BossChallengeRankServerData>& vecRankDetails);
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    
    virtual void ScrollTargetReached( Sexy::ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( Sexy::ScrollWidget* scrollWidget ) override {}
    
private:
    const std::vector<BossChallengeRankServerData> GetRankServerData() const;
    
    
private:
    PVZ2UIScrollingWidget* m_pScrollingWidget;
};

#endif /* BossChallengeInfo_h */
