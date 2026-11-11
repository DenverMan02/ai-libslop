/*
 * LevelBasedModifierModule.h
 *
 *  Created on: 2023-7-13
 *      Author: admin
 */

#ifndef LEVELBASEDMODIFIERMODULE_H_
#define LEVELBASEDMODIFIERMODULE_H_

#include <string>

#include "LevelModule.h"
#include "PVZTypes.h"
#include "RtObject.h"
#include "Singleton.h"
#include "ZombieEnums.h"
#include "GridItemAnimation.h"

typedef RtWeakPtr<class LevelModifierModuleCollection> LevelModifierModuleCollectionPtr;

#ifdef ENUM_OR_STRING
#undef ENUM_OR_STRING
#endif
#define ENUM_OR_STRING(x) x


enum LevelBasedModifierType
{
	ENUM_OR_STRING(LevelBasedModifier_DefaultZombieLevel),
	ENUM_OR_STRING(LevelBasedModifier_DefaultArtifactUseTimes),
	ENUM_OR_STRING(LevelBasedModifier_DefaultNoPlantfood),
	ENUM_OR_STRING(LevelBasedModifier_ZombieLevel),
	ENUM_OR_STRING(LevelBasedModifier_ZombieSpeed),
	ENUM_OR_STRING(LevelBasedModifier_Immunity),
	ENUM_OR_STRING(LevelBasedModifier_ZombieAttack),
	ENUM_OR_STRING(LevelBasedModifier_PlantPackets),
	ENUM_OR_STRING(LevelBasedModifier_SunReduced),
	ENUM_OR_STRING(LevelBasedModifier_PlantDamageReduced),
	ENUM_OR_STRING(LevelBasedModifier_PlantCDIncrease),
	ENUM_OR_STRING(LevelBasedModifier_DisablePlant),
	ENUM_OR_STRING(LevelBasedModifier_PlantCostIncrease),
	ENUM_OR_STRING(LevelBasedModifier_Mold),
	ENUM_OR_STRING(LevelBasedModifier_ZombieTypes)
};

enum LevelBasedModifierSubTypeMoldType
{
	LevelBasedModifierSubType_LeftMold,
	LevelBasedModifierSubType_RightMold
};

enum LevelBasedModifierSubTypeZombieType
{
	LevelBasedModifierSubType_TombRaiser = 1,
	LevelBasedModifierSubType_Barrel,
	LevelBasedModifierSubType_BarrelPusher,
	LevelBasedModifierSubType_Chicken,
	LevelBasedModifierSubType_Qigong,
	LevelBasedModifierSubType_FutureProtector,
	LevelBasedModifierSubType_Wizard,
	LevelBasedModifierSubType_BeachOctopus,
	LevelBasedModifierSubType_IceAgeDodo,
	LevelBasedModifierSubType_SkyCityTwinsPlane,
	LevelBasedModifierSubType_CrystalSkull,
	LevelBasedModifierSubType_EightiesGlitter,
	LevelBasedModifierSubType_DinoPushEgg,
	LevelBasedModifierSubType_ModernAllStar,
	LevelBasedModifierSubType_Gentleman,
	LevelBasedModifierSubType_Ballet,
	LevelBasedModifierSubType_Sushi,
	LevelBasedModifierSubType_ZombieBirthdayPharaoh
};

struct LevelBasedModifierInfo
{
	LevelBasedModifierInfo()
	: BaseType(LevelBasedModifier_ZombieLevel)
	, SubType(-1)
	, Level(1)
	{

	}

	LevelBasedModifierType BaseType;
	int SubType;
	int Level;
};

class LevelBasedModifierModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifierModule, LevelModule, RtClass);

	LevelBasedModifierModule();

    void SetLevel(int i_level) { m_level = i_level; }
    int GetLevel() { return m_level; }

    static std::string GetModuleClassName(LevelBasedModifierType i_type);

    virtual float GetValue(int i_index);
    int GetSubType();

