
#ifndef __PLANT_PEAVINE_H__
#define __PLANT_PEAVINE_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "PlantTypeVine.h"

class Zombie;

class PlantPeavineProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantPeavineProps, PlantPropertySheet, RtClass);
	
	PlantPeavineProps()
	:PlantFoodProjectileCount{1}
    ,Lv1SpecialAttackProbability{0.2}
    ,Lv2SpecialAttackProbability{0.6}
    ,Lv3SpecialAttackProbability{0.8}
    ,Lv2BoostAttackRate{0.15}
    ,Lv3BoostAttackRate{0.3}
    {}
	
	int PlantFoodProjectileCount;
    float Lv1SpecialAttackProbability;
    float Lv2SpecialAttackProbability;
    float Lv3SpecialAttackProbability;
    float Lv2BoostAttackRate;
    float Lv3BoostAttackRate;
};


class PlantPeavine : public PlantVineFramework
{
public:
	RT_CLASS_DEFINE(PlantPeavine, PlantVineFramework, RtClass);

    ~PlantPeavine();

	bool			CanApplyPlantfood() override;
	void			ApplyPlantfood() override;
	void			UpdatePlantfood() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool		    FindTargetAndFire(PlantWeapon i_plantWeapon);
	void 			Initialize() override;

	// void 			UpdatePowerUpStats() override;
	void 			OnRelocationBegun() override;
	void 			OnRelocationComplete() override;
	void            UpdateActions() override;    
    bool            OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam);
    void 			initializeProjectile(int i_index, Projectile* i_projectile);

protected:
    void            onDestroy() override;

private:

    enum
    {
        WEAPON_PeaNomal,
        WEAPON_PeaChill,
        WEAPON_PeaFire,
        WEAPON_PeaPrimal,
        WEAPON_PeaElectric,
        WEAPON_PeaShadow,
        WEAPON_PeaSling,
        WEAPON_PeaPoison,
        WEAPON_PeaAvatar,
    };

    void onBoostPlant(Plant* i_plant) override;
    int  getProjectileType();
    bool isAttackableMainPlant(Plant* i_plant);

	// RtWeakPtr<ComponentFamilyConditionRadius> m_boostRadius;
    // void onRailcartMoved(GridItemRailcart* i_railcart);
    void addGlowEffect(Plant* i_plant, Plant* i_boostPlant);
    void removeGlowEffect(Plant* i_plant);
    void onPlantPlaced(Plant* i_plant) override;
    void boostPlant(Plant* i_plant);

private:
	PeavinePlantgfood m_plantfood;    
    float m_specialAttackProbability;
    float m_boostAtk;    
};

class PlantAnimRig_Peavine : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Peavine, PlantAnimRig, RtClass);

    bool PlaySecondAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

    std::string getPlantFoodOnAnimName() override  { return "plantfood_start"; }
    std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
    std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }

};

#endif
