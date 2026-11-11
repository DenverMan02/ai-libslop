//
//  BasePowerup.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BasePowerup__
#define __PlantsVersusZombies2__BasePowerup__

#include "GameObject.h"
#include "Core.h"
#include "StateMachine.h"
#include "PowerupType.h"

STATE_ENUM_BASE_BEGIN(PowerupState)
	POWERUP_Idle,
	POWERUP_Selected,
	POWERUP_Activated,
STATE_ENUM_END(PowerupState);

const int POWERUP_FREE_TIMES = 3;

class BasePowerup : public GameObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(BasePowerup, GameObject, Sexy::RtClass);

	BasePowerup();
	virtual ~BasePowerup() {}

	void Update();
	virtual void Draw(Sexy::Graphics* i_g) {}

	void Select();
	void Deselect();
	void Activate();
	void Deactivate();

	class PowerupType* GetType() { return m_powerupType; }
	void SetPowerupType(PowerupTypePtr i_powerupType) { m_powerupType = i_powerupType; }

	void SetDemonstration(const bool i_demo) { m_demonstration = i_demo; }
	void SetIgnoreCost(const bool i_ignoreCost) { m_ignoreCost = i_ignoreCost; }
	bool GetIgnoreCost() const { return m_ignoreCost; }
	void SetIsInWarning(bool isInWarning);
	bool IsInWarning() const {return m_isInWarning;}

	float GetPowerupTimeRemaining() const { return m_timeRemaining; }
	void DecrementTimeByUseCost();
	void ResetTimeRemaining();
	
	inline void SetMaxPurchasesAllowed(const int8 i_maxPurchases);
	inline int8 GetPurchasesLeft();
    
//    int GetUseTimes() { return m_useTimes; }
//    void SetUseTimes(int times) { m_useTimes = (times > 0) ? times : m_useTimes; }

protected:
	virtual void onInitialized() override;
	virtual void onSelected() {}

	DECLARE_STATE_FUNCTIONS(PowerupState, Idle);
	DECLARE_STATE_FUNCTIONS(PowerupState, Selected);
	DECLARE_STATE_FUNCTIONS(PowerupState, Activated);

	void        setState(PowerupState i_newState);
	PowerupState getState() const;
    bool        isInState(uint32 i_state) const;

private:
	/// Serialized values
	PowerupTypePtr m_powerupType;
	
	bool m_selected;
	bool m_demonstration;
	bool m_ignoreCost;
	bool m_isInWarning;
	float m_timeRemaining;
	int	m_purchasesLeft;
//    int m_useTimes;

	/// Transient values
	int32		getPowerupStateSerialization();
	void		setPowerupStateSerialization(int32 i_state);
	StateMachine<PowerupState> m_powerupState;
};

inline void BasePowerup::SetMaxPurchasesAllowed(const int8 i_maxPurchases)
{
	m_purchasesLeft = i_maxPurchases;
}

inline int8 BasePowerup::GetPurchasesLeft()
{
	return m_purchasesLeft;
}

class PowerupTouchBased : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupTouchBased, BasePowerup, RtClass);
	
	PowerupTouchBased();
	virtual ~PowerupTouchBased();
	
protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
    
	const Sexy::Touch& getLastTouchEvent() const;
	const Sexy::TouchID& getActiveTouchIdent() const;
	
	virtual bool onTouchBegin(const Sexy::Touch& i_touch) { return false; }
	virtual void onTouchMoved(const Sexy::Touch& i_touch) {}
	virtual void onTouchEnd(const Sexy::Touch& i_touch) {}
	virtual void onTouchCanceled() {}
    
private:
    bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
	
private:
	Sexy::TouchID m_touchIdent;
	Touch m_lastTouchEvent;
};

namespace Message
{
	void PowerupWarning(BasePowerup* i_powerup);
}

#endif /* defined(__PlantsVersusZombies2__BasePowerup__) */
