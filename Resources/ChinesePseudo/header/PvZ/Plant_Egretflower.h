#ifndef PLANT_EGRETFLOWER_H_
#define PLANT_EGRETFLOWER_H_

#include "Plant.h"
#include "Projectile.h"
#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "Precompile.h"
#include "GridItemAnimation.h"

#pragma mark - EgretflowerProps

class EgretflowerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(EgretflowerProps, PlantPropertySheet, RtClass);

    EgretflowerProps()
    :LoadingTime(8)
    ,LoadingTimeDecrease(4)
    ,UnionMaxNumber(3)
    ,UnionAttackIncrease(0.1)
    ,MaxMissileNumber(2)
    {

    }

    int MaxMissileNumber;
    int UnionMaxNumber;
    float UnionAttackIncrease;
    float LoadingTime;
    float LoadingTimeDecrease;
};

#pragma mark - PlantEgretflowerEnum

enum PlantEgretflowerEnum
{
	EGRETFLOWER_IDLE = STATE_FRAMEWORK_BEGIN,
	EGRETFLOWER_STATE_DESTROY
};

#pragma mark - PlantEgretflower

class PlantEgretflower : public PlantFramework
{
public:
RT_CLASS_DEFINE(PlantEgretflower, PlantFramework, RtClass);

    PlantEgretflower();

	virtual void			Initialize() override;
    virtual void			UpdateActions() override;
    virtual bool            IsInvincible() const override;

    virtual bool 			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	virtual void			CancelPlantfood() override;

    virtual void            onDestroy() override;
    virtual bool            OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void            onAnimStoppedCallback(const std::string& i_anim) override;

    virtual DamageInfo      TakeDamage(const DamageInfo& i_damage) override;
private:
    bool                    canAutoTrigger() const;
    void                    UpdateUnionState();
    void                    SetIsUnion(bool i_flag);

    float                   GetLoadingTime();
    PlantWeapon             GetPlantNormalWeapon();

    bool                    m_isUnion;
    int                     m_prevUnionCount;
    int                     m_attackMode;
    int                     m_missileNum;
    pvztime_t               m_nextMissile;
    RtWeakPtr<Effect_PopAnim>   m_linkingEffect;
    std::vector<Sexy::Point>    m_targets;
};

class EgretflowerCountSubSystem : public GameSubSystem
{
public:
RT_CLASS_DEFINE(EgretflowerCountSubSystem, GameSubSystem, RtClass);

    EgretflowerCountSubSystem();

    int GetEgretflowerNum();
    void EgretflowerAdd();
    void EgretflowerRemove();

private:
    int m_count;
};

#pragma mark - PlantAnimRig_Egretflower

class PlantAnimRig_Egretflower : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Egretflower, PlantAnimRig, RtClass);

    PlantAnimRig_Egretflower();

    void SetAttackMode(int i_attackMode);

protected:
    virtual std::string getAttackAnimationName() override;
    virtual void onAnimStopped() override;

private:
    int m_attackMode;
};

#pragma mark - EgretflowerMissileProps

class EgretflowerMissileProps : public ProjectilePropertySheet
{
public:
RT_CLASS_DEFINE(EgretflowerMissileProps, ProjectilePropertySheet, RtClass);

    EgretflowerMissileProps()
    :StunDuration(1)
    {

    }

    float StunDuration;
};

#pragma mark - EgretflowerNormalProjectile

class EgretflowerNormalProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(EgretflowerNormalProjectile, Projectile, RtClass);

    EgretflowerNormalProjectile();

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    bool isAreaDamage;
};

#pragma mark - EgretflowerMissileProjectile

class EgretflowerMissileProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(EgretflowerMissileProjectile, Projectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

};

#pragma mark - EgretflowerBomb

class EgretflowerBomb : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(EgretflowerBomb, GridItemAnimation, RtClass);

    void SetPlant(PlantPtr i_ptr);
    void StartEffect();

    virtual int CalcRenderOrder() const override;
protected:
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    void onAnimationDone(const std::string& i_labelName);
    PlantPtr m_plantPtr;
};

#pragma mark - EgretflowerPlane

class EgretflowerPlane : public BoardEntity
{
public:
    RT_CLASS_DEFINE(EgretflowerPlane, BoardEntity, RtClass);

    EgretflowerPlane();
    virtual ~EgretflowerPlane();
    
    void                initialize(const Sexy::Point& i_target);
    void                setData(bool i_avatard, float i_damageRate);
    virtual void        onUpdate() override ;
    virtual void        onDestroy() override;
protected:
    void                onArrive();
    bool                m_avatared;
    float               m_speed;
    float               m_damageRate;
    Sexy::Point         m_targetPoint;
    StandaloneEffectPtr m_renderEffect;
};

#pragma mark - EgretflowerPlantFoodBomb

class EgretflowerPlantFoodBomb : public Projectile
{
public:
    RT_CLASS_DEFINE(EgretflowerPlantFoodBomb, Projectile, RtClass);
    EgretflowerPlantFoodBomb();
    ~EgretflowerPlantFoodBomb();
    
    void SetAvatared(bool i_avatared);
    void SetDamageRate(float i_damage);
	void SetGridPosition(int i_x, int i_y);
    
protected:
    virtual bool handleImpact(BoardEntity* i_impactedEntity) override;
	void onDestroy() override;

private:
    void onBomb();
    bool m_avatared = false;
    float m_damageRate = 0.f;
	Point m_targetPoint;
};

#pragma mark - EgretflowerPlantFoodFire

enum EgretflowerFireState{
	PVZ_BEGIN_ENUM(EgretflowerFireSTATE_),
	EgretflowerFireSTATE_UNKNOWN,
	EgretflowerFireSTATE_SPAWNING,
	EgretflowerFireSTATE_IDLE,
	EgretflowerFireSTATE_DISAPPEAR,
	EgretflowerFireSTATE_DEAD,
    PVZ_END_ENUM(EgretflowerFireSTATE_)
};

class EgretflowerPlantFoodFire : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(EgretflowerPlantFoodFire, GridItemAnimation, RtClass);

    EgretflowerPlantFoodFire();

    virtual int CalcRenderOrder() const override;

    void InitFire(const DamageInfo& i_damageInfo);

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    void setState(EgretflowerFireState i_state);
    void onAnimationDone(const std::string& i_tabel);
private:
    void takeEffect();
    EgretflowerFireState m_state;
    float m_duration;
    DamageInfo m_damageInfo;
    pvztime_t m_endTime;
    pvztime_t m_updateTime;
    RtWeakPtr<class Effect_PopAnim> m_effect;
};

#endif