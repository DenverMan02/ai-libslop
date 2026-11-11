//
//  Plant_Springbean.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 4/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Springbean_h
#define PlantsVersusZombies2_Plant_Springbean_h

#include "PlantFramework.h"
#include "PopAnimRig.h"

class PlantSpringbean : public PlantFramework
{
public:
    enum Springbean_State
    {
        SPRINGSTATE_IDLE = STATE_FRAMEWORK_BEGIN, // waiting for zombie to get near
        SPRINGSTATE_COCKING,                      // getting to cock state.
        SPRINGSTATE_COCKED,                       // waiting to spring
        SPRINGSTATE_SPRUNG,                       // bean is released
        SPRINGSTATE_SLEEPING,                     // bean is resting.
        SPRINGSTATE_RECOVER,                      // bean is waking up.
        SPRINGSTATE_PLANTFOOD,                    // in plantfood state.
    };
    
    
	RT_CLASS_DEFINE(PlantSpringbean, PlantFramework, RtClass);
    
    virtual void    Initialize() override;
    virtual void	UpdateActions() override;
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    virtual bool	CanApplyPlantfood() override;
    virtual void	ApplyPlantfood() override;
    virtual void    UpdatePlantfood() override;
    virtual void    CancelPlantfood() override;

	virtual void	TakeSmashAttack(ZombiePtr i_srcZombie) override;

    virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    virtual bool    IsInvincible() const override;

    virtual bool    HasShadow() override;
    virtual float   GetShadowScaling() override;
    virtual SexyVector2 GetShadowOffset() override;

    virtual BoardEntityHeight GetEntityHeight() const override;
    void Idle() override;
protected:
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
private:
	bool			isZombieClose();
    void            tossZombie(Zombie* i_zombie);
    void            tossEnded(Zombie* i_zombie);
    
    void            setState(uint i_plantState);
	
	bool			isAnimDone();

	AnimHandle		m_playingAnim;
    
    pvztime_t       m_zombieStunTimeAfterPF;
    std::vector<ZombiePtr> m_zombieStunedAfterPF;
};



#endif
