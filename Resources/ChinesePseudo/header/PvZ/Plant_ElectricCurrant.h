//
//  Plant_ElectricCurrant.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 2/3/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_ElectricCurrant_h
#define Plant_ElectricCurrant_h

#include "GridItemRailcart.h"
#include "GridItemMechanismPlank.h"
#include "GridSquareElectricCurrantFencePiece.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"

class PlantElectricCurrant;

typedef struct _ElectricCurrantLocation
{
	Point m_start;
	Point m_end;
} ElectricCurrantLocation;

class ElectricCurrantFence : public GameObject
{
public:
	RT_CLASS_DEFINE(ElectricCurrantFence, GameObject, RtClass);
	
	ElectricCurrantFence();
	virtual ~ElectricCurrantFence();

	void CreateFence(const Point i_start, const Point i_end, bool i_isPowered, bool i_isLevelAttack);
	void ApplyPlantfood();
	void DestroyFence();
	
	bool HasNode(Point i_node);
	
	bool IsVertical() { return m_isVertical; }
	bool IsPowered() { return m_isPowered; }
	
	ElectricCurrantLocation m_location;
	
	std::vector<RtWeakPtr<GridSquareElectricCurrantFencePiece>> m_pieces;
	bool m_isPowered;
    bool m_isLevelAttack;
	bool m_isVertical;
};

struct point_compare
{
	bool operator()(const Point &lhs, const Point &rhs) const
	{
		if (lhs.mY == rhs.mY)
		{
			return (lhs.mX < rhs.mX);
		}
		
		return (lhs.mY < rhs.mY);
	}
};

class ElectricCurrantFenceSystem : public GameSubSystem
{
public:
	typedef enum
	{
		EC_DIR_UP = 0,
		EC_DIR_RIGHT,
		EC_DIR_DOWN,
		EC_DIR_LEFT,
		EC_DIR_NUMDIRS
	} FenceDirection;
	
	enum
	{
		EC_MAX_FENCES_PER_NODE = 2
	};
	
	RT_CLASS_DEFINE(ElectricCurrantFenceSystem, GameSubSystem, RtClass);
	
	ElectricCurrantFenceSystem();
	virtual ~ElectricCurrantFenceSystem();
	
	void AddNode(PlantElectricCurrant* i_plant);
	void RemoveNode(PlantElectricCurrant* i_plant);
	void ApplyPlantfoodToNode(PlantElectricCurrant *i_plant);
	
	void RemoveOrphanedFences();
	void RecreateFencesAfterNodeRemoval(Point &i_nodeLoc);
	int GetNumFencesOnNode(PlantElectricCurrant *i_plant);
	
	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	
	bool HasAttackTargets(Point i_point);
	bool DoFenceAttack(PlantElectricCurrant *i_plant);
	void DoHitEffect(BoardEntity *entity);
    
    void SetDamageRate(float i_rate) { m_damageRate = i_rate; }
    void SetIsLevelAttack(bool i_level) { m_isLevelAttack = i_level; }
	
	bool	m_levelEnded;
	
private:
	int getNearestPlants(PlantElectricCurrant *i_mainPlant, std::vector<PlantElectricCurrant*> &io_nearestPlants);
	int getNearestPlants(Point &i_plantLoc, std::vector<PlantElectricCurrant*> &io_nearestPlants);
	int getEntitiesToAttackInFence(RtWeakPtr<ElectricCurrantFence> fence, std::vector<BoardEntity*> &boardEntities);
	
	void addFence(PlantElectricCurrant *i_start, PlantElectricCurrant *i_end, bool isPlantfooded);
	void addFenceHelper(Point i_start, Point i_end, bool isPlantfooded);
	void removeFenceBetweenPlants(PlantElectricCurrant *i_plant1, PlantElectricCurrant *i_plant2);
	std::vector<RtWeakPtr<ElectricCurrantFence>>::iterator removeFence(RtWeakPtr<ElectricCurrantFence> i_fence);
	void clearEffectsOnNode(Point i_gridLoc);
	
	void getOrderedLocations(PlantElectricCurrant *i_start, PlantElectricCurrant *i_end, Point &o_startLoc, Point &o_endLoc);
	RtWeakPtr<ElectricCurrantFence> getPieceWithEndpoints( Point i_node1, Point i_node2);
	bool doEndNodesExistForFence(RtWeakPtr<ElectricCurrantFence> i_fence, std::set<Point, point_compare> &o_missingNodes);
	
	void onLevelEnded();
	void removeAllFences();
	bool doesFenceContainNode(RtWeakPtr<ElectricCurrantFence> i_fence, Point i_point);
	
	void onRailcartMoved(GridItemRailcart* i_railcart);
    void onMechanismPlankMoved(GridItemMechanismPlank* i_plank);
	
	std::vector<RtWeakPtr<ElectricCurrantFence>> m_fences;
    
    float m_damageRate = 1.0f;
    bool m_isLevelAttack = false;
};

class PlantElectricCurrant : public PlantFramework
{
public:
	enum
	{
		WEAPON_FENCE_OFFSET = 2
	};
	
	RT_CLASS_DEFINE(PlantElectricCurrant, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
    void CancelPlantfood() override;
	
	void OnRelocationBegun() override;
	void OnRelocationComplete() override;
	
	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;
	
	bool IsPowered() { return m_isPowered; }
	void CreatePlantElectrifiedGlow();
	void RemovePlantElectrifiedGlow();
	
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void DoAttack();
    
    void NumbZombieIfPossible(BoardEntity *entity);
	
protected:
	
	void onKilled(bool i_instantKill)  override;
    void onSleeped(bool sleeped) override;
    void onDestroy() override;
	void onEntityDamaged(BoardEntity* i_entity) override;
	void doFenceAttack();
	
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
private:
	
	enum State
	{
		STATE_EC_START_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_EC_ATTACK,
		STATE_EC_FINISH_ATTACK,
		STATE_EC_FENCE_ATTACK
	};
	
	void setState(const uint i_state);
    
    void DoHitEffect(BoardEntity *entity);
	
    float m_damageRate;
    
	pvztime_t m_nextAttack;
	bool m_isPowered;
	RtWeakPtr<GridSquareElectricCurrantGlowPiece> m_fenceGlow;
	
	RtWeakPtr<ElectricCurrantFenceSystem> m_fenceSystem;
};

class PlantAnimRig_ElectricCurrant : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ElectricCurrant, PlantAnimRig, RtClass);
	
	void StartAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void LoopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void StopAttacking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	bool PlayPlantFoodEnd() override;
    
    void SetIsLevelFiveAttack(bool i_levelFive) { m_isLevelFiveAttack = i_levelFive; }
	
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
    std::string getAttackLoopAnimationName();
    std::string getAttackStopAnimationName();
    std::string getWaterAnimName() override;
    
private:
    bool m_isLevelFiveAttack = false;
};

class ElectricCurrantProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ElectricCurrantProps, PlantPropertySheet, RtClass);
	
	ElectricCurrantProps()
	{
        AttackUpPercent = 0.2f;
        NumbRate = 0.2f;
	}
    
    float AttackUpPercent;
    float NumbRate;
};

#endif /* Plant_ElectricCurrant_h */
