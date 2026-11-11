/*
 * PowerupTacticalCuke.h
 *
 *  Created on: 2013-10-22
 *      Author: wuxj
 */

#ifndef POWERUPTACTICALCUKE_H_
#define POWERUPTACTICALCUKE_H_

#include "Effect_PopAnim.h"
#include "BasePowerup.h"
#include "GameObject.h"


class TacticalCukeGameObject : public GameObject
{
public:
	RT_CLASS_DEFINE(TacticalCukeGameObject, GameObject, Sexy::RtClass);

	TacticalCukeGameObject();
	virtual ~TacticalCukeGameObject();

	virtual void 	onInitialized() override;
	virtual void 	onDestroy() override;

	void 			Activate(const bool i_active, const float fallDuration, const int additionDamage);
	void 			Update();
	inline bool		IsActive() const {return m_active;}

	void 			Draw(Sexy::Graphics* i_g);

private:
	enum CukeState
	{
		PVZ_BEGIN_ENUM(CUKE_STATE_),
		CUKE_STATE_FALLING,
		CUKE_STATE_ATTACK,
		CUKE_STATE_EXPLOSION,
		PVZ_END_ENUM(CUKE_STATE_)
	};

	void 			setState(CukeState state);
	void 			reset();

	void 			onAnimStopped(StandaloneEffect* i_effect);

	bool						m_hasExploded;
	bool 						m_active;
	CukeState 					m_cukeState;
	float 						m_fallTimeElapsed;
	float 						m_fallDuration;
	float 						m_whiteFadeToBoardTimeRemaining;
    int                         m_additionDamage;
	RtWeakPtr<Effect_PopAnim> 	m_effectCuke;
	RtWeakPtr<Effect_PopAnim> 	m_effectExplosion;

	SexyVector2					m_placementPosition;
};

class PowerupTacticalCuke : public BasePowerup
{
public:
	RT_CLASS_DEFINE(PowerupTacticalCuke, BasePowerup, Sexy::RtClass);

	PowerupTacticalCuke();
	virtual ~PowerupTacticalCuke();
    void onInitialized() override;

	virtual void Draw(Sexy::Graphics* i_g) override;

    void LaunchCuke(bool success);
protected:
	OVERRIDE_STATE_UPDATE(PowerupState, Idle);
	OVERRIDE_STATE_UPDATE(PowerupState, Selected);
    OVERRIDE_STATE_ONENTER(PowerupState, Selected);
	OVERRIDE_STATE_UPDATE(PowerupState, Activated);
	OVERRIDE_STATE_ONEXIT(PowerupState, Activated);
    
    void                    OnNotifyPowerupUsesChanged(class PowerupRecord* i_record);

private:
	/// Serialized
	RtWeakPtr<TacticalCukeGameObject> 	m_TCGameObject;
    void CreateCukeObjectAndRefreshStatus();
    int m_gemBeforeLaunch = 0;
    int m_freeGemBeforeLaunch = 0;
};


namespace Message
{
    void PowerupTacticalCukeExplod();
}

#endif /* POWERUPTACTICALCUKE_H_ */
