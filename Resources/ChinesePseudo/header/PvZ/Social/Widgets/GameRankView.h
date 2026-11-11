//
//  GameRankView.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-7-25.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GameRankView__
#define __PlantsVersusZombies2__GameRankView__


#include "PVZ2UIButton.h"
#include "ProfileUtils.h"
#include "PVZ2UIAwardScreen.h"
#include "SocialMgr.h"

enum GameRankButtonId
{
    GameRank_Button_Id_Close = 0,
    GameRank_Button_Id_Start,
    GameRank_Button_Id_View_Formation,
    GameRank_Button_Id_NoStar
};

class RankWidget : public Widget
{
public:
    RankWidget(GameRankInfo &i_info, int i_ranking);
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void Draw(Graphics *i_g);
    
private:
    void InitView();
    
    GameRankInfo m_rankInfo;
    int m_ranking;
    
    Image *m_imgRank;
    Image *m_iconBG;
    Image *m_icon;
    SexyString m_name;
    SexyString m_time;
    
    Rect    m_rectIcon;
    Rect    m_rectRankIcon;
    Rect    m_rectName;
    Rect    m_rectTime;
    Rect    m_rectBG;
};

class GameRankView : public Widget, Sexy::ButtonListener
{
public:
    GameRankView(std::string i_levelName);
    ~GameRankView();
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void Update();
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    void SelectTab(int i_tabId);
    void RefreshRank();
    void OnFetchGameRank();
    
    void MergeGameRank();
private:
    void InitView();
    
    Image*                              m_imgRibbon;
    SexyString                          m_strStarTitle;
    std::vector<SexyString>             m_starDescriptions;
    SexyString                          m_strMyScore;
    
    Rect                                m_rectStarDialog;
    Rect                                m_rectStarInternal;
    Rect                                m_rectScoreDialog;
    Rect                                m_rectScoreInternal;
    Rect                                m_rectMyScoreInternal;
    Rect                                m_rectRibbon;
    Rect                                m_rectStarTitle;
    Rect                                m_rectDescBorder;
    Rect                                m_rectReward;
    std::vector<Rect>                   m_rectStarDescs;
    
    std::vector<class PVZ2UIButton*>	m_tabButtons;
    PVZ2UIButton*                       m_closeButton;
    PVZ2UIButton*                       m_starButton;
    PVZ2UIButton*                       m_viewFormationButton;
    std::vector<RankWidget*>            m_rankWidgets;
    
    std::string                         m_levelName;
    int                                 m_levelIndex;
    
    int                                 m_numStars;
    int                                 m_activeStarIndex;
    class PopAnimRig*                   m_rig[3];
    std::vector<ProfileUtils::ChallengeStatusHolder> m_challengeDisplays;
    
    bool                                m_loadDataSuccess;
    int                                 m_selectTabId;
    std::vector<GameRankInfo>           m_gameRankInfos;
    GameRankItem                        m_localGameRankItem;
};

#endif /* defined(__PlantsVersusZombies2__GameRankView__) */
