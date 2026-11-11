//
//  GridItemArmrack.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-11-4.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemGourdFire__
#define __PlantsVersusZombies2__GridItemGourdFire__

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"

namespace Sexy { class Graphics; }

enum GourdFireState
{
    PVZ_BEGIN_ENUM(GOURDFIRESTATE_),
    GOURDFIRESTATE_IDLE,
    PVZ_END_ENUM(GOURDFIRESTATE_)
};


class Effect_PopAnim;

class GridItemGourdFire : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemGourdFire, GridItem, RtClass);
    
	virtual ~GridItemGourdFire() {}

	inline int 	GetVariationID() const;
	inline void SetVariationID(const int variationID);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return false; }
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
    void fire(int row,int col,int length,float burnTime,class GridItemArmrack* armrack);
    void UpdateActions();
    
	virtual int CalcRenderOrder() const override;
    
    virtual void Destroy() override;
	virtual void onDraw(Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
    
protected:
	virtual void onGridItemInitialize() override;



    
private:
	void setState(GourdFireState state);
	void drawGridItem(Sexy::Graphics* i_g);
	void spawnDirt();
	int calcDamageState();
    
	GourdFireState m_state;
	pvztime_t m_graveStartRiseTime;
	float m_eatenProgress;
	int m_riseHeight;
	int m_damageStates;
	pvztime_t m_lastHitTime;
	int m_currDamageState;
	
	int	m_variationID;
	bool m_dirtEffectSpawned;
    


    
    float       SPAWN_ENERGY_TIME;
    pvztime_t leftSpawnEnergyTime;
    Image* energyGridImage;
    float fadeAlpha;
    int fadeFlag;
    
    
    pvztime_t m_explodedAtTime;
    int m_lastExplosionPropagationDistance;
	std::vector<BoardEntity*> m_damagedEntities;
    
    int m_column;
    int m_row;
    
    
    //PopAnimRig*  fireAnim;
    
    void SetBoardSpaceOrigin(const Sexy::SexyVector3 &i_origin, int i_renderLayerOverride /* = -1 */);
};

inline int GridItemGourdFire::GetVariationID() const
{
	return m_variationID;
}

inline void GridItemGourdFire::SetVariationID(const int variationID)
{
	m_variationID = variationID;
}














#endif /* defined(__PlantsVersusZombies2__GridItemArmrack__) */
