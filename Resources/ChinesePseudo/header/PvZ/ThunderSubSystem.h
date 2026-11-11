//
//  ThunderSubSystem.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ThunderSubSystem__
#define __PlantsVersusZombies2__ThunderSubSystem__

#include "GameSubSystem.h"
#include "GameEventMgr.h"
#include "RtReflectionDelegate.h"
#include "Plant.h"
#include "ThunderWaveAction.h"

struct ArtifactThunderData
{
	ArtifactThunderData()
	: ThunderBuffDuration(0)
	, BleedingDPS(0)
	, BleedingDuration(0)
	, StunDuration(0)
	, SlowDPS(0)
	, SlowDuration(0)
	{

	}

	float ThunderBuffDuration;
	float BleedingDPS;
	float BleedingDuration;
	float StunDuration;
	float SlowDPS;
	float SlowDuration;
};

class ThunderSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(ThunderSubSystem, GameSubSystem, RtClass);
    
    static bool CanbeThundered(Plant * plant);
    static bool CanbeThundered(Zombie * zombie);
	
    void AddPlantToThunder(class Plant * i_plant,
                           ThunderType i_thunderType, float i_killRate = 0);
    
    virtual void Update() override;
    
    void AddRandomThunderToZombies(ArtifactThunderData i_data);

protected:
	virtual void registerForEvents() override;
    
    void onLightningAnimDone(class StandaloneEffect * i_effect);
    void onConnectHitDone(class StandaloneEffect * i_effect);
    
    void onLightningAnimCommand(const std::string& i_animLabel,
                                pvztime_t i_timeStamp,
                                const std::string& i_animCommand,
                                const std::string& i_animCommandParam);
    
    void onHitAnimCommand(const std::string& i_animLabel,
                          pvztime_t i_timeStamp,
                          const std::string& i_animCommand,
                          const std::string& i_animCommandParam);
    
    Plant * findNearByPlant(PlantPtr i_plant,int & i_direct);
    bool    IsInHitPlants(class Plant * i_plant);
    
    void takeHitEffect();
    
    void setConnectPopAnim(Effect_PopAnim * i_effect,int i_direct,PlantPtr i_plant);
    
private:
    
    ThunderType m_thunderType;
    
    PlantPtr              m_curePlant;
    PlantPtr              m_nearByPlant;
    std::vector<PlantPtr> m_hitPlants;
    
    int                   m_nearByCount;
    
    std::vector<Effect_PopAnim*> m_effectAnims;
    float				  m_killRate = 0;
};

#endif /* defined(__PlantsVersusZombies2__ThunderSubSystem__) */
