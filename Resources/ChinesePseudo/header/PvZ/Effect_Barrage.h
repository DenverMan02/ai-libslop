//
//  Effect_Barrage.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/7/6.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Effect_Barrage__
#define __PlantsVersusZombies2__Effect_Barrage__

#include "RtObject.h"
#include "Projectile.h"
#include "TimeMgr.h"

struct BarrageWaveInfo
{
    bool cycle;
    bool fire;
    bool track;
    int startRotation;
    int angle;
    int bulletQuantity;
    pvztime_t interval;
    std::string barrageName;
    
    BarrageWaveInfo()
    {
        cycle = false;
        fire = false;
        track = false;
        startRotation = 0;
        angle = 0;
        bulletQuantity = 0;
        interval = 0;
        barrageName = "";
    }
};

class Effect_Barrage : public RealObject
{
public:
    RT_CLASS_DEFINE(Effect_Barrage, RealObject, RtClass);
    
    Effect_Barrage();
    ~Effect_Barrage();
    
    void Init();
    bool IsInitlized();
    void StopBarrage();
    void StartBasicBarrage();
    void StartNewBarrageWave();
    void InitBarrage(BoardEntity * i_shooter, float offsetX = 0, float offsetY = 0, bool i_isVice = false);
    void AddBarrageWaveInfo(bool i_fire, bool i_cycle, bool i_track, int i_startRotation, int i_angle, int i_bulletQuantity, float i_interval, std::string i_barrageName);
    void AddBarrageWaveByProps(bool i_track, bool i_cycle, int i_startRotation, int i_endRotation, int i_bulletQuantity, float i_interval, float i_nextInterval, std::string i_barrageName);
    void Update();
    void onShootDone(const std::string &i_animName);
    void SetViceBarrage(Effect_Barrage * i_vice);
    Effect_Barrage * GetViceBarrage();
    
private:
    bool m_isVice;
    bool m_initlized;
    float m_centerOffsetX;
    float m_centerOffsetY;
    pvztime_t m_duration;
    pvztime_t m_lastTime;
    pvztime_t m_lastInterval;
    BoardEntity *m_shooter;
    std::vector<BarrageWaveInfo> m_barrageWaves;
    std::vector<BarrageWaveInfo>::iterator m_currentWave;
    Effect_Barrage * viceBarrage;
};

class PooyanBossBarrage : public Projectile
{
public:
    RT_CLASS_DEFINE(PooyanBossBarrage, Projectile, RtClass);
    
    PooyanBossBarrage() {}
    virtual ~PooyanBossBarrage() {}
protected:
    virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

#endif /* defined(__PlantsVersusZombies2__Effect_Barrage__) */
