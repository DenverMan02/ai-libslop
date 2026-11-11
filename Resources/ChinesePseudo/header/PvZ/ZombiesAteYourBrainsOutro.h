//
//  ZombiesAteYourBrainsOutro.h
//  PlantsVersusZombies2
//
//  Created by jsola on 7/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiesAteYourBrainsOutro_h
#define PlantsVersusZombies2_ZombiesAteYourBrainsOutro_h

#include "OutroModule.h"

#include "Zombie.h"
#include "TimeLine.h"

class ZombiesAteYourBrainsOutro : public OutroModule
{
public:
    enum ZombieOutroText
    {
        ZombieOutroText_BrainsLoss,
        ZombieOutroText_CannonLoss,
        ZombieOutroText_PlantLoss,
        ZombieOutroText_NoText,
        ZombieOutroText_SteamMiniLoss,
    };
    
public:
    RT_CLASS_DEFINE(ZombiesAteYourBrainsOutro, OutroModule, RtClass) {}
     
	void SetWinningZombie(ZombiePtr i_zombie);
    void SetTextToShow(ZombieOutroText textToShow);
	
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
     
private:
	void onUpdate();
	void startLossOutro();
	
	void outro_playChomp(pvztime_t i_atTime);
	void outro_playScream(pvztime_t i_atTime);
	void outro_showZombiesWonPAM(pvztime_t i_atTime);
	void outro_notifyComplete(pvztime_t i_atTime);
	void outro_freezeGameplay(pvztime_t i_atTime);
	void outro_onZombieWinPAMDone(const std::string& i_animLabel);
	
	void sendPostEndPlay();
	void sendPostPVZ1ModeEndPlay();
	void sendPostPVZ2UnchartedModeEndPlay();
	void onRiftNetworkResponse(int i_context, int i_status);
	void onPVZ1ModeNetworkResponse(int i_context, int i_status);

	ZombiePtr m_winningZombie;
	
	// Outro handler properties
	bool m_freezed = false;
	TimeLine m_outroTimeline;
    
    ZombieOutroText m_textToShow = ZombieOutroText_BrainsLoss;
};
 
class ZombiesAteYourBrainsOutroProperties : public OutroModuleProperties
{
public:
    RT_CLASS_DEFINE(ZombiesAteYourBrainsOutroProperties, OutroModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return ZombiesAteYourBrainsOutro::StaticGetClass();
    }
 
    ZombiesAteYourBrainsOutroProperties()
    {
    }
};

#endif
