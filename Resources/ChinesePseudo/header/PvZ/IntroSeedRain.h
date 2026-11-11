//
//  IntroSeedRain.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-5-18.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroSeedRain__
#define __PlantsVersusZombies2__IntroSeedRain__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Collectable.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(SDIState)
SDIState_DaveIntro,
SDIState_FirepeashooterIntro,
SDIState_GamePlaying,
SDIState_AcornIntro,
STATE_ENUM_END(SDIState);

class SeedRainIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(SeedRainIntro, StandardLevelIntro, RtClass);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    void            OnGameplayStarted();
    
    DECLARE_STATE_FUNCTIONS(SDIState, DaveIntro);
    DECLARE_STATE_FUNCTIONS(SDIState, FirepeashooterIntro);
    DECLARE_STATE_FUNCTIONS(SDIState, GamePlaying);
    DECLARE_STATE_FUNCTIONS(SDIState, AcornIntro);
    
    int32 getSeedRainIntroStateSerialization();
    void  setSeedRainIntroStateSerialization(int32 i_state);
    
private:
    
    void        setState(SDIState i_newState);
	bool        isInState(SDIState i_state) const;
    
    Collectable * AddCollectableSeedRain(const std::string & i_plant_name);
    
    Effect_BouncingArrow* addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void				  clearBouncingArrows();
    
    void        onNarrationFinished();
    
    void        onPlantPlanted(Plant * i_plant);
    void        onZombieSpawned(Zombie* i_zombie);
    
private:
	StateMachine<SDIState>  m_SRIState;
    
    std::vector<StandaloneEffectPtr>  m_bouncingArrows;
    
    CollectablePtr          m_FirstSeedRain;
    CollectablePtr          m_AcornSeedRain;
    ZombiePtr               m_zombieWalrus;
    
    pvztime_t               m_timeDaveIntro;
    pvztime_t               m_timeWalrusIntro;
    
    int                     m_rowWalrus;
    
    bool                    m_bWalrusDone;
};


class SeedRainIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(SeedRainIntroProperties, StandardLevelIntroProperties, RtClass);
    
    SeedRainIntroProperties()
    {
        
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return SeedRainIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroSeedRain__) */
