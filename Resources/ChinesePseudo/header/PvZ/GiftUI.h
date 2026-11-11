//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GiftUI_h
#define PlantsVersusZombies2_GiftUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "Effect_BouncingArrow.h"
#include "MiniBoard.h"

enum eTreasureBtnAction
{
    eTreasureBtn_CloseAction     = -1,
    eTreasureBtn_GachaAction     = 0 ,
    eTreasureBtn_LuckyLeafAction = 1 ,
    eTreasureBtn_ToLuckyLeaf     = 2 ,
    eTreasureBtn_ToPendant       = 3 ,
    eTreasureBtn_ShowLeafStoreAction = 10
};

enum
{
    BoardUI_BtnShooter,
    BoardUI_BtnShowList,
    BoardUI_BtnChooseOne,
    BoardUI_BtnChooseTen,
    BoardUI_BtnOk,
};

enum
{
    TreasureStep_None = 0,
    TreasureStep_Scale = 1,
    TreasureStep_FlyTo = 2,
    
    TreasureStep_End = 3,
    TreasureStep_EndOne = 3,
    TreasureStep_EndTen = 4,
};

class CGiftUI;

class CSelectChangedHandler
{
public:
    CSelectChangedHandler(){};
    ~CSelectChangedHandler(){};
    
    virtual bool OnSelectChanged(Sexy::Widget* pCaller,int id){ return true;};
};

class CListItem: public Sexy::Widget
{
public:
    CListItem(){};
    ~CListItem(){};
    
    virtual void OnSelect(bool b){};
};

class CListPoolItem: public CListItem
{
private:
    ImagePtr    m_pImgTitle;
    ImagePtr    m_pImgHeader;
    ImagePtr    m_pImgSel[2];
    ImagePtr    m_pImgDef[2];
    class PVZ2UIButton* m_pBtn;
    int         m_iID;
public:
    CListPoolItem(int id);
    ~CListPoolItem();
    
    void    SetImgTitle(ImagePtr pImg);
    void    SetImgHeader(ImagePtr pImg);
    void    SetButton(class PVZ2UIButton* pBtn);
    void    SetButtonImgSel(ImagePtr pImg,ImagePtr pImgDown);
    void    SetButtonImg(ImagePtr pImg,ImagePtr pImgDown);
    
    virtual void OnSelect(bool b);
    virtual void Draw(Graphics* i_g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* i_g);
    virtual void Resize(int i_x,int i_y,int i_w,int i_h);
};

class CListPanel: public Sexy::Widget
{
    
public:
    CListPanel(class CListUI* pParent);
    ~CListPanel();
    
    virtual void Draw(Graphics* i_g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* i_g);
    virtual void Resize(int i_x,int i_y,int i_w,int i_h);
    
    void    AddItem(CListItem* pItem);
    void    ClearItem();
    void    SetItemW(int iW){ m_iItemW = iW;};
    void    SetItemH(int iH){ m_iItemH = iH;}
    void    SetItemIvX(int iIv){ m_iItemIvX = iIv;};
    void    SetItemIvY(int iIv){ m_iItemIvY = iIv;};
    void    SetGapX(int iGap){ m_iGapX = iGap;}
    void    SetGapY(int iGap){ m_iGapY = iGap;}
    
    void    SetBackGroundImg(ImagePtr pImg);
    void    Select(int i);
    void    Deselect(int i);
private:
    ImagePtr m_imgBk;
    int     m_iItemW;
    int     m_iItemH;
    
    //X interval between item
    int     m_iItemIvX;
    //Y interval between item;
    int     m_iItemIvY;
    //X space from two side board
    int     m_iGapX;
    //Y space from top board
    int     m_iGapY;


    std::vector<CListItem*> m_vecListItem;
    
    class CListUI*  m_pParent;
};

class CListUI: public Sexy::Widget,public ButtonListener,public Sexy::ScrollWidgetListener
{
public:
    CListUI();
    ~CListUI();
    
    virtual void Draw(Graphics* i_g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* i_g);
    virtual void Resize(int i_x,int i_y,int i_w,int i_h);
    virtual void ButtonPress(int i_id);
    virtual void ButtonDepress(int i_id);
   
    void    SetBackGroundImg(ImagePtr pImg){ m_imgBk = pImg;    };
    void    SetTitileImg(ImagePtr pImg)    { m_imgTitile = pImg; };
    void    SetSelectChangedHandler(class CSelectChangedHandler* pHandler){m_pSelectChangedHandler = pHandler;}
    
    CListPanel* GetListPanel(){return m_pListPanel;}
    void    SetHeaderH(int iH);
    void    SetXGap(int iXGap){ m_iXGap = iXGap;}
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {};
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {};

private:
    ImagePtr m_imgBk;
    ImagePtr m_imgTitile;
    int      m_iHeaderH;
    int      m_iXGap;
    int      m_iBottomGap;
    
    class CSelectChangedHandler* m_pSelectChangedHandler;
    class PVZ2UIScrollingWidget* m_pScrollWidget;
    CListPanel*  m_pListPanel;
    int   m_iLastSelectIdx;
};

#endif
