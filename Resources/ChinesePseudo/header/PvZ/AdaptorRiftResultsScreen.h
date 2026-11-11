//
//  AdaptorRiftResultsScreen.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/29/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftResultsScreen_h
#define AdaptorRiftResultsScreen_h

#include <string>

#include "HotUIAdaptor.h"
#include "HotUISeedPacket.h"
#include "HotUIWidget.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class HotUIRiftResultsScreenProperties : public HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(HotUIRiftResultsScreenProperties, HotUIWidgetProperties, RtClass);
    
};

struct AdaptorRiftResultsScreenParams
{
	AdaptorRiftResultsScreenParams()
		: Win(false)
		, JustBeatZomboss(false)
	{}
	
	bool Win;
	bool JustBeatZomboss;
    ButtonDelegate DismissFunction;

};

class AdaptorRiftResultsScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftResultsScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Continue,
		Back,
	};
	
public:
	AdaptorRiftResultsScreen();
	virtual ~AdaptorRiftResultsScreen();

	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
	void SetParams(const AdaptorRiftResultsScreenParams& i_params);
    
    void Update() override;
	
	void Close();
    
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	void setup();
	void setupFirstClearReward(class MapEventItem* i_event, int i_difficulty);
	void refresh();
	void onContinueClick();
    void playWinLossText();
    void awardPerkPoints();
    
    std::string getWinLossAnimLabelSuffix() const;
    
	AdaptorRiftResultsScreenParams m_params;
	std::vector<HotUIAdaptor*> m_entries;
};

#endif
