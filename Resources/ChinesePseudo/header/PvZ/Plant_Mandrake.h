

#ifndef __PLANT_MANDRAKE_H__
#define __PLANT_MANDRAKE_H__

#include "PlantFramework.h"
#include "PopAnimRig.h"
#include "PlantAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Projectile.h"
#include "ZombieLaneChangingSubsystem.h"
#include "NewPVPUtils.h"
#include <vector>
#include"SexyMatrix.h"  
STATE_ENUM_CHILD_BEGIN(MandrakeState, PlantState)
    MANDRAKESTATE_IDLE,
    MANDRAKESTATE_IDLELEVEL,
    MANDRAKESTATE_ATTACK,
    MANDRAKESTATE_ATTACKLOOP,
    MANDRAKESTATE_GROW,
    STATE_PLANTFOOD_READY,
    STATE_ENUM_END(MandrakeState)

class PlantMandrakeProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantMandrakeProps, PlantPropertySheet, RtClass);

    PlantMandrakeProps():ProjectileLobHeight(325.f),ProjectileTimeOfFlight(1.2f)
    {
        PhantomRate = 0.3f;
        PhantomLevelRate = 0.6f;
        PlantRecoverTime = 8.0f;

    }

    float PhantomRate;
    float PhantomLevelRate;
    float PlantRecoverTime;
    float ProjectileLobHeight;
    float ProjectileTimeOfFlight;
};



class MandrakeProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(MandrakeProjectileProps, ProjectilePropertySheet, RtClass);
    
    MandrakeProjectileProps()
    {
        ProjectileLobHeight = 325.0f;
        ProjectileTimeOfFlight = 1.2f;
        PropertyReductionMultiplierPerBounce = 0.75;
        StunDuration = 0.5;
    }

    float ProjectileLobHeight;
    float ProjectileTimeOfFlight;
    float PropertyReductionMultiplierPerBounce;
    float StunDuration;
    // float InitialExtraVelocitySeconds;
    CurveType InitialExtraVelocityCurve = CURVE_LINEAR;
};

class PlantMandrake : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMandrake, PlantFramework, RtClass);

    void Initialize() override;
    void UpdateActions() override;

    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    void UpdatePlantfood() override;

    void onPlantfoodStarted() override;
    virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile *Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    void         SetState(const uint i_state);
    void         onAnimStoppedCallback(const std::string& i_labelname) override;
    int         alterAttackAnime();
    bool         FindZombie();
    Projectile*  onPlantfoodTrigger();
    void SetLayerNames();
	virtual bool HasShadow()  { return false; }
    virtual void Idle();
private:
    pvztime_t m_idleCoolDown;
    pvztime_t m_idleCoolDownEnd;
    int  m_tossmaxLevel;
    bool m_isAvatarSecondAttack = false;
    bool m_canfire;
    char m_Level5AttackCount;
    char m_attackanim;
public:
    std::vector<std::string> i_layerNames_Lv2_on;
    std::vector<std::string> i_layerNames_Lv1;
    std::vector<std::string> i_layerNames_Lv5;
    std::vector<std::string> i_layerNames_Lv2_off;
    std::vector<std::string> i_layerNames_Lv5_grow;
    std::vector<std::string> i_layerNames_Lv5_growon;
    std::vector<std::string> i_layerNames_Lv5_growoff;
    std::vector<std::string> i_layerNames_Lv5_attack;
};

class PlantAnimRig_Mandrake : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Mandrake, PlantAnimRig, RtClass);

    PlantAnimRig_Mandrake():i_idleTag("idle")
    {
    }

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	virtual void onPopAnimInitialized();
    void SetPlant(RtWeakPtr<Plant> i_plant)  {m_waternut  = i_plant; }
    void setIdleTag(const std::string& i_tag) { i_idleTag = i_tag; }
    virtual std::string getIdleAnimationName() override;
    virtual std::string getWaterAnimName() { return "whatr"; }
    bool PlayRecoverLooped();

    std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;

private:
    std::string i_idleTag;
	RtWeakPtr<Plant> m_waternut;
public:
    std::vector<std::string> i_layerNames_Lv2_on = {"003","005"};
    std::vector<std::string> i_layerNames_Lv5_attack = {"024","025","026","027","028","029","030","031","032","033","036","034","035","037","038","039","040","041","042","043","044"};
    std::vector<std::string> i_layerNames_Lv5 = {"001","002","004","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024"};

};  


class ParkourProjectile : public Projectile
{
public:
    enum ParkourState
    {
        PARKOUR_JUMP,
        PARKOUR_SLIDING,
        PARKOUR_RUN,
        PARKOUR_LOOP
    };
    RT_CLASS_DEFINE(ParkourProjectile, Projectile, RtClass);

