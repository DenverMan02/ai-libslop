//
//  HotUIPropertyAnimator.h
//  PvZ2
//
//  Created by Sola, Joseph on 11/2/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef HotUIPropertyAnimator_h
#define HotUIPropertyAnimator_h

#include "HotUIWidget.h"
#include "HotUIComponent.h"
#include "Curve.h"

enum PropertyAnimatorTarget
{
    PAT_WidgetX,
    PAT_WidgetY,
};

struct PropertyAnimatorCurveParams
{
    PropertyAnimatorCurveParams()
    : StartValue(0.0f)
    , EndValue(0.0f)
    , Duration(0.0f)
    , PhaseOffset(0.0f)
    {}
    
    // Starting value of the animation
    float StartValue;
    // Ending value of the animation
    float EndValue;
    // Amount of time to spend in the animation
    float Duration;
    // Ranges from 0 to 1, modifies the starting position within the animation as a fraction of total animation time
    float PhaseOffset;
};

class HotUIPropertyAnimator : HotUIComponent
{
public:
    RT_CLASS_DEFINE(HotUIPropertyAnimator, HotUIComponent, RtClass);
    
    virtual void Update() override;
    
protected:
    virtual void onInitializeComponent() override;
    
private:
    void applyValueToProperty(float i_value, PropertyAnimatorTarget i_property, HotUIWidget* i_target);

    pvztime_t m_startTime;
};

class HotUIPropertyAnimatorProperties : HotUIComponentProperties
{
public:
    RT_CLASS_DEFINE(HotUIPropertyAnimatorProperties, HotUIComponentProperties, RtClass);
    
    HotUIPropertyAnimatorProperties()
    : TargetProperty(PAT_WidgetX)
    , Curve(CURVE_CONSTANT)
    {}
    
    virtual RtClass* GetComponentClass() const override
    {
        return HotUIPropertyAnimator::StaticGetClass();
    }
    
    CurveType Curve;
    PropertyAnimatorTarget TargetProperty;
    
    // This set of properties is applied, exactly as specified, to the first widget in the Targets list
    PropertyAnimatorCurveParams FirstTargetCurve;
    // Each subsequent target uses the properties of the previous target, with NextTargetDelta values added to it
    // This allows you to set up, for example, staggered animations that cascade across several widgets in a row.
    PropertyAnimatorCurveParams NextTargetDelta;
};

#endif /* HotUIPropertyAnimator_h */
