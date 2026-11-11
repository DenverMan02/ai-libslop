//
//  CreatureType.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __CREATURETYPE_H__
#define __CREATURETYPE_H__

#include <set>
#include <string>
#include <vector>

#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"
#include "CreaturePropertySheet.h"

typedef RtWeakPtr<const CreaturePropertySheet> CreaturePropsPtr;
typedef RtWeakPtr<class Creature> CreaturePtr;

class CreatureType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(CreatureType, ObjectTypeDescriptor, RtClass);

	// Default values
	CreatureType()
	{
	}

	std::string							CreatureClass;
	
	std::string							HomeWorld;
	std::string							DisplayTypeName; // For zombies that have multiple types but need a single user-facing display type.
	std::string							AlmanacBackdropName;

	const CreatureType *GetDisplayType() const;
	std::string GetAlmanacBackdropName() const;

	const std::vector<std::string>& GetNonAudioResourceGroups(void) const { return ResourceGroups; }

private:

	std::string							PopAnim;
	std::string							AnimRigClass;
	std::vector<std::string>			ResourceGroups;
	std::vector<std::string>			AudioGroups;

public:

	CreaturePropsPtr					Properties;

	void								AddInGameResourceRequirements(std::set<std::string>& io_resourceGroups) const;
	const std::vector<std::string>&		GetArtResourceGroups() const;
	const std::vector<std::string>&		GetAudioGroups() const;

	CreaturePropsPtr					GetPropsPtr() const;
	const class CreaturePropertySheet*	GetProps() const;

	const std::string&					GetPopAnimName() const;
	const std::string&					GetPopAnimRigClassName() const;
	
	class CreatureAnimRig*				CreateAnimRig() const;

	void								EnsureResourceGroupsLoaded() const;
	const bool							IsCreatureEnabled() const;
	
	
	SexyString GetFormattedNameString() const;
	SexyString GetFormattedToolTip() const;
	SexyString GetFormattedDescription() const;
	SexyString GetFormattedDescriptionHeader() const;
};


#endif // __CREATURETYPE_H__
