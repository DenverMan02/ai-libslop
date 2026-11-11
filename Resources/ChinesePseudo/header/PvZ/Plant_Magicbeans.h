#ifndef __PLANT_MAGICBEANS_H__
#define __PLANT_MAGICBEANS_H__

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "PlantPropertySheet.h"
#include "ComponentDamageRadius.h"
#include "GameSubSystem.h"

class MagicbeansProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(MagicbeansProps, PlantPropertySheet, RtClass);

    MagicbeansProps()
    {
        NumPlantfoodRockets = 3;
        FireTime = 1.0f;
        PlantfoodFireTime = 0.5f;
        TargetOffset.x = 0;
        TargetOffset.y = 0;
    }

    int NumPlantfoodRockets;
    pvztime_t FireTime;
    pvztime_t PlantfoodFireTime;
    SexyVector2 TargetOffset;

    bool Primal = false;
    int ReadyDecPercent = 0;
    float TimeUntilArmed = 15.f;
    DuplicatableProps DuplicationInformation;
//    ComponentDamageRadiusProps ExplodeRadius;
    
};

class PlantMagicbeans : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMagicbeans, PlantFramework, RtClass);

private:
    enum State
    {
        SELF_STATE_NOTREADY = STATE_FRAMEWORK_BEGIN,
        STATE_RISING,
        STATE_SHAKE,
        STATE_EXPLODING,
        STATE_FLYING,
    };

public:
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    virtual void	Initialize() override;
    virtual void	UpdateActions() override;
    virtual bool	CanApplyPlantfood() override;
    virtual bool	HasShadow() override;
    virtual float	GetShadowScaling() override;
    virtual void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    void onBeThrown() override;
    void onDestroy() override;
    void onBePushed() override;
    void	 onAnimStoppedCallback(const std::string& i_animCommand) override;
    void onKilled(bool i_instantKill) override;
    bool m_killed = false;
    float p_hitpoints;
    PopAnimRig::AnimStoppedReflectionDelegate GetAnimationStopDelegate();
    int myrandom();
    void FallBeans(bool show_animation);
    bool	 IsDelayDestroy() override;
    bool m_invincible = false;
    static bool WhetherCanBePulled(const Plant* i_plant, int i_endCol);
    void SetIsFlying();
    void ForceArming();
    void FlyThroughAir(SexyVector2 i_startPixelLoc, SexyVector2 i_destPixelLoc);
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override
    {
        return (COLLIDE_GROUND_ZOMBIES | COLLIDE_DYING_ZOMBIES);
    }

    virtual bool	OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;

    virtual void 	OnRelocationComplete() override;

    virtual bool 	CanBeShoveled() override;
    bool IsInvincible() const override;
    virtual bool    TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;

    virtual bool	CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void Idle() override;

    void onSetDuplicate(bool i_duplicate) override { };
    void queueShot(pvztime_t i_launchTime, const Point& i_targetLocation, bool bBig = false);

private:
    float m_interval;
    int num_beans;
    bool can_destroy = false;
    int already_beans;
    float shot_T =0;
//    void Explode();
    bool DoDuplicate();
//    bool shouldExplodeBecauseShovedOffBoard(const int i_direction);

//    RtWeakPtr<ComponentDamageRadius> m_explodeRadius;
};

class MagicbeansLauncherSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(MagicbeansLauncherSubSystem, GameSubSystem, RtClass);

    MagicbeansLauncherSubSystem();

    struct MagicbeansLauncherEntry
    {
        MagicbeansLauncherEntry() {}
        MagicbeansLauncherEntry(PlantMagicbeans* i_owner, pvztime_t i_launchTime, const Point& i_target, bool bBig = false);

        //PlantBanana *m_owerPlant;
        PlantPtr Owner;
        RtWeakPtr<const MagicbeansProps> MagicbeansPropertySheet;
        pvztime_t LaunchTime;
        bool m_isLevel5 = false;
        Point Target;
        bool  bIsBig;
    };

    void QueueShot(PlantMagicbeans* i_owner, pvztime_t i_launchTime, const Point& i_target, bool bBig = false);
    void Update() override;
    MagicbeansLauncherEntry* GetLauncherEntry(int i);

private:
    void launch(const MagicbeansLauncherEntry& i_entry);
    std::vector<MagicbeansLauncherEntry> m_shots;

};
class MagicBeansProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(MagicBeansProjectile, Projectile, RtClass);
	bool OnCollideGround() override;
    int myrandom();
};

class MagicbeansshotProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(MagicbeansshotProjectileProps, ProjectilePropertySheet, RtClass);

    MagicbeansshotProjectileProps()
    {
        BounceAngleInRadians = SexyMath::DegToRad(45.0f);
        BounceOutwardTendency = 0.5f;
        BouncesUntilSelfDestruct = 5;
        Bounces4SecondLevel = 6;
        Bounces4ThirdLevel = 7;
        EndingPAM = "POPANIM_EFFECTS_GRAPESHOT_HIT";
    }

    float BounceAngleInRadians;
    float BounceOutwardTendency;
    int BouncesUntilSelfDestruct;
    int Bounces4SecondLevel;
    int Bounces4ThirdLevel;
    std::string EndingPAM;
};

class MagicbeansshotProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(MagicbeansshotProjectile, Projectile, RtClass);

    MagicbeansshotProjectile()
    {
        m_lastRowHit = -1.0f;
        m_numberOfTimesBounced = 0;
    }
    bool OnCollideRoof() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    //bool ShouldClipWithWater() const override { return true; }
    void SetProjectileAnimation();
    Plant* m_plant;

protected:
    void moveThroughTime(pvztime_t i_dt) override;

private:
    float	determineBounceDirection(float i_upChance);
    bool	handleBounceAndReportConsumption();
    void	showHitExplosion(float explosionX, float explosionY);

    int m_lastRowHit;
    int m_numberOfTimesBounced;
};

#endif
