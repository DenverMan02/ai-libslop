/*
 * 	NewPVPSeedBankModule.h
 *
 * 	Created on: 2022-10-13
 */

#ifndef __NEWPVPSEEDBANKMODULE_H__
#define __NEWPVPSEEDBANKMODULE_H__

#include "RtObject.h"

#include "core.h"
#include "GameEventMgr.h"
#include "NewPVPGame.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedBankModule.h"
#include "SeedPacket.h"
#include "UIWidget.h"
#include "UIWidgetImage.h"

enum NewPVPButton
{
	BTN_MAIN_VIEW_BACK = 0,
	BTN_MAIN_VIEW_BOTTOM_TAB_START = 10,

	BTN_TAB_BATTLE_LEISURE_MODE = 20,
	BTN_TAB_BATTLE_COMPETITIVE_MODE = 21,


	BTN_PLANT_UPGRADE = 100,

};

enum NewPVPMainViewTabIndex
{
	NewPVPMainViewTab_invalid = -1,
	NewPVPMainViewTab_battle,

};


class NewPVPSeedBank : public SeedBankNew
{
public:
	RT_CLASS_DEFINE(NewPVPSeedBank, SeedBankNew, RtClass);

	NewPVPSeedBank();
	virtual ~NewPVPSeedBank();

	void SortTurns(std::vector<NewPVPZombieLevelInfo>& i_infos);

	void setZombiePacketInfoList(const std::vector<int>& i_list, int i_current = 0);
	void setPlantPacketInfoList(const std::vector<CurrentSelectedPlantPacketInfo>& i_list, int i_current = 0);

	void onNotifyTurnChanged(int i_current);

   	bool IsMouseOver(const int i_mouseX, const int i_mouseY) override;
   	bool OnTouch(const Sexy::Touch& i_touch) override;
    void Draw(Graphics* i_g) override;

    void fillSeedPackets() override;

    void AddPacket(UIWidgetPtr i_packetWidget);
    void RefreshPackets();
    void SetMaxShowNum(int iVal) { m_maxShowNum = iVal; }

    void setPlantAndZombiePacketNum(int i_plantPacketNum, int i_zombiePacketNum);

    void ShowZombieBank(bool i_visible);
    void EnableSinglePacket(int i_index);
    void RecoverPackets();

protected:
   	void registerForEvents() override;
    void initialize(const uint8 i_packetCount = 0) override;
    void setPacketPositions() override;

    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    int getButtonAt(int x, int y);
    void onGameplayRealStarted();
    void onUpdate() override;

protected:
    int m_curPage;
    int m_maxShowNum;
    Sexy::Rect m_decBtnArea;
    Sexy::Rect m_incBtnArea;
    Sexy::TouchID m_touchIdent;

    std::vector<NewPVPZombiePacketInfo> m_zombiePacketInfoList;
    std::vector<CurrentSelectedPlantPacketInfo> m_plantPacketInfoList;

    int m_plantPacketNum;
    int m_zombiePacketNum;

    float m_scale;
    std::vector<class SeedPacket_NewPVP*> m_packets;
};

typedef RtWeakPtr<NewPVPSeedBank> NewPVPSeedBankPtr;


class SeedPacket_NewPVP : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_NewPVP, SeedPacket, RtClass);

	enum Type
	{
		TYPE_INVALID,
		TYPE_PLANT,
		TYPE_ZOMBIE
	};

    SeedPacket_NewPVP();

    bool IsReady();

	virtual void Draw(Graphics* i_g) override;
    virtual bool OnTouch(const Sexy::Touch& i_touch) override;
    virtual void OnMouseMove(const int i_mouseX, const int i_mouseY) override;

    virtual bool IsAffordable() override;
    virtual bool TryUse(class PacketCursor* pCursor) override;
    virtual void CopyFrom(SeedPacket* pCopy) override;

    const PacketRenderData& GetZombieRenderData() override;

    void SetRare(int i_rare) { m_rare = i_rare; }
    int GetRare() { return m_rare; }

    void SetCost(int iVal);
    int GetCost() const { return m_iCost; }

    void SetNum(int i_num) { m_iNum = i_num; }
    int GetNum() const { return m_iNum; }

    void SetLevel(int i_level) { m_iLevel = i_level; }
    int GetLevel() const { return m_iLevel; }

    void SetSunIncrease(int i_sunInc) { m_iSunIncrease = i_sunInc; }
    int GetSunIncrease() { return m_iSunIncrease; }

    void SetLocked(bool setting, const SexyString& desc);
    bool IsLocked() const { return m_bLocked; }
    SexyString GetLockedDes() { return m_strLockDesc; }

    void SetType(Type i_type) { m_type = i_type; }
    bool IsPlantType() { return m_type == TYPE_PLANT; }
    bool IsZombieType() { return m_type == TYPE_ZOMBIE; }

    void SetUnlockedTurn(int i_turn) { m_unlockedTurn = i_turn; }
    int GetUnlockedTurn() { return m_unlockedTurn; }

