//
//  GridItemFireWall.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-12.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemFireWall_h
#define PlantsVersusZombies2_GridItemFireWall_h

#include "GridItem.h"
#include "EffectAnimRig_FireWall.h"
#include "Zombie.h"

class GridItemFireWallPropertySheet : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemFireWallPropertySheet, GridItemPropertySheet, RtClass);
    
	GridItemFireWallPropertySheet()
	{}
    
    std::string PopAnim;
    float iAttackValue = 0.0f;
    float iRunningTime = 0.0f;
    float iAttackInterval = 0.0f;
};


class GridItemFireWall : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemFireWall, GridItem, RtClass);
    
    struct DamageZombieInfo
    {
        DamageZombieInfo() {}
        DamageZombieInfo(RtWeakPtr<Zombie> ptr, ZombieState state)
        : zombePtr(ptr), oldState(state)
        {
            
        }
        
        void ResumeState()
        {
            if (zombePtr.IsValid())
            {
                zombePtr->setZombieState(oldState);
            }
        }
        
        RtWeakPtr<Zombie> zombePtr;
        ZombieState       oldState;
    };
    
	GridItemFireWall();
    
    virtual ~GridItemFireWall();
    
	bool IsDamageableByPlants() const override { return false; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
    void SetAvatar(bool isAvatar);
    void SetDamageRate(float rate);
protected:
    
	void registerForEvents() override;
	void onGridItemInitialize() override;
	void onUpdate() override;
    void onDraw(class Sexy::Graphics* i_g) override;
    
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
	void TakeDamage(const DamageInfo& i_damage) override;
    
private:
    
    bool IsInFire(RtWeakPtr<Zombie> ZombiePtr);
    
private:
    
    RtWeakPtr<class EffectAnimRig_FireWall> m_pRenderRig;
    std::vector<DamageZombieInfo> m_pBeDamageZombieVec;
    pvztime_t m_iLastDamageTime = 0;
    float m_damageRate = 1.0f;
};

#endif
