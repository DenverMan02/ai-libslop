/*
 * StarChallengeBarrelPowderZombieKill.h
 *
 *  Created on: 2022-8-10
 *      Author: zhousen
 */

#ifndef STARCHALLENGEBARRELPOWDERZOMBIEKILL_H_
#define STARCHALLENGEBARRELPOWDERZOMBIEKILL_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeBarrelPowderZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeBarrelPowderZombieKill, Challenge, RtClass);

    StarChallengeBarrelPowderZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void OnZombiePowderKill(Zombie* zombie);
	void onGameplayStarted();
    void gameplayEnded();

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
};

class StarChallengeBarrelPowderZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeBarrelPowderZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeBarrelPowderZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_BARREL_POWDER_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_BARREL_POWDER_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeBarrelPowderZombieKillProps()
    : Count(0)
    {}

    int Count;
};



#endif /* STARCHALLENGEBARRELPOWDERZOMBIEKILL_H_ */
