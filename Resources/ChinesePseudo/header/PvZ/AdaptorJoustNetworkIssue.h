//
//  AdaptorJoustNetworkIssue.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/2/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorJoustNetworkIssue__
#define __PlantsVersusZombies2__AdaptorJoustNetworkIssue__

#include "HotUIAdaptor.h"
#include "JoustDataPackets.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

class AdaptorJoustNetworkIssue : public HotUIAdaptor
{
public:	
	RT_CLASS_DEFINE(AdaptorJoustNetworkIssue, HotUIAdaptor, RtClass);

public:
	AdaptorJoustNetworkIssue(JoustAPINetworkIssue i_networkIssue, JoustAPIContext i_context);
	AdaptorJoustNetworkIssue();
	virtual	~AdaptorJoustNetworkIssue();

protected:
	
	void ButtonDepress(int i_buttonID) override;
	
	// Override for basic widgets
	bool		OnBackButtonPressed() override;

	// UI View Link Handling
	void		onLoadUIView() override;
	void		onLinkToUIViewCreated() override;
	
	void onButtonRetry();
	void onButtonFail();
	
	void				refresh();

	JoustAPINetworkIssue		m_networkError;
	JoustAPIContext 			m_networkContext;
};

#endif
