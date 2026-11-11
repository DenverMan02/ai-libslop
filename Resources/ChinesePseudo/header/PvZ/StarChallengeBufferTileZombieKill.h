/*
 * StarChallengeBufferTileZombieKill.h
 *
 *  Created on: 2022-8-6
 *      Author: zhousen
 */

#ifndef STARCHALLENGEBUFFERTILEZOMBIEKILL_H_
#define STARCHALLENGEBUFFERTILEZOMBIEKILL_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeBufferTileZombieKill : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeBufferTileZombieKill, Challenge, RtClass);

    StarChallengeBufferTileZombieKill();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onGameplayStarted();
    void gameplayEnded();
    bool CheckZombiesInBufferTile(Zombie* zombie);
    void ZombieConditionApplied(Zombie* i_zombie, int i_condition, pvztime_t i_duration);
    void ZombieConditionEnded(Zombie* i_zombie, int i_condition);

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
    std::vector<ZombiePtr> m_ZombiesInBufferTile;
};

class StarChallengeBufferTileZombieKillProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeBufferTileZombieKillProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeBufferTileZombieKill::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_BUFFERTILE_ZOMBIE_KILL_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_BUFFERTILE_ZOMBIE_KILL_NAME]"));
    }

    StarChallengeBufferTileZombieKillProps()
    : Count(0)
    {}

    int Count;
};

#endif /* STARCHALLENGEBUFFERTILEZOMBIEKILL_H_ */