protected:
    virtual void initializeModule() override;
    virtual void postInitialize() override;
    virtual void registerForEvents() override;

    int m_level;
    LevelBasedModifierType m_type;
};

class LevelBasedModifierModuleProps : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelBasedModifierModuleProps, LevelModuleProperties, RtClass);

	LevelBasedModifierModuleProps()
	: SubType(-1)
	, Level(1)
	{

	}

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifierModule::StaticGetClass();
	}

	int SubType;
	int Level;

	std::vector<std::vector<float>> Values;
};

// Zombie level
class LevelBasedModifier_ZombieLevelModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieLevelModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_ZombieLevelProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieLevelProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_ZombieLevelModule::StaticGetClass();
	}
};

// Zombie speed
class LevelBasedModifier_ZombieSpeedModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieSpeedModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_ZombieSpeedProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieSpeedProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_ZombieSpeedModule::StaticGetClass();
	}
};

// Zombie immunity
class LevelBasedModifier_ImmunityModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ImmunityModule, LevelBasedModifierModule, RtClass);

	void registerForEvents() override;

	void GetZombieConditionsImmunities(std::vector<ZombieConditions>& i_conditions);
};

class LevelBasedModifier_ImmunityProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ImmunityProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_ImmunityModule::StaticGetClass();
	}

	std::vector<std::vector<ZombieConditions>> ZombieConditionsImmunities;
};

// Zombie attack
class LevelBasedModifier_ZombieAttackModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieAttackModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_ZombieAttackProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieAttackProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_ZombieAttackModule::StaticGetClass();
	}
};

// Plant packets
class LevelBasedModifier_PlantPacketsModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantPacketsModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_PlantPacketsProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantPacketsProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_PlantPacketsModule::StaticGetClass();
	}
};

// Sun reduced
class LevelBasedModifier_SunReducedModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_SunReducedModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_SunReducedProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_SunReducedProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_SunReducedModule::StaticGetClass();
	}
};

// Plant damage reduced
class LevelBasedModifier_PlantDamageReducedModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantDamageReducedModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_PlantDamageReducedProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantDamageReducedProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_PlantDamageReducedModule::StaticGetClass();
	}
};

// Plant cost increase
class LevelBasedModifier_PlantCostIncreaseModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantCostIncreaseModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_PlantCostIncreaseProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantCostIncreaseProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_PlantCostIncreaseModule::StaticGetClass();
	}
};

// Plant disable
class LevelBasedModifier_DisablePlantModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DisablePlantModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_DisablePlantProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DisablePlantProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_DisablePlantModule::StaticGetClass();
	}
};

// Plant cd increase
class LevelBasedModifier_PlantCDIncreaseModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantCDIncreaseModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_PlantCDIncreaseProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_PlantCDIncreaseProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_PlantCDIncreaseModule::StaticGetClass();
	}
};

// Mold
class GridItemFakeMold : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemFakeMold, GridItemAnimation, RtClass);

	GridItemFakeMold();

	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
	void onGridItemInitialize() override;
};

class LevelBasedModifier_MoldModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_MoldModule, LevelBasedModifierModule, RtClass);

	void registerForEvents() override;

private:
	void loadComplete();
	void generateGridMap();
};

class LevelBasedModifier_MoldProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_MoldProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_MoldModule::StaticGetClass();
	}

	RtWeakPtr<class BoardGridMapProps> GridMap;
};

// Zombie types
class LevelBasedModifier_ZombieTypesModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieTypesModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_ZombieTypesProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_ZombieTypesProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_ZombieTypesModule::StaticGetClass();
	}
};

// Default zombie levels
class LevelBasedModifier_DefaultZombieLevelModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultZombieLevelModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_DefaultZombieLevelProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultZombieLevelProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_DefaultZombieLevelModule::StaticGetClass();
	}
};

