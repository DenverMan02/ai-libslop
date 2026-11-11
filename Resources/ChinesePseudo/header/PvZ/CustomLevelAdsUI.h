#ifndef __CUSTOM_LEVEL_ADS_UI_H__
#define __CUSTOM_LEVEL_ADS_UI_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"
#include "Widget.h"

class UIWidgetSheet;

class CustomLevelAds : public UIWidget
{
public:
	RT_CLASS_DEFINE(CustomLevelAds, UIWidget, RtClass);	
	
	CustomLevelAds();
	virtual ~CustomLevelAds();

	void SetType(const std::string& i_type);

	virtual void	Draw(Graphics* i_g) override;
	virtual void	OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	//PVZ2_CHINESE_START
    virtual const Sexy::Rect GetHitRect() override;

protected:
	// Protected Interface (Inheritable)

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;

	void onNotifyADWatchFinish(int i_type);

private:
    int m_currentTimes;
    int m_maxTimes;
	int m_adsType;
};


#endif