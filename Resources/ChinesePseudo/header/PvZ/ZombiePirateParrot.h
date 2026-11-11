//
//  ZombiePirateParrot.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePirateParrot_h
#define PlantsVersusZombies2_ZombiePirateParrot_h

#include "Zombie.h"
#include "PvZ2IDs.h"
#include "Plant.h"

STATE_ENUM_CHILD_BEGIN(ZombieStateParrot, ZombieState)
	ZS_P_FlyToTarget,
	ZS_P_AttachedToPlant,
	ZS_P_PickingUpPlant,
	ZS_P_DestroyingPlant,
	ZS_P_Returning,
	ZS_P_FlyingAway,
STATE_ENUM_END(ZombieStateParrot)

class ZombiePirateParrot : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePirateParrot, Zombie, RtClass);
	
	virtual void SetTargetColAndRow(int i_col, int i_row);
	virtual void SetCaptain(ZombiePtr i_captain);
	virtual void OnCaptainDied();
	
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;
	
protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onApplyCondition(ZombieConditions i_condition) override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	virtual bool willDieToShrinking() override { return true; }

	virtual void onTurnedToAsh() override;
	virtual void onElectrocuted() override;
	virtual void onDestroy() override;
    
    // Parrot shadow changes when flying away
    virtual SexyVector2 GetShadowScaling() const override;
	
	virtual class Plant* findPlantTarget();
	
	PlantPtr pickTarget(Point& i_targetPos);

	DECLARE_STATE_FUNCTIONS(ZombieState, FlyToTarget);
	DECLARE_STATE_FUNCTIONS(ZombieState, AttachedToPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, PickingUpPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, DestroyingPlant);
	DECLARE_STATE_FUNCTIONS(ZombieState, Returning);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyingAway);
	
protected:
	virtual bool moveToDestination(const float i_destX, const float i_destY);
	//PVZ2_CHINESE_START
    struct PlantCache
    {
        SexyVector3 plantPos;
        uint        plantState;
        int         plantRow;
        
        PlantCache()
        {
            plantPos = SexyVector3(-1, -1, 0);
            plantState = -1;
            plantRow = -1;
        }
    };
    
	PlantCache     m_plantCache;
	//PVZ2_CHINESE_END
	ZombiePtr		m_captain;
	PlantPtr		m_pickedUpPlant;
	int				m_targetCol = -1;
	int				m_targetRow = -1;
};

#endif
