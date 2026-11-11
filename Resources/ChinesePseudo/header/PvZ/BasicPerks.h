//
//  BasicPerks.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 6/5/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef BasicPerks_h
#define BasicPerks_h

#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "Wave.h"
#include "ZombieEnums.h"

typedef RtWeakPtr<class PennyPerkProperties> PennyPerkPropertiesPtr;

class PennyPerkProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(PennyPerkProperties, PropertySheetBase, RtClass);

	std::string TypeName;
	std::string ClassName;
	std::string Description;
	std::string IconName;

	std::vector<MapEventSubType> LevelTypesWhereEnabled;
	std::vector<MapEventSubType> LevelTypesWhereDisabled;

	virtual SexyString GetDescriptionForLevel(int i_level);
	virtual SexyString TranslatePerkName();
};

//To be extended for each new perk
class PennyPerk : public GameObject
{
public:
	RT_CLASS_DEFINE(PennyPerk, GameObject, RtClass);
	PennyPerk();
	virtual ~PennyPerk();
	virtual void Initialize(PennyPerkPropertiesPtr i_propsPtr, int i_level = 0);
	PennyPerkPropertiesPtr GetProps() { return m_props; }
	virtual void Activate();

	bool IsActivated() { return m_activated; }

protected:
	int m_perkLevel;
	PennyPerkPropertiesPtr m_props;
	bool m_activated;
};

class PennyPerkTimedEffect : public PennyPerk
{
	RT_CLASS_DEFINE(PennyPerkTimedEffect, PennyPerk, RtClass);
	~PennyPerkTimedEffect();
	void Activate() override;

protected:
	virtual void update();
	virtual void onUpdate() {}
	virtual void updateOthers() {}
	virtual void onLevelStart();
	virtual void onBasicLevelStart();
	virtual void onLastStandLevelStarting();
	virtual pvztime_t calcNextUpdateTime();

	pvztime_t m_nextUpdateTime;
};


///Traffic Jam

class PennyPerkTrafficJamProperties : public PennyPerkProperties
{
	RT_CLASS_DEFINE(PennyPerkTrafficJamProperties, PennyPerkProperties, RtClass);

	std::vector<int> ZombieDelayLevels;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkTrafficJam : public PennyPerk
{
public:
	RT_CLASS_DEFINE(PennyPerkTrafficJam, PennyPerk, RtClass);
	~PennyPerkTrafficJam() {}
	void Activate() override;
	int GetDelaySeconds();

private:
	int m_waveDelaySeconds;
};


///More Score

class PennyPerkMoreScoreProperties : public PennyPerkProperties
{
	RT_CLASS_DEFINE(PennyPerkMoreScoreProperties, PennyPerkProperties, RtClass);

	std::vector<float> ScoreBonusPercentage;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkMoreScore : public PennyPerk
{
public:
	RT_CLASS_DEFINE(PennyPerkMoreScore, PennyPerk, RtClass);
	PennyPerkMoreScore() {}
	void Activate() override;
	float GetBonusScorePercentage();

private:
	float m_additionalScorePercentage;
};


///Sun Break

class PennyPerkSunBreakProperties : public PennyPerkProperties
{
	RT_CLASS_DEFINE(PennyPerkSunBreakProperties, PennyPerkProperties, RtClass);

	std::vector<int> NumberOfBursts;
	std::vector<int> SunPerBurst;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkSunBreak : public PennyPerk
{
public:
	RT_CLASS_DEFINE(PennyPerkSunBreak, PennyPerk, RtClass);
	PennyPerkSunBreak() {}
	void Activate() override;

private:
	void onWaveStarted(int i_waveNumber, WaveType::WaveType i_waveType, bool i_isFinalWave);

	int m_numBurstsToSpawn;
	int m_sunPerBurst;
	int m_numExtraBurstsSpawned;
};


///Zombie Inhibitor

class PennyPerkZombieInhibitorProperties : public PennyPerkProperties
{
    RT_CLASS_DEFINE(PennyPerkZombieInhibitorProperties, PennyPerkProperties, RtClass);

    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

    std::vector<class ClassRestrictionSet> ZombiesToRemove;
    std::string ZombieTypeToSwapIn;
	std::string DisplayName;
	std::vector<std::string> LevelDescriptions;

	SexyString TranslatePerkName() override;
	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkZombieInhibitor : public PennyPerk
{
public:
    RT_CLASS_DEFINE(PennyPerkZombieInhibitor, PennyPerk, RtClass);
    ~PennyPerkZombieInhibitor() {}

    ZombieTypePtr TryOverrideZombieType(ZombieTypePtr i_zombieType);
};


///Apply Condition

class PennyPerkApplyConditionProperties : public PennyPerkProperties
{
	RT_CLASS_DEFINE(PennyPerkApplyConditionProperties, PennyPerkProperties, RtClass);

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<float> TimesBetweenApplications;
	std::vector<int> ConditionDamageValues;
	std::vector<float> ConditionDurations;
	std::vector<ZombieConditions> ConditionsToApply;
    std::vector<int> MinZombiesToAffect;
    std::vector<int> MaxZombiesToAffect;

	SexyString GetDescriptionForLevel(int i_level) override;
	SexyString TranslatePerkName() override;
};

class PennyPerkApplyCondition : public PennyPerkTimedEffect
{
public:
	RT_CLASS_DEFINE(PennyPerkApplyCondition, PennyPerkTimedEffect, RtClass);

protected:
	void onUpdate() override;

private:
	pvztime_t calcNextUpdateTime() override;

	void applyCondition();
	bool canApplyCondition(class Zombie* i_zombie, ZombieConditions i_condition);
};

class PennyPerkSunBankProperties : PennyPerkProperties
{
public:
	RT_CLASS_DEFINE(PennyPerkSunBankProperties, PennyPerkProperties, RtClass);

	std::vector<int> AdditionalStartingSun;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkSunBank : public PennyPerk
{
public:
	RT_CLASS_DEFINE(PennyPerkSunBank, PennyPerk, RtClass);

	void Activate() override;
};

class PennyPerkQuickDeliveryProperties : PennyPerkProperties
{
public:
	RT_CLASS_DEFINE(PennyPerkQuickDeliveryProperties, PennyPerkProperties, RtClass);

	std::vector<float> TimeReductionPercentage;

	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkQuickDelivery : public PennyPerk
{
public:
	RT_CLASS_DEFINE(PennyPerkQuickDelivery, PennyPerk, RtClass);

	void Activate() override;

	float GetTimeReductionMultiplier();

private:
	float m_timeReductionMultiplier = 0;
};

namespace Message
{
    void RiftLevelPerkActivation(PennyPerk* i_perk);
}

#endif /* BasicPerks_h */
