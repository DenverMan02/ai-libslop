#ifndef __PLANT_COCONUTCANNON_H__
#define __PLANT_COCONUTCANNON_H__

#include "Precompile.h"
#include "PlantFramework.h"
#include "Projectile.h"

enum CoconutCannonState
{
	COCONUT_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
	COCONUT_STATE_RECOVER_LOOP,
	COCONUT_STATE_RECOVER_END
};

class StarCoconutCannonProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(StarCoconutCannonProjectile, Projectile, RtClass);
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual bool OnCollideRoof() override;
    
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

class CoconutCannonProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CoconutCannonProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual bool OnCollideRoof() override;

	void SetExplosionParameters(float i_explodeAtLocation, float i_minimumSpeedScale, float i_numZombiesForMinScale);
	
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
	std::vector<ZombiePtr> m_pushedZombies;
};

class CoconutCannonSpecialProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CoconutCannonSpecialProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


class PlantCoconutCannon : public PlantFramework 
{
	RT_CLASS_DEFINE(PlantCoconutCannon, PlantFramework, RtClass);

	PlantCoconutCannon()
	: m_hitRowBelow(false)
	, m_touchIdent(Sexy::InvalidTouchID)
	{
		// Do nothing.
	}
	
	virtual ~PlantCoconutCannon();
	
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
    
protected:
    
    //PVZ2_CHINESE_BEGIN
//	virtual void DoSpecialForAvatarNormal(){ m_StarRateCoolDown = 0.7f; }  // for avatar
	//PVZ2_CHINESE_END
	
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
};

#endif // __PLANT_COCONUTCANNON_H__
