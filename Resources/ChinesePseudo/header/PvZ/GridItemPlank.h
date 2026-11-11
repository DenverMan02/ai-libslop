//
//  GridItemPlank.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/13/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMPLANK_H__
#define __GRIDITEMPLANK_H__

#include "Precompile.h"
#include "GridItem.h"

namespace Sexy { class Graphics; }

class GridItemPlank : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemPlank, GridItem, RtClass);

	GridItemPlank() {}
	virtual ~GridItemPlank() {}
	void AddToRenderQueue(RenderQueue* i_queue) override;
	
protected:
	virtual void onDraw(Sexy::Graphics* i_g) override;
	virtual void onDrawShadow(class Sexy::Graphics* i_g) override;

	virtual int CalcRenderOrder() const override;
};

#endif
