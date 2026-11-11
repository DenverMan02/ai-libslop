//
//  PVpCoinStore.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15/12/21.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef PVpCoinStore_h
#define PVpCoinStore_h

#include "Widget.h"
#include "MagentoService.h"
#include "PVZ2UIButton.h"

class PvpCoinStore : public Sexy::Widget, public ButtonListener
{
public:
    PvpCoinStore();
    ~PvpCoinStore();
    void Draw(Graphics* i_g) override;
    void ButtonDepress(int i_id) override;
private:
    void createPurchasePanel(MagentoCategoryPropsPtr i_categoryProps);
private:
    int m_dialogWidth;
    int m_dialogHeight;
    SexyString m_title;
    PVZ2UIButton*             m_closeButton;
    PVZ2UIScrollingWidget*    m_scrollingWidget;
    MagentoCategoryPropsPtr    m_storeProps;

};

#endif /* PVpCoinStore_hpp */
