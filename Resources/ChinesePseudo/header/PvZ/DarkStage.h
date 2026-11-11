//
//  DarkStage.h
//  PlantsVersusZombies2
//
//  Created by Erik Rydeman on 8/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DarkStage_h
#define PlantsVersusZombies2_DarkStage_h

#include <string>

#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "ZombieEnums.h"

class DarkStage : public StageModule
{
    
public:
    RT_CLASS_DEFINE(DarkStage, StageModule, RtClass);
    
	ZombieTypePtr			GetArmor3ZombieType();
	virtual ZombieTypePtr	GetZombieTypeForBasicHelm(HelmType i_helmType) override;
	virtual ZombieTypePtr	ResolveZombieType(const std::string& i_genericTypeName);
	
	//void GenerateRandomEvents(const DangerRoomPropertySheet* i_dangerRoomProps, const int i_level, MTRand &i_random, WaveManagerProperties *o_props) const override;

protected:
    virtual void registerForEvents() override;
	virtual int	GetDefaultZombieSpawnPositionX(int i_row) override;
    
private:
	ZombieTypePtr m_armor3ZombieType;
};



class DarkStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(DarkStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return DarkStage::StaticGetClass();
	}

	std::string Armor3ZombieTypeName;
};

#endif


