/*
 * ZombieCarnieMagician.h
 *
 *  Created on: 2022-10-8
 *      Author: zhousen
 */

#ifndef ZOMBIEMAGICHAT_H_
#define ZOMBIEMAGICHAT_H_

#include "Precompile.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "Projectile.h"
#include "ZombieAnimRig.h"
#include "GridItemBreakableTarget.h"
#include "ZombieWithActions.h"
#include "ZombiePirateParrot.h"
#include "ZombieAnimRig_Parrot.h"

// Griditem Magichat
class GridItemMagichatProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemMagichatProps, GridItemBreakableTargetProps, RtClass);

    GridItemMagichatProps()
	{
	}
};

class GridItemMagichat : public GridItemBreakableTarget
{
public:
    RT_CLASS_DEFINE(GridItemMagichat, GridItemBreakableTarget, RtClass);

    GridItemMagichat();

    virtual int CalcRenderOrder() const override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;
    virtual bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }
	virtual void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) const override;
	virtual void KillGridItem() override;

	void SetDuration(pvztime_t time);
	void SetLevel(int level);

protected:
	virtual void onUpdate() override;
    virtual void onGridItemInitialize() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

    void GenerateZombie();

protected:
    pvztime_t m_lifeEndTime;
    pvztime_t m_spawnTimeInterval;
    int m_currentLevel;
};

// zombie
class ZombieCarnieMagicianProps : public ZombieWithActionsProps
{
public:
    RT_CLASS_DEFINE(ZombieCarnieMagicianProps, ZombieWithActionsProps, RtClass);

    float TeleportOtherStartTime = 0.f;
    float TeleportSelfStartTime = 5.f;
    float DoveSpawnStartTime = 10.f;

    float TimeBetweenTeleportOther = 10.f;
    float TimeBetweenTeleportSelf = 5.f;
    float TimeBetweenDoveSpawn = 15.f;
    float TeleportationFailPercentage = 50.f;
    PlantRestrictionSet ImmuneToPlantRestrictionSet;
    pvztime_t DisappearDuration = 15.0f;
};

class ZombieCarnieMagician : public ZombieWithActions
{
public:
    enum MagicianActionStatus
    {
        TELEPORT_OTHER,
        TELEPORT_SELF,
        SPAWN_DOVE,
        NO_ACTION
    };

    RT_CLASS_DEFINE(ZombieCarnieMagician, ZombieWithActions, RtClass);

protected:
    void onZombieInitialize() override;
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    bool isImmuneToShrinking() override { return true; }
    void EMPeachStun(pvztime_t i_time) override { }
    void onApplyCondition(ZombieConditions i_condition) override;
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;

protected:
    float m_nextTeleportOtherTime = PVZ_EOT();
    float m_nextTeleportSelfTime = PVZ_EOT();
    float m_nextDoveSpawnTime = PVZ_EOT();
    MagicianActionStatus m_currentAction;

    virtual bool tryStartZombieActions();
};

class ZombieCarnieMagicianArtifact : public ZombieCarnieMagician
{
public:

    RT_CLASS_DEFINE(ZombieCarnieMagicianArtifact, ZombieCarnieMagician, RtClass);

    void SetRecoveryTime(int time);
    void SetMagichatParams(float hitpoint, pvztime_t duration);
    void SetEnableDove(bool enable);
    void SetPassiveField3(bool enable);
    bool GetPassiveField3() const { return m_passiveField3; }

protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);

    void onZombieInitialize() override;
    void onDestroy() override;
    bool tryStartZombieActions() override;
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;

    void RecoveryZombie();
    void GenerateMagichat();
    void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    bool CheckDisappear();
    void CreateDisappearEffect();

protected:
    int m_recoveryTimes;
    float m_magichatHitpoints;
    pvztime_t m_magichatDuration;
    pvztime_t m_disappearEndTime;
    bool m_enableDove;
    bool m_passiveField3;
};

//Anim rig

class ZombieAnimRig_Magician : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Magician, ZombieAnimRig, RtClass) {}

protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;

};

// dove
class ZombieCarnieMagicianDoveProps : public ZombiePirateCaptainParrotProps
{
public:
    RT_CLASS_DEFINE(ZombieCarnieMagicianDoveProps, ZombiePirateCaptainParrotProps, RtClass);

