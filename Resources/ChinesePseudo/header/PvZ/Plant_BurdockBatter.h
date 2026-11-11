/*
 * 	Plant_BurdockBatter.h
 *
 * 	Created on: 2023-2-1
 * 		Author: kkdud
 */

#ifndef __PLANT_BURDOCKBATTER_H__
#define __PLANT_BURDOCKBATTER_H__

#include "GameSubSystem.h"
#include "PlantFramework.h"

STATE_ENUM_CHILD_BEGIN(BurdockBatterState, PlantState)
	STATE_BURDOCKBATTER_ATTACKING_STRAIGHT,
	STATE_BURDOCKBATTER_ATTACKING_PARABOLIC,
	STATE_BURDOCKBATTER_ATTACKING_MELEE,
	STATE_BURDOCKBATTER_ATTACKING_HOMER,
	STATE_BURDOCKBATTER_ATTACKING_PLANTFOOD,
	STATE_BURDOCKBATTER_ATTACKING_AVATAR,
	STATE_BURDOCKBATTER_COOLDOWN,
STATE_ENUM_END(BurdockBatterState);

class BurdockBatterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BurdockBatterProps, PlantPropertySheet, RtClass);

	std::vector<std::string> ValidProjectileTypes;

	float StraightBallDamageRate = 2.0f;
	float StraightBallVelocityRate = 2.0f;
	float StraightBallTossGridNum = 0.0f;
	float StraightBallTossGridNumLV2 = 0.5f;
	float StraightBallTossGridNumLV3 = 1.0f;
	float ParabolicBallStunSecond = 2.0f;
	float ParabolicBallStunSecondLV2 = 3.0f;
	float ParabolicBallStunSecondLV3 = 4.0f;
	float MeleeDamageAmount = 50.0f;
	float MeleeTossGridNum = 0.05f;
	float HomerTriggerRate = 0.1f;
	float HomerDamageRate = 5.0f;
	float HomerStunDur = 4.0f;
	float StunDurRateOnBigZombie = 0.5f;
	float PlantfoodDamage = 1000.0f;
	float PlantfoodStunDur = 4.0f;


	float Cooldown = 1.0f;
};

class PlantBurdockBatter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBurdockBatter, PlantFramework, RtClass);

	bool isValidProjectile(Projectile* i_proj);
	bool isValidZombie(Zombie* i_zombie);
	bool isCapturableProjectile(Projectile* i_proj);

protected:
	void Initialize() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void Idle() override;

private:
	void UpdateActions() override;

	void buildValidPropsList();

	void setState(BurdockBatterState i_newState, bool i_force = false);
	bool isInState(int i_state) { return m_plant->m_state == i_state; }
	bool isAttacking();
	Rect getSearchRect();
	Rect getHitRect();
	bool getValidProjectiles(std::vector<Projectile*>& o_projs, Rect i_searchRect, bool i_isStrict = false);
	bool getValidZombies(std::vector<Zombie*>& o_zombies, Rect i_searchRect);
	bool getValidBoareEntities(std::vector<BoardEntity*>& o_entities, Rect i_searchRect);

	void scanBattleField();

	void toHitProjectile(std::vector<Projectile*> i_projectiles);
	void toHitZombie(std::vector<Zombie*> i_zombies);
	void toHitBoardEntities(std::vector<BoardEntity*> i_entities);

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	void doHit();

	void enhanceStraightToProjectile(Projectile* i_proj);
	void enhanceParabolicToProjectile(Projectile* i_proj);
	void enhanceHomerToProjectile(Projectile* i_proj);
	void enhancePlantfoodToProjectile(Projectile* i_proj);
	void enhanceAvatarToProjectile(Projectile* i_proj);
	void attackBoardEntity(BoardEntity* i_entity);

	SexyVector3 getParabolicTargetPosition(Projectile* i_proj);

	void onAnimStoppedCallback(const std::string& i_anim) override;

	void onAttackAnimDone();

	void addHomerTriggerEffect();

	void captureProjectileForPlantfood(Projectile* i_proj);

	std::vector<ProjectilePropertySheet*> m_validProjectileProps;
	pvztime_t m_cooldownEndTime = PVZ_EOT();
	bool m_isNextCriticalHit = false;
	bool m_hasTriggerGene = false;

};

class PlantAnimRig_BurdockBatter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_BurdockBatter, PlantAnimRig, RtClass);

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getIdleAnimationName() override { return "idle"; }
	std::string getIdleCriticalAnimationName() { return "special_idle"; }
	std::string getAttackStraightBallAnimationName() { return "attack"; }
	std::string getAttackParabolicBallAnimationName() { return "attack2"; }
	std::string getAttackMeleeAnimationName() { return "attack"; }
	std::string getAttackHomerAnimationName() { return "attack_lv5"; }
	std::string getAttackPlantfoodAnimationName() { return "attack_plantfood"; }
	std::string getAttackAvatarAnimationName() { return "attack_plantfood02"; }

	std::string getHitCommandStr() { return "attack"; }
};

class BurdockBatterFallProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BurdockBatterFallProjectile, Projectile, RtClass);

	void onProjectileInitialized() override;

	bool OnCollideGround() override;
	void doFallDamage();
	void fall();
};

class BurdockBatterCriticalHit : public Projectile
{
public:
	RT_CLASS_DEFINE(BurdockBatterCriticalHit, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
};


typedef RtReflectionDelegate<Delegate1<class BoardEntity*> > CollideEntityCallback;
class BurdockBatter_SubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(BurdockBatter_SubSystem, GameObject, RtClass);

	enum Type
	{
		ENHANCE_TYPE_Straight,
		ENHANCE_TYPE_Parabolic,
		ENHANCE_TYPE_Melee,
		ENHANCE_TYPE_Homer,
		ENHANCE_TYPE_Critical,
	};

	struct EnhancedProjectile
	{
		ProjectilePtr	m_projectile = nullptr;
		ProjectilePtr   m_fallingProjectile = nullptr;

		Type			m_type = ENHANCE_TYPE_Straight;
		float 			m_stunDuration = 0.0f;
		float 			m_tossDistance = 0.0f;
		float 			m_velocityRate = 0.0f;
		float      		m_damageAmountRate = 0.0f;
	};

	BurdockBatter_SubSystem();
	~BurdockBatter_SubSystem();

	bool isProjectileAlreadyIn(Projectile* i_proj, Type i_type);

	void addStraightProjectile(Projectile* i_proj, float i_damageRateExtra, float i_valocityRateExtra, float i_tossDist);
	void addParabolicProjectile(Projectile* i_proj, float i_stunDurExtra, SexyVector3 i_targetPos, float i_flightHeight, float i_flightTime);
	void addHomerProjectile(Projectile* i_proj, Projectile* i_fallingProj);

	void addCriticalProjectile(Projectile* i_proj); // find and captured

	void setStunDurRateForBigZombie(float i_rate);

protected:

	void Update() override;
	void registerForEvents() override;

private:

	void onProjectileCollideEntity(Projectile* i_projectile, BoardEntity* i_entity);

	EnhancedProjectile* findEnhancedProjectile(Projectile* i_proj, Type i_type);

	std::vector<EnhancedProjectile> m_enhancedProjectiles;

	float m_bigZombieStunDurRate = 1.0f;

};

#endif
