/*
 * StarChallengeBlowBarrelZombie.h
 *
 *  Created on: 2022-8-10
 *      Author: zhousen
 */

#ifndef STARCHALLENGEBLOWBARRELZOMBIE_H_
#define STARCHALLENGEBLOWBARRELZOMBIE_H_


#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"


class StarChallengeBlowBarrelZombie : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeBlowBarrelZombie, Challenge, RtClass);

    StarChallengeBlowBarrelZombie();

    virtual void registerForEvents() override;
	virtual SexyString GetProgressDescription() const override;

protected:
	void onZombieBlow(Zombie* zombie);
	bool CheckZombiesInToss(Zombie* zombie);
	void onGameplayStarted();
    void gameplayEnded();

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_Count;// kill zombie count
};

class StarChallengeBlowBarrelZombieProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeBlowBarrelZombieProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeBlowBarrelZombie::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_BLOW_BARREL_ZOMBIE_DESC]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_BLOW_BARREL_ZOMBIE_NAME]"));
    }

    StarChallengeBlowBarrelZombieProps()
    : Count(0)
    {}

    int Count;
};



#endif /* STARCHALLENGEBLOWBARRELZOMBIE_H_ */
