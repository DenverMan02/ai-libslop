#ifndef __PLANT_PRIMAL_PEASHOOTER_H__
#define __PLANT_PRIMAL_PEASHOOTER_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "Plant_Peashooter.h"

enum PrimalPeashooterProjectileType
{
    PPPPT_None = -1,
    PPPPT_Normal = 0,
    PPPPT_Rock,
    PPPPT_PFNormal,
    PPPPT_PFRock,
    PPPPT_Level5Lava,
    PPPPT_PFLevel5Lava,
    PPPPT_AvatarBall,
};

enum Level5SplitDirect
{
    SPLIT_UP_RIGHT = 0,
    SPLIT_UP_LEFT,
    SPLIT_UP,
    SPLIT_DOWN,
    SPLIT_COUNT,
};

class Zombie;

class PrimalPeashooterSplitTargetProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PrimalPeashooterSplitTargetProjectileProps, ProjectilePropertySheet, RtClass);
    
    PrimalPeashooterSplitTargetProjectileProps()
    :DamageDuration(0.0f)
    {}
    
    float DamageDuration;

};

class PrimalPeashooterSplitTargetProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PrimalPeashooterSplitTargetProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual bool OnCollideGround() override;
    virtual void onProjectileInitialized() override;
    virtual void InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
    
    virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    virtual void onUpdate(pvztime_t i_dt) override;
    
    void onAnimStopped(const std::string &i_animName);
    
    void setStartDirect(int directIdx);
    
    bool m_isOnGround;
    bool m_isDisapear;
    float m_runTime;
    int  m_endIdx;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class PrimalPeashooterProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(PrimalPeashooterProjectileProps, ProjectilePropertySheet, RtClass);
	
	PrimalPeashooterProjectileProps()
	:StunDuration(0.0f)
	,KnockbackChance(0.0f)
	,KnockbackDistance(0.0f)
	,KnockbackTime(0.0f)
	,KnockbackHeight(0.0f)
    ,ShouldSplit(false)
    ,SplitSpan(0.15f)
	{}
	
	float StunDuration;
	float KnockbackChance;
	float KnockbackDistance;
	float KnockbackTime;
	float KnockbackHeight;
    bool  ShouldSplit;
    float SplitSpan;
};

class PrimalPeashooterProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PrimalPeashooterProjectile, Projectile, RtClass);

    virtual void onProjectileConverted() override;
protected:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void onSplashDamageHitEntity(BoardEntity *i_hitEntity)override;

    virtual void onProjectileInitialized() override;
    virtual void onUpdate(pvztime_t i_dt) override;
private:
	void hitZombie(BoardEntity *i_hitEntity);
	
	bool shouldStun(BoardEntity* i_impactedEntity);
	void stunZombie(BoardEntity* i_impactedEntity);

	bool shouldKnockback(BoardEntity* i_impactedEntity);
	void knockbackZombie(BoardEntity* i_impactedEntity);
    
    void doSplit(bool isEnd);
    
    float splitTime;
};

class PlantPrimalPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPrimalPeashooter, PlantFramework, RtClass);
	
    virtual void    AddPot(PlantPot* pot) override;

	Projectile*         Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool                CanApplyPlantfood() override {return true;}
    virtual void		CancelPlantfood() override;
    virtual bool        OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
private:
	Projectile* firePlantfoodProjectile(Zombie* i_targetZombie, PlantWeapon i_plantWeapon);
};

class PlantAnimRig_PrimalPeashooter : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PrimalPeashooter, PlantAnimRig, RtClass);
    
protected:
    std::string getPlantFoodOffAnimName() override;

};

#endif //__PLANT_PRIMAL_PEASHOOTER_H__
