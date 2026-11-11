//
//  NationalDayRewardConfigInfo.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-9-01.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_NationalDayRewardConfigInfo_h
#define PlantsVersusZombies2_NationalDayRewardConfigInfo_h

#include "RtObject.h"


enum NationalDayRewardType
{
    NDRT_PLANT,
    NDRT_PLANTFRAGMENT
};

struct NationalDayRewardItem
{
    std::string strRewardName;
    NationalDayRewardType eRewardType;
    int iCount;
    int iWeight;
    
    NationalDayRewardItem()
    {
        iCount = 0;
        iWeight = 0;
        strRewardName = "";
        eRewardType = NDRT_PLANTFRAGMENT;
    }
};

struct NationalRewardFromServer
{
    std::string rewardName;
    NationalDayRewardType rewardType;
    int rewardCount;
    
    NationalRewardFromServer()
    {
        rewardName = "";
        rewardType = NDRT_PLANTFRAGMENT;
        rewardCount = 0;
    }
};

struct NationalDayActivityDate
{
    NationalDayActivityDate()
    : iCost(35), strDate("[NATIONALDAY_ACTIVE_TIME_1]")
    , strContent("[NATIONALDAY_ACTIVE_CONTENT]")
    {}
    
    int iStart;
    int iEnd;
    int iCost;
    std::string strDate;
    std::string strContent;
    std::string strImageBanner;
    std::vector<NationalDayRewardItem> vNationalDayRewardItemList;
};


class NationalDayRewardConfigInfo : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(NationalDayRewardConfigInfo, Sexy::RtObject, RtClass);
    
    NationalDayRewardConfigInfo();
    
    void InitDate();
    
    std::vector<NationalDayActivityDate>& GetNationalDayActivityDateList() { return m_vNationalDayActivityDateList; }
    
private:
    
    std::vector<NationalDayActivityDate> m_vNationalDayActivityDateList;
    
};

class NatinalDayRewardMgr
{
    
public:
    
    virtual ~NatinalDayRewardMgr() {};
    
    static NatinalDayRewardMgr& GetInstance();
    
    int TodayInNationalDay(time_t iTimeStamp);
    
    bool CanDoNationalActivity();
    
    int  GetIntervalTime();
    
    int CalcCurrentActiveIndex(time_t iTimeStamp);
    
    NationalDayActivityDate* GetCurrentNationalDayActivityDate();
    void SetRewardItem(NationalRewardFromServer &item);
    NationalDayRewardItem* GetRewardItem();
    
    NationalDayRewardItem& GetMyRewardItem() { return m_stNationalDayRewardItem; }
    
    void SetMyRewardItem(NationalDayRewardItem& item) { m_stNationalDayRewardItem = item; }
    
private:
    
    int GetTotalWeight(NationalDayActivityDate* pDate);
    
protected:
    
    NatinalDayRewardMgr();
    
private:
    
    NationalDayRewardItem m_stNationalDayRewardItem;
    
};

#endif
