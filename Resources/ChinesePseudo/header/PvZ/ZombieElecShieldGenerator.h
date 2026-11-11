//

//  ZombieElecShieldGenerator.h

//  PlantsVersusZombies2

//

//  Created by Michael Fromwiller on 7/19/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__ZombieFutureProtector__

#define __PlantsVersusZombies2__ZombieFutureProtector__



#include "DamageInfo.h"

#include "PlatformAutodetect.h"

#include "RtDb.h"

#include "RtObject.h"

#include "StateMachine.h"

#include "TimeMgr.h"

#include "ZombieMech.h"

#include "ZombieAnimRig_Mech.h"



STATE_ENUM_CHILD_BEGIN(ZombieState_ElecShieldGenerator, ZombieState_Mech)

	ZS_ElecShieldGenerator_ActivatingShield,

	ZS_ElecShieldGenerator_DeactivatingShield,

STATE_ENUM_END(ZombieState_ElecShieldGenerator)


struct GeneratorValues
{
	float	ShieldSizeX = 3.0f;
	float	ShieldSizeY = 3.0f;
	float	ShieldHP = 1200.0f;
	float	ShieldReactivationDelay = 5.0f;
	float 	Velocity = 40.0f;
	bool 	IsValid = false;
};



class ZombieElecShieldGeneratorProps : public ZombieMechProps
{
public:
	RT_CLASS_DEFINE(ZombieElecShieldGeneratorProps, ZombieMechProps, RtClass);

	ZombieElecShieldGeneratorProps()
	{
		ShieldActivationColumn = 15.f;
		ShieldSizeX = 3.0f;
		ShieldSizeY = 3.0f;
		ShieldHP = 1200.0f;
		ShieldCount = 1;
		ShieldReactivationDelay = -1.0f;
		ShieldDiesUponLossOfControl = true;
		ShieldVelocityX = 40.0f;
	}

	float	ShieldActivationColumn;
	float	ShieldSizeX;
	float	ShieldSizeY;
	float	ShieldHP;
	int32	ShieldCount;
	float	ShieldReactivationDelay;
	bool	ShieldDiesUponLossOfControl;
	float   ShieldVelocityX;

	std::string SoundOnShieldActivate;
	std::string SoundOnShieldDeactivate;
};



class GridItemProtectorShield;



class ZombieElecShieldGenerator : public ZombieMech

{

public:

	RT_CLASS_DEFINE(ZombieElecShieldGenerator, ZombieMech, RtClass);



	virtual ~ZombieElecShieldGenerator();



	void				OnShieldDestroyed();



	virtual void EMPeachStun(pvztime_t i_duration) override;

	void				activateShield();

	void				deactivateShield();

    virtual void 		setInitValues(GeneratorValues i_values) { m_generatorValues = i_values; m_generatorValues.IsValid = true; }


	bool 				CanBeHypnotized() const override { return false; }


protected:



	virtual void		registerForEvents() override;



	DECLARE_STATE_FUNCTIONS(ZombieState, ElecShieldGenerator_ActivatingShield);

	DECLARE_STATE_FUNCTIONS(ZombieState, ElecShieldGenerator_DeactivatingShield);

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);

	OVERRIDE_STATE_ONENTER(ZombieState, Walk);

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	OVERRIDE_STATE_ONENTER(ZombieState, Die);

	OVERRIDE_STATE_UPDATE(ZombieState, EMPeachStun);

	void onDestroy() override;



	virtual void		onZombieInitialize() override;

	virtual void		onUpdate() override;

	virtual void		onLostHead() override;

	virtual void		onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

	virtual void		onFlicked(Zombie* i_zombie);

	virtual void		onApplyCondition(ZombieConditions i_condition) override;

    virtual void 		onChangeTeams(TeamFlags i_oldTeams, TeamFlags i_newTeams) override;

    virtual void 		onPlaceOnBoard() override;


private:



	void				onShieldActivateAnimationDone();

	void				onShieldDeactivateAnimationDone();



	void				spawnShield();





	// Private member variables (serialized)



	int					m_damageState;

	bool				m_shieldIsActive;

	int32				m_shieldCount;

	pvztime_t			m_shieldReactivationDelay;

	RtWeakPtr<GridItemProtectorShield>	m_shieldPtr;

	bool				m_playedWalkSound;

	bool				m_stoppedWalkSound;

	GeneratorValues		m_generatorValues;

};




enum ZombieAnimRigState_ElecShieldGenerator

{

	ZOMBIEANIM_ELECSHIELDGENERATOR_ACTIVATING_SHIELD = ZOMBIEANIM_USERDEFINED+1,

	ZOMBIEANIM_ELECSHIELDGENERATOR_HAS_SHIELD,

	ZOMBIEANIM_ELECSHIELDGENERATOR_DEACTIVATING_SHIELD,

};



class ZombieAnimRig_ElecShieldGenerator : public ZombieAnimRig_Mech

{

public:

    RT_CLASS_DEFINE(ZombieAnimRig_ElecShieldGenerator, ZombieAnimRig_Mech, RtClass);



	// Protector specific functionality

	virtual bool ActivateShield(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	virtual bool DeactivateShield(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);



	void SetDamageState(const int i_state) override;


protected:

	virtual void onPopAnimInitialized() override;

	virtual const std::vector<std::string>& getHeadLayerNames() override;

	virtual const std::vector<std::string>& getArmLayerNames() override;

	virtual const std::vector<std::string>& getArmReplacementPairNames() override;



	virtual void onAnimStopped() override;

};



#endif /* defined(__PlantsVersusZombies2__ZombieFutureProtector__) */

