//
//  ZombieIceAgeChief.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 03/12/16.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieIceAgeChief_h
#define PlantsVersusZombies2_ZombieIceAgeChief_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"

class ZombieIceAgeChiefProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeChiefProps, ZombiePropertySheet, RtClass);
    ZombieIceAgeChiefProps();
    pvztime_t WindSpawnInterval;
};

class ZombieIceAgeChiefEliteProps : public ZombieIceAgeChiefProps
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeChiefEliteProps, ZombieIceAgeChiefProps, RtClass);
	ZombieIceAgeChiefEliteProps() {
	}
};

STATE_ENUM_CHILD_BEGIN(ZombieState_IceChief, ZombieState)
ZS_IceChief_SpawnWind,
STATE_ENUM_END(ZombieState_IceChief)

class ZombieIceAgeChief : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeChief, Zombie, RtClass);
    
    ZombieIceAgeChief() { }
protected:
    virtual void onZombieInitialize() override;
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override
    ;
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    DECLARE_STATE_FUNCTIONS(ZombieState, SpawnWind);

    void onAnimationDone(const std::string& i_animName);
    virtual void SpwanWind(const Sexy::Point& grid);
    void PlayWindEffect(const Sexy::Point& grid);
    pvztime_t m_nextWindTime = PVZ_EOT();
};

class ZombieIceAgeChiefElite : public ZombieIceAgeChief
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeChiefElite, ZombieIceAgeChief, RtClass);

    OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	virtual void onPlaceOnBoard() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void SpwanWind(const Sexy::Point& grid) override;

protected:
	void MoveZombie(BoardEntity* i_impactedEntity, float i_distance, float i_time);
};

enum ZombieAnimRigState_IceChief
{
    ZOMBIEANIM_IceChief = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_Chief : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Chief, ZombieAnimRig, RtClass);
    bool PlaySpawnWind(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
};

namespace Message
{
    void ZombieIceAgeChiefSpwanWind(int i_row);
}

#endif
