/*
 * Plant_NarcissusShooter.h
 *
 *  Created on: 2018-7-31
 *      Author: Administrator
 */

#ifndef PLANT_NARCISSUSSHOOTER_H_
#define PLANT_NARCISSUSSHOOTER_H_

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "ZombieParticle.h"
#include "Projectile.h"
#include "Effect_PopAnim.h"

class NarcissusShooterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(NarcissusShooterProps, PlantPropertySheet, RtClass);

	NarcissusShooterProps()
	: BubbleRate(0.9f)
	, DoubleAttackRate(0.5f)
	, ImprovedDoubleAttackBonus(1.0f)
	, PlantFoodProjectileNum(30)
	, SuperAttackRate(0.9f)
	, SuperAttackDuration(3.0f)
	, SuperStunDuration(2.0f)
	, WaterDamageExtra(20)
	{
		// Do nothing.
	}

	float BubbleRate;
	float DoubleAttackRate;
	float ImprovedDoubleAttackBonus;
	int PlantFoodProjectileNum;
	float SuperAttackRate;
	float SuperAttackDuration;
	float SuperStunDuration;
	float WaterDamageExtra;
};

class PlantNarcissusShooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantNarcissusShooter, PlantFramework, RtClass);

	virtual void			Initialize() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	void					CancelPlantfood() override;
	//virtual bool			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void					damageZombies(PlantWeapon i_plantWeapon, bool i_special);
	void					damageZombies(PlantWeapon i_plantWeapon, DamageInfo i_damage, bool i_special);
	//virtual bool			OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	virtual void			UpdateActions() override;
	bool 					FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual void 			PlayAttackAnimation() override;
	bool					ShouldClipWithWater() const override;
	//bool					IgnoreCurrentAction(PlantActionType i_type) override;
private:
	void DoLevelSpecial(int state, PlantWeapon i_plantWeapon);
	void playZombieHitEffect(Zombie* i_zombie, SexyVector3 i_offset);
	Projectile* LaunchBubble(Zombie* i_zombie);
	void onAnimStopped(const std::string& i_animLabel);
	void separatePlantfoodProjectiles();
	Projectile* DoPlantfoodEffect(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
	void EndSuperAttack();

	int m_comboCount;
	bool m_inDoubleAttack;
	std::vector<int> m_plantfood_projectile_num;
	int m_plantfood_index;
	bool m_superAttackState;
	bool m_hasStartedSuperAttack;
	float m_superDamageApplied;
	float m_superNextHitEffect;
	pvztime_t m_superEndTime;
};

class PlantAnimRig_NarcissusShooter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_NarcissusShooter, PlantAnimRig, RtClass);

	PlantAnimRig_NarcissusShooter();
public:
	void				setIsInWater(bool flag);
	virtual std::string getPlantFoodMainAnimName() override;
	virtual std::string getIdleAnimationName() override;
private:
	bool m_isInWater;
};

class NarcissusBasicProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(NarcissusBasicProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetPlantfood(bool i_plantfood) { m_isPlantfood = i_plantfood; }

protected:
	virtual void onInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;
	virtual void onDestroy() override;
private:
	bool canCarryHelmType(HelmType) const;
	bool canCarryHelmFrom(Zombie* i_zombie) const;
	class BoardEntity* tryCarryZombieParticle(ZombieParticle* i_particle);
	class BoardEntity* tryCarryHelmFrom(Zombie* i_zombie);
	class BoardEntity* tryCarryEntity(BoardEntity* i_target);

	RtWeakPtr<class BoardEntity> CarriedEntity;
	bool m_isPlantfood;
};

class NarcissusPlantfoodProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(NarcissusPlantfoodProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
private:
	void LaunchPlantfoodBubbles(BoardEntity* i_entity);
};

class NarcissusAvatarProjectile : public NarcissusPlantfoodProjectile
{
public:
	RT_CLASS_DEFINE(NarcissusAvatarProjectile, NarcissusPlantfoodProjectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class NarcissusShooter_Effect_PopAnim : public Effect_PopAnim
{	
public:
	RT_CLASS_DEFINE(NarcissusShooter_Effect_PopAnim, Effect_PopAnim, RtClass);
	void SetPlant(Plant* i_plant);
	void DoubleAttackCallBack(const std::string& i_animLabel);
private:
	RtWeakPtr<Plant> m_targetPlant;
};

#endif /* PLANT_NARCISSUSSHOOTER_H_ */
