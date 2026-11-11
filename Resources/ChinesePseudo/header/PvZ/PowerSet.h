//
//  PowerSet.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 3/14/16.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __POWERSET_H__
#define __POWERSET_H__

#include "PowerPropertySheet.h"

enum PowerType
{
	POWER_INVALID,
	POWER_SUNPRODUCER,
	POWER_WARMING,
	POWER_DUPLICATOR,
	POWER_SHIELD,
	POWER_DAMAGERADIUS,
	
	POWER_SUNSHROOM_GROWTH,
	POWER_REDSTINGER_LOCATIONDATA,
	POWER_STRAWBURST_GROWTH,

	POWER_AVATAR_SHIELD,
	POWER_AVATAR_DAMAGERADIUS,

	POWER_GENE_SHIELD,
};

enum PowerContext
{
	POWER_CONTEXT_NORMAL,
	POWER_CONTEXT_PLANTFOOD,
	POWER_CONTEXT_PHATBEET_POWERFUL,
    POWER_CONTEXT_PHATBEET_POWERFULLV3,
	POWER_CONTEXT_PHATBEET_OUTER_PF,
	POWER_CONTEXT_ESCAPEROOT_POTATOMINE,
	POWER_CONTEXT_ESCAPEROOT_PRIMALPOTATOMINE,
	POWER_CONTEXT_ESCAPEROOT_CHERRYBOMB,
	POWER_CONTEXT_ESCAPEROOT_GRAPESHOT,
	POWER_CONTEXT_HAPPYLEEK_YOUNG,
	POWER_CONTEXT_HAPPYLEEK_OLD
};

struct PowerNode
{
	PowerNode()
	{
		Type = POWER_INVALID;
		Context = POWER_CONTEXT_NORMAL;
	}
	
	PowerType		Type;
	PowerContext	Context;
	std::string		Props;
	RtWeakPtr<PowerPropertySheet>	PropsPtr;
};

class PowerSet
{
public:
	const RtWeakPtr<PowerPropertySheet> Find(PowerType i_type);
	const RtWeakPtr<PowerPropertySheet> Find(PowerType i_type, PowerContext i_context);
	
	std::vector<PowerNode>	Powers;
	
private:
	void updateNode(PowerNode& i_node);
};

#endif
