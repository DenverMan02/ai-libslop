//
//  GridItemBronze.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-12-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemBronze__
#define __PlantsVersusZombies2__GridItemBronze__

#include <iostream>
#include "Precompile.h"
#include "GridItem.h"
#include "zombieanimrig.h"
#include "Zombie.h"



enum BronzeState
{
    PVZ_BEGIN_ENUM(BRONZESTATE_),
        BRONZESTATE_RISING,
        BRONZESTATE_IDLE,
    PVZ_END_ENUM(BRONZESTATE_)
};



class GridItemBronze : public GridItem
{
public:
	enum BronzeType
	{
		BronzeStrength = 1,
		BronzeAgile,
		BronzeMage,
        
		BronzeMark,	//keep at last
		BronzeTypeCount = BronzeMark - 1
	};
    
public:
	RT_CLASS_DEFINE(GridItemBronze, GridItem, RtClass);
    
	GridItemBronze() {}
	virtual ~GridItemBronze();
	
	void initBronzeType(BronzeType i_bronzeType);
    
	bool 		CanSpawnBronze() const;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    void    TakeFatalDamage(const DamageInfo& i_damageInfo) override;
    void    MowDown();
    
	virtual int CalcRenderOrder() const override;
    void playBrokenAnimation(int currentStep);
    

    virtual void onDestroy() override;
    
    bool ShouldDrawShadow() const override;
    
    pvztime_t leftSpawnBronzeTime = PVZ_EOT();
    float m_shakeOffset = 0;
    int   m_totalSpawnTime = 0;
protected:
    
    virtual void onDrawShadow(class Sexy::Graphics* i_g) override;
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onDraw(Sexy::Graphics* i_g) override;
    virtual void onTakeDamage(const DamageInfo& i_damage) override;
    
    void initializeAnimRig();
    
    
private:
	void setState(BronzeState state);
	void spawnBronze();
    
	void onArmrackInEnd();
    void spawnZombie(const std::string&);
    void spawnTransitionAnimation();
    ZombieTypePtr getZombieBronzeType() const;
    
    
    BronzeType m_bronzeType = BronzeStrength;
	BronzeState m_state = BRONZESTATE_Invalid;
	pvztime_t m_lastHitTime = PVZ_EOT();

	

	bool m_armrackInEffectSpawned = false;
    bool m_CanCollision = false;
    
    RtWeakPtr<class PopAnimRig> 	m_animBronzeStump;
    
    float m_showTextStartTime = 0;
    int m_currentSpawnStep = 0;
    int   m_maxSpawnAnimStep = 4;
    int   m_lastStep = 0;
    
};





#endif /* defined(__PlantsVersusZombies2__GridItemBronze__) */
