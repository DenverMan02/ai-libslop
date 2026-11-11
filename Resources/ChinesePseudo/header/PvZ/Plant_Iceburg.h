#ifndef __PLANT_ICEBURG_H__
#define __PLANT_ICEBURG_H__

#include "PlantFramework.h"
#include "StateMachine.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

enum PlantState_Iceburg
{
	STATE_SHOOT = STATE_FRAMEWORK_BEGIN,
};

STATE_ENUM_BASE_BEGIN(LaunchState)
	LaunchState_INIT,
	LaunchState_LAUNCHING,
	LaunchState_END,
STATE_ENUM_END(LaunchState);

class PlantTypeIceburg : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeIceburg, PlantType, RtClass);
    virtual int GetCost(PlantAvatarType i_avatarType) const override;
};


class PlantIceburg : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantIceburg, PlantFramework, RtClass);

	virtual void Initialize() override;
    virtual void	PostInitialize() override;

	virtual void UpdateActions() override;

	virtual float GetShadowScaling() override
	{ 
		return 0.7f; 
	}

	virtual bool HasShadow() override;
	
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool TryBlockZombossRush(Zombie* i_zomboss) override;

	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;

	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;

//    virtual GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon);

	virtual void		PlayAttackAnimation() override;

	void 				LaunchSnowball(const SexyVector2& i_target);

	void				FindValidZombiesAndAttack();

	//launch state
	bool       			 	isInState(LaunchState i_state) const;
	void        			setState(LaunchState i_newState);
	bool CanBeTargeted() override { return false; }
    void Idle() override;
    
    //override for star level
    Sexy::Rect GetPlantAttackGridRect(PlantWeapon i_plantWeapon) override;
    Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    
protected:
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	
	/// Bomb State Machine
	DECLARE_STATE_FUNCTIONS(LaunchState, INIT);
	DECLARE_STATE_FUNCTIONS(LaunchState, LAUNCHING);
	DECLARE_STATE_FUNCTIONS(LaunchState, END);

private:
	int32					getLaunchStateSerialization();
	void					setLaunchStateSerialization(int32 i_state);
	
	bool 							m_exploded;
	pvztime_t 						m_nextLaunchTime;
	StateMachine<LaunchState> 		m_LaunchState;
	int								m_launchNumbers;
	std::vector<BoardEntityPtr> 	m_validTargets;
	std::vector<BoardEntityPtr> 	m_hittedTargets;
};

#endif //__PLANT_ICEBURG_H__
