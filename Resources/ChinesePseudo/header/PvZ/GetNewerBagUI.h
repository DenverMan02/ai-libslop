//
//  GetNewerBagUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GetNewerBagUI__
#define __PlantsVersusZombies2__GetNewerBagUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "EditListener.h"
#include "EditWidget.h"
#include "NetworkServiceManager.h"


class GetNewerBagUI : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::EditListener, public Sexy::NetworkServiceListener
{
public:
    
	GetNewerBagUI(bool i_ignoreCode = false,bool bNewer=true);
	virtual ~GetNewerBagUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void            RequestRechargeCheck(int i_retries = 0);
	void            TryRequest();
	void            OnRequestFinished(std::string i_json);

	void            ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
	void            ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context);
	void            ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
	void            ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);
    
	virtual void    EditWidgetText(int i_id, const SexyString& i_string);
	virtual bool    AllowChar(int i_id, SexyChar i_char);
    
private:
    
    void setupScreen();
    
    void drawShadedBox(Graphics* i_g, Rect extents);
    
    void GetBag(int itype = -1);
    void onCloseDialog();

private:
    
    class PVZ2UIEditWidget*         m_editWidget;
    
    PVZ2UIButton * 					m_button_cancel;
    PVZ2UIButton * 					m_button_ok;
    PVZ2UIButton * 					m_button_get;
    Sexy::Rect                      m_rectDialog;
    bool                            m_bNewer;
    
    bool           					m_haveGet;
    int32                 			m_retriesLeft;
    int32              				m_randomSeed;
    Image*							m_giftImage;
    Image*							m_giftImageTitle;
    SexyString						m_giftTitle;
    SexyString						m_giftDesc;

};

#endif /* defined(__PlantsVersusZombies2__GetNewerBagUI__) */
