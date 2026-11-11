//
//  TrainingConfirmDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.11.5
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TrainingConfirmDlg__
#define __PlantsVersusZombies2__TrainingConfirmDlg__

#include "UISingletonDialog.h"
#include "UIListener.h"

//---------------------------------------------------------
class TrainingConfirmDlg : public UISingletonDialog<TrainingConfirmDlg>
{
public:
    typedef Sexy::Delegate1<int> CallbackEvent;
public:
    TrainingConfirmDlg();
    virtual ~TrainingConfirmDlg();
    virtual bool							OnCreate();
    virtual std::string                 GetLayoutName() { return "TrainingConfirm"; }
    virtual void							Draw(Sexy::Graphics* i_g);
    virtual void							DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id);
    
    void                                SetCallback(CallbackEvent callback) { m_callback = callback; }
    void                                SetMessage(const SexyString& strTitle, const SexyString& strMsg);
    void                                SetBackground(Sexy::Image* pImage);
    
protected:
    CallbackEvent					m_callback;
    
};


#endif /* defined(__PlantsVersusZombies2__TrainingConfirmDlg__) */
