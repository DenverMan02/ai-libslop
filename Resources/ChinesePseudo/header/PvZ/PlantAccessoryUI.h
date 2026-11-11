/*
 * PlantAccessoryUI.h
 *
 *  Created on: 2015-1-12
 *      Author: jianglc
 */

#ifndef PLANTACCESSORYUI_H_
#define PLANTACCESSORYUI_H_

#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "PlantAccessoryPropertySheet.h"
#include "PlantAccessoryMgr.h"
#include "MagentoService.h"
#include "AnimationControllerHelpers.h"

enum PlantAccessoryUIButtonId
{
    PLANT_ACCESSORY_BUTTON_ID_CLOSE = 100,
    PLANT_ACCESSORY_BUTTON_ID_BIND,
    PLANT_ACCESSORY_BUTTON_ID_EXCHANGE,
    PLANT_ACCESSORY_BUTTON_ID_SALE,
    PLANT_ACCESSORY_BUTTON_ID_UNBIND,
    PLANT_ACCESSORY_BUTTON_ID_SWITCH,
    PLANT_ACCESSORY_BUTTON_ID_INVALID,
    PLANT_ACCESSORY_BUTTON_ID_UNUSBLE,
    PLANT_ACCESSORY_BUTTON_ID_LINK,
    PLANT_ACCESSORY_BUTTON_ID_PACKET,
    PLANT_ACCESSORY_BUTTON_ID_RESET,
    PLANT_ACCESSORY_BUTTON_ID_STEADY,
    PLANT_ACCESSORY_PACKGET_BUTTON_ID_CONFIRM,
    PLANT_ACCESSORY_PACKGET_BUTTON_ID_CLOSE,
    PLANT_ACCESSORY_STEADY_LEVELUP_OK,
    PLANT_ACCESSORY_LEVEL_UP_CLOSE,
    PLANT_ACCESSORY_STEADY_Q_MARK,
    BTN_DESCRIPTION_OK,
    
};

enum PlantAccessoryUITabPanel
{
	PREVIEW_TAB = 1,
    EXCHANGE_TAB,
    SALE_TAB,
    STEADY_TAB,
};

enum BindedType
{
	NOT_BINDED,
	BINDED_BY_OTHER_PLANTS,
	BINDED_BY_SELF_PLANT
};

struct AccessoryPieceUIInfo
{
	AccessoryPieceUIInfo()
	{
		Type = "";
		OwnedPiece = 0;
		DisplayImageName = "";
	}

	std::string Type;
	int OwnedPiece;
	std::string DisplayImageName;
};

class AccessoryContent : public Widget, Sexy::ButtonListener
{
public:
	AccessoryContent(int i_id, BindedType i_bindedType, AccessoryUIInfo& i_info, bool i_unlocked, std::string i_type, bool i_banned, AccessoryPieceUIInfo& i_pieceInfo,
			PlantAccessoryUITabPanel i_panel);
	~AccessoryContent();

	virtual void Draw(Graphics *i_g);
	virtual void MouseDown(int x, int y, int theClickCount);
	void InternalDraw(Graphics *i_g);

	bool IsSelected();
	bool IsBinded();
	void SetSelected(bool i_selected);
	void SetBinded(bool i_binded);
    void SetSpecial(bool i_spec);

    int GetLevel();
    void SetLevel(int i_level);

	bool IsUnlocked();

	const std::string GetType();

	void LinkContents(const std::vector<AccessoryContent*> i_contents);

	AccessoryUIInfo& GetUIInfo();

	const int GetId();

	void UnselectOtherContents();

    void SetDisplayImage(Image* i_image);
	Image* GetDisplayImage();

	BindedType GetBindedType();

	int	GetOwnedPiece();

private:

    void InitView();
    void OnNotifyTutorialSelectContent(const std::string& i_type);

    int			m_Id;
    int         m_level;
	Image *     m_displayImage;
	Image *     m_bgImage;
	bool		m_isSelected;
	bool		m_isBinded;
    bool        m_isSpecial;
	AccessoryUIInfo m_info;
	// Used only in exchange mode
	bool		m_isUnlocked;

	std::vector<AccessoryContent*> m_contents;

	std::string m_type;
	bool		m_banned;

	BindedType	m_bindedType;
	Image *     m_displayPieceImage;
	SexyString	m_ownedPieceTxt;
	PlantAccessoryUITabPanel m_currentPanel;
};

namespace Message
{
    void NoticeMainUI(AccessoryContent* i_content);
    void NoticeAccessoryUIClose();
    void NotifyTutorialSelectContent(const std::string& i_type);
}

