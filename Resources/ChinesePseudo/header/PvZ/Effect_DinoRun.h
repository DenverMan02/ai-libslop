
#ifndef Effect_DinoRun_hpp
#define Effect_DinoRun_hpp

#include "StandaloneEffect.h"
#include "GridItemType.h"
#include "RtDb.h"

class Creature;
class DinosaurRunner;
class Plant;
class Zombie;

class Effect_DinoRun : public StandaloneEffect
{
public:
    RT_CLASS_DEFINE(Effect_DinoRun, StandaloneEffect, RtClass);
    Effect_DinoRun();
    ~Effect_DinoRun();
    void SetKeyRow(int row);
protected:
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    Creature * SpawnDino(const std::string & dinoType);
    std::string pickDinoTypeName();
    int pickRandRow();
    void applyDamage();
    void ClearSpecifiedDinos();
private:
    void DinoSearchTargetPlants(RtWeakPtr<DinosaurRunner> runner);
    void DinoSearchTargetZombies(RtWeakPtr<DinosaurRunner> runner);
private:
    pvztime_t m_spawnDinoTime;
    pvztime_t m_timeToDamage;
    pvztime_t m_timeToShowShadow;
    pvztime_t m_EndTime;
    
    int m_dinoMaxCount;
    int m_spawnDinoCount;
    float m_spawnDinoInterval;
    int m_keyRow;
    int m_lastUsedRow;
    bool m_shadowIgnored;
    std::string m_lastUsedDino;
    std::vector<EntityWeight> DinoTypesToSpawn;
    std::vector<RtWeakPtr<Creature>> m_dinoRunners;
    std::vector<RtWeakPtr<Zombie>> m_zombiesToBeKilled;
    std::vector<RtWeakPtr<Plant>> m_plantsToBeKilled;
};

#endif /* Effect_DinoRun_hpp */
