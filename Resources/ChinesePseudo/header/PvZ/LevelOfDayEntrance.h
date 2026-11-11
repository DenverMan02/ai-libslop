//
//  LevelOfDayEntrance.hpp
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/13.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef LevelOfDayEntrance_h
#define LevelOfDayEntrance_h

#include "PopingWidget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "RealObject.h"
#include "Core.h"
#include "MagentoService.h"
#include "StateMachine.h"
#include "StateMachineTableBuilder.h"
#include "EffectAnim_UIAnim.h"

enum ArrowDirection
{
    AD_None,
    AD_Left,
    AD_Right,
    AD_Up,
    AD_Down
};

struct StartOffset
{
    int index;
    int startX;
    int startY;
};

struct ArrowInfo
{
    int startX;
    int startY;
    ArrowDirection dir;
};

class LevelOfDayItem : public Widget
{
public:
    LevelOfDayItem(int i_inidex);
    virtual ~LevelOfDayItem();
    void Draw(Sexy::Graphics* i_g) override;
    void DrawFinishedMark(Sexy::Graphics* i_g);
    void SetScaling(bool i_scaling);
    
private:
    Image*       m_bgImage;
    int          m_dayIndex;
    bool         m_special;
    bool         m_scaling;
    bool         m_highLight;
    pvztime_t    m_startScaleTime;
};

class LevelOfDayEntrance;

class LevelOfDayPanel : public Widget
{
public:
    LevelOfDayPanel(Rect &i_rect, LevelOfDayEntrance* i_entrance);
    virtual ~LevelOfDayPanel();
    
    void Draw(Sexy::Graphics* i_g) override;
    
    void	InitView();
    
private:
    LevelOfDayEntrance* m_entrance = nullptr;
};

class LevelOfDayEntrance : public PopingWidget, public ButtonListener//, public Sexy::ScrollWidgetListener
{
public:
    LevelOfDayEntrance();
    ~LevelOfDayEntrance();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void UpdateTimeLabel();
    void OnRefresh();
    
//    void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
//    void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    
    void CalcStartOffset();
    StartOffset GetStartOffsetByIndex(int i_index);
    void AddDayItem(LevelOfDayItem* i_item);
    void ClearDayItem();
    
private:
    void InitView();
    
    void AddResourceGroups();
    void ReleaseResourceGroups();
    void DrawArrow(Graphics* i_g);
    std::string GetLeveloftheDayLevelName();
    
private:
    Rect m_titleRect;
    Rect m_hintRect;
    Rect m_timeLebelRect;
    Rect m_timeShowRect;
    Rect m_panelRect;
    
    bool        m_refreshed;
    
    int m_iBaseX;
    int m_iBaseY;
    
    SexyString  m_title;
    SexyString  m_timeToShow;
    
    EffectAnim_UIAnim            m_nyButton;
    std::vector<std::string>     m_loadedGroup;
    std::vector<StartOffset>     m_startOffset;
    std::vector<ArrowInfo>       m_arrowDir;
    std::vector<LevelOfDayItem*> m_items;
    
    Color m_timeColor;
    LevelOfDayPanel* m_levelOfDayPanel;
    
    class PVZ2UIButton*         m_closeBtn;
    class PVZ2UIButton*         m_startBtn;
    class PVZ2UIButton*         m_salesBtn;
};

#endif /* LevelOfDayEntrance_h */
