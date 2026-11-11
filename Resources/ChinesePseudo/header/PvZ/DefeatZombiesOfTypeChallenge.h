//
//  DefeatZombiesOfTypeChallenge.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/26/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef DefeatZombiesOfTypeChallenge_h
#define DefeatZombiesOfTypeChallenge_h

#include "ChallengeModule.h"
#include "DamageInfo.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "TodDebug.h"
#include "UIWidget.h"
#include "RestrictionSet.h"
#include "TodStringFile.h"

class DefeatZombiesOfTypeChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(DefeatZombiesOfTypeChallenge, Challenge, RtClass);
	
	SexyString GetProgressDescription() const override;

protected:
	void initializeModule() override;
	void registerForEvents() override;
	
private:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayEnded();
	void onGameplayStarted();
	
	DamageTypeFlags getIgnoredDeathTypes() { return DAMAGE_FROM_MOWER | DAMAGE_SUICIDE | DAMAGE_FRIENDLY_FIRE; } //Check with design to see if any more need to be added
	
	int m_zombiesKilled;
	RtWeakPtr<UIWidget> m_defeatedZombiesWidget;
};

class DefeatZombiesOfTypeChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(DefeatZombiesOfTypeChallengeProps, LevelModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return DefeatZombiesOfTypeChallenge::StaticGetClass();
	}
	
	SexyString GetDescription() const override
	{
		SexyString numZombies = StrFormat(_S("%d"), NumZombiesToKill);
		SexyString descriptionText = StringToSexyString(Description);
		
		SexyString description = TodReplaceString(descriptionText, _S("{NUMBER}"), numZombies);
		
		return description;
	}
	
	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[CHALLENGE_DEFEAT_ZOMBIES_OF_TYPE_NAME]"));
	}
	
	DefeatZombiesOfTypeChallengeProps()
	: NumZombiesToKill(0)
	{}
	
	std::string Description;
	int NumZombiesToKill;
	ZombieRestrictionSet TypesToKill;
};

#endif /* DefeatZombiesOfTypeChallenge_h */
