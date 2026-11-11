//
//  Plant_AlarmSagittifolia.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 2/3/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_AlarmSagittifolia_h
#define Plant_AlarmSagittifolia_h

#include "GridItemRailcart.h"
#include "GridItemMechanismPlank.h"
#include "GridSquareAlarmSagittifoliaFencePiece.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"
#include "Projectile.h"
#include "LightningBolt.h"

class PlantAlarmSagittifolia;

typedef struct _AlarmSagittifoliaLocation
{
	Point m_start;
	Point m_end;
} AlarmSagittifoliaLocation;

struct point_compare_vertical
{
	bool operator()(const Point &lhs, const Point &rhs) const
	{	
		return (lhs.mY < rhs.mY);
	}
};


class AlarmSagittifoliaFence : public GameObject
{
public:
	RT_CLASS_DEFINE(AlarmSagittifoliaFence, GameObject, RtClass);
	
	AlarmSagittifoliaFence();
	virtual ~AlarmSagittifoliaFence();

	void CreateFence(const Point i_start, const Point i_end);
	bool HasNode(Point i_node);
	void DestroyFence();
	
	AlarmSagittifoliaLocation 										m_location;
	std::vector<RtWeakPtr<GridSquareAlarmSagittifoliaFencePiece>> 	m_pieces;
};


class AlarmSagittifoliaFenceSystem : public GameSubSystem
{
public:
	typedef enum
	{
		EC_DIR_UP = 0,
		EC_DIR_DOWN,
		EC_DIR_NUMDIRS
	} FenceDirection;

	struct DelayAction{
		RtWeakPtr<Plant> 		k_plant;
		pvztime_t				v_delaytime;
	};
	
	RT_CLASS_DEFINE(AlarmSagittifoliaFenceSystem, GameSubSystem, RtClass);
	
	AlarmSagittifoliaFenceSystem();
	virtual ~AlarmSagittifoliaFenceSystem();

	void AddNode(PlantAlarmSagittifolia* i_plant);
	void AddNodeDelay(PlantAlarmSagittifolia* i_plant, pvztime_t i_delay);
	void Update() override;

	void RemoveNode(PlantAlarmSagittifolia* i_plant);
	void RemoveOrphanedFences();

	BoardEntity* GetAttackTargets(Point i_point);
	
	void RecreateFencesAfterNodeRemoval(Point &i_nodeLoc);
	int GetNumFencesOnNode(PlantAlarmSagittifolia *i_plant);
	
	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);

	bool												m_levelEnded;

private:
	
	int getNearestPlants(PlantAlarmSagittifolia *i_mainPlant, std::vector<PlantAlarmSagittifolia*> &io_nearestPlants);
	int getNearestPlants(Point &i_plantLoc, std::vector<PlantAlarmSagittifolia*> &io_nearestPlants);
	int getEntitiesToAttackInFence(RtWeakPtr<AlarmSagittifoliaFence> fence, std::vector<BoardEntity*> &boardEntities);
	
	void addFence(PlantAlarmSagittifolia *i_start, PlantAlarmSagittifolia *i_end);
	void addFenceHelper(Point i_start, Point i_end);
	void removeFenceBetweenPlants(PlantAlarmSagittifolia *i_plant1, PlantAlarmSagittifolia *i_plant2);
	std::vector<RtWeakPtr<AlarmSagittifoliaFence>>::iterator removeFence(RtWeakPtr<AlarmSagittifoliaFence> i_fence);
	void clearEffectsOnNode(Point i_gridLoc);
	
	void getOrderedLocations(PlantAlarmSagittifolia *i_start, PlantAlarmSagittifolia *i_end, Point &o_startLoc, Point &o_endLoc);
	RtWeakPtr<AlarmSagittifoliaFence> getPieceWithEndpoints( Point i_node1, Point i_node2);
	bool doEndNodesExistForFence(RtWeakPtr<AlarmSagittifoliaFence> i_fence, std::set<Point, point_compare_vertical> &o_missingNodes);
	
	void onLevelEnded();
	void removeAllFences();
	bool doesFenceContainNode(RtWeakPtr<AlarmSagittifoliaFence> i_fence, Point i_point);
	
	void onRailcartMoved(GridItemRailcart* i_railcart);
    void onMechanismPlankMoved(GridItemMechanismPlank* i_plank);
	
	std::vector<RtWeakPtr<AlarmSagittifoliaFence>> 		m_fences;
    std::vector<DelayAction> 							m_delayTask;
};


