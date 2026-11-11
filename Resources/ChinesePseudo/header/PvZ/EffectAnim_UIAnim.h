//
//  EffectAnim_UIAnim.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/3/17.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef EffectAnim_UIAnim_h
#define EffectAnim_UIAnim_h

#include "RtDelegate.h"
#include "PopAnimRig.h"
#include "Effect_PopAnim.h"

class EffectAnim_UIAnim
{
public:
    EffectAnim_UIAnim();
    ~EffectAnim_UIAnim();
    
    typedef Delegate1<const std::string&> ThenDelegate;
//    typedef Delegate2<const std::string&, const std::string&> TheDpDelegate;
    
    void InitUIAnim(std::string i_anim, float i_scale, SexyVector2 i_point, bool i_center = true);
    void InitPlantUIAnim(std::string i_plantName, float i_scale, SexyVector2 i_point, bool i_center = true);
    
    void OnUpdate();
    void OnDraw(class Graphics* i_g);
    
    Effect_PopAnim* GetAnimPtr();
    PopAnimRig* GetPopAnimRig();
    void SetDrawScale(float i_scale);
    
    void HideAvatarLayer();
    void SetColor(const Sexy::Color &i_color);
    
    void HideLayer(std::string i_layer);
    void ShowLayer(std::string i_layer);
    
    void PlayIdleLoop();
    void PlayOnce(std::string i_anim);
    void PlayLoop(std::string i_anim);
    void PlayOnceThenLoop(std::string i_animOnce, std::string i_animLoop);
    void PlayOnceThen(std::string i_animOnce, ThenDelegate i_thenDo);
    
    std::string GetIdleAnim();
    float GetAnimTime(std::string i_anim);
    
    bool IsValid();
    void SafeRelease();
    
    void SetVisible(bool i_visible);
    bool IsVisible();
    
private:
    bool m_visible;
    
    pvztime_t m_loopingStartTime;
    std::string m_plantName;
    std::string m_idleAnimName;
    std::string m_loopingAnim;
    Effect_PopAnim* m_anim;
    PopAnim* m_pam;
};

#endif /* EffectAnim_UIAnim_h */