class AccessoryScrollPanel : public Widget
{
public:

	AccessoryScrollPanel(Rect &i_rect, int i_contentSize, const MagentoCategoryPropsPtr& i_category, PlantAccessoryUITabPanel i_type, PlantTypePtr i_plantType);
    ~AccessoryScrollPanel();

    void LinkContents(const std::vector<AccessoryContent*> i_contents);

    void SelectDefaultContent();

private:

    void	InitView();

    int     m_contentSize;

    std::vector<class AccessoryContent*> m_contents;
    MagentoCategoryPropsPtr m_category;
    PlantAccessoryUITabPanel m_type;
    PlantTypePtr m_plantType;
};

class AccessorySteadyPanel : public Widget
{
public:
    AccessorySteadyPanel();
    ~AccessorySteadyPanel();

    void init();

    virtual void Draw(Graphics *i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;

    void OnSteadyUINoticed(AccessoryContent* i_count);
    void OnSteadySuccess(int i_id);

private:
    AccessoryContent* m_left;
    AccessoryContent* m_right;
    class TextScollingWidget* m_leftStr;
    class TextScollingWidget* m_rightStr;
};

class AccessorySuperPacket : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
    AccessorySuperPacket();
    ~AccessorySuperPacket();

    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    virtual void Draw(Graphics *i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init();

};

class UISuperAccessoryLevelUp : public Widget, public Sexy::ButtonListener
{
public:
    UISuperAccessoryLevelUp();
    ~UISuperAccessoryLevelUp();

    virtual void Draw(Graphics *i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init(int i_uid);
private:
    Sexy::Image* m_image;
    SexyString m_str;
    int m_level;
};

class ShowSuperAccessoryDescriptionUI : public Widget, public ButtonListener
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView();
};

class PlantAccessoryUI : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
	PlantAccessoryUI(PlantTypePtr i_plantType);
    ~PlantAccessoryUI();

    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    void ToPanel(int i_tab);

    void DoSwitchTargetAccessory();

    void ShowAccessorySuperPacket();
    void CloseAccessorySuperPacket();

    void ShowSteadySuccessSuperPacket(int id);
    void CloseSteadySuccessSuperPacket();

    void showSuperAccessoryDescription();
    void closeSuperAccessoryDescription();

    void TriggerTutorial();

private:
    void InitView();
    void createPanel(PlantAccessoryUITabPanel i_tab);
    void RecreateCurrentPanel();

    void OnCloseDialog();

    void OnMainUINoticed(AccessoryContent* i_content);

    void OnConfirmExchange();

    void OnAccessorySaleComplete();

    void OnConfirmSale();

    void OnExchangeComplete(bool i_success);

    void OnActionComplete();
    void OnSoldTargetAccessory(int32 i_type);

    void OnConfirmReset();
    void OnConfirmSteady();

    void OnSteadySuccess(int id);
    void OnResetSuccess(int id);

    std::vector<std::pair<int,int>> GetCurrentSteadyCost();

    void onNarrationFinished();

	PVZ2UIScrollingWidget* m_scrollingWidget;
    PVZ2UIButton*           m_closeButton;
    PVZ2UIButton*			m_mainButton;
    PVZ2UIButton*			m_linkButton;
    PVZ2UIButton*           m_packetButton;
    PVZ2UIButton*           m_resetButton;
    PVZ2UIButton*           m_qmarkButton;
    std::vector<class PVZ2UIButton*>	m_tabButtons;
    PlantAccessoryUITabPanel m_currentPanel;
    AccessorySuperPacket* m_superPacket;
    UISuperAccessoryLevelUp* m_steadyLevelup;
    ShowSuperAccessoryDescriptionUI* m_desUI;

    AccessoryUIInfo 		m_info;

    std::string				m_selectedContentType;
    int						m_selectedContentId;

    SexyString m_description;
    SexyString m_boostDescription;
    SexyString m_ownedPiecesTxt;
    SexyString m_requiredPiecesTxt;
    SexyString m_Name;
    SexyString m_soldPriceTxt;
    SexyString m_ownedAccessoryTxt;
    SexyString m_materialState;
    float m_matRate;

    Image* 	   m_qualityImg;

    PlantTypePtr m_plantType;

    //PopAnimRig*  m_pAnimRig;

    //Image* m_plantPotImage;

    Image* 	   m_displayImg;
    int		   m_maxOwnedAccessory;
public:
    bool	   m_firstTutorialShow;
};

#endif /* PLANTACCESSORYUI_H_ */
