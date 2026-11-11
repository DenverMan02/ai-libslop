//
//  Plant_SpringPrincess.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 3/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SpringPrincess__
#define __PlantsVersusZombies2__Plant_SpringPrincess__

#include "GameObject.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieTosser_SubSystem.h"

namespace Sexy
{
	class SexyVector3;
}

enum AKP_STYLE
{
    AKP_NONE,
    AKP_NORMAL,
    AKP_EXPLODE,
    AKP_ICE,
    AKP_END,
};

class SpringprincessProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SpringprincessProjectile, Projectile, RtClass);
	
	SpringprincessProjectile();
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool OnCollideGround() override;
	static SpringprincessProjectile* getSpringprincessProjectile(Sexy::Point& i_gridPosition);
	void SetInitialLaunchValues(float i_height, float i_timeToTarget, int i_row);
    void RollProjectileStyle();
    bool AddAvatarSpecialCollide(BoardEntity* i_entity);
	int magicbeans_num = 0;
	bool is_spring = false;   //标记第二阶段的弹簧状态
	bool readiness_time = 0;	//标记第二阶段的弹簧状态准备时间
	bool is_magicbeans = false;   //标记魔法弹簧状态
	bool has_zombie = false;    //标记是否有锁定的僵尸
	BoardEntity* over_entity = nullptr;
	Zombie* mm_zombie = nullptr;
	RtWeakPtr<Zombie> m_hookedZombie = NULL;;
	bool is_over = false;  //标记僵尸可剩余的弹射
	bool on_sp = false;    //在地面发生碰撞 播放弹起动画时 为 true  完毕后为false  用于设置弹起动画播放时不处理碰撞  结束时 销毁子弹
	float m_destroyTime = 7.0f;
	float m_currentDtime = 0;
	bool has_avatar = false;
	bool is_pf = false;
	bool magic_ok = false;
	bool hasCollideGround = false;
	float temp_T = 0;
	int m_rowBeingFiredAt;
	SexyVector3 mm_position;
	std::vector<BoardEntityPtr>	m_targetsAlreadyHit;
	float spring_time = 0;
	float m_PrepareCD = 5;
    
protected:
	void onUpdate(pvztime_t i_dt) override;
	void onProjectileInitialized() override;
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
	
private:

    void DoFission(BoardEntity* i_entity);
	void DoBounce();
    void DealSplashDamage(BoardEntity* i_entity, bool i_chill);
    void OnEffectDone(class StandaloneEffect* i_effect);
    void OnEffectDone2(class StandaloneEffect* i_effect);
    void HideAllLayer();
    void ShowNormalMegaSpringprincess();
    void ShowFireMegaSpringprincess();
    void ShowIceMegaSpringprincess();
    
    Projectile* FissionProjectile(int type =0);
	BoardEntity* findNextTarget(int i_row = -1);
    BoardEntity* findNearestTargetType(BoardEntityTypeFlag i_flag, int i_row);
	
    AKP_STYLE m_akpStyle;
	float m_initialLobHeightThisBounce = 0;
	float m_initialTimeOfFlightThisBounce;
	float m_reductionRatio;
	float m_targetingRadius;

};

class SpringprincessProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(SpringprincessProjectileProps, ProjectilePropertySheet, RtClass);
	
	SpringprincessProjectileProps()
	{
		ProjectileBounceCount = 5;
		ProjectileRetargetingRadius = 200.0f;
		PropertyReductionMultiplierPerBounce = 0.75;
		DamageReductionAmountPerBounce = 5;
        SpringprincessSpecialFireDamage = 200.f;
        SpringprincessSpecialFireRadius = 2.f;

	}

    bool FissionAfterFirstCollide;
	int ProjectileBounceCount;
	float ProjectileRetargetingRadius;
	float PropertyReductionMultiplierPerBounce;
    float DamageReductionAmountPerBounce;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    float SpringprincessSpecialFireDamage;
    float SpringprincessSpecialFireRadius;
};

class PlantSpringprincess : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSpringprincess, PlantFramework, RtClass);
	PlantSpringprincess();
	bool CanApplyPlantfood() override;
	void DoSpecial(int i_extraParam = 0) override;
	virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
protected:
	void LaunchProjectileAt(SpringprincessProjectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
private:
	Projectile* FissionProjectile();
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target, int i_row);
	BoardEntityPtr findBestTargetInRow(int i_row);
	BoardEntity* findLeftmostTargetType(BoardEntityTypeFlag i_flag, int i_row);
	float m_fireTime = 0;
	float m_AttackCD = 5;
	float m_PFDamageAdd = 5;
	float m_PFADamageAdd = 5;
};

class SpringprincessProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SpringprincessProps, PlantPropertySheet, RtClass);
	
	SpringprincessProps()
	{
        FissionProbilityPercent = 0;
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
        PFDamageAdd = 200.f;
        PFADamageAdd = 300.f;
        AttackCD = 5.f;
        PrepareCD =2.f;
	}
	
    // Projectile properties
    int FissionProbilityPercent;
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
	float PrepareCD;
	float PFDamageAdd;
	float PFADamageAdd;
	float AttackCD;
};

#endif /* defined(__PlantsVersusZombies2__Plant_SpringPrincess__) */
