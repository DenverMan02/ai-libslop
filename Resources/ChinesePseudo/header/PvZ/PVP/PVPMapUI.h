//
//  PVPMapUI.h
//  PlantsVersusZombies2
//
//  Created by csh on 15/10/13.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVPMapUI__
#define __PlantsVersusZombies2__PVPMapUI__

#include "RtDb.h"
#include "RtDelegate.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"
#include "ButtonListener.h"
#include "PVZ2UIButton.h"
#include "Effect_PopAnim.h"
#include "PVPManager.h"

#include "MapEditor.h"

class WorldMapCamera;
class PVPMapUI;

class PVPHouseData
{
public:
    void Update();
    void Destroy();
public:
    int houseId = 0;
    int zoneId = 0;
    ImagePtr btn_imageA;
    ImagePtr cloudImg;
    class PopAnimRig* m_achieveAnim = NULL;
    Sexy::Rect btn_rect;
    Sexy::Rect achieve_rect;
    SexyVector2 pos;
    bool btn_down = false;
    bool achieveEffectEnable = false;
    int achieveEffectValue = 0;
    int achieveEffectPosY = 0;
    int achieveGold = 0;
    int achieveMetal = 0;
};

typedef struct
{
    int zoneId = 0;
    SexyVector2 pos;
    ImagePtr lockBtn;
    Sexy::Rect btn_rect;
} PVPZoneData;

enum DialogType
{
    Dialog_unlockArea = 0,
    Dialog_unlockDisable,
    Dialog_defend,
    Dialog_attack,
    Dialog_main,
    Dialog_pvp,
};

enum PVPMapRenderLayer
{
    MAP_LAYER_BRIDGE = 0,
    MAP_LAYER_BRIDGE_END = 100,
    MAP_LAYER_HOUSE = 100,
    MAP_LAYER_HOUSE_END = 200,
};

struct StringComponent
{
    SexyString str;
    Sexy::PrimeTypeface* font;
    Color color;
    Sexy::Rect rect;
    DrawStringJustification just;
    
    StringComponent()
    : font(NULL)
    , color(Color::Black)
    , just(DS_ALIGN_LEFT)
    {
    }
    
    StringComponent(SexyString _str, Sexy::PrimeTypeface* _font, Color _color, Sexy::Rect _rect, DrawStringJustification _just)
    : str(_str)
    , font(_font)
    , color(_color)
    , rect(_rect)
    , just(_just)
    {
    }
};

typedef struct
{
    ImagePtr img;
    Sexy::Rect rect;
} WidgetComponent;

struct WidgetRects
{
    int index;
    Sexy::FRect rect;
    WidgetRects()
    : index(0)
    {
        
    }
    
    WidgetRects(int _index, Sexy::FRect _rect)
    : index(_index)
    , rect(_rect)
    {        
    }
};

struct WidgetImg
{
    int index;
    ImagePtr img;
    Sexy::Rect rect;
    WidgetImg()
    : index(0)
    {
        
    }
    
    WidgetImg(int _index, ImagePtr _img, Sexy::Rect _rect)
    : index(_index)
    , img(_img)
    , rect(_rect)
    {
        
    }
};

class WidgetDebugPosition : public Sexy::Widget
{
public:
    
    WidgetDebugPosition();
    virtual ~WidgetDebugPosition();
    
    void	Draw(Sexy::Graphics* i_g) override;
    void    TouchMoved(const Sexy::Touch& touch) override;
    void    TouchBegan(const Sexy::Touch& touch) override;
    void    TouchEnded(const Sexy::Touch& touch) override;
    
protected:
    std::map<int, Sexy::Rect*>      m_imageRectMap;
    
private:
    
    Sexy::Point     m_startPosition;
    bool            m_dragging;
    Sexy::Rect*     m_currentRect;
};

class PVPMapDialog : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    
    PVPMapDialog(PVPMapUI* pUI, DialogType dt, int zoneid, int houseid);
    virtual ~PVPMapDialog();
    
    virtual void    Update() override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    
    virtual void	ButtonPress(int i_id) override;
    virtual void	ButtonDepress(int i_id) override;
    void            TouchEnded(const Sexy::Touch& touch) override;
    
    void            SetCoolDown(int i_time);
    
