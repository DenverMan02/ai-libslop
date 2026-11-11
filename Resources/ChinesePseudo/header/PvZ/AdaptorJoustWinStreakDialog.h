//
//  AdaptorJoustWinStreakDialog.hpp
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alex on 9/22/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustWinStreakDialog_h
#define AdaptorJoustWinStreakDialog_h

#include "HotUIAdaptor.h"
#include "RtObject.h"

#include "RtReflectionDelegate.h"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class AdaptorJoustWinStreakDialog : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustWinStreakDialog, HotUIAdaptor, RtClass);

	void Close();
	
	void Setup(const ButtonDelegate& i_continue);
	void ButtonDepress(int i_buttonID) override;
	
protected:
	void onLoadUIView() override;
	
private:
	void refresh();
	
	ButtonDelegate m_continue;
};

#endif /* AdaptorJoustWinStreakDialog_h */
