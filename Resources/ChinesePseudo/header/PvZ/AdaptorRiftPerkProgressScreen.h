//
//  AdaptorRiftResultsScreen.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/29/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftPerkProgressScreen_h
#define AdaptorRiftPerkProgressScreen_h

#include <string>

#include "HotUIAdaptor.h"
#include "HotUISeedPacket.h"
#include "HotUIWidget.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class HotUIRiftPerkProgressScreenProperties : public HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(HotUIRiftPerkProgressScreenProperties, HotUIWidgetProperties, RtClass);
    
};

struct AdaptorRiftPerkProgressScreenParams
{
	AdaptorRiftPerkProgressScreenParams()
	{}
	
    ButtonDelegate DismissFunction;

};

class AdaptorRiftPerkProgressScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftPerkProgressScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Continue,
		Back,
	};
	
public:
	AdaptorRiftPerkProgressScreen();
	virtual ~AdaptorRiftPerkProgressScreen();

	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
	void SetParams(const AdaptorRiftPerkProgressScreenParams& i_params);
    
    void Update() override;
	
	void AnimateProgressBar();
	
	void Close();
    
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	void setup();
	void refresh();
	void onContinueClick();
    
	AdaptorRiftPerkProgressScreenParams m_params;
    
};

#endif
