//
//  StarChallengeBlowZombie.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-3-27.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarChallengeBlowZombie__
#define __PlantsVersusZombies2__StarChallengeBlowZombie__

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengeBlowZombie : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeBlowZombie, Challenge, RtClass);
    
    virtual void registerForEvents() override;
    
    StarChallengeBlowZombie();

	SexyString GetProgressDescription() const override;
    
private:
    void gameplayStarted();
    void gameplayEnded();
    
    void onZombieBlown(class Zombie* zombie);
    
    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }
    
    int m_zombieCount;
    RtWeakPtr<UIWidget> m_UI;
};

class StarChallengeBlowZombieProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeBlowZombieProps, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeBlowZombie::StaticGetClass();
    }
    
    virtual SexyString GetDescription() const override
    {
        SexyString target = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_BLOW_ZOMBIE]"), _S("{COUNT}"), target);
    }
    
    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_BLOW_ZOMBIE_NAME]"));
    }
    
    StarChallengeBlowZombieProps()
    : Count(0)
    {}
    
    int Count;
};

class ChallengeBlowZombieUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(ChallengeBlowZombieUI, ChallengeUI, RtClass);
    
    ChallengeBlowZombieUI();
    void SetCurrent(int count);
    void SetTarget(int target);
protected:
    virtual SexyString getCountText() override;
    
private:
    int	m_current;
    int m_target;
};

#endif /* defined(__PlantsVersusZombies2__StarChallengeBlowZombie__) */
