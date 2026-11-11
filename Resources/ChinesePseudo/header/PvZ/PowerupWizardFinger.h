//
//  PowerupWizardFinger.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 12/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerupWizardFinger_h
#define PlantsVersusZombies2_PowerupWizardFinger_h

#include "Effect_PopAnim.h"
#include "BasePowerup.h"
#include "GameObject.h"

class WizardFingerGameObject : public GameObject
{
public:
	RT_CLASS_DEFINE(WizardFingerGameObject, GameObject, Sexy::RtClass);

	WizardFingerGameObject()
	: m_active(false)
	, m_playingAttack(false)
	{}

	virtual void onInitialized() override;
	virtual void onDestroy() override;

	class BoardEntity* GetClosestEntity(const SexyVector2 &i_location);
	void SetLocation(const SexyVector2& i_location);
	void SetActive(const bool i_active);
	void Update();

private:

	bool m_active;

	SexyVector2 m_touchLocation;
	RtWeakPtr<Effect_PopAnim> m_effectBack;
	RtWeakPtr<Effect_PopAnim> m_effectFront;
	RtWeakPtr<Effect_PopAnim> m_effectTop;
	bool m_playingAttack;
public:
};

class PowerupWizardFinger : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupWizardFinger, BasePowerup, Sexy::RtClass);

	PowerupWizardFinger()
	: m_touchIdent(Sexy::InvalidTouchID)
	{}

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

	OVERRIDE_STATE_ONENTER(PowerupState, Idle);
	OVERRIDE_STATE_ONENTER(PowerupState, Selected);
	OVERRIDE_STATE_UPDATE(PowerupState, Activated);
	OVERRIDE_STATE_ONEXIT(PowerupState, Activated);

private:
	bool shouldActivate(const Sexy::Touch& i_touch);
	void activate(const Sexy::Touch& i_touch);
	bool isTouching();
	bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();

	/// Serialized
	RtWeakPtr<WizardFingerGameObject> m_WFGameObject;
	
	/// Transient
	Sexy::TouchID m_touchIdent;
};

#endif
