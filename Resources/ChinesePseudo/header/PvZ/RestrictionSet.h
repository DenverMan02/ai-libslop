//
//  RestrictionSet.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 10/31/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RestrictionSet__
#define __PlantsVersusZombies2__RestrictionSet__

#include "RtObject.h"
#include "BoardEnums.h"
#include "PVZTypes.h"
#include <string>
#include <vector>

class GridItem;
class Plant;
class PlantType;
class Zombie;

enum RestrictionSetType
{
	Blacklist,
	Whitelist,
};

// A blacklist or whitelist, you choose.
// An empty blacklist allows everything.  An empty whitelist allows nothing.
class StringRestrictionSet : public RtObject
{
public:
	RT_CLASS_DEFINE(StringRestrictionSet, RtObject, RtClass);
	
	StringRestrictionSet()
	: ListType{Blacklist}
	{}
	
	RestrictionSetType ListType;
	std::vector<std::string> List;
	
	bool IsIncluded(const std::string& i_item) const;
	bool IsExcluded(const std::string& i_item) const;
};

class PlantRestrictionSet : public StringRestrictionSet
{
public:
	RT_CLASS_DEFINE(PlantRestrictionSet, StringRestrictionSet, RtClass);
	
	using StringRestrictionSet::IsIncluded;
	using StringRestrictionSet::IsExcluded;
	
	bool IsIncluded(const Plant* i_plant) const;
	bool IsExcluded(const Plant* i_plant) const;
	
	bool IsIncluded(PlantTypePtr i_plantType) const;
	bool IsExcluded(PlantTypePtr i_plantType) const;
};

// Special set for specifying planting restritions.  Assumes the values in the set will be plant typenames,
// allows you to specify a PlantingReason to use when planting is blocked, and provides a nice pass-thru
// method for gathering planting restrictions in our usual flow.
//
// A default planting restriction set has no planting restrictions.
//
// If you want to block all planting, change the property sheet to a whitelist with a "block planting" reason,
// and don't whitelist any plants.  You may need to make sure your planting reason is reflected out in RestrictionSet.cpp.
//   "PlantingRestrictions" : {
//     "Type" : "Whitelist",
//     "List" : [ ],
//     "BlockedPlantingReason" : "PLANTING_NOT_ON_RAILS"
//   },
//
// If you want to block planting for certain plants, you can use a more specific blacklist or whitelist by plant typename:
//   "PlantingRestrictions" : {
//     "Type" : "Blacklist",
//     "List" : [ "gravebuster", "hotpotato", "jalapeno", "cherrybomb" ],
//     "BlockedPlantingReason" : "PLANTING_NOT_ON_GRAVESTONES"
//   },
class PlantingRestrictionSet : public PlantRestrictionSet
{
public:
	RT_CLASS_DEFINE(PlantingRestrictionSet, PlantRestrictionSet, RtClass);
	
	PlantingRestrictionSet()
	: BlockedPlantingReason{PLANTING_OK}
	{}
	
	PlantingReason BlockedPlantingReason;
	
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const;
};

class ZombieRestrictionSet : public StringRestrictionSet
{
public:
	RT_CLASS_DEFINE(ZombieRestrictionSet, StringRestrictionSet, RtClass);
	
	using StringRestrictionSet::IsIncluded;
	using StringRestrictionSet::IsExcluded;
	
	bool IsIncluded(const Zombie* i_zombie) const;
	bool IsExcluded(const Zombie* i_zombie) const;
	
	bool IsIncluded(ZombieTypePtr i_zombieType) const;
	bool IsExcluded(ZombieTypePtr i_zombieType) const;
};

class GridItemRestrictionSet : public StringRestrictionSet
{
public:
	RT_CLASS_DEFINE(GridItemRestrictionSet, StringRestrictionSet, RtClass);
	
	using StringRestrictionSet::IsIncluded;
	using StringRestrictionSet::IsExcluded;
	
	bool IsIncluded(const GridItem* i_gridItem) const;
	bool IsExcluded(const GridItem* i_gridItem) const;
	
	bool IsIncluded(GridItemTypePtr i_gridItemType) const;
	bool IsExcluded(GridItemTypePtr i_gridItemType) const;
};

class ClassRestrictionSet : public StringRestrictionSet
{
    public:
    RT_CLASS_DEFINE(ClassRestrictionSet, StringRestrictionSet, RtClass);

    bool IsIncluded(const std::string& i_item) const = delete;
    bool IsExcluded(const std::string& i_item) const = delete;

    bool IsIncluded(const GameObject* i_gameObject) const;
    bool IsExcluded(const GameObject* i_gameObject) const;

    bool IsIncluded(const RtClass* i_class) const;
    bool IsExcluded(const RtClass* i_class) const;
};

#endif /* defined(__PlantsVersusZombies2__RestrictionSet__) */
