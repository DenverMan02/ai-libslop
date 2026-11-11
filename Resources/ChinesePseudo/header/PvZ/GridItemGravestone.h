//
//  GridItemGravestone.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __GRIDITEMGRAVESTONE_H__
#define __GRIDITEMGRAVESTONE_H__

#include <algorithm>

#include "Core.h"
#include "DamageInfo.h"
#include "EntityComponent.h"
#include "GridItemAnimation.h"
#include "Point.h"
#include "Rect.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "ZombieEnums.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

enum GravestoneState
{
    PVZ_BEGIN_ENUM(GRAVESTONESTATE_),
	GRAVESTONESTATE_DISABLED,
    GRAVESTONESTATE_BURIED,
    GRAVESTONESTATE_RISING,
    GRAVESTONESTATE_IDLE,
    GRAVESTONESTATE_BEINGEATEN,
    GRAVESTONESTATE_SAVED,
    PVZ_END_ENUM(GRAVESTONESTATE_)
};

class GridItemGravestonePropertySheet : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemGravestonePropertySheet, GridItemAnimationProps, RtClass);
	
	GridItemGravestonePropertySheet()
	{
		PopAnimRigClass = "GravestoneAnimRig";
		DamageStateCount = 5;
		BreakEffect = "";
		BreakEffectSound = "";
		CanBeEatenByGravebuster = true;
		GraveBusterEatTimeOveride = -1;
		GridExtents = Point(1,1);
		IsAnimated = false;
	}
	
	int8		DamageStateCount;
	std::string BreakEffect;
	std::string BreakEffectSound;
	SexyVector2 ArtCenter;
	bool		CanBeEatenByGravebuster;
	float		GraveBusterEatTimeOveride;
	Point		GridExtents;
	bool		IsAnimated;
};

class GridItemGravestone : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemGravestone, GridItemAnimation, RtClass);

	GridItemGravestone() {}

	bool		CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override	{ return m_state != GRAVESTONESTATE_DISABLED; }
	bool		CanBeTargetedBy(const BoardEntity* i_entity) const override	{ return m_state != GRAVESTONESTATE_DISABLED; }
    bool		IsDamageableByPlants() const override	;
	
	int			CalcRenderOrder() const override;
	Sexy::Point	GetGridExtents() const override;
	void		GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	virtual PlantingReason GetCantPlantReason() const;

	bool				CanSpawnZombies() const;
	void				SetRiseDelay(const pvztime_t i_delay);
	bool				CanBeEatenByGravebuster() const;
	bool				HasEatTimeOverride() const;
	float				GetEatTimeOverride() const;
	inline void			SetBeingEaten();
	inline void			FinishEatingAndDestroy();
	inline void			CancelBeingEaten(const float i_eatenProgress);
	bool ShouldClipWithWater() const override {return true;}

protected:

	void		registerForEvents() override;
	void		onGridItemInitialize() override;
	void		onUpdate() override;
	void		onTakeDamage(const DamageInfo& i_damage) override;
	Sexy::Rect	calcCollisionRect() override;
	void		onDestroy() override;

	int			calcDamageState();
	void		spawnBreakEffect(const int i_damageLevel);
	void		setState(const GravestoneState i_state);
	Point		getGridExtents() override;
	SexyVector2		getRenderOffset() override;

	// Serialized
	GravestoneState		m_state = GRAVESTONESTATE_Invalid;
	int					m_currDamageState = 0;
	EntityComponent_GroundEffect	m_groundEffect;

protected:
	void				initializeAnimRig();
	void				updateState();

	void				spawnDirt();
	void				setRiseHeight(float i_arbitraryHeightLerpValue);

	void				onEnableGridItems();

	// Serialized
	pvztime_t			m_stateTime = 0;
	pvztime_t			m_stateDuration = PVZ_EOT();
	float				m_eatenProgress = 1.0f;
	int					m_damageStates = 0;
};

inline void GridItemGravestone::SetBeingEaten()
{
	setState(GRAVESTONESTATE_BEINGEATEN);
}

inline void GridItemGravestone::CancelBeingEaten(const float i_eatenProgress)
{
	// At a minimum we pretend you were eaten 50% to get a nice rising effect.
	m_eatenProgress = max(i_eatenProgress, 0.5f);
	setState(GRAVESTONESTATE_SAVED);
}

inline void GridItemGravestone::FinishEatingAndDestroy()
{
	onKilled();
	Destroy();
}

inline Point	GridItemGravestone::getGridExtents()
{
	const GridItemGravestonePropertySheet* props = GetProps<GridItemGravestonePropertySheet>();
	
	return props->GridExtents;
}

inline SexyVector2	GridItemGravestone::getRenderOffset()
{
	const GridItemGravestonePropertySheet* props = GetProps<GridItemGravestonePropertySheet>();
	
	return props->ArtCenter;
}


namespace Message
{
	void GravestoneCreated(GridItemGravestone* i_graveStone);
	void GravestoneDestroyed(GridItemGravestone* i_graveStone);
}

#endif
