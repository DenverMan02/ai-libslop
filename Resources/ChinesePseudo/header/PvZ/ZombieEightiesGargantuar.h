//
//  ZombieEightiesGargantuar.h
//  PlantsVersusZombies2
//
//  Created by Elliott Mina on 7/22/2015.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieEightiesGargantuar_h
#define PlantsVersusZombies2_ZombieEightiesGargantuar_h

#include "ZombieGargantuar.h"
#include "ZombieAnimRig_Gargantuar.h"
#include "Projectile.h"


class ZombieEightiesGargantuarProps : public ZombieGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieEightiesGargantuarProps, ZombieGargantuarProps, RtClass);
	
	ZombieEightiesGargantuarProps()
	{
		JamStyle = "";
		ArbitrarySmashDelay = 0.0f;
		ArbitrarySmashDelayVariance = 0.0f;
		ShockWaveSpawnOffset = { 0.0f, 0.0f };
	}
	
	std::string JamStyle;
	float ArbitrarySmashDelay;
	float ArbitrarySmashDelayVariance;
	SexyVector2 ShockWaveSpawnOffset;
};

class ZombieEightiesGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieEightiesGargantuar, ZombieGargantuar, RtClass);
	ZombieEightiesGargantuar();
	void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle() override;

protected:
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void onUpdate() override;

private:
	void createShockWave();
	void setArbitrarySmashTime();
	SexyVector2 calcShockWaveSpawnPosition();
	SexyVector3 calcShockWaveTargetPosition();

	bool m_isJamming;
	pvztime_t m_arbitrarySmashTime;
};

class ZombieAnimRig_EightiesGargantuar : public ZombieAnimRig_Gargantuar
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_EightiesGargantuar, ZombieAnimRig_Gargantuar, RtClass);
    
    ZombieAnimRig_EightiesGargantuar()
    {
//        m_hasTorch = true;
    }
};

#endif
