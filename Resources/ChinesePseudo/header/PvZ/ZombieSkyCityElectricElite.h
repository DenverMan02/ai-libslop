/*
 * ZombieSkyCityElectricElite.h
 *
 *  Created on: 2021-7-14
 *      Author: zhousen
 */

#ifndef ZOMBIESKYCITYELECTRICELITE_H_
#define ZOMBIESKYCITYELECTRICELITE_H_

#include "EliteModule.h"
#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "ZombieSkyCity.h"
#include "dtypes.h"
#include "RestrictionSet.h"
#include "BoardConstants.h"
#include "Projectile.h"
#include "Effect_Barrage.h"

class ZombieEliteSkyCityElectric : public ZombieSkyCityElectric, public ZombieEliteModule
{
public:
	RT_CLASS_DEFINE(ZombieEliteSkyCityElectric, ZombieSkyCityElectric, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	void onZombieInitialize() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }
    void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

    void FinishSpecialSkill();
    bool GetFirstWaveState() const { return _isFirstWaveState; }

protected:
    void DoSpecialSkill();

protected:
    pvztime_t _specialSkillEndTime;// after this time , we should end special skill
    pvztime_t _skillCooldownTime;
    bool _isDoingSpecialSkill;// when we are in special skill , we should not turn to walk state
    bool _isFirstWaveState;// if is in first wave of special skill state
};

class ZombieEliteSkyCityElectricProps : public ZombieSkyCityElectricProps
{
public:
    RT_CLASS_DEFINE(ZombieEliteSkyCityElectricProps, ZombieSkyCityElectricProps, RtClass);

    ZombieEliteSkyCityElectricProps();

    pvztime_t SpecialSkillDuration;// skill time duration
    pvztime_t SkillCooldownTime;// skill cool down time
};

class ZombieEliteElectricProjectileActionDefinition : public ZombieElectricProjectileActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombieEliteElectricProjectileActionDefinition, ZombieElectricProjectileActionDefinition, RtClass);
    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieEliteElectricProjectileActionHandler : public ZombieElectricProjectileActionHandler
{
public:
    RT_CLASS_DEFINE(ZombieEliteElectricProjectileActionHandler, ZombieElectricProjectileActionHandler, RtClass);
    void fireProjectile() override;
    void launchProjectile(SexyVector3 i_source, SexyVector3 i_target, ProjectilePropertySheetPtr i_projectile, float i_timeToHit) override;
};


#endif /* ZOMBIESKYCITYELECTRICELITE_H_ */
