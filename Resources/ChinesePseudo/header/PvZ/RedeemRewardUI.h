//
//  CodeRewardUI.h
//  PlantsVersusZombies2
//
//  Created by Tiger on 16/11/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RedeemRewardUI_h
#define RedeemRewardUI_h

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "RechargeRewardConfig.h"
#include "NetworkData.h"
#include "UISingletonDialog.h"


class RedeemRewardUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	RedeemRewardUI(const std::string& payTime, const std::string& payCode, const std::string& orderNumber);
    virtual ~RedeemRewardUI();
    
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    
    void updateRewardList(const std::string& payTime, const std::string& payCode, const std::string& orderNumber);
    void showRewardList();
    int  calStartX(int rowCount);

protected:
    void OnRedeemPlantTrialSuccess();
    int GetNeedTotalPiece(const std::string &strPlantName, int iDesLevel);

private:
    enum buttonID
    {
    	btn_get = 1,
    };

    struct KeyInfo
    {
    	std::string key;
    	int quantity;
    };

    SexyString m_contentTitle;
    std::map<int, int> m_redeemList;
    std::vector<KeyInfo> m_keyList;
    Rect m_dialogRect;

    int m_startX;
    int m_startY;
    int m_firstRowCount;

    std::string m_payTime;
    std::string m_payCode;
    std::string m_orderNumber;

    class PurchaseItemWidget* m_purchasedItemUI;
    ImagePtr m_worldPackImage;

};

#endif /* RedeemRewardUI_h */
