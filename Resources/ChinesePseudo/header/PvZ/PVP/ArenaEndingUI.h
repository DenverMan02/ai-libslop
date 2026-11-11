//
//  ArenaEndingUI.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-10-28.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaEndingUI__
#define __PlantsVersusZombies2__ArenaEndingUI__

#include "Core.h"
#include "ResourceHelpers.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"
//#include "PVZTypes.h"
#include "ArenaPrecompile.h"

namespace Message
{
    
}

class ArenaZombieWidget : public Sexy::Widget
{
public:
    ArenaZombieWidget();
    ~ArenaZombieWidget();
    
    void SetZombieSeedType(ZombieTypePtr i_zombieType);
    
    virtual void Draw(Sexy::Graphics* i_g);
    //virtual void Update();
    
    void drawToBuffer();
    
    void         DrawText(Graphics* i_g);
    
    void setNum(int i_num) { m_num = i_num; }
    
    ZombieTypePtr m_seedZombieType;
    DeviceImage*  m_seedPacketImage = NULL;
    
private:
    int m_num;
};

class ArenaEndingUI : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    ArenaEndingUI(ArenaResult i_result, const std::vector<ZombieRecord>& i_zombieList, bool i_league, int iStarNum = 0);
    virtual ~ArenaEndingUI();
    
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void Update();
    
    virtual void ButtonPress(int i_id);
    virtual void ButtonDepress(int i_id);
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void         SetNumStars(int i_num) { m_numStar = i_num; }
    //void         DrawNumStars(Sexy::Graphics* i_g);
    void        SetTutorial(bool setting) { m_bTutorial = setting; }

private:
    void InitView();
    void CreateZombieWidgets(Sexy::Rect i_rect);
    
    void RemoveEffectAnim();
    
    void CreateVictoryEffect();
    void OnVictoryEffectFinished(const std::string& i_animLabelName);
    
    void CreateFailedEffect();
    void OnFailedEffectFinished(const std::string& i_animLabelName);
    
    void CreateWordEffect();
    void OnWordEffectFinished(const std::string& i_animLabelName);
    
    void CreateMetalEffect();
    void OnMetalEffectFinished(const std::string& i_animLabelName);
    
    void CreateCoinEffect();
    void OnCoinEffectFinished(const std::string& i_animLabelName);
    
    void CreateCupEffect();
    void OnCupEffectFinished(const std::string& i_animLabelName);
    
    void CreateLeagueEffect();
    void OnLeagueEffectFinished(const std::string& i_animLabelName);
    
    void LayoutEffect(std::vector<class PopAnimRig*>& vecEffects);
    void UpdateEffect();
    
    void DrawEffect(Sexy::Graphics* i_g);
    
    void CreateLostInfo();
    
private:
    PVZ2UIButton*		m_startButton = nullptr;
    ArenaResult         m_result = Result_Won;
    std::vector<ZombieRecord> m_zombieRecords;
    int m_numStar = 0;
    SexyString          m_currencyTxt;
    SexyString          m_medalTxt;
    SexyString          m_cupTxt;
    
    bool                m_league = false;
    SexyString          m_leagueMedalTxt;
    SexyString          m_leagueCurrencyTxt;
    
    class PopAnimRig*   m_pAccountVictory = nullptr;
    class PopAnimRig*   m_pAccountFaild = nullptr;
    class PopAnimRig*   m_pAccountMetal = nullptr;
    class PopAnimRig*   m_pAccountCup = nullptr;
    class PopAnimRig*   m_pAccountCoin = nullptr;
    class PopAnimRig*   m_pAccountLeague = nullptr;
    class PopAnimRig*   m_pAccountLossWord = nullptr;
    
    bool  m_bMetalShowFinished = false;
    bool  m_bCoinShowFinished = false;
    bool  m_bCupShowFinished = false;
    bool  m_bWordShowFinished = false;
    bool  m_bLeagueShowFinished = false;
    SexyVector2         m_posOffset;
    bool  m_bTutorial = false;
};

#endif /* defined(__PlantsVersusZombies2__ArenaEndingUI__) */
