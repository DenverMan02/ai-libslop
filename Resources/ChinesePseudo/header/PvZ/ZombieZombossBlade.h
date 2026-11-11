//
//  ZombieZombossBlade.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieZombossBlade_h
#define PlantsVersusZombies2_ZombieZombossBlade_h

#include "Zomboss.h"
#include "ZombiePropertySheet.h"

STATE_ENUM_CHILD_BEGIN(ZombossBladeState, ZombossState)
	ZombossBlade_TakeShield,
	ZombossBlade_Shielding,
	ZombossBlade_Summon,
	ZombossBlade_Dash,
	ZombossBlade_DashAttack,
	ZombossBlade_Chop,
    ZombossBlade_PrepareBladeKee,
	ZombossBlade_TakeBladeKee,
	ZombossBlade_ChangeLane,
	ZombossBlade_HangBeforeLanding,
	ZombossBlade_Land,
	ZombossBlade_FlyOutsideScreen,
	ZombossBlade_FlyAttackWarning,
	ZombossBlade_FlyAttack,
STATE_ENUM_END(ZombossBladeState);


enum EZombossBladeAction
{
	ZombossBladeInvalidAction,
	ZombossBladeTakeShieldAction,
	ZombossBladeSummonAction,
	ZombossBladeRandomAction,
	ZombossBladeFlyAttackAction
};

enum EZombossBladeRandomAction
{
	ZombossBladeInvalidRandomAction,
	ZombossBladeDashAction,
	ZombossBladeBladeKeeAction
};

struct ZombossRandomAction
{
	ZombossRandomAction()
	{
		ActionWeight = 200;
		RandomAction = ZombossBladeInvalidRandomAction;
	}

	int 						ActionWeight;
	EZombossBladeRandomAction 	RandomAction;
};

struct ZombossBladeStage
{
	typedef std::vector<std::string> 					PlantList;
	typedef std::vector<std::string>::iterator 			PlantListIterator;
	typedef std::vector<std::string>::const_iterator 	PlantListConstIterator;

	ZombossBladeStage()
	{
		AnimRateModifier				= 1.0f;
		HitPoints 						= 5000;
		Level 							= 1;
		IdleTime.SetRange(1.f, 1.f);
		PercentOfDamageWhenShielding 	= 0.3f;

		SummonCountMin					= 0;
		SummonCountMax					= 0;

		DashDPS							= 4000.0f;
		DashAnimRate					= 2.0f;
		DashVelocityByGrid 				= 1.0f;

		BladeKeeVelocityByGrid 			= 1.0f;

		FlyAttackVelocityByGrid 		= 1.5f;
		FlyAttackWarningDuration.SetRange(1.f, 1.f);
		FlyAttackCountMin				= 0;
		FlyAttackCountMax				= 0;
	}

	/// Properties
	int									HitPoints;
	int 								Level;
	float								AnimRateModifier;
	ValueRange							IdleTime;
	PlantList							PlantListTakeFullDamage;
	float 								PercentOfDamageWhenShielding;

	/// Skills

	std::vector<ZombossRandomAction>	RandomActions;

	//Summon
	CZombieSummonDataPool				ZombieSummonDataPool;
	int 								SummonCountMin;
	int 								SummonCountMax;

	//Dash
	float								DashDPS;
	float								DashAnimRate;
	float								DashVelocityByGrid;

	//BladeKee
	float 								BladeKeeVelocityByGrid;

	//FlyAttack
	float								FlyAttackVelocityByGrid;
	ValueRange							FlyAttackWarningDuration;
	int 								FlyAttackCountMin;
	int 								FlyAttackCountMax;
};

class ZombieZombossBladeProps : public ZombossProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossBladeProps, ZombossProps, RtClass);

	ZombieZombossBladeProps()
	{

	}

	std::vector<ZombossBladeStage> 	Stages;
};

class ZombieZombossBlade : public Zomboss
{
public:
	RT_CLASS_DEFINE(ZombieZombossBlade, Zomboss, RtClass);

