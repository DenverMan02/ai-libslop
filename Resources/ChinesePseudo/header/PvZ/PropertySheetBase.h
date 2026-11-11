//
//  PropertySheetBase.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PROPERTYSHEETBASE_H__
#define __PROPERTYSHEETBASE_H__

#include <set>
#include <string>

#include "GameObject.h"
#include "RtDb.h"
#include "RtObject.h"

class PropertySheetBase : public GameObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(PropertySheetBase, GameObject, RtClass);

	// As of today, there is no unified system for loading resource groups from PropertySheets.
	// It's up to each individual system that uses PropertySheet objects to gather and load
	// resource groups from each PropertySheet in its list.
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const
	{}
	
protected:
	PropertySheetBase()
	{}
};

typedef RtWeakPtr<PropertySheetBase> PropertySheetPtr;

#endif // __PROPERTYSHEETBASE_H__
