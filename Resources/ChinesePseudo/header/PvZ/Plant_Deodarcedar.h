/*
 * 	Plant_Deodarcedar.h
 *
 * 	Created on: 2023-3-20
 * 		Author: kkdud
 */

#ifndef PLANT_DEODARCEDAR_H__
#define PLANT_DEODARCEDAR_H__

#include "PlantFramework.h"

STATE_ENUM_CHILD_BEGIN(DeodarcedarState, PlantState)
	STATE_DEODARCEDAR_ENERGY_SAVE_SELF,
//	STATE_DEODARCEDAR_ENERGY_SAVE_OTHERS,
	STATE_DEODARCEDAR_UPGRADE,
	STATE_DEODARCEDAR_ATTACK_NORMAL,
	STATE_DEODARCEDAR_ATTACK_PLANTFOOD,
STATE_ENUM_END(DeodarcedarState);


class DeodarcedarProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(DeodarcedarProps, PlantPropertySheet, RtClass);

	float MinimumAttackableEnergy = -1.0f;
	float LaunchInterval = 15.0f;
	float LaunchIntervalLv3 = 15.0f;
	float EnergySaveInterval = 5.0f;
	float EnergySaveAmountSelf = 20.0f;
	float EnergySavePlantNumFactor = 10.0f;

	float EnergyStage2 = 100.0f;
	float EnergyStage3 = 300.0f;
	float EnergyMax = 150.0f;

	float AttackUpRate = 0.15f;
	float AttackUpRate3 = 0.3f;
	float AttackUpDuration = 10.0f;

	float CritRate = 0.5f;
	float CritDamageAmountFactor = 2.5f;

	float BaseDamage = 20.0f;
	float VelocityXWithGridNum = 0.5f;
	float RunePlantfoodStuckRate = 1.0f;
	float RunePlantfoodStuckDuration = 1.0f;
	float RuneAvatarLightningArcDiameterGridNum = 3.0f;
	float RuneAvatarLightningArcDamageAmount = 100.0f;

	float RuneAvatarLightningArcDamageAmountGuaranteed = 3.0f;
	float RuneAvatarLightningArcDamageAmountLevelFactor = 15.0f;
	float RuneAvatarLightningArcDamageAmountPlantFactor = 0.5f;

	float RunePlantfoodNormalAttackDamageAmountGuaranteed = 20.0f;
	float RunePlantfoodNormalAttackDamageAmountLevelFactor = 50.0f;
	float RunePlantfoodNormalAttackDamageAmountPlantFactor = 3.0f;

	float PlantfoodPlusEnergyProviderNum = 10.0f;

	std::vector<float> 	RuneDiameterGridNum = { 1.0f, 3.0f, 5.0f };
	std::vector<int>	RuneLightningNumPerSecond = { 1, 3, 5 };
	std::vector<int>	RuneLightningNumMax = { 10, 20, 30 };
	std::vector<float>	RuneAliveDuration = { 5.0f, 10.0f, 15.0f };
	std::vector<float>	RuneLightningDamageFactor = { 1.0f, 10.0f, 100.0f };

	std::vector<float> 	PlantfoodRuneDiameterGridNum = { 3.0f, 5.0f };
	std::vector<int>	PlantfoodRuneLightningNumPerSecond = { 3, 5 };
	std::vector<int>	PlantfoodRuneLightningNumMax = { 20, 40 };
	std::vector<float>	PlantfoodRuneAliveDuration = { 20.0f, 25.0f };

	std::vector<std::string> ElectricPlantTypes;

	std::vector<std::string> 	RuneIdleAnimation = { "idle_11", "idle_12", "idle_13" };
	std::vector<std::string>	RuneAttackNormalAnimation = { "light_11", "light_12", "light_13", "light_14", "light_15" };
	std::vector<std::string> 	RuneAttackCritAnimation = { "light_35", "light_35", "light_35", "light_35", "light_35" };

	std::vector<std::string> 	PlantfoodRuneIdleAnimation = { "idle_21", "idle_22" };
	std::vector<std::string>	PlantfoodRuneAttackNormalAnimation = { "light_21", "light_31", "light_32", "light_33", "light_34" };
	std::vector<std::string> 	PlantfoodRuneAttackCritAnimation = { "light_35", "light_35", "light_35", "light_35", "light_35" };

	std::string PlantfoodRuneArcAnimation = "arc";
};

