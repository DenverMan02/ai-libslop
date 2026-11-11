/*
 * Plant_OrchidMage.h
 *
 *  Created on: 2022-8-12
 *      Author: huangzhisheng
 */

#ifndef PLANT_ORCHIDMAGE_H_
#define PLANT_ORCHIDMAGE_H_

#endif /* PLANT_ORCHIDMAGE_H_ */
#include "Plant.h"
#include "PlantFramework.h"
#include "RtDb.h"
#include "RtObject.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"

//Props
class OrchidmageProps : public PlantPropertySheet{
public:
	RT_CLASS_DEFINE(OrchidmageProps, PlantPropertySheet, RtClass);
	OrchidmageProps()
	{
		NumPlantfoodRockets = 4;
		PlantfoodFireTime = 0.25f;
		TargetOffset.x = 0;
		TargetOffset.y = 0;
		ChargingTime = 10.0f;
		MyCooldownTimeMin = 4.0f;
		MyCooldownTimeMin = 4.0f;
		NormalDamagePerSecond = 225.0f;
		ExplodeDamage = 450.0f;
	}

	int NumPlantfoodRockets;
	float ExplodeDamage;
	float NormalDamagePerSecond;
	pvztime_t PlantfoodFireTime;
	SexyVector2 TargetOffset;
	pvztime_t ChargingTime;
	pvztime_t MyCooldownTimeMin;
	pvztime_t MyCooldownTimeMax;
	std::vector<std::string> ZombieWhiteList;
};

class PlantOrchidMage : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantOrchidMage, PlantFramework, RtClass);
	virtual void	Initialize() override;
	virtual void	UpdateActions() override;
	virtual void	DoSpecial(int i_extraParam = 0) override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual void onAnimStoppedCallback(const std::string& i_animCommand) override;
	virtual void AutoFire() override;

	bool fristFind;
	bool isPlantAttack;
	bool toPassive;
	bool isAfterPlantFood;
protected:
	virtual void CancelPlantfood();
	SexyVector3 findLayerLocation(std::string componentName);
	void hideGravitationalBall(int targetBall);
	void appearGravitationalBall(int targetBall);
	bool triggerPassive(); //Detect enemies within passive attack
	void startPassive();
	void onDestroy();
//	void Draw(class Graphics* i_g);
	void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation);
	void onStandaloneEffectFinishedCallback(class StandaloneEffect *i_effect);
	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam);

private:
	enum State
	    {
	        STATE_PLANTFOOD_ATTACK = STATE_FRAMEWORK_BEGIN,
	        STATE_TRANSITION,
	        STATE_RECOVERY,
	        STATE_ATTACK
	    };
	enum ballState
	{
		ORCHIDMAGE_BALL1,
		ORCHIDMAGE_BALL2,
		ORCHIDMAGE_BALL3,
		ORCHIDMAGE_ALLBALL4
	};
	void setState(const uint i_state);
	Rect passiveRange;
	int passiveTimes;
	bool timeLock;
	bool playingPassive;
	bool canAttack;
	bool attackOnPlaying;
	bool attacking;
	pvztime_t m_idleEndTime;
	pvztime_t passiveTime;
	pvztime_t recoverTime;
	pvztime_t nextRecover;
};

class Effect_PassiveBall :	public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_PassiveBall, Effect_PopAnim, RtClass);
    void startBallShowUp(SexyVector3 m_position);
protected:
    void playBallShowUp(SexyVector3 m_position);
    int m_renderDifferenceFromPlant = RENDER_LAYER_PLANT + 1;
};

class Effect_ProjectileHit : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_ProjectileHit, Effect_PopAnim, RtClass);
    void startBound(pvztime_t boundTime, ZombiePtr i_zombie);
    void starSpiralPill(pvztime_t spiralTime, float posX, float posY);

protected:
    void playBound(pvztime_t boundTime, ZombiePtr i_zombie);
    void playSpiralPill(pvztime_t spiralTime, float posX, float posY);
    int m_renderDifferenceFromPlant = RENDER_LAYER_PLANT_ABOVE_ZOMBIES - RENDER_LAYER_PLANT;
};

class PlantAnimRig_OrchidMage : public PlantAnimRig
{
public:
	 RT_CLASS_DEFINE(PlantAnimRig_OrchidMage, PlantAnimRig, RtClass);

		bool PlayInitialFrame() override;
		bool PlayAttackOn();
		bool PlayAttackIdle();
	    bool PlayAttack();
	    bool PlayPassive();
	    bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
	    void onPopAnimCommand(pvztime_t i_atTime, const std::string &i_command, const std::string &i_param)  override;
};

///projectile
class OrchidmageProjectile_1 : public Projectile
{
public:
	RT_CLASS_DEFINE(OrchidmageProjectile_1, Projectile, RtClass);
	OrchidmageProjectile_1();
	float boundProbability2;
	float boundProbability3;
	int m_plantLevel;
	pvztime_t timeInterval;
	pvztime_t boundTime;
	pvztime_t spiralTime;       //Total time of spiral pill
	bool spiralPill; 			//determine whether it is a special skill of rank 5
	bool isPlantFood;
	bool isAvatar;
	float m_ExplodeDamage;
	float m_NormalDamagePerSecond;

protected:
	void getTheMaximumNumberOfDrags(const int m_plantLevel);
//	void onDraw(class Graphics* i_g);
	void explode();
	void onUpdate(pvztime_t i_dt) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	bool OnCollideEntity(BoardEntity* i_entity) override;
	void onDestroy();
	void boundZombie(Zombie* m_zombie);
	void blackHoleKillsZombies();
	void damageEntities();
	SexyVector3 movePosition(SexyVector3 i_target,float fraction);

private:
	pvztime_t 	secondPull;	//time for the second pull
	pvztime_t 	thirdPull;	//Time for the third pull
	pvztime_t 	gridItemFirstHarm;
	pvztime_t	gridItemSecondHarm;
	pvztime_t	gridItemThirdHarm;
	float mWidth;
	float mHeight;
	bool throughZombie = false;
	bool toPull = false;
	bool Explosive = true;
	bool turnOnSeckill;
	bool damageSwitch;
	bool secondDamageSwitch;
	bool thirdDamageSwitch;
	std::vector<BoardEntity*> targets;
	Sexy::Rect m_spikeRange;
	Sexy::Rect  m_AttackRange;
	pvztime_t m_plosiveTime;
	pvztime_t m_DamageEndTime;
	int maxDrags;
	int counter;
	int AttackTop;
	int AttackBottom;
};


class OrchidmageProjectile_2 : public Projectile
{
public:
	RT_CLASS_DEFINE(OrchidmageProjectile_2, Projectile, RtClass);
	OrchidmageProjectile_2();

protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	void repelZombie(BoardEntity* i_entity);

private:
	bool repelzombie = true;
};


class ZombieMove
{
public:
	ZombieMove()
    : moveVelocity(0.0f)
	, lastXPosition(0.0f)
	, targetPositionY(0.0f)
	, sign(true)
	, remove(false)
	, Zombie(nullptr)
	, hasVerticalChange(false)
	, targetPositionX(0.0f)
	, targetTime(0.0f)
    {}

    ZombiePtr Zombie;

    bool hasVerticalChange;
    bool sign;
    bool remove;
    float targetPositionY;
    float lastXPosition;
    float targetPositionX;
    float moveVelocity;
    pvztime_t targetTime;
};

class OrchidMageSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(OrchidMageSubsystem, GameSubSystem, RtClass);
	OrchidMageSubsystem();
	~OrchidMageSubsystem() override;

	virtual void Update() override;

	void addZombieToVector(ZombieMove& newZombie);
	void moveToDestination(ZombieMove& m_zombie);
	bool haveZombieMove(Zombie* zombie);
	void setZombiePositionX(Zombie* zombie,float positionX);
	ZombieMove GetZombieMove(Zombie* zombie);

protected:
	virtual int findPath(ZombieMove& m_zombie);

private:
	void ChangePosition(ZombieMove& m_zombie);
	void onZombieDeath(Zombie* zombie);
	void onZombieDestroyed(Zombie* zombie);
	void onZombieDropHead(Zombie* zombie);
	std::vector<ZombieMove> m_zombieList;
};

class OrchidMageLauncherSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(OrchidMageLauncherSubSystem, GameSubSystem, RtClass);

	void QueueShot(PlantOrchidMage* i_owner, pvztime_t i_launchTime, const Point& i_target, bool i_isPlantfood);

	struct OrchidMageLauncherEntry
	{
		OrchidMageLauncherEntry() {}
		OrchidMageLauncherEntry(PlantOrchidMage* i_owner, pvztime_t i_launchTime, const Point& i_target, bool i_isPlantfood);

		PlantPtr Owner;
		RtWeakPtr<const OrchidmageProps> OrchidmagePropertySheet;
		pvztime_t LaunchTime;
		Point Target;
		bool m_isPlantfood;
	};

	void Update() override;

private:
	void launch(const OrchidMageLauncherEntry& i_entry);

	std::vector<OrchidMageLauncherEntry> m_shots;
};
//#endif /* PLANT_ORCHIDMAGE_H_ */
