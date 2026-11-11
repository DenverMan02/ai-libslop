//
//  GridItemRailcart.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/13/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMRAILCART_H__
#define __GRIDITEMRAILCART_H__

#include "Precompile.h"
#include "GridItem.h"

class GridItemRailcart : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemRailcart, GridItem, RtClass);

	GridItemRailcart();
	virtual ~GridItemRailcart();
    
	int CalcRenderOrder() const override;
    
    static bool IsAStationaryPlantfoodPlant(const std::string i_plantName);
	static bool IsAStationaryPlant(const std::string i_plantName);
	static bool IsAStationaryGridItem(const std::string& i_gridItemName);

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
	virtual void onDraw(class Graphics* i_g) override;
    virtual void onGridItemInitialize() override;
    
private:
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();
	void handleCartMoving(const Sexy::Touch& i_touch);
    void parseCartImage();

	Sexy::TouchID m_owningTouchIdent;
    ImagePtr	  m_cartImage;
};

namespace Message
{
	void RailcartMoved(GridItemRailcart* i_railcart);
}

#endif
