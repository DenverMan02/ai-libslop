/*
 * UIPartyAssist.h
 *
 *  Created on: 2023-9-5
 *      Author: zhousen
 */

#ifndef UIPARTYASSIST_H_
#define UIPARTYASSIST_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "UIListener.h"
#include "RepeatUIComponent.h"
//#include "NameMapperEnum.h"
#include "UICornucopia.h"
#include "UIUtil.h"

namespace Message
{

}
//////////////////
// bonus detail
//////////////////
struct PartyAssistBonusInfo
{
	PartyAssistBonusInfo() {
		ObjectID = 4015;
		Quantity = 111;
		Status = 0;
		Ratio = 44;
	}

	int ObjectID;
	int Quantity;
	int Status;// 2: has got, 1 : mustgot, 0 : not .
	float Ratio;// percentage
};

/////////////////////////
/// wish bonus detail
/////////////////////////
struct PartyAssistWishBonusInfo
{
	PartyAssistWishBonusInfo() {
		ObjectID = 3008;
		Quantity = 100;
		Status = 0;
	}

	int ObjectID;
	int Quantity;
	int Status;// 1 : choose , 0 : not choose
};

struct PartyTaskInfo
{
    PartyTaskInfo(){}

    int ObjectID;
	int Quantity;
	int Status;
};

////////////////////
// main data v303
////////////////////
class PartyAssistMainData : public INetworkData
{
public:
    RT_CLASS_DEFINE(PartyAssistMainData, INetworkData, RtClass);

    PartyAssistMainData() {
    	ActivityRoundNumber = 0;
    	CurrentRoundLevel = 0;
    	Tickets = 0;
    	FinalBonusPlant = "peashooter";
    	FinalBonusPlantAvatarLayer = "custom_01";
    	AssistTicketList = {1,1,1,2,2,2,3,3,3,4};
    	EnableChooseWish = false;
    }

    int ActivityRoundNumber;// round number
    int CurrentRoundLevel;// current round level
    std::vector<int> AssistTicketList;
    std::vector<std::vector<PartyAssistWishBonusInfo> > WishChooseList;
    // std::map<std::string, int> TaskInfos;// for tasks
    std::vector<PartyTaskInfo> TaskInfos;
    int Tickets;
    std::vector<S2C_BonusInfo> RewardPreview;
    std::vector<PartyAssistBonusInfo> NextLevelBonusList;
    std::vector<PartyAssistBonusInfo> AllBonusList;
    std::string FinalBonusPlant;// plant name
    std::string FinalBonusPlantAvatarLayer;// plant avatar layer
    std::vector<std::vector<S2C_BonusInfo>> PresentList;
    int EnableChooseWish;
};

/////////////////
// assist data
/////////////////
class PartyAssistData : public INetworkData
{
public:
    RT_CLASS_DEFINE(PartyAssistData, INetworkData, RtClass);

    PartyAssistData() {
    	Tickets = 1;
    	CurrentLevel = 1;
    }

    std::vector<S2C_BonusInfo> BonusList;
    int Tickets;
    int CurrentLevel;
};

/////////////////////////
// Party Assist Main
/////////////////////////
class UIPartyAssist : public UISingletonDialog<UIPartyAssist>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
	UIPartyAssist();
    virtual ~UIPartyAssist();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UIPartyAssistMain"; }
    virtual void                            Update() override;
	virtual void							ButtonDepress(int i_id) override;

    virtual void TabSelectionChanged(int tabID);
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

private:
	void UpdateTimer();
	void ShowMainTips();
	void CloseMainTips();
	void InitAssist();
	void InitFinalBonusHeadicon(const std::string plant, const std::string avatar);
    void InitPresent();
    void InitTasks();
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    void Assist();
    void Reset(class UIMessageBox* box, int buttonID);
    void ChangeBonusInfo(bool change);

    void GoToPresentShop(UIMessageBox* box, int buttonID);
    void ShowNotEnough();
    void ShowResetTips();
    void Refresh();
    void RefreshLevel();
    void UpdateLevel();
    void RefreshTickets();
    void RefreshResetButton();
    void AssistConfirm(UIMessageBox* box, int buttonID);
	void RefreshTasks();
    
