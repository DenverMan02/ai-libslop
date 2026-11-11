
#ifndef Effect_DinoShadow_hpp
#define Effect_DinoShadow_hpp

#include "TimeLine.h"
#include "EffectObject.h"

class Effect_DinoShadowProps : public EffectObjectPropertySheet
{
public:
    RT_CLASS_DEFINE(Effect_DinoShadowProps, EffectObjectPropertySheet, RtClass);
    
    Effect_DinoShadowProps()
    {
        MoveDuration = 5.0f;
        MoveDistance = 1000.0f;
        Scale = 4.0f;
        Alpha = 136;
    }
    
    pvztime_t	MoveDuration;
    float		MoveDistance;
    float		Scale;
    int         Alpha;
};

class Effect_DinoShadow : public EffectObject
{
public:
    RT_CLASS_DEFINE(Effect_DinoShadow, EffectObject, RtClass);
    Effect_DinoShadow();
    ~Effect_DinoShadow();
protected:
    void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
    void onUpdate() override;
private:
    CurveCollection_Float m_movementCurves;
};

#endif /* Effect_DinoShadow_hpp */
