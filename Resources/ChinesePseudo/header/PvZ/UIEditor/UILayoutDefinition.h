//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UILayoutDefinition_h_
#define _UILayoutDefinition_h_

#include "PropertySheetBase.h"
#include "UIRect.h"
#include "UIWidgetType.h"
#include "RtSerial.h"
#include "Reflection.h"

//------------------------------------------------------------------------------------------------------------------------------
// UILayoutDefinition
//------------------------------------------------------------------------------------------------------------------------------
class UILayoutDefinition : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(UILayoutDefinition, PropertySheetBase, RtClass);
	virtual bool Serialize(const Sexy::RtSerializeContext& inContext) override;
	bool WriteWidgetTypeChilds(Reflection::RCustomType* pCustomType, VecUIWidgetType& vecWidgetTypes, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey);
    
	static UILayoutDefinition*				GetLayout(const std::string& strLayout);
	static UILayoutDefinition*				GetLayoutByPath(const std::string& path);
    static UILayoutDefinition*				GetLayoutCurrent();

	std::vector<std::string>&				GetResGroups() { return m_resGroups; }
	std::vector<UIWidgetType>&		GetWidgets() { return m_Widgets; }

    bool                                IsNeedDarkenBG(void) const;
    bool								NeedAttachLawnApp(void) const;
public:
	std::vector<std::string>					m_resGroups;
	std::vector<UIWidgetType>			m_Widgets;
    bool                                m_bNeedDarkenBG = false;
    bool								m_bNeedAttachLawnApp = true;
};


#endif
