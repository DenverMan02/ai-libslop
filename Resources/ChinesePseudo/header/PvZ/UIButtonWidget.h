//
//  UIButtonWidget.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 3/4/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_UIButtonWidget_h
#define PlantsVersusZombies2_UIButtonWidget_h

#include "RtObject.h"
#include "TimeMgr.h"
#include "UIWidget.h"
#include "ResourceHelpers.h"
#include "core.h"
#include "PrimeTextWidget.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class UIButtonWidget : public UIWidget
{
public:
	RT_CLASS_DEFINE(UIButtonWidget, UIWidget, RtClass);
	
	UIButtonWidget();
	
	void Draw(Graphics* i_g) override;
	void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	void OnMouseMove(const int i_mouseX, const int i_mouseY) override;

	void SetColorLabel(Color& color) { m_labelColor = color; }
	void SetColorButton(Color& color) { m_buttonColor = color; }
	void SetLabelText(const SexyString& i_text, PrimeTypeface* typeface, Rect i_textRect, const Color& i_color);
	
	void SetImageNormal(CachedUIResourcePtr<Image> i_image) { m_normalImage = i_image; }
	void SetImagePressed(CachedUIResourcePtr<Image> i_image) { m_pressedImage = i_image; }
	
	void SetSoundPressed(std::string i_soundPressed) { m_soundPressed = i_soundPressed; }
	void SetSoundReleased(std::string i_soundReleased) { m_soundReleased = i_soundReleased; }
	
protected:
	virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

	// Protected Interface (Inheritable)
	
	virtual void		performButtonAction() {}

private:
	CachedUIResourcePtr<Image> m_normalImage;
	CachedUIResourcePtr<Image> m_pressedImage;
	
	Color	m_labelColor;
	Color	m_buttonColor;
	
	std::string		m_soundPressed;
	std::string		m_soundReleased;

	PrimeTextWidget*  m_labelWidget;
};

#endif
