//
//  PennyPerkPennyShield.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 2/4/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef PennyPerkPennyShield_h
#define PennyPerkPennyShield_h

#include "BasicPerks.h"

class PennyPerkPennyShieldProperties : public PennyPerkProperties
{
public:
	RT_CLASS_DEFINE(PennyPerkPennyShieldProperties, PennyPerkProperties, RtClass);
	
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	std::vector<float> TimesBetweenApplications;
	std::vector<int> ShieldHealth;
	std::vector<std::vector<int>> ShieldColumns;
	std::vector<int> NumberOfShields;
	
	SexyString GetDescriptionForLevel(int i_level) override;
};

class PennyPerkPennyShield : public PennyPerkTimedEffect
{
	RT_CLASS_DEFINE(PennyPerkPennyShield, PennyPerkTimedEffect, RtClass);
	
protected:
	void onUpdate() override;
	
private:
	pvztime_t calcNextUpdateTime() override;
	void createShields();
};

#endif /* PennyPerkPennyShield_h */
