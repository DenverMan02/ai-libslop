//
//  Plant_Sarracenia.h
//  PlantsVersusZombies2
//  create by lfy

#ifndef __PLANT_SARRACENIA_H__
#define __PLANT_SARRACENIA_H__


#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GameSubSystem.h"

////////////////////////////////////////
/// LancerHoyaProps
////////////////////////////////////////
class PlantSarraceniaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantSarraceniaProps, PlantPropertySheet, RtClass);

	PlantSarraceniaProps()
	{
		ThrowSnakeCoolDown = 3.0f;
		SpecialChargeDuration = 20.0f;
		SpecialChargeDuration2 = 17.5f;
		SpecialChargeDuration3 = 15.0f;
		ZombieFlickOffDuration = 1.5f;
		BaseDamage = 90.0f;
		Level5ExtraDamage = 500.0f;
		PlantfoodBaseDamage = 100.0f;
        AvatarPlantFoodPlayCount = 0;
        StunnedDuration = 0.0f;
        ActiveSkillsChargeDuration = 0.0f;
        ActiveSkillsLv2ChargeDuration = 0.0f;
        ActiveSkillsLv3ChargeDuration = 0.0f;
        Lv5Rate = 0.0f;
	}
	pvztime_t ThrowSnakeCoolDown;
	pvztime_t SpecialChargeDuration;
	pvztime_t SpecialChargeDuration2;
	pvztime_t SpecialChargeDuration3;
	pvztime_t ZombieFlickOffDuration;
	float BaseDamage;
	float Level5ExtraDamage;
	float PlantfoodBaseDamage;
	ZombieRestrictionSet CannotBeSpeicalHit;// only for not level5
    int AvatarPlantFoodPlayCount;
    float StunnedDuration;
    pvztime_t ActiveSkillsChargeDuration;
    pvztime_t ActiveSkillsLv2ChargeDuration;
    pvztime_t ActiveSkillsLv3ChargeDuration;
    ZombieRestrictionSet SpecialZombieList;
    ZombieRestrictionSet ImpZombieList;
    float Lv5Rate;
};

////////////////////////////////////////
/// PlantSarracenia
////////////////////////////////////////
class PlantSarracenia : public PlantFramework
{
public:
	enum Sarracenia
	{
		STATE_SARRACENIA_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_THROW_SNAKE,
		STATE_SPECIAL_ATTACK,
		STATE_TURN_TO_SPECIAL,
	};
	RT_CLASS_DEFINE(PlantSarracenia, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdateActions() override;
	Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	bool IsInSpecialStatus();
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    // virtual void	Draw(Graphics* g);
    BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) { return ENTITYTYPE_ZOMBIE; }

protected:
	void setState(uint i_plantState);
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

	void UpdateStatus();
	bool onTouchEvent(const Sexy::Touch& i_touch);
    void onCancelEvent();
	pvztime_t CalcSpecialChargeDuration();

    void pfPetrifiedZombies(int zombieCount);
    void normalPetrifiedZombies(int zombieCount);
    bool canBePetrified(Zombie* zombie);
    bool canBeStunned(Zombie* zombie);
    void playNormalLaserEffect(Zombie* zombie, const std::string& i_popAnimName);
    // void playSpecialLaserEffect(Zombie* zombie, const std::string& i_popAnimName);
    // void playPfEffect();
    // void playEyesEffect(BoardEntity* i_entity);

    void createPetrifiedGrid(Zombie* zombie, bool isHalfDamage);

    bool checkHasZombieInRight();
    void getPFAttackTargets(std::vector<BoardEntity*>& targets);
    void getAvatarPFAttackTargets(std::vector<BoardEntity*>& targets);
    void getPFTargets(std::vector<BoardEntity*>& targets);

    std::string getFossilTypeName(Zombie* i_zombie);

protected:
	pvztime_t m_specialStatusStartTime;// special status time
	bool m_inSpecialStatus;
    Rect m_collisionRect;

    bool m_isMiniBoard;
    int m_doPetrifiLevel = 0;
    pvztime_t m_activeSkillTime;        
    float m_lv5Rate;
    bool m_canFire;
    Sexy::TouchID	m_touchIdent;    
};


////////////////////////////////////////
/// PlantAnimRig_Sarracenia
////////////////////////////////////////
class PlantAnimRig_Sarracenia : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Sarracenia, PlantAnimRig, RtClass);

	void SetPlantPtr(PlantPtr ptr) { m_plantPtr = ptr; }
    bool PlaySpecialAttack(const std::string& i_animName, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
protected:
	void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
    std::string getPlantFoodMainAnimName() { if (m_bAvatar) return "pf2"; else return "pf1"; }

protected:
    PlantPtr m_plantPtr;
};

class ViperProjectileProp : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(ViperProjectileProp, ProjectilePropertySheet, RtClass);
    ViperProjectileProp()
    {
        KeepMaxAliveDurations = 0.0f;
        AppendDuration = 0.0f;
        PoisonDuration = 0.0f;
        PoisonDamage = 0.0f;
    }
    float KeepMaxAliveDurations;
    float AppendDuration;
    float PoisonDuration;
    float PoisonDamage;
};

class ViperProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ViperProjectile, Projectile, RtClass);
    void onPosionPlant(class PlantGroup* group);
    // bool OnCollideEntity(BoardEntity* i_entity) override;
    bool HandleImpact(BoardEntity* i_impactedEntity = NULL);

protected:
    virtual void damageEntity(class BoardEntity* i_entity) override;
    bool findTagetZombie(std::vector<BoardEntity*> i_target);
   bool handleImpact(BoardEntity* i_impactedEntity = NULL) { return false; }
private:
    std::vector<PlantPtr> m_poisonousPlants;
    std::vector<BoardEntity*> m_targetZombies;
    int m_poisonousPlantCnt = 0;
    bool m_collideEntity = false;
    float m_searchRadius = 0.0f;
    // SexyVector2 m_serchLocation;
};

#endif /* PLANT_LANCERHOYA_H_ */
