/*
 * ZombieFairyTaleWitch.h
 *
 *  Created on: 2022-3-11
 *      Author: admin
 */

#ifndef ZOMBIEFAIRYTALEWITCH_H_
#define ZOMBIEFAIRYTALEWITCH_H_

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "RestrictionSet.h"
#include "PopAnimRig.h"
#include "ZombieAnimRig.h"

class BoardEntity;
class Effect_PopAnim;
class Plant;

STATE_ENUM_CHILD_BEGIN(ZombieState_FairyTaleWitch, ZombieState)
    ZS_FAIRYTALEWITCH_Casting,
STATE_ENUM_END(ZombieState_FairyTaleWitch)

enum ZombieAnimRigState_FairyTaleWitch
{
	ZOMBIEANIM_FAIRYTALEWITCH_CASTING = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_FairyTaleWitch : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleWitch, ZombieAnimRig, RtClass) {}

	// DarkWizard specific functionality
	bool StartCasting(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieFairyTaleWitchProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieFairyTaleWitchProps, ZombiePropertySheet, RtClass);

    ZombieFairyTaleWitchProps()
    {
        SoundOnSpellActivate = "Play_RaZombie_WandActivate";
    }
    std::string TransformPopAnim;
    Sexy::Point TransformOffset;

    std::string SoundOnSpellActivate;
    std::string ProjectilePopAnim;

    ProjectilePropertySheetPtr Projectile;

    PlantRestrictionSet TargetablePlantTypes;
};

class ZombieFairyTaleWitch : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieFairyTaleWitch, Zombie, RtClass);

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Casting);

	virtual void registerForEvents() override;

private:
    void onZombieInitialize() override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	void onMowedDown() override;
	void onDestroy() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	bool isValidSpellTarget(Plant* plant);
	Plant* getValidSpellTarget();
    void onAnimationDone(const std::string& i_animName);
	void onSpellImpact(BoardEntity* i_impactedEntity);

	bool tryTransform(Plant* i_plant);
	std::string getTransformType();
	void transform(Plant* i_plant);
	void createTransformEffect(const SexyVector3& i_position);
	bool canTransform(Plant* i_plant);
	bool tryCastSpell();
	void recoverTransformedPlants();
	void OnPlantDestroyed(Plant* i_plant);

	std::vector<RtWeakPtr<Plant> > m_transformedPlants;
	std::vector<int> m_passedCols;
};


#endif /* ZOMBIEFAIRYTALEWITCH_H_ */
