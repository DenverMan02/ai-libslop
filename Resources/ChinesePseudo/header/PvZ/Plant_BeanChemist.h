#ifndef PlantsVersusZombies2_Plant_BeanChemist_h
#define PlantsVersusZombies2_Plant_BeanChemist_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemAnimation.h"

class BeanChemistProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BeanChemistProps, PlantPropertySheet, RtClass);

    BeanChemistProps()
    :PlantRecoverTime(17.5),
    PlantRecoverTime3(12),
    ProjectileLobHeight(350),
    ProjectileTimeOfFlight(1.2)
    {
        
    }

    float ProjectileLobHeight;
    float ProjectileTimeOfFlight;

    float PlantRecoverTime;
    float PlantRecoverTime3;
};


STATE_ENUM_CHILD_BEGIN(BeanChemistState, PlantState)
    BeanChemist_ATTACK,
    BeanChemist_RECOVER_LOOP,
    BeanChemist_RECOVER_WEAKUP,
STATE_ENUM_END(BeanChemistState);

enum BeanChemistBulletType
{
    BeanChemistBulletType_Green,
    BeanChemistBulletType_Blue,
    BeanChemistBulletType_Purple,
};

class PlantBeanChemist : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBeanChemist, PlantFramework, RtClass);
	
	virtual void Initialize() override;
    virtual void UpdateActions() override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;

	BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override { return ENTITYTYPE_ZOMBIE; }
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual class Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual void onAnimStoppedCallback(const std::string& i_animCommand);

    virtual void Idle() override;

    void SetState(const uint i_state);
    BeanChemistBulletType GetBulletType();

private:
    BeanChemistBulletType GetRandomBulletType();
    float GetRevoverTime();
private:

    BeanChemistBulletType m_bulletType;
}; 

class PlantAnimRig_BeanChemist : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_BeanChemist, PlantAnimRig, RtClass);

    virtual std::string getIdleAnimationName() override;
    virtual	std::string getPlantFoodMainAnimName() override;
    virtual std::string getWaterAnimName() override;

    void SetTargetPlant(RtWeakPtr<Plant> i_plant) {m_targetPlant = i_plant;};
    bool PlayRecoverLooped();

private:
	std::string m_idleTag;
	RtWeakPtr<Plant> m_targetPlant;
};

class BeanChemistProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BeanChemistProjectile, Projectile, RtClass);

    BeanChemistProjectile();

	virtual bool OnCollideGround() override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    void SetBulletType(BeanChemistBulletType i_type);
    void WillCreateSmoke(bool i_flag) { m_createSmoke = i_flag; }
    void SetNewPlantLevel(int i_level) { m_newPlantLevel = i_level; }
    void SetNewPlantPlantfoodRate(float i_rate) { m_newPlantPlantfoodRate = i_rate; }

protected:
    virtual std::string getImpactPam() override;
private:
    void CreateSmoke(Sexy::Point i_point);

    BeanChemistBulletType m_bulletType;
    bool m_createSmoke;
    int m_newPlantLevel;
    float m_newPlantPlantfoodRate;
    ZombiePtr m_targetZombiePtr;
};


class BeanChemistSmoke : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(BeanChemistSmoke, GridItemAnimation, RtClass);

    BeanChemistSmoke();
    virtual int CalcRenderOrder() const override;
    
    void SetBulletType(BeanChemistBulletType i_type);
    void SetDamageAmount(float i_amount) { m_damageAmount = i_amount; }
    void SetNewPlantLevel(int i_level) { m_newPlantLevel = i_level; }
    void SetNewPlantPlantfoodRate(float i_rate) { m_newPlantPlantfoodRate = i_rate; }
    void SetWhiteListZombie(ZombiePtr i_zombiePtr) { m_targetZombiePtr = i_zombiePtr; }

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    pvztime_t m_endTime;
    BeanChemistBulletType m_bulletType;
    float m_damageAmount;
    int m_newPlantLevel;
    float m_newPlantPlantfoodRate;
    ZombiePtr m_targetZombiePtr;
};




#endif