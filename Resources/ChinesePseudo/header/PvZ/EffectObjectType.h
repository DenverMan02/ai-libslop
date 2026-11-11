//
//  GridItemType.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 6/8/2012.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __EFFECTOBJECTITEMTYPE_H__
#define __EFFECTOBJECTITEMTYPE_H__

#include <set>
#include <string>
#include <vector>

#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"

class EffectObjectPropertySheet;

typedef RtWeakPtr<const EffectObjectPropertySheet> EffectObjectPropsPtr;

class EffectObjectType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(EffectObjectType, ObjectTypeDescriptor, RtClass);
	
	// Default values
	EffectObjectType()
	{
	}
	
	std::string					EffectObjectClass;
	std::vector<std::string>	ResourceGroups;
	EffectObjectPropsPtr		Properties;
	
	void AddResourceRequirements(std::set<std::string>& io_resourceGroups) const;
	
	EffectObjectPropsPtr					GetPropsPtr() const;
	const class EffectObjectPropertySheet*	GetProps() const;
};

#endif
