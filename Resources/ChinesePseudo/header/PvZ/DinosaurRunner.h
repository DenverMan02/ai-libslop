
#ifndef DinosaurRunner_hpp
#define DinosaurRunner_hpp

#include "Dinosaur.h"

STATE_ENUM_CHILD_BEGIN(DinoRunnerState, DinosaurState)
CS_DINORUNNER_RunLeft,
CS_DINORUNNER_TurnLeftToRight,
CS_DINORUNNER_RunRight,
STATE_ENUM_END(DinoRunnerState);

class Zombie;

class DinosaurRunner : public Dinosaur
{
public:
    RT_CLASS_DEFINE(DinosaurRunner, Dinosaur, RtClass);
    
    DinosaurRunner();
    virtual ~DinosaurRunner();
    
    OVERRIDE_STATE_FUNCTIONS(CreatureState, Idle);
    DECLARE_STATE_FUNCTIONS(DinoRunnerState, RunLeft);
    DECLARE_STATE_FUNCTIONS(DinoRunnerState, TurnLeftToRight);
    DECLARE_STATE_FUNCTIONS(DinoRunnerState, RunRight);
    
    bool CanBeCharmed() override;
    void Charm() override;
    void SetSmokeEnabled(bool enabled);
    void TurnLeftToRight();
    virtual void ScaredAway(BoardEntity* i_instigator);
    bool CanBeScaredAway();
    Sexy::Rect CalcAttackRect() const override;
    bool CanAttackPlants();
    bool CanAttackZombies();
    RtWeakPtr<Plant> FindTargetPlant();
    RtWeakPtr<Zombie> FindTargetZombie();
    void NumPlantsKilledInc();
    void NumZombiesKilledInc();
    void SetRunRight(float i_maxOffsetX = 0.0f);
    void SetMaxZombiesCanKill(int i_num) { m_MaxZombiesCanKill = i_num; }
    void SetMaxPlantsCanKill(int i_num) { m_MaxPlantsCanKill = i_num; }
    void AddToHistoryTargets(BoardEntityPtr i_boardEntityPtr);
    bool IsInTargetHistory(BoardEntityPtr i_entity);
    bool isValidZombieTarget(Zombie* i_zombie) override;

protected:
    int CalcRenderOrder() const override;
    void onPlaceOnBoard() override;
    void onTurnLeftToRightAnimDone(const std::string& i_animLabelName);
    void Move(float xSpeed, float zSpeed);
    float GetSmokeTimeInterval();
    float GetSmokeAnimScale();
    float GetSmokeOffsetY();
    int GetSmokeRenderOrder();
    void GenerateSmoke(const std::string &aimName, float offsetX = 0, float offsetY = 0);
protected:
    pvztime_t					m_timeToRun;
    pvztime_t					m_timeToTurn;
    pvztime_t                   m_timeToSmoke;
    pvztime_t                   m_smokeInterval;
    pvztime_t                   m_timeToAttack;
    pvztime_t                   m_turnInterval;
    float                       m_smokeOffsetY;
    float                       m_smokeOffsetX;
    bool                        m_smokeEnabled;
    int                         m_numZombiesKilled;
    int                         m_numPlantsKilled;
    int                         m_MaxZombiesCanKill;
    int                         m_MaxPlantsCanKill;
    std::vector<BoardEntity*>  	m_targetHistory;
    bool 						m_rendLayerToProjectileLayer;
};

class DinosaurRunnerPropertySheet : public DinosaurPropertySheet
{
public:
    RT_CLASS_DEFINE(DinosaurRunnerPropertySheet, DinosaurPropertySheet, RtClass);
    
    DinosaurRunnerPropertySheet()
    {
        ArtCenter = {90, 125};
        MovementSpeed = 145.0f;
        IdleDuration = 0.5;
        MaxZombiesToKill = 3;
        MinZombiesToKill = 1;
        MaxPlantsToKill = 2;
        MinPlantsToKill = 1;
    }
    float MovementSpeed;
    pvztime_t IdleDuration;
    
    int MaxZombiesToKill;
    int MinZombiesToKill;
    int MaxPlantsToKill;
    int MinPlantsToKill;
};

class DinosaurAnimRig_Runner : public CreatureAnimRig
{
public:
    RT_CLASS_DEFINE(DinosaurAnimRig_Runner, CreatureAnimRig, RtClass);
    
    void PlayRunLeft(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
    void PlayTurnLeftToRight(AnimStoppedReflectionDelegate i_onStopped = {});
    void PlayRunRight(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
};

#endif /* DinosaurRunner_hpp */
