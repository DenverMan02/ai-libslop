//
//  TutorialPeashooterDeath.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/15/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TutorialPeashooterDeath_h
#define PlantsVersusZombies2_TutorialPeashooterDeath_h

#include "LevelModule.h"
#include "GameNotify.h"

class TutorialPeashooterDeathModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(TutorialPeashooterDeathModule, LevelModule, RtClass) {}

protected:
	virtual void	registerForEvents() override;

private:
	void			onPlantDied(class Plant* i_plant);
};

class TutorialPeashooterDeathProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(TutorialPeashooterDeathProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return TutorialPeashooterDeathModule::StaticGetClass();
	}
};


#endif
