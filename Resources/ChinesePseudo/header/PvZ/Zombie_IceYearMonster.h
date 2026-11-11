
/*
 * Zombie_IceYearMonster.h
 *
 *  Created on: 2024-01-08
 *      Author: zjj
 */

#ifndef PlantsVersusZombies2_IceYearMonster_h
#define PlantsVersusZombies2_IceYearMonster_h

#include "ZombieAnimRig.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "Projectile.h"
#include "EliteModule.h"
#include "Effect_PopAnim.h"
#include "ProjectilePropertySheet.h"
#include "SexyVector.h"

class ZombieIceYearMonsterProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieIceYearMonsterProps, ZombieWithActionsProps, RtClass);
	ZombieIceYearMonsterProps()
    {
    }
	ProjectilePropertySheetPtr Projectile;
	float restTime;
	float ultimateskillTime;
};



class ZombieIceYearMonster : public Zombie, public ZombieEliteModule{
public:
	RT_CLASS_DEFINE(ZombieIceYearMonster, Zombie, RtClass);
	ZombieIceYearMonster();
	virtual ~ZombieIceYearMonster();

	void recover();
protected:
	virtual void 	onZombieInitialize();
	virtual void	onUpdate();


	bool	WillTargetPlant(Plant* i_plant){return false;}
	virtual BoardEntity *findTarget(){return NULL;}
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }
	virtual void onStartBleeding(){};
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
    DECLARE_STATE_FUNCTIONS(ZombieState, ResilienceEnterBreak);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, ResilienceRecover);
	void onDraw(class Sexy::Graphics* i_g) override;

	void takeBodyDamage(const DamageInfo& i_incomingDamage) override;
    void	setState(int i_action);
	void	onAnimStoppedCallback(const std::string& i_animLabel);
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
	bool	isOnLastColumn();
	void	JumpingTarget(SexyVector3 targetPosition, bool IsAttack);

	BoardEntityPtr	findMaxCostPlant();
	void KillPlant();
	void SetEffectVisibility(bool i_show);
	virtual void onResilienceRecoverAnimStopped(const std::string& i_animLabel) override;

	// class Zombie* spawnZombie(ZombieTypePtr i_zombieType) const;
	// int getSpawningColumn() const
    void spawnGridItem(Point i_gridLocation, GridItemTypePtr i_type, std::string i_spawnAnimationID, std::string i_spawnSoundID);

    void Freezing_Breath();
	void SpawnZombie();
	void UltimateSkill();

	enum actionState
	{
		PreAttack,
		CastSkill,
		SkillOne,
		SkillTwo,
		SkillRest,
		SkillAttack,
		SkillOneEnd,
		SkillReturn,
		SkillThree,
		ResilienceBreak
	};
private:
	void SetDestinationPosition();

private:
	pvztime_t endTime;
	pvztime_t endRest;
	int m_state;
	bool Walkflag;
	bool startEffect;
	SexyVector3 targetPosition;
	SexyVector3 InitialPosition;
	BoardEntityPtr m_target;
    bool SkillFlag;
	float m_endPosX;
	pvztime_t UltimateskillTime;
	bool firstboard;
	bool m_skillretflag;
};

class ZombieAnimRig_IceYearMonster : public ZombieAnimRig
{
public:
	 RT_CLASS_DEFINE(ZombieAnimRig_IceYearMonster, ZombieAnimRig, RtClass);
	 bool PlayTapAnimation(std::string animation ,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};


class IceYearMonsterProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(IceYearMonsterProjectile, Projectile, RtClass);
	virtual void onProjectileInitialized();
	void SetAnimname(std::string i_taganimname);
	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL);
	// void	onAnimStoppedCallback(const std::string& i_animLabel);
	void RotateToward();
	void SetTargetPosition(SexyVector3 i_targetPosition) {m_targetPosition = i_targetPosition;}

	std::string m_idleanimename;
	SexyVector3 m_targetPosition;
};

class Effect_AirflowUp :	public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_AirflowUp, Effect_PopAnim, RtClass);
    Effect_AirflowUp(){}
    void startAirflowUp (SexyVector3 m_position);
protected:
    void playAirflowUp (SexyVector3 m_position);
};

class Effect_AirflowDown :	public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_AirflowDown, Effect_PopAnim, RtClass);
    Effect_AirflowDown(){}
    void startAirflowDown (SexyVector3 m_position);
protected:
    void playAirflowDown (SexyVector3 m_position);
};

class Effect_ZombieIceMove : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_ZombieIceMove, Effect_PopAnim, RtClass);
    Effect_ZombieIceMove(){}
	void Setinstigator(RtWeakPtr<class BoardEntity> i_instigator);
protected:
	virtual void onDestroy() override;
private:
	RtWeakPtr<class BoardEntity> m_instigator;
};

enum GridItemFrostState
{
	PVZ_BEGIN_ENUM(FROSTSTATE_),
	FROSTSTATE_UNKNOWN,
	FROSTSTATE_SPAWNING,
	FROSTSTATE_IDLE,
	FROSTSTATE_FADING,
	FROSTSTATE_DEAD,
	PVZ_END_ENUM(FROSTSTATE_)
};

class GridItemFrost : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemFrost, GridItemAnimation, RtClass);
    GridItemFrost() {}
	int CalcRenderOrder() const override;
	PlantingReason GetCantPlantReason() const;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	void onAnimation(const std::string &i_animName);
	virtual void setState(GridItemFrostState i_state);
	void		GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

private:
    GridItemFrostState m_state;
};

#endif /* ZOMBIE_ICEYEARMONSTER_H_ */
