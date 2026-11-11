//
//  GachaMgr.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 16/8/30.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef GachaMgr_h
#define GachaMgr_h

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "NetworkData.h"

namespace Message
{
    void NotifySyncActivityData(bool i_success);
    void NotifyDrawFinish();
    void NotifyTutorialResponse();
    void NotifyTutorialResponseInner();
}

enum InitState
{
    GACHA_NOT_INITIALIZING,
    GACHA_INITIALIZING
};

enum TutorialStep
{
	Gacha_None,
	Gacha_Normal_Draw,
	Gacha_Epic_Draw,
	Gacha_Avatar_Draw,
    Gacha_Legend_Draw,
};

struct CurrentDrawInfo
{
    CurrentDrawInfo()
    {
        cost = 0;
        mutiDraw = false;
        keyMode = false;
        type = GACHA_NORMAL;
    }
    
    int cost;
    bool mutiDraw;
    bool keyMode;
    GachaType type;
};

struct GachaItemInfo
{
    GachaItemInfo()
    {
        cost = 0;
        rewardCoins = 0;
        freeTimes = 0;
        costMuti = 0;
        rewardCoinsMuti = 0;
    }
    
    int cost;
    int rewardCoins;
    int freeTimes;
    int costMuti;
    int rewardCoinsMuti;
};

struct GachaActivityItemInfo
{
    GachaActivityItemInfo()
    {
        type = 0;
        cost = 0;
        rewardCoins = 0;
        freeTimes = 0;
        costMuti = 0;
        rewardCoinsMuti = 0;
    }
    
    int type;
    int cost;
    int rewardCoins;
    int freeTimes;
    int costMuti;
    int rewardCoinsMuti;
};

class GachaActivityInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(GachaActivityInfo, Sexy::RtObject, Sexy::RtClass);
    
public:    
    std::vector<S2C_NewGachaInfo>     gachaInfos;
    std::vector<GachaActivityItemInfo>     gachaItemInfos;
};

class GachaMgr : public LazySingleton <GachaMgr>
{
public:
    GachaMgr();
    ~GachaMgr();
    
    enum
    {
        LOTTERY_TYPE_NORMAL = 1,
        LOTTERY_TYPE_KEY,
    };
    
    void CreateTargetGachaItem(GachaType i_type, const Rect &i_rect, Widget* i_parent);
    int GetTargetGachaRewardCoin(GachaType i_type, bool isMutiDraw);
    int GetTargetGachaCost(GachaType i_type, bool isMutiDraw);
    int GetTargetGachaFreeTimes(GachaType i_type);
    class GachaItem* CreateTargetGachaItemDraw(GachaType i_type, bool isMutiDraw, const Rect &i_rect, Widget* i_parent);
    MagentoProductPropsPtr FindTargetGachaDrawItem(GachaType i_type, bool isMutiDraw);
    void DoGachaDraw(GachaType i_type, bool isMutiDraw);
    void SetCurrentGachaDraw(const CurrentDrawInfo& i_info) { m_drawInfo = i_info; }
    CurrentDrawInfo& GetCurrentGachaDraw() { return m_drawInfo; }
    void SetDrawLastFreeTimes(int i_type, int i_time);
    void SetDrawFirstPaid(int i_type, bool i_first);
    bool IsDrawFirstPaid(int i_type);
    // Only record for the first draw
    bool IsDrawFirstPaidTemp(int i_type, bool i_muti);
    void SetDrawFirstPaidTemp(int i_type, bool i_first);
    
    int GetGachaKeyMatId(GachaType eType, bool bMulti) const;
    bool IsUseGachaKeyMode(GachaType eType, bool bMulti) const;
    
    void RequestGachaInit();
    void DrawGachaAgain();
    
    bool GetDelayDialog() { return m_delayDialog; }
    void SetDelayDialog(bool i_delay) { m_delayDialog = i_delay; }
    void PopDelayDialog();
    
    void SetInitState(InitState i_state) { m_initState = i_state; }
    bool IsInitializing() { return m_initState == GACHA_INITIALIZING; }
    
    void DoLocalDraw();
    
    int GetTutorialOffset() { return m_tutorialOffset; }
    void SetTutorialOffset(int i_offset) { m_tutorialOffset = i_offset; }

    void DoAdvertiseDraw(GachaType i_type, bool isMutiDraw);// use in advertise
    void DoFreeGachaDraw(GachaType i_type, bool isMutiDraw, int freeNum);// use in tutorial

    void SetTutorialStep(TutorialStep i_step);
    TutorialStep GetTutorialStep() { return m_tutorialStep; }
    void TriggerTutorialShow(TutorialStep i_step);
    void RemoveAllDisplayers();

    void SetObtainTutorialAvatar(bool flag);
    bool GetObtainTutorialAvatar();

    void SetObtainTutorialEpicDraw(bool flag) { m_obtainEpicDrawflag = flag; }
    bool GetObtainTutorialEpicDraw() { return m_obtainEpicDrawflag; }

    void SetObtainTutorialLegendDraw(bool flag) { m_obtainLegendDrawflag = flag; }
    bool GetObtainTutorialLegendDraw() { return m_obtainLegendDrawflag; }

private:    
    MagentoCategoryPropsPtr m_storeProps;
    CurrentDrawInfo m_drawInfo;
    std::vector<GachaItemInfo> m_itemInfos;
    bool m_delayDialog;
    bool m_firstDrawNormalTemp;
    bool m_firstDrawRareTemp;
    InitState m_initState;
    int m_tutorialOffset;
    TutorialStep m_tutorialStep;
    std::vector<class GachaItemDisplayer*> m_displayers;
    bool m_obtainAvatarflag;
    bool m_obtainEpicDrawflag;
    bool m_obtainLegendDrawflag;
    
    bool GachaDrawItemEqual(GachaType i_type, bool isMutiDraw, const std::string& i_name);
    
    void RefreshActivity();
    void SyncActivityData(const GachaActivityInfo& i_data);
    
    void OnCanceledDraw();
    void OnGachaDrawResult(bool i_success);
    void OnNetworkError(int erroId, const std::string& i_reqID);
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

#endif /* GachaMgr_h */
