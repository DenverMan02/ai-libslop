//
//  MechanismPlankModule.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2/19/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_MechanismPlankModule_h
#define PlantsVersusZombies2_MechanismPlankModule_h

#include "LevelModule.h"
#include "BoardEnums.h"
#include "PlantType.h"

class MechanismPlankModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(MechanismPlankModule, LevelModule, RtClass){}

	virtual void registerForEvents() override;

private:
	void placeMechanismPlanksAndGears();
    
    void gatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons);
};


class MechanismPlankProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(MechanismPlankProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return MechanismPlankModule::StaticGetClass();
	}

	Sexy::Rect			MechanismGearsRect;
	std::vector<int>	MechanismPlankRows;
};

#endif
