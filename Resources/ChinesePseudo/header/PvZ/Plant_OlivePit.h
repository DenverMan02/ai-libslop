//
//  PlantOlivePit.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 3/19/20.
//  Copyright © 2020 PopCap Games. All rights reserved.
//

#ifndef PlantOlivePit_h
#define PlantOlivePit_h

#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "TimeLine.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"
#include "AnimRigLayerSet.h"
#include "Zombie.h"
#include "BoardEntity.h"
#include <string>

enum OlivePitState
{
	OLIVEPITSTATE_INIT = STATE_FRAMEWORK_BEGIN,
	OLIVEPITSTATE_READY,
	OLIVEPITSTATE_SWALLOWING,
	OLIVEPITSTATE_CHEWING,
	OLIVEPITSTATE_OILSPEW,
	OLIVEPITSTATE_PF_SWALLOWING,
	OLIVEPITSTATE_TANGLE,// tangle
};

enum {
	TANGLE_NOT_READY,
	TANGLE_INIT,
	TANGLE_LOOP,
	TANGLE_END,
};

class OlivePitProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(OlivePitProps, PlantPropertySheet, RtClass);
	
	OlivePitProps()
	:	PitCapacity(1)
	,	ChewTime(3)
	,	OilItemName("oil")
	,	OilSpitRecharge(3)
	,	OilDuration(3)
	,	OilCondition(ZCONDITION_Slowdown)
	,	ZombieFallTime(3)
	,	PFZombiePullTime(1)
	, 	PFZombieFallTime(1)
	{}
	
	int PitCapacity;
	int PitCapacityLv2;// lv = 2
	int PitCapacityLv3;// lv >= 3
	float ChewTime;
	float ChewTimeLv2;
	float ChewTimeLv3;
	std::vector<int> AboveLevelZombieChewList;// check swallow one zombie into chew time level.
	pvztime_t TangleDuration;// level 5 tangle zombie time
	pvztime_t TangleCooldown;// tangle cool down time
	ClassRestrictionSet PitExcludelist;
	ClassRestrictionSet PitCapacityExcludelist; //Zombies that may be eaten, but don't add to capacity
	std::string OilItemName;
	float OilSpitRecharge;
	Rect OilSpitRange;
	float OilDuration;
	ZombieConditions OilCondition;
	ClassRestrictionSet CanBeTargetedByList;
	float ZombieFallTime;
	float PFZombiePullTime;
	float PFZombieFallTime;
	int PlantfoodDragZombieMax;
	int AvatarPlantfoodDragZombieMax;
};

class PlantOlivePit : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantOlivePit, PlantFramework, RtClass);
	
	void		Initialize() override;
	void		UpdateActions() override;
	CollisionTypeFlags	GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	bool		CanBeTargetedBy(const BoardEntity* i_entity) override;
	bool		CanBeRangeTargeted() override { return false; }
	bool		CanApplyPlantfood() override;
	void		ApplyPlantfood() override;
	void		CancelPlantfood() override;
	bool		HasShadow() override { return false; }
	void		SwallowZombie(ZombiePtr i_zombie);
	void		DragInZombies(std::vector<BoardEntity*> i_zombies);
	int			CalcRenderOrder() override { return m_renderOrder; };
	bool 		TryBlockPush()override{return true;}
	
protected:
	void		onDestroy() override;
	void		setState(int i_state);
	bool		canEatZombie(ZombiePtr i_zombie);
	bool 		canEatZombiePlantfood(ZombiePtr i_zombie);
	void		onAnimStoppedCallback(const std::string& i_animName) override;
	void 		tryAddOilToTile(Point i_tile);
	void 		killZombie(ZombiePtr i_zombie, bool plantDestroy = false);// check kill zombie when plantDestroy
	void 		setupZombieToBeSwallowed(ZombiePtr i_zombie);
	bool  		CheckAboveLevelZombieChew(Zombie* ptr);
	void 		HandleTangleZombie();
	Zombie*     CheckTangleZombie(std::vector<BoardEntity*> i_zombies);
	
	void onUseAttackCallback(pvztime_t i_atTime);
	void onUseSpecialCallback(pvztime_t i_atTime);

	void onAnimTangleStoppedCallback1(const std::string& i_animName);
	void onAnimTangleStoppedCallback2(const std::string& i_animName);
	void UpdateChewing();
	