protected:
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

    void InitText() override;
    void DrawText(Graphics* i_g) override;
    void onSeedPacketPlanted(SeedPacket* i_packet) override;
    void onCursorDestroyed(BaseCursor* i_cursor) override;
    void updateAffordability(const SunCurrency i_newSunCurrency) override;
    void onTurnChanged(int i_currentTurn);
    void onNotifyTriggerUpgradeSkill(float i_sunMultiplier);
    void registerForEvents() override;
    AddPacketReason GetAffordState();
    void initialize();

protected:
    bool m_bLocked;
    bool m_sunEnough = false;
    SexyString  m_strLockDesc;

    int m_iNum = 1;
    int m_iLevel = 1;
    int m_iCost = 25;
    int m_iSunIncrease = 1;

    Type m_type = TYPE_INVALID;

    int m_unlockedTurn = -1;
    std::vector<Image*> m_unlockedTurnImgs;
    int m_rare = -1;
};

typedef RtWeakPtr<SeedPacket_NewPVP> SeedPacket_NewPVPPtr;

struct QueueZombieInfo
{
	std::string TypeName = "";
	int Level = 1;
};

class UINewPVPTopZombieQueue : public SlidingWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPTopZombieQueue, SlidingWidget, RtClass);

	void Draw(Graphics* i_g) override;
	void initLoadingResourcesGroupList() override {}
	void registerForEvents() override;

	void onNotifyZombieCacheDatasChanged(const std::vector<ZombieCacheData>& i_queue);
	void onNotifyTurnChanged(int i_current);
	void onGameplayStarted();
	void onGameplayRealStarted();

	void onLoadComplete() override;
	void setZombieItemNum(int i_num);
	void setItemPositions();
	void setZombieQueue(std::vector<ZombieCacheData> i_queue);
	void clearZombieQueue();

	RtWeakPtr<class UINewPVPTopZombieQueueItem>	gettItem(const int index);

	int gettItemCount() { return m_itemNum; }

	int	m_totalRoundNum = 20;
	int m_currentRoundNum = 1;

	int m_itemNum = 0;

	std::vector<ZombieCacheData> m_currentZombieQueue;
    
    float m_scale = 1.0f;
};

typedef RtWeakPtr<UINewPVPTopZombieQueueItem> UINewPVPTopZombieQueueItemPtr;


class UINewPVPTopZombieQueueItem : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPTopZombieQueueItem, UIWidget, RtClass);


	void Draw(Graphics* i_g) override;

	void setTypeName(std::string i_typeName) { m_typeName = i_typeName; }
	void setLevel(int i_level) { m_level = i_level; }
	void setEmpty() { m_typeName = ""; }
	void setRare(int i_rare) { m_rare = i_rare; }

	std::string m_typeName = "";
	int	m_level = 1;
    float m_scale = 1.0f;
    int m_rare = -1;
};

class NewPVPSeedBankModule : public SeedBankModule
{
public:
	RT_CLASS_DEFINE(NewPVPSeedBankModule, SeedBankModule, RtClass);
    NewPVPSeedBankModule();

	virtual void			AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
   	virtual bool			UsesSeedChooser() const override;
    void				closePlantUpgradeWidget();

protected:
	virtual void			initializeModule() override;
	virtual void			registerForEvents() override;

    virtual void			createSeedBank() override;
	virtual void			onLoadComplete() override;
    virtual void			onGameStarted() override;
    virtual void 			onLevelEnded() override;

    void                createPlantSeedBank();
    void                createZombieSeedBank();

    void				createNewPVPSeedBank();

    void                onAddToRenderQueue(class RenderQueue* i_queue);
    void                onDraw(Graphics* i_g);
    void                onPlantShoveled(Plant* i_plant);
    void				onNotifyUpgradePlant(Plant* i_plant);


protected:
    NewPVPSeedBankPtr m_newPVPSeedBank = nullptr;

    class TouchCloseContainer* m_plantUpgradeWidget = nullptr;
};

