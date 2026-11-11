//
//  AdaptorJoustNetworkConnection.h
//  PlantsVersusZombies2
//
//  Created by Randy Knapp on 7/18/17
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorJoustNetworkConnection__
#define __PlantsVersusZombies2__AdaptorJoustNetworkConnection__

#include "HotUIAdaptor.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "HotUIImage.h"
#include "HotUILabel.h"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class AdaptorJoustNetworkConnection : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustNetworkConnection, HotUIAdaptor, RtClass);

public:
	AdaptorJoustNetworkConnection();
	virtual	~AdaptorJoustNetworkConnection();
	
	void Close();
	
	void ButtonDepress(int i_buttonID) override;
	bool OnBackButtonPressed() override;

protected:
	void onLoadUIView() override;
};

#endif
