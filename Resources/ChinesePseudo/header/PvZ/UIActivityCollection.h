#ifndef ActivityCollection_H_
#define ActivityCollection_H_

#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "PVZ2UIButton.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

enum ActivityCollectionTab : int
{
    ACT_START = 0,
    ACT_LuckBag,
    ACT_PlayerSurvey,
    ACT_LimitGroupBuy,
    ACT_RichMan,
    ACT_Festival_Piggy_Bank_2019,
    ACT_RechargeDailySignActivity,
    ACT_LimitedSummon,
    ACT_National_LevelOfDay_Entrance,
    ACT_DiscountShopActivity,
    ACT_Carnival,//10
    ACT_OneYuan,
    ACT_GoldenEgg,
    ACT_BossChallenge,
    ACT_VaseBreaker,
    ACT_WishingPool,
    ACT_SecretStore,
    ACT_Anniversary_Treasure,
    ACT_NewYearGoods,
    ACT_PlantCultivate,
    ACT_TENYEARRECORD,//20
    ACT_PartyAssist,
    ACT_CustomVoting,
    ACT_CallofWish,
    ACT_DaveKitchen,
    ACT_FightZodiac,//25
    ACT_DragonTreasure,
    ACT_NewYearGiftBox,
    ACT_END
};

struct ActivityShortInfo
{
    int ActivityID;
    int Sequence;
    int Open;
};

class ActivityCollectionData : public INetworkData
{
public:
	RT_CLASS_DEFINE(ActivityCollectionData, INetworkData, RtClass);

	bool IsActivityClose(int activityID);

    std::vector<ActivityShortInfo> ActivityInfoList;
    std::string Icon;
    std::string Title;
    int NewPlayer;
};

class ActivityCollectionPriviewData : public INetworkData
{
public:
	RT_CLASS_DEFINE(ActivityCollectionPriviewData, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> RewardPreview;
};

////////////////////////////////////////////////////////////////////////////

class ActivityCollectionContainer
{
public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) {};
    virtual void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) {};
};


class ActivityCollectionTabBase
{
public:
	ActivityCollectionTabBase();
	virtual ~ActivityCollectionTabBase();

    void InitView(int i_tabID, PVZ2UIButton* i_tabButton, Widget* i_tabWidget);
	void SetSelect(bool setting);

public:
    int GetTabID() { return m_tabID; }
    PVZ2UIButton* GetTabButton() { return m_pTabBtn; };
    Sexy::Widget* GetTabWidget()  { return m_pTabWidget; }
    ActivityCollectionContainer* GetTabContainer()  { return m_pTabContainer; }
    void SetTabContainer(ActivityCollectionContainer* i_pTabContainer);

    bool HasContainerInit() { return m_containerInit; }
    void SetContainerInit(bool i_flag) { m_containerInit = i_flag; }
    void SetUnlock(bool unlock) { m_unlock = unlock; }
    bool GetUnlockState() { return m_unlock; }

protected:
    int m_tabID;
    PVZ2UIButton* m_pTabBtn;
    Widget* m_pTabWidget;
    bool m_containerInit;
    ActivityCollectionContainer* m_pTabContainer;
    bool m_unlock;
};

class UIActivityCollection : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    UIActivityCollection();
    virtual ~UIActivityCollection();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void CreateView();

    static bool CheckActivityOpenAtLeastOne();

private:
//    ActivityCollectionTab GetTabByActivity(ActivityTypeID i_id);
//    ActivityTypeID GetActivityByTab(ActivityCollectionTab i_tab);
    ActivityCollectionTab GetTabByActivity(int i_id);
    int GetActivityByTab(ActivityCollectionTab i_tab);

    void SelectTab(int i_tab);
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void CheckTabButton(ActivityCollectionTab i_tab);

    std::map<ActivityCollectionTab, ActivityCollectionTabBase*> m_tabMap;
private:
    bool m_hasInitView;
//    std::map<ActivityCollectionTab, ActivityTypeID> m_activityList;
    std::map<ActivityCollectionTab, int> m_activityList;
public:
    int m_currentTab;
    ActivityCollectionData m_cacheData;
};



class ActivityCollectionManager : public LazySingleton<ActivityCollectionManager>
{
public:


};

#define gActivityCollectionMgr ActivityCollectionManager::GetInstancePtr()


#endif

