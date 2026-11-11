/*
 * Plant_CarrotLauncher.h
 *
 *  Created on: 2014-7-30
 *      Author: jianglc
 */

#ifndef PLANT_CARROTLAUNCHER_H_
#define PLANT_CARROTLAUNCHER_H_

#include "PlantFramework.h"
#include "PlantAnimRig_CarrotLauncher.h"
#include "GameSubSystem.h"

enum CarrotLauncherState
{
	CARROT_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
	CARROT_STATE_RECOVER_LOOP,
	CARROT_STATE_RECOVER_END
};

class CarrotMissile : public BoardEntity
{
public:
	RT_CLASS_DEFINE(CarrotMissile, BoardEntity, Sexy::RtClass);

	CarrotMissile();
	virtual ~CarrotMissile();

	enum MissileState
	{
		PVZ_BEGIN_ENUM(MISSILE_STATE_),
		MISSILE_STATE_FALLING,
		MISSILE_STATE_ATTACK,
		MISSILE_STATE_EXPLOSION,
		MISSILE_STATE_PLANTED,
		PVZ_END_ENUM(MISSILE_STATE_)
	};

	virtual void 	onInitialized() override;
	virtual void 	onDestroy() override;

	void 			Activate(const bool i_active, const float fallDuration, const int i_row, const int i_col, const float i_attackLevel, const bool i_avatar);
    virtual void    onUpdate() override;
    virtual void    onDraw(Graphics* i_g) override;
	inline bool		IsActive() const {return m_active;}
	MissileState	getState() { return m_missileState; }
	int				getDropCol() { return m_dropCol; }
	int				getDropRow() { return m_dropRow; }

private:
	void 			setState(MissileState state);
	bool			canDamage(const BoardEntity* i_entity) const;

	void 			onAnimStopped(StandaloneEffect* i_effect);
    void            onMissileAnimStopped(const std::string & i_animName);
	void			createDropEffect(bool i_exploded);

	bool						m_hasExploded;
	bool 						m_active;
	MissileState 				m_missileState;
	float 						m_fallTimeElapsed;
	float 						m_fallDuration;
	RtWeakPtr<Effect_PopAnim> 	m_effectMissile;
    class Effect_PopAnim*       m_effectExplosion;

	SexyVector2					m_placementPosition;
	int							m_dropCol;
	int							m_dropRow;
	float						m_attackLevel;
	bool						m_isAvatar;
};

namespace Message
{
	void MissileDropped(CarrotMissile* i_missile);
}

class PlantCarrotLauncher : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCarrotLauncher, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
	//virtual void DoSpecial(int i_extraParam);
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual void PlayAttackAnimation() override;
	bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual void UpdateActions() override;
	virtual void ApplyPlantfood() override;
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;

protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
    Projectile* normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    void setState(int i_newState);
    bool isReadyToFire();
    CarrotRocketState CheckRocketState();
    int GetRandomHitWidth();
    float GetRocketCooldown();

    int m_leftRocket;
    bool m_missileLaunched;
};

class CarrotMissileSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(CarrotMissileSubsystem, GameSubSystem, RtClass);
    
    CarrotMissileSubsystem();
    ~CarrotMissileSubsystem() override;
    
    void ActivateCarrotMissile(const bool i_active, const float fallDuration, const int i_row, const int i_col, const float i_attackLevel, const bool i_avatar);
    bool HasMissileOnSameSquare(RtWeakPtr<CarrotMissile> i_missile);
    
private:
    std::vector<RtWeakPtr<class CarrotMissile> > m_CarrotMissiles;
    void onMissileDropped(CarrotMissile* i_missile);
};


#endif /* PLANT_CARROTLAUNCHER_H_ */
