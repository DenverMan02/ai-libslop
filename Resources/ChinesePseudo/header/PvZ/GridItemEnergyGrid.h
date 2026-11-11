//
//  GridItemArmrack.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-11-4.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemEnergyGrid__
#define __PlantsVersusZombies2__GridItemEnergyGrid__

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"

namespace Sexy { class Graphics; }

enum EnergyGridState
{
    PVZ_BEGIN_ENUM(ENERGYGRIDSTATE_),
    ENERGYGRIDSTATE_BURIED,
    ENERGYGRIDSTATE_RISING,
    ENERGYGRIDSTATE_IDLE,
    ENERGYGRIDSTATE_BEINGEATEN,
    ENERGYGRIDSTATE_SAVED,
    PVZ_END_ENUM(ENERGYGRIDSTATE_)
};


class Effect_PopAnim;

class GridItemEnergyGrid : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemEnergyGrid, GridItem, RtClass);
    
	GridItemEnergyGrid();
	virtual ~GridItemEnergyGrid() {}
	
	bool 		CanSpawnZombies() const;
	inline void SetBeingEaten();
	inline void CancelBeingEaten(float eatenProgress);
	inline int 	GetVariationID() const;
	inline void SetVariationID(const int variationID);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return false; }
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
	void		SetRiseDelay(pvztime_t i_delay);
    
	virtual int CalcRenderOrder() const override;
    
    virtual void Destroy() override;
    
    float       needStayTime;
    
protected:
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onDraw(Sexy::Graphics* i_g) override;


    
    
private:
	void setState(EnergyGridState state);
	void drawGridItem(Sexy::Graphics* i_g);
	void spawnDirt();
	int calcDamageState();
    
	EnergyGridState m_state = ENERGYGRIDSTATE_Invalid;
	pvztime_t m_graveStartRiseTime = PVZ_EOT();
	float m_eatenProgress = 1.0f;
	int m_riseHeight = 0;
	int m_damageStates = 5;
	pvztime_t m_lastHitTime = PVZ_EOT();
	int m_currDamageState = 0;
	
	int	m_variationID = 0;
	bool m_dirtEffectSpawned = false;
    
    bool m_IsPlantOn = false;
    
    RtWeakPtr<Effect_PopAnim> effectBagua;
    
    pvztime_t			m_creationTime = PVZ_EOT();

    pvztime_t leftSpawnEnergyTime;
    float fadeAlpha = 1.0f;
    int fadeFlag = 1.0f;
};

inline int GridItemEnergyGrid::GetVariationID() const
{
	return m_variationID;
}

inline void GridItemEnergyGrid::SetVariationID(const int variationID)
{
	m_variationID = variationID;
}

inline void GridItemEnergyGrid::SetBeingEaten()
{
	setState(ENERGYGRIDSTATE_BEINGEATEN);
}

inline void GridItemEnergyGrid::CancelBeingEaten(float eatenProgress)
{
	// At a minimum we pretend you were eaten 50% to get a nice rising effect.
	m_eatenProgress = max(eatenProgress, 0.5f);
	setState(ENERGYGRIDSTATE_SAVED);
}












#endif /* defined(__PlantsVersusZombies2__GridItemArmrack__) */
