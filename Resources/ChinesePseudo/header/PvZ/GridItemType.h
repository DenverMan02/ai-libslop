//
//  GridItemType.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/8/2012.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMTYPE_H__
#define __GRIDITEMTYPE_H__

#include "Precompile.h"
#include "ObjectTypeDescriptor.h"
#include "GridItemPropertySheet.h"

typedef RtWeakPtr<const GridItemPropertySheet> GridItemPropsPtr;

class GridItemType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(GridItemType, ObjectTypeDescriptor, RtClass);
	
	// Default values
	GridItemType()
	{
	}
	
	std::string                 GridItemClass;
    std::vector<std::string>	ResourceGroups;
	GridItemPropsPtr            Properties;
    
    void AddResourceRequirements(std::set<std::string>& io_resourceGroups) const;
    const std::vector<std::string>& GetNonAudioResourceGroups(void) const { return ResourceGroups; }
	
	GridItemPropsPtr GetPropsPtr() const;
	const class GridItemPropertySheet* GetProps() const;
};

class EntityWeight : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(EntityWeight, ObjectTypeDescriptor, RtClass);
    
    EntityWeight()
    {
        EntityName = "";
        Weight = 0;
    }
    
    std::string EntityName;
    int Weight;
};


#endif // __ZOMBIETYPE_H__
