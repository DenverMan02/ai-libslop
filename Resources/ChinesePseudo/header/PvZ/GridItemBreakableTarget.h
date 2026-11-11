//
//  GridItemBoardEntityConditionTarget.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 12/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemBreakableTarget__
#define __PlantsVersusZombies2__GridItemBreakableTarget__

#include <string>

#include "DamageInfo.h"
#include "DamageLifetime.h"
#include "GridItemAnimation.h"
#include "RtDb.h"
#include "RtObject.h"
#include "TimeMgr.h"

//
// Grid items that have breakable stages, configured through the
// DamageLifetime.
//

class GridItemBreakableTarget : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemBreakableTarget, GridItemAnimation, RtClass);
    GridItemBreakableTarget();
    
    void StartRegenImmediately();
    
    bool IsHealthFull();
    virtual void Heal();
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
	int CalcRenderOrder() const override;

    void TakeDamage(const DamageInfo& i_damage) override;
	
    void SetRenderOffset(SexyVector2 i_offset) { m_renderOffset = i_offset; }
    void SetRenderScale(SexyVector2 i_scale) { m_renderScale = i_scale; }
	
	virtual bool IsControlled() const { return m_isControlled; }
	virtual void SetIsControlled(bool i_isControlled) { m_isControlled = i_isControlled; }
    
    bool IsPlayingDeathAnimation() const { return m_playingDeathAnim; }

protected:
    virtual void deathAnimDoneHandler() {}

protected:
    void onGridItemInitialize() override;
    void onTakeDamage(const DamageInfo& i_damage) override;
    void onUpdate() override;
    
    SexyVector2	getRenderOffset() override;
    SexyVector2 getRenderScale() override;
    
    void onSpawnAnimDone(const std::string& i_animLabelName);
    void onHitAnimDone(const std::string& i_animLabelName);
    void onDeathAnimDone(const std::string& i_animLabelName);
    void startDeathAnim();

    virtual void spawnBreakEffect(int i_damageLevel);
    
    SexyVector2 m_renderOffset;
    SexyVector2 m_renderScale;
    
    pvztime_t m_lastTookDamage;
    bool m_playingTakeDamageAnim;
    bool m_playingDeathAnim;
	bool m_isControlled;
    int m_damagePhase;
};

#endif
