//
//  ZombieTosser_SubSystem.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 4/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  A subsystem that tosses zombies about.
//

#ifndef __PLANT_SPRINGBEAN_SUBSYSTEM_H__
#define __PLANT_SPRINGBEAN_SUBSYSTEM_H__

#include <vector>

#include "GameSubSystem.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "SexyVector.h"
#include "TimeMgr.h"
#include "ActionSubSystem.h"

class Zombie;

typedef RtReflectionDelegate<Delegate1<class Zombie*> > ZombieLandedCallback;
typedef RtReflectionDelegate<Delegate1<class Zombie*> > ZombieInSkyCallback;

struct TossedZombie
{
	SexyVector3 m_originalPos;
	SexyVector3 m_targetPos;
	SexyVector3 m_position;
	SexyVector3 m_velocity;
	SexyVector3 m_acceleration;
	pvztime_t m_durationTime;
	RtWeakPtr<class Zombie> m_zombie;
	ZombieLandedCallback m_onLandedCallback;
	bool        m_changesRows;   // this will be true if our intended trajectory changes rows.
	bool        m_wasFlying;
    bool        m_setStun;

    // for stuck in sky
    pvztime_t m_durationSkyTime;
    pvztime_t m_skyStartTime;
    ZombieInSkyCallback m_inSkyCallback;
	RtWeakPtr<class Plant> m_plant;
};

//
// a subsystem that tosses zombies in an arc.
//
class ZombieTosserSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieTosserSubSystem, GameSubSystem, RtClass);
    
    void LaunchZombieHorizontal(class Zombie* i_zombie, float i_distanceX, float i_apexHeight, pvztime_t i_timeToHit, ZombieLandedCallback i_landedCallback = ZombieLandedCallback(), bool setStunCondition = true);

    void LaunchZombie(class Zombie* i_zombie, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit, ZombieLandedCallback i_landedCallback = ZombieLandedCallback(), bool setStunCondition = true);
    void LaunchZombieWithPlant(class Zombie* i_zombie, class Plant* i_plant, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit, ZombieLandedCallback i_landedCallback = ZombieLandedCallback(), bool setStunCondition = true);
    void LaunchZombieOriginalZHeight(class Zombie* i_zombie, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit, ZombieLandedCallback i_landedCallback = ZombieLandedCallback(), bool setStunCondition = true);
    void ReleaseZombie(class Zombie* i_zombie);

    SexyVector3 GetTargetPosition(class Zombie* i_zombie);
    ZombieLandedCallback GetOnLandedCallback(class Zombie *i_zombie);
    bool IsTossed(class Zombie* i_zombie);
	
    virtual void Update() override;
    
    static SexyVector3 CaculateTargetButNotOffScreen(Zombie* i_zombie, float desiredXOffset);

protected:
	virtual void registerForEvents() override;
	TossedZombie* findTossedZombie(Zombie* i_forZombie);
	void removeTossedZombie(Zombie* i_forZombie);

    std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
    std::vector<RtWeakPtr<class Plant> > m_deadPlants;
	std::vector<TossedZombie> m_tossedZombies;
	std::vector<TossedZombie> m_newTossedZombies;

protected:
    void onZombieDestroyed(Zombie* i_zombie);
    void onPlantLost(Plant* i_plant);
    void internalLaunchZombie(float i_apexHeight, pvztime_t i_timeToHit, TossedZombie &i_tossedZombie, bool setStunCondition);
};

enum KnockbackReason
{
	KR_PlantKnockback,
	KR_PlantBlowOffScreen,
	KR_PlantFlickOffScreen,
	KR_PowerupKnockback,
	KR_PowerupFlickOffScreen
};
//RT_INVOKEVARIANT_DECLARE_TYPE_SINT32(KnockbackReason);

//RT_INVOKEVARIANT_DECLARE_TYPE_UINT64(KnockbackReason);


class ZombieGentlemanTosserSubSystem : public ZombieTosserSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieGentlemanTosserSubSystem, ZombieTosserSubSystem, RtClass);
	ZombieGentlemanTosserSubSystem() :m_bIsStoped(false)  {}
	virtual ~ZombieGentlemanTosserSubSystem() {};
	virtual void Update() override;
	void setIsStoped(bool bIsStoped);
	bool getIsStoped() const;
	bool isZombieTosseStoped(class Zombie* i_zombie) const;
private:
	bool m_bIsStoped;
};