class PlantAlarmSagittifolia : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAlarmSagittifolia, PlantFramework, RtClass);
	
	~PlantAlarmSagittifolia();

	void Initialize() override;
	void UpdateActions() override;
	
	bool IsInvincible() const override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
    void CancelPlantfood() override;
	
	void OnRelocationBegun() override;
	void OnRelocationComplete() override;
	void onEndCondition(PlantConditions i_condition) override;
	void onApplyCondition(PlantConditions i_condition) override;

	virtual bool CanBeWatered() override;

	uint getState();
	RtWeakPtr<AlarmSagittifoliaFenceSystem> getFenceSystem(){
		return m_fenceSystem;
	};

	std::vector<BoardEntityPtr> 				m_shareHitTarget;
	
protected:
	void onDestroy() override;
	void onSleeped(bool sleeped) override;
	void onEntityDamaged(BoardEntity* i_entity) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
private:
	void onLastStandStart();
	void onUpdateIdle(const Point& i_start, const Point& i_end, bool i_flag);
	void Explode();
	void Level5Effect();
	void setState(const uint i_state);
	void playAnimation(const std::string& i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_delegate = PopAnimRig::AnimStoppedReflectionDelegate());

	void travelToJumpUpDestination();
	void travelToLandingDestination();
	
	bool										m_afterFood;
	Point										m_targetPoint;
	SexyVector3									m_startPos;
	SexyVector3									m_endPos;
	RtWeakPtr<Zombie>							m_targetZombie;
	std::vector<ZombieTypePtr> 					m_affectedZombieTypes;
	RtWeakPtr<AlarmSagittifoliaFenceSystem> 	m_fenceSystem;
 
};


class PlantAnimRig_AlarmSagittifolia : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_AlarmSagittifolia, PlantAnimRig, RtClass);
	PlantAnimRig_AlarmSagittifolia();
	
	void setIdleTag(const std::string& i_tag);
	void setPlant(RtWeakPtr<Plant> i_plant){m_alarm = i_plant;};
    std::string getIdleAnimationName() override;
private:
	std::string m_idleTag;
	RtWeakPtr<Plant> m_alarm;
};


class AlarmSagittifoliaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(AlarmSagittifoliaProps, PlantPropertySheet, RtClass);
	
	AlarmSagittifoliaProps()
	{
		StunTime = 10.0f;
        NumbRate = 0.2f;
		ParalysisTime = 10.0f;
		EmpRadius = 200;
		FiledBaseDamage = 20.0f;
		ExRadius = 50.0f;
	}

	float StunTime;
	float NumbRate;
    float ParalysisTime;
    float EmpRadius;
	float FiledBaseDamage;
	float ExRadius;
	std::vector<std::string> AffectedZombieTypes;
};


class TeslaBomb : public Projectile
{
public:
    RT_CLASS_DEFINE(TeslaBomb, Projectile, RtClass);
    TeslaBomb();
    ~TeslaBomb();
    
    void SetAvatared(bool i_avatared);
    void SetFieldDamage(float i_damage);
	void SetGridPosition(int i_x, int i_y);
    
protected:
	void onDestroy() override;

private:
    bool m_avatared = false;
    float m_damage = 0.f;
	Point m_point;
	RtWeakPtr<AlarmSagittifoliaAvatarSkillSystem> m_skillSystem;
};


class ElectricArcStream : public LightningBolt
{
public:
	RT_CLASS_DEFINE(ElectricArcStream, LightningBolt, RtClass);

	ElectricArcStream();
	void setPlant(RtWeakPtr<Plant> i_plant){ m_ownPlant = i_plant; }

protected:
	void createBounce() override;
	void causeDamage(BoardEntityPtr i_target) override;

private:
	RtWeakPtr<Plant> m_ownPlant;

};

#endif