    SexyVector2 FeatherEffectSpawnOffset;
};

class ZombieCarnieDove : public ZombiePirateParrot
{
public:
    RT_CLASS_DEFINE(ZombieCarnieDove, ZombiePirateParrot, RtClass);

protected:

    void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

    void playBirdLossAnimation(bool i_birdExplodes);

};

class ZombieCarnieDoveArtifact : public ZombiePirateParrot
{
public:
    RT_CLASS_DEFINE(ZombieCarnieDoveArtifact, ZombiePirateParrot, RtClass);

    void SetTargetZombie(ZombiePtr zombie);

protected:
	OVERRIDE_STATE_FUNCTIONS(ZombieState, FlyToTarget);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, AttachedToPlant);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, PickingUpPlant);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, DestroyingPlant);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Returning);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, FlyingAway);

	void onDestroy() override;
	bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;
	bool moveToDestination(const float i_destX, const float i_destY) override;
	bool CanBeTossedByPlants(ZombieTossedPower i_tossStrength) const override;
	void onApplyCondition(ZombieConditions i_condition) override;
	int CalcRenderOrder() const override;
	void onElectrocuted() override;
	void onTurnedToAsh() override;
    void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;

    void playBirdLossAnimation(bool i_birdExplodes);
	ZombiePtr pickTarget(Sexy::Point pos);
	bool CheckTargetDead();

    struct ZombieCache
    {
        SexyVector3 Pos;
        uint        State;
        int         Row;

        ZombieCache()
        {
            Pos = SexyVector3(-1, -1, 0);
            State = -1;
            Row = -1;
        }
    };
    ZombieCache m_zombieCache;
    ZombiePtr m_pickedUpZombie;

};

class ZombieAnimRig_Dove : public ZombieAnimRig_Parrot
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Dove, ZombieAnimRig_Parrot, RtClass);

    bool PlayFly() override;
    bool PlayFlyBack() override;
    bool PlayCarry() override;
};

//
// Teleport Zombies Forward
//

class ZombieTeleportActionDefinition : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombieTeleportActionDefinition, ZombieActionDefinition, RtClass);

    ZombieTeleportActionDefinition()
    : NumZombies(3)
    , TilesToAdvance(3)
    , TilesToAdvanceBig(2)
    , ColumnMin(0)
    , WeightLeftmost(33)
    , WeightRightmost(33)
    , WeightRandom(33)
    , NoRepeatTargets(false)
    , DelayWarpIn(true)
    {}

    int     NumZombies;
    int     TilesToAdvance;
    int 	TilesToAdvanceBig;
    int     ColumnMin;
    int     WeightLeftmost;
    int     WeightRightmost;
    int     WeightRandom;
    float   TimeBeforeWarpStart;
    float   TimeOfWarpOut;
    float   TimeZombieIsGone;
    float   TimeOfWarpIn;
    bool    NoRepeatTargets;
    bool    DelayWarpIn;

    bool    DoOnlySelfTeleport = false;
    bool    IgnoreSelfWhileTeleportingOther = false;
	bool    CanShiftLane = false;
	int    	MaxRowShift = 0;
	float 	TeleportFailureChance = 0;

	std::vector<ZombieConditions> ConditionsRemovedByWarping;
    ClassRestrictionSet ZombieTargetExcludeList;
    ClassRestrictionSet ZombieTargetExcludeListAdvance;

    std::string RampUpAnimation;
    std::string LoopingAnimation;
    std::string RampDownAnimation;

    bool CanStartAction(class ZombieWithActions* i_zombie) const override;
    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
    std::vector<RtWeakPtr<Zombie>> FindTargetsForWarp(ZombieWithActions* i_zombie) const;
    bool IsValidTarget(RtWeakPtr<Zombie> zombie, bool isArtifactField3 = false) const;
};

class ZombieTeleportActionHandler : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombieTeleportActionHandler, ZombieActionHandler, RtClass);

