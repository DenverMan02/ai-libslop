//
//  Plant_IcyCurrant.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 2/3/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_IcyCurrant_h
#define Plant_IcyCurrant_h

#include "GridItemIcyFence.h"
#include "GridItemMechanismPlank.h"
#include "GridSquareElectricCurrantFencePiece.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GameSubSystem.h"

class GridItemRailcart;
class PlantIcyCurrant;

class IcyCurrantFence: public GameObject
{
public:
	RT_CLASS_DEFINE(IcyCurrantFence, GameObject, RtClass);
	
	IcyCurrantFence();
	virtual ~IcyCurrantFence();
	
	void Init(PlantIcyCurrant* icyOwner, PlantIcyCurrant* icyCurrant);

	static IcyCurrantFence* CreateFence(PlantIcyCurrant* icyOwner, PlantIcyCurrant* icyCurrant);
    
	RtWeakPtr<Plant> owner;
	RtWeakPtr<Plant> node;
	std::vector<IcyFencePtr> fenceList;
    
protected:
    void onDestroy() override;
};

class PlantIcyCurrant : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantIcyCurrant, PlantFramework, RtClass);
	
	PlantIcyCurrant();
	virtual ~PlantIcyCurrant();

	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
    void CancelPlantfood() override;

	void OnRelocationBegun() override;
	void OnRelocationComplete() override;
	
	bool IsPowered() { return m_isPowered; }
	
	void DoAttack(std::vector<class BoardEntity *>& entityList);

	void AddFence(RtWeakPtr<IcyCurrantFence> fence);
	void RemoveFence(RtWeakPtr<IcyCurrantFence> fence);

	float GetPrimaryDamage();

	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;

protected:
	
	void onKilled(bool i_instantKill)  override;
    void onDestroy() override;
    void onLevelEnd();
    void onRailcartMoved(GridItemRailcart* i_railcart);
	
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	
	void Explode();

private:
	
	void CreateFence();
	void ReleaseFence();

	enum State
	{
		STATE_IC_ATTACK= STATE_FRAMEWORK_BEGIN,
		STATE_IC_PLANTFOOD_END,
	};
	
	void setState(const uint i_state);
    
	pvztime_t m_nextAttack;
	pvztime_t m_plantFoodEnd;
	bool m_isPowered;
	bool m_isLevelEnd;
	std::vector<RtWeakPtr<IcyCurrantFence> > m_fence;

	static std::list<PlantIcyCurrant*> stIcyCurrantList;
};

class PlantAnimRig_IcyCurrant : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_IcyCurrant, PlantAnimRig, RtClass);
	PlantAnimRig_IcyCurrant(): m_bAvatar(false) {}
	
	void StartAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void StopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    void SetAvatar(bool bAvatar) { m_bAvatar = bAvatar; }
	
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;
    std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
    std::string getAttackLoopAnimationName();
    std::string getAttackStopAnimationName();
    std::string getWaterAnimName() override;
    
private:
    bool m_bAvatar;
};

class IcyCurrantProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(IcyCurrantProps, PlantPropertySheet, RtClass);
	
	IcyCurrantProps()
	{
		FrozenRateLv2 = 1.f;
		FrozenRateLv3 = 1.f;
		ApplyPlantFoodRateLv4 = 1.f;
		PlantFoodDuration = 10.f;
	}
    
    float FrozenRateLv2;
    float FrozenRateLv3;
    float ApplyPlantFoodRateLv4;
    pvztime_t PlantFoodDuration;
};

#endif /* Plant_IcyCurrant_h */
