//
//  RiverEntity.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/3/27.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RiverEntity__
#define __PlantsVersusZombies2__RiverEntity__

#include <stdio.h>
#include "BoardEntity.h"
#include "RiverCrossingDodoRider.h"
#include "StateMachine.h"

enum RiverEntityDirection
{
    RiverEntityDirection_INIT,
    RiverEntityDirection_MOVINGUP,
    RiverEntityDirection_MOVINGDOWN
};

enum RiverEntitiesType
{
    RET_FloatingIce,
    RET_SkatingGuacodile
};

class RiverEntity : public BoardEntity
{
public:
     RT_CLASS_DEFINE(RiverEntity, BoardEntity, RtClass);
    
    RiverEntity();
    virtual ~RiverEntity();
        
    float                   getMovingTime() { return m_riverEntityMovingTime; };
    void                    setMovingTime(float i_time) { m_riverEntityMovingTime = i_time; }
    
    void                    riverEntityInitialize();
    bool                    IsMoving();
    void                    StartMoving();
    void                    SetMovingDirection(std::string i_dir);
    void                    SetGrid(int i_col);
    
    virtual void            Update();
    
    void                    SetRiverEntityType(RiverEntitiesType i_type);
    RiverEntitiesType       GetRiverEntityType();
    bool                    CheckRiverEntityCloseToEdge();
    RiverEntityDirection    GetRiverEntityDirection() { return m_riverEntityDirection; }
    
protected:
    virtual void            onInitialized() override;
    virtual void            onDestroy() override;
    virtual void            onDraw(Graphics* i_g) override;
    // virtual void         onGameplayStarted();
    // virtual void         onDrawShadow(Graphics* i_g);
    virtual void            registerForEvents() override;
    virtual void            unregisterForEvents() override;
    virtual std::string		GetUpPamLabel();
    virtual std::string		GetDownPamLabel();
    virtual SexyVector2 	GetDrawOffet();
    
private:    
    int32                   getRiverEntityStateSerialization();
    void                    setRiverEntityStateSerialization(int32 i_state);
    
    void                    checkMoving();
    void                    keepMoving();
protected:
    RtWeakPtr<class PopAnimRig>     m_popAnimRig;
    RiverEntityDirection            m_riverEntityDirection;
    
private:
    int                             GridX;
    int                             GridY;
    bool                            m_isMoving;
    
    RiverEntitiesType               m_riverEntityType;
    
    float                           m_riverEntityMovingTime;
    pvztime_t                       m_riverEntityStartTime;
};

struct RiverEntityProperties
{
    RiverEntityProperties()
    {
        GridX = -1;
    }
    
    int				GridX;
    float           MovingTime;
    std::string		TypeName;
    std::string		Direction;
};

struct RiverEntitySpawner
{
    RiverEntitySpawner()
    {
        nextSpawnTime = PVZ_EOT();
        lastSpawnTime = PVZ_EOT();
        GridX = -1;
    }
    
    RiverEntitiesType   riverEntityType;
    int                 GridX;
    pvztime_t           nextSpawnTime;
    pvztime_t           lastSpawnTime;
};

STATE_ENUM_BASE_BEGIN(RiverEntitiesManagerState)
    RiverEntitiesManagerState_INIT,
    RiverEntitiesManagerState_READY,
    RiverEntitiesManagerState_RUNNING,
    RiverEntitiesManagerState_DONE,
STATE_ENUM_END(RiverEntitiesManagerState);

// Manages wave progression.
class RiverEntitiesManager : public RtObject
{
    RT_CLASS_DEFINE(RiverEntitiesManager, RtObject, RtClass);
public:
    RiverEntitiesManager();
    ~RiverEntitiesManager();
    
    // void Initialize(RtWeakPtr<class RiverEntitiesManagerProperties> i_props, LootConfig *i_lootConfig, bool i_hasDynamicZombies);
    void Initialize(void);
    void SetNextRiverEntitiesTime(pvztime_t i_time);
    bool shouldSpawnRiverEntities(RiverEntityProperties i_prop) const;
    void spawnRiverEntities(RiverEntityProperties i_props);
    void addRiverEntitiesColsInfo(RiverEntityProperties i_props);
    void onDestoryRiverEntity(RiverEntity *entity);
    
//    void setState(RiverEntitiesManagerState i_state) { m_riverEntitiesManagerState = i_state; }
//    RiverEntitiesManagerState getState() { return m_riverEntitiesManagerState; }
    
    int32 getRiverEntitiesManagerStateSerialization();
    void setRiverEntitiesManagerStateSerialization(int32 i_state);
    void setState(RiverEntitiesManagerState i_newState);
    bool isInState(RiverEntitiesManagerState i_state) const;
    RiverEntitiesManagerState getState();
    
    void StartManagement();
    void RemoveRiverEntity(RiverEntity * entity);
    void Update();
    
    bool CheckDodoriderChomped(RiverCrossingDodoRider * i_dodorider);
    // void GetRiverEntities(std::vector<const RiverEntity*> &o_riverEntity) const;
    // void GetRiverEntitiesByIndex(int i_index, std::vector<const RiverEntity*> &o_riverEntity) const;
    
    void *CheckFloatingIce(SexyVector3 pos);
    void unbindAllFloatingIce();
    
    // const RiverEntitiesManagerProperties *GetProps() const;
private:
    void InitRiverEntitiesManager();
    
    DECLARE_STATE_FUNCTIONS(RiverEntitiesManagerState, INIT);
    DECLARE_STATE_FUNCTIONS(RiverEntitiesManagerState, READY);
    DECLARE_STATE_FUNCTIONS(RiverEntitiesManagerState, RUNNING);
    DECLARE_STATE_FUNCTIONS(RiverEntitiesManagerState, DONE);
private:
    bool                                        m_stateHasInited;
    bool                                        m_paused;
    
    float                                       m_riverEntitySpawnRate;
    
    std::vector<RiverEntityProperties>          m_riverEntitiesProps;
    StateMachine<RiverEntitiesManagerState>     m_riverEntitiesManagerState;
    
    //std::string                               m_riverEntityTypeString;
    std::vector<RiverEntity *>                  m_runningRiverEntities;
    std::vector<RiverEntitySpawner *>           m_riverEntitiedSpawner;
};

#endif /* defined(__PlantsVersusZombies2__RiverEntity__) */
