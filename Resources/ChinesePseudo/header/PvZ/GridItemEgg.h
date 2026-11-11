
#ifndef GridItemEgg_hpp
#define GridItemEgg_hpp

#include "RtDb.h"
#include "RtObject.h"
#include "GridItemJammable.h"
#include "ZombieEightiesBasic.h"

class Creature;

class GridItemEggProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemEggProps, GridItemBreakableTargetProps, RtClass);
    
    GridItemEggProps()
    {
        FlyDuration = 0.5;
        TimeDPS = 10;
        DamageInterval = 0.25;
    }
    virtual ~GridItemEggProps() {}
    
    std::string DinoTypeToSpawn;
    pvztime_t FlyDuration;
    float TimeDPS;
    float DamageInterval;
};

enum EggState
{
    PVZ_BEGIN_ENUM(EGGSTATE_),
    EGGSTATE_IDLE,
    EGGSTATE_SWALLOWED,
    EGGSTATE_FLYTODESTROY,
    EGGSTATE_FLY,
    PVZ_END_ENUM(EGGSTATE_)
};

class GridItemEgg : public GridItemBoardEntityConditionTarget
{
public:
    RT_CLASS_DEFINE(GridItemEgg, GridItemBoardEntityConditionTarget, RtClass);
    
    GridItemEgg();
    ~GridItemEgg();
    
    bool		IsDamageableByPlants() const override
				{ return true; }
    void		onGridItemInitialize() override;
    bool IsControlled() const override;

    bool IsDamageable() const override;

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    
    void MoveOverTimeTo(const Sexy::Point& i_gridLocation, pvztime_t i_duration) override;
    Creature * SpawnDino(const std::string & dinoType);
    
    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    void TakeDamage(const DamageInfo& i_damage) override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    bool ShouldDrawShadow() const override;

    
    //Called by outer entities
    void IsSwallowedByEntity(BoardEntity* i_instigator);
    void FlyOutBoard(int i_gridY);
    
    void setState(EggState i_state);
    EggState getState();
    void updateState();
    void onUpdate() override;
    void onDraw(Graphics* i_g) override;
    
    bool CanPushMe();
    void onRollAnimDone(const std::string& i_animLabelName);
    virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
    void FlyThroughAir(SexyVector3 i_startPixelLoc, SexyVector3 i_destPixelLoc);
    void registerForEvents() override;
    void onPostLoad() override;
    void SetLevelHitpoints(int level);
protected:
    Sexy::Rect calcCollisionRect() override;
    void onDrawShadow(class Sexy::Graphics* i_g) override;
    void onTakeDamage(const DamageInfo& i_damage) override;
    void deathAnimDoneHandler() override;
    
    void onBreakAnimDone(const std::string& i_animLabelName);
    void onTurnToAshAnimDone(const std::string& i_animLabelName);
    void onGameplayEnded();
private:
    bool IsInState(uint32 state) const { return m_state == state; }
    void drawEggAnim(Graphics* i_g);
    
    EggState m_state;
    pvztime_t m_flyStartTime;
    pvztime_t m_flyDuration;
    pvztime_t m_flyEndTime;
    SexyVector3 m_flyStartPos;
    SexyVector3 m_flyEndPos;
    float m_rotation;
    bool m_playingSpecialAnim;
    int m_eggDamagePhase;
    pvztime_t m_timeToApplyDamage;
};

class GridItemEggAnimRig : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemEggAnimRig, PopAnimRig, RtClass);
    
    GridItemEggAnimRig();
    
    void PlayIdle();
    void PlayRoll(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayTurnToAsh(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void SetDamageState(int i_damageState);
private:
    int m_damagePhase;
    std::string m_idleAnimName;
};

#endif
