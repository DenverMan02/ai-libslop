//
//  PVZ2UIBuyPlantDialog.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang "Zhang Xu cai" on 4-23-2014.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UIBuyGiftDialog__
#define __PlantsVersusZombies2__PVZ2UIBuyGiftDialog__

#include "MagentoService.h"
#include "PVZ2UIButton.h"

enum BuyGiftButtonId
{
    BuyGift_Id_Buy = 0,
    BuyGift_Id_Cancel
};

namespace Message
{
    void ReflashStoreGiftUI();
}

class PVZ2UIBuyGiftDialog : public Widget, public Sexy::ButtonListener
{
public:
	PVZ2UIBuyGiftDialog(){ }
    PVZ2UIBuyGiftDialog(MagentoProductPropsPtr i_props, bool i_quick = true);
    virtual ~PVZ2UIBuyGiftDialog();
    virtual void    Draw(Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void    Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void    ButtonDepress(int i_id);
protected:
    MagentoProductPropsPtr m_props;
    bool    m_quick;
    float   m_progress;
    int     m_price;
    
    PVZ2UIButton*   m_btnBuy;
    PVZ2UIButton*   m_btnCancel;
    
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
    
    void ConfigGiftContent();
    void onPopRewardPressed();
    
    enum EGiftCostType
    {
        eGiftCostType_Coin = 0,
        eGiftCostType_Gem,
    };
    
    EGiftCostType m_eGiftCostType;
};

#endif /* defined(__PlantsVersusZombies2__PVZ2UIBuyGiftDialog__) */