	//interfaces from Zomboss
    virtual ImagePtr getHeadIcon() override;
	virtual void startFunctioning() override;

	virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
	virtual Sexy::Point GetGridExtents() const override;

	virtual void TakeDamage(const DamageInfo& i_damage) override;
    
    virtual void onEndCondition(ZombieConditions i_condition) override;
    
    bool IgnoreKillbox() const override;
    
protected:
	//interfaces from Zomboss
	virtual void onChangeActiveStage(int i_activeStageIndex) override;
	virtual void onChangeStageAnimDone(const std::string& i_label) override;
	virtual bool canChangeStage() const override;

	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(class Sexy::Graphics* i_g) override;

    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
private:
	DECLARE_STATE_FUNCTIONS(ZombieState, TakeShield);
	DECLARE_STATE_FUNCTIONS(ZombieState, Shielding);
	DECLARE_STATE_FUNCTIONS(ZombieState, Summon);
	DECLARE_STATE_FUNCTIONS(ZombieState, Dash);
	DECLARE_STATE_FUNCTIONS(ZombieState, DashAttack);
	DECLARE_STATE_FUNCTIONS(ZombieState, Chop);
    DECLARE_STATE_FUNCTIONS(ZombieState, PrepareBladeKee);
	DECLARE_STATE_FUNCTIONS(ZombieState, TakeBladeKee);
	DECLARE_STATE_FUNCTIONS(ZombieState, ChangeLane);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangBeforeLanding);
	DECLARE_STATE_FUNCTIONS(ZombieState, Land);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyOutsideScreen);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyAttackWarning);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyAttack);

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);

	const ZombossBladeStage& getActiveStage() const;
	void initializeStageData(const ZombossBladeStage& stage);

	//skill-related
	void 			resetSkills();
	bool			canCoolDownIdleTime();
	bool			canPerformAction();
	void 			findPlantsToChop(std::vector<BoardEntity*>& o_entityList);
    void            FindZombieToChop(std::vector<Zombie*>& zombieList);
	void 			findPlantsToFlyAttack(std::vector<BoardEntity*>& o_entityList);
	bool 			tryDashAction();
	SexyVector3  	findPositionToLand();
	void 			chopPlantsInFront(const std::string& i_callbackName);
	Sexy::Rect 		calcZombossAttackRect();


	void 			onTakeShieldAnimDone(const std::string& i_label);
	void 			onSummonAnimDone(const std::string& i_label);
	void 			onDashAttackAnimDone(const std::string& i_label);
    void 			onDashEndAnimDone(const std::string& i_label);
	void 			onChopAnimDone(const std::string& i_label);
	void 			onJumpAnimDone(const std::string& i_label);
	void 			onLandAnimDone(const std::string& i_label);
	void 			onFlyOusideScreenAnimDone(const std::string& i_label);
	void 			onPrepareBladeKeeAnimDone(const std::string& i_label);
    void 			onTakeBladeKeeAnimDone(const std::string& i_label);

	// Action picking
	void 			performZombossAction();
	bool 			performZombossSummonAction();
	bool 			performZombossRandomAction();
	bool 			performZombossFlyAttackAction();
	bool 			performZombossTakeShieldAction();
	bool 			tryPerformZombossRandomAction(EZombossBladeRandomAction i_randomAction);

	//Damage process when shielding
	void 			processDamage(DamageInfo& io_damage);

private:
    
	pvztime_t							m_idleTime;

	//skills

	//Action
	EZombossBladeAction					m_previousAction;
	EZombossBladeRandomAction			m_previousRandomAction;

	//summon
	int									m_summonCountLeft;

	//dash
	bool								m_dashAfterLanding;
	float								m_dashVelocity;

	//change lane
	pvztime_t							m_hangEndTime;

	//FlyAttack
	int 								m_rowToFlyAttack;
	float								m_flyAttackVelocity;
	pvztime_t							m_flyAttackWarningEndTime;
	int									m_flyAttackCountLeft;
	RtWeakPtr<class PopAnimRig> 		m_FlyAttackWarningEffect;
};

#endif
