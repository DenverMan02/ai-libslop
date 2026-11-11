//
//  PVZ2UIBuyPlantDialog.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-8-8.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UIBuyPlantDialog__
#define __PlantsVersusZombies2__PVZ2UIBuyPlantDialog__

#include "MagentoService.h"
#include "PVZ2UIButton.h"

enum BuyPlantButtonId {
    BuyPlant_Id_Buy = 0,
    BuyPlant_Id_Cancel
};

class PVZ2UIBuyPlantDialog : public Widget, public Sexy::ButtonListener
{
public:
	PVZ2UIBuyPlantDialog(){ }
    PVZ2UIBuyPlantDialog(MagentoProductPropsPtr i_props, bool i_quick = true);
    virtual ~PVZ2UIBuyPlantDialog();
    virtual void    Draw(Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void    Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void    ButtonDepress(int i_id);
protected:
    MagentoProductPropsPtr m_props;
    bool    m_quick;
    float   m_progress;
    int     m_price;
    int     m_actid;
    
    PVZ2UIButton*   m_btnBuy;
    PVZ2UIButton*   m_btnCancel;
    Image*			m_imgIcon   = NULL;
    Image*          m_imgBanner = NULL;
    
    SexyString  m_strTitle;
    SexyString  m_strDesc;
    SexyString  m_strProgress;
    
    Rect    m_rectDialog;
    Rect    m_rectInternal;
    Rect    m_rectTitle;
    Rect    m_rectDesc;
    Rect    m_rectBannerBg;
    Rect    m_rectBanner;
    Rect    m_rectProgress;
    
    void onUseGemFinish(const bool& isSuccess);
};

#endif /* defined(__PlantsVersusZombies2__PVZ2UIBuyPlantDialog__) */
