//
//  CardPlayUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-10-28.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__CardPlayUI__
#define __PlantsVersusZombies2__CardPlayUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "PVZ2UIButton.h"
#include "Effect_PopAnim.h"
#include "DangerRoomStatScreen.h"
#include "GameFeatureType.h"

struct CardDropData
{
	std::string bonus_name;
	uint16		appear_weight;
    uint16		select_weight;
    
	CardDropData()
	{
        appear_weight = 0;
        select_weight = 0;
	}
};

class CardItemDisplayer : public PVZ2UIButton
{
public:
    
	CardItemDisplayer(int i_buttonId, ButtonListener* i_listener);
	virtual ~CardItemDisplayer();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
    void setSelected(bool i_isSelected)
    {
        m_bIsSelected = i_isSelected;
    }
    
    void setOpen(bool i_isOpen)
    {
        m_bIsOpen = i_isOpen;
    }
    
    void SetBonus(const std::string& i_bonus_name);
    
    BonusTypePtr GetBonus() const
	{
		return m_bonus;
	}
    
    Image* GetContentImage() const
	{
		return m_contentImage;
	}
    
private:
    Image* m_contentImage;
    
    BonusTypePtr m_bonus;
    
    bool   m_bIsSelected;
    bool   m_bIsOpen;
};

///////////////////////////////////

enum CardPlayButtons
{
	CARD_PLAY_CLOSE = 100,
    
    CARD_BUY_START  = 200,

    CARD_BUY_BY_MONEY = 300
};

enum CardPlayState
{
	CARDSTATE_INITIAL = 0,
    
    CARDSTATE_WAITING_FOR_SELECT,
    CARDSTATE_SELECT_OPENING,
    
    CARDSTATE_WAITING_OTHERS_OPENING,
    CARDSTATE_OTHERS_OPENING,
    
    CARDSTATE_ALL_OPENED
};

class CardPlayUI : public Sexy::Widget, public ButtonListener
{
public:
	
	CardPlayUI();
	virtual ~CardPlayUI();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    
	virtual void Draw(Graphics* i_g);
    virtual void DrawOverlay(Graphics* i_g);
	virtual void ButtonDepress(int i_id);
    
private:
    
    void CreateFannedOutCards(float theX, float theY,int i_card_id);
    
    void FlipCards(int i_card_id);
    
    void GenerateAllDrops();
    
    std::string GenerateFirstDrops();
    
    void GenerateOtherDrops();
    
    bool CanGetPiece(const std::string& i_plant_name);
    
    void exchangeWidget(Widget * first,Widget * second);
    
    void drawShadedBox(Graphics* i_g, Rect extents);
    
    void onPaySucess();
    
    void onPopRewardPressed();
    
    void popRewardDialog(BonusTypePtr bonus, bool bDoNotAddReward = false);
    
    void onUseGemFinish(const bool& isSuccess);
    int buttonId;
    
    std::vector<CardItemDisplayer*> m_offerings;
    std::vector<PVZ2UIButton*>      m_buttons;
    
    std::vector<CardDropData>       m_arrAllDrops;
    std::vector<CardDropData>       m_arrCardDrops;
    
    int             m_nSelectIndex;
    int				m_nPurchaseButtonIndex;
    
    Sexy::Rect      m_rectDialog;
    
    SexyString		m_cardTitle;
    SexyString		m_cardDesc;
    
    CardPlayState   m_eState;
    
    //pvztime_t 		m_time_Opening;
    
    /////////
    /*
    Effect_PopAnim* m_popAnimEffect;
    
    class PopAnimRigRectDrawer* m_rigRectDrawer;
	class PopAnimRig*           m_rig;
    */
    /////////
    
    std::vector<FanCardData>        m_fanCards;
    pvztime_t                       m_tutorialMarkerLastHit;
    pvztime_t                       m_tutorialPauseDuration;
    
    PVZ2UIButton *                  button_close;
};

#endif /* defined(__PlantsVersusZombies2__CardPlayUI__) */
