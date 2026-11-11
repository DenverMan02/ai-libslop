/*
 * ArtifactUFOTools.h
 *
 *  Created on: 2022-1-25
 *      Author: kkdud
 */

#ifndef _ARTIFACTUFOTOOLS_H__
#define _ARTIFACTUFOTOOLS_H__



#include "GameSubSystem.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "SexyVector.h"
#include "TimeMgr.h"
#include "DamageInfo.h"
#include "Zombie.h"
#include "Effect_PopAnim.h"
#include "Artifact.h"
#include "Zombie.h"


class Zombie;
typedef RtReflectionDelegate<Delegate1<class Zombie*> > ZombieLandedCallback;


struct RisedZombie
{
	RtWeakPtr<class Zombie> m_zombie;
	SexyVector3 			m_position;
	SexyVector3 			m_velocity;
	float					m_riseTime;
	float 					m_elapsed;
	ZombieLandedCallback 	m_onLandedCallback;
	bool       		 		m_wasFlying;
    bool					m_isUp;

    pvztime_t 				m_backCd;
    float 					m_backWidth;
    pvztime_t 				m_backTimer;
};


class ArtifactUFOSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactUFOSubSystem, GameSubSystem, RtClass);

public:

	ArtifactUFOSubSystem();
	~ArtifactUFOSubSystem();

	void riseZombie(class Zombie* i_zombie, SexyVector3 i_riseVelocity, pvztime_t i_riseTime, ZombieLandedCallback i_landedCallback = ZombieLandedCallback());

	void riseAndTossBackZombie(class Zombie* i_zombie, SexyVector3 i_riseVelocity, pvztime_t i_riseTime, float i_backCd, float i_backWidth, ZombieLandedCallback i_landedCallback = ZombieLandedCallback());

	bool IsRising(class Zombie* i_zombie);

	void Update() override;
	void setValues(float i_gravity, float i_maxHeight);
	void setBackValues(float i_backCd, float i_backWidth);

	RisedZombie* findRisedZombie(Zombie* i_forZombie);

protected:
	virtual void registerForEvents() override;

	void onZombieDamageTaken(Zombie* i_zombie, const DamageInfo& i_damage);

	std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
	std::vector<RisedZombie> m_risedZombies;
	std::vector<RisedZombie> m_newRisedZombies;

private:
	void onZombieDestroyed(Zombie* i_zombie);
	void internalRiseZombie(RisedZombie i_risedZombie);
	bool canZombieBeSeckilled(ZombiePtr i_zombiePtr);

	float m_gravity;
	float m_maxHeight;
};


class UFO : public GameObject
{
public:
	RT_CLASS_DEFINE(UFO, GameObject, RtClass);

	enum UfoType {
		UFO_ACTIVE,
		UFO_PASSIVE
	};

	enum UFOState
	{
		UFOSTATE_INVALID = -1,
		UFOSTATE_ENTER,
		UFOSTATE_WORK,
		UFOSTATE_QUIT,
	};

	struct RiseDes {
	    pvztime_t maxRiseTime;
		RtWeakPtr<BoardEntity> target;
		std::string pamName;
		RtWeakPtr<ArtifactUFO> owner;
		UfoType type;
	};

	UFO();
	~UFO();

	void update();
	void setState(UFOState i_state);

	void setValues(RiseDes i_des);

    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);
    void onAnimStopped(const std::string& i_animLabel);

    void doRising();

	RtWeakPtr<Effect_PopAnim> m_ufoEffectPtr;
	pvztime_t m_startTime;

	std::string m_pamName;

    pvztime_t m_riseTimer;
    pvztime_t m_maxRiseTime;
    RtWeakPtr<ArtifactUFO> m_owner;
    RtWeakPtr<Zombie> m_target;
	UfoType m_type;

	UFOState m_state;
	SexyVector3 m_position;
	float m_scale;
};

#endif
