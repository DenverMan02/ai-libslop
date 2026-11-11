//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetType_h_
#define _UIWidgetType_h_

#include "UIRect.h"

class UIWidgetType;
//------------------------------------------------------------------------------------------------------------------------------
// WidgetFactory
//------------------------------------------------------------------------------------------------------------------------------
//namespace UI
//{
template<typename T>
class WidgetFactory;

/*
template <>
class WidgetFactory<PVZ2UIButton *>
{
public:
static const std::string& GetTypeName() const;
static PVZ2UIButton * ToWidget(class Sexy::Widget* pWidget);
};
*/

#define WIDGETFACTORY_DEFINE(T, _NAME) \
template <>\
class WidgetFactory <class T * >\
{\
public:\
	static const std::string&		GetTypeName();\
	static class T*						GetWidget(class Sexy::Widget* pWidget);\
	static class Sexy::Widget*	TypeToWidget(UIWidgetType* pWidgetType, T* pWidget);\
	static bool								WidgetToType(UIWidgetType* pWidgetType, T* pWidget);\
	static bool								IsWrite(UIWidgetType* pWidgetType, const std::string& propName);\
    static bool								IsHave(UIWidgetType* pWidgetType, const std::string& propName);\
};

#include "UIWidgetTypeFactory.h"
#undef WIDGETFACTORY_DEFINE

//}

//------------------------------------------------------------------------------------------------------------------------------
// UIWidgetType
//------------------------------------------------------------------------------------------------------------------------------
class UIWidgetType
{
public:
    UIWidgetType();
	~UIWidgetType() {}

	class Sexy::Widget*		ToWidget(Sexy::Widget* pWidget);
	bool									FromWidget(Sexy::Widget* pWidget, bool bRescurive = true);
	void									InitWidget(Sexy::Widget* pWidget);
	bool									IsPropertyNeedWrite(const std::string& propName);
    bool									HasProperty(const std::string& propName);
    
    static bool             IsAutoWidget(Sexy::Widget* pWidget);
	
public:
	std::string m_Type;
	std::string m_Name;
	int	m_ID = 0;
	float m_X = 0;
	float m_Y = 0;
	float m_Width = 50;
	float m_Height = 50;
	bool m_Clip = true;
	std::string m_Text;
	std::string m_ImageNormal;
	std::string m_ImageDown;
	std::string m_ImageBack;
	int			m_ImageType;
    SexyVector2 m_Scale;    // UIWidgetAnim
    Sexy::Color m_Color;
    Sexy::Color m_PressColor;
    int         m_FontIndex = -1;
    int         m_Align = 0;
    float       m_Rotate = 0.0f;
    std::string m_Label;
	std::vector<UIWidgetType> m_Childs;
	bool		m_drawTab = true;
	int m_tabWidth = 0;
	int m_tabHeight = 0;
};

typedef std::vector<UIWidgetType> VecUIWidgetType;


#endif
