/*
 * StarChallengeProtectPlantByProtectorShield.h
 *
 *  Created on: 2022-8-9
 *      Author: zhousen
 */

#ifndef STARCHALLENGEPROTECTPLANTBYPROTECTORSHIELD_H_
#define STARCHALLENGEPROTECTPLANTBYPROTECTORSHIELD_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeProtectPlantByProtectorShield : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeProtectPlantByProtectorShield, Challenge, RtClass);

    StarChallengeProtectPlantByProtectorShield();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onGameplayStarted();
    void gameplayEnded();
    void PlantFlickOffByProtectorShield(Plant* i_plant);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// flick plant number
};

class StarChallengeProtectPlantByProtectorShieldProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeProtectPlantByProtectorShieldProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeProtectPlantByProtectorShield::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_PROTECT_PLANTS_BY_PROTECTER_SHIELD_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_PROTECT_PLANTS_BY_PROTECTER_SHIELD_NAME]"));
    }

    StarChallengeProtectPlantByProtectorShieldProps()
    : Count(0)
    {}

    int Count;
};




#endif /* STARCHALLENGEPROTECTPLANTBYPROTECTORSHIELD_H_ */
