//
//  GameMaskUI.h
//  PlantsVersusZombies2
//
//  Created by Eric Nan on 15-4-20.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GameMaskUI_h
#define PlantsVersusZombies2_GameMaskUI_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "Effect_FloatingText.h"

class GameMaskUI : public Sexy::Widget
{
public:
    enum MaskArrowType
    {
        Arrow_None,
        Arrow_Up,
        Arrow_Down,
        Arrow_Left,
        Arrow_Right,
    };
public:
    
    GameMaskUI(Sexy::SexyVector2 vMaskTargetPos
               , int iMaskTargetRadius
               , Sexy::Widget* pEvent = nullptr
               , std::string strLawnDesc = "");
    ~GameMaskUI();
    static GameMaskUI* ShowMask(Sexy::Widget* i_widget, MaskArrowType i_arrowType,
                                const std::string& i_desc = "", Rect i_rect = Rect());

    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(ModalFlags* theFlags, Graphics* g) override;
    void Update() override;
    void DoClose();
    
    void TouchBegan( const Sexy::Touch& i_touch ) override;
    void TouchMoved( const Sexy::Touch& i_touch ) override;
    void TouchEnded( const Sexy::Touch& i_touch ) override;
    void TouchesCanceled() override;

    void SetArrowOffset(int iOffsetX, int iOffsetY, float iRot) { m_vArrowOffset = {(float)iOffsetX, (float)iOffsetY}; m_iArrowRot = iRot; }
    void SetDialogOffset(int iOffsetX, int iOffsetY) { m_vDialogOffset = {(float)iOffsetX, (float)iOffsetY}; }
    void SetInFront(Sexy::Widget* pWidget);
    void SetToFront();
    
    void SetIsArrowExist(bool bExist) { m_bArrowExist = bExist; }
    
    void RefreshDialogText(const SexyString& strText);

    void EnableScale(bool i_enable);

    void SetIgnoreCheck(bool i_ignore) { m_ignoreCheck = i_ignore; }

private:
    
    void DrawMask(Sexy::Graphics* pGraphics, int iX, int iY, int iW, int iH);
    void InitView();
    void DrawRaduius(Sexy::Graphics *i_g);
    void DrawDialog(Sexy::Graphics *i_g);
    void AddArrow();
    void DrawArrow(Sexy::Graphics *i_g);
    void UpdateArrow();
    Sexy::SexyVector2 GetBasePos();
    void UpdateClose();
    void DrawClose(Sexy::Graphics *i_g);
    void OnCloseAnimEnd(const std::string &strLabel);
    bool IsMouseOnButton(const Sexy::Touch& touch);    
    Touch TouchConver(const Sexy::Touch& pTouch);
    
private:
    
    pvztime_t         m_iStartChangingTime;
    Sexy::Widget*     m_pEventWidget;

    //about radius
    Sexy::SexyVector2 m_vMaskTargetPos;
    int               m_iTargetRadius;
    bool              m_bRadiusChanging;
    Sexy::SexyVector2 m_vMaskWorldPos;
    
    //about arrow
    Sexy::SexyVector2 m_vArrowOffset;
    float             m_iArrowRot;
    class PopAnimRig* m_pArrowRig;
    bool              m_bArrowExist;
    
    //about dialog
    bool              m_bDialogChanging;
    bool              m_bDialogVisible;
    Sexy::SexyVector2 m_vDialogOffset;
    std::string       m_strLawnString;
    Sexy::PrimeTextWidget* m_pDialogTextWidget;
    Sexy::SexyVector2 m_vDialogPos;
    
    //about pop close
    class PopAnimRig* m_pPopClose;
    bool			  m_ignoreCheck;
};

//------------------------------------------------------------------------------------------

#endif
