//
//  ZombieZombossMech_IceAge.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 1/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_IceAge__
#define __PlantsVersusZombies2__ZombieZombossMech_IceAge__

#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "GridItemZombieConditionTarget.h"
#include "ZombieAction.h"

class ZombossRocket;

class ZombieZombossMechIceAgeProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechIceAgeProps, ZombieZombossMechProps, RtClass);
	
	ZombieZombossMechIceAgeProps()
	{
		IceCrustHealth = 1;
	}
	
	RtWeakPtr<ZombieActionDefinition> RevealAction;
	RtWeakPtr<ZombieActionDefinition> CoverUpAction;
    
	int		IceCrustHealth;
};

class ZombieZombossMech_IceAge : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_IceAge, ZombieZombossMech, RtClass);
	
	void OnRocketHitGround(ZombossRocket* i_rocket) override;

    Sexy::Rect CalcGridFootprint() const override;
    
	int GetIceCrustMaxHealth();
	void AddCrust();
    int CalcRenderOrder() const override;
    
    void ShowFogEffect();
    
    void TakeDamage(const DamageInfo& i_damage) override;

protected:
	
	void onPlaceOnBoard() override;
    
	void startRandomAction() override;
	
	void Retreat(ZombieState i_endState) override;
	void StartCoverUp();
	
	void onSetHelm() override;
    void onTakeHelmDamage(const DamageInfo& i_receivedDamage) override;
	class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onEndCondition(ZombieConditions i_condition) override;

	bool ShouldDrawShadow() const override { return false; }
    
    void buildStunMovementCurve() override { getMovementCurve().Clear(); };
	
	void onZombossExitFinal() override;

private:
	
	void updateHelmEffects();
	void updateHelmEffect(Effect_PopAnim* effect);
    
private:
    bool m_bInEliminate = false;
};

class ZombieAnimRig_ZombossMech_IceAge : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_IceAge, ZombieAnimRig_ZombossMech, RtClass);

	ZombieAnimRig_ZombossMech_IceAge();
	
	void PlaySpawnGlacier(int i_column, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFreezeRow(int i_row, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayRegenerateIceCrust(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayReveal(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayStun(PopAnimRig::LoopingAnimContinuedDelegate i_onAnimContinued);

	void PlayRocketStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued) override;

	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	
	void SetCovered(bool i_covered) { m_isCovered = i_covered; }
	
protected:

	const char* getPreIntroAnimName() const override;
	const char* getIntroAnimName() const override;
	const char* getRocketStartAnimName() const override;
	const char* getRocketLaunchAnimName() const override;
	const char* getIdleAnimName() const override;
    const char* getStunEndAnimName() const override;
    
private:
	bool m_isCovered;
	
};

class ZombossIceAgeGlacierBlock : public GridItemBreakableTarget
{
public:
	RT_CLASS_DEFINE(ZombossIceAgeGlacierBlock, GridItemBreakableTarget, RtClass);

    void onKilled() override;
};

/// Actions

class ZombossSpawnGlacierColumnActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSpawnGlacierColumnActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossSpawnGlacierColumnActionDefinition()
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSpawnGlacierColumnActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSpawnGlacierColumnActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void onSpawnAnimationEnd(const std::string& i_animLabel);
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;

private:
	int m_columnToSpawn = -1;
    int m_currentRow = 1;
};


class ZombossCoverUpActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossCoverUpActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossCoverUpActionDefinition()
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossCoverUpActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossCoverUpActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void regenerateIceCrust() const;
	void onRegenerateAnimationEnd(const std::string& i_animLabel);
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	
};


class ZombossHelmLostActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossHelmLostActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossHelmLostActionDefinition()
	{}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
    
    pvztime_t IceCrustRevealMinTime = PVZ_EOT();
};

class ZombossHelmLostActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossHelmLostActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void onRevealAnimationEnd(const std::string& i_animLabel);

    pvztime_t m_revealEndTime = PVZ_EOT();
};


class ZombossFreezingWindRowActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossFreezingWindRowActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossFreezingWindRowActionDefinition()
	{}
	
	void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const override;

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossFreezingWindRowActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossFreezingWindRowActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void spawnFreezingWind(int i_rowToFreeze) const;
	void onFreezeAnimationEnd(const std::string& i_animLabel);
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;

private:
	int m_rowToFreeze = 1;
};


class ZombossSpawnShieldActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSpawnShieldActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossSpawnShieldActionDefinition()
	{}
	
	void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames) const override;
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSpawnShieldActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSpawnShieldActionHandler, ZombieActionHandler, RtClass);
	
protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void onSpawnShieldAnimationEnd(const std::string& i_animLabel);
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
};


#endif
