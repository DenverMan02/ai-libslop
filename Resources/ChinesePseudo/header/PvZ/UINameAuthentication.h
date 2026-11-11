//
//  UINameAuthentication.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UINameAuthentication_h_
#define _UINameAuthentication_h_

#include "UISingletonDialog.h"
#include "EditListener.h"

namespace Message
{
	void NameAuthenticationSuc(bool i_success);
}

class UINameAuthentication : public UISingletonDialog<UINameAuthentication>, public Sexy::EditListener
{
public:
	typedef Sexy::Delegate2<UINameAuthentication*, int> InputCallbackEvent;

	UINameAuthentication();
	virtual ~UINameAuthentication();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "NameAuthentication"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void authName();
	void                                SetCallback(InputCallbackEvent iEvent) { m_callbackEvent = iEvent; }
	bool isTextEmpty();
	bool isCanAuth();
	bool is_name_valid(const std::string& name);
	bool isAllChineseWord(const char* upsz);
	bool is_cardId_valid(const std::string& name);
	bool AllisNum(std::string str);
    std::string& trim(std::string& str);

    static UINameAuthentication* ShowDialog(bool shouldLogStatus);
private:
	class EditWidget*					m_pNameInput;
	class EditWidget*                   m_pCardInput;
	InputCallbackEvent                  m_callbackEvent;
	UIWidgetText* m_pSucText;
	UIWidgetText* m_pErrorText;
	UIWidgetText* m_pErrorText2;

	static bool _shouldLogStatus;// if should send player udid, pay sum, name, identity to server
};

#endif
