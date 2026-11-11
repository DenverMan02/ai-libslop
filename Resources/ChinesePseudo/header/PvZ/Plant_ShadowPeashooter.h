#ifndef __PLANT_SHADOWPEASHOOTER_H__
#define __PLANT_SHADOWPEASHOOTER_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "BoardEntity.h"
#include "AnimRigLayerSet.h"
#include "ComponentVisualStretcher.h"
#include "PlantStatefulFramework.hpp"
#include "Effect_PopAnim.h"
#include "Utils.h"
#include "GridItemAnimation.h"

class Zombie;

STATE_ENUM_BASE_BEGIN(ShadowPeashooterState)
    SHADOWPEA_NORMAL,
    SHADOWPEA_STARTING_SINK,
    SHADOWPEA_SINKING,
    SHADOWPEA_HIDING,
    SHADOWPEA_START_SWALLOWING,
    SHADOWPEA_START_STUN,
    SHADOWPEA_STUN,
    SHADOWPEA_SWALLOWING,
    SHADOWPEA_START_SURFACING,
    SHADOWPEA_SURFACING,
    SHADOWPEA_SURFACED,
STATE_ENUM_END(ShadowPeashooterState);

class PlantShadowPeashooter : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantShadowPeashooter, PlantFramework, RtClass);

    bool isBoosted();
    virtual ~PlantShadowPeashooter() {}
    int m_bombTier;    
    
    float GetSkillDamageRate();

protected:
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void onAnimStoppedCallback(const std::string& i_animName) override;
    bool CanBeTargeted() override;
    bool CanBeShoveled() override;
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool CanApplyPlantfood() override;
    void UpdateActions() override;
    void Initialize() override;
    Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool IsInvincible() const override;
    int	GetPlantFoodPlayCount() override;
    
private:
    void AddLayerSet(std::string i_setName, std::vector<std::string> i_layerNames);
    int calcBombTier();
    bool isZombieInFrontOfPlant(ZombiePtr i_zombie);
    void killThisPlant();
    void updateZombiesSwallowed();
    void ShowLayerSet(std::string i_setName);
    void swallowZombie(RtWeakPtr<Zombie> i_zombie);
    void setState(int32_t i_nextState);
    
    bool shouldHideFromZombies(std::vector<BoardEntity*>& i_entities);
    bool shouldSwallowZombie(Zombie* i_zombie);

    void LineShot(bool i_canMakeHole = false);
    void CreateHole(Point i_point);
    
    bool m_isLevel5Attack;
    pvztime_t m_lv5SkillTime;
    int m_zombiesSwallowed;
    AttachedEffectManager m_attachedEffects;
    AnimRigLayerSet m_layerSet;
    std::vector<std::string> m_baseNormalLayers;
    std::vector<std::string> m_baseBoostedLayers;
    int32_t m_currentState;
    RtWeakPtr<Zombie> m_zombieToEat;
    float m_shadowSuckVelocity;
    pvztime_t m_releaseStunTime;
    int m_newAvatarBoostRate;
    bool zombieIsBlacklisted(const Zombie* i_zombie) const; 
};

class PlantAnimRig_ShadowPeashooter : public PlantAnimRig
{
public:

    PlantAnimRig_ShadowPeashooter();
	
	RT_CLASS_DEFINE(PlantAnimRig_ShadowPeashooter, PlantAnimRig, RtClass);

    void SetIsLevel5Attack(bool i_flag){
        m_isLevel5Attack = i_flag;
    }

private:
    virtual std::string getAttackAnimationName() override;

    bool m_isLevel5Attack;
};

////Plant food bomb
class PlantShadowPeashooterBomb : public Projectile
{
public:
    RT_CLASS_DEFINE(PlantShadowPeashooterBomb, Projectile, RtClass);
    
    void InitializeBomb(PlantShadowPeashooter* i_parentPlant, int i_tier);
    
private:
    bool OnCollideGround() override;
    void dealDamage(int i_tier);
    PlantShadowPeashooter* m_parentShooter;
    int m_bombTier; 
};

enum ShadowpeashooterBlackHoleState
{
    PVZ_BEGIN_ENUM(ShadowpeashooterBlackHole_),
    ShadowpeashooterBlackHole_UNKNOWN,
    ShadowpeashooterBlackHole_RESETTING,
    ShadowpeashooterBlackHole_IDLE,
    ShadowpeashooterBlackHole_DEAD,
    PVZ_END_ENUM(ShadowpeashooterBlackHole_)
};

struct SwallowHoleItem
{
    RtWeakPtr<Zombie> m_zombie; 
    pvztime_t m_died;
    float m_suckVelocity;
};

class ShadowpeashooterBlackHole : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(ShadowpeashooterBlackHole, GridItemAnimation, RtClass);

    ShadowpeashooterBlackHole();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ShadowpeashooterBlackHole_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(ShadowpeashooterBlackHoleState i_state);
    void tryAbsorbZombies();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onResetFinished(const std::string &i_animName);
    void onDeadFinished(const std::string &i_animName);
    void onZombieLanding(Zombie *i_zombie);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    ShadowpeashooterBlackHoleState m_state;
    bool m_checkFlag;
    std::vector<SwallowHoleItem> m_zombieVec;
};

class ShadowpeashooterBlackHoleProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(ShadowpeashooterBlackHoleProps, GridItemAnimationProps, RtClass);
    ShadowpeashooterBlackHoleProps()
    : Lifetime(1.0)
    , EffectRectRight(1)
    , EffectRectLeft(1)
    , EffectRectTop(1)
    , EffectRectBottom(1)
    , ElectricDamage(0.0f)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    float ElectricDamage;
};

#endif //__PLANT_PEASHOOTER_H__
