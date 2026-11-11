//
//  ZombieLostCityGuide.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-11-30.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieLostCityGuide__
#define __PlantsVersusZombies2__ZombieLostCityGuide__

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"
#include "RestrictionSet.h"
#include "Projectile.h"


STATE_ENUM_CHILD_BEGIN(ZombieState_Guide, ZombieState)
ZS_Guide,
STATE_ENUM_END(ZombieState_Guide)


class ZombieLostCityGuideProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieLostCityGuideProps, ZombiePropertySheet, RtClass);
    
    ZombieLostCityGuideProps()
    {
        
    }
    
};

class ZombieLostCityGuide : public Zombie
{
public:
    
	RT_CLASS_DEFINE(ZombieLostCityGuide, Zombie, RtClass);
    
    ZombieLostCityGuide() : m_iDoDoorCount(0) { }
    
protected:
    
    void onZombieInitialize() override;
    
	void onUpdate() override;
    
    DECLARE_STATE_FUNCTIONS(ZombieState, Guide);
    
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    void GenerateDoor(Sexy::Point startGrid, Sexy::Point endGrid);
    
    Effect_PopAnim* LocateEffect(Sexy::Point effectGrid, bool bStart);
    
    void CheckAndGenerateDoor();
    
private:
    
    void OnGuideAnimationDone(const std::string& i_animName);
    
    bool IsValidGuideDoorInRow();
    
private:
    
    int m_iDoDoorCount;
};

////////////

enum ZombieAnimRigState_PVPNurse
{
    ZOMBIEANIM_GUIDE_GUIDE = ZOMBIEANIM_USERDEFINED,
};


class ZombieAnimRig_Guide : public ZombieAnimRig
{
public:
    
    RT_CLASS_DEFINE(ZombieAnimRig_Guide, ZombieAnimRig, RtClass) {}
    
    bool DoGuideAnimation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
};

//----------------------------------------------------------------------

typedef RtWeakPtr<class GuideEndDoor> GuideEndDoorPtr;

class GuideEndDoor : public Effect_PopAnim
{
    
public:
    
    RT_CLASS_DEFINE(GuideEndDoor, Effect_PopAnim, RtClass);
    
    GuideEndDoor() : m_bBlock(false) {}
    
    virtual ~GuideEndDoor() { ReleaseBlockZombie(); }
    
    void onUpdate() override;
    
    void InitDate(Sexy::Point& selfGrid);
    
    void DoFadeIn(RealObject *pTarget);
    
    Sexy::Point& GetSelfPosition() { return m_SelfPosition; }
    
    void SetMaxHP(float iMaxHP);
    
    bool IsBlock() { return m_bBlock; }
    
    void PlayBlock();
    
    void DoDestory();
    
protected:
    
    void registerForEvents() override;
    
private:
    
    void OnGatherPlantingRestrictions(const Sexy::Point& i_gridPosition
                                      , const PlantType* i_plantType,
                                      std::vector<PlantingReason>* io_plantingReasons);
    
    void DoFadeInZombie(Zombie* pZombie);
    
    void CollectBlockZombie(Zombie* pZombie);
    
    void ReleaseBlockZombie();
    
    void PlayIdle();
    
    float GetZombiesEatDPS();
    
private:
    
    Sexy::Point m_SelfPosition;
    
    float m_iCurrentHP = 0.0f;
    
    float m_iMaxHP = 0.0f;
    
    bool m_bBlock = false;
    
    std::vector<ZombiePtr> m_vZombiePtr;
    
};

//----------------------------------------------------------------------

class GuideStartDoor : public Effect_PopAnim
{
    
public:
    
    RT_CLASS_DEFINE(GuideStartDoor, Effect_PopAnim, RtClass);
    
    GuideStartDoor() : m_iStartTime(PVZ_T()) {}
    
    virtual ~GuideStartDoor() {}
    
    void InitDate(Sexy::Point& selfGrid, GuideEndDoorPtr endPtr);
    
    Sexy::Point& GetSelfPosition() { return m_SelfPosition; }
protected:
    void registerForEvents() override;
    virtual bool manualDestroy() { return false; }
private:
    void onUpdate() override;
    void OnFadeOut(RealObject *pTarget);
    void OnGatherPlantingRestrictions(const Sexy::Point& i_gridPosition
                                      , const PlantType* i_plantType,
                                      std::vector<PlantingReason>* io_plantingReasons);
private:
    
    Sexy::Point m_SelfPosition;
    GuideEndDoorPtr m_ptrEndDoor;
    pvztime_t m_iStartTime;
    
};

#endif /* defined(__PlantsVersusZombies2__ZombieLostCityGuide__) */
