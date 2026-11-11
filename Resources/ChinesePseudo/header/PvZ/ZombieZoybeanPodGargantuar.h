//
//  ZombieZoybeanPodGargantuar.hpp
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 11/30/18.
//  Copyright © 2018 PopCap Games. All rights reserved.
//

#ifndef ZombieZoybeanPodGargantuar_h
#define ZombieZoybeanPodGargantuar_h

#include <stdio.h>
#include "ZombieGargantuar.h"
#include "GameEventMgr.h"
#include "ZombieAnimRig_Gargantuar.h"

//props
class ZombieZoybeanPodGargantuarProps : public ZombieGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieZoybeanPodGargantuarProps, ZombieGargantuarProps, RtClass);
	ZombieZoybeanPodGargantuarProps():pauseDuration(0.0f)
	{}

	float pauseDuration;
};
class ZombieZoybeanPodGargantuar : public ZombieGargantuar
{
public:
    RT_CLASS_DEFINE(ZombieZoybeanPodGargantuar, ZombieGargantuar, RtClass);
    
    ZombieZoybeanPodGargantuar()
    {
        spawnFromPodAnimationName = "spawn";
        pauseDuration = 0.0f;
        additionalDamage = 0.0f;
    }
    float pauseDuration;
    float additionalDamage;
    bool isImpReadyToBeThrown() override { return false; }
    void onTakeFatalDamage(const DamageInfo& i_lastReceivedDamage) override { BroadcastMessage(Message::GargantuarDefeated, this); }
	void SetPlantFamilies(std::vector<std::string> i_families, float i_resistancePiercing) { m_plantFamilies = i_families; m_resistancePiercingOverride = i_resistancePiercing; }

protected:
	virtual BoardEntity *findTarget() override;
	void onUpdate() override;
    void onTurnedToAsh() override;
    void onElectrocuted() override;
	DamageInfo calcEatDamage() override;
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
private:
	std::vector<std::string> m_plantFamilies;
	float m_resistancePiercingOverride;
};

class ZombieZoybeanPodChildGargantuar :public ZombieZoybeanPodGargantuar{
public:
	RT_CLASS_DEFINE(ZombieZoybeanPodChildGargantuar, ZombieZoybeanPodGargantuar, RtClass);
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
};

class ZombieAnimRig_ZoybeanPodGargantuar : public ZombieAnimRig_Gargantuar
{
public:
    RT_CLASS_DEFINE_ABSTRACT(ZombieAnimRig_ZoybeanPodGargantuar, ZombieAnimRig_Gargantuar, RtClass);
};

#endif /* ZombieZoybeanPodGargantuar_h */
