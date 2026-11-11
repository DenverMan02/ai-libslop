//
//  LevelOfTheDayConfigInfo.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-9-01.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelOfTheDayConfigInfo_h
#define PlantsVersusZombies2_LevelOfTheDayConfigInfo_h

#include "RtObject.h"
#include "NameMapper.h"

const int coin2018 = 23024;
//const int statue2019 = id_mat_renaissance_challenge_statue;

enum LevelOfTheDayRewardType
{
    THEDAYREWARDTYPE_COIN,
    THEDAYREWARDTYPE_GEM,
    THEDAYREWARDTYPE_PLANT,
    THEDAYREWARDTYPE_PLANTPIECE,
    THEDAYREWARDTYPE_AVATARPIECE,
    THEDAYREWARDTYPE_COIN2018,
    THEDAYREWARDTYPE_STATUE2019,
};

struct TheDayRewardItem
{
    std::string strItemName;
    
    LevelOfTheDayRewardType eType;
    int         iWeight;
    int         iCount;
    
    SexyString GetDisplayText() const;
};

struct TheDayItem
{
    TheDayItem() {}
    
    int iStartDate;
    int iEndDate;
    
    std::string strDayName;
    
    //header
    std::string strImageBannerHeader;
    std::string strLawnStringBannerHeader;
    std::string strLawnStringBannerHeadDesc;
    
    //Footer
    std::string strImageBannerFooter;
    std::string strLawnStringBannerFooter;
    std::string strLawnStringBannerFootDesc;
    
    std::string strAnimPinataArt;
    std::string strAnimConfettiEffect;
    std::vector<TheDayRewardItem> vRewardList;
    std::vector<TheDayRewardItem> vExtraRewardList;
    std::vector<std::string> vLevelName;
    std::vector<int> vCountList;
};

class LevelOfTheDayConfigInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(LevelOfTheDayConfigInfo, Sexy::RtObject, RtClass);
    
    LevelOfTheDayConfigInfo();
    void InitDate();
    std::vector<TheDayItem>& GetTheDayItemList() { return m_vTheDayItemList; }
    
private:
    std::vector<TheDayItem> m_vTheDayItemList;
};

class LevelOfTheDayMgr
{
public:
    virtual ~LevelOfTheDayMgr() {};
    
    static LevelOfTheDayMgr& GetInstance();
    TheDayItem* GetCurrentTheDayItem();
    
//    TheDayItem* GetTheDayItem(const std::string& strDayName);
    TheDayItem* GetTheDayItem(const std::string strDayName = "Birthdayz");
    void SetCurrentDayName(std::string strDayName) { m_strCurrentDayName = strDayName; }
    void SpawnEffectFromTop(Sexy::Widget* pParentWidget, int iX, int iDis);
    void InitRewardPool();
    std::vector<TheDayRewardItem>& GetTheDayRewardItemPool() { return m_vTheDayRewardItem; }
    
    bool IsTheLastDay();
    bool IsDataValid();
    int  GetDayInterval();
    int  GetRealInterval();
    
    std::string& GetCurrentLevelName();
    void SetNeedPopupAcion(bool bNeed) { m_bNeedPopupAction = bNeed; }
    bool GetNeedPopupAcion() { return m_bNeedPopupAction; }
    void CleanTheDayRewardItemPool() { m_vTheDayRewardItem.clear(); }
    void AddTheDayRewardItemPool(TheDayRewardItem& i_item) { m_vTheDayRewardItem.push_back(i_item); }
    
    int  GetTotalRewardCount() const;
    void SetTotalRewardCount(int i_count);
    
protected:
    LevelOfTheDayMgr();
    
private:
    int GetTotalWeight(std::vector<TheDayRewardItem>& vList);
    void RandomInPool(int iCount, std::vector<TheDayRewardItem>& vPoolList);
    
private:
    std::string m_strCurrentDayName;
    std::vector<TheDayRewardItem> m_vTheDayRewardItem;
    
    bool  m_bNeedPopupAction;
    int   m_totalRewardCount;
};

#endif
