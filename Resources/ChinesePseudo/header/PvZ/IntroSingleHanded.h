//
//  IntroSingleHanded.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-6-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroSingleHanded__
#define __PlantsVersusZombies2__IntroSingleHanded__

#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "AnimationMgr.h"
#include "CollectablePlantUpgrade.h"

class IntroSingleHanded : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(IntroSingleHanded, StandardLevelIntro, RtClass);
    
    int          GetWaveForStartRocket();
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;

private:

    void showTools(bool i_isShown);

    void startIntro();
    void onUpdate();
    void onEndLevel();
    
    void onPlantUpgradeSpawned(CollectablePlantUpgrade* i_plant_upgrade);
    void onFireSingleHandedRockets();

    void clearBouncingArrows();

    enum State
    {
        PVZ_BEGIN_ENUM(STATE_ISH_),
        STATE_ISH_START,
        STATE_ISH_MOVE_PLANT,
        STATE_ISH_WAIT_FOR_UPDATE_PLANT,
        //STATE_ISH_UPDATE_PLANT,
        STATE_ISH_AVOID_BOMB,
        STATE_ISH_PLAYING,
        PVZ_END_ENUM(STATE_ISH_),
    };
    
    class Effect_BouncingArrow * addBouncingArrow(const SexyVector2& i_screenLocation);
    
    void setState(State i_state);

    State                           m_state;
    float							m_timeInCurrentState;
    AnimationMgrWkPtr               m_animationMgr;
    bool                            m_tipUpgrade;
    bool                            m_tipRockets;

    std::vector<StandaloneEffectPtr>	m_bouncingArrows;
};

/////////

class IntroSingleHandedProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(IntroSingleHandedProperties, StandardLevelIntroProperties, RtClass);
	
    IntroSingleHandedProperties()
    {
        WaveForStartRocket = 6;
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return IntroSingleHanded::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
    int WaveForStartRocket;
};

#endif /* defined(__PlantsVersusZombies2__IntroSingleHanded__) */
