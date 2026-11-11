/*
 * 	ArtifactDinosaurHornTools.h
 *
 * 		Created on: 2022-6-2
 * 			Author: kkdud
 */

#ifndef PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTDINOSAURHORNTOOLS_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTDINOSAURHORNTOOLS_H_

#include "EffectObject.h"
#include "GridItemType.h"
#include "Plant.h"
#include "RtDb.h"
#include "StandaloneEffect.h"
#include "Artifact.h"

class Creature;
class DinosaurRunner;
class Plant;
class Zombie;

class Effect_DinoRun_For_Artifact_Dinosaur_horn : public StandaloneEffect
{
public:
    RT_CLASS_DEFINE(Effect_DinoRun_For_Artifact_Dinosaur_horn, StandaloneEffect, RtClass);
    Effect_DinoRun_For_Artifact_Dinosaur_horn();
    ~Effect_DinoRun_For_Artifact_Dinosaur_horn();
    void spawnDinos(std::vector<ArtifactDinosaurHornProperties::TypeToSpawnDes> i_dinoTypeToSpawn, int i_dinosaurNumPerLine);
    bool canZombieBeSecKilled(Zombie* i_zombie);

protected:
    virtual void onInitialized() override;
    virtual void onUpdate() override;
    Creature * SpawnDino(const std::string & dinoType, int i_row);
    std::string pickDinoTypeName();
    void applyDamage();
    void applyDamageNormal();
    float calcDamageAmountToSurvivor(std::string i_typeName);
    void ClearSpecifiedDinos();
    int getMinNumToSeckill(std::string i_typeName);
    int getMaxNumToSeckill(std::string i_typeName);
private:
    void DinoSearchTargetPlants(RtWeakPtr<DinosaurRunner> runner);
    void DinoSearchTargetZombies(RtWeakPtr<DinosaurRunner> runner);
    void DinoSearchStunZOmbies(RtWeakPtr<DinosaurRunner> runner);
private:
    pvztime_t m_spawnDinoTime;
    pvztime_t m_timeToDamage;
    pvztime_t m_timeToShowShadow;
    pvztime_t m_EndTime;

    int m_dinosaursNumPerLine;
    bool m_shadowIgnored;
    std::string m_lastUsedDino;
    std::vector<ArtifactDinosaurHornProperties::TypeToSpawnDes> m_dinoTypesToSpawn;
    std::vector<RtWeakPtr<Creature>> m_dinoRunners;
    std::vector<RtWeakPtr<Zombie>> m_zombiesToBeKilled;
    std::vector<RtWeakPtr<Plant>> m_plantsToBeKilled;
};


class Effect_DinoFootShadow_For_Artifact_Dinosaur_horn : public StandaloneEffect
{
public:
    RT_CLASS_DEFINE(Effect_DinoFootShadow_For_Artifact_Dinosaur_horn, StandaloneEffect, RtClass);
    Effect_DinoFootShadow_For_Artifact_Dinosaur_horn();
    ~Effect_DinoFootShadow_For_Artifact_Dinosaur_horn();

    void SetMoveEndPos(SexyVector2 pos);
    void StartMove();
protected:
    virtual void onInitialized() override;
    virtual void onDraw(class Graphics* i_g) override;
    virtual void onUpdate() override;

    void TryToFindBramble();

private:

    pvztime_t		m_moveStartTime;
    pvztime_t		m_moveEndTime;

    pvztime_t		m_scaleStartTime;
    pvztime_t		m_scaleEndTime;
    pvztime_t		m_treadTime;
    SexyVector2		m_startPos;
    SexyVector2		m_endPos;
    SexyVector2		m_shadowScale;
    float           m_scale;
    bool            m_moveStarted;

    bool            m_foundBramble = false;
};

class EffectObject_DinoTreadProps_For_Artifact_Dinosaur_horn : public EffectObjectPropertySheet
{
public:
    RT_CLASS_DEFINE(EffectObject_DinoTreadProps_For_Artifact_Dinosaur_horn, EffectObjectPropertySheet, RtClass);

    EffectObject_DinoTreadProps_For_Artifact_Dinosaur_horn()
    {
        TreadStayTime = 5.0f;
        TreadDamage = 2000;
    }
    pvztime_t	TreadStayTime;
    float TreadDamage;
};

class EffectObject_DinoTread_For_Artifact_Dinosaur_horn : public EffectObject
{
public:
    RT_CLASS_DEFINE(EffectObject_DinoTread_For_Artifact_Dinosaur_horn, EffectObject, RtClass);
    EffectObject_DinoTread_For_Artifact_Dinosaur_horn();
    ~EffectObject_DinoTread_For_Artifact_Dinosaur_horn();

    void	onUpdate() override;
    void    onDestroy() override;
    void	onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
    void	applyDamage();
    bool canZombieBeSecKilled(Zombie* i_zombie);
protected:
    void registerForEvents() override;
    void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
private:
    std::string pickBrambleAnim(const int& i_plantY);

    pvztime_t	m_timeToApplyDamage;
    pvztime_t   m_timeToPullBramble;
    int m_row;
    int m_column;

    PlantPtr m_cachedBramble;
};


#endif /* PLANTSVERSUSZOMBIES2_PVZ2_ARTIFACTDINOSAURHORNTOOLS_H_ */