    ParkourProjectile():m_state(PARKOUR_RUN),StunDuration(0.5f),damageflag(false),jumpend(false),AttackStateFlag(0),AttackEnd(0)
    {}
	void onProjectileInitialized() override;
    bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    BoardEntity* findNextTarget(int i_row,int newx);
    BoardEntity* findNearestTargetType(BoardEntityTypeFlag i_flag, int i_row,int m_Width,float newx);
	virtual void onUpdate(pvztime_t i_dt) override;
	void SetInitialLaunchValues(float i_height, float i_timeToTarget, int i_row);
    virtual void onAnimStoppedCallback(const std::string& i_labelname);
    void DoBounce();
    void JumpEffect(BoardEntity* i_impactedEntity);
    void stunZombie(Zombie *i_zombie,	float stunedRate = 1.0f);
    bool canZombieLaunch(Zombie* zombie);
    void SetAttackStateFlag(int flag) { AttackStateFlag = flag;}
    void SetAttackEnd(bool flag)  {AttackEnd = flag;}

    bool damageflag;
    float m_initialLobHeightThisBounce;
    int m_rowBeingFiredAt;
	float m_initialTimeOfFlightThisBounce;
    float m_reductionRatio;
	float m_targetingRadius;
    float StunDuration;
    bool jumpend;
    std::vector<BoardEntity*>	m_targetsAlreadyHit;
    SexyVector3 normalAcceleration;
    SexyVector3 normalVelocity;
    SexyVector3 normalPos;
    ParkourState m_state;
    int AttackStateFlag;
    bool AttackEnd;
};

class mutationParkourProjectile : public ParkourProjectile
{
public:

    RT_CLASS_DEFINE(mutationParkourProjectile, ParkourProjectile, RtClass);
    mutationParkourProjectile():m_drawcount(0)
    {}
    std::vector<SexyTransform2D> transforms;
    // SexyTransform2D transform_01;
    // SexyTransform2D transform_02;
    int m_drawcount;
    // virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;

    void onDraw(Sexy::Graphics* i_g) override;
};

class PhantomParkourProjectile : public mutationParkourProjectile
{
public:
    PhantomParkourProjectile():attackflag(true)
    {
        m_startTime = PVZ_T();
    }
    RT_CLASS_DEFINE(PhantomParkourProjectile, mutationParkourProjectile, RtClass);
    bool                handleImpact(BoardEntity* i_impactedEntity = nullptr) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual void onUpdate(pvztime_t i_dt) override;
    void moveZombieByRows(Zombie* i_zombie, int numRows);
    void PhantomEffect();
    void TossAndDamage();
    // void SetlayerNames_Lv5_attack();
    // void moveThroughTime(pvztime_t i_dt) override;
    //    float calcLerpVelocity();
    // float i_PhantomRate;
    // float i_PhantomLevelRate;
    bool attackflag;
    pvztime_t m_startTime;
    SexyVector3 attackPosend;
    std::vector<BoardEntity*> m_zombietargets;
    std::vector<BoardEntity*>	m_targetsHit;
    std::vector<std::string> i_layerNames_Lv2_on = {"003","005"};
    std::vector<std::string> i_layerNames_Lv2_off =  {"y02","y01"};
    std::vector<std::string> i_layerNames_Lv1 = {"zuojiao","y08","y07"," y09","y10","y11","shenti_01","shenti_02","shenti_03","shenti_04","youjiao","zui01","m1","m2","y05","y06","y4","y3","y01","y02","shenti03","shenti02"};
    std::vector<std::string> i_layerNames_Lv5 = {"001","002","004","006","007","008","009","010","011","012","013","014","015","016","017","018","019","020","021","022","023","024"};
    std::vector<std::string> i_layerNames_Lv5_attack = {"024","025","026","027","028","029","030","031","032","033","034","035","037","038","039","040","041","042","043","044"};
};

class ParkourPlantfoodProjectile : public Projectile
{
    RT_CLASS_DEFINE(ParkourPlantfoodProjectile, Projectile, RtClass);
    ParkourPlantfoodProjectile():m_plantLevel(1)
    {}
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void SetLevel(int i_plantLevel) {m_plantLevel = i_plantLevel;}
    std::vector<BoardEntityPtr> m_hitted;
    int m_plantLevel;
};
class ParkourPlantfoodAvatarProjectile : public ParkourPlantfoodProjectile
{
    RT_CLASS_DEFINE(ParkourPlantfoodAvatarProjectile, ParkourPlantfoodProjectile, RtClass);
    ParkourPlantfoodAvatarProjectile():m_plantLevel(1)
    {}
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    // void SetLevel(int i_plantLevel) {m_plantLevel = i_plantLevel;}
    int m_plantLevel;
};
#endif //__PLANT_MANDRAKE_H__
 
