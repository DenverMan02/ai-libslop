// UIInvitation.h
// Create by lfy in 2023.07.20
//

#ifndef __UIINVITATION_H__
#define __UIINVITATION_H__

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "RepeatUIComponent.h"
#include "EffectAnim_UIAnim.h"
#include "UIUtil.h"
enum
{
    SHARED_BTN_SAVE = 98,
    SHARED_BTN_SHARE = 99,
    
    INVATATION_BTN_CLOSE = 100,
    INVATATION_BTN_RECRUITMENT,
    // INVATATION_BTN_RECRUITMENT_ORDER,
    // INVATATION_BTN_RECRUITMENT_TASK,
    // INVATATION_BTN_RECRUITMENT_GACHA,

    INVATATION_BTN_RECRUITMENT_SHARED,
    INVATATION_BTN_RECRUITMENT_HELP,
    INVATATION_BTN_RECRUITMENT_TIPS,
    INVATATION_BTN_RECRUITMENT_COPY_CODE,

    INVATATION_BTN_ORDER_OK,
};

// struct InvitationBonus
// {
//     InvitationBonus()
//     : m_objectId(0)
//     , m_quantity(0)
//     {}

//     int m_objectId;
//     int m_quantity;
// };

struct InvitationInfo
{
    InvitationInfo()
    {
        m_inviteCount = 0;
        m_inviteStarCount = 0;
    }

    int m_inviteCount;
    int m_inviteStarCount;
};

struct InvitationTask
{
    InvitationTask()
    : m_condition(false)
    , m_type(0)
    , m_status(false)
    {}
    int m_condition;
    bool m_status;
    int m_type;
    std::vector<S2C_BonusInfo> m_bonus;
};

struct InvitationPlayerInfo
{
    InvitationPlayerInfo()
    {
        m_playerId = "";
        m_playerName = "";
        m_playerStar = "";
        m_createTime = "";
    }

    std::string m_playerId;
    std::string m_playerName;
    std::string m_playerStar;
    std::string m_createTime;

};

struct recordData
{
    std::string recordName;
    std::string recordTimeStr;
    time_t recordTime;
};

struct InvitationLottery
{
    InvitationLottery():
    PoolID(0),
    Obtained(false)
    {

    }

    std::vector<S2C_BonusInfo> Content;
    int PoolID;
    std::vector<S2C_BonusInfo> PoolList;
    int Obtained;
};
enum InvitationLotteryState
{
    InvitationLS_Idle,
	InvitationLS_Lotterying,
	InvitationLS_Result,
};
class InvitationRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(InvitationRewardData, INetworkData, RtClass);

    int AwardIndex;
    std::vector<S2C_BonusInfo> RewardList;

};

class InvitationLotteryPanel: public UISingletonDialog<InvitationLotteryPanel> 
{
    friend class UIInvitation;
public:
	InvitationLotteryPanel();
	virtual ~InvitationLotteryPanel();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "InvitationLotteryPanel"; }
 	virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

	void InitView(const std::vector<InvitationLottery>& i_bonus);
	void StartLottery(int i_index);

    void RequestLottery();

protected:
    void LotteryEffect();
	void LotteryEffectFinish(const std::string& i_animLabel);
    void ShowBonusUI();
	void CloseBonusUI();

    void DetermineSelect(class UIMessageBox* box, int buttonID);
    void RequestChest(int i_index);

	bool m_bonusShown;
	class PopingBonusUI* m_lotteryBonusUI = nullptr;
	std::vector<InvitationLottery> m_bonusInfoVec;
    std::vector<class UIRewardFrameSelect*> m_frameVec;

	int m_bonusIndex = 0;
    int m_selectIndex = -1;
	float m_speed = 0.f;
	int m_currentStep = 0;
    int m_speedUpEndStep = 0;
    int m_speedDownEndStep = 0;
    int m_rollingEndStep = 0;
	pvztime_t m_nextItemTime = 0.f;
    int bonussize = 0;
    int bonuslistsize = 0;
	EffectAnim_UIAnim m_bonusEffect;
	InvitationLotteryState m_state = InvitationLS_Idle;
	
	void UpdateSelectFrame();
    void StartNextLoop();
	void InitSteps();
	void ShowBonus();
	bool AlmostThere();
	void SelectNext();
	bool CanSelectNext();
	bool TryToSelectNext();
    bool CurrentGem = false;
};

class InvitationData : public INetworkData
{
public:
    RT_CLASS_DEFINE(InvitationData, INetworkData, RtClass);

    InvitationData()
    {
        m_currentActivityID = 0;
        m_invitationCode = "";
        m_canBind = false;
        m_sharedState = false;
        m_bindState = false;
        m_sharedBonus.clear();
        m_bindBonus.clear();
        m_task.clear();
        m_playerInfo.clear();
        m_lotteryCostNum = 0;
        m_lotteryPool.clear();
        m_itemNum = 0;
    }

    int m_currentActivityID;
    std::string m_invitationCode;
    bool m_canBind;
    bool m_sharedState;
    bool m_bindState;
    std::vector<S2C_BonusInfo> m_sharedBonus;
    std::vector<S2C_BonusInfo> m_bindBonus;
    std::vector<InvitationTask> m_task;
    InvitationInfo m_invitationInfo;
    std::vector<InvitationPlayerInfo> m_playerInfo;
    int m_lotteryCostNum;
    std::vector<InvitationLottery> m_lotteryPool;
    int m_itemNum;
};

class UIInvitationRecordItem : public Widget
{
public:
    void InitView(const recordData& i_data);
    virtual void Draw(Graphics* i_g) override;

protected:    
    // SexyString m_name;
    std::string m_time;    
    recordData m_data;    
};

class UIInvitation : public UISingletonDialog<UIInvitation>, public UI::TabControlListener, public Sexy::ScrollWidgetListener, public Sexy::EditListener
{
public:	

	UIInvitation();
    virtual ~UIInvitation() { RemoveAllWidgets(true, true); }
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIInvitation"; }
    virtual void                            Update() override;
	virtual void							ButtonDepress(int i_id) override;

    virtual void TabSelectionChanged(int tabID) {}
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}	
    
private:

    void initSharedButton();
    void sharedImmediately();
	void showMainTips();
	void closeMainTips();
    void copyInvitatedCode();
    void showMainHelp();
    void closeMainHelp();

    void initOrder(const std::vector<S2C_BonusInfo>& i_bindBonus);
    void initTasks();
    void initLottery();

    void initInvitedRecode(std::vector<InvitationPlayerInfo>& i_playerInfo);
    void initInvitedCode(const std::string& i_code);
    void initInvitedNum();
    void initSharedBtn(bool i_visiable);
    void sendShared();    
    
	void UpdateTimer();
public:
    void RefreshTokenNum();
    bool CanLottery();
    int  GetCurrentIntegral();
    // void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void AddIntegral(int i_num);
    void GetCurrentGem();
    int GetCurrentGemCost();
    void    LockButton();
    void    UnlockButton();

private:
    class ActivityDescriptionUI* m_descriptionUI1;// main tips ui.    
    class ActivityDescriptionUI* m_descriptionUI2;
    class EditWidget* m_searchInput;
    std::string m_invitedCode;
    time_t m_activityExpireTime;// activity expire time. 
    int m_invitedNum;       
    InvitationData m_activityData;
    class InvitationLotteryPanel* m_lotteryPanel;   
    std::vector<recordData> m_recordData;
};

class InvitationTaskData : public INetworkData
{
public:
    RT_CLASS_DEFINE(InvitationTaskData, INetworkData, RtClass);
    std::vector<S2C_BonusInfo> bonusList;
};

class InvitationTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(InvitationTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;

protected:
    virtual void RequestReward() override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g);

};

class UIInvitationSharedDetail : public UISingletonDialog<UIInvitationSharedDetail>
{
public:
	UIInvitationSharedDetail() {}
	virtual ~UIInvitationSharedDetail() { }

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIInvitationSharedDetail"; }
	virtual void ButtonDepress(int i_id) override;

	void LoadData(const InvitationData& i_data);	
private:
    
    void initView();
    void DoShare();
    void DoSave();
    void requestShared();       // daily shared

    InvitationData m_data;
};



class UIInvitationMgr : public LazySingleton<UIInvitationMgr>
{
public:
	UIInvitationMgr() {}
	virtual ~UIInvitationMgr() {}

    void LoadData(const InvitationData& data);
    const InvitationData& GetData() const;

    void RequestNetwork();
    bool SetNotice();
private:
    // void TestData();

private:
    InvitationData m_data;
};

#endif
