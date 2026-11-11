/*
 * StarChallengePotionZombieKill.h
 *
 *  Created on: 2022-8-8
 *      Author: zhousen
 */

#ifndef STARCHALLENGEPOTIONZOMBIEKILL_H_
#define STARCHALLENGEPOTIONZOMBIEKILL_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengePotionZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengePotionZombieKill, Challenge, RtClass);

    StarChallengePotionZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayStarted();
    void gameplayEnded();
    bool CheckZombiesInPotion(Zombie* zombie);
    void ZombieConditionApplied(Zombie* i_zombie, int i_condition, pvztime_t i_duration);
    void ZombieConditionEnded(Zombie* i_zombie, int i_condition);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
    std::vector<ZombiePtr> m_ZombiesInPotion;
};

class StarChallengePotionZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengePotionZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengePotionZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_POTION_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_POTION_ZOMBIE_KILL_NAME]"));
    }

    StarChallengePotionZombieKillProps()
    : Count(0)
    {}

    int Count;
};


#endif /* STARCHALLENGEPOTIONZOMBIEKILL_H_ */
