#ifndef Plant_Armorflame_H_
#define Plant_Armorflame_H_

#include "HeroPlant.h"
#include "Projectile.h"
#include "PlantAnimRig.h"
#include "ComponentWarmingRadius.h"

class ComponentWarmingRadiusForHeroPlant : public ComponentWarmingRadius
{
	RT_CLASS_DEFINE(ComponentWarmingRadiusForHeroPlant, ComponentWarmingRadius, RtClass);
public:
    virtual void GetGridItemsInRadius(std::vector<BoardEntity*>& o_touchedEntities) override;

};

class ArmorflameProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ArmorflameProps, PlantPropertySheet, RtClass);
    
	int EnhancementFireCounterRequired = 3;//增加层数所需的攻击次数
	float EnhancementReduceTime = 10.0f;//减少层数需要的时间
	float BaseEnhancementAttackRate = 0.25f;//层数基础倍率

	ComponentWarmingRadiusProps NormalWarmingRadius;
	ComponentWarmingRadiusProps PlantfoodWarmingRadius;
};

class PlantTypeArmorflame : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeArmorflame, PlantType, RtClass) {}
    
    void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

class PlantArmorflame : public HeroPlantFramework
{
public:
    RT_CLASS_DEFINE(PlantArmorflame, HeroPlantFramework, RtClass);

	virtual void			Initialize() override;
    virtual void 			UpdateUnconditionally() override;

	virtual void			registerForEvents() override;
	virtual void			unregisterForEvents() override;

	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			CancelPlantfood() override;

	virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	void onZombieDied(class Zombie* zombie, const class DamageInfo* i_deathBlow);

	void increaseAttackCount();
	void refreshBuff();

	float GetMissileDamageImprove();
	float GetMissileDeprioritizeRate();

	float GetCannonballPiercingDamageImprove();
	float GetCannonballPiercingSlowDownRate();
	float GetCannonballExtensionOfTime();

protected:
	int m_plantfoodCounter;
	int m_attackCounter;
	int m_attackCounterStep;
	int m_enhancementLevel;
	int m_enhancementLevelMax;
	float m_enhancementReduceTime;
	pvztime_t m_enhancementLevelTimer;
	pvztime_t m_buffCheckTimer;

	RtWeakPtr<ComponentWarmingRadiusForHeroPlant> m_warmingRadius;
};

class PlantAnimRig_Armorflame : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Armorflame, PlantAnimRig, RtClass);

	virtual bool PlayPreviewAnim(bool bHideLayer) override;

	void SetEnhancementLevel(int i_level);
    
};

class ArmorflameCannonball : public Projectile
{
public:
    RT_CLASS_DEFINE(ArmorflameCannonball, Projectile, RtClass);
public:
    void InitializeArmorflameCannonball(bool i_isPlantfood);

    virtual void onUpdate(pvztime_t i_dt) override;

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;

    void spawnProjectile();
	void explode();
	void checkAnimRig();

private:
	bool m_isPlantfood;
	float m_flashingTimer;
	float m_explodeTimer;
    float m_seekerTimer;
	float m_damageTimer;
	float m_piercingDamageRate;
	float m_piercingSlowdown;
	bool m_collideState;
};


class ArmorflameMissile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArmorflameMissile, Projectile, RtClass);
	
    void InitializeArmorflameMissile(bool i_isPlantfood);
	void SetOverrideTarget(BoardEntity* i_overrideTarget);

    void FindNewTarget();
	BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
	bool CanBeTarget(BoardEntity* i_entity);
    
protected:
	virtual void onDraw(Graphics* i_g) override;
	virtual void onDeflection(class BoardEntity* i_deflector) override;
	virtual void moveThroughTime(pvztime_t i_dt) override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void damageEntity(BoardEntity* i_entity) override;
	virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
    virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

	float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);

private:
	bool m_deflected;
	bool m_isPlantfood;
	float m_appendDamageRate;
    int m_maxTargets;

	RtWeakPtr<BoardEntity> m_overrideTarget;
    std::vector<BoardEntityPtr> m_hitEntities;
	std::vector<SexyTransform2D> m_phantomTrans;
};


#endif
