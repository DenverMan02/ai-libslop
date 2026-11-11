//
//  BoardDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.3.10
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _BoardDlg_h_
#define _BoardDlg_h_

#include "UISingletonDialog.h"
#include "UIWidgetRadio.h"
#include "NetworkData.h"
#include "UIListener.h"

class BoardDlg : public UISingletonDialog<BoardDlg>, public UI::RadioListener
{
public:
	BoardDlg();
	virtual ~BoardDlg();
	virtual bool            OnCreate() override;
    //virtual void            OnClose() override;
	virtual std::string     GetLayoutName() override { return "board"; }
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;

	// ButtonListener
	virtual void            ButtonDepress(int i_id) override;
    // UI::RadioListener
    virtual void            RadioSelectionChanged(class UIWidgetRadio* pRadioBtn) override;
    
    void                    InitInfoList(const S2C_NoticeInfoList& infoList);
    void                    RefreshTabList();
    void                    RefreshContent();
protected:
    void                    onNotifyBoardInfoGetReward(const S2C_NoticeInfoGet* pData);
    class BoardTabBtn*      getTabBtn(int i_id);
    
    void                    hideAllRewards(Sexy::Widget* pParent);
    void                    layoutAllRewards(Sexy::Widget* pParent);
    class BoardRewardIcon*  getNewReward(Sexy::Widget* pParent);
    void                    setReward(Sexy::Widget* pParent, Sexy::Image* pImage, int i_num);
    void                    showReward(Sexy::Widget* pParent, const S2C_CurrencyInfo& currencyInfo);

private:
    class UIScrollControl*      m_pScrollTabs = NULL;
    class UIScrollControl*      m_pScrollContent = NULL;
    class UIWidgetText*         m_pTitleText = NULL;
    class UIWidgetText*         m_pContentText = NULL;    
    class UIWidgetImage*         m_pContentImage = NULL;
    Sexy::Widget*               m_pRewardWidget = NULL;
    std::vector<S2C_NoticeInfo> m_infoList;
    int                         m_selectedBoardID = 0;
    Rect                        m_rectBg;
    Rect                        m_rectBgMore;
    Rect                        m_rectScroll;
    Rect                        m_rectScrollMore;
    Rect                        m_rectBoardTabBtn;
public:
    static bool              s_NeedShow;
};

//------------------------------------------------------
// BoardTabBtn
//------------------------------------------------------
class BoardTabBtn : public UIWidgetRadio
{
public:
    BoardTabBtn(int i_id, const SexyString& text);
    virtual void        Draw(Sexy::Graphics* i_g) override;
    
    void                SetNew(bool setting) { m_bNew = setting; }
    void                SetReward(bool setting) { m_bReward =  setting; }
    
protected:
    bool                m_bNew = true;
    bool                m_bReward = true;
    Sexy::Image*        m_pImageNew = NULL;
    Sexy::Image*        m_pImageReward = NULL;
    Sexy::Image*        m_pImageUnselectedMask = NULL;
    Sexy::Widget*       m_pRewardBack = NULL;
};

//------------------------------------------------------
// BoardRewardIcon
//------------------------------------------------------
class BoardRewardIcon : public Sexy::Widget
{
public:
    virtual void        Draw(Sexy::Graphics* i_g) override;
    void                SetReward(Sexy::Image* pImage, int i_num);
protected:
    Sexy::Image*        m_pIconImage = NULL;
    SexyString          m_strNum;
};


#endif
