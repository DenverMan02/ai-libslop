//

//  ZombieGargantuarMech.h

//  PlantsVersusZombies2

//

//  Created by jsola on 11/15/12.

//  Copyright (c) 2012 PopCap Games. All rights reserved.

//



#ifndef PlantsVersusZombies2_ZombieGargantuarMech_h

#define PlantsVersusZombies2_ZombieGargantuarMech_h



#include "RtDb.h"

#include "RtObject.h"

#include "SexyVector.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "Zombie.h"

#include "ZombieGargantuar.h"



class ZombieGargantuarMech;



STATE_ENUM_CHILD_BEGIN(ZombieState_GargMech, ZombieGargantuarState)

    ZS_GARG_EMPeachStun,

	ZS_GARG_EyeLaserFiring,

STATE_ENUM_END(ZombieState_GargMech)





// A single laser sweep has these states

//	- Power up

//		- Beam extends to initial point

//	- Sweep!

//		- Beam travels from initial point to end point (this sweep occurs while extending / retracting!)

//		- Beam damages target(s?)

//	- Power down

//		- Beam retracts back into the eyes

// If interrupted, we jump to Power Down state and retract quickly



enum EyeLaserState

{

	LASER_Off,

	LASER_PowerUp,

	LASER_Sweeping,

	LASER_PowerDown

};



struct EyeLaserTracker

{

	friend class ZombieGargantuarMech; // This lets us reflect this struct out from within ZombieGargMech

	

	EyeLaserTracker() :

		m_timeInState(0.f),

		m_state(LASER_Off),

		m_firingInterrupted(false),

		m_beamStartOffset(0.f, 0.f, 0.f),

		m_beamEndOffset(0.f, 0.f, 0.f),

		m_beamCurrentOffset(0.f, 0.f, 0.f),

		m_lastActiveBeamExtent(0.f),

		m_beamExtent(0.f),

		m_eyeLaserWarmUpTime(0.f),

		m_eyeLaserSweepTime(0.f)

	{}

    void SetOwningZombie(RtWeakPtr<class Zombie> i_owner, float			i_eyeLaserWarmUpTime = 1.0f, float i_eyeLaserSweepTime = 1.0f);

	

	void StartFiring(const SexyVector3& i_startBoardLoc, const SexyVector3& i_endBoardLoc);

	void FiringInterrupted();

	

	void Update(pvztime_t i_elapsedTime);

	bool IsActive();

	bool IsSweeping();

	

	SexyVector3 GetCurrentFireLocationBoardSpace();

	float		GetBeamExtent();

	

private:

	void setState(EyeLaserState i_newState);

	

	pvztime_t		m_timeInState;

	EyeLaserState	m_state;

	

	bool			m_firingInterrupted;

	

	SexyVector3		m_beamStartOffset;

	SexyVector3		m_beamEndOffset;

	SexyVector3		m_beamCurrentOffset;

	float			m_lastActiveBeamExtent;

	float			m_beamExtent;

	float			m_eyeLaserWarmUpTime;

	float			m_eyeLaserSweepTime;
    
    RtWeakPtr<Zombie> m_owningZombie;
};



class ZombieGargantuarMech : public ZombieGargantuar

{

public:

	RT_CLASS_DEFINE(ZombieGargantuarMech, ZombieGargantuar, RtClass);

	

	ZombieGargantuarMech() :

		m_stunDuration(0.f),

		m_endTimeOfLastLaserAttack(0.f),

		m_laserStartComplete(false)

	{}



	virtual void EMPeachStun(pvztime_t i_duration) override;

	bool IsStunned() const override;



	/// from BoardEntity

	virtual void AddToRenderQueue( class RenderQueue* i_queue) override;

	

protected:

	DECLARE_STATE_FUNCTIONS(ZombieState, EMPeachStun);

	DECLARE_STATE_FUNCTIONS(ZombieState, EyeLaserFiring);



	OVERRIDE_STATE_ONENTER(ZombieState, Walk);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	

	virtual void onZombieInitialize() override;

    virtual void onZombiePostLoad() override;

	virtual void onUpdate() override;

	virtual void onDestroy() override;

	virtual bool hasHeadParticle() const override {return false;}

	

	// Some future zombies do not have proper anims electrocute/ash

	virtual bool allowElectrocuteState() const override

	{

		return false;

	}

	virtual bool allowAshState() const override

	{

		return false;

	}

	

private:

	void drawLaser(class Graphics* i_graphics);

	float drawLaserFromTo(class Graphics* i_graphics, const SexyVector3& i_from, const SexyVector3& i_to);

	

	bool pickLaserTargets(SexyVector3& o_startLocBoard, SexyVector3& o_endLocBoard);

	void fireOnLaserTargets(SexyVector3 i_startLocBoard, SexyVector3 i_endLocBoard);

	void onEyeLaserStartComplete(const std::string&);

	void onEyeLaserEndComplete(const std::string&);

	

	// Stun

	pvztime_t m_stunDuration;

	RtWeakPtr<class Effect_PopAnim> m_stunDamageEffect;

	

	// Laser

	RtWeakPtr<class Effect_PopAnim> m_beamStartRig;

	RtWeakPtr<class Effect_PopAnim> m_beamRig;

	RtWeakPtr<class Effect_PopAnim> m_scorchRig;

	SexyVector3 m_nextFireStartLoc;

	SexyVector3 m_nextFireEndLoc;

	EyeLaserTracker m_laserState;

	pvztime_t m_endTimeOfLastLaserAttack;

	bool m_laserStartComplete;

};



#endif

