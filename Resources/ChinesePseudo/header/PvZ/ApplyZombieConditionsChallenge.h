//
//  ApplyZombieConditionsChallenge.hpp
//  PlantsVersusZombies2Framework
//
//  Created by Agarwal, Trisha on 6/24/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef ApplyZombieConditionsChallenge_h
#define ApplyZombieConditionsChallenge_h

#include "ChallengeModule.h"
#include "GridItem.h"
#include "LevelModule.h"
#include "RtDb.h"
#include "TodStringFile.h"
#include "UIWidget.h"

class ApplyZombieConditionsChallenge : public Challenge
{
public:
    RT_CLASS_DEFINE(ApplyZombieConditionsChallenge, Challenge, RtClass);
    
    void registerForEvents() override;
    
    ApplyZombieConditionsChallenge()
    {
        m_numConditionsApplied = 0;
    }

	SexyString GetProgressDescription() const override;

private:
    void gameplayStarted();
    void gameplayEnded();
    
    void onZombieConditionApplied(Zombie* i_zombie, int i_condition, pvztime_t i_duration);
    void onZombieBurnedToAsh(Zombie* i_zombie);
    void onZombieElectrified(Zombie* i_zombie);
    
    void incrementNumConditionApplied();
    
    int m_numConditionsApplied;
	RtWeakPtr<UIWidget> m_conditionCounterWidget;
};

class ApplyZombieConditionsChallengeProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(ApplyZombieConditionsChallengeProps, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return ApplyZombieConditionsChallenge::StaticGetClass();
    }
    
    SexyString GetDescription() const override
    {
        SexyString numZombieConditions = StrFormat(_S("%d"), NumZombieConditionsToApply);
        
        SexyString endString = TodReplaceString(_S("[CHALLENGE_APPLY_ZOMBIE_CONDITIONS_OF_TYPE]"), _S("{COUNT}"), numZombieConditions);
        
        //TODO: Check with design if we want to display all conditions or just the first one, going with first one for now
        if(ConditionToInflict.size() > 0)
        {
            std::string k_zombieConditionString = ConvertZombieConditionToString((ZombieConditions)(ConditionToInflict[0])); //0 is none by default.
            SexyString zombieConditionType = StringToSexyString(StrFormat("[%s]", StringToUpper(k_zombieConditionString).c_str()));
            endString = TodReplaceString(endString, _S("{TYPE}"), zombieConditionType);
        }
		else if(IncludeBurnedToAsh)
		{
			endString = TodReplaceString(endString, _S("{TYPE}"), _S("[ASH]"));
		}
		else if(IncludeElectrified)
		{
			endString = TodReplaceString(endString, _S("{TYPE}"), _S("[ELECTRIFY]"));
		}
        
        return endString;
    }
    
    SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[CHALLENGE_APPLY_ZOMBIE_CONDITIONS_OF_TYPE_NAME]"));
    }
    
    ApplyZombieConditionsChallengeProps()
    : NumZombieConditionsToApply(0)
    , IncludeBurnedToAsh(false)
    , IncludeElectrified(false)
    {}
    
    int NumZombieConditionsToApply;
    std::vector<ZombieConditions> ConditionToInflict;
    bool IncludeBurnedToAsh;
    bool IncludeElectrified;
};

#endif /* ApplyZombieConditionsChallenge_h */
