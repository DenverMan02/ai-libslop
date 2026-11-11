//
//  KiwiFruitProjectile.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/1/19.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef KiwiFruitProjectile_h
#define KiwiFruitProjectile_h

#include "Projectile.h"
#include "Plant.h"

class KiwiFruitProjectile : public Projectile
{
public:
    enum KiwiProjectileStatus
    {
        KiwiStatus_Flying,
        KiwiStatus_Hitting,
    };
    
    RT_CLASS_DEFINE(KiwiFruitProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onUpdate(pvztime_t i_dt) override;
    virtual void onProjectileInitialized() override;
    virtual void onDestroy() override;
    
    void SetLevelAttack(pvztime_t i_interval, pvztime_t i_aliveTime, int i_plantLevel);
//    void SetDamageInterval(pvztime_t i_interval) { k_damageInterval = i_interval; }
//    void SetAlivePeriod(pvztime_t i_time) { k_alivePeriod = i_time; }
    
private:
    void dealAreaDamage();
    uint32 m_state;
    
    //this two variables are used to deal level attack, don't change them in this class!
    pvztime_t k_alivePeriod;
    pvztime_t k_damageInterval;
    
    pvztime_t m_damageTime; //For dealing damage with interval
    pvztime_t m_aliveTime; //For life period
    
    int m_plantLevel;
};

#pragma mark - KiwiFruitSmallProjectile

class KiwiFruitSmallProjectile : public Projectile
{
public:
	enum KiwiProjectileStatus
	{
		KiwiSmallStatus_Idle,
		KiwiSmallStatus_Finding,
		KiwiSmallStatus_Flying,
		KiwiSmallStatus_Hitting,
		KiwiSmallStatus_Destroy
	};

	RT_CLASS_DEFINE(KiwiFruitSmallProjectile, Projectile, RtClass);
	KiwiFruitSmallProjectile();
	~KiwiFruitSmallProjectile();

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void onUpdate(pvztime_t i_dt) override;
	virtual void onProjectileInitialized() override;
	virtual void onDestroy() override;

	void SetAliveTime(pvztime_t i_aliveTime);
	virtual bool OnAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string &i_animCommand, const std::string &i_animCommandParam);
	void onAttackStop(const std::string &i_animName);
	void onDestroyAniStop(const std::string &i_animName);
	void onZombieDestroyed(Zombie* i_zombie);
	void onPlantDied(Plant* i_plant);
	void playDestoryAnim();
	void setPlantData(PlantTargetParams i_targetParams, Plant *i_plant, float i_maxPosX);
    void setZombieTarget(Zombie *zombie);
private:
	Zombie* m_zombie;
	uint32 m_state;
	float m_distanceWithZombie;
	pvztime_t m_aliveTime; //For life period
	pvztime_t m_floatingTime;//
	pvztime_t m_scaleTime;
	float m_maxPosX;

	//for find next zombie
	PlantTargetParams m_targetParams;
	Plant *m_plant;
};

#endif /* KiwiFruitProjectile_h */
