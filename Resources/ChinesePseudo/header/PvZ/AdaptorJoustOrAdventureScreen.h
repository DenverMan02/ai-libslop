//
//  AdaptorJoustOrAdventureScreen.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/29/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustOrAdventureScreen_h
#define AdaptorJoustOrAdventureScreen_h

#include "HotUIAdaptor.h"
#include "RtObject.h"
#include "IHttpDriver.h"
#include "Curve.h"

class JoustAPIResponse;
class AdaptorJoustNetworkConnection;

namespace Message
{
	void JoustShowingFUEInAdventureScreen(bool i_showingFUE);
}

class AdaptorJoustOrAdventureScreen : public HotUIAdaptor, public INetworkStatusListener
{
	RT_CLASS_DEFINE(AdaptorJoustOrAdventureScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Adventure,
		Joust
	};
	
	enum JoustState
	{
		Available,
		Unavailable,
		AvailableButOffline,
		None
	};
	
public:
	AdaptorJoustOrAdventureScreen();
	virtual ~AdaptorJoustOrAdventureScreen();
	
	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
protected:
	void Update() override;
	
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
	void NetworkStatusChanged( IHttpDriver::NetworkStatus status ) override;

private:
	void setup();
	void close();
	
	bool canHandleInput();
	
	void updateJoustState();
	void setJoustState(JoustState i_state);
	void setFUEState(bool i_showingFUE);
	void onJoustNarrativeComplete();
	void onHotUIAnimFinished(const std::string& i_animName);

	bool m_online = false;
	bool m_showingFUE = false;
	JoustState m_currentJoustState = JoustState::None;
};

#endif /* AdaptorJoustOrAdventureScreen_h */
