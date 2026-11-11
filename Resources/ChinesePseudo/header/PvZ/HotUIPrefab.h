//
//  HotUIPrefab.h
//  PlantsVersusZombies2
//
//  Created by Alex Gelles on 8/15/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved, son!
//

#ifndef __PlantsVersusZombies2__HotUIPrefab__
#define __PlantsVersusZombies2__HotUIPrefab__

#include "HotUIWidget.h"
#include "HotUIAdaptor.h"


class HotUIPrefab : public HotUIWidget
{
public:

	RT_CLASS_DEFINE(HotUIPrefab, HotUIWidget, RtClass);

	HotUIPrefab()
	{ };

	virtual ~HotUIPrefab();
	void RemovedFromManager(WidgetManager* theWidgetManager) override;
	template<typename T>
	T* GetWidgetByName(const std::string& name) const
	{
		return m_hotUIAdaptor->GetWidgetByName<T>(name);
	}
	
	template<typename T>
	T* GetAdaptor() const
	{
		return m_hotUIAdaptor->CastChecked<T>();
	}
	
protected:
	void onInitializeWidget() override;
	
private:
	void RemoveChildren();
	
private:
	HotUIAdaptor* m_hotUIAdaptor;
	
};


class HotUIPrefabProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIPrefabProperties, HotUIWidgetProperties, RtClass);

	HotUIPrefabProperties()
	{
		
	};

	RtClass* GetWidgetClass() const override
	{
		return HotUIPrefab::StaticGetClass();
	}

public:
	std::string UIFileName;
	std::string AdaptorClassName;
};

#endif
