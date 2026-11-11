//
//  AdaptorSecurityGourdDialog.h
//  PlantsVersusZombies2
//
//  Created by Randy Knapp on 7/18/17
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdaptorSecurityGourdDialog__
#define __PlantsVersusZombies2__AdaptorSecurityGourdDialog__

#include "HotUIAdaptor.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"

typedef std::function<void()> ButtonCallback;

class AdaptorSecurityGourdDialog : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorSecurityGourdDialog, HotUIAdaptor, RtClass);

public:
	AdaptorSecurityGourdDialog();
	virtual	~AdaptorSecurityGourdDialog();
	
	void Setup(int i_cost, int i_gemCount, const ButtonCallback& i_onAccept, const ButtonCallback& i_onDecline, const ButtonCallback& i_onOpenGemStore);
	void Close();
	
	void ButtonDepress(int i_buttonID) override;
	bool OnBackButtonPressed() override;

protected:
	void onLoadUIView() override;
	
private:
	void refresh();
	void onGemCurrencyChanged(int delta, const bool i_willBeBankedLater);
	
private:
	int m_cost;
	int m_gemCount;
	ButtonCallback m_onAccept;
	ButtonCallback m_onDecline;
	ButtonCallback m_onOpenGemStore;
};

#endif
