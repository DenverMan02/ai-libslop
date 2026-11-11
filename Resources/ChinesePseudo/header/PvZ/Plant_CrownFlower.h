/*
 * 	Plant_CrownFlower.h
 *
 * 	Created on: 2022-8-4
 * 		Author: kkdud
 */

#ifndef __PLANT_CROWNFLOWER_H__
#define __PLANT_CROWNFLOWER_H__

#include "PlantFramework.h"


STATE_ENUM_CHILD_BEGIN(CrownFlowerState, PlantState)
	CROWNfLOWER_STATE_ATTACKING,
	CROWNfLOWER_STATE_COOLDOWN,
STATE_ENUM_END(CrownFlowerState);


class CrownFlowerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(CrownFlowerProps, PlantPropertySheet, RtClass);

    float ReloadDuration = 0.5f;

    std::vector<float> DurationInRayStage = { 2.f, 5.f, 5.f };
    std::vector<float> DpsInRayStage = { 40.f, 120.f, 240.f };

    float HighEnergyHoldTime = 5.f;
    float TimeNeedToOpenHighEnergyStateLv3 = 3.f;

    float PlantfoodProjectileBaseDamageAmount = 1000.f;
    float AvatarProjectileBaseDamageAmount = 1000.f;
    float AvatarProjectileLightningDps = 150.f;

    std::vector<std::string> CannotBePushedZombieTypes;
    std::vector<std::string> CannotBeTargetedTypes;
    std::vector<std::string> CannotBePenetratedTypes;

    std::vector<std::string> SpecialMediumZombieTypes;
};

class PlantCrownFlower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCrownFlower, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;
	void UpdateUnconditionally() override;
	void Draw(Graphics* g) override;
	void onDestroy() override;
//	void onSleeped(bool sleeped) override;
	void OnRelocationBegun() override;
	void NotifySetHidden(bool i_newValue, bool i_oldValue) override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	class Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	DamageInfo TakeDamage(const DamageInfo& i_damage) override;

	void onApplyCondition(PlantConditions i_condition) override;

	void onAnimStoppedCallback(const std::string& i_animCommand) override;

	bool isValidTarget(RtWeakPtr<BoardEntity> i_entity);
	bool isPenetrable(RtWeakPtr<BoardEntity> i_entity);
	bool isTargetInAttackRange(RtWeakPtr<BoardEntity> i_entity);
	bool canZombieBePushed(RtWeakPtr<Zombie> i_zombie);

	Rect getNormalAttackRange();

private:
	void setState(CrownFlowerState i_newState);
	void updateTarget();
	void damageTargets(std::vector<RtWeakPtr<BoardEntity>> i_entities);
	float getRayEntityScaleY(std::vector<RtWeakPtr<BoardEntity>> i_entities);
	void updateZombiesPushing(std::vector<RtWeakPtr<BoardEntity>> i_entities);
	float calcPushingTotalWeight();
	void updatePushing();
	void onPushingZombiesChanged(std::vector<RtWeakPtr<Zombie>> i_oldVector);
	void refreshPushTypeAndValue();
	void freedPushZombies();

	void createRayEntity();
	void setRayStage(int i_stage);
	bool isInHighEnergyState() { return PVZ_T() < m_highEnergyStateEndTime; }
	void lostHighEnergyState();

	void tryStopAttacking();
	void stopAttacking();

	void onHeightEnergyStateChanged();

private:
	pvztime_t m_endTime = PVZ_EOT();
	RtWeakPtr<BoardEntity> m_target = nullptr;

	int m_rayStage = -1;
	float m_rayDamageAmountPerSecond = 15.f;

	bool m_isInHighEnergyState = false;
	pvztime_t m_highEnergyStateEndTime = PVZ_T();

	RtWeakPtr<class PenetratingRayEntity> m_rayEntity;
	RtWeakPtr<class EffectCrownFlowerPFRay> m_pfRayEffect;

	pvztime_t m_nextStuckTime;
	int m_plantfoodProjectileIndex = 0;

	std::vector<RtWeakPtr<Zombie>> m_pushingZombies;
	int m_pushType = 0;			// type: 0:no affect, 1: slow down, 2: stuck, 3: push
	float m_pushValue = 0.f;	// type == 1 : speed reduce percent, type == 3: push speed

	SexyVector3 m_firePosition;
};

class PlantAnimRig_CrownFlower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CrownFlower, PlantAnimRig, RtClass);

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getNormalAttackStartAnimLabel() { return m_isInHeState ? "attack_start_he" : "attack_start"; }
	std::string getNormalAttackingAnimLabel() { return m_isInHeState ? "attack_loop_he" : "attack_loop"; }
	std::string getNormalAttackEndAnimLabel() { return m_isInHeState ? "attack_end_he" : "attack_end"; }
	std::string getIdleAnimationName() override { return m_isInHeState ? "idle_he" : "idle"; }
	std::string getPlantFoodMainAnimName() override { return m_bAvatar ? "avatar" : "plantfood"; }

	void setHeState(bool i_flg) { m_isInHeState = i_flg; }

private:
	bool m_isInHeState = false;
};

class PenetratingRayEntity : public BoardEntity
{
public:
	RT_CLASS_DEFINE(PenetratingRayEntity, BoardEntity, RtClass);

	PenetratingRayEntity();

	void initialize();
	void AddToRenderQueue(RenderQueue* i_queue) override;
	void drawRayEntity(Graphics *i_g);
	void drawRayShooter(Graphics *i_g);
	SexyVector3 getTargetHitPosition(RtWeakPtr<BoardEntity> i_entity);

