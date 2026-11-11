//
//  CollectableSeedRain.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-4-14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectableSeedRain__
#define __PlantsVersusZombies2__CollectableSeedRain__

#include <cstddef>
#include <string>

#include "Collectable.h"
#include "CollectableType.h"
#include "PVZTypes.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"

class BaseCursor;
class PlantCursor;
class ZombieCursor;

class CollectableSeedRain : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableSeedRain, Collectable, RtClass);
    
    void SetPlantFoodType(bool i_plantFoodType);
	void SetPlantSeedType(const std::string& i_seedType);
	void SetZombieSeedType(const std::string& i_seedType);
    void SetTargetGrid(Point i_grid);
    Point GetTargetGrid() const;
    
    bool GetIsSelect();
    
	CollectableSeedRain();

#ifdef HOST_ANDROID
	void Android_OnAppResumeFocus();
#endif
    
	int CalcRenderOrder() const override;
    
protected:
	void onDraw(class Sexy::Graphics* i_g) override;
	void onDestroy() override;
    
    void registerForEvents() override;
    bool onTouchEvent(const Sexy::Touch& i_touch) override;
	
	virtual bool drawCost();
    
    void onCursorDestroyed(BaseCursor* i_cursor);
	
	void drawToBuffer();
    
    bool          m_PlantFoodType;
	PlantTypePtr  m_seedPlantType;
    ZombieTypePtr m_seedZombieType;
    Point         m_targetGrid;
	DeviceImage*  m_seedPacketImage = NULL;
    
private:
    
	// Not serialized
	PlantCursor * m_plantCursor;
    ZombieCursor* m_zombieCursor;
    bool          m_IsSelect;
};

namespace Message
{
	void CollectableSeedRainFinished(CollectableSeedRain * i_collectable);
}

#endif /* defined(__PlantsVersusZombies2__CollectableSeedRain__) */
