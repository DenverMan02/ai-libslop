//
//  NewerPresentUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-10-23.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NewerPresentUI__
#define __PlantsVersusZombies2__NewerPresentUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "gameNetWork/NetworkData.h"

enum NewerPresentButtons
{
	NEWER_PRESENT_CLOSE = 0,
    NEWER_PRESENT_BUY,
    NEWER_PRESENT_FIRSTCHARGE,
};

enum NewerPresentType
{
    NewerPresent_Advance = -2,
    NewerPresent_Base    = -1,
    NewerPresent_FristReCharge = 1,
};

class NewerPresentUI : public Sexy::Widget, public ButtonListener
{
public:
	
	NewerPresentUI(int iType);
	virtual ~NewerPresentUI();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    
	virtual void Draw(Graphics* i_g);
    virtual void DrawOverlay(Graphics* i_g);
	virtual void ButtonDepress(int i_id);

    
private:
    void DrawPlantImage(Graphics* i_g);
    void DrawGiftEffect(Graphics* i_g);
    void DrawDialogBottomBackground(Graphics* i_g);
    void drawShadedBox(Graphics* i_g, Rect extents);
    void DrawRibbon(Graphics* i_g);
    void onPaySucess();
    void DrawNewPresentInfoBg(Graphics* i_g);
    void onGemCurrencyAdd(int i_delta);
    
    void GotRebateData(S2C_ChristmasRebate* pData);
    
    void DrawRebatePresent(Graphics* i_g);
    
    void RebateAndroidRequestProcess(int iPlantId);
    
    std::string GetCountImagePath(int count);
    
    ImagePtr GetPlantPieceImage(int type);
    
    Sexy::Rect      m_rectDialog;
    
    SexyString		m_giftTitle;
    SexyString		m_giftDesc;
    
    int   m_iType;
    ImagePtr m_plantImage;
    std::string m_strPlantName;
};

#endif /* defined(__PlantsVersusZombies2__NewerPresentUI__) */
