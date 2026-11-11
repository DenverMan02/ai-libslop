//
//  StorePlantGiftView.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-7-30.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StorePlantGiftView_h
#define PlantsVersusZombies2_StorePlantGiftView_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "MagentoService.h"
#include "PVZ2UIPlantCard.h"
#include "SettingsDialog.h"
#include "FestivalManager.h"
#include "PlantType.h"
#include "PVZ2UIPlantCard.h"
#include "PlantLevelUpListView.h"

//------------------------------------------------------------------------------------------

namespace Message
{
    void RefreshOtherLevelButtons(int iSelectedButtonId);
    void RefreshStorePlantGift();
}

enum LevelButtonType
{
	LEVEL_BTN_LEVEL_ONE,
	LEVEL_BTN_LEVEL_TWO,
    LEVEL_BTN_LEVEL_THREE,
    LEVEL_BTN_LEVEL_FOUR,
	LEVEL_BTN_AVATAR,
	LEVEL_BTN_COUNT
};

//------------------------------------------------------------------------------------------
//---------------------------      Class SkillButtonUI     ---------------------------------
//------------------------------------------------------------------------------------------

class SkillButtonUI : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
    SkillButtonUI(bool isAvatar, const SkillPropertySheetPtr & skillSheet, int iLevel);
    ~SkillButtonUI();
    
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    void SetCurrentPlantName(const std::string & sName) { m_sPlantName = sName; }
    
private:
    
    enum ESkillButtonType
    {
        eSkillButtonType_Tips = 0,
        eSkillButtonType_Count,
    };
    
    void InitView();
    
    PVZ2UIButton * m_pButtonCallTips;
    Image * m_pImage;
    
    SkillPropertySheetPtr m_ptrPropertySheet;
    
    std::string m_sPlantName;
    
    int  m_iLevel;
    bool m_bAvatar;
};

//------------------------------------------------------------------------------------------
//---------------------------      Class SkillButtonUI     ---------------------------------
//------------------------------------------------------------------------------------------

class LevelButtonUI : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
    LevelButtonUI(bool isAvatar, const std::string & sPlantName, int iLevel);
    ~LevelButtonUI();
    
    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void	ButtonDepress(int i_id);
    
    void ClickIt();
    bool GetButtonSelected() { return m_bSelected; }
    void SetButtonUnselected() { m_bSelected = false; }
    bool IsButtonAvatar() { return m_bAvatar; }
    bool isButtonHas() { return m_bHas; }
    void SetButtonHas() { m_bHas = true; }
    
private:
    
    enum ESkillButtonType
    {
        eSkillButtonType_Selected = 0,
        eSkillButtonType_Count,
    };
    
    void InitView();
    
    std::string m_sPlantName;
    
    PVZ2UIButton * m_pButtonSelected;
    Image * m_pNoticedImage;
    
    int  m_iLevel;
    bool m_bAvatar;
    bool m_bSelected;
    bool m_bHas;
};

//------------------------------------------------------------------------------------------

#endif
