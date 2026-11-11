//
//  DangerRoomRewardUI.h
//  PlantsVersusZombies2
//
//  Created by Li, Jie (Jeffty) on 15/9/15.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomRewardUI__
#define __PlantsVersusZombies2__DangerRoomRewardUI__

#include "UIWidget.h"
#include "SeedPacket.h"
#include "Point.h"
#include "VictoryOutro.h"

struct RewardEffect
{
    std::string plantPiecesName;
    int piecesCount;
    RtWeakPtr<Effect_PopAnim>     m_RewardEffectMain;
    SexyVector2 m_StartPos;
    SexyVector2 m_EndPos;
    std::vector< RtWeakPtr<Effect_PopAnim> >     m_RewardEffectParticle;
    std::vector< SexyVector2 > m_ParticlePos;
    int m_iNextParticleIndex;
};

class DangerRoomRewardUI : public Widget
{
public:
    DangerRoomRewardUI();
    virtual ~DangerRoomRewardUI();
    
    virtual void Draw(Graphics* i_g);
    
    void InitDangerRoomRewardAnim(int LevelIndex, int currentScore, int gainScore);
    void InitDangerRoomRewardSkipLevel(int LevelIndex);
    void SetDangerRoomBonusFromServer(int i_gems);
    
    bool IsRewardSkipping() { return m_skippingReward; }
    
protected:
    virtual void MouseUp(const int i_mouseX, const int i_mouseY, const int i_clickCount);

    void onNotifyRewardStart(int i_level, int i_currentScore, int i_totalScore);
    void onNotifySkipLevelRewardStart(int iLevelIndex);
    void OnBackToMap();
    void DrawSkipLevelAnim(Graphics* i_g);
    void DrawSkipLevelAnimConfirm(Graphics* i_g);
    void DrawScoreAnim(Graphics* i_g);
    void DrawScoreConfirmAnim(Graphics* i_g);
    void DrawFirstAnim(Graphics* i_g);
    void DrawSecondAnim(Graphics* i_g);
    void DrawThirdAnim(Graphics* i_g);
    void DrawDiamondAnim(Graphics* i_g);
    void DrawWaitConfirm(Graphics* i_g);
    
    void OnCloseDialog();
    void OnGetDangerRoomBonus(bool i_success);
    void OnGetDangerRoomSkippingBonus(bool i_success);
    
protected:
    const int m_iMaxParticleCount;
    const int m_iMaxEffectCount;
    const float m_fRewardAnimTime;
    
    std::vector<RewardEffect> m_stRewardEffect;
    RtWeakPtr<Effect_PopAnim>     m_RewardEffectDiamond;
    int m_iRewardEffectDiamond;
    
    RtWeakPtr<Effect_PopAnim>     m_ScoreShow;
    
    std::map<std::string, int> m_mapSkipLevelItems;
    int m_iSkipLevelMoneyAmount;
    int m_iSkipLevelDiamondAmount;
    
    pvztime_t m_fDurationTime;
    
    enum RewardState
    {
        E_SHOW_SCORE,
        E_WAIT_SCORE_CONFIRM,
        E_SHOW_PIECES_SELECT1,
        E_SHOW_PIECES_SELECT2,
        E_SHOW_PIECES_SELECT3,
        E_SHOW_DIAMOND,
        E_WAIT_CONFIRM,
        
        E_SHOW_SKIP_LEVEL,
        E_SHOW_SKIP_LEVEL_FINISH
    };
    
    RewardState m_eStep;
    
    PrimeTextWidget* m_scoreTotal;
    PrimeTextWidget* m_scoreGet;
    
    int m_currentLevel;
    int m_currentScore;
    int m_gainScore;
    bool m_skippingReward;
    
    friend class DangerRoomRewardAnim;
    RtWeakPtr<class DangerRoomRewardAnim> m_pAnimCtrl;
};

class DangerRoomRewardAnim : public GameObject
{
public:
    RT_CLASS_DEFINE(DangerRoomRewardAnim, GameObject, RtClass);
    
    void SetMyUI(DangerRoomRewardUI* pUI){ m_pUI = pUI; }
    
    void onSkipLevelAnimDone(const std::string& i_label);
    void onScoreAnimDone(const std::string& i_label);
    void onFirstAnimDone(const std::string& i_label);
    void onSecondAnimDone(const std::string& i_label);
    void onThirdAnimDone(const std::string& i_label);
    void onDiamondAnimDone(const std::string& i_label);
    
protected:
    DangerRoomRewardUI* m_pUI;
};


#endif /* defined(__PlantsVersusZombies2__DangerRoomRewardUI__) */