	void setOwner(RtWeakPtr<BoardEntity> i_entity);
	bool isOwnerMoved();

	void setIsValidTargetFunc(std::function<bool(RtWeakPtr<BoardEntity>)> i_func) { m_isValidTargetFunc = i_func; }
	void setIsPenetrableFunc(std::function<bool(RtWeakPtr<BoardEntity>)> i_func) { m_isPenetrableFunc = i_func; }
	void setDamageTargetsFunc(std::function<void(std::vector<RtWeakPtr<BoardEntity>>)> i_func) { m_damageTargetsFunc = i_func; }

	void setStartPosition(SexyVector3 i_startPos) { m_startPosition = i_startPos; }
	void setAttackRect(Rect i_rect) { m_attackRect = i_rect; }


	void setYScaleAttennuation(float i_attenuation, float i_minYScale = 0.f) { m_yScaleAttenuation = i_attenuation; m_minYScale = i_minYScale; }
	void setScaleYFunction(std::function<float(std::vector<RtWeakPtr<BoardEntity>>)> i_func) { m_scaleYFunc = i_func; }

	void setChildEffectPopAnimStr(std::string i_pamName, std::string i_animLabel = "idle");
	void setHitEffectPopAnimStr(std::string i_pamName, std::string i_animLabel = "idle");
	void setShooterEffectPopAnimStr(std::string i_pamName, std::string i_animLabel = "idle");

	void onPlaceOnBoard() override;
	int CalcRenderOrder() const override;
	bool ShouldDrawShadow() const override { return false; }

	void setTarget(RtWeakPtr<BoardEntity> i_target) { m_target = i_target; }
	std::vector<RtWeakPtr<BoardEntity>>& getPenetratedTargets() { return m_penetratedTargets; }


protected:
	void onInitialized() override {};
	void onDestroy() override;
	void onUpdate() override;
	void onDraw(Graphics* i_g) override;

	void refreshTargetVector();
	void refreshChildEffects();
	void refreshHitEffects();
	void refreshShooterEffect();

	void createExtraHitEffects();

	void refreshHitEffectsPosition();

	void refreshChildEffectsScale();
	void refreshHitEffectsScale();
	float getHitEffectScale();

	void createShooterEffect();

private:
	RtWeakPtr<BoardEntity> m_target;
	std::vector<RtWeakPtr<BoardEntity>> m_penetratedTargets;

	std::function<bool(RtWeakPtr<BoardEntity>)> m_isValidTargetFunc;
	std::function<bool(RtWeakPtr<BoardEntity>)> m_isPenetrableFunc;
	std::function<void(std::vector<RtWeakPtr<BoardEntity>>)> m_damageTargetsFunc;
	std::function<float(std::vector<RtWeakPtr<BoardEntity>>)> m_scaleYFunc;

	RtWeakPtr<BoardEntity> m_owner;
	SexyVector3 m_ownerPosition;
	std::vector<RtWeakPtr<Effect_PopAnim>> m_childEffects;
	std::vector<RtWeakPtr<Effect_PopAnim>> m_hitEffects;
	std::vector<Rect> m_childEffectClipRect;

	float m_yScaleAttenuation = 0.f;
	float m_minYScale = 0.f;

	std::string m_childEffectPopAnimName = "";
	std::string m_hitEffectPopAnimName = "";
	std::string m_shooterEffectPopAnimName = "";

	std::string m_childEffectAnimationToPlay = "";
	std::string m_hitEffectAnimationToPlay = "";
	std::string m_shooterEffectAnimationToPlay = "";

	RtWeakPtr<class Effect_PopAnim> m_rayRig;
	RtWeakPtr<class Effect_PopAnim> m_rayShooterRig;
	SexyVector3 m_startPosition;

	Rect m_attackRect;
};

class CrownFlowerPlantfoodProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(CrownFlowerPlantfoodProjectileProps, ProjectilePropertySheet, RtClass);

	CrownFlowerPlantfoodProjectileProps()
	{
		MinTossAngle = 25.0f;
		MaxTossAngle = 55.0f;
		TossSpeed = 600.0f;
		TossSpinRadiansPerSecond = -500.0f;
	}

	float MinTossAngle;
	float MaxTossAngle;
	float TossSpeed;
	float TossSpinRadiansPerSecond;
};

class CrownFlowerPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CrownFlowerPlantfoodProjectile, Projectile, RtClass);

	void setIsAvatarProjectile(bool i_flg) { m_isAvatarProjectile = i_flg; }
	void setLightningDps(float i_dps) { m_lightningDps = i_dps; }
	void setOverrideAttackLevel(float i_overrideAttackLevel);

	void onUpdate(pvztime_t i_dt) override;
	bool OnCollideEntity(BoardEntity* i_entity) override;
	void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;


private:
    void playHitEffect(BoardEntity* i_thitOwner, bool i_playSpark);
    void hitMechZombie(Zombie* i_zombie);
    void hitNormalZombie(Zombie* i_zombie);

    void ReleaseChainLightning();

    bool m_isAvatarProjectile = false;
    std::vector<ZombiePtr> m_lightedZombie;
    float m_lightningDps = 0.f;
    float m_overrideAttackLevel = 0.f;
    float m_finalDamageRate = 0.f;
};


#endif /* __PLANT_CROWNFLOWER_H__ */
