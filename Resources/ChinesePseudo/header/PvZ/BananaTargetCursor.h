//
//  BananaTargetCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BananaTargetCursor__
#define __PlantsVersusZombies2__BananaTargetCursor__

#include "BaseCursor.h"
#include "RtDb.h"
#include "Plant_Banana.h"

class BananaTargetCursor : public BaseCursor
{
public:
    RT_CLASS_DEFINE(BananaTargetCursor, BaseCursor, Sexy::RtClass) {}
    
    BananaTargetCursor() {}
    explicit BananaTargetCursor(const Sexy::Touch& i_boardSpaceTouch, PlantBanana* i_bananaPlant);
    virtual ~BananaTargetCursor();
    
    const PlantBanana* GetBananaPlant() const { return m_bananaPlant; }
    
protected:
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
    
private:
    void onPlantDied(Plant* i_plant);
    
    Sexy::SexyVector2 m_cursorOffset;
    PlantBanana* m_bananaPlant = nullptr;
};

#endif /* defined(__PlantsVersusZombies2__BananaTargetCursor__) */
