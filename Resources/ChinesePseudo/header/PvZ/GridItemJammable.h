//
//  GridItemJammable.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 8/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemJammable__
#define __PlantsVersusZombies2__GridItemJammable__

#include <stdio.h>
#include "GridItemBoardEntityConditionTarget.h"

class GridItemJammable : public GridItemBoardEntityConditionTarget
{
public:
	RT_CLASS_DEFINE(GridItemJammable, GridItemBoardEntityConditionTarget, RtClass);
	
	GridItemJammable();
	virtual ~GridItemJammable();
	
	void onGridItemInitialize() override;
	
	virtual void StartJamming();
	virtual void StopJamming();
	virtual std::string GetJamStyle();
	void SetJamStyle(const std::string& style);
	virtual bool IsJamming();
	
private:
	bool m_isMyJamOn;
	std::string m_jamStyle;
};

namespace Message
{
	void JammableGridItemAddedToBoard(GridItemJammable *item);
}

#endif /* defined(__PlantsVersusZombies2__GridItemJammable__) */
