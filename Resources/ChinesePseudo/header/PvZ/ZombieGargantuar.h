//
//  ZombieGargantuar.h
//  PlantsVersusZombies2
//
//  Created by aseavy on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieGargantuar_h
#define PlantsVersusZombies2_ZombieGargantuar_h

#include <string>

#include "BoardEntity.h"
#include "DamageInfo.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"

class ZombieGargantuar;
namespace Message
{
	void GargantuarDefeated(ZombieGargantuar* i_gargantuar);
}

STATE_ENUM_CHILD_BEGIN(ZombieGargantuarState, ZombieState)
	ZS_Gargantuar_Smashing,
	ZS_Gargantuar_ThrowImp,
STATE_ENUM_END(ZombieGargantuarState);

class ZombieGargantuar : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieGargantuar, Zombie, RtClass);
    
    virtual ~ZombieGargantuar();
    virtual void DropAllLoot() override;
    int GetThrownImpIndex(){return m_thrownImpIndex;}
    void SetThrownImpIndex(int index){m_thrownImpIndex = index;}
    void SetHiddenImp(int index);
    bool CanBeFlickedOff() const override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	virtual void onInitialized() override;
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	virtual std::string getElectrocutePAMName() const override;
	virtual std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_GARGANTUAR_ASH"; }
    GroundEffectType GetTideEffect() const override { return GROUND_EFFECT_Tide_Gargantuar; }
    void TakeDamage(const DamageInfo& i_damage) override;
	void onTakeFatalDamage(const DamageInfo& i_lastReceivedDamage) override;
    SexyVector3 GetStunnedEffectOffset() const override;
    BoardEntity* findTarget() override;
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }
    
    virtual bool isImpReadyToBeThrown();
    
    bool isFarEnoughOutToThrowImp();
    
    void onApplyCondition(ZombieConditions i_condition) override;
    virtual int GetImpTargetColumn();
private:
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    

	DECLARE_STATE_FUNCTIONS(ZombieState, Smashing);
    DECLARE_STATE_FUNCTIONS(ZombieState, ThrowImp);

    void onZombieDied(Zombie* i_zombie);
	void fireImpCannon();

protected:
    
    uint32 m_thrownImpIndex;
	AnimHandle m_watchAnimHandle;
};

#endif
