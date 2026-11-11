/*
 * StarChallengeFirecrackerZombieKill.h
 *
 *  Created on: 2022-8-9
 *      Author: zhousen
 */

#ifndef STARCHALLENGEFIRECRACKERZOMBIEKILL_H_
#define STARCHALLENGEFIRECRACKERZOMBIEKILL_H_

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeFirecrackerZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeFirecrackerZombieKill, Challenge, RtClass);

    StarChallengeFirecrackerZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayStarted();
    void gameplayEnded();
    bool CheckZombieDeadByFirecracker(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
};

class StarChallengeFirecrackerZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeFirecrackerZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeFirecrackerZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_FIRECRACKER_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_FIRECRACKER_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeFirecrackerZombieKillProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGEFIRECRACKERZOMBIEKILL_H_ */
