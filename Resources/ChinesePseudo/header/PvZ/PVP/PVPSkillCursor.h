//
//  PVPSkillCursor.hp
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15/10/31.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef PVPSkillCursor_h
#define PVPSkillCursor_h

#include "ZombieCursor.h"
#include "PlantFramework.h"

class PVPSkillCursor : public ZombieCursor
{
public:
    RT_CLASS_DEFINE(PVPSkillCursor, ZombieCursor, RtClass) {}
    PVPSkillCursor();
    explicit PVPSkillCursor(const Sexy::Touch& i_touch, SeedPacketPtr i_seedPacket);
protected:
    void onUpdate() override;
    float m_radius;
};

#endif /* PVPSkillCursor_h */
