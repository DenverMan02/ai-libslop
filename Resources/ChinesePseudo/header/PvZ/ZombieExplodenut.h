/*
 * ZombieExplodenut.h
 *
 *  Created on: 2020-10-23
 *      Author: zhousen
 */

#ifndef ZOMBIEEXPLODENUT_H_
#define ZOMBIEEXPLODENUT_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "AnimRigLayerSet.h"

namespace Message
{
    void NotifySelfExplodeExplodenut();
}

/// 
/// zombie anim rig
///
class ZombieAnimRig_Explodenut : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Explodenut, ZombieAnimRig_Basic, RtClass);
    ZombieAnimRig_Explodenut();

	void onPopAnimInitialized() override;

    void SetObjectPtr(ZombiePtr ptr) { _zombiePtr = ptr; }
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    
    virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;

private:
    ZombiePtr _zombiePtr;
    AnimRigLayerSet _damageLayerSet;// change 
};

///
/// zombie explodenut props
///
class ZombieExplodenutProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieExplodenutProps, ZombiePropertySheet, RtClass);
    ZombieExplodenutProps();

    float BodyDamageLevel1Ratio;// after this ratio change bodydamage ratio1 animation
    float BodyDamageLevel2Ratio;// after this ratio change bodydamage ratio2 animation
    int ExplodeDamage;// explode damage
};

///
/// state
///
STATE_ENUM_CHILD_BEGIN(ZombieState_Explodenut, ZombieState)
    ZS_Explodenut_Explode,// if zombie dies, then explode
STATE_ENUM_END(ZombieState_Explodenut)

///
/// zombie jalapeno
///
class ZombieExplodenut : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieExplodenut, Zombie, RtClass);

    OVERRIDE_STATE_ONENTER(ZombieState, Die);
    DECLARE_STATE_FUNCTIONS(ZombieState, Explode);

    void onZombieInitialize() override;
    ZombieParticle* DropHead() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onUpdate() override;

    int GetBodyDamageLevel();// calc body damage level

private:
    void Explode();
    void DamagePlant();
    void OnSwallowZombie(Zombie* zombie);

private:
    bool _isSwallowDead;// check if is swallow die
    float _damageLevel1;// damage layer ratio
    float _damageLevel2;
};

#endif /* ZOMBIEEXPLODENUT_H_ */
