//
//  ZombieMagicBronze.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-12-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieMagicBronze__
#define __PlantsVersusZombies2__ZombieMagicBronze__

#include "ZombieQigong.h"

STATE_ENUM_CHILD_BEGIN(ZombieMagicBronzeState, ZombieState)
	ZS_MagicBronze_Pull,
	ZS_MagicBronze_Summon,
    ZS_MagicBronze_Debut,
STATE_ENUM_END(ZombieMagicBronzeState);

class ZombieMagicBronze : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieMagicBronze, Zombie, RtClass);
    
    virtual bool CanBeFlickedOff() const override
	{
        return false;
	}
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }

protected:
	virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    virtual std::string getElectrocutePAMName() const override;
	virtual std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BRONZE_ASH"; }

    SexyVector3 GetStunnedEffectOffset() const override;
    
    virtual ZombieParticle* DropArm() override;
    
    virtual bool DoSkill(ZombieSkillType skill_type) override;

private:
    
    DECLARE_STATE_FUNCTIONS(ZombieState, Pull);
	DECLARE_STATE_FUNCTIONS(ZombieState, Summon);
    DECLARE_STATE_FUNCTIONS(ZombieState, Debut);
    
    void DoPullSkill();
    
    void pullPlant(Plant* i_plant, bool canFly);
    
	void startPulling(Zombie* z);
    
	void onSummonAnimDone(const std::string& i_label);
    void onPullAnimDone(const std::string& i_label);
    void onDebutAnimDone(const std::string& i_label);
    
    pvztime_t       m_startPlayingPullAnimTime = PVZ_EOT();
};

#endif /* defined(__PlantsVersusZombies2__ZombieMagicBronze__) */
