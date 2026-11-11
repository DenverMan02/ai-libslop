//
//  ZombieDinoPushEgg.hpp
//  PlantsVersusZombies2
//
//  Created by popcap on 11/2/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ZombieDinoPushEgg_hpp
#define ZombieDinoPushEgg_hpp

#include "ZombieWithPushingAction.h"
#include "RestrictionSet.h"

class GridItemBoardEntityConditionTarget;

class ZombieDinoPushEggProps : public ZombieWithActionsProps
{
public:
    RT_CLASS_DEFINE(ZombieDinoPushEggProps, ZombieWithActionsProps, RtClass);
    
    int32_t	NumberOfEggsToSpawnWith = 1;
    std::vector<EntityWeight> EggTypesToSpawn;
};

class ZombieDinoPushEgg : public ZombieWithPushingAction
{
public:
    RT_CLASS_DEFINE(ZombieDinoPushEgg, ZombieWithPushingAction, RtClass);
    
    ZombieDinoPushEgg();
    
    virtual ~ZombieDinoPushEgg();
    
    void onZombieInitialize() override;
    
    void TakeDamage(const DamageInfo& i_damage) override;
    void TakeFatalDamage(const DamageInfo& i_damage) override;
    
    bool CanBeFlickedOff() const override;
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    bool CanBeFlicked() const override;
    
    int CalcRenderOrder() const override;
    void spawnGridItemThatZombiePushes(int32_t column) override;
    
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    std::string pickDinoEgg();
    void onDraw(class Sexy::Graphics* i_g) override;
    
    bool willDieToShrinking() override { return true; }

private:
    void drawPushRectangle(const Sexy::Graphics* i_g);
    
    int m_renderOrder;
    bool m_isOnScreen;
};

class ZombieAnimRig_PushEgg : public ZombieWithPushingActionAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_PushEgg, ZombieWithPushingActionAnimRig, RtClass);
    
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
    
private:
    
};

#endif /* ZombieDinoPushEgg_h */