class NewPVPSeedBankProperties : public SeedBankProperties
{
public:
	RT_CLASS_DEFINE(NewPVPSeedBankProperties, SeedBankProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return NewPVPSeedBankModule::StaticGetClass();
	}

	virtual SeedBankType GetBankType() const override
	{
		return SEEDBANK_NEWPVP;
	}

	NewPVPSeedBankProperties()
	{
	}

public:
//    int     TotalBrains;
};


// UINewPVPSunIncreaseBank

class UINewPVPSunIncreaseBank : public UIWidget, public ButtonListener
{
public:
	RT_CLASS_DEFINE(UINewPVPSunIncreaseBank, UIWidget, RtClass);

	UINewPVPSunIncreaseBank();
	~UINewPVPSunIncreaseBank();

	void registerForEvents() override;
	void Draw(Graphics* i_g) override;
	void onUpdate()	override;

	void initLoadingResourcesGroupList() override;

	void onLoadComplete() override;

	void setCurrentSunIncreaseValue(int i_currentValue);
	int getCurrentSunIncreaseValud() { return m_currentSunIncreaseValue; }

	bool isUpgradeButtonVisible() { return m_buttonVisible; }

private:
	void onNotifySunAddIncrease();
	void onGameplayRealStarted();

	bool handleTouch(const Sexy::Touch& i_touch);
	void startTouch(Sexy::TouchID i_touchIdent);
	void cancelTouch();

	void initIconEffect();
	void playSalaryUpgradeEffect();
	void refresh();

	int m_currentSunIncreaseValue = 0;
	int m_upgradeCost = 300;
	int m_upgradeValue = 200;
	int m_currentSun = 0;
	int m_currentLevel = 0;

	pvztime_t m_sunAddCD = PVZ_EOT();
	pvztime_t m_lastSunAddTime = PVZ_T();

	bool m_buttonVisible = true;
	bool m_buttonDone = false;
	Rect m_buttonRect = Rect();
	Sexy::TouchID m_touchIdent = Sexy::InvalidTouchID;

	Effect_PopAnim* m_iconEffect = nullptr;
	Effect_PopAnim* m_iconEffect2 = nullptr;
    float m_scale = 1.0f;
    bool m_isTutorial = false;
    pvztime_t m_showWarningTime = PVZ_EOT();
    bool m_hasTutorialUpgradeSun = false;
};

// click plant on board and then display this widget on the right

class NewPVPPlantUpgradeBehavior : public Widget, public ButtonListener
{
public:
	NewPVPPlantUpgradeBehavior();
    void Draw(Sexy::Graphics* i_g) override;
    void ButtonDepress(int i_id) override;
    void Update() override;
    void RefreshUI();

public:
    void Init(PlantPtr i_plantPtr);

private:
    int GetUpgradeCost();
    int GetNextLevel();
    bool CanUpgrade();
    bool CanAffordUpgrade();

    PlantPtr m_plantPtr = nullptr;
    class UIWidgetImage* m_levelImage = nullptr;
    class UIWidgetText* m_plantTitleText = nullptr;
    class UIWidgetText* m_plantDesLevelText = nullptr;
    class UIWidgetText* m_plantDesText = nullptr;
    class PVZ2UIButton* m_upgradeButton = nullptr;
};

// UINewPVPSurrenderButton

class UINewPVPSurrenderButton : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPSurrenderButton, UIWidget, RtClass);

	void Draw(Graphics* i_g) override;

	void initLoadingResourcesGroupList() override;

	void OnMouseUp(const int i_mouseX, const int i_mouseY) override;

	void registerForEvents() override;

private:
	void onGameplayRealStarted();
	void onConfirmSurrender();

	bool m_hasSurrendered = false;

};

// UINewPVPReportButton

class UINewPVPReportButton : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPReportButton, UIWidget, RtClass);

	void Draw(Graphics* i_g) override;

	void initLoadingResourcesGroupList() override;

	void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;

	void registerForEvents() override;

private:
	void onGameplayRealStarted();
	void onConfirmReport();
	void onNewPVPNetworkResponseReceived(int i_context, int i_status);
	void onReportResult(bool i_success);

	bool m_hasReported = false;

};

// UINewPVPZombieUpgradeSkillBank

class UINewPVPZombieUpgradeSkillBank : public UIWidget
{
public:
	UINewPVPZombieUpgradeSkillBank();

	RT_CLASS_DEFINE(UINewPVPZombieUpgradeSkillBank, UIWidget, RtClass);

