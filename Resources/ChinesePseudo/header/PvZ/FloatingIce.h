//
//  FloatingIce.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/3/26.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FloatingIce__
#define __PlantsVersusZombies2__FloatingIce__

#include "RiverEntity.h"

class FloatingIce : public RiverEntity
{
public:
     RT_CLASS_DEFINE(FloatingIce, RiverEntity, RtClass);
    
    FloatingIce();
    virtual ~FloatingIce();
    
    void FloatingIceInitialize();
    
    void SetCarryingDodoRider(bool i_carrying);
    bool IsCarryingDodoRider();
    Rect GetFloatingIceRect();
    void DragingDodoRider();
    void PlayCarryingAnim();
    void SetPlayCarryingAnim(bool i_play);
    void StartToSink();
    void PlayRiseAnim();
    void PlaySinkAnim();
    virtual int CalcRenderOrder() const override;
    
    bool IsSinking() { return m_sinking; }
    bool IsSinked() { return m_sinked; }
    
private:
    
    void initializePAM(PopAnim* i_popAnim);
    void onAnimStopped(const std::string& i_animName);
    
private:
    bool m_sinked;
    bool m_sinking;
    bool m_isCarryingDodoRider;
    bool m_needPlayCarryingAnim;
};

#endif /* defined(__PlantsVersusZombies2__FloatingIce__) */
