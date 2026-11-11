#ifndef __PlantsVersusZombies2__Plant_PhatBeet__
#define __PlantsVersusZombies2__Plant_PhatBeet__

#include "Plant.h"
#include "Zombie.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "DamageInfo.h"
#include "ComponentDamageRadius.h"
#include "PlantPropertySheet.h"

class PhatBeetProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PhatBeetProps, PlantPropertySheet, RtClass);
    PhatBeetProps();
	
    float PowerfulAttackRatioMin;
    float PowerfulAttackRatioMax;
    float LvPowerfulAttackRatioMin;
    float LvPowerfulAttackRatioMax;

	float Lvl5DotDuration;
	float Lvl5DotDamage;
	float Lvl5StunDuration;
	float Lvl5Cd;
	float Lvl5TargetZombieLevel;
};

struct DotStruct
{
	ZombiePtr m_zombie;
	pvztime_t m_endTime;
};

class PlantPhatBeetDotSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantPhatBeetDotSystem, GameSubSystem, RtClass);
	
	PlantPhatBeetDotSystem();
	virtual ~PlantPhatBeetDotSystem();

	void SetData(float i_damageAmount, float i_timeDuration);

	void AddZombie(ZombiePtr i_zombie);
	void Update() override;

private:
	std::vector<DotStruct> m_dotList;
	pvztime_t m_timeTakeDamage;
	float m_damageAmount;
	float m_timeDuration;
};

class PlantPhatBeetTossSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PlantPhatBeetTossSystem, GameSubSystem, RtClass);
	PlantPhatBeetTossSystem();

    void TossZombies(Zombie* i_zombie);
	void onFlyingEnd(Zombie* i_zombie);
	void setStunTime(float i_time);
private:
	float m_time;
};

class PlantPhatBeet : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPhatBeet, PlantFramework, RtClass);
    
	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override { return true; }
    void ApplyPlantfood() override;
	void CancelPlantfood() override;
    
    void NotifyDamagedEntity(BoardEntity *entity) override;
    bool TryApplyDamageToEntity(DamageInfo &damageInfo, BoardEntity *entity) override;
	
protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
    void tossZombie(Zombie* i_zombie);
	
private:
	enum State
	{
		STATE_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_PLANTFOOD_ATTACK,
		STATE_ATTACKING,
		STATE_ATTACKLVL5,
	};
    
	void setState(const uint i_state);
	bool shouldStartAttack();
	bool isCurrentlyPowerfulAttack();
	void calculateAttacksUntilNextPowerful();
	void calculateNextAttack();
	void setTypeOfAttackToMake();
	void makeNextAttackPowerful();
	void makeNextAttackNormal();
	void doBasicAttack();
	void doLvl5Attack();
	bool canPullHelmFrom(Zombie *i_zombie) const;
    void calcRealDamage(ComponentDamageRadiusProps &damageRadiusProps);

	int       m_attacksUntilPowerful;
	pvztime_t m_timeOfNextAttack;
    bool m_isAvatarPfAttack;
	RtWeakPtr<ComponentDamageRadius> m_damageRadius;
	RtWeakPtr<ComponentDamageRadius> m_plantfoodDamageRadius;
	RtWeakPtr<ComponentDamageRadius> m_Lvl5DamageRadius;
	RtWeakPtr<PlantPhatBeetDotSystem> m_dotSystem;
	pvztime_t m_timeAttackLvl5;
	bool m_isLvl5Attack;
};

class PlantAnimRig_PhatBeet : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_PhatBeet, PlantAnimRig, RtClass);
	PlantAnimRig_PhatBeet();
	
	void setAttackTag(const std::string& i_tag);
    virtual std::string getAttackAnimationName() { return m_attackTag; }
private:
	std::string m_attackTag;
};

#endif /* defined(__PlantsVersusZombies2__Plant_PhatBeet__) */
