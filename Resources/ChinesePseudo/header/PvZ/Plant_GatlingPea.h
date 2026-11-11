//
//  Plant_GatlingPea.h
//  PlantsVersusZombies2

#ifndef Plant_GatlingPea_hpp
#define Plant_GatlingPea_hpp

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "PlantAnimRig.h"

class GatlingPeaProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(GatlingPeaProps, PlantPropertySheet, RtClass);
    
    GatlingPeaProps()
    {
        PlantFoodProjectileCount = 1;
    }
    
    int PlantFoodProjectileCount;
    float ArcPelletChance1;
    float ArcPelletChance2;
};

class PlantGatlingPea : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantGatlingPea, PlantFramework, RtClass);
    PlantGatlingPea();
    
    virtual void Initialize() override;
public:
    bool			CanApplyPlantfood() override;
    void			ApplyPlantfood() override;
    void 			UpdatePlantfood() override;
    void			CancelPlantfood() override;
    virtual void	UpdateActions() override;
    Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool            IsInGeneBuffAttack();
    
private:
    void onPlantfoodStarted() override;
    int  getPlantActionIdx();
    virtual void	onAnimStoppedCallback(const std::string& i_animLabelName) override;
    Projectile* launchArcPelletAtTarget(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    int m_iRemainProjs;
    pvztime_t m_RemainProjTime;
    float m_ArcPelletRand;
    bool m_launchArcPellet;
    GatlingPeaPlantfood m_plantfood;
    int m_geneBuffAttack;
};


class PlantAnimRig_GatlingPea : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_GatlingPea, PlantAnimRig, RtClass);

    virtual std::string getIdleAnimationName() override;
    virtual std::string getAttackAnimationName() override;
    virtual std::string getWaterAnimName() override;

    void SetTargetPlant(RtWeakPtr<Plant> i_plant) { m_targetPlant = i_plant; }

private:
	RtWeakPtr<Plant> m_targetPlant;
};

#endif /* Plant_GatlingPea_hpp */
