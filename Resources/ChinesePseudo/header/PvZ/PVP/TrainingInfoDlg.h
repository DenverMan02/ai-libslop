//
//  TrainingInfoDlg.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.11.5
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TrainingInfoDlg__
#define __PlantsVersusZombies2__TrainingInfoDlg__

#include "UISingletonDialog.h"
#include "UIListener.h"
#include "ObjectTypeDescriptor.h"

//---------------------------------------------------------
class TrainingInfoDlg : public UISingletonDialog<TrainingInfoDlg>
{
public:
    TrainingInfoDlg();
    virtual ~TrainingInfoDlg();
    virtual bool							OnCreate();
    virtual std::string                 GetLayoutName() { return "TrainingInfo"; }
    virtual void							Draw(Sexy::Graphics* i_g);
    virtual void							DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
    
    // ButtonListener
    virtual void							ButtonDepress(int i_id);
    
    void                                SetType(ObjectTypeDescriptorPtr i_objectType);
    
protected:
    class AlmanacPage*                  m_pAlmanacPage;
    Sexy::Widget*                       m_pBackground;
    
};


#endif /* defined(__PlantsVersusZombies2__TrainingInfoDlg__) */
