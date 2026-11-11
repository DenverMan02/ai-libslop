#ifndef __PLANT_PLANTAIN_H__
#define __PLANT_PLANTAIN_H__

#include "Precompile.h"
#include "PlantFramework.h"
#include "Projectile.h"

namespace Message
{
    void ZombieConfusion(Zombie* i_zombie);
}


enum PlantainState
{
	PLANTAIN_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
	PLANTAIN_STATE_RECOVER_IN,
	PLANTAIN_STATE_RECOVER_LOOP,
	PLANTAIN_STATE_RECOVER_END
};

class StarPlantainProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StarPlantainProjectile, Projectile, RtClass);
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
    void SetExplosionParameters(float i_explodeAtLocation, float i_minimumSpeedScale, float i_numZombiesForMinScale, float i_stunTime);
	
protected:
	virtual void onInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;
    
private:
	void doExplosion(const std::string& i_animLabel);
	void handleExplosionDone(const std::string& i_animLabel);
	
	bool m_fuseLit;
	float m_explosionTargetX;
    bool  m_explosived;
	float m_minScale;
	int m_numZombiesForMinScale;
    float m_stunTime;
	std::vector<ZombiePtr> m_pushedZombies;
};

class PlantainProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PlantainProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetExplosionParameters(float i_explodeAtLocation, float i_minimumSpeedScale, float i_numZombiesForMinScale);
	void setOwnerLevel(int nLevel);
protected:
	virtual void onInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;

private:
	void doThrough(BoardEntityPtr i_entity);
	void doExplosion(const std::string& i_animLabel);
	void handleExplosionDone(const std::string& i_animLabel);
	bool isPassThroughZombie(BoardEntityPtr i_entity);
	bool isShouldTakeDamage(BoardEntityPtr i_entity);
	bool isZombieCanBeTossToEnd(BoardEntityPtr i_entity);
	bool m_fuseLit;
	float m_explosionTargetX;
    bool  m_explosived;
	float m_minScale;
	int m_numZombiesForMinScale;
	std::vector<ZombiePtr> m_pushedZombies;
	std::vector<BoardEntityPtr> m_vecPassThroughZombies;
	int m_nOwnerLevel;
};

class PlantPlantain : public PlantFramework 
{
	RT_CLASS_DEFINE(PlantPlantain, PlantFramework, RtClass);

	PlantPlantain()
	: m_hitRowBelow(false)
	, m_touchIdent(Sexy::InvalidTouchID)
	, m_bIsSuperSkill(false)
	{
		// Do nothing.
	}
	
	virtual ~PlantPlantain();
	
public:
	virtual void	SetPopAnimDelegates(class PlantAnimRig* i_rig) override;
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	
	virtual bool	CanApplyPlantfood() override;
	virtual void 	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
    void Idle() override;
	void SetHitRowBelow(bool i_hitRowBelow);

    virtual void AutoFire() override;
    void SetCoolDownRate(float i_rate) { m_StarRateCoolDown = i_rate; }
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	
	void SetTargetZombie(ZombiePtr i_targetZombie);
	void SetTargetZombie(Zombie* i_targetZombie);
private:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	
	void fireProjectileCallback(pvztime_t i_atTime);
	void onFireAnimDone(const std::string& i_animLabel);
	void onRecoverAnimDone(const std::string& i_animLabel);
	
	void setState(int i_newState);
	bool isReadyToFire();

	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();
	
	// Set by the Cannon Minigame to make targeting easier
	bool 			m_hitRowBelow;
	Sexy::TouchID	m_touchIdent;
    float           m_StarRateCoolDown = 1.0f;

private:
	ZombiePtr m_spuerSkillTargetZombie;
	bool m_bIsSuperSkill;
};


class PlantainProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(PlantainProps, StarRateProps, RtClass);
	
	PlantainProps()
	{
		NumPushedZombiesForMinSpeed = 5;
		MinimumSpeedScaleWhilePushing = 0.3f;
		ExplodeAtXPosition = 750.f;
        StarPFStunTime = 5.0f;
		SpecialAttackRate = 0.2;
	}

	float MinimumSpeedScaleWhilePushing;
	int32 NumPushedZombiesForMinSpeed;
	float ExplodeAtXPosition;
    float StarPFStunTime;
	float SpecialAttackRate;
	float SuperSkillAttackRate;
};


class PlantainPlantFoodProjectile : public Projectile
{
public:
	enum KiwiProjectileStatus
    {
        Tornado_Flying,
        Tornado_Hitting,
    };
	RT_CLASS_DEFINE(PlantainPlantFoodProjectile, Projectile, RtClass);
	virtual void onUpdate(pvztime_t i_dt) override;
	virtual void onProjectileInitialized() override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void TakeAttack_Hit1();
	void					onZombieTossEnd(Zombie* i_zombie);
	void setOwnerLevel(int level);
	void setIsOwnerAvatar(bool isAvatar);
private:
	void dealTornadoAreaDamage();
	bool isZombieShouldStun(Zombie* i_zombie);
	bool isZombieShouldFlickOff(Zombie* i_zombie);
	bool isZombieCanBeToss(Zombie* i_zombie);
	bool isZombieCanBeBlackOff(Zombie* i_zombie);
	void onDestroy() override;

	bool isCanFlicOff(Zombie* i_targetZombie);

	uint32 m_state;
	
	pvztime_t k_alivePeriod;
    pvztime_t k_damageInterval;
    
    pvztime_t m_damageTime; //For dealing damage with interval
    pvztime_t m_aliveTime; //For life period
private:
	bool m_bIsCollided;
	int m_nPlantLevel;
	bool m_bIsAvatar;
	std::vector<ZombiePtr> m_flickOffZombies;
};

////////
class PlantainPlantFoodProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PlantainPlantFoodProjectileProps, ProjectilePropertySheet, RtClass);
    
    PlantainPlantFoodProjectileProps()
    {
        AirshipDamage = 1000.0f;
		proDuration = 5.0f;
    }
    
    float		AirshipDamage;
	float 	proDuration;
	SexyVector2 InitialPositionOffset;
};


class PlantainSuperSkillProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PlantainSuperSkillProjectile, Projectile, RtClass);
	PlantainSuperSkillProjectile() : m_pOwnerPlant(nullptr) {}

	void SetOwnerPlant(PlantPlantain* ownerPlant);
	PlantPlantain* GetOwnerPlant() const;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
private:
	bool isZombieCanConfusion(ZombiePtr i_zombie);
	void ChangeZombieTeam(Zombie* i_zombie) const;
	PlantPlantain* m_pOwnerPlant;
};


class PlantainSuperSkillProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(PlantainSuperSkillProjectileProps, ProjectilePropertySheet, RtClass);
	PlantainSuperSkillProjectileProps() : HealsOnHypnosis(true) {}
	bool HealsOnHypnosis;
};

#endif // __PLANT_Plantain_H__
