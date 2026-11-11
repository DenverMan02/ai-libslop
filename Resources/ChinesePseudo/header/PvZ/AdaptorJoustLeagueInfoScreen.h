//
//  AdaptorJoustLeagueInfoScreen_h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 8/16/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustLeagueInfoScreen_h
#define AdaptorJoustLeagueInfoScreen_h

#include "HotUIAdaptor.h"
#include "AdaptorJoustLeagueInfoEntry.h"
#include "RtObject.h"

class AdaptorJoustLeagueInfoScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustLeagueInfoScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Close
	};
	
protected:
	~AdaptorJoustLeagueInfoScreen();
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
	void ButtonDepress(int i_buttonID) override;
	
	bool OnBackButtonPressed() override;
	
private:
	void onClose();
	
	void refresh();
	
	std::vector<AdaptorJoustLeagueInfoEntry*> m_leagueEntries;
};


#endif