class PlantDeodarcedar : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantDeodarcedar, PlantFramework, RtClass);

	Projectile* fire();

protected:
//	void registerForEvents() override;
//	void unregisterForEvents() override;
	void Initialize() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void Idle() override;

	void onAnimStoppedCallback(const std::string& i_anim) override;
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

private:
	void UpdateActions() override;

	void updateEnergySaveSelf();
	void updateShooter();

	void setState(DeodarcedarState i_state);

	void onEnergySaveSelfAnimationDone();
//	void onEnergySaveOthersAnimationDone();
	void onUpgradeAnimationDone();
	void onAttackNormalAnimationDone();

	void checkUpgradeStage();

	bool canFindTargets();
	

//	void onGetCharge(BoardEntity* i_srcBoardEntity, BoardEntity* i_dstBoardEntity);

	void applyAttackUpFeatures();
	void addPlantAttackUpEffect(Plant* i_plant);
	bool canAttackUpPlant(Plant* i_plant);
	bool isElectricPlant(Plant* i_plant, bool includeSelf = false);

	void gatherLightningEnergy(int i_index);	// 1: normal save, 2: plantfood save

	ProjectilePropertySheetPtr 	getCurrentRuneProjectileType();
	SexyVector3 				getCurrentRuneInitialVelocity();

	float	getEnergySavedByPlants();
	float   getCurrentRuneDiameterGridNum();
	int		getCurrentRuneLightningNumPerSecond();
	int		getCurrentRuneLightningNumMax();
	float	getCurrentRuneAliveDuration();
	float	getCurrentRuneLightningDamageFactor();
	float	getCurrentRuneLightningDamageFactorWithEnergy();
	float 	getCurrentRuneLaunchInterval();
	float 	getCurrentRuneCritRate();
	float 	getCurrentRuneCritDamageAmountFactor();
	float 	getCurrentRuneBaseDamageAmount();
	float 	getCurrentRuneVelocityXWithGridNum();
	float 	getCurrentRuneStuckRate();
	float 	getCurrentRuneStuckDuration();
	float 	getCurrentRuneLightningArcDiameterGridNum();
	float 	getCurrentRuneLightningArcDamageAmount();
	float 	getCurrentRuneNormalAttackDamageAmountOverride();

	std::string 				getCurrentRuneIdleAnimationToPlay();
	std::vector<std::string> 	getCurrentRuneNormalAttackAnimationToPlay();
	std::vector<std::string> 	getCurrentRuneCritAttackAnimationToPlay();
	std::string 				getCurrentRuneLightningArcAnimationToPlay();

	int 	getCurrentPlantfoodRuneStageIndex();

	float 		m_energy = 80;
	float		m_nextEnergySaveAmount = 0;

	pvztime_t 	m_launchTimer = PVZ_EOT();
	pvztime_t 	m_energySaveTimer = PVZ_EOT();

	int 		m_stage = 1;

	float		m_energyProviderNum = 0.0f;

};

class PlantAnimRig_Deodarcedar : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Deodarcedar, PlantAnimRig, RtClass);

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getIdleAnimationName() override { return "idle_" + std::to_string(m_popAnimStage); }
	std::string getPlantFoodMainAnimName() override;
    std::string getWaterAnimName() { return "water_" + std::to_string(m_popAnimStage); }

	std::string getEnergySaveSelfAnimation() { return "energy_save_" + std::to_string(m_popAnimStage); }
//	std::string getEnergySaveOthersAnimation() { return "energy_save_" + std::to_string(m_popAnimStage); }
	std::string getUpgradeAnimation() { return "upgrade_" + std::to_string(m_popAnimStage); }
	std::string getAttackNormalAnimation() { return "fire_" + std::to_string(m_popAnimStage); }
	std::string getAttackNormalCommand() { return "fire"; }
	std::string getAttackPlantfoodCommand() { return "fire"; }

	void setStage(int i_stage) { m_popAnimStage = i_stage; }
	void setPlantfoodRunStage(int i_stage) { m_plantfoodRunStage = i_stage; }

