//
//  ProbabilityTypeContainer.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 1/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#include "ObjectTypeDescriptor.h"

#ifndef PlantsVersusZombies2_ProbabilityTypeContainer_h
#define PlantsVersusZombies2_ProbabilityTypeContainer_h

//
// Serializable ProbabilitySet
//
// Use to add a weighted set of type (string) elements in other configurable classes.
//
// Similar to ProbabilitySet, but simpler in scope and meant mainly for configurable
// JSON elements.  Terry will no doubt see this and be sad, but we decided not to
// try and wrangle ProbabilitySet into something serializable.
//

struct ProbabilityTypeRecord : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(ProbabilityTypeRecord, ObjectTypeDescriptor, RtClass);
    ProbabilityTypeRecord();
	std::string		TypeName;
	int				Weight;
    int             Level;
};

class ProbabilityTypeContainer : ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(ProbabilityTypeContainer, ObjectTypeDescriptor, RtClass);
	
	const ProbabilityTypeRecord& PickItem() const
	{
		int totalWeight = calculateTotalWeight();
		
		int pick = RandRangeInt(0, totalWeight - 1);
		int acculumatedWeight = 0;
		
		for (size_t i = 0; i < Entries.size(); i++)
		{
			acculumatedWeight += Entries[i].Weight;
			
			if (pick < acculumatedWeight)
			{
				return Entries[i];
			}
		}
		
		DBG_ASSERT(false);
		return Entries[0];
	}
	
	const ProbabilityTypeRecord& PickItem(class MTRand* i_rand) const
	{
		int totalWeight = calculateTotalWeight();

		int pick = RandRangeInt(0, totalWeight - 1, i_rand);
		int acculumatedWeight = 0;

		for (size_t i = 0; i < Entries.size(); i++)
		{
			acculumatedWeight += Entries[i].Weight;

			if (pick < acculumatedWeight)
			{
				return Entries[i];
			}
		}

		DBG_ASSERT(false);
		return Entries[0];
	}

	const std::vector<ProbabilityTypeRecord>& GetEntries() const { return Entries; }
	
private:
	int calculateTotalWeight() const
	{
		int totalWeight = 0;
		
		for (auto record : Entries)
		{
			totalWeight += record.Weight;
		}
		
		return totalWeight;
	}
	
	std::vector<ProbabilityTypeRecord> Entries;
};



#endif