private:
    time_t m_activityExpireTime;
    UIWidgetText* m_countdownTimerText;
    class ActivityDescriptionUI* m_descriptionUI;// main tips ui.
    bool m_showAllBonus;// show all bonus btn
    Widget* m_bonusContainer;
    pvztime_t m_shiningChangeTimeEnd;
    bool m_shiningStatus;
    int m_ticketsCount;
};

//////////////////////////
//
//////////////////////////
class PartyAssistBonusWidget : public UIRewardFrameSelect
{
public:
	PartyAssistBonusWidget(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual ~PartyAssistBonusWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void Init(PartyAssistBonusInfo& data);

	static PartyAssistBonusWidget* CreateUIRewardFrame(int objectId, int num, bool hasFrame);

protected:
	PartyAssistBonusInfo m_data;
	SexyString m_desc;
	Image* m_mustGotImg;
};

/////////////////////////
// PartyAssistMgr
/////////////////////////
class PartyAssistMgr : public LazySingleton<PartyAssistMgr>
{
public:
	PartyAssistMgr();
	virtual ~PartyAssistMgr();

    void LoadData(const PartyAssistMainData& data);
    const PartyAssistMainData& GetData() const;
    void RequestNetwork();

private:
    void TestData();

private:
    PartyAssistMainData m_data;
};

//////////////////////////////////////
/// PartyAssistWishingPoolSelectItem
//////////////////////////////////////
class PartyAssistWishingPoolSelectItem : public Sexy::Widget, public Sexy::ButtonListener
{
    friend class PartyAssistWishingPoolSelectLine;
public:
    PartyAssistWishingPoolSelectItem();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void InitView(class PartyAssistWishingPoolSelectLine* i_parent, int i_index, PartyAssistWishBonusInfo i_info);
    void SetSelect(bool i_flag);
    bool CanSelectd() const { return m_canSelect; }

private:
    int m_touchId;
    int m_index;
    bool m_canSelect;
    bool m_selected;

    class PartyAssistWishingPoolSelectLine* m_parent;
    class UIWidgetImage* m_selectedImage;
    SexyString m_des;
    class StoneLotteryItemTipUI* m_tipUI;
};

class PartyAssistWishingPoolSelectLine : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    void Draw(Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(int i_index, std::vector<PartyAssistWishBonusInfo>& i_infos);
    void SelectItem(int i_index);

    int GetSelectItemIndex();

private:
    int m_index;
    Sexy::Image* m_leftImage = nullptr;
    std::vector<PartyAssistWishingPoolSelectItem*> m_itemList;
};

class UIPartyAssistWishingPoolSelect : public UISingletonDialog<UIPartyAssistWishingPoolSelect>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPartyAssistWishingPoolSelect"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SelectLottery();
    void GoToPresentShop(UIMessageBox* box, int buttonID);

private:
    std::vector<PartyAssistWishingPoolSelectLine*> m_lineList;
};



//////////////////////////////////////
/// PartyTaskWidget
//////////////////////////////////////

class PartyTaskData : public INetworkData
{
public:
    RT_CLASS_DEFINE(PartyTaskData, INetworkData, RtClass);
    std::vector<S2C_BonusInfo> bonusList;
};

class PartyTaskWidget : public TemplateTaskWidget
{
public:    
    virtual void InitTask(GeneralTask* i_task);
    void InitData(PartyTaskInfo i_data, int i_index);
    virtual void ButtonDepress(int i_id) override;
protected:
    virtual void UpdateButtonState();
    virtual void DrawProgress(Sexy::Graphics* i_g) {}
    virtual void RequestReward();
    void DrawRewards(Sexy::Graphics* i_g);
private:
    PartyTaskInfo m_data;
    int m_index;
};

class PartyTreasureWidget : public NewTreasureWidget
{
public:
    virtual void Init(int i_index) override;
protected:    
    virtual void OnPurchaseButtonDepress() override;
    void BuyConfirm(class UIMessageBox* box, int buttonID);    
};


#endif /* UIPARTYASSIST_H_ */
