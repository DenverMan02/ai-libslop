/*
 * StarChallengeCardGameTurnPass.h
 *
 *  Created on: 2022-7-11
 *      Author: admin
 */

#ifndef STARCHALLENGECARDGAMETURNPASS_H_
#define STARCHALLENGECARDGAMETURNPASS_H_

#include "ChallengeModule.h"
#include "ChallengeUI.h"
#include "TodStringFile.h"

class StarChallengeCardGameTurnPass : public Challenge
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPass, Challenge, RtClass);

    virtual void registerForEvents() override;

    StarChallengeCardGameTurnPass();

	SexyString GetProgressDescription() const override;

private:
    void gameplayStarted(int i_turn);
    void gameplayEnded();

    virtual ChallengeUI* getChallengeUI() override
    {
        return m_UI->Cast<ChallengeUI>();
    }

    RtWeakPtr<UIWidget> m_UI;
    int m_currentTurn;
};

class StarChallengeCardGameTurnPassProps : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPassProps, LevelModuleProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeCardGameTurnPass::StaticGetClass();
    }

    virtual SexyString GetDescription() const override
    {
        SexyString cast = StrFormat(_S("%d"), Count);
        return TodReplaceString(_S("[STARCHALLENGE_CARD_GAME_TURN_PASS]"), _S("{COUNT}"), cast);
    }

    virtual SexyString GetDescriptiveName() const override
    {
        return TodStringTranslate(_S("[STARCHALLENGE_CARD_GAME_TURN_PASS_NAME]"));
    }

    StarChallengeCardGameTurnPassProps()
    : Count(0)
    {}

    int Count;
};

class StarChallengeCardGameTurnPassBeta : public StarChallengeCardGameTurnPass
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPassBeta, StarChallengeCardGameTurnPass, RtClass){}

};

class StarChallengeCardGameTurnPassBetaProps : public StarChallengeCardGameTurnPassProps
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPassBetaProps, StarChallengeCardGameTurnPassProps, RtClass){}

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeCardGameTurnPassBeta::StaticGetClass();
    }
};

class StarChallengeCardGameTurnPassGamma : public StarChallengeCardGameTurnPass
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPassGamma, StarChallengeCardGameTurnPass, RtClass){}

};

class StarChallengeCardGameTurnPassGammaProps : public StarChallengeCardGameTurnPassProps
{
public:
    RT_CLASS_DEFINE(StarChallengeCardGameTurnPassGammaProps, StarChallengeCardGameTurnPassProps, RtClass){}

    virtual RtClass* GetModuleClass() const override
    {
        return StarChallengeCardGameTurnPassGamma::StaticGetClass();
    }
};



class ChallengeCardGameTurnPassUI : public ChallengeUI
{
public:
    RT_CLASS_DEFINE(ChallengeCardGameTurnPassUI, ChallengeUI, RtClass);

    ChallengeCardGameTurnPassUI();
    void SetCurrent(int count);
    void SetTarget(int target);
protected:
    virtual SexyString getCountText() override;

private:
    int	m_current;
    int m_target;
};

#endif /* STARCHALLENGECARDGAMETURNPASS_H_ */
