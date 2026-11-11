//
//  PlantUtils.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_UTILS_H__
#define __PLANT_UTILS_H__

#include "PlantFramework.h"

// Peashooter plantfood helper, should be used by all 'peashooting' plants that
// have the gatling plantfood.

enum FireStates
{
	TWOSTARS_NOAVATAR,
	THREESTARS_NOAVATAR,
	TWOSTARS_AVATAR,
	THREESTARS_AVATAR,
	ONLY_AVATAR,
};

enum ProjectileTypes
{
	NORMAL_PEA,
	FIRE_PEA,
	SNOW_PEA,
	ULTRA_FIRE_PEA,
};

namespace PlantUtils
{
	GridItemPtr GetBestDamageableGridItemFromEntities(std::vector<BoardEntity*> entities);
	ZombiePtr GetBestZombieFromEntities(const std::vector<BoardEntity*> i_entities, PlantTargetParams& i_targetParams);
	std::vector<BoardEntityPtr> GetEntityClusterTargets(std::vector<BoardEntity*> i_entities, BoardEntityTypeFlag i_targetType, const float i_radius);
}

class PeashooterPlantfood
{
public:
	PeashooterPlantfood();
	
	void Start(pvztime_t i_duration, int i_shotTotal,float i_extraDamage);
	void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const PlantAction& i_action);
	
	void SetBackwardsProjectiles(bool i_backwards);
    void SetRotation(float i_rotation);

	pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int m_shotsFired;
	int m_shotTotal;
	bool m_backwardsProjectiles;
    
private:
	float m_rotation;
    float m_extraDamage;
};

class LotusshooterPlantfood
{
public:
	LotusshooterPlantfood();

	void Start(pvztime_t i_duration, int i_shotTotal,float i_extraDamage, bool i_avatar);
	void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const std::vector<PlantAction>& i_actions);

	void SetBackwardsProjectiles(bool i_backwards);
    void SetRotation(float i_rotation);

	pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int m_shotsFired;
	int m_shotTotal;
	bool m_backwardsProjectiles;

private:
	float m_rotation;
    float m_extraDamage;
    bool m_avatar;
};


class OakshooterPlantfood
{
public:
	OakshooterPlantfood();
	
	void Start(pvztime_t i_duration, int i_shotTotal, Plant * plant);
    
	void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const PlantAction& i_action);
	
    void SetRotation(float i_rotation);
    
protected:
    
    typedef struct _OakHitItem
    {
        float                  hitpoints;
        SexyVector3            pos;
        bool                   dead;
        int                    hitcount;
    } OakHitItem;
    
private:
    pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int       m_shotsFired;
	int       m_shotTotal;
	float     m_rotation;
    int       m_ent_index;
    
    float     m_damage;
    
    std::vector<OakHitItem> ents_vec;
};


// PlantFoodCounter, Counts the number of shots fired over a period of time.
// TODO: Duplication. Make PeashooterPlantfood use or extend this
class PlantFoodCounter : public RtObject
{
public:
	RT_CLASS_DEFINE(PlantFoodCounter, RtObject, RtClass);
	
	PlantFoodCounter();
	
	void Start(pvztime_t i_duration, int i_shotTotal);
	
	int GetNumShotsToFireSinceLastUpdate() const;
	void MarkShotsAsFired(int i_numShots);
	float GetFractionOfShotsFired() const;
    
    bool IsFinish() { return m_shotsFired >= m_shotTotal; }
	
	pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int m_shotsFired;
	int m_shotTotal;
};

class LemonPlantFoodCounter : public PlantFoodCounter
{
    
public:
    
    RT_CLASS_DEFINE(LemonPlantFoodCounter, PlantFoodCounter, RtClass);
    
    void Start(pvztime_t i_duration, int i_shotTotal, BoardEntityPtr ptrPlant);
    
    void Update();
    static bool TargetIsValid(BoardEntity* target);
private:
    void GenerateLemonRain(int iX, int iY, BoardEntityPtr ptrTarget, BoardEntityPtr ptrPlant);

private:
    
    std::vector<BoardEntityPtr> m_targets;
    BoardEntityPtr m_ptrPlant;
    
};

class LemonNormalShooter : public PlantFoodCounter
{
    
public:
    
    RT_CLASS_DEFINE(LemonNormalShooter, PlantFoodCounter, RtClass);
    
    void Start(pvztime_t i_duration
               , int i_shotTotal
               , BoardEntityPtr ptrPlant
               , RtWeakPtr<ProjectilePropertySheet> ptrProjectile);
    
    void Update();
    
private:

    BoardEntityPtr m_ptrPlant;
    RtWeakPtr<ProjectilePropertySheet> m_ptrProjectile;
    
};

class GatlingPeaPlantfood
{
public:
    GatlingPeaPlantfood();
    
    void Start(pvztime_t i_duration, int i_shotTotal,float i_extraDamage);
    virtual void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const PlantAction& i_action);
    
    void SetBackwardsProjectiles(bool i_backwards);
    void SetRotation(float i_rotation);
    
    pvztime_t m_shotsPerSecond;
    pvztime_t m_startTime;
    int m_shotsFired;
    int m_shotTotal;
    bool m_backwardsProjectiles;
    
    float m_rotation;
    float m_extraDamage;
private:
};

class PeavinePlantgfood : public GatlingPeaPlantfood
{
public:
	void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const PlantAction& i_action) override;
};

class DracaenaPlantgfood : public GatlingPeaPlantfood
{
public:
	void Update(Plant* i_owner, const SexyVector3& i_plantPosition, float i_plantScale, const PlantAction& i_action) override;
};
#endif
