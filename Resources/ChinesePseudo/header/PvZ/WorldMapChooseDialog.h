//
//  ActivityLevelDialog.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-8-28.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMapChooseDialog_h
#define PlantsVersusZombies2_WorldMapChooseDialog_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"

//---------------------------------------------------------------------------------
#define BUTTON_NUM (6)

enum PlantLevelUpTutorialState
{
	// These must be in the ORDER THAT THEY APPEAR. Do not place an end-game tutorial
	// in the beginning of this list...
	PLANT_TUTORIAL_NONE,
	PLANT_TUTORIAL_STAR_1,
	PLANT_TUTORIAL_LEVELUP_1,
	PLANT_TUTORIAL_STORE_1,
    GACHA_TUTORIAL_1,
    DANGERROOM_TUTORIAL_1,
    PLANTBOX_INTRO_2,
    PLANTGJ_INTRO_2,
};

enum EDIALOG_TYPE
{
    eDialog_Type_ActivityLevel = 0,
    eDialog_Type_Plant,
    eDialog_Type_Welfare,
    EDialog_Type_Count,
    eDialog_Type_Treasure,
    eDialog_Type_Riddles
};

namespace Message
{
    void CheckMapChooseDialog();
    void CheckValidChooseDialog();
    void PopAllButtonsState();
    void KillChooseDialog(UIWidget * pDialog);
}

//---------------------------------------------------------------------------------

class RiddlesLaternTip : public Widget
{
    void Draw(Sexy::Graphics* i_g) override;
};

class RiddlesRedPackTip : public Widget
{
    void Draw(Sexy::Graphics* i_g) override;
};

//---------------------------------------------------------------------------------

class WorldMapChooseDialog : public Widget, Sexy::ButtonListener
{
public:
    
    WorldMapChooseDialog(EDIALOG_TYPE eType);
    ~WorldMapChooseDialog();
    
    virtual void 	Update();
    virtual void    ButtonPress(int i_id);
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    virtual void 	DrawOverlay(Graphics* i_g);
    
    EDIALOG_TYPE    GetDialogType() { return m_eType; }
    void    OnOK();
    Point GetButtonPosition(int i_type);
    PVZ2UIButton* GetButton(int i_type) { return m_pButton[i_type]; }
    
private:
    
    enum EBUTTON_TYPE
    {
        //eDialog_Type_ActivityLevel
        eButton_Type_Yati = 0,
        eButton_Type_Gargantuar,
        eButton_Type_Devil,
        eButton_Type_WealthGod,
        
        //eDialog_Type_Plant
        eButton_Type_StarChallenge,
        eButton_Type_PlantLevelUp,
        eButton_Type_PlantAvatar,
        eButton_Type_TransGenosis,
        eButton_Type_PlantFamily,
        eButton_Type_Artifact,
        eButton_Type_Gene,
        
        //eDialog_Type_Welfare
        eButton_Type_Lottery,
        eButton_Type_Gifts,
        eButton_Type_NewerGifts,
        
        eButton_Type_Treasure,
        eButton_Type_GoldCan,
        eButton_Type_MiniGame,
        eButton_Type_Pedant,
        
        eButton_Type_Lantern,
        eButton_Type_RedPack,
        
        eButton_Type_Count,
    };
    
    void InitView();
    void KillMyChildren();
    
    PVZ2UIButton* CreateButton(int bId, Image* img, bool notice, bool isScale = false);
    
    bool ShowTheNoticeAboutPlantLevelUp();
    bool ShowTheNoticeAboutAvatar();
    bool ShowTheNoticeAbourTG();
    
    bool ShouldDrawTGIcon();
    
    void onStarTutorialFinished();
    void onLevelUpTutorialFinished();
    void onStoreTutorialFinished();
    void onDangerroomTutorialFinished();
    
    void onCloseDialog();
    
    void AddLaternTips();
    
    void AddRedPackTips();

    PVZ2UIButton *  m_pButton[BUTTON_NUM];
    
    EDIALOG_TYPE    m_eType;
    int             m_iBgWidth;
    int             m_iBgHeight;
    PlantLevelUpTutorialState    m_tutorialState;
	class BouncingArrow*		 m_tutorialArrow;
    SexyString                   m_leftActivityDays;
    bool                         m_isDangerRoom;
    bool                         m_plantBonus;
    bool                         m_avatarBonus;
    bool                         m_showEnableFamilyNotice;
};

//---------------------------------------------------------------------------------

#endif
