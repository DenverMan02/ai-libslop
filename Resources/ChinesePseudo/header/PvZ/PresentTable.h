//
//  PresentTable.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PresentTable_h
#define PlantsVersusZombies2_PresentTable_h

#include "RtObject.h"
#include "RtDb.h"
#include "ObjectTypeDescriptor.h"

typedef Sexy::RtWeakPtr<const class PresentTable> PresentTablePtr;

struct PresentTableEntry
{
	PresentTableEntry()
	{
		Weight = 1;
	}
	
	std::string PresentType;
	int			Weight;
};

class PresentTable : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PresentTable, ObjectTypeDescriptor, Sexy::RtClass);
	
	PresentTable()
	{
		Shiny = false;
	}
	
	std::string Roll(uint32 i_randomSeed) const;
	
	bool Shiny;
	std::vector<PresentTableEntry> Entries;
};

#endif
