/*
 * PlantAccessoryPropertySheet.h
 *
 *  Created on: 2015-1-7
 *      Author: jianglc
 */

#ifndef PLANTACCESSORYPROPERTYSHEET_H_
#define PLANTACCESSORYPROPERTYSHEET_H_

#include "PropertySheetBase.h"
#include "RtObject.h"
#include "PlantBoostPropertySheet.h"

typedef RtWeakPtr<class PlantAccessoryPropertySheet> PlantAccessoryPropertySheetPtr;

struct AccessoryAvatarInfo
{
	AccessoryAvatarInfo()
	{
		ResGroupName = "";
		ImageName = "";
	}

	std::string ResGroupName;
	std::string ImageName;
};

enum AccessoryQuality
{
    QUALITY_NORMAL,
    QUALITY_MAGIC,
    QUALITY_EPIC,
    QUALITY_UNIQUE,
    QUALITY_LEGEND,
	QUALITY_SUPER,
};

struct SteadyMaterial
{
	int Id;
	int Num;
};

struct SteadyNeed
{
	int CurrentLevel;
	std::vector<SteadyMaterial> Require;
	std::string NewLevelBoostDes;
};

class PlantAccessoryPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantAccessoryPropertySheet, PropertySheetBase, RtClass);

	PlantAccessoryPropertySheet()
	{
		Name = "";
		Description = "";
		BoostDescription = "";
		DisplayImage = "";
		MinEnabledLevel = 0;
		RequiredPieces = 0;
		PurchasePrice = 0;
		Quality = QUALITY_NORMAL;
		SalePrice = 0;
        ObjectTypeId = 0;
		SteadyList.clear();
		MaxLevel = 0;
	}

	// For name display
	std::string Name;
	// For plain description
	std::string Description;
	// For boost description
	std::string BoostDescription;
	// For display in UI
	std::string DisplayImage;
	// For avatar display res group name
	//std::string ResGroupName;
	AccessoryAvatarInfo AvatarInfo;
	// For plant restrictions
	std::vector<std::string> DisabledPlants;
	// For level restrictions
	int MinEnabledLevel;
	// For boosts
	std::vector<PlantBoost> Boosts;
	// Required pieces
	int RequiredPieces;
	// Purchase price
	int PurchasePrice;
	// Quality
	AccessoryQuality Quality;
	// Sale price
	int SalePrice;
    // ObjectId
    int ObjectTypeId;
	// Super Accessory Max Level
	int MaxLevel;
	// Steady material
	std::vector<SteadyNeed> SteadyList;
	// Super accessory boost list
	std::vector<std::vector<PlantBoost>> SuperBoostList;
};


#endif /* PLANTACCESSORYPROPERTYSHEET_H_ */
