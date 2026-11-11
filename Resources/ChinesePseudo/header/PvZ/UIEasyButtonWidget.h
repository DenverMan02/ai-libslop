//
//  UIEasyButtonWidget.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/8/25.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIEasyButtonWidget_h
#define UIEasyButtonWidget_h

#include "RtObject.h"
#include "TimeMgr.h"
#include "UIWidget.h"
#include "ResourceHelpers.h"
#include "core.h"

namespace Sexy {
    class Graphics;
}  // namespace Sexy

class UIEasyButtonWidget : public UIWidget
{
public:
    RT_CLASS_DEFINE(UIEasyButtonWidget, UIWidget, RtClass);
    
    UIEasyButtonWidget();
    
    void Draw(Graphics* i_g) override;
    void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    void SetPressedChangeLight(bool i_change);
    
    void SetImageNormal(const std::string& i_image);
    void SetImagePressed(const std::string& i_image);
    
    Image* GetImageNormal() { return m_normalImage; }
    Image* GetImagePressed() { return m_pressedImage; }
    
    void SetSoundPressed(const std::string& i_soundPressed) { m_soundPressed = i_soundPressed; }
    void SetSoundReleased(const std::string& i_soundReleased) { m_soundReleased = i_soundReleased; }
    
    void SetOnPressed(bool pressed) { m_onPressed = pressed; }
    bool GetIsOnPressed() { return m_onPressed; }
    
    void AddNotice(const std::string& i_image = "IMAGE_UI_HUD_WORLDMAP_NOTICE_ICON", float x = -0.1f, float y = 0.f);// x,y is percent
    void RemoveNotice();
    
    void SetButtonAction(std::function<void()> i_onActivate){ m_onActivate = i_onActivate; }
    
protected:
    virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
protected:
    ImagePtr m_normalImage;
    ImagePtr m_pressedImage;
    ImagePtr m_noticeImage;
    
    Color m_buttonColor;
    float m_noticeX = 0;
    float m_noticeY = 0;
    
    std::string	m_soundPressed;
    std::string	m_soundReleased;
    
    bool m_onPressed = false;
    
    std::function<void()> m_onActivate = nullptr;
};

#endif /* UIEasyButtonWidget_h */