private:
	int m_zombiesEaten;
	ZombiePtr m_zombieToEat;
	ZombiePtr m_zombieToTangle;
	std::vector<ZombiePtr> m_plantfoodZombiesToEat;
	CurveSequence_SexyVector3 m_zombieSwallowCurve;
	std::vector<CurveSequence_SexyVector3> m_plantfoodZombieSwallowCurves;
	pvztime_t m_chewingEndTime;
	pvztime_t m_tangleCooldown;
	pvztime_t m_tangleEndTime;
	pvztime_t m_nextOilSpitTime;
	int m_pitCapacity;// lv1 lv2 lv3 and above, modify pit capacity
	int m_aboveLevelZombieChew;// when zombie level above this, plant chew one then into chew_state
	float m_chewTime;// chew state duration stime
	int m_plantfoodDrawZombieMax;// when plantfood drag zombie num max.
	int m_tangleState;// tangle state
	int m_renderOrder;// the rendderOrder value
};

class PlantTypeOlivepit : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeOlivepit, PlantType, RtClass) {}
	
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

class PlantAnimRig_OlivePit : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_OlivePit, PlantAnimRig, RtClass);
	
	bool PlayPreviewAnim(bool bHideLayer = false) override;
	bool PlayZenGardenIdleAnim() override;
	void PlayChewingAnim(float i_chewTime);
	
	void onAnimFinished(const std::string& i_animName);

	void SetAvatar(bool avatar){ m_avatar = avatar; }
	
protected:
	void playChewStart();
	void playChewLooped();
	void playChewEnded();
	
private:
	std::string getPlantFoodOnAnimName() override { 
		return m_avatar ? "plantfood2_start" : "plantfood_start"; 
	}
	std::string getPlantFoodMainAnimName() override { 
		return m_avatar ? "plantfood2_loop" : "plantfood_loop"; 
	}
	std::string getPlantFoodOffAnimName() override { 
		return m_avatar ? "plantfood2_end" : "plantfood_end"; 
	}
	std::string getPreviewAnimationName();
	
	pvztime_t m_chewLoopEnd;
	bool m_avatar;
};


enum GridItemOilState
{
	PVZ_BEGIN_ENUM(OILSTATE_),
	OILSTATE_UNKNOWN,
	OILSTATE_SPAWNING,
	OILSTATE_RESETTING,
	OILSTATE_IDLE,
	OILSTATE_FADING,
	OILSTATE_DEAD,
	PVZ_END_ENUM(OILSTATE_)
};

class GridItemOilProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemOilProps, GridItemAnimationProps, RtClass);
	GridItemOilProps()
	: OilTime(0.5)
	{}
	
	pvztime_t OilTime;
};

class GridItemOil : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemOil, GridItemAnimation, RtClass);
	
	GridItemOil();
	int CalcRenderOrder() const override;
	
	void ResetTimer(float i_newLifetime);
	void OnWashedOut();
	
	void InitializeProperties (float i_resistancePiercing, float i_oilLifetime, std::vector<std::string> i_plantFamilies, ZombieConditions i_conditionsToApply);
	
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
	void setState(GridItemOilState i_state);
	void applyOil();
	
	void onSpawnFinished(const std::string& i_animName);
	void onDeathFinished(const std::string& i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
private:
	pvztime_t m_creationTime;
	GridItemOilState m_state;
	float m_resistancePiercing;
	float m_lifetime;
	std::vector<std::string> m_plantFamilies;
	ZombieConditions m_conditionsToApply;
};

#endif /* PlantOlivePit_h */