// toss in sky subsystem
class ZombieTosserInSkySubSystem : public ZombieTosserSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieTosserInSkySubSystem, ZombieTosserSubSystem, RtClass);
    ZombieTosserInSkySubSystem();
	virtual ~ZombieTosserInSkySubSystem();
	virtual void Update() override;

    void TossZombieInSky(class Zombie* i_zombie, class Plant* i_plant, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit,
    		bool setStunCondition = true, pvztime_t durationSky = 0.0f);
    void LaunchZombieInSky(class Zombie* i_zombie, class Plant* i_plant, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit,
        		ZombieLandedCallback i_landedCallback = ZombieLandedCallback(), bool setStunCondition = true, pvztime_t durationSky = 0.0f, ZombieInSkyCallback i_inSkyCallback = ZombieInSkyCallback());

    void SetZombieLandEndFunc(Delegate1<class Zombie*> func);
    void SetZombieInSkyFunc(Delegate1<class Zombie*> func);

    void SetZombieLandEndFunc(Zombie* zombie, Delegate1<class Zombie*> func);
    void SetZombieInSkyFunc(Zombie* zombie, Delegate1<class Zombie*> func);

protected:
	void OnZombieLandEnd(Zombie* i_zombie);
	void OnZombieInSky(Zombie* i_zombie);
	void onPlantLost(Plant* i_plant);

protected:
    std::vector<RtWeakPtr<class Plant> > m_deadPlants;
	Delegate1<class Zombie*> m_landEndDelegate;
	Delegate1<class Zombie*> m_inSkyDelegate;
	std::map<class Zombie*, Delegate1<class Zombie*> > m_landEndDelegateMap;
	std::map<class Zombie*, Delegate1<class Zombie*> > m_inSkyDelegateMap;
};

enum Direction
{
	Direction_Invalid = -1,
	Direction_TopRight,
	Direction_Top,
	Direction_TopLeft,
	Direction_Left,
	Direction_BottomLeft,
	Direction_Bottom,
	Direction_BottomRight,
	Direction_Right,
	Direction_Mid,
	Direction_Max,
};

struct TossedBezeirZombie
{
	SexyVector3 m_originalPos;
	SexyVector3 m_targetPos;
	SexyVector3 m_position;
	SexyVector3 m_velocity;
	SexyVector3 m_acceleration;
	pvztime_t m_durationTime;
	RtWeakPtr<class Zombie> m_zombie;
	ZombieLandedCallback m_onLandedCallback;
	bool        m_changesRows;   // this will be true if our intended trajectory changes rows.
	bool        m_wasFlying;
    bool        m_setStun;

    // for stuck in sky
    pvztime_t m_durationSkyTime;
    pvztime_t m_skyStartTime;
    ZombieInSkyCallback m_inSkyCallback;
};

class ZombieBezeirTosserSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ZombieBezeirTosserSubSystem, GameSubSystem, RtClass);
    ZombieBezeirTosserSubSystem();
	virtual ~ZombieBezeirTosserSubSystem();
	virtual void Update() override;

    void SetZombieFlyFunc(Delegate1<class Zombie*> func);
    void SetZombieFlyEndFunc(Delegate1<class Zombie*> func);
	void MoveToTarget( class BoardEntity* midTarget,  class Zombie* tossTarget, SexyVector2 finalTargetPos, pvztime_t duration, bool stunCondition = true);

protected:
	virtual void registerForEvents() override;

	void AssignBezeirTarget(Direction direct,  class Zombie* zombie, SexyVector2 finalTargetPos, pvztime_t duration);
	ccBezierConfig AssignBezeirConfig(Direction direct, class Zombie* zombie, SexyVector2 finalTargetPos);
	Direction CalcDirection(Sexy::Point midTarget, Sexy::Point tossTarget);

	void OnZombieFlyEnd(class Zombie* i_zombie);
    void onZombieDestroyed(class Zombie* i_zombie);

protected:
	std::vector<RtWeakPtr<class Zombie> > m_deadZombies;
	std::vector<TossedBezeirZombie> m_flyZombies;
	std::vector<TossedBezeirZombie> m_newZombies;
//	std::vector<RtWeakPtr<class Zombie> > m_flyZombies;
//	std::vector<RtWeakPtr<class Zombie> > m_newZombies;

	Delegate1<class Zombie*> m_flyDelegate;
	Delegate1<class Zombie*> m_flyEndDelegate;
};

namespace Message
{
	void ZombieTossed(Zombie* i_zombie);
	void ZombieTossEnd(Zombie* i_zombie);
	void ZombieKnockedBackByPlayer(KnockbackReason i_reason);

	void ZombieGentleManDrop(Zombie* i_zombie);
}


#endif
