/*
 * PlantDefeatZombieChallenge.h
 *
 *  Created on: 2021-7-28
 *      Author: zhousen
 */

#ifndef PLANTDEFEATZOMBIECHALLENGE_H_
#define PLANTDEFEATZOMBIECHALLENGE_H_

#include "ChallengeModule.h"
#include "DamageInfo.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "TodDebug.h"
#include "UIWidget.h"
#include "RestrictionSet.h"
#include "TodStringFile.h"
#include "StringHelper.h"

class PlantDefeatZombieChallenge : public Challenge
{
public:
	RT_CLASS_DEFINE(PlantDefeatZombieChallenge, Challenge, RtClass);

	SexyString GetProgressDescription() const override;

protected:
	void initializeModule() override;
	void registerForEvents() override;

private:
	void PlantKillZombie(const std::string& plant);
	void onGameplayEnded();
	void onGameplayStarted();

	int m_zombiesKilled;
	RtWeakPtr<UIWidget> m_defeatedZombiesWidget;
};

class PlantDefeatZombieChallengeProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PlantDefeatZombieChallengeProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return PlantDefeatZombieChallenge::StaticGetClass();
	}

	SexyString GetDescription() const override
	{
		SexyString numZombies = StrFormat(_S("%d"), NumZombiesToKill);
		SexyString descriptionText = StringToSexyString(Description);
		std::string plantName = "[" + Sexy::Upper(PlantTypeName) + "]";
		SexyString realPlantName = StringHelper::ToStringValue(plantName);
		SexyString description = TodReplaceString(descriptionText, _S("{NUMBER}"), numZombies);
		SexyString finalDescription = TodReplaceString(description, _S("{NAME}"), realPlantName);
		return finalDescription;
	}

	SexyString GetDescriptiveName() const override
	{
		return TodStringTranslate(_S("[CHALLENGE_PLANT_DEFEAT_ZOMBIES_NAME]"));
	}

	PlantDefeatZombieChallengeProps()
	: NumZombiesToKill(0)
	{
		PlantTypeName = "";
	}

	std::string Description;
	int NumZombiesToKill;// how many zombies should be killed
	std::string PlantTypeName;// use plant to kill zombie

};

#endif /* PLANTDEFEATZOMBIECHALLENGE_H_ */
