/*
 * StarChallengeSandstormZombieKill.h
 *
 *  Created on: 2022-8-5
 *      Author: zhousen
 */

#ifndef STARCHALLENGESANDSTORMZOMBIEKILL_H_
#define STARCHALLENGESANDSTORMZOMBIEKILL_H_

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengeSandstormZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeSandstormZombieKill, Challenge, RtClass);

    StarChallengeSandstormZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void ZombieFlicked(Zombie* i_zombie);
	void ZombieDropHead(Zombie* i_zombie);
	void onGameplayStarted();
    void gameplayEnded();
    void ZombieEnterSandstorm(Zombie* zombie);
    void ZombieExitSandstorm(Zombie* zombie);
    bool CheckZombiesInSandstorm(Zombie* zombie);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
    std::vector<ZombiePtr> m_ZombiesInSandstorm;
};

class StarChallengeSandstormZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeSandstormZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeSandstormZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_SANDSTORM_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_SANDSTORM_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeSandstormZombieKillProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGESANDSTORMZOMBIEKILL_H_ */