// Default artifact use times
class LevelBasedModifier_DefaultArtifactUseTimesModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultArtifactUseTimesModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_DefaultArtifactUseTimesProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultArtifactUseTimesProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_DefaultArtifactUseTimesModule::StaticGetClass();
	}
};

// Default no plantfood
class LevelBasedModifier_DefaultNoPlantfoodModule : public LevelBasedModifierModule
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultNoPlantfoodModule, LevelBasedModifierModule, RtClass);
};

class LevelBasedModifier_DefaultNoPlantfoodProps : public LevelBasedModifierModuleProps
{
public:
	RT_CLASS_DEFINE(LevelBasedModifier_DefaultNoPlantfoodProps, LevelBasedModifierModuleProps, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelBasedModifier_DefaultNoPlantfoodModule::StaticGetClass();
	}
};

// Level Collection Property Sheet
class LevelModifierModuleCollection : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelModifierModuleCollection, PropertySheetBase, RtClass);

	LevelModifierModuleCollection()
	: Description("")
	, Name("")
	, ResourceName("")
	{

	}

	std::string Description;
	std::string Name;
	std::vector<LevelBasedModifierInfo> ModuleInfos;
	std::string ResourceName;

	virtual SexyString GetDescription();
	virtual SexyString GetName();
	virtual std::string GetResourceName();

	void GatherModuleInfos(std::vector<LevelBasedModifierInfo>& i_infos);
};

// Level Difficulty Property Sheet
class LevelModifierDifficulty : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelModifierDifficulty, PropertySheetBase, RtClass);

	LevelModifierDifficulty()
	: Difficulty(1)
	{

	}

	LevelModifierModuleCollectionPtr DefaultCollection;
	std::vector<LevelModifierModuleCollectionPtr> Collections;
	int Difficulty;
};

// Level Manager

struct LevelBasedSelectInfo
{
	LevelBasedSelectInfo(const LevelModifierModuleCollectionPtr& i_collectionPtr, int i_difficulty)
	: SelectedCollections(i_collectionPtr)
	, Difficulty(i_difficulty)
	{

	}

	LevelBasedSelectInfo()
	: Difficulty(1)
	{

	}

	LevelModifierModuleCollectionPtr SelectedCollections;
	int Difficulty;
};

class CollectionSorter
{
public:
	CollectionSorter() {}

	bool operator()(const LevelBasedSelectInfo& i_a, const LevelBasedSelectInfo& i_b) const;
};

class LevelBasedModifierModuleMgr : public LazySingleton<LevelBasedModifierModuleMgr>
{
public:
	LevelBasedModifierModuleMgr();
	virtual ~LevelBasedModifierModuleMgr();

	void AddLevelModifierModuleCollections(int i_difficultyIndex, int i_collectionIndex);
	void RemoveLevelModifierModuleCollections(int i_difficultyIndex, int i_collectionIndex);
	LevelModifierModuleCollectionPtr GetLevelModifierModuleCollection(int i_difficultyIndex, int i_collectionIndex);
	const std::vector<LevelModifierModuleCollectionPtr>& GetLevelModifierModuleCollections(int i_difficultyIndex);
	LevelModifierModuleCollectionPtr GetDefaultLevelModifierModuleCollection(int i_difficultyIndex);

	void TestCollection();
	void SyncCollections();
	void ClearSelectedCollections();

	bool HasTargetCollection(const std::string& i_aliasName);
	bool HasCollectionSelected(const std::string& i_aliasName);

	int GetTotalCollectionLevels();

private:
	void syncDefaultCollections(int i_difficultIndex);
	void syncSelectedCollections();
	void addCollectionModule(const LevelBasedModifierInfo& i_info);
	int getMaxSelectedDifficulty();

	std::vector<LevelBasedSelectInfo> m_selectedCollections;
};

#endif /* LEVELBASEDMODIFIERMODULE_H_ */
