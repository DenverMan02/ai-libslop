//
//  GridItemLinkedPlantShield.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/15/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemLinkedPlantShield_h
#define PlantsVersusZombies2_GridItemLinkedPlantShield_h

#include <vector>

#include "DamageInfo.h"
#include "GridItemPlantShield.h"
#include "RtDb.h"
#include "RtObject.h"

class GridItemLinkedPlantShield : public GridItemPlantShield
{
public:
	RT_CLASS_DEFINE(GridItemLinkedPlantShield, GridItemPlantShield, RtClass);
	
	// Associates all plant shields in the set with each other
	static void SetPlantShieldGroup(const std::vector<GridItemLinkedPlantShield*>& i_group);

protected:
	void setPartners(const std::vector<GridItemLinkedPlantShield*>& i_partners);
	
	virtual void onGridItemInitialize() override;
    virtual void onTakeDamage(const DamageInfo& i_damage) override;

private:
	std::vector<RtWeakPtr<GridItemLinkedPlantShield> > m_partners;
};

#endif
