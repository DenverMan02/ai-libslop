#ifndef __PLANT_PEANUT_H__
#define __PLANT_PEANUT_H__

#include "Plant_Peashooter.h"

class PeanutProps : public PeashooterProps
{
public:
    RT_CLASS_DEFINE(PeanutProps, PeashooterProps, RtClass);    
    float PlantFoodShieldHitpoints = 0;
};

class PlantPeanut : public PlantPeashooter
{
public:
	RT_CLASS_DEFINE(PlantPeanut, PlantPeashooter, RtClass);
	
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    
	void Initialize() override;
	void ApplyPlantfood() override;
    void PlayChewedOnSound() override;
    
    void UpdatePlantfood() override;
    void CancelPlantfood() override;
	
    Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	float		GetLaunchDelayMultiplier() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	
	void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	bool TryBlockZombossRush(Zombie* i_zombie) override;
    
private:
	virtual void updateShieldHealth(const float i_newShieldHealth);
	
	float m_shieldHealth = -1.0f;
};

enum EPeaNutAttackType
{
    ePeaNutAttackType_Invalid = -1,
    ePeaNutAttackType_Bottom,
    ePeaNutAttackType_Top,
    ePeaNutAttackType_Both
};

class PlantAnimRig_Peanut : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Peanut, PlantAnimRig, RtClass);
	
	int CalcDamageStateCount() override;
	bool PlayIdleLooped() override;
	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	
	void ShowArmorHelmet(bool i_show, bool bHasAvatar, int i_shieldDamageState);
	
    EPeaNutAttackType GetCurrentAttackType() const { return m_eAttackType; }
    void SetPlayAttackBoth() { m_eAttackType = ePeaNutAttackType_Both; }
    void SetPlayAttackTop() { m_eAttackType = ePeaNutAttackType_Top; }
    void SetPlayAttackBottom() { m_eAttackType = ePeaNutAttackType_Bottom; }
    
    std::vector<std::string> GetArmorLayers();
    
private:
	void onPopAnimInitialized() override;
	
	int  m_shieldDamageIndex = 0;
    
    EPeaNutAttackType m_eAttackType = ePeaNutAttackType_Invalid;
};

#endif //__PLANT_WALLNUT_H__
