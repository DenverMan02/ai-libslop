//
//  ArmorPropertySheet.hpp
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alexander on 12/19/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ArmorPropertySheet_hpp
#define ArmorPropertySheet_hpp

#include <string>
#include <vector>
#include <map>

#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "Utils.h"
#include "ZombieEnums.h"

typedef std::map<std::string, std::vector<std::string> > ToggleMap;

class ArmorPropertySheetUtils : public PropertySheetBase
{
	RT_CLASS_DEFINE(ArmorPropertySheetUtils, PropertySheetBase, RtClass);
	
	ArmorPropertySheetUtils()
	{
		ToggleLayers = {};
	}
	
	ToggleMap ToggleLayers;
	
	static const std::vector<std::string> GetToggleLayers(const std::string& i_zombieType);
};

typedef RtWeakPtr<class ArmorPropertySheet> ArmorPropertySheetPtr;

class ArmorPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ArmorPropertySheet, PropertySheetBase, RtClass);
	
	ArmorPropertySheet()
	{
		ClassName = "Armor";
		ArmorType = "Unknown";
		
		BaseHealth = 0.0f;
		
		ArmorFlags = ARMOR_None;
		
		ArmorLayers = {};
		ArmorLayerHealth = {};
		
		ParticleLayerOverride = {};
		
		ImpactSoundEvent = "";
		DropSoundEvent = "";
	}
	
	// The Armor class to instantiate.
	std::string ClassName;
	
	std::string ArmorType;
	
	// Baseline amount of health
	float BaseHealth;
	
	// Flags for our armor
	ArmorTypeFlags ArmorFlags;
	
	std::vector<std::string> ArmorLayers;
	std::vector<float> ArmorLayerHealth;
	
	std::vector<std::string> ParticleLayerOverride;
	
	std::string ImpactSoundEvent;
	std::string DropSoundEvent;
	
	// this is only called once after the JSON file have been loaded into the tables
	bool Serialize(const RtSerializeContext& inContext) override;
	
private:
	void postLoadFixup();
	
	std::vector<ArmorTypeFlags> JSONArmorFlags;
};

class NewspaperArmorPropertySheet : public ArmorPropertySheet
{
public:
	RT_CLASS_DEFINE(NewspaperArmorPropertySheet, ArmorPropertySheet, RtClass);
	
	NewspaperArmorPropertySheet()
	{
		FireLayer = "";
	}
	
	std::string FireLayer;
};

class CoalCartDefaultPropertySheet : public ArmorPropertySheet
{
public:
	RT_CLASS_DEFINE(CoalCartDefaultPropertySheet, ArmorPropertySheet, RtClass);

	CoalCartDefaultPropertySheet()
	{
	}

	std::string AshSoundEvent;
};

#endif /* ArmorPropertySheet_hpp */
