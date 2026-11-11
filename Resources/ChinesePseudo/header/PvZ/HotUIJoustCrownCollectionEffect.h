//
//  HotUIJoustCrownCollectionEffect.h
//  PvZ2
//
//  Created by Sola, Joseph on 11/15/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef HotUIJoustCrownCollectionEffect_h
#define HotUIJoustCrownCollectionEffect_h

#include "HotUIWidget.h"
#include "Curve.h"
#include "TimeLine.h"

struct CrownCollectionEffectInstance
{
    pvztime_t StartTime = 0.0f;
    float AngleRadians = 0.0f;
};

class HotUIJoustCrownCollectionEffect : HotUIWidget
{
public:
    RT_CLASS_DEFINE(HotUIJoustCrownCollectionEffect, HotUIWidget, RtClass);
    
    void StartEffects(int i_numCrowns, float i_overTime);
    
protected:
    void onInitializeWidget() override;
    void onDraw(Sexy::Graphics* i_g) override;
    
private:
    void buildEffectCurves();
    
    ImagePtr m_image;
    CurveSequenceCollection<float> m_effectCurves;
    std::vector<CrownCollectionEffectInstance> m_effectInstances;
};

class HotUIJoustCrownCollectionEffectProperties : HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(HotUIJoustCrownCollectionEffectProperties, HotUIWidgetProperties, RtClass);
    
    RtClass* GetWidgetClass() const override
    {
        return HotUIJoustCrownCollectionEffect::StaticGetClass();
    }
    
    std::string CrownImage;
    float ImageWidth;
    
    float FadeInTime;
    float TweenTime;
    float TweenDistance;
    CurveType TweenCurve;
    float MinAngleRadians = 0.0f;
    float MaxAngleRadians = SEXYMATH_2PI;
};
#endif /* HotUIJoustCrownCollectionEffect_h */
