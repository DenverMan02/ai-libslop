//
//  PVZTypes.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PVZTYPES_H__
#define __PVZTYPES_H__

#include "core.h"
#include "Precompile.h"
#include "RtObject.h"
#include "ObjectTypeDirectory.h"

class CollectableType;
class CreatureType;
class GameFeatureType;
class GridItemType;
class EffectObjectType;
class PlantType;
class PlantLevelStats;
class PlantPropertySheet;
class PowerPropertySheet;
class PowerupType;
class PresentTable;
class PresentType;
class PrimeText_PotentialTypeface;
class PrimeText_PotentialTypeface_Alias;
class HotUIColor;
class HotUIColorAlias;
class ToolPacketProps;
class ZombieType;
class BonusType;
class HotUIColor;
class HotUIColorAlias;
class LevelScoringRules;

enum BoardEntityTypeFlag
{
	PVZ_BEGIN_FLAG_ENUM(ENTITYTYPE_),
	PVZ_FLAG(ENTITYTYPE_PLANT),
	PVZ_FLAG(ENTITYTYPE_ZOMBIE),
	PVZ_FLAG(ENTITYTYPE_GRIDITEM),
    PVZ_FLAG(ENTITYTYPE_CREATURE),
    PVZ_FLAG(ENTITYTYPE_PLANTGROUP),
    PVZ_FLAG(ENTITYTYPE_OTHERBOARDENTITIES),
	PVZ_END_FLAG_ENUM(ENTITYTYPE_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(BoardEntityTypeFlag);

#define gPlantTypeMgr (ObjectTypeDirectory<PlantType>::GetInstancePtr())
typedef ObjectTypeDirectory<PlantType>::Iterator				PlantTypeIter;
typedef ObjectTypeDirectory<PlantType>::ObjectTypePtr 			PlantTypePtr;

#define gPowersMgr (ObjectTypeDirectory<PowerPropertySheet>::GetInstancePtr())
typedef ObjectTypeDirectory<PowerPropertySheet>::Iterator			PowersIter;
typedef ObjectTypeDirectory<PowerPropertySheet>::ObjectTypePtr 		PowersPtr;

#define gZombieTypeMgr (ObjectTypeDirectory<ZombieType>::GetInstancePtr())
typedef ObjectTypeDirectory<ZombieType>::Iterator				ZombieTypeIter;
typedef ObjectTypeDirectory<ZombieType>::ObjectTypePtr 			ZombieTypePtr;

#define gGridItemTypeMgr (ObjectTypeDirectory<GridItemType>::GetInstancePtr())
typedef ObjectTypeDirectory<GridItemType>::Iterator				GridItemTypeIter;
typedef ObjectTypeDirectory<GridItemType>::ObjectTypePtr		GridItemTypePtr;

#define gCreatureTypeMgr (ObjectTypeDirectory<CreatureType>::GetInstancePtr())
typedef ObjectTypeDirectory<CreatureType>::Iterator				CreatureTypeIter;
typedef ObjectTypeDirectory<CreatureType>::ObjectTypePtr		CreatureTypePtr;

#define gEffectObjectTypeMgr (ObjectTypeDirectory<EffectObjectType>::GetInstancePtr())
typedef ObjectTypeDirectory<EffectObjectType>::Iterator				EffectObjectTypeIter;
typedef ObjectTypeDirectory<EffectObjectType>::ObjectTypePtr		EffectObjectTypePtr;

#define gCollectableTypeMgr (ObjectTypeDirectory<CollectableType>::GetInstancePtr())
typedef ObjectTypeDirectory<CollectableType>::Iterator			CollectableTypeIter;
typedef ObjectTypeDirectory<CollectableType>::ObjectTypePtr		CollectableTypePtr;

#define gPresentTableMgr (ObjectTypeDirectory<PresentTable>::GetInstancePtr())
typedef ObjectTypeDirectory<PresentTable>::Iterator				PresentTableIter;
typedef ObjectTypeDirectory<PresentTable>::ObjectTypePtr		PresentTablePtr;

#define gPresentTypeMgr (ObjectTypeDirectory<PresentType>::GetInstancePtr())
typedef ObjectTypeDirectory<PresentType>::Iterator				PresentTypeIter;
typedef ObjectTypeDirectory<PresentType>::ObjectTypePtr			PresentTypePtr;

#define gPowerupTypeMgr (ObjectTypeDirectory<PowerupType>::GetInstancePtr())
typedef ObjectTypeDirectory<PowerupType>::Iterator				PowerupTableIter;
typedef ObjectTypeDirectory<PowerupType>::ObjectTypePtr			PowerupTablePtr;

#define gGameFeatureTypeMgr (ObjectTypeDirectory<GameFeatureType>::GetInstancePtr())
typedef ObjectTypeDirectory<GameFeatureType>::Iterator				GameFeatureTableIter;
typedef ObjectTypeDirectory<GameFeatureType>::ObjectTypePtr		GameFeatureTablePtr;

#define gPotentialTypefaceTypeMgr (ObjectTypeDirectory<PrimeText_PotentialTypeface>::GetInstancePtr())
typedef ObjectTypeDirectory<PrimeText_PotentialTypeface>::Iterator			PotentialTypefaceIter;
typedef ObjectTypeDirectory<PrimeText_PotentialTypeface>::ObjectTypePtr		PotentialTypefacePtr;

#define gPotentialTypefaceAliasTypeMgr (ObjectTypeDirectory<PrimeText_PotentialTypeface_Alias>::GetInstancePtr())
typedef ObjectTypeDirectory<PrimeText_PotentialTypeface_Alias>::Iterator			PotentialTypefaceAliasIter;
typedef ObjectTypeDirectory<PrimeText_PotentialTypeface_Alias>::ObjectTypePtr		PotentialTypefaceAliasPtr;

#define gHotUIColorMgr (ObjectTypeDirectory<HotUIColor>::GetInstancePtr())
typedef ObjectTypeDirectory<HotUIColor>::Iterator			HotUIColorIter;
typedef ObjectTypeDirectory<HotUIColor>::ObjectTypePtr		HotUIColorPtr;

#define gHotUIColorAliasMgr (ObjectTypeDirectory<HotUIColorAlias>::GetInstancePtr())
typedef ObjectTypeDirectory<HotUIColorAlias>::Iterator			HotUIColorAliasIter;
typedef ObjectTypeDirectory<HotUIColorAlias>::ObjectTypePtr		HotUIColorAliasPtr;

#define gLevelScoringRules (ObjectTypeDirectory<LevelScoringRules>::GetInstancePtr())
typedef ObjectTypeDirectory<LevelScoringRules>::Iterator			LevelScoringRulesTableIter;
typedef ObjectTypeDirectory<LevelScoringRules>::ObjectTypePtr		LevelScoringRulesTablePtr;

//PVZ2_CHINESE_BEGIN
#define gBonusTypeMgr (ObjectTypeDirectory<BonusType>::GetInstancePtr())
typedef ObjectTypeDirectory<BonusType>::Iterator				BonusTableIter;
typedef ObjectTypeDirectory<BonusType>::ObjectTypePtr           BonusTablePtr;
//PVZ2_CHINESE_END

// We can go negative, even if only for a second...
typedef int32													SunCurrency;
// We can go negative, even if only for a second...
typedef int32													CoinCurrency;
typedef int32													GemCurrency;	//PVZ2_CHINESE_START
typedef int32                                                   StoneCurrency;
typedef int32                                                   RedPacketCurrency;
// We can go negative for a delta.
typedef int32													StarCurrency;
typedef int32													KeyCurrency;
typedef int32                                                   LeafCurrency;
typedef int32													StaminaCurrency;
typedef int32													AvatarPiecesCurrency;
typedef int32													PennyFuelCurrency;
typedef int32													ZombossSignalCurrency;
typedef int32													PennyTechCurrency;

class PVZTypes : public RtObject
{
public:
	RT_CLASS_DEFINE(PVZTypes, RtObject, RtClass);
    static bool VerifyPlantTypes();
    static bool VerifyZombieTypes();
    static bool VerifyCreatureTypes();
    static bool VerifyProjectileTypes();
    static bool VerifyWorldMapAndLevels();
};

#endif // __PVZTYPES_H__
