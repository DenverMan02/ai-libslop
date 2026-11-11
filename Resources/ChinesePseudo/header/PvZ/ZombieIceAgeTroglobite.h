//
//  ZombieIceAgeTroglobite.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 11/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieIceAgeTroglobite__
#define __PlantsVersusZombies2__ZombieIceAgeTroglobite__

#include "ZombieWithPushingAction.h"
#include "RestrictionSet.h"

class GridItemBoardEntityConditionTarget;

class ZombieIceAgeTroglobiteProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeTroglobiteProps, ZombieWithActionsProps, RtClass);
	
	int32_t	NumberOfIceblocksToSpawnWith = 1;
    std::string ConditionToApply = "icecubed";
};

class ZombieIceAgeTroglobite : public ZombieWithPushingAction
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeTroglobite, ZombieWithPushingAction, RtClass);
	
	ZombieIceAgeTroglobite();
    
    virtual ~ZombieIceAgeTroglobite();
    
    void onZombieInitialize() override;

    void TakeDamage(const DamageInfo& i_damage) override;
    void TakeFatalDamage(const DamageInfo& i_damage) override;
    
    bool CanBeFlickedOff() const override;
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    bool CanBeFlicked() const override;
	// virtual void onUpdate() override;
    // virtual void onPlaceOnBoard();
    
	int CalcRenderOrder() const override;
    void spawnGridItemThatZombiePushes(int32_t column) override;
	int m_renderOrder;
    std::vector<ZombiePtr> m_iceBlockImps;
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	void onDraw(class Sexy::Graphics* i_g) override;
	
private:
	void drawPushRectangle(const Sexy::Graphics* i_g);
	

    bool m_isOnScreen;
    

};

class ZombieAnimRig_Troglobite : public ZombieWithPushingActionAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Troglobite, ZombieWithPushingActionAnimRig, RtClass);	
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	
private:

};

#endif /* defined(__PlantsVersusZombies2__ZombieIceAgeTroglobite__) */
