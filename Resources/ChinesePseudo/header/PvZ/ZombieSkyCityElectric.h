//
//  ZombieSkyCityElectric.h
//  PlantsVersusZombies2
//
//  Created by NanLang on 06/24/15.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieSkyCityElectric_h
#define PlantsVersusZombies2_ZombieSkyCityElectric_h

#include <string>

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

class ZombieElectricProjectileActionDefinition : public ZombieProjectileActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombieElectricProjectileActionDefinition, ZombieProjectileActionDefinition, RtClass);

    float                       TimeUntilHit;
    ProjectilePropertySheetPtr  ProjectileExtra;
    bool                        TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieElectricProjectileActionHandler : public ZombieProjectileActionHandler
{
public:
    RT_CLASS_DEFINE(ZombieElectricProjectileActionHandler, ZombieProjectileActionHandler, RtClass);
    void fireProjectile() override;
    virtual void launchProjectile(SexyVector3 i_source, SexyVector3 i_target, ProjectilePropertySheetPtr i_projectile, float i_timeToHit);
};


class ZombieSkyCityElectricProps : public ZombieSkyCityProps
{
public:
	RT_CLASS_DEFINE(ZombieSkyCityElectricProps, ZombieSkyCityProps, RtClass);
};

class ZombieSkyCityElectric : public ZombieSkyCity
{
public:
    RT_CLASS_DEFINE(ZombieSkyCityElectric, ZombieSkyCity, RtClass);
    ZombieSkyCityElectric();
    Effect_Barrage * GetBarragePtr();
    
protected:
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Glide);
    
    void onZombieInitialize() override;
    std::string getAshPAMName() const override;
    
    void DoAttack();
    
protected:
    bool                m_barrageStarted;
    bool                m_isGliding;
    int                 m_iPrevColunm;
    pvztime_t           m_startGlideTime;
    Sexy::SexyVector3   m_startGlidePosition;
    Sexy::SexyVector3   m_targetGlidePosition;
    Effect_Barrage      m_barrage;
};

class ZombieAnimRig_Electric : public ZombieAnimRig_SkyCity
{
public:
    
	RT_CLASS_DEFINE(ZombieAnimRig_Electric, ZombieAnimRig_SkyCity, RtClass);
    const std::string getRangedAttackAnimationName() override;
    const std::string getEatAirShipAnimationName() override;
    bool PlayRangedAttack(AnimStoppedReflectionDelegate i_onAnimStopped) override;
};

class ZombieSkyCityElectricProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieSkyCityElectricProjectileProps, ProjectilePropertySheet, RtClass);
    ZombieSkyCityElectricProjectileProps() : PlantCondition(0) {}
    int PlantCondition;
};

class ZombieSkyCityElectricProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ZombieSkyCityElectricProjectile, Projectile, RtClass);
    ZombieSkyCityElectricProjectile() {};
    bool OnCollideEntity(BoardEntity* i_entity) override;
};

#endif
