//
//  GridItemEliminateShield.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-3-25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemEliminateShield__
#define __PlantsVersusZombies2__GridItemEliminateShield__

#include "Core.h"
#include "DamageInfo.h"
#include "EntityComponent.h"
#include "GridItemAnimation.h"
#include "Point.h"
#include "Rect.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "ZombieEnums.h"

enum EliminateShieldState
{
    PVZ_BEGIN_ENUM(ELIMINATESHIELDSTATE_),
    ELIMINATESHIELDSTATE_RISING,
    ELIMINATESHIELDSTATE_IDLE,
    ELIMINATESHIELDSTATE_IDLE2,
    ELIMINATESHIELDSTATE_CHANGEDAMAGE,
    ELIMINATESHIELDSTATE_DIE,
    PVZ_END_ENUM(ELIMINATESHIELDSTATE_)
};

class GridItemEliminateShield : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemEliminateShield, GridItemAnimation, RtClass);
    
	GridItemEliminateShield() {}
    
    bool		CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
	bool		CanBeTargetedBy(const BoardEntity* i_entity) const override;
	bool		IsDamageableByPlants() const override;
    
    void        TakeDamage(const DamageInfo& i_damage) override;
    
	int			CalcRenderOrder() const override;
    
protected:
    
	void		registerForEvents() override;
	void		onGridItemInitialize() override;
	void		onUpdate() override;
	void		onTakeDamage(const DamageInfo& i_damage) override;
	Sexy::Rect	calcCollisionRect() override;
	void		onDestroy() override;
    
    void		setState(const EliminateShieldState i_state);
    void        updateState();
    
private:
	void        initializeAnimRig();
    
    void        onRiseAnimDone(const std::string& i_label);
    void        onHitAnimDone(const std::string& i_label);
    void        onDieAnimDone(const std::string& i_label);
    void        onChangeDamageDone(const std::string& i_label);
    
    void        onEliminateOnce();
    
private:
    
	int			m_currDamageState = 0;
    
    EliminateShieldState m_state = ELIMINATESHIELDSTATE_Invalid;
    
    int         m_eliminateCount = 0;
};

namespace Message
{
	void EliminateShieldDestroyed(int i_gridY);
}

#endif /* defined(__PlantsVersusZombies2__GridItemEliminateShield__) */
