/*
 * HotUIWidgetValue.h
 *
 *  Created on: 2023-3-31
 *      Author: admin
 */

#ifndef HOTUIWIDGETVALUE_H_
#define HOTUIWIDGETVALUE_H_

#include "HotUIWidget.h"

// Sort Widget
class HotUIWidgetValue: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIWidgetValue, HotUIWidget, RtClass);

	HotUIWidgetValue();

	virtual ~HotUIWidgetValue();

	inline void SetValue(float i_value) { m_value = i_value;}
	inline float GetValue() { return m_value; }

protected:
    float m_value;
};

class HotUIWidgetValueProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetValueProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetValueProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetValue::StaticGetClass();
	}
};


#endif /* HOTUIWIDGETVALUE_H_ */