protected:
    void onStartAction() override;
    void onUpdateAction() override;
    void onEndAction() override;

    void startWarpingZombiesOut();
    void startDisappearingZombies();
    void startWarpingZombiesIn();
    void warpZombieOut(RtWeakPtr<Zombie> zombie);
    void disappearZombie(RtWeakPtr<Zombie> zombie);
    void reappearZombie(RtWeakPtr<Zombie> zombie);
    void warpZombieIn(RtWeakPtr<Zombie> zombie);
    void placeZombieInNewPosition(RtWeakPtr<Zombie> zombie);
    void createWarpingEffectAt(RtWeakPtr<Zombie> zombie, std::string startAnimationName, std::string endAnimationName);
    void onAnimationDone(const std::string& i_animName);
    void playLoopingAnimationAgain();

protected:
    enum StateEnum
    {
        STATE_INITIAL,
        STATE_WARP_OUT,
        STATE_DISAPPEAR,
        STATE_WARP_IN,
        STATE_DONE,
    };
    StateEnum m_state = STATE_INITIAL;

    bool m_delayedWarp;

public:
    float m_timeToStartWarpOut;
    float m_timeToStartDisappearing;
    float m_timeToStartWarpIn;
    std::vector<RtWeakPtr<Zombie>> m_targets;
};

//=====================================================================================================
// ZombieSpawnActionDefinition
//=====================================================================================================

struct WeightsInt
{
	int Count;
	int Weight;
};

class ZombieSpawnActionDefinition : public ZombieActionDefinition
{
public:
RT_CLASS_DEFINE(ZombieSpawnActionDefinition, ZombieActionDefinition, RtClass);

    bool CanStartAction(class ZombieWithActions* i_zombie) const override;
    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	virtual std::vector<RtWeakPtr<Plant>> FindTargetPlants(ZombieWithActions* i_zombie) const;
	virtual std::vector<RtWeakPtr<Zombie>> FindTargetZombies(ZombieWithActions* i_zombie) const;

	std::string SpawnZombieType;
	std::vector<WeightsInt> ZombieSpawnWeights;
	std::vector<WeightsInt> ZombieSpawnWeightsAdvance;
	std::vector<std::string> PlantTargetExcludeList;
	std::vector<std::string> ZombieTargetExcludeList;
	std::string SpawnStartAnimation;
	std::string SpawnDoneAnimation;
    SexyVector2 SpawnOffset;
	bool IsADove = false;

protected:
    virtual bool IsValidTarget(PlantPtr i_targetPlant) const;
    virtual bool IsValidTargetZombie(ZombiePtr i_targetZombie, bool isArtifactField3 = false) const;

protected:
	virtual void sortPlants(std::vector<RtWeakPtr<Plant>> io_plants,  ZombieWithActions* i_zombie) const;
	virtual void sortZombies(std::vector<RtWeakPtr<Zombie>> io_zombies,  ZombieWithActions* i_zombie) const;
};

class ZombieSpawnArtifactDoveActionDefinition : public ZombieSpawnActionDefinition
{
public:
RT_CLASS_DEFINE(ZombieSpawnArtifactDoveActionDefinition, ZombieSpawnActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

protected:
	bool IsValidTargetZombie(ZombiePtr i_targetZombie, bool isArtifactField3 = false) const override;
};

class ZombieSpawnActionHandler : public ZombieActionHandler
{
public:
RT_CLASS_DEFINE(ZombieSpawnActionHandler, ZombieActionHandler, RtClass);

protected:
    void onStartAction() override;
    void onEndAction() override;

	virtual void onAnimationDone(const std::string& i_animName);
    void OnPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_params) override;
protected:
	std::vector<RtWeakPtr<Plant>> m_targets;

    virtual void startSpawnZombies();
    virtual void spawnZombie(std::string& i_zombieTypeName, RtWeakPtr<Plant> i_targetPlant);
};

class ZombieSpawnArtifactDoveActionHandler : public ZombieSpawnActionHandler
{
public:
RT_CLASS_DEFINE(ZombieSpawnArtifactDoveActionHandler, ZombieSpawnActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onEndAction() override;

protected:
	void startSpawnZombies() override;
	void spawnZombieToZombie(std::string& i_zombieTypeName, RtWeakPtr<Zombie> i_targetZombie);

	std::vector<RtWeakPtr<Zombie>> m_targetsZombie;
};

#endif /* ZOMBIEMAGICHAT_H_ */
