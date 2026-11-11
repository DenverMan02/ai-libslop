/*
 * NewPVPHealthBar.h
 *
 *  Created on: 2022-10-18
 *      Author: admin
 */

#ifndef NEWPVPHEALTHBAR_H_
#define NEWPVPHEALTHBAR_H_

#include "UIHeadshot.h"
#include "UIWidget.h"

class NewPVPHealthBar : public UIWidget
{
public:
	enum BarType
	{
		Type_Self,
		Type_Oppoent
	};

	RT_CLASS_DEFINE(NewPVPHealthBar, UIWidget, RtClass);

	NewPVPHealthBar();
	~NewPVPHealthBar();

	void SetType(BarType i_type) { m_type = i_type; }

	// Public Interface (Inheritable)

	virtual void	Draw(Graphics* i_g) override;
    virtual void    AddToRenderQueue(class RenderQueue* i_queue) override;

	void            FlashDamage();
	void 			SetHeadShotID(int32 i_id);
	void			SetPlayerNameSexyStr(SexyString i_sexyStr) { m_nameSexyStr = i_sexyStr; }

protected:
	// Protected Interface (Inheritable)

	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	virtual void		initLoadingResourcesGroupList() override;
	virtual void		registerForEvents() override;

    void onUpdate() override;

private:

	// Event handling
	void				onGamePaused();
	void				onGameUnpaused();

	void 				onBarTakeDamage(int i_type, float i_amount);
	void 				onGameplayStarted();
	void 				onBarSetPercentage(int i_type, float i_percent);

	// Private Members (serialized)
	float                                   m_phasePercent;
	float 									m_maxHealthAmount;
	pvztime_t								m_damageFlashStartTime;
	BarType									m_type;

	// headshot
	int32 				m_headShotID = 0;
//    UIHeadshot* 		m_pHeadshotIcon = nullptr;
    UIHeadshotIcon* 	m_pHeadshotIcon = nullptr;
    bool 				m_hasEffect;
    SexyString			m_nameSexyStr = SexyString();
};


class NewPVPTestButton : public UIWidget, public ButtonListener
{
public:
	enum UpgradeType
	{
		UpgradeType_SpeedUp,
		UpgradeType_HP,
		UpgradeType_Immune,
		UpgradeType_Attack,
		UpgradeType_Invisible,

	};

	enum ButtonState
	{
		ButtonState_Activated,
		ButtonState_Ready
	};

	RT_CLASS_DEFINE(NewPVPTestButton, UIWidget, RtClass) {}

	NewPVPTestButton();
	~NewPVPTestButton();

	virtual void Draw(Graphics* i_g) override;
//	virtual void    AddToRenderQueue(class RenderQueue* i_queue) override;

	void SetLabel(const SexyString& i_label);
	void SetType(UpgradeType i_type);

	void SetUnlockedTurn(int i_turn) { m_unlockedTurn = i_turn; }
	int GetUnlockedTurn() { return m_unlockedTurn; }
    void Adapt();

protected:
	void 				onGameplayStarted();

	virtual void initLoadingResourcesGroupList() override;

	void		registerForEvents() override;
	void 		unregisterForEvents() override;

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

private:
	bool handleTouch(const Sexy::Touch& i_touch);
	void handleLongPress(Sexy::Point i_location);
	void startTouch(Sexy::TouchID i_touchIdent);
	void cancelTouch();
	void onNotifyZombieUpgradeUnlocked(int i_type);
	void onTurnChanged(int i_currentTurn);
	void showTips(const std::string& i_tips, float i_scaleX = 1.0f, float i_scaleY = 1.0f);
	void killTips();
	SexyString SetTouchDescription(const SexyString& i_sexyString, float& i_scaleY);
	SexyString SetTouchDescription(const std::string& i_string, float& i_scaleY);
	void createClickedEffect();

	class StretchableNewLawnButton* m_button;
	Sexy::TouchID m_touchIdent;
	UpgradeType m_type;
	int m_unlockedTurn;
	std::vector<Image*> m_unlockedTurnImgs;
	ButtonState m_buttonState;
	bool m_isInLongPressState;
	class StoneLotteryItemTipUI* m_tipUI;
	RtWeakPtr<class Effect_PopAnim> m_effect;
    
    float m_scale = 1.0f;
};

class UINewPVPRoundBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(UINewPVPRoundBank, UIWidget, RtClass);

	UINewPVPRoundBank();
	~UINewPVPRoundBank();

	void Draw(Graphics* i_g) override;
	void registerForEvents() override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;

private:
	void onGameplayStarted();
	void onTurnChanged(int i_currentTurn);

	void drawTipsOfOppoentZombies(Graphics* i_g);

	int m_totalRound = 20;
	int m_currentRound = 0;
};

class NewPVPInfoCard : public UIWidget
{
public:
	enum CardType
	{
		Type_Self,
		Type_Oppoent
	};

	RT_CLASS_DEFINE(NewPVPInfoCard, UIWidget, RtClass);

	NewPVPInfoCard();
	~NewPVPInfoCard();

	void registerForEvents() override;

	void Draw(Graphics* i_g) override;
	void onUpdate() override;

	void SetType(CardType i_type) { m_type = i_type; }
	CardType GetType() { return m_type; }

	void SetRankAvatarID(int i_id) { m_rankAvatarID = i_id; }
	int32 GetRankAvatarId() { return m_rankAvatarID; }

	void SetHeadShotID(int32 i_id);
	int32 GetHeadShotID() { return m_headShotID; }

	void SetNameStr(SexyString i_str) { m_nameStr = i_str; }

	void SetEnterCallback(std::function<void(int, class NewPVPInfoCard*)> i_onEnter) { m_onEnterCallback = i_onEnter; }

	void UpdateCardEntering();
	void Enter();
	bool isEnteringFinished() const;

private:
	CardType m_type = Type_Self;

	UIHeadshotIcon* m_pHeadshotIcon = nullptr;
	bool m_hasEffect = false;
	SexyString m_nameStr = SexyString();
	int32 m_headShotID = 0;
	int32 m_rankAvatarID = 0;

	pvztime_t m_enterStartTime = PVZ_EOT();
	pvztime_t m_enterEndTime = PVZ_EOT();
	std::function<void(int, class NewPVPInfoCard*)> m_onEnterCallback;
};

namespace Message
{
	void BarTakeDamage(int i_type, float i_amount);
	void BarSetPercentage(int i_type, float i_percent);
}

#endif /* NEWPVPHEALTHBAR_H_ */
