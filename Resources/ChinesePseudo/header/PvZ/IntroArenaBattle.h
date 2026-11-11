
  /*IntroArenaBattle.h
  PlantsVersusZombies2

  Created by Jiang, Lichun on 15-10-19.
  Copyright (c) 2015年 PopCap Games. All rights reserved.*/


#ifndef __PlantsVersusZombies2__IntroArenaBattle__
#define __PlantsVersusZombies2__IntroArenaBattle__

#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "AnimationMgr.h"

class IntroArenaBattle : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(IntroArenaBattle, StandardLevelIntro, RtClass);
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual bool suppressReadySetGo() const override { return true; }
    
private:
    bool preventSave();
    void onStartIntro();
    void onLoadComplete() override;
};

//////

class IntroArenaBattleProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(IntroArenaBattleProperties, StandardLevelIntroProperties, RtClass);
    
    IntroArenaBattleProperties()
    {
        
    }
    
    virtual RtClass* GetModuleClass() const override
    {
        return IntroArenaBattle::StaticGetClass();
    }
    
    virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

#endif /* defined(__PlantsVersusZombies2__IntroArenaBattle__) */
