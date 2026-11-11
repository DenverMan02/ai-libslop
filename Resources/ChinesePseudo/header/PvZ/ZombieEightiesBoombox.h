//
//  ZombieEightiesBoombox.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 7/21/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesBoombox__
#define __PlantsVersusZombies2__ZombieEightiesBoombox__

#include <stdio.h>

#include "DamageInfo.h"
#include "RtObject.h"
#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_EightiesBoombox, ZombieState)
ZS_BOOMBOX_BoomBoxUp,
ZS_BOOMBOX_BoomBox,
STATE_ENUM_END(ZombieState_EightiesBoombox)

class ZombieEightiesBoomboxProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBoomboxProps, ZombiePropertySheet, RtClass);
    
    ZombieEightiesBoomboxProps()
    {
        JamStyle = "";
        BoomBoxDuration = 0.f;
        PlantFreezeRadius = 0;
        BoomBoxColumn = 0;
    }
	
	PlantRestrictionSet PlantBoomRestrictionSet;
    std::string JamStyle;
    float BoomBoxDuration;
    int PlantFreezeRadius;
    float BoomBoxColumn;
};

class ZombieEightiesBoombox : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieEightiesBoombox, Zombie, RtClass);
    ZombieEightiesBoombox();
    
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	void onDestroy() override;
	
	DECLARE_STATE_FUNCTIONS(ZombieState, BoomBoxUp);
    DECLARE_STATE_FUNCTIONS(ZombieState, BoomBox);
	
    std::string GetJamStyle() override;
        
private:
	void onZombieInitialize() override;
	
    bool shouldPlayBoomBox();
	void findPlantsToBoom();
	
	void playBlockingJam();
	void endBlockingJam();
	void applyBoomConditionToPlantsInRange();
	
	void onBoomboxRaised();
	void onBoomboxLowered();
	
    pvztime_t						m_boomTimeEnd;
	pvztime_t						m_nextBoomTime;
	bool							m_hasBoomed;
	std::vector<RtWeakPtr<Plant>>   m_plantsToBoom;
};

enum ZombieAnimRigState_EightiesBoombox
{
    ZOMBIEANIM_BOOMBOX_START_JAMMING = ZOMBIEANIM_USERDEFINED,
    ZOMBIEANIM_BOOMBOX_JAMMING,
    ZOMBIEANIM_BOOMBOX_STOP_JAMMING
};

class ZombieAnimRig_EightiesBoombox : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_EightiesBoombox, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_EightiesBoombox();
	
	void RaiseBoombox(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void StartJamming();
    void StopJamming(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
	SexyVector2 GetHeadOffset() override;
    
private:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesBoombox__) */
