/*
 * StarChallengeTentZombieKill.h
 *
 *  Created on: 2022-8-8
 *      Author: zhousen
 */

#ifndef STARCHALLENGETENTZOMBIEKILL_H_
#define STARCHALLENGETENTZOMBIEKILL_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeTentZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeTentZombieKill, Challenge, RtClass);

    StarChallengeTentZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayStarted();
    void gameplayEnded();
    bool CheckZombiesInCondition(Zombie* zombie);
    void ZombieSpawnedByTent(Zombie* zombie);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
    std::vector<ZombiePtr> m_Zombies;// zombies in condition
};

class StarChallengeTentZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeTentZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeTentZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_TENT_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_TENT_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeTentZombieKillProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGETENTZOMBIEKILL_H_ */
