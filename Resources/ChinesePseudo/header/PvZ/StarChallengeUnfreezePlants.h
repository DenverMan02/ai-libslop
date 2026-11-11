/*
 * StarChallengeUnfreezePlants.h
 *
 *  Created on: 2022-8-8
 *      Author: zhousen
 */

#ifndef STARCHALLENGEUNFREEZEPLANTS_H_
#define STARCHALLENGEUNFREEZEPLANTS_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengeUnfreezePlants : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeUnfreezePlants, Challenge, RtClass);

    StarChallengeUnfreezePlants();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onGameplayStarted();
    void gameplayEnded();
    void PlantConditionApplied(Plant* i_plant, int i_condition);
    void PlantConditionEnded(Plant* i_plant, int i_condition);
    bool CheckPlantsInCondition(Plant* plant);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;
    std::vector<PlantPtr> m_Plants;
};

class StarChallengeUnfreezePlantsProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeUnfreezePlantsProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeUnfreezePlants::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_UNFREEZE_PLANTS_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_UNFREEZE_PLANTS_NAME]"));
    }

    StarChallengeUnfreezePlantsProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGEUNFREEZEPLANTS_H_ */
