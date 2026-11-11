//
//  BuyItemUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BuyItemUI__
#define __PlantsVersusZombies2__BuyItemUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

class BuyItemUI : public Sexy::Widget, public ButtonListener
{
public:
	enum BuyType
	{
		BuyMower,
		BuyPresent,
		AdsMower,
		NormalAdsMower
	};

public:
	BuyItemUI(BuyType i_type);
    virtual ~BuyItemUI();

	virtual void Update();
    virtual void Draw(Graphics* i_g);
    virtual void ButtonDepress(int i_id);

	void OnPaySuccess();
	void OnPurchaseDialogClosed();
    void OnBuySuccess_IOS(const bool& i_success);

	static std::string GetSkuByType(BuyType i_type);
    static int          GetGemsCostByType(BuyType i_type);
    
private:
	void InitUI();
	void InitByType();
	void DrawByType(Graphics* i_g);
	void onNotifyADWatchFinish(int i_type);

private:
	BuyType			m_type;
	Sexy::Rect		m_rectDialog;
	SexyString		m_strDesc;
	SexyString		m_adStrLeftTimes;
	Sexy::Image*	m_imgTitle;
	SexyString		m_strTitle;
	RtWeakPtr<class PopAnimRig>		m_mowerAni;
	bool					m_bPaySuccess;
};

#endif /* defined(__PlantsVersusZombies2__BuyItemUI__) */
