//
//  UIBossChallengeReward.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/9/1.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIBossChallengeReward_h
#define UIBossChallengeReward_h

#include "UISingletonDialog.h"

class UIBossChallengeReward : public UISingletonDialog<UIBossChallengeReward>
{
public:
    UIBossChallengeReward();
    virtual ~UIBossChallengeReward();
    virtual bool							OnCreate();
    virtual std::string				GetLayoutName() { return "BossChallengeReward"; }
    virtual void							Draw(Sexy::Graphics* i_g);
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id);
    
private:
    void OnBossChallengeReward(int result, const class S2C_BossChallengteReward* data);
    void OnNetworkError(int erroId, const std::string& requestID);
    void UpdateInterview();
private:
    int m_errorCode = 0;
    int m_state = 0;
    int m_gem = 0;
    int m_coin = 0;
    int m_head = -1;
    int m_rank = 0;
    int m_pecent = 0;
    SexyString m_tip;
    class UIHeadshotIcon* m_headWidget = nullptr;
};

#endif /* UIBossChallengeReward_h */
