//
//  Plant_SpartanBamboo.h
//  PlantsVersusZombies2
//
//  Created by Sudheer, Alma on 03/10/23.
//  Copyright © 2023 PopCap Games. All rights reserved.
//

#ifndef Plant_BambooSpartan_h
#define Plant_BambooSpartan_h


#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantType.h"
#include "Shield.h"
#include "SexyMatrix.h"  
#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Projectile.h"
#include "ZombieLaneChangingSubsystem.h"
#include "NewPVPUtils.h"
#include "PlantGroup.h"
#include "Effect_PopAnim.h"
#include "PowerSet.h"
class Zombie;

struct KnockbackData
{
    float KnockbackCells;
    float KnockbackHeight;
    float KnockbackTime;
};
enum ShieldType
{
	SHIELD_MAIN,
	SHIELD_SECONDARY
};

class SpartanBambooMatrixSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(SpartanBambooMatrixSystem, GameSubSystem, RtClass);

    struct PlantMatrix{
		std::vector<RtWeakPtr<Plant>>   m_plants;
		pvztime_t				m_cooldown;
        int                     m_serial;
        Sexy::Point             m_point;
        // int                     m_level;
        int                     m_berserker;
        time_t                  m_berserkertime;
        float                   m_damage;
        RtWeakPtr<Effect_PopAnim>         _effect;
        SexyVector3             m_position;
	};  
	SpartanBambooMatrixSystem():m_matrixcount(0)
    {}
    float GetAttackFrequency(int i_isberserker);
    float GetAttackSpeed(float i_attackFrequency);
    int AddMatrix(const std::vector<RtWeakPtr<Plant>> i_plants,const Sexy::Point& i_point, const SexyVector3& i_position,float i_damage);
	void Update() override;
    void RemoveMatrix(int i_serial,const RtWeakPtr<Plant>& i_plant);
    // void ResetCoolDown()
    void againApplyMatrix(const std::vector<RtWeakPtr<Plant>> i_plants, const RtWeakPtr<Plant>& i_plant);
    void SetBerserkerCondition(int i_serial, const RtWeakPtr<Plant>& i_plant);
    void SetPlantBerserkerCondition(int i_serial,int i_isberserker);
    RtWeakPtr<Effect_PopAnim> PlayMatrixEffect(const SexyVector3& i_position);
    std::string getImpactPam() { return "POPANIM_EFFECTS_SPARTANBAMBOO_EFFECT";}
    void OnKillZombie(int i_serial,Zombie* zombie);
    bool HasPlantsCondition(const std::vector<RtWeakPtr<Plant>> i_plants);
private:
    void AttackMatrix(PlantMatrix& i_matrix) ;
    bool FindTarget(const Sexy::Point& i_point);
    Sexy::Point ConfirmZombieTarget(const Sexy::Point& i_point);

private:
    std::vector<PlantMatrix> 		m_matrixs;
    int                     m_matrixcount;
    std::vector<Sexy::Point> m_pointTarget;
    // RtWeakPtr<Effect_PopAnim> _effect;// effect object 

};


class SpartanBambooProps : public PlantPropertySheet
{
    RT_CLASS_DEFINE(SpartanBambooProps, PlantPropertySheet, RtClass);
public:
    SpartanBambooProps()
    {
        InitialCooldownTime = 0.0f;
        PierceMultiplier = 1;
        BattleTranceDamageMultiplier = 100;
        JabDPS = 0;
        TotalHitPoints = 0;
		ProjectileLobHeight = 350.f;
        ProjectileTimeOfFlight = 1.2f;
        ShielHitPoints = 1400;
    }

    float InitialCooldownTime;
    float PierceMultiplier;
    float BattleTranceDamageMultiplier;
    ClassRestrictionSet PierceInclusionList;
    ClassRestrictionSet PFKnockbackExclusionList;
    ClassRestrictionSet SpearAttackKillList;
    KnockbackData KnockbackDetails;
    float JabDPS; //Dummy data for Almanac display
    float TotalHitPoints; //Dummy data for Almanac display
    float ProjectileLobHeight;
	float ProjectileTimeOfFlight;
    float ShielHitPoints;
    float GetPacketCoolDownTime(int iStarLv) const override;
};

