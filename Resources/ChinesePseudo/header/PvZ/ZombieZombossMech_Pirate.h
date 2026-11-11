//
//  ZombieZombossMech_Pirate.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_Pirate__
#define __PlantsVersusZombies2__ZombieZombossMech_Pirate__

#include "ZombieZombossMech.h"

class ZombossRocket;

class ZombossImpCannonActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossImpCannonActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombossImpCannonActionDefinition()
	{
		ImpLaunchDelay = 3.0f;
		ImpLaunchInterruptDamageAmount = 100.f;
		ImpLaunchCount = 7;
		ImpLaunchTime = 1.0;
		ImpLaunchTimeVariance = 0.5;
		ImpLaunchHeight = 300;
		ImpLaunchMinColumn = 2;
		ImpLaunchMaxColumn = 5;
	}

	virtual bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::string ImpType;
	float ImpLaunchInterruptDamageAmount;
	float ImpLaunchDelay;
	int ImpLaunchCount;
	float ImpLaunchTime;
	float ImpLaunchTimeVariance;
	float ImpLaunchHeight;
	int ImpLaunchMinColumn;
	int ImpLaunchMaxColumn;
};

class ZombossImpCannonActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossImpCannonActionHandler, ZombieActionHandler, RtClass);
	
	ZombossImpCannonActionHandler()
		: m_endLoopingAt(PVZ_EOT())
	{}
	
protected:
	virtual void onStartAction() override;
	virtual void onUpdateAction() override;
	virtual void onEndAction() override;
	
private:
	void onRocketStartAnimDone(const std::string& i_animName);
	void onRocketLaunchAnimDone(const std::string& i_animName);
	void onRocketLaunchFireAnimDone(const std::string& i_animName);

	pvztime_t m_endLoopingAt;
};

class ZombieZombossMechPirateProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechPirateProps, ZombieZombossMechProps, RtClass);
};

class ZombieZombossMech_Pirate : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_Pirate, ZombieZombossMech, RtClass);
	
	void SetCurrentImpCannonActionDef(ZombieActionDefinitionPtr i_actionDef);

private:
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void launchCannonImps();

	ZombieActionDefinitionPtr m_impCannonActionDef;
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_Pirate__) */
