//
//  IntroEvilDave.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-6-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroEvilDave__
#define __PlantsVersusZombies2__IntroEvilDave__

#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "AnimationMgr.h"

class IntroEvilDave : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(IntroEvilDave, StandardLevelIntro, RtClass);
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    
private:
    void onStartIntro();
    void onGameplayStarted();
    void onUpdate();
    void onEndLevel();
    void onPlantDied(class Plant * i_plant);
    void onZombiePlanted(class Zombie* i_zombie);
    
    void clearBouncingArrows();
    
    enum State
    {
        PVZ_BEGIN_ENUM(STATE_IED_),
        STATE_IED_START,
        STATE_IED_PLANTING,
        STATE_IED_WAIT_FOR_PLANTED,
        STATE_IED_PLAYING,
        PVZ_END_ENUM(STATE_IED_),
    };
    
    class Effect_BouncingArrow * addBouncingArrow(const SexyVector2& i_screenLocation);
    
    void setState(State i_state);
    
    State                           m_state;
    float							m_timeInCurrentState;
    AnimationMgrWkPtr               m_animationMgr;
    bool                            m_tipPlanted;
    bool                            m_tipEated;
    
    std::vector<StandaloneEffectPtr>	m_bouncingArrows;
};

//////

class IntroEvilDaveProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(IntroEvilDaveProperties, StandardLevelIntroProperties, RtClass);
	
    IntroEvilDaveProperties()
    {
        
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return IntroEvilDave::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

#endif /* defined(__PlantsVersusZombies2__IntroEvilDave__) */
