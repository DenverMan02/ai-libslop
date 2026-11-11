//
//  LostNetActivityUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 2016/12/28.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef LostNetActivityUI_H
#define LostNetActivityUI_H

#include "PVZ2UIButton.h"
#include "PopingWidget.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "MagentoService.h"

class LostNetActivityUI : public PopingWidget, public ButtonListener
{
public:
    LostNetActivityUI();
    ~LostNetActivityUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void OnPaid();
    
    void InitView();
    
private:
    void UpdateBonus();
    void UpdateTimeLabel();
    void CheckAndPay();
    void OnBuyOfflineBundle(MagentoProductProps* i_props);
    void BuyOfflineBundleSuccess();
    
private:
    bool m_inited = false;
    int m_todayBonusId;
    
    SexyString m_timeLabelPre = _S("");
    SexyString m_timeLabel = _S("");
    SexyString m_gemsBonus = _S("");
    SexyString m_bonusName = _S("");
    SexyString m_coinBonus = _S("");
    SexyString m_bubble1 = _S("");
    SexyString m_bubble2 = _S("");
    SexyString m_price1 = _S("");
    SexyString m_price2 = _S("");
    SexyString m_price3 = _S("");
    
    Rect m_bgRect;
    Rect m_gemBonusRect;
    Rect m_todayBonusImgRect;
    Rect m_todayBonusRect;
    Rect m_coinBonusRect;
    
    Rect m_bubbleHint1;
    Rect m_bubbleHint2;
    
    Rect m_priceRect;
    Rect m_price1Rect;
    Rect m_price2Rect;
    Rect m_price3Rect;
    
    Rect m_closeRect;
    Rect m_buttonRect;
    Rect m_timeLabelRect;
    
    Color m_plantNameColor;
    
    Image* m_bonusImg;
    
    PVZ2UIButton* m_payBtn = nullptr;
    PVZ2UIButton* m_closeBtn = nullptr;
    MagentoProductPropsPtr m_product;
};

#endif /* LostNetActivityUI_H */
