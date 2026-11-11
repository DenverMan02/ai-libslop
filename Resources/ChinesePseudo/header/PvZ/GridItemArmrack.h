//
//  GridItemArmrack.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-11-4.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemArmrack__
#define __PlantsVersusZombies2__GridItemArmrack__

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"
#include "zombieanimrig.h"
#include "Zombie.h"


namespace Sexy { class Graphics; }

enum ArmrackState
{
    PVZ_BEGIN_ENUM(ARMRACKSTATE_),
    ARMRACKSTATE_RISING,
    ARMRACKSTATE_IDLE,
    PVZ_END_ENUM(ARMRACKSTATE_)
};

enum ArmrackType
{
	ArmrackRandom,
	ArmrackHammer,
	ArmrackArmor,
	ArmrackFlag,
	ArmrackBomb,
	ArmrackTorch,
    ArmrackBlade,
	ArmrackNunchaku,
	ArmrackMark,	//keep at last
	ArmrackTypeCount = ArmrackMark - 1
};


class Effect_PopAnim;

typedef RtWeakPtr<class GridItemArmrack> GridItemArmrackPtr;

class GridItemArmrack : public GridItem
{
public:
	ArmrackType m_armrackType;

public:
	RT_CLASS_DEFINE(GridItemArmrack, GridItem, RtClass);
    
	GridItemArmrack() {}
	virtual ~GridItemArmrack();
	
    ZombiePtr findNearZombieTarget();
    
	bool 		CanSpawnZombies() const;
	inline int 	GetVariationID() const;
	inline void SetVariationID(const int variationID);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    
	virtual int CalcRenderOrder() const override;
    
    ZombieTypePtr ArmZombie(ZombieTypePtr i_zombieType) const;
    
    void    setFirePointer(class PopAnimRig* fire,int row,int col);
    virtual void onDestroy() override;
    bool ShouldDrawShadow() const override;

    void		GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
protected:

    virtual void onDrawShadow(class Sexy::Graphics* i_g) override;
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onDraw(Sexy::Graphics* i_g) override;
    virtual void onTakeDamage(const DamageInfo& i_damage) override;
    
    void initializeAnimRig();

    
private:
	void setState(ArmrackState state);
	void spawnArmrack();
	void spawnBreakEffect(int i_damageLevel);
	int calcDamageState();

	void onArmrackInEnd();
    
	ArmrackState m_state = ARMRACKSTATE_Invalid;
	int m_damageStates = 5;
	pvztime_t m_lastHitTime = PVZ_EOT();
	int m_currDamageState = 0;
	
	int	m_variationID = 0;
	bool m_armrackInEffectSpawned = false;
    bool m_CanCollision = false;
    bool m_haveGiveTanhao = false;

    int m_fireColumn = 0;
    int m_fireRow = 0;
    RtWeakPtr<class PopAnimRig> 	m_fireAnim;
    RtWeakPtr<class PopAnimRig> 	m_animArmrack;
};

inline int GridItemArmrack::GetVariationID() const
{
	return m_variationID;
}

inline void GridItemArmrack::SetVariationID(const int variationID)
{
	m_variationID = variationID;
}











#endif /* defined(__PlantsVersusZombies2__GridItemArmrack__) */