enum SpartanBambooState
{
    SPARTANBAMBOOSTATE_INIT = STATE_FRAMEWORK_BEGIN,
    SPARTANBAMBOOSTATE_IDLE,
    SPARTANBAMBOOSTATE_SPEARJAB,     //attack state with shield
    SPARTANBAMBOOSTATE_SPEARREMOTE,     //attack remote target
    SPARTANBAMBOOSTATE_SHIELDBREAK,  //shield break animation
    SPARTANBAMBOOSTATE_BATTLETRANCE, //attack state after shield falls off
    SPARTANBAMBOOSTATE_BATTLEBERSERKER, 
    SPARTANBAMBOOSTATE_BATTLEBERSERKERLOOPEDN, 
    SPARTANBAMBOOSTATE_BATTLEBERSERKEREDN, 
    SPARTANBAMBOOSTATE_PLANTFOOD,     //Slams spear on ground to create shock wave
    SPARTANBAMBOOSTATE_BEGINBERSERKER
};

// enum BerserkerState
// {
//     SPARTANBAMBOOSTATE_BATTLEBERSERKERLOOP, 
//     SPARTANBAMBOOSTATE_BATTLEBERSERKEREDN, 
// };


class PlantSpartanBamboo : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantSpartanBamboo, PlantFramework, RtClass);

    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon)  override;
    bool		FindTargetAndFire(PlantWeapon i_plantWeapon)   {return false;}
    DamageInfo TakeDamage(const DamageInfo &i_damage) override;
    void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void         onAnimStoppedCallback(const std::string& i_labelname) override;

    bool HasShield();
    bool CanBeHealed();
    Shield* GetShield(){ return m_shield.Get(); }
    void onDestroy() override;

private:
    bool findTargets(Sexy::Rect i_searchRect,bool i_hasremote = false);
    bool targetInAttackArea();
    bool RemoteAttackTarget();
    ZombiePtr ConfirmZombieTarget();
    std::vector<BoardEntity*> getJabTargets();
    DamageInfo getDamageInfo(PlantWeapon i_weapon);
    void onAnimComplete(const std::string &i_animName);
    void onRemoteAnimComplete(const std::string &i_animName);
    void onRemoteLoopAnimComplete(const std::string &i_animName);
    void onJabAnimComplete(const std::string &i_animName);
    // bool isSpecialTarget(BoardEntity* i_entity);
    // bool canKill(const Zombie* i_zombie);
    void dealDamage();
    void plantfoodDamage();
    SpartanBambooState getState();
    PlantWeapon getWeapon();
    void tryKnockbackZombie(Zombie* i_zombie);
    bool CanZombieLaunch(Zombie* i_zombie);
    bool canKnockbackZombie(Zombie* i_zombie);
    void breakShield();
    void createEffect(std::string i_effectName, SexyVector3 i_position);
    int SearchUDPlant(std::vector<RtWeakPtr<Plant>>& i_plants);
    int SearchLRPlant(std::vector<RtWeakPtr<Plant>>& i_plants);
    void ApplyMatrix(const std::vector<RtWeakPtr<Plant>> i_plants, int matrixcount);
    virtual Projectile *Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual void OnKillZombie(Zombie* i_zombie);
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    virtual int		GetPlantFoodPlayCount()		override;								
	void onApplyCondition(PlantConditions i_condition) override;
	virtual void onEndCondition(PlantConditions i_condition) override;
    void onWatered(bool watered) override;
	void OnRelocationBegun() override;
    
    pvztime_t m_initialCooldown = PVZ_EOT();
    pvztime_t m_jabCooldown = PVZ_EOT();
    pvztime_t m_spearremoteCooldown = PVZ_T();
    RtWeakPtr<Shield> m_shield;
    bool m_shieldBroken = false;
    bool m_berserker = false;
    pvztime_t m_berserkerTime;
	RtWeakPtr<SpartanBambooMatrixSystem> 	m_matrixsystem;
    uint _m_state;
    bool _end_berserker = false;
    int m_remote_count = 0;
    bool m_remoteharm = true;
public: 
    // void Sethelmetlayer(bool i_hasbattlearray) { GetAnimRig()->SetLayerVisibility("helmet",i_hasbattlearray);}
    void SetBattLearrayState(bool i_battlearray); 
    void SetSerial(int i_serial) {m_serial = i_serial;}
    bool CanMatrixCondition();
    void SetBerserkerCondition(bool i_isberserker,pvztime_t i_berserkerTime = PVZ_EOT());
    void calculatecooldown();
    void MatrixAttack();
    void Cancelmatrixbuff();
    bool GetBerserkercondition() {return m_berserker;}
    void setState(const uint i_state);
    void setremotecount(int i_count) {m_remote_count =  i_count;}
    void HasRemoteharm(bool i_remoteharm) {m_remoteharm =  i_remoteharm;}
    void Matrixberserker();
    bool isSpecialTarget(BoardEntity* i_entity);
    bool canKill(const Zombie* i_zombie);
    RtWeakPtr<Plant> CanPlantType(Sexy::Point i_Pos,int x, int y);

    // void SetplantfooddamageAvatar(bool i_avatar) {m_avatar = i_avatar;}
    // bool m_avatar = false;

    bool m_battlearray = false;
    int  m_serial;
    float m_berserkerattackcooldown;
    float m_maxhealth;
};

class SpearProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(SpearProjectileProps, ProjectilePropertySheet, RtClass);
    
    SpearProjectileProps()
    {
        burntime = 5.0f;
        Vulnerable = 0.1f;
        oiltime  = 15.0f;
    }
    float Vulnerable;
    float burntime;
    float oiltime;

};

class SpearProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(SpearProjectile, Projectile, RtClass);
    // bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;
    // virtual bool OnCollideEntity(BoardEntity* i_entity) override;

	// void onProjectileInitialized() override;
	virtual void onUpdate(pvztime_t i_dt) override;
    // virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL);
public:
    void SetPlant(RtWeakPtr<Plant> i_plant) { m_impactedplant = i_plant;}
private:
    RtWeakPtr<Plant> m_impactedplant;
protected:

};


enum PlantAnimRigState_SpartanBamboo
{
    PLANTANIM_SpartanBamboo_SHIELDING = PLANTANIM_USERDEFINED,
};

class PlantAnimRig_SpartanBamboo : public PlantAnimRig_Shielded
{
    RT_CLASS_DEFINE(PlantAnimRig_SpartanBamboo, PlantAnimRig_Shielded, RtClass);
public:
    int GetArmorStateCount();
    void SetArmorStateIndex(int i_index) ;
	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

    bool PlayIdle(bool i_shieldUp);
    void SetHasShield(bool i_hasShield) { m_hasShield = i_hasShield;}
    void SetHasBerserker(bool i_berserker) { m_berserker = i_berserker;}
    AnimHandle PlayJabAnimation(AnimStoppedDelegate i_onAnimStopped, bool i_shieldUp);
    AnimHandle PlayremoteAnimation(AnimStoppedDelegate i_onAnimStopped, bool i_shieldUp);
    bool PlayremoteLoopAnimation(std::string i_animLabel,AnimStoppedDelegate i_onAnimStopped);
    AnimHandle PlayShieldBreakAnimation(AnimStoppedDelegate i_onAnimStopped,bool i_hasBerserker);
    AnimHandle PlayBeginBerserkerAnimation(AnimStoppedDelegate i_onAnimStopped);
    AnimHandle PlayEndBerserkerAnimation(AnimStoppedDelegate i_onAnimStopped);
    void Hashelmet(bool HasPlantMatrix) {}
	virtual bool playPlantFoodMain()override;
    void Setplantfood_count(int i_count) { m_plantfood_count = i_count;}
private:
    void onPopAnimInitialized() override;
    std::string getPlantFoodMainAnimName() override;
    bool m_hasShield = true;
    bool m_berserker = false;
    int  m_plantfood_count = 2;
};

enum GridItemspearState
{
	PVZ_BEGIN_ENUM(SPEARSTATE_),
	SPEARSTATE_UNKNOWN,
	SPEARSTATE_SPAWNING,
	SPEARSTATE_IDLE,
	SPEARSTATE_FADING,
	SPEARSTATE_DEAD,
	PVZ_END_ENUM(SPEARSTATE_)
};

class GridItemspear : public GridItemAnimation
{
public:

	RT_CLASS_DEFINE(GridItemspear, GridItemAnimation, RtClass);
    GridItemspear()
    {}
    struct AttackMatrix{
		int                         m_serial;
		float				        m_attackspeed;
        float                           m_damage;
        int                          m_attackcount;
        pvztime_t                      m_cooldown;
		std::vector<RtWeakPtr<Plant>>   m_plants;

	}; 
	int CalcRenderOrder() const override;

protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	virtual void setState(GridItemspearState i_state);

protected:  
    void causeDamage(AttackMatrix& i_plantmatrix);
	void onAnimation(const std::string &i_animName);

public:
    // void SetDamage(float i_damagePerSecond) { DamagePerSecond = i_damagePerSecond;}
    void SetPlantMatrix(int i_serial, float i_attackspeed, float i_damage, int i_attackcount,std::vector<RtWeakPtr<Plant>> i_plants);
private:
	Sexy::Point _position;// water mist grid position
    GridItemspearState m_state;
	std::vector<AttackMatrix>   m_lifematrix;
};

class GridItemspearrainProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemspearrainProps, GridItemAnimationProps, RtClass);
    GridItemspearrainProps()
    {}
public:
    
};
#endif /* Plant_BambooSpartan_h */
