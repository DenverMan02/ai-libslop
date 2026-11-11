//
//  ZombieType.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIETYPE_H__
#define __ZOMBIETYPE_H__

#include "Precompile.h"
#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"
#include "ZombiePropertySheet.h"

typedef RtWeakPtr<const ZombiePropertySheet> ZombiePropsPtr;

enum ZombieResistenceRank
{
	ZombieResistenceRank_D,
	ZombieResistenceRank_C,
	ZombieResistenceRank_B,
	ZombieResistenceRank_A,
	ZombieResistenceRank_S,
	ZombieResistenceRank_SS
};

class ZombieResistenceConfig : public ObjectTypeDescriptor
{
public:
	static const ZombieResistenceConfig* GetConfig();

public:
	RT_CLASS_DEFINE(ZombieResistenceConfig, ObjectTypeDescriptor, RtClass);

	struct ResistenceValueInfo
	{
		ResistenceValueInfo()
		: MinValue(0.0f)
		, MaxValue(0.0f)
		{

		}

		float MinValue;
		float MaxValue;
	};

	ZombieResistenceConfig()
	{

	}

public:
	std::vector<ResistenceValueInfo> ResistenceValueInfos;

};

class ZombieType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(ZombieType, ObjectTypeDescriptor, RtClass);
	
	// Default values
	ZombieType()
	{
        Enabled       = true;
		Placeable     = true;
        IsBasicZombie = false;
        IsFlagZombie = false;
        BoardAlmanac  = false;
	}
    
    std::string		ZombieClass;
    std::string		HomeWorld;
    std::string		DisplayTypeName; // For zombies that have multiple types but need a single user-facing display type.
    
    bool                        Enabled;
    bool                        BoardAlmanac;
    std::vector<std::string>    RecommendPlants;
    
    std::vector<float> Resistences;

    const ZombieType *GetDisplayType() const;
    
    const std::vector<std::string>& GetNonAudioResourceGroups(void) const { return ResourceGroups; }
    
private:
	
	std::string                 PopAnim;
	std::string                 AnimRigClass;
	std::vector<std::string>	ResourceGroups;
	std::vector<std::string>	AudioGroups;    
public:    
	
	ZombiePropsPtr 	Properties;
	bool			Placeable;
    bool								IsBasicZombie;
    bool								IsFlagZombie;
    void                                AddInGameResourceRequirements(std::set<std::string>& io_resourceGroups) const;
    const std::vector<std::string>&		GetArtResourceGroups() const;
    const std::vector<std::string>&		GetAudioGroups() const;
	
	ZombiePropsPtr                      GetPropsPtr() const;
	const class ZombiePropertySheet*    GetProps() const;
    
    const std::string&                  GetPopAnimName() const;
	const std::string&                  GetPopAnimRigClassName() const;

	class ZombieAnimRig*				CreateAnimRig() const;
    
    virtual int GetCost() const;
    virtual int GetCostBrain() const;
    float GetPacketCoolDown() const;
    void								EnsureResourceGroupsLoaded() const;
};

namespace Sexy
{
	enum ZombieFlagType
	{
		ZOMBIEFLAGTYPE_NOFLAG,
		ZOMBIEFLAGTYPE_FLAG_NORMAL,
		ZOMBIEFLAGTYPE_FLAG_VETERAN
	};
}

class BasicZombieWeights : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(BasicZombieWeights, ObjectTypeDescriptor, RtClass);
	
	BasicZombieWeights()
	{
		ZombieTypeName = "";
		Weight = 0;
	}
	
	std::string ZombieTypeName;
	int Weight;
};

#endif // __ZOMBIETYPE_H__