private:
	int m_popAnimStage = 1;
	int m_plantfoodRunStage = 0;
};


class DeodarcedarLightningRune : public Projectile
{
public:
	RT_CLASS_DEFINE(DeodarcedarLightningRune, Projectile, RtClass);

	void setProjectileIdleAnimationToPlay(std::string i_animLabel);
	void setLightningAttackEffectAnimationToPlay(std::vector<std::string> i_normalAttack, std::vector<std::string> i_critAttack) { m_normalAttackAnimations = i_normalAttack; m_critAttackAnimations = i_critAttack; }
	void setLightningArcAnimationToPlay(std::string i_animLabel) { m_arcAnimation = i_animLabel; }

	void setProjectileStage(int i_stage) { m_projectileStage = i_stage; }
	void setDiameterGridNum(float i_num) { m_diameterGridNum = i_num; }
	void setLightningNumPerSecond(int i_num) { m_lightningNumPerSecond = i_num; }
	void setLightningNumMax(int i_num) { m_lightningNumMax = i_num; }
	void setAliveDuration(float i_duration) { m_aliveTimer = PVZ_T() + i_duration; }
	void setTotalEnergy(float i_energy) { m_totalEnergy = i_energy; }
	void setLightningDamageFactor(float i_factor) { m_lightningDamageFactor = i_factor; }
	void setLightningDamageFactorWithEnergy(float i_factor) { m_lightningDamageFactorWithEnergy = i_factor; }
	void setAttackInterval(float i_interval) { m_attackInterval = i_interval; }
	void setCritRate(float i_rate) { m_critRate = i_rate; }
	void setCritDamageAmountFactor(float i_factor) { m_criteDamageAmountFactor = i_factor; }
	void setStuckRate(float i_rate) { m_stuckRate = i_rate; }
	void setStuckDuration(float i_duration) { m_stuckDuration = i_duration; }
	void setStuck(float i_duration) { m_stuckDuration = i_duration; }
	void setLightningArcDiameterGridNum(float i_num) { m_lightningArcDiameterGridNum = i_num; }
	void setLightningArcDamageAmount(float i_damageAmount) { m_lightningArcDamage = i_damageAmount; }
	void setNormalAttackDamageAmountOverride(float i_damageAmount) { m_normalAttackDamageAmountOverride = i_damageAmount; }

protected:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;

private:
	void updateAlive();
	void updateRune();
	void findTargetsAndAttack();
	void doAWaveOfAttack();
	void attackTarget(BoardEntity* i_ent, int i_turnIndex = 0, int ratio = 1.0f);
	void generateArc(BoardEntity* i_ent);

	int 	m_projectileStage = 1;
	float 	m_diameterGridNum = 1;
	int		m_lightningNumPerSecond = 1;
	int 	m_lightningNumMax = 5;
	int		m_lightningNumCount = 0;
	float 	m_totalEnergy = 0.0f;
	float 	m_lightningDamageFactor = 1.0f;
	float 	m_lightningDamageFactorWithEnergy = 1.0f;
	float 	m_attackInterval = 1.0f;
	float 	m_critRate = 0.0f;
	float 	m_criteDamageAmountFactor = 1.0f;
	float 	m_stuckRate = 0.0f;
	float 	m_stuckDuration = 0.0f;
	float 	m_lightningArcDamage = 0.0f;
	float	m_lightningArcDiameterGridNum = 0.0f;
	float 	m_normalAttackDamageAmountOverride = 0.0f;

	int 		m_leftLightningNum = 0;
	pvztime_t 	m_aliveTimer = PVZ_EOT();
	pvztime_t 	m_nextAttackTime = PVZ_EOT();

	std::vector<std::string> 	m_normalAttackAnimations;
	std::vector<std::string> 	m_critAttackAnimations;
	std::string 				m_arcAnimation;

	std::vector<RtWeakPtr<BoardEntity> > m_targetPool;
	int m_plantfoodRunStage = 0;
};


#endif /* PLANT_DEODARCEDAR_H__ */
