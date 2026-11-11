//
//  ShovelCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ShovelCursor__
#define __PlantsVersusZombies2__ShovelCursor__

#include "BaseCursor.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
struct Touch;
}  // namespace Sexy

class ShovelCursor : public BaseCursor
{
public:
	RT_CLASS_DEFINE(ShovelCursor, BaseCursor, RtClass) {}

	ShovelCursor() {}
	ShovelCursor(const Sexy::Touch& i_boardSpaceTouch);

protected:
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void onDraw(Sexy::Graphics* i_g) override;
	virtual void doShovelEntity(BoardEntity* i_entity);
	virtual bool CanShovelPlant(int i_x, int i_y);

private:
	bool tryToShovelPlant();
	bool tryToShovelGridItem();
	void shovelEntity(BoardEntity* i_entity, int i_gridX, int i_gridY);

private:
	bool m_continueoperation;
};

namespace Message
{
	void PlantShoveled(class Plant* i_plant);
	void SunProducedByShovel(int i_amount);
}

#endif /* defined(__PlantsVersusZombies2__ShovelCursor__) */
