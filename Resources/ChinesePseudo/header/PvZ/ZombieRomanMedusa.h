//
//  ZombieRomanMedusa.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 1/22/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef ZombieRomanMedusa_h
#define ZombieRomanMedusa_h

#include "RestrictionSet.h"
#include "StateMachine.h"
#include "ZombieIceAgeTroglobite.h"

class ZombieRomanMedusaProps : public ZombieIceAgeTroglobiteProps
{
public:
	RT_CLASS_DEFINE(ZombieRomanMedusaProps, ZombieIceAgeTroglobiteProps, RtClass);
	
	ZombieRomanMedusaProps()
	{
		std::string ImpType = "roman_armor4";
		NumberOfIceblocksToSpawnWith = 3;
		ConditionToApply = "stoneblocked";
		PetrifiedZombieHealthMultiplier = 1.5;
		PetrifiedZombieType = "zombie_statue";
	}
	
	float PetrifiedZombieHealthMultiplier;
	std::string PetrifiedZombieType;
};

class ZombieRomanMedusa : public ZombieIceAgeTroglobite
{
public:
	RT_CLASS_DEFINE(ZombieRomanMedusa, ZombieIceAgeTroglobite, RtClass);
	
	ZombieRomanMedusa() {}
	ZombiePtr FindPetrifyTarget();
	void spawnGridItemThatZombiePushes(int32_t column) override;
//	void DrawCollisionInfo(Graphics* g) override;
	
protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	void onApplyCondition(ZombieConditions i_condition) override;
	
private:
	void onZombieInitialize() override;
	bool tryPetrify();
	
	pvztime_t m_nextPetrifyTime;
};

class ZombieAnimRig_Medusa : public ZombieAnimRig_Troglobite
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Medusa, ZombieAnimRig_Troglobite, RtClass);
	
	bool PlayPetrify(AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieRomanMedusaPetrifyActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieRomanMedusaPetrifyActionDefinition, ZombieActionDefinition, RtClass);
	
	ValueRange TimeBeforeFirst;
	ValueRange TimeBetweenActions;
	ClassRestrictionSet CannotBePetrified;
	Rect PetrifyRectangle;
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, ZombieWithActions* i_zombie) const override;
};

class ZombieRomanMedusaPetrifyActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieRomanMedusaPetrifyActionHandler, ZombieActionHandler, RtClass);
	
	ZombieRomanMedusaPetrifyActionHandler()
	{}
	
	void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
	
protected:
	void onStartAction() override;
	void onAnimationDone(const std::string& i_animName);
	void onUpdateAction() override;
	void onEndAction() override;
	
private:
	void petrifyTarget();
};

#endif /* ZombieRomanMedusa_h */
