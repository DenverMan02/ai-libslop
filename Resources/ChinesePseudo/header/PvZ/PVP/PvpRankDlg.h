//
//  PvpRankDlg.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 2015.11.20.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _PvpRankDlg_h_
#define _PvpRankDlg_h_

#include "UISingletonDialog.h"
#include "PlaybackData.h"
#include "NetworkData.h"

class PvpRankDlg;

class RankTitleWidget : public Sexy::Widget
{
public:
    RankTitleWidget(PvpRankDlg* pPvpRankDlg);
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    void                    TouchBegan(const Sexy::Touch& touch) override;
    
    void                    SetLeagueInfo(const S2C_PVP_LeagueInfo& info);
    
    PvpRankDlg*             m_pPvpRankDlg;
    S2C_PVP_LeagueInfo      m_leagueInfo;
    SexyString              m_title;
    Image*                  m_iconImage;
    int                     m_pos;
};

////////////////////////////////////////////////////////////////////////////////////
class RankItemWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RankItemWidget(int rowIdx, int rankType, PvpRankDlg* pPvpRankDlg);
    RankItemWidget(PvpRankDlg* pPvpRankDlg);
    virtual void			Resize(int theX, int theY, int theWidth, int theHeight) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    void                    TouchBegan(const Sexy::Touch& touch) override;
    void                    TouchEnded(const Sexy::Touch& touch) override;
    
    virtual void			ButtonDepress(int i_id) override;
    
    void                    onSelected(bool selected);
    
    bool                    m_bIsShowMore;
    bool                    m_bIsLoadFinish;
    
    PvpRankDlg*             m_pPvpRankDlg;
    int                     m_iRowIdx;
    bool                    m_bIsSelected;
    
    int32                   m_iScrollTouchID;
    
    class PVZ2UIButton*     m_pBtnSeePark;
    class PVZ2UIButton*     m_pBtnSeeArmy;
    
    int                     m_rankType;
    S2C_PVP_RankInfo        m_rankInfo;
    
};

////////////////////////////////////////////////////////////////////////////////////
class PvpArmyDlg : public UISingletonDialog<PvpArmyDlg>
{
public:
	PvpArmyDlg();
	virtual ~PvpArmyDlg();
	virtual bool            OnCreate();
	virtual std::string     GetLayoutName() { return "PvpSeeArmy"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();

	// ButtonListener
	virtual void            ButtonDepress(int i_id);
    
    void                    SetRankInfo(const S2C_PVP_RankInfo& info);
    void                    SetZbList();
    
    class UIWidgetText*     m_pTextTitle;
    class UIScrollControl*  m_pScrollMain;
    S2C_PVP_RankInfo        m_rankInfo;
};

////////////////////////////////////////////////////////////////////////////////////
#define Pre_Garden_Rank_Count   3

class PvpRankDlg : public UISingletonDialog<PvpRankDlg>
{
public:
    PvpRankDlg();
    virtual ~PvpRankDlg();
    virtual bool            OnCreate();
    virtual std::string     GetLayoutName() { return "PvpRank"; }
    virtual void            Draw(Sexy::Graphics* i_g);
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    virtual void            Update();
    
    // ButtonListener
    virtual void            ButtonDepress(int i_id);
    
    void                    onRowSelected(int rowIdx, int rankType);
    void                    onRowSelected(int rowIdx, class UIScrollControl* scroll, std::vector<RankItemWidget*>& rankItems);
    
    void                    ViewUserArmy(S2C_PVP_RankInfo rankInfo);
    
protected:
    void                    refreshScroll(int rankType, class UIScrollControl* scroll, std::vector<RankItemWidget*>& rankItems, const std::vector<S2C_PVP_RankInfo>& rankList);
    void                    setGardenInfo();
    void                    setGardenTitleInfo();
    
private:
    void                    onNotifyPreviewModeBegin();
    void                    onNotifyAddOtherUserZbList(int64 profileId);
    
private:
    class UITabControl*     m_pTabControl;
    class UITabContent*     m_pTabMain;
    class UIScrollControl*  m_pScrollRankTitle = nullptr;
    class UIScrollControl*  m_pScrollAward = nullptr;
    
    class UIScrollControl*  m_pScrollLeague;
    std::vector<RankItemWidget*>  m_leagueRankItems;
    class UIWidgetText*     m_pText;
    bool                    m_isRequestLeagueData;
    int                     m_leagueMaxCount;
    
    class UITabContent*     m_pTabCur;
    class UIScrollControl*  m_pScrollGarden;
    std::vector<RankItemWidget*>  m_gardenRankItems;
    int                     m_gardenMaxCount;
    
    class UIWidgetText*     m_pTextLast;
    class UIWidgetText*     m_pTextLastRank[Pre_Garden_Rank_Count];
    class UIWidgetText*     m_pTextLastAward[Pre_Garden_Rank_Count];
    bool                    m_isRequestGardenData;
    
    S2C_PVP_RankInfo        m_requestRankInfo;
    
};


#endif
