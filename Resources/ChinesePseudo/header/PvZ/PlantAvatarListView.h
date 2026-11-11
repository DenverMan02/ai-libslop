//
//  PlantAvatarListView.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-9-3.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAvatarListView_h
#define PlantsVersusZombies2_PlantAvatarListView_h

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
#include "Effect_PopAnim.h"
#include "PlantNewAvatar.h"

namespace Message
{
    void RefreshAvatarCardData();
    void NotifyExchangeFinish();
    void NotifyPackageViewClose();
}

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantAvatarContent : public Widget
{
public:
    
	PlantAvatarContent(MagentoProductPropsPtr i_props, int i_id, ButtonListener* theButtonListener);
	virtual ~PlantAvatarContent();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    
    void SetSelected(bool i_selected);
    const bool GetCurrentSelectedFlag() { return m_bSelected; }
    const MagentoProductPropsPtr & GetCurrentPlantProps() { return m_props; }
    
private:
    
    void RefreshCurrentData();
    
    MagentoProductPropsPtr m_props;
    PVZ2UIButton * m_pButton;
    
    Rect        m_rectBG;
    
    float       m_progress;
    bool        m_bSelected;
    bool        m_bUnLock;
    bool        m_bCanUnlock;
    bool        m_bFirstNoBar;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantAvatarScrollListUI : public Widget, Sexy::ButtonListener
{
public:
	PlantAvatarScrollListUI(Rect &i_rect);
    virtual ~PlantAvatarScrollListUI();
    
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    
    const MagentoProductPropsPtr & GetCurrentPlantProps() { return m_contents[m_nLastSelect]->GetCurrentPlantProps(); }
    void CurrentPlantChange(bool & bChange);
    
private:
    
    void	InitView(int i_rareFiler = 0);
    
    void	SelectPlant(int i_id);
    
    int     m_nLastSelect;
    bool    m_bChange;
    bool    m_bFirstInit;
    
    std::vector<class PlantAvatarContent*> m_contents;
    int 	m_tutorialSelectId;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantAvatarSwitchButton : public Sexy::Widget
{
public:
    PlantAvatarSwitchButton();
    virtual ~PlantAvatarSwitchButton();

    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );
    virtual void Draw(Sexy::Graphics* i_g);

    void setData(int i_avatarID, bool i_isUnlock);
    void OnSelectTinyIcon();
private:
    Sexy::Image* m_image;
    int m_avatarID;
    bool m_isUnlock;
    Sexy::TouchID m_touch;
    bool m_isSelect;
};

class PlantAvatarSwitchButtonScrollWidget : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
    RT_CLASS_DEFINE(PlantAvatarSwitchButtonScrollWidget, Sexy::Widget, RtClass);
public:    

    PlantAvatarSwitchButtonScrollWidget();
    virtual ~PlantAvatarSwitchButtonScrollWidget();

	virtual void	Draw(Sexy::Graphics* i_g);

    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    void resortButtons();

    void SetData(MagentoProductPropsPtr i_props);

private:

    void initDialog();

    Sexy::Widget *m_content;
    MagentoProductPropsPtr m_props;

};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantAvatarListView : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    
	PlantAvatarListView();
	virtual ~PlantAvatarListView();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void 	DrawOverlay(Sexy::Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    void refreshPlantAvatar(int avtarIndex);

    void PatchRefresh();
    
    void TriggerTutorial();

    void OnNotifyPackageViewClose();

private:
    
    void InitView();
    void RefreshCurrentData();
    
    void UpdateAccessoryButton(PlantTypePtr i_plantType);
    void OnNoticeAccessoryUIClose();

    Image* GetAccessoryQuality(AccessoryQuality i_quality);

    enum EButtonType
    {
        eButtonType_Close = 0,
        eButtonType_Info,
        eButtonType_Exchange,
        eButtonType_AvatarUnlockOne,
        eButtonType_AvatarUnlockTwo,
        eButtonType_Accessory,
        eButtonType_Count,
    };
    
    MagentoProductPropsPtr m_props;
    
    PVZ2UIScrollingWidget *     m_pScrollingWidget;
    PlantAvatarScrollListUI *   m_pPlantListUI;
    PlantAvatarSwitchButtonScrollWidget *  m_pPlantAvatarSwitchWidget;
    
    PVZ2UIButton *  m_pButtonClose;
    PVZ2UIButton *  m_pButtonInfo;
    PVZ2UIButton *  m_pButtonExchange;
    PVZ2UIButton *  m_pButtonUnlock[2];
    
    // For accessory entry
    PVZ2UIButton *  m_pButtonAccessory;

    PopAnimRig   *  m_pAnimRig;
    
    LevelUpPriceData m_strData;
    
    Sexy::Rect  m_rectDialog;
    Sexy::Rect  m_rectScoll;
    
    SexyString  m_sLabel;
    SexyString  m_sButtonContent;
    SexyString  m_sAvatarShortDes;
    
    class PlantDisplayBoard* m_plantDisplay;
    
    float       m_fProgress;
    
    bool        m_bUnLock;
    bool        m_tutorial;
    
    bool        m_bShowNotice;
    SexyString 	m_boostDescription;
    Image*		m_qualityBgImage;
    Image*		m_acclevelImage;
    Effect_PopAnim* m_buttonAnim;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantAvatarInfoDialog : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
	PlantAvatarInfoDialog(MagentoProductPropsPtr i_props, bool bShowNotice);
	virtual ~PlantAvatarInfoDialog();
	
	//virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    //virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void InitDialog();
    void PlantLevelUp();
    void CloseChildDialog();
    const std::string & GetCurrentPlantPieceLevel(const std::string & sPlantName);
    const std::string & GetCurrentPlantPieceLevelTextContent(const std::string & sPlantName);
    
    bool CheckPlantIsInActivityLevel(FestivalGameMode & eGameMode);
    
    enum EPlantAvatarInfoButtonType
    {
        ePlantAvatarInfoButtonType_Close = 0,
        ePlantAvatarInfoButtonType_Return,
        ePlantAvatarInfoButtonType_Gacha,
        ePlantAvatarInfoButtonType_ActivityLevel,
        ePlantAvatarInfoButtonType_Count,
    };
    
    MagentoProductPropsPtr m_ptrProps;
    
    PVZ2UIButton *  m_pButtonBack;
    PVZ2UIButton *  m_pButtonClose;
    PVZ2UIButton *  m_pButtonGoToActivityLevel;
    PVZ2UIButton *  m_pButtonGoToGacha;
    
    SexyString      m_sAcivityContent;
    
    Sexy::Rect      m_rectDialog;
    
    bool            m_bShowComeFromActivity;
    bool            m_bShowNotice;
    
    bool            m_bSpecialWay;
    SexyString      m_sSpecialWayContent;
    
    FestivalGameMode    m_eGameMode;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
class PlantAvatarPackageItem : public Sexy::Widget
{
public:
    PlantAvatarPackageItem();
    virtual ~PlantAvatarPackageItem();

    virtual void Draw(Sexy::Graphics* i_g);

    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );

    void setOldInfo(MagentoProductPropsPtr i_props);
    void setNewInfo(PlantNewAvatarPtr i_info);

    void selectAvatar();
    void UpdateState();

    void EquipAvatar();
    void UnEquipAvatar();
    void ExchangeAvatar();

    void OnNotifityRequsetExchangeNewAvatar(bool i_success, int i_newAvatarId);
    void OnSelectItem();
private:
    void InitDialog();

    Sexy::TouchID m_touch;
    Sexy::Image* m_image;

    MagentoProductPropsPtr m_oldInfo;
    PlantNewAvatarPtr m_newInfo;

    float m_progress;
    SexyString m_strPiece;
    SexyString m_strName;

public:
    bool m_isOld;
    bool m_isUnLock;
    bool m_isEquip;
    bool m_isFullPiece;

    SexyString m_strBuffer;
    SexyString m_strGetSource;
    bool m_isSelect;
};

class PlantAvatarPackageView : public Sexy::Widget, Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    PlantAvatarPackageView(MagentoProductPropsPtr i_props);
    virtual ~PlantAvatarPackageView();

    virtual void	Draw(Sexy::Graphics* i_g);
	virtual void	ButtonDepress(int i_id);

    void onSelectAvatar(PlantAvatarPackageItem* i_item);

    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    void OnNarrationSystemFinish();
    void ShowGachaIntro2Mask();

private:
    void InitDialog();

    void SetButtonState(int i);
    void OnNotifyExchangeFinish();

    MagentoProductPropsPtr m_ptrProps;

    PVZ2UIButton *  m_pButtonFunction;
    PVZ2UIButton *  m_pButtonCancel;
    PVZ2UIButton *  m_pButtonClose;

    PlantAvatarPackageItem* m_selectItem;
    int m_buttonState;

    SexyString m_strBuffer;
    SexyString m_strGetSource;

    std::vector<PlantNewAvatarPtr> m_newAvatarList;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

#endif
