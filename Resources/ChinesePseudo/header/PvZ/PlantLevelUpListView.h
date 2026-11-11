//
//  PlantLevelUpListView.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-5-19.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantLevelUpListView_h
#define PlantsVersusZombies2_PlantLevelUpListView_h

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
#include "NetworkData.h"
#include "GameCommon.h"

namespace Message
{
    void RefreshCurrentList();
    void TutorialFinish();
    void LevelUpTutorialFinishFirstStep();
    void RefreshCardData();
    void RefreshSkillButtonRender();
    void ChangeRareFilterState(int i_rare, bool i_flag);
    void ScrollReInitView(int i_rare);
}

extern bool canPlantLevelUp(const MagentoProductPropsPtr & ptr, bool checkCoin, bool checkGeneralChips);

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantContent : public Widget
{
public:
    
	PlantContent(MagentoProductPropsPtr i_props, int i_id, ButtonListener* theButtonListener);
	virtual ~PlantContent();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    //virtual void ButtonDepress(int i_id);
    
    void SetSelected(bool i_selected);
    const bool GetCurrentSelectedFlag() { return m_bSelected; }
    const MagentoProductPropsPtr & GetCurrentPlantProps() { return m_props; }
    
public:
    
    PVZ2UIButton * m_pButton;
    
private:
    
    void RefreshCurrentData();
    void onChangePlantSuccess(const std::string& i_plantName);
    
    MagentoProductPropsPtr m_props;
    
    Rect        m_rectBG;
    
    float       m_progress;
    bool        m_bSelected;
    bool        m_bUnLock;
    bool        m_bLevelUp;
    bool        m_bCenUnlock;
    bool        m_bFirstNoBar;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantScrollListUI : public Widget, Sexy::ButtonListener
{
public:
	PlantScrollListUI(Rect &i_rect);
    virtual ~PlantScrollListUI();
    
    virtual void	ButtonDepress(int i_id);
    virtual void	Draw(Sexy::Graphics* i_g);
    
    const MagentoProductPropsPtr & GetCurrentPlantProps() { return m_contents[m_nLastSelect]->GetCurrentPlantProps(); }
    void CurrentPlantChange(bool & bChange);
    PVZ2UIButton* GetFirstPlantContentByName();
    
private:
    
    void	InitView(int i_rareFiler = 0);
    bool    CheckPlantLevelUpActived(const MagentoProductPropsPtr & ptr);
    
    void	SelectPlant(int i_id);
    
    int     m_nLastSelect;
    bool    m_bChange;
    bool    m_bFirstInit;
    
    std::vector<class PlantContent*> m_contents;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

enum ESkillTipsType
{
    eSkillTipsType_LowSkill = 0,
    eSkillTipsType_LowForpertySkill,
    eSkillTipsType_HighSkill,
    eSkillTipsType_HighForpertySkill,
    eSkillTipsType_Count
};

class PlantSkillButtonUI : public Widget, Sexy::ButtonListener
{
public:
    
    PlantSkillButtonUI(SkillPropertySheetPtr & skillSheet, int nLevel, ESkillTipsType eType, int nCurrentLevel = 1);
    virtual ~PlantSkillButtonUI();
    
    virtual void	Update() override;
    virtual void    ButtonPress(int i_id) override;
    virtual void	ButtonDepress(int i_id) override;
    virtual void	ButtonMouseLeave(int i_id) override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    
    void SetContent(SkillPropertySheetPtr & skillSheet)
    {
        m_bRefresh = true;
        m_pSkillSheet = skillSheet;
    }
    
private:
    
    enum ESkillButtonType
    {
        eSkillButtonType_Tips = 0,
        eSkillButtonType_Count,
    };
    
    void    InitView();
    
    PVZ2UIButton * m_pButtonCallTips;
    SkillPropertySheetPtr m_pSkillSheet;
    Image * m_pIcon;
    
    int  m_nLevel;
    int  m_nCurrentLevel;
    bool m_bRefresh;
    
    ESkillTipsType m_eType;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

enum 
{
    FILTER_SWITCH_WHITE = 1<<1,
    FILTER_SWITCH_GREEN = 1<<2,
    FILTER_SWITCH_BLUE = 1<<3,
    FILTER_SWITCH_PURPLE = 1<<4,
    FILTER_SWITCH_ORANGE = 1<<5,
    FILTER_SWITCH_ALL = 0xffff,
};

class RareFilterButton : public Sexy::Widget
{
public:
    RareFilterButton(int i_rare);
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
private:
    int32 m_iTouch;
    Sexy::Image* m_upImage;
    Sexy::Image* m_downImage;
    bool m_buttonState;
    int m_rare;
};

class RareFilterPanel : public Sexy::Widget
{
public:
    RareFilterPanel();
    ~RareFilterPanel();
    virtual void Draw(Sexy::Graphics* i_g);
    void initView();
    void onRareFilterButtonStateChange(int i_rare, bool i_changed);
private:
    int m_filterExcept;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantLevelUpListView : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    
    PlantLevelUpListView(std::string strPlantName = "", bool bPlantTrial = false);
	virtual ~PlantLevelUpListView();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void TutorialFinish();
    void TutorialLevelUpFinishFirstStep();

    void HideDisplayItems(bool bImmediately = false);
    void EnableAutoNext();
    void DisableAutoNext();
    void DisplayPlantLevel(int i_level);

    bool AutoTestSelected(int Id);
    void AutoTestPlantLevelUp();
    void AutoTestUnlockPlant();
    const MagentoProductPropsPtr& GetCurrentPlantProp();
    void SetCurrentPlantProp(const MagentoProductPropsPtr& i_props);
    void onQueuedNarrationFinished();
private:
    
    void InitView();
    void InitSkillUI(bool bRefresh = false);
    void RefreshCurrentData();
    void LevelUpCancel();
    void LevelUpOk();
    void onPlantLevelUpSuccess();
	void RefreshSkillButtonRender();
    
    enum EButtonType
    {
        eButtonType_Close = 0,
        eButtonType_Info,
        eButtonType_LevelUp,
        eButtonType_SwitchToNew,
        eButtonType_Count,
        
        eButtonType_CoverOne,
        eButtonType_CoverTwo
    };
    
    MagentoProductPropsPtr m_props;
    
    PlantSkillButtonUI * m_pLowLevelSkill;
    PlantSkillButtonUI * m_pLowLevelPorpertySkill;
    PlantSkillButtonUI * m_pHighLevelSkill;
    PlantSkillButtonUI * m_pUniqueLevelSkill;
    PlantSkillButtonUI * m_pFiveLevelSkill;
    
    PVZ2UIScrollingWidget * m_pScrollingWidget;
    PlantScrollListUI *     m_pPlantListUI;
    
    PVZ2UIButton *  m_pButtonClose;
    PVZ2UIButton *  m_pButtonInfo;
    PVZ2UIButton *  m_pButtonLevelUp;
    PVZ2UIButton *  m_pButtonSwitchToNew;
    
    PVZ2UIButton *  m_pWidgetCoverOne;
    PVZ2UIButton *  m_pWidgetCoverTwo;
    
    PopAnimRig   *  m_pAnimRig;
    
    LevelUpPriceData m_strData;
    
    Sexy::Rect  m_rectDialog;
    Sexy::Rect  m_rectScoll;
    
    SexyString  m_sLabel;
    SexyString  m_sButtonContent;
    
    class PlantDisplayBoard* m_plantDisplay;
    
    float       m_fProgress;
    int         m_iPlantLevel;
    int         m_iPlantMaxLevel;
    int         m_iPlantMinLevel;
    
    bool        m_bLevelUp;
    class BouncingArrow*    m_tutorialArrow;
    bool        m_bFinishFirstStep;
    bool        m_bShowNotice;
    bool        m_bCannotLevelUp;
    bool        m_bPlantTrialShow;
    bool        m_hideDisplayItems;
    bool        m_enableAutoNext;
    std::string        m_strPlantName;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

enum EPlantSkillTipsType
{
    ePlantSkillTipsType_ArrowTop = 0,
    ePlantSkillTipsType_ArrowRight,
    ePlantSkillTipsType_ArrowLeft,
    ePlantSkillTipsType_ArrowBottom,
    ePlantSkillTipsType_Count
};

class PlantSkillTipsUI : public Sexy::Widget
{
public:
    
    PlantSkillTipsUI(SexyString & sTips, int iPostionX, int iPostionY, EPlantSkillTipsType eType = ePlantSkillTipsType_ArrowTop);
    virtual ~PlantSkillTipsUI(){}
    
    virtual void Draw(Sexy::Graphics* i_g);
    
	void SetImage(Sexy::Image* pBG, Sexy::Image* pArrow);
	void SetArrowOffset(const SexyVector2& offset) { m_arrowOffset = offset; }
    void SetTips(const SexyString& strTips, float fScaleHeight, const Color& tipClr);
private:
    
    SexyString m_sTips;
    float      m_fScaleHeight;
    
    EPlantSkillTipsType m_eType;

	Sexy::Image*		m_pImageBG;
	Sexy::Image*		m_pImageArrow;
	SexyVector2		m_arrowOffset;
    Color           m_tipsColor;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantLevelUpInfoDialog : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
	PlantLevelUpInfoDialog(MagentoProductPropsPtr i_props, bool bShowNotice, bool ShowSpecialPiece, int SpecialPieceId);
	virtual ~PlantLevelUpInfoDialog();
	
	//virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    //virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
private:
    
    void InitDialog();
    void PlantLevelUp();
    void CloseChildDialog();
    void onGetGachaInfo(S2C_GachaInfo* info);
    
    const std::string & GetCurrentPlantPieceLevel(const std::string & sPlantName);
    const std::string & GetCurrentPlantPieceLevelTextContent(const std::string & sPlantName);
    
    bool CheckPlantIsInActivityLevel(FestivalGameMode & eGameMode);
    
    enum EPlantLevelUpInfoButtonType
    {
        ePlantLevelUpInfoButtonType_Close = 0,
        ePlantLevelUpInfoButtonType_Store,
        ePlantLevelUpInfoButtonType_Return,
        ePlantLevelUpInfoButtonType_WorldLevel,
        ePlantLevelUpInfoButtonType_ActivityLevel,
        ePlantLevelUpInfoButtonType_GoldCan,
        ePlantLevelUpInfoButtonType_Count,
    };
    
    MagentoProductPropsPtr m_ptrProps;
    
    PVZ2UIButton *  m_pButtonBack;
    PVZ2UIButton *  m_pButtonClose;
    PVZ2UIButton *  m_pButtonGoToStore;
    PVZ2UIButton *  m_pButtonGoToWorld;
    PVZ2UIButton *  m_pButtonGoToActivityLevel;
    
    std::string     m_sLevelName;
    std::string     m_sLevelContent;
    SexyString      m_sAcivityContent;
    
    Sexy::Rect      m_rectDialog;
    
    bool            m_bShowComeFrom;
    bool            m_bShowComeFromActivity;
    bool            m_bShowNotice;
    
    bool            m_bSpecialWay;
    SexyString      m_sSpecialWayContent;
    
    bool            m_bShowSpecialPiece;
    int             m_sSpecialPieceId;
    GAME_ITEM_INFO  m_sSpecialPieceItem;
    
    FestivalGameMode    m_eGameMode;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

class PlantLevelUpCheckDialog : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
	PlantLevelUpCheckDialog(MagentoProductPropsPtr i_props);
	virtual ~PlantLevelUpCheckDialog();
	
	//virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    //virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
    
    virtual void	MouseDown(const int i_mouseX, const int i_mouseY, const int i_clickCount);
    
private:
    
    void InitDialog();
    void LevelUpCancel();
    void LevelUpOk();
    void LevelUpOkBook();
    void LevelUpWithGeneralChips(int i_general, int i_universal);
    bool InitDataInfo();
    void RefreshData();
    
    bool checkCanLevelup();
    bool checkCanLevelupByBook();
    bool checkCanLevelupWithGeneralChips();
    void updateLevelupBook();
    void onLevelupBook(bool success);
    
    void onCoinStoreClose();

    enum EPlantLevelUpCheckButtonType
    {
        ePlantLevelUpCheckButtonType_Close = 0,
        ePlantLevelUpCheckButtonType_LevelUp,
        ePlantLevelUpCheckButtonType_AddCoin,
        ePlantLevelUpCheckButtonType_Count,
        ePlantLevelUpCheckButtonType_LevelUpByBook,
        ePlantLevelUpCheckButtonType_LevelUpWithGeneralChips,
    };
    
    LevelUpPriceData m_strData;
    
    MagentoProductPropsPtr m_ptrProps;
    SkillPropertySheetPtr  m_ptrSkillProperty;
    SkillPropertySheetPtr  m_ptrSkillAdvanced;
    
    PVZ2UIGameObjectCard *  m_pPlantCard;
    PVZ2UIButton *          m_pButtonClose;
    PVZ2UIButton *          m_pButtonLevelup;
    PVZ2UIButton *          m_pButtonLevelupByBook;
    PVZ2UIButton *          m_pButtonLevelupWithGeneralChips;
    PVZ2UIButton *          m_pButtonAddCoin;
    
    Image * m_pSkillPropertyIcon;
    Image * m_pSkillAdvancedIcon;
    
    Sexy::Rect      m_rectDialog;
    Sexy::Rect      m_plantPieceImgRect;
    Sexy::Rect      m_specialPieceImgRect;
    
    int             m_iDiglogWidth;
    int             m_iCurrentLevel;
    int             m_iPlantPieceCount;
    int             m_iSpecialPieceId;
    GAME_ITEM_INFO  m_sSpecialPieceItem;
    int             m_iSpecialPieceCount;
    int             m_iCoinCount;
    
    int             m_iOwnPlantPieceCount = 0;
    int             m_iOwnSpecialPieceCount = 0;
    int             m_iOwnCoinCount = 0;
    
    bool            m_levelupLock;
    bool            m_bShowComeFrom;
    bool            m_bShowComeFromActivity;
    bool            m_bShowRedCoinNumber;
    bool            m_bShowRedPieceNumber;
    bool            m_bShowRedSpecialPieceNumber;
};

//碎片提示
class PlantLevelUpWithGeneralChipsHit : public Widget
{
public:
    PlantLevelUpWithGeneralChipsHit();
    virtual ~PlantLevelUpWithGeneralChipsHit();
    virtual void Draw(Sexy::Graphics* i_g) override;

    void InitView(MagentoProductPropsPtr i_ptr);
public:
    int m_plantChipsNumber = 0;
    int m_generalChipsNumber = 0;
    int m_universalChipsNumber = 0;
    int m_coinsNumber = 0;
    int m_nutrientNumber = 0;
};

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#endif
