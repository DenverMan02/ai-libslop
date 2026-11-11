#ifndef __PLANT_POTATOMINE_H__
#define __PLANT_POTATOMINE_H__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "ComponentDamageRadius.h"

class PotatomineProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PotatomineProps, PlantPropertySheet, RtClass);
    
    bool Primal = false;
    int ReadyDecPercent = 0;
    float TimeUntilArmed = 15.f;
    DuplicatableProps DuplicationInformation;
    ComponentDamageRadiusProps ExplodeRadius;
};

class PlantPotatomine : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPotatomine, PlantFramework, RtClass);

private:
	enum State 
	{
		SELF_STATE_NOTREADY = STATE_FRAMEWORK_BEGIN,
		STATE_RISING,
		STATE_ARMED,
		STATE_EXPLODING,
		STATE_FLYING,
	};

public:  

	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual bool	HasShadow() override;
    virtual float	GetShadowScaling() override;
    void TakeSmashAttack(ZombiePtr i_instigator) override;
    
    void SetIsFlying();
    void ForceArming();
	void FlyThroughAir(SexyVector2 i_startPixelLoc, SexyVector2 i_destPixelLoc);

	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override
	{ 
		return (COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES);
	}

	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	virtual void 	OnRelocationComplete() override;

	virtual bool 	CanBeShoveled() override;
    virtual bool	IsInvincible() const override;
    virtual bool    TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;

	virtual bool	CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void Idle() override;
    
    void onSetDuplicate(bool i_duplicate) override { };
    
private:
    void Explode();
    bool DoDuplicate();
    bool shouldExplodeBecauseShovedOffBoard(const int i_direction);
    
    RtWeakPtr<ComponentDamageRadius> m_explodeRadius;
};

#endif
