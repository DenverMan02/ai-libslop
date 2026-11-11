//
//  HotUITableViewCell.h
//  PlantsVersusZombies2
//
//  Created by Matthew Fairfax on 11/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUITableViewCell__
#define __PlantsVersusZombies2__HotUITableViewCell__

#include "HotUIButton.h"

typedef RtWeakPtr<class HotUITableViewCell> HotUITableViewCellPtr;

class HotUITableViewCell : public HotUIButton
{
public:
	
	RT_CLASS_DEFINE(HotUITableViewCell, HotUIButton, RtClass);
	
	HotUITableViewCell();
	virtual ~HotUITableViewCell();
	
	bool CalculateAnchorLocation() override;
};

class HotUITableViewCellProperties : public HotUIButtonProperties
{
public:
	RT_CLASS_DEFINE(HotUITableViewCellProperties, HotUIButtonProperties, RtClass);
	
	HotUITableViewCellProperties()
	{}
	
	RtClass* GetWidgetClass() const override
	{
		return HotUITableViewCell::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__HotUITableViewCell__) */
