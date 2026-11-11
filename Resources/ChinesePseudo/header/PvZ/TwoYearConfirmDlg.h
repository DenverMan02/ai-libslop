//
//  TwoYearConfirmDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.28
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _TwoYearConfirmDlg_h_
#define _TwoYearConfirmDlg_h_

#include "UIEditor/UISingletonDialog.h"

class TwoYearConfirmDlg : public UISingletonDialog<TwoYearConfirmDlg>
{
public:
	enum
	{
		ConfirmType_Cancel,
		ConfirmType_Wechat_Friends,
        ConfirmType_WEchat_TimeLine,
	};
    
    enum {
        NO_WECHAT = 0,
        SHARE_FIRST = 1,
        SHARE_SECOND = 2,
    };
    
	typedef Sexy::Delegate2<int, int> CallbackEvent;		// param1-dialog type, param2-button clicked type
public:
	TwoYearConfirmDlg();
	virtual ~TwoYearConfirmDlg();
	virtual bool							OnCreate();
	virtual std::string					GetLayoutName() { return "TwoYearConfirm"; }
    virtual void							Draw(Sexy::Graphics* i_g);

	// ButtonListener
	virtual void							ButtonDepress(int i_id);

	void									SetType(int iType, const SexyString& strText, bool hasGift);
    void                                SetCallback(CallbackEvent callback) { m_callback = callback; }
    
    void                        onShareDataToWeChat(int iType, int iButtonID);
    void                        onShareDateSuccess(int iType, int iButtonID);
    
    void                        SetShareURL(const std::string url) { m_url = url; }
    
protected:
    void ShareWechatSuccess();
    void ShareWechatFailed();

protected:
	class UIWidgetText*			m_pWidgetText;
	class Widget*					m_pWidgetReward;
	int										m_iType;
	CallbackEvent					m_callback;
    
    std::string                 m_url;
};


#endif
