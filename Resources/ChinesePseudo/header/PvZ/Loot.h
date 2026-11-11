//
//  Loot.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 10/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Loot_h
#define PlantsVersusZombies2_Loot_h

#include "PropertySheetBase.h"
#include "RtObject.h"
#include "RtDb.h"
#include "PVZTypes.h"
namespace Sexy {
class SexyVector3;
}  // namespace Sexy

// dsiems - At some point we could refactor this so that the designers
// just need to specify the collectable type as a string. We'd need
// a real collectable factory to be able to do this, instead of the various
// LawnApp::Add*Collectable functions.
enum Loot
{
	PVZ_BEGIN_ENUM(LOOT_),
	LOOT_None,
	LOOT_SilverCoin,
	LOOT_GoldCoin,
	LOOT_Diamond,
	LOOT_EgyptKey,
	LOOT_PirateKey,
	LOOT_CowboyKey,
    LOOT_KongfuKey,
	LOOT_FutureKey,
    LOOT_DarkKey,
    LOOT_BeachKey,
    LOOT_IceageKey,
    LOOT_SkycityKey,
    LOOT_LostcityKey,
    
	// These have not been exported to designers yet.
	LOOT_ShinyPresent,
	LOOT_NormalPresent,
	
	LOOT_Powerup,
    LOOT_Component,
	PVZ_END_ENUM(LOOT_)
};

// Per-level loot configuration.
// Level must have this to drop loot.
class LootConfig : public RtObject
{
	RT_CLASS_DEFINE(LootConfig, RtObject, RtClass);
public:
	LootConfig()
	{
		LevelLength = -1.0f;
		Disable = false;
	}

	bool Disable;
	double LevelLength;
};
typedef RtWeakPtr<LootConfig> LootConfigPtr;

// Each entry represents a type of loot that may be scheduled.
// Duplicates on the Loot enum are allowed.
struct LootTableEntry
{
	LootTableEntry()
	{
		UniqueId = "";
		Type = LOOT_None;
		Min = 0;
		Max = 0;
		Period = 0;
		World = "";
		EnabledAfter = "";
	}

	std::string UniqueId;
	Loot Type;
	int Min;
	int Max;
	double Period;
	std::string World;
	std::string EnabledAfter;
};

// List of statically defined loot scheduling data.
class LootTable : public RtObject
{
	RT_CLASS_DEFINE(LootTable, RtObject, RtClass);
public:
	LootTable() {}
	std::vector<LootTableEntry> Entries;
};

// Per-LootEntry save data.
struct LootEntrySaveData
{
	LootEntrySaveData() 
	{
		UniqueId = "";
		LevelLengthsPlayed = 0.0f;
		NextDropTime = FLT_MAX;
		NextScheduleTime = 0.0f;
	}

	std::string UniqueId;
	double LevelLengthsPlayed; 	// Number of 'LevelLengths' played on this entry.
	double NextDropTime;		// In 'LevelLengths' units.
	double NextScheduleTime; 	// In 'LevelLengths' units.
};

// This needs to be serialized outside the player profile
// on a per-profile basis. We want it outside the profile
// so that we don't end up with wacky merge conflicts server-side.
class LootSaveData : public RtObject
{
	RT_CLASS_DEFINE(LootSaveData, RtObject, RtClass);
public:
	LootSaveData() 
	{
		ProfileIndex = 0;
	}

	// Don't hold onto pointers returned by this function.
	LootEntrySaveData* GetLootEntryData(const std::string& i_uniqueId);
	int32_t ProfileIndex;

private:
	std::vector<LootEntrySaveData> m_lootEntryInstancedData;
};

class Collectable;
namespace LootHelpers
{
    extern LootTable* gDownloadedLootTable;

	Collectable* Drop(Loot i_loot, const SexyVector3 &i_position);
	int LootToCoinValue(Loot i_loot);

	void GenerateLootForLevel(const std::string& i_levelName, double i_levelLength, std::vector<Loot> &o_loot);
}

#endif
