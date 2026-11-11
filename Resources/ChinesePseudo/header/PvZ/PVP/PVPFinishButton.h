//
//  PVPFinishButton.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/4/8.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PVPFinishButton_h
#define PVPFinishButton_h

#include "PVZ2UIButton.h"
#include "MagentoService.h"
#include "UIMessageBox.h"

class PVPFinishButton : public PVZ2UIButton
{
public:
    typedef Sexy::Delegate1<int> CallbackEvent;
public:
    void ShowBuyConfirm(CallbackEvent callback);
    void SetPrice(int gem);
    PVPFinishButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
    ~PVPFinishButton();
protected:
    void Draw(Graphics* i_g) override;
private:
    int GemToYuan(int gem);
    void PrivateDraw(Graphics* i_g);
    void ConfirmBuy(UIMessageBox* box, int buttonID);
    void onItemPurchasedFromStore(MagentoProductProps* i_props);
    MagentoProductPropsPtr GetProps(int price);
private:
    int m_gem;
    CallbackEvent	 m_callback;
    MagentoProductPropsPtr m_props;
};

#endif /* PVPFinishButton_h */
