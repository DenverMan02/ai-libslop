//
//  WorldMap_StarConvert.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/28.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMap_StarConvert_h
#define WorldMap_StarConvert_h

#include "UIEasyButtonWidget.h"
#include "EffectAnim_UIAnim.h"
#include "StarConvertConfig.h"
#include "Image.h"

class WorldMap_StarConvert : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_StarConvert, UIEasyButtonWidget, RtClass);
    
    WorldMap_StarConvert();
    virtual ~WorldMap_StarConvert();
    
    virtual void    onUpdate() override;
    
    virtual void    Draw(Graphics* i_g) override;
    
    void            CheckActivated();
    void            OnRefreshStarConvert();
    
private:
    void            OnButtonClicked();
    void            RefreshShouldDrawBubble();
    bool            ShouldDrawBubble();
    
private:
    bool                m_canGet;
    ConvertObject       m_convertObject;
    EffectAnim_UIAnim   m_plantAnim;
    SexyString          m_stars;
    Image*              m_featureImg = nullptr;
};

namespace Message
{
    void RefreshStarConvert();
}

#endif /* WorldMap_StarConvert_h */