private:
    DialogType      m_Dtype;
    int             m_houseId;
    int             m_zoneId;
    int             m_sourcesNum;
    int             m_sourcesSpeed;
    int             m_unlockPrice;
    float           m_fCoolDownEndTime;
    
    PVPMapUI*       m_PUI;
    PVZ2UIButton*   m_OKBtn;
    PVZ2UIButton*   m_CancelBtn;
    
    PVZ2UIButton*   m_achieveBtn;
    PVZ2UIButton*   m_defendBtn;
    
    PVZ2UIButton*   m_changeEnemyBtn;
    PVZ2UIButton*   m_scoutBtn;
    PVZ2UIButton*   m_attackBtn;
    ImagePtr        m_attackBtnImg;
    Sexy::Rect      m_attackBtnRect;
    class PopAnimRig* m_pEvilDaveHead;
    std::map<int, WidgetComponent>      m_imageComponents;
    std::map<int, StringComponent>      m_stringComponents;
    
    int gold;
    int totalGold;
    int goldSpeed;
    int metal;
    int totalMetal;
    int metalSpeed;
    int unlockPrice;
    int attackPrice;
    bool m_bEvilDavid;
};

class PVPMapUI :
public Sexy::ButtonListener, //  WidgetDebugPosition Sexy::Widget MapEditor
public MapEditor
{
public:
    
    PVPMapUI();
    virtual ~PVPMapUI();
    
    void            onShow();
    
    virtual void    Update() override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    virtual void	ButtonPress(int i_id) override;
    virtual void	ButtonDepress(int i_id) override;
    void            TouchMoved(const Sexy::Touch& touch) override;
    void            TouchBegan(const Sexy::Touch& touch) override;
    void            TouchEnded(const Sexy::Touch& touch) override;
    
    virtual void    OnGesturePinch(Sexy::Point i_centerPoint, int i_distanceBetweenFingersSquared, float i_scaleDelta) override;
    void            ShowDialog(DialogType dt, int zoneid = 0, int houseid = 0);
    void            KillDialog();
    
    
    void            onPVPNarrationFinished();
    
    void            OnPVPEvilDavilNarrationFailedFinished();
    void            OnPVPEvilDavilNarrationSuccessFinished();
    void            OnPVPEvilDavidNattationStartFinished();
    
private:
    void            initData();
    void            setupScreen();
    void            setCameraPosition(int deltaX, int deltaY);
    void            zoomMap(int x, int y, float deltaScale);
    void            flushStringComponents();
    void            setDownBtn(int id);
    void            setUnlockBtnDown(int id);
    void            resetDownBtn();
    void            colorEffectUpdate();
    void            unlockColorEffectUpdate();
    void            zoomEffectUpdate();
    void            enableZoomEffect();
    void            enableAchieveEffect(int index);
    void            achieveEffectUpdate();
    bool            isContain(FPoint rectPos,FPoint mp);
    bool            isContain(FPoint mp1,FPoint mp2,FPoint mp3,FPoint mp4,FPoint mp);
    float           Multiply(FPoint p1, FPoint p2, FPoint p0);
    
    bool            IsIndexValid(int iIndex, int iMax);
    void            DrawEvilDavid(Sexy::Graphics* pGraghics, void* pBigMapInfo, FPoint& stBasePoint);
    
protected:
    void            onPVPTrainingZombieChanged(bool bPlayEffect);
    
    void            refreshHouseAnim();
    
private:
    
    Effect_PopAnim *                        m_popAnimEffect;
    PVZ2UIButton*                           m_attackBtn;
    PVZ2UIButton*                           m_defendBtn;
    PVPHouseData*                           m_houseData[PVPMapHouseNum];
    PVPZoneData*                            m_zoneData[PVPMapZoneNum];
    
    Sexy::TouchID							m_toucheID[2];
    Sexy::Point								m_mouseStartPosition;
    bool                                    m_mouseDragging;
    bool                                    m_touchZoom;
    int                                     m_downBtnId;
    int                                     m_unlockBtnId;
    PVPMapDialog*                           m_dialog;
    
    Sexy::Widget*                           m_pZombiePanel;
    
    std::map<int, WidgetComponent>          m_imageComponents;
    std::map<int, StringComponent>          m_stringComponents;
    WidgetImg                               m_widgetImg[1000];
    int                                     m_widgetImgNum;
    Sexy::Color                             m_houseColor;
    bool                                    m_colorLerpAdd;
    float                                   m_zoomEffectValue;
    bool                                    m_zoomEffectAdd;
    bool                                    m_zoomEffectEnable;
    float                                   m_lastRefreshTime;
    class PopAnimRig*                       m_nameChangeAnimRig;
	float										m_timerDelayShow;
    float                                    m_timerRefresh = -1;
};







#endif /* defined(__PlantsVersusZombies2__PVPMapUI__) */
