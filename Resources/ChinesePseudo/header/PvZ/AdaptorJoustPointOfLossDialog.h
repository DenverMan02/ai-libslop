//
//  AdaptorJoustPointOfLossDialog.cpp
//  PlantsVersusZombies2
//
//  Created by Alexander Kobylarek 9/8/17
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorJoustPointOfLossDialog__
#define __PlantsVersusZombies2__AdaptorJoustPointOfLossDialog__

#include "AdaptorPointOfLossDialog.hpp"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class AdaptorJoustPointOfLossDialog : public AdaptorPointOfLossDialog
{
	RT_CLASS_DEFINE(AdaptorJoustPointOfLossDialog, AdaptorPointOfLossDialog, RtClass);

public:
	AdaptorJoustPointOfLossDialog();
	virtual	~AdaptorJoustPointOfLossDialog();
	
	void SetOnResumePlay(const ButtonDelegate& i_onResumePlay);
	void ButtonDepress(int i_buttonID) override;
	
	void SetConfirmationVisible(bool i_visible);

protected:
	
	void refresh() override;
	void onLoadUIView() override;
	
	ButtonDelegate m_onResumePlay;
};

#endif
