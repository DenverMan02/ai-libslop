/*
 * 	InitialGridItemWizardCrucible.h
 *
 * 		Created on: 2022-5-27
 * 			Author: kkdud
 */

#ifndef PLANTSVERSUSZOMBIES2_PVZ2_INITIALGRIDITEMWIZARDCRUCIBLE_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_INITIALGRIDITEMWIZARDCRUCIBLE_H_

#include "LevelModule.h"

class InitialGridItemWizardCrucible : public LevelModule
{
public:
	RT_CLASS_DEFINE(InitialGridItemWizardCrucible, LevelModule, RtClass);

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
	virtual void registerForEvents() override;

private:
	void onLoadComplete();
};

struct WizardCrucibleDescribe
{
	WizardCrucibleDescribe()
	{
		GridX = -1;
		GridY = -1;

		BoilingDuration = 5.0f;
		CrucibleHitpoints = 2000.0f;
		ExplodeDamageAmount = 500.0f;
		VenomDamageAmountPerSecond = 50.0f;
		VenomExistDuration = 5.0f;
	}

	int				GridX;
	int				GridY;

	float BoilingDuration;
	float CrucibleHitpoints;
	float ExplodeDamageAmount;
	float VenomDamageAmountPerSecond;
	float VenomExistDuration;
};

class InitialGridItemWizardCrucibleProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(InitialGridItemWizardCrucibleProps, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return InitialGridItemWizardCrucible::StaticGetClass();
	}

	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<WizardCrucibleDescribe>	InitialGridItemWizardCrucibles;
};


#endif
