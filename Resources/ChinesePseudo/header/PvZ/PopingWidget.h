//
//  PopingWidget.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/10.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PopingWidget_h
#define PopingWidget_h

#include "Widget.h"
#include "TimeMgr.h"
#include "core.h"

enum PopingType
{
    PVZ_BEGIN_FLAG_ENUM(PT_),
    
    PVZ_FLAG(PT_FromUp),
    PVZ_FLAG(PT_FromLeft),
    PVZ_FLAG(PT_FromRight),
    PVZ_FLAG(PT_FromDown),
    PVZ_FLAG(PT_FromCenter),
    PVZ_FLAG(PT_FromMiddle),
    
    PVZ_FLAG(PT_ToUp),
    PVZ_FLAG(PT_ToLeft),
    PVZ_FLAG(PT_ToRight),
    PVZ_FLAG(PT_ToDown),
    PVZ_FLAG(PT_ToCenter),
    PVZ_FLAG(PT_ToMiddle),
    
    PVZ_FLAG(PT_Scaled),
    PVZ_FLAG(PT_Fade),
    
    PVZ_END_FLAG_ENUM(PT_),
};
PVZ_MAKE_ENUM_BIT_OPERATORS(PopingType);

class PopingWidget : public Sexy::Widget
{
public:
    PopingWidget();
    ~PopingWidget();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void StartPop();
//    virtual void ButtonDepress(int i_id);
    
    Sexy::SexyVector2 GetCurrentPosition() { return m_currentPos; }
    
    Rect GetMainRect() { return m_mainRect; };
    void SetMainRect(Rect i_rect) { m_mainRect = i_rect; };
    
    void SetPopingScales(float i_start, float i_dest);
    void SetStartPosition(Sexy::SexyVector2 i_start);
    void SetTargetPosition(Sexy::SexyVector2 i_dest);
    void SetPopingPositions(Sexy::SexyVector2 i_start, Sexy::SexyVector2 i_dest);
    void SetPopingTime(pvztime_t i_popingTime);
    
    void DrawPopingImage(Sexy::Graphics* i_g, class Image* i_image, Rect i_rect);
    void DrawPopingImage(Sexy::Graphics* i_g, class Image* i_image, int i_x, int i_y, int i_w, int i_h);
    void DrawPopingMirrorImage(Sexy::Graphics* i_g, class Image* i_image, Rect i_rect);
    void DrawPopingMirrorImage(Sexy::Graphics* i_g, class Image* i_image, int i_x, int i_y, int i_w, int i_h);
    void DrawPoping9SliceImage(Sexy::Graphics* i_g, const Rect i_rect, class Sexy::Image* i_image);
    void DrawPoping9SliceImage(Sexy::Graphics* i_g, class Sexy::Image* i_image, const Rect i_rect);
    void DrawPoping3SliceImage(Sexy::Graphics* i_g, const Rect i_rect, Sexy::Image* i_image);
    void DrawPoping3SliceImage(Sexy::Graphics* i_g, Sexy::Image* i_image, const Rect i_rect);
    void WritePopingWordInRect(Graphics* i_g, const SexyString& i_label, const Rect& i_inRect, Sexy::PrimeTypeface* i_font, Color i_color, DrawStringJustification i_justification, bool i_wrapped);
    
    void DrawPopingBoxImage(Sexy::Graphics* i_g, class Image* i_image, Rect i_rect);
    void DrawPopingBoxImage(Sexy::Graphics* i_g, Rect i_rect, class Image* i_image);
    
    virtual void HideAllButtonAndAnims() {}
    virtual void RecoverAllButtonAndAnims() {}
    
    void NormalInit(PopingType i_type, float i_popingTime = 0.3f);
    void ClearPopingType() { m_popingType = PT_None; }
    void AddPopingType(PopingType i_type) { m_popingType |= i_type; }
    void RemovePopingType(PopingType i_type) { m_popingType &= i_type; }
    bool HasPopingType(PopingType i_type) { return (i_type & m_popingType); }
    
    bool IsPoping() { return m_poping; }
    
private:
    Rect        m_mainRect;
    
    SexyVector2 m_startPos;
    SexyVector2 m_destPos;
    SexyVector2 m_currentPos;
    
    float       m_startScale;
    float       m_destScale;
    float       m_currentScale;
    
    pvztime_t   m_startTime;
    pvztime_t   m_popingTime;
    pvztime_t   m_endTime;
    
    bool        m_fade;
    bool        m_poping;
    
    PopingType  m_popingType;
};

#endif /* PopingWidget_h */
