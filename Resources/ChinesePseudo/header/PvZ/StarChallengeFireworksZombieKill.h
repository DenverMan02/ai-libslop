/*
 * StarChallengeFireworksZombieKill.h
 *
 *  Created on: 2022-8-9
 *      Author: zhousen
 */

#ifndef STARCHALLENGEFIREWORKSZOMBIEKILL_H_
#define STARCHALLENGEFIREWORKSZOMBIEKILL_H_



#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengeFireworksZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeFireworksZombieKill, Challenge, RtClass);

    StarChallengeFireworksZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayStarted();
    void gameplayEnded();
    bool CheckZombieDeadByFireworks(class Zombie* i_zombie, const DamageInfo* i_deathBlow);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
};

class StarChallengeFireworksZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeFireworksZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeFireworksZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_FIREWORKS_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_FIREWORKS_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeFireworksZombieKillProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGEFIREWORKSZOMBIEKILL_H_ */
