//
//  ZombieAction.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 5/9/12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEACTION_H__
#define __ZOMBIEACTION_H__

#include "ComponentBase.h"
#include "RtObject.h"
#include "ProjectilePropertySheet.h"
#include "RenderQueue.h"

class Zombie;
class ZombieWithActions;
class ZombieGeneralBase;

//
// Zombies can have phases.
//
enum ZombieActionPhase
{
	ActionPhase_None,
	ActionPhase_Entering,
	ActionPhase_SkillFirst,
	ActionPhase_Attacking,
	ActionPhase_Cooldown,
    ActionPhase_Stunned,
    ActionPhase_SkillLast,
	ActionPhase_Retreat,
	ActionPhase_RetreatInjured,
	ActionPhase_Dying,
	ActionPhase_Destroy
};

//
// ZombieActions are best thought of as AI states.
//
// They have implicit weights and frequency values for selection and tend to be self-running.
//
// Currently it is expected that there is one ZombieAction running at a time.  This is mainly
// because the system doesn't need the extra complexity.
//

typedef RtWeakPtr<const class ZombieActionDefinition> ZombieActionDefinitionPtr;

class ZombieActionDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ZombieActionDefinition, PropertySheetBase, RtClass);
	
	ZombieActionDefinition()
	: Weight(1), RepeatMin(0), RepeatMax(0), Phase(ActionPhase_None), PhaseAfter(ActionPhase_None), PhaseAfterRepeatZero(ActionPhase_None), CanPickAgain(false), Invulnerable(false), Cdtime(0)
	{}
	
	virtual bool CanStartAction(class ZombieWithActions* i_zombie) const { return true; }
	virtual bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const;
	
	int Weight;
	int RepeatMin;
	int RepeatMax;
	bool CanPickAgain;
	bool Invulnerable;
	std::string SoundOnStart;
    pvztime_t   Cdtime;
    ZombieActionPhase Phase;
   	ZombieActionPhase PhaseAfter;
	ZombieActionPhase PhaseAfterRepeatZero;
};

class ZombieActionHandler : public GameObject
{
public:
	RT_CLASS_DEFINE(ZombieActionHandler, GameObject, RtClass);
	
	ZombieActionHandler()
	: m_done(false)
	{}
	
	void InitFromDefinition(class Zombie* i_zomboss, ZombieActionDefinitionPtr i_definition);
	ZombieActionDefinitionPtr GetDefinition() const;
	
	void StartAction();
	void UpdateAction();
	void EndAction();
	
	bool IsActionDone() const;
	
	virtual void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) {}
	virtual void AddToRenderQueue(class RenderQueue* i_queue) {}
	
protected:
	virtual void onInitializeAction() {}
	virtual void onStartAction() {}
	virtual void onUpdateAction() {}
	virtual void onEndAction() {}
	
	void markActionDone();
	
	class ZombieWithActions* getZombie() const;
	
	template<typename T>
	T* getDefinition() const;
	
private:
	ZombieActionDefinitionPtr m_definition;
	RtWeakPtr<class ZombieWithActions> m_zombie;
	bool m_done;
};

template<typename T>
T* ZombieActionHandler::getDefinition() const
{
	return GetDefinition()->CastChecked<T>();
}

//
// Base Action Library
//

//
// Fire Projectiles
//

class ZombieProjectileActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieProjectileActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombieProjectileActionDefinition() {}
	
	ProjectilePropertySheetPtr Projectile;
	std::string ProjectileSound;
	SexyVector3 SpawnOffset;
	
	ValueRange TimeBeforeFirst;
	ValueRange TimeBetween;
    ValueRange TimeBetweenBarrages;
	
    std::string OverrideProjectileAnimation;
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieProjectileEliteActionDefinition : public ZombieProjectileActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieProjectileEliteActionDefinition, ZombieProjectileActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieProjectileActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieProjectileActionHandler, ZombieActionHandler, RtClass);
	
	ZombieProjectileActionHandler()	{}
	
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	
protected:
	virtual void fireProjectile();
	
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	void onAnimationDone(const std::string& i_animName);
};

class ZombieProjectileEliteActionHandler : public ZombieProjectileActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieProjectileEliteActionHandler, ZombieProjectileActionHandler, RtClass);

	virtual void fireProjectile();
};

//
// Launch Projectiles in the air
//

enum ZombieProjectileActionTarget
{
	ProjectileActionTarget_PlantGroups,
	ProjectileActionTarget_FriendlyZombies
};

class ZombieProjectileLaunchActionDefinition : public ZombieProjectileActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieProjectileLaunchActionDefinition, ZombieProjectileActionDefinition, RtClass);

	float		ApexHeight = 0;
	float		TimeUntilHit = 0;
	bool		OnlyHitTarget = false;
	bool		AttackZombiesOnce = false;
	bool		NoRepeatTargets = false;

	ZombieProjectileActionTarget	TargetType = ProjectileActionTarget_PlantGroups;

 	void launchProjectile(SexyVector3 i_source, SexyVector3 i_target, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit);
 	BoardEntity* findTarget(class ZombieWithActions* i_zombie) const;

 	bool CanStartAction(class ZombieWithActions* i_zombie) const override;
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
protected:
    virtual bool isValidTarget(BoardEntity* i_target) const { return true; }
};

class ZombieProjectileLaunchActionHandler : public ZombieProjectileActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieProjectileLaunchActionHandler, ZombieProjectileActionHandler, RtClass);

	void SetTarget(BoardEntityPtr i_target, SexyVector3 i_targetPosition) { m_target = i_target; m_targetPosition = i_targetPosition; }

protected:
	void fireProjectile() override;

	virtual void launchProjectile();
	void launchProjectile(SexyVector3 i_source, SexyVector3 i_target, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit);

public:
	SexyVector3 m_targetPosition;
	BoardEntityPtr m_target = nullptr;
};


//
// Drop Zombies On Board
//

class ZombieDropZombiesOnBoardActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieDropZombiesOnBoardActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombieDropZombiesOnBoardActionDefinition() {}
	
	int ColumnEnd = 0;
	int ColumnStart = 0;
	int Count = 0;
	int MinSpawn = 0;
	int MaxSpawn = 0;
	bool CenterOnInstigator = false;
	bool RiseFromGround = false;
	std::string ZombieName;
	std::vector<std::string> ZombieNames;
	std::vector<int> ZombieWeights;
	float TimeBeforeSpawn = 0.0f;
	float ZombieFallTime = 0.0f;
	
	std::string RampUpAnimation;
	std::string LoopingAnimation;
	std::string RampDownAnimation;
	
	std::string EffectTypeToShow;
	std::string DropAudioEvent = "Play_Zomb_LostCity_Zomboss_ZombieDrop_Lever_AirStrike";
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ZombieDropZombiesOnBoardActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieDropZombiesOnBoardActionHandler, ZombieActionHandler, RtClass);
	
	ZombieDropZombiesOnBoardActionHandler()
	{
		m_timeToDrop = PVZ_EOT();
		m_timeToPlaySpawnAnimation = PVZ_EOT();
	}
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	void onAnimationDone(const std::string& i_animName);
	
private:
	void postSpawnZombieSetup(Zombie* i_zombie, SexyVector3 i_destination, float i_fallDuration, float i_startHeight);
	void dropZombies();
	
	void createSpawnAnimation();
	void playLoopingAnimationAgain();
	
	float m_timeToDrop;
	float m_timeToPlaySpawnAnimation;
};

//
// Zombies can have phases.
//
enum InstantTargetAttackAction
{
    InstantTargetAttackAction_Invalid,
    InstantTargetAttackAction_PromoteRomans
};

class ZombieInstantTargetAttackActionDefinition : public ZombieProjectileLaunchActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombieInstantTargetAttackActionDefinition, ZombieProjectileLaunchActionDefinition, RtClass);

    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, ZombieWithActions* i_zombie) const override;

    InstantTargetAttackAction   InstantAttack = InstantTargetAttackAction_Invalid;

protected:
    bool isValidTarget(BoardEntity* i_target)const override;

};

class ZombieInstantTargetAttackActionHandler : public ZombieProjectileLaunchActionHandler
{
public:
    RT_CLASS_DEFINE(ZombieInstantTargetAttackActionHandler, ZombieProjectileLaunchActionHandler, RtClass);

    void SetTarget(BoardEntityPtr i_target, SexyVector3 i_targetPosition) { m_target = i_target; m_targetPosition = i_targetPosition; }

protected:
    void launchProjectile() override;

public:
    SexyVector3 m_targetPosition;
    BoardEntityPtr m_target = nullptr;
};


#endif