	void Draw(Graphics* i_g) override;

	void initLoadingResourcesGroupList() override;

	void registerForEvents() override;

	class NewPVPTestButton* GetButton(int i_index);

protected:
	void onLoadComplete() override;

	void onGameplayRealStarted();

	std::vector<class NewPVPTestButton*> m_buttons;
    float m_scale = 1.0f;
};



class UINewPVPSkillBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPSkillBank, UIWidget, RtClass);

	enum SkillBankType
	{
		SkillBankType_Invalid,
		SkillBankType_Initial,
	};

	void Draw(Graphics* i_g) override;

	void initLoadingResourcesGroupList() override;

	void setSkillBankType(SkillBankType i_type);

//	void setInitialSkillInfos(std::vector<NewPVPZombieSkillInfo>& i_infos);

protected:
	void onLoadComplete() override;

	SkillBankType m_type = SkillBankType_Invalid;

	std::vector<class UINewPVPInitialSkill*> m_skills;
};


STATE_ENUM_CHILD_BEGIN(UINewPVPInitialSkillState, WidgetState)
	WS_Activated,
	WS_Cooldown,
STATE_ENUM_END(UINewPVPInitialSkillState);

class UINewPVPInitialSkill : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPInitialSkill, UIWidget, RtClass);

	enum SkillType
	{
		SkillType_Invalid = -1,
		SkillType_HP,
		SkillTypee_Attack,
		SkillType_Invisible,
		SkillType_SpeedUp,
		SkillType_Plantfood
	};


	UINewPVPInitialSkill();
	virtual ~UINewPVPInitialSkill();

	virtual void					Draw(Graphics* i_g) override;
	virtual bool					OnTouch(const Sexy::Touch& i_touch) override;
//	virtual bool					IsMouseOver(const int i_mouseX, const int i_mouseY) override;
	virtual const Sexy::Point		GetCenterPointOnScreen() override;

    void                            SetTouchDelegate(Sexy::Delegate0wRet<bool> delegate);

    void							SetSkillType(SkillType i_type);

    void							SetCooldownDuration(float i_dur) { m_cooldownDuration = i_dur; }
    bool							IsOnCooldownState() { return isInState(WS_Cooldown); }

    void							SetIsShowRestTimes(bool i_isShow) { m_isShowRestTimes = i_isShow; }
    void							SetAvailableTimes(int i_times) { m_restTimes = i_times; }
    int 							GetAvailableTimes() { return m_restTimes; }

    void							SetActivatedDuration(float i_dur) { m_activatedDuration = i_dur; }
    void							SetIsShowActivatedEffect(bool i_isShow) { m_isShowActivatedEffect = true; }
    bool							IsOnActivatedState() { return isInState(WS_Activated); }

protected:

	// Protected Interface (Inheritable)

	virtual void					registerForEvents() override;
	virtual void					unregisterForEvents() override;

	void							onCheatEnabled();

	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState, Pressed);
	OVERRIDE_STATE_ONENTER(WidgetState, NotReady);
	OVERRIDE_STATE_UPDATE(WidgetState, NotReady);

	DECLARE_STATE_FUNCTIONS(WidgetState, Activated);
	DECLARE_STATE_FUNCTIONS(WidgetState, Cooldown);


	virtual void					onCursorDestroyed(class BaseCursor* i_cursor);
	virtual void					onPlantfoodCountChanged(int i_newCount);

	void 							onGameplayEnded();

	virtual void					onUpdate() override;
	virtual void					initLoadingResourcesGroupList() override;

private:
	bool							handleTouch(const Sexy::Touch& i_touch);
	void startTouch(Sexy::TouchID i_touchIdent);
	void onTouchEnd();
	void onUsed();
	void onUsedCancel();

	void							cancelTouch();

	void							createActivatedEffect() {}
	void 							deleteActivatedEffect() {}

	Sexy::TouchID 					m_touchIdent = Sexy::InvalidTouchID;

    SkillType						m_type = SkillType_Invalid;

    Image* 							m_normalImage = nullptr;
    Image* 							m_pressedImage = nullptr;

    pvztime_t						m_cooldownEndTime = PVZ_EOT();

    float							m_cooldownDuration = 1;

    int 							m_restTimes = 0;

    bool							m_isShowRestTimes = false;

    float 							m_activatedDuration = 0;
    pvztime_t 						m_deActivateTime = PVZ_T();
    bool							m_isShowActivatedEffect = false;
};


#endif /* __NEWPVPSEEDBANKMODULE_H__ */
