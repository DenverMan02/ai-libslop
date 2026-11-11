//
//  Plant_LotusShower.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-1-14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_LotusShower_h
#define PlantsVersusZombies2_Plant_LotusShower_h

#include "PlantFramework.h"
#include "Projectile.h"

class PlantLotusShower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLotusShower, PlantFramework, RtClass);
    
	void Initialize() override;
	
    bool CanApplyPlantfood() override { return true; }
    
	void ApplyPlantfood() override;
    
	void CancelPlantfood() override;
    
	bool CanEndPlantfood() override;
    
    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    bool ShouldClipWithWater() const override;
    
    void WaterLotusBullet(bool bPlantFood = false);
    
    void SquareDamage(float iAmount);
    void Idle() override;
private:
    
    void LandBulletProc(Projectile* pProjectile, PlantWeapon iPlantWeapon, bool bPlantFood = false);
    
    Projectile* LandLotusBullet(bool bPlantFood = false);
    
    void WaterLotusLauncher(bool bPlantFood = false);
    
};


class LotusShowerPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(LotusShowerPropertySheet, PlantPropertySheet, RtClass);
    
    ValueRange LandBulletFlyTime;
    ValueRange LandBulletFlyHeight;
};

class PlantAnimRig_LotusShower : public PlantAnimRig
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_LotusShower, PlantAnimRig, RtClass);
    
    std::string getIdleAnimationName() override;
    
};

class Effect_DropInWater : public Effect_PopAnim
{
    RT_CLASS_DEFINE(Effect_DropInWater, Effect_PopAnim, RtClass);
    
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void SetPlantLotus(RtWeakPtr<Plant> ptrPlantLotusShower) { m_ptrPlantLotusShower = ptrPlantLotusShower; }
    
    void SetState(bool bPlantFood) { m_bPlantFood = bPlantFood; }
    
private:
    
    RtWeakPtr<Plant> m_ptrPlantLotusShower;
    
    bool m_bPlantFood = false;
};

class LandProjectile : public Projectile
{
    RT_CLASS_DEFINE(LandProjectile, Projectile, RtClass);
    
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
};

class WaterProjectile : public Projectile
{
    RT_CLASS_DEFINE(WaterProjectile, Projectile, RtClass);
    
    WaterProjectile() : m_bVortex(false) {}
    
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
    
    void onUpdate(pvztime_t i_dt) override;
    
protected:
    
    bool IsOverColumn();
    
private:
    
    bool m_bVortex;
};

class WaterPlantFoodProjectile : public WaterProjectile
{
    RT_CLASS_DEFINE(WaterPlantFoodProjectile, WaterProjectile, RtClass);
    
    bool OnCollideEntity(BoardEntity* i_entity) override;
    
    void SetAvatar(bool bAvatar) { m_bAvatar = bAvatar; }
    
private:
    
    bool m_bAvatar = false;
    
    std::set<BoardEntityPtr> m_EntitiesSet;
};



#endif
