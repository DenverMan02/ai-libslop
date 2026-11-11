//
//  LevelMutatorSimpleModifierModules.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 6/4/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

//
// These are modules that override one or more stats in the level, typically via accessors in BoardHelpers.
//

#ifndef PlantsVersusZombies2_LevelMutatorSimpleModifierModules_h
#define PlantsVersusZombies2_LevelMutatorSimpleModifierModules_h

#include <string>

#include "LevelModule.h"
#include "PVZTypes.h"
#include "RtObject.h"

class LevelMutatorRiftTimedSunModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelMutatorRiftTimedSunModule, LevelModule, RtClass);

    void postInitialize() override;
    int GetZombieSunDropValue(const std::string& i_typeName, int i_level);
    void GetOverridePlantBannedList(std::vector<std::string>& i_list);
    int GetPlantBannedListSize();

protected:
    void registerForEvents() override;

private:
    void onZombieKilled(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
};

struct RiftTimedSunDropData
{
	RiftTimedSunDropData()
	: ZombieTypeName("")
	{

	}

	std::string ZombieTypeName;
	std::vector<int> SunDropValues;
};

class LevelMutatorRiftTimedSunProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelMutatorRiftTimedSunProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelMutatorRiftTimedSunModule::StaticGetClass();
	}

	SexyString GetDescription() const override;

	SexyString GetDescriptiveName() const override;

	std::vector<RiftTimedSunDropData> SunDrops;
	std::vector<std::string> InvalidPlantTypes;
};

class LevelMutatorRiftTimedToolModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelMutatorRiftTimedToolModule, LevelModule, RtClass);

    void postInitialize() override;

    int GetToolSize();
    void GetOverrideToolList(std::vector<std::string>& i_list);
};

class LevelMutatorRiftTimedToolProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelMutatorRiftTimedToolProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelMutatorRiftTimedToolModule::StaticGetClass();
	}

	SexyString GetDescription() const override;

	SexyString GetDescriptiveName() const override;

	std::vector<std::string> ToolTypes;
};

class LevelMutatorStartingPlantfoodModule : public LevelModule
{ 
public:
	RT_CLASS_DEFINE(LevelMutatorStartingPlantfoodModule, LevelModule, RtClass) {}

    void postInitialize() override;
    int GetPlantfoodOverride();
};

class LevelMutatorStartingPlantfoodProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelMutatorStartingPlantfoodProps, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelMutatorStartingPlantfoodModule::StaticGetClass();
	}
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
	
	int StartingPlantfoodOverride = -1;
};


class LevelMutatorSeedSlotCountModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorSeedSlotCountModule, LevelModule, RtClass) {}
    
    int GetSeedSlotCountOverride();
};

class LevelMutatorSeedSlotCountProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorSeedSlotCountProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorSeedSlotCountModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int SeedSlotCountOverride = -1;
};


class LevelMutatorPowerupSetModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorPowerupSetModule, LevelModule, RtClass) {}
    
    std::string GetPowerupSetOverride();
};

class LevelMutatorPowerupSetProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorPowerupSetProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorPowerupSetModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    std::string PowerupSetOverride;
};


class LevelMutatorMaxSunModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorMaxSunModule, LevelModule, RtClass) {}
    
    int GetMaxSunOverride();
};

class LevelMutatorMaxSunProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorMaxSunProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorMaxSunModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int MaxSunOverride = -1;
};


class LevelMutatorStartSunModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorStartSunModule, LevelModule, RtClass) {}
    
    int GetStartSunModifier();
};

class LevelMutatorStartSunProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorStartSunProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorStartSunModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int StartSunModifier = 0;
};


class LevelMutatorMowerSpawnModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorMowerSpawnModule, LevelModule, RtClass) {}
    
    MowerSpawnOverride GetMowerSpawnOverride();
};

class LevelMutatorMowerSpawnProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorMowerSpawnProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorMowerSpawnModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    MowerSpawnOverride SpawnOverride = MOWER_SPAWN_USE_DEFAULT;
};

class LevelMutatorZombieCountdownFirstWaveSecsModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieCountdownFirstWaveSecsModule, LevelModule, RtClass) {}
    
    int GetFirstWaveSecsOverride();
};

class LevelMutatorZombieCountdownFirstWaveSecsProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieCountdownFirstWaveSecsProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorZombieCountdownFirstWaveSecsModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int FirstWaveSecs = -1;
};


class LevelMutatorZombieLevelModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieLevelModule, LevelModule, RtClass) {}
    
    int GetZombieLevelOverride();
};

class LevelMutatorZombieLevelProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieLevelProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorZombieLevelModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int BaseZombieLevel = -1;
};

class LevelMutatorZombieGeneralLevelModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieGeneralLevelModule, LevelModule, RtClass) {}
    
    int GetZombieLevelOverride();
};

class LevelMutatorZombieGeneralLevelProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorZombieGeneralLevelProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorZombieGeneralLevelModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int BaseZombieLevel = -1;
};

class LevelMutatorSunDropperModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorSunDropperModule, LevelModule, RtClass) {}
    
    LevelModuleProperties* GetLevelModuleOverride();
};

class LevelMutatorSunDropperProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorSunDropperProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorSunDropperModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    RtId    LevelModuleOverride;
};


class LevelMutatorRiftZombossPhasesModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LevelMutatorRiftZombossPhasesModule, LevelModule, RtClass) {}
    
    int GetZombossPhasesOverride();
};

class LevelMutatorRiftZombossPhasesProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LevelMutatorRiftZombossPhasesProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return LevelMutatorRiftZombossPhasesModule::StaticGetClass();
    }
	
	SexyString GetDescription() const override;
	
	SexyString GetDescriptiveName() const override;
    
    int     ZombossPhases = 3;
};


#endif
