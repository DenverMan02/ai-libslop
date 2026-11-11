//
//  CollectableArenaZombie.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-10-27.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CollectableArenaZombie__
#define __PlantsVersusZombies2__CollectableArenaZombie__

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

class CollectableArenaZombie : public Collectable
{
public:
    RT_CLASS_DEFINE(CollectableArenaZombie, Collectable, RtClass);
    
    void SetZombieSeedType(ZombieTypePtr i_zombieType);
    
    CollectableArenaZombie();
    
    int CalcRenderOrder() const override;
    
    void PrepareMoving();
    
protected:
    void onDraw(class Sexy::Graphics* i_g) override;
    void onDestroy() override;
    
    void registerForEvents() override;
    bool onTouchEvent(const Sexy::Touch& i_touch) override;
    
    virtual bool drawCost();
    
    //void onCursorDestroyed(BaseCursor* i_cursor);
    
    virtual void drawToBuffer();
    virtual void onFinishMotion() override;
    virtual void onUpdate() override;
    virtual void StartMoving();
    
    ZombieTypePtr m_seedZombieType;
    //Point         m_targetGrid;
    DeviceImage*  m_seedPacketImage = NULL;
    
private:
    
    pvztime_t   m_startMovingTime;
    
    bool        m_enableMove;
    
    // Not serialized
    //PlantCursor * m_plantCursor;
    //ZombieCursor* m_zombieCursor;
    //bool          m_IsSelect;
};

//namespace Message
//{
//    void CollectableSeedRainFinished(CollectableSeedRain * i_collectable);
//}

#endif /* defined(__PlantsVersusZombies2__CollectableArenaZombie__) */
