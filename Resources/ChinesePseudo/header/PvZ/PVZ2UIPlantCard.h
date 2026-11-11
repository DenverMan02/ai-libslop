//
//  PVZ2UIPlantCard.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UIPlantCard_h
#define PlantsVersusZombies2_PVZ2UIPlantCard_h

#include "PVZTypes.h"
#include "PVZ2UIButton.h"
#include "BoardEntity.h"
#include "MagentoService.h"
#include "PrimeTextWidget.h"
#include "SocialInfo.h"
#include "ObjectTypeDescriptor.h"

// This is used to display a game object inside of a cute little box.
// It will expand to fill its width and height. The inner background image
// will not be scaled, but it will be centered within the box with its
// edges clipped to fit.

namespace Message
{
    void ChangeStoreDisplayerButton();
	void updateBuyPlantButton();
}

enum SeedChooserButtonId
{
	Button_Accessory,
	BuyPlant_Click
};

class PVZ2UIGameObjectCard : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PVZ2UIGameObjectCard(ObjectTypeDescriptorPtr i_objectType, bool i_animated, PlantAvatarType eAvatar = E_AVATAR_ILLEGAL, bool needPot = false, bool loadBG = true);
	PVZ2UIGameObjectCard(Image* i_image);
	virtual ~PVZ2UIGameObjectCard();
	
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	
	void SetShowPlantPrice(bool i_showPrice);
	void SetGreyedOut(bool i_grey);
	void SetShowLock(bool i_showLock);
	void SetUseSmallLock(bool i_smallLock);
	void SetTutorialBackground();
	void SetSpecificBackground(Sexy::Image* i_backgroundImage, Color i_borderColor);
	void SetStandaloneImage(Sexy::Image* i_image);
    void SetDayFirstPayRewardImage(Sexy::Image* pImage);
    void SetObjectExtendsOutOfRect(bool i_extents);
    void SetItemOffset(float i_percentVertical);
	
	void SetVerticalOffsetPct(float i_newPct);
    
    void SetPopAnimScale(float i_scale);
    void SetShowLevelRank(bool i_show);
    void SetSmallLevelRank();
    static class Image* GetLevelImage(int level);

	bool isExperiencePlant();
	void setIsShowExpLevel(bool isShowExpLevel);

	void ChangeNextAvatar();
	void SetAvatarIndex(int i_avatarIndex);
	int  GetAvatarIndex();

	void SetIsShowPlantPot(bool i_show);

	void SetNeedDeleteGroup(bool i_flag) { m_deleteGroup = i_flag; }

private:
	ObjectTypeDescriptorPtr m_objectType;
	bool m_animated;
	
	bool m_showLevelRank;
    bool m_smallLevelRank;
	bool m_showPrice;
	bool m_greyedOut;
	bool m_showLock;
	bool m_smallLock;
    bool m_objectExtentsOutOfRects;
    bool m_showPlantPot;
	
	float m_verticalOffsetPct;

	SexyString m_plantPrice;

	Color m_backgroundBorderColor;

	class PopAnimRig* m_animRig;
    Sexy::Rect m_animRigRect;
	
	Sexy::Image* m_upgradeImage;

	Sexy::Image* m_backgroundImage;

	Sexy::Image* m_plantPotImage;
    
    std::string m_plantPieceType;

	bool m_bIsShowExpLevel;
    bool m_loadBG;
	int m_avatarIndex;

	bool m_deleteGroup = true;
};

// Contains a PVZ2UIGameObjectCard that shows the reward, and draws the object's
// description to the side

class PVZ2UIRewardObjectDisplayer : public Sexy::Widget
{
public:
	PVZ2UIRewardObjectDisplayer(ObjectTypeDescriptorPtr i_objectType, bool i_starReward = false, int i_starNum = 0, PlantAvatarType eAvatar = E_AVATAR_NONE, bool i_isToPiece = false, bool i_isView = false);
	PVZ2UIRewardObjectDisplayer(Image* i_placardImage, SexyString i_overlayTitleText, SexyString i_objectName, SexyString i_objectDescription,
                                Image* i_bgImage = NULL, bool i_centerDes = false);
	virtual ~PVZ2UIRewardObjectDisplayer();
	
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void DrawOverlay(Sexy::Graphics* i_g, int i_priority);

	inline void SetOverlayTitleText(SexyString i_titleText);

	inline void SetDescription(SexyString i_description);

	inline void SetName(SexyString i_name);

protected:
	SexyString m_objectName;
	SexyString m_objectDescription;
    SexyString m_overlayTitleText;
	PVZ2UIGameObjectCard* m_objectCard;
	Image* m_placardImage;

	//zhaobk added star plant desc
	bool m_starReward;
	int m_starNum;
    bool m_isToPiece;
    bool m_centerDes;
};

inline void PVZ2UIRewardObjectDisplayer::SetOverlayTitleText(SexyString i_titleText)
{
	m_overlayTitleText = i_titleText;
}

inline void PVZ2UIRewardObjectDisplayer::SetDescription(SexyString i_description)
{
	m_objectDescription = i_description;
}

inline void PVZ2UIRewardObjectDisplayer::SetName(SexyString i_name)
{
	m_objectName = i_name;
}

class PVZ2UIAccessoryObjectDisplayer : public Sexy::Widget
{
public:
	PVZ2UIAccessoryObjectDisplayer(Image* i_qualityImg, Image* i_displayImg, SexyString i_name, SexyString i_description, SexyString i_boostDescription);
	virtual ~PVZ2UIAccessoryObjectDisplayer();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void DrawOverlay(Sexy::Graphics* i_g, int i_priority);

	inline void SetOverlayTitleText(SexyString i_titleText);

	inline void SetDescription(SexyString i_description);

	inline void SetName(SexyString i_name);

protected:
	SexyString m_objectName;
	SexyString m_objectDescription;
	SexyString m_objectBoostDescription;
    SexyString m_overlayTitleText;
	PVZ2UIGameObjectCard* m_objectCard;
	Image* m_placardImage;
};

inline void PVZ2UIAccessoryObjectDisplayer::SetOverlayTitleText(SexyString i_titleText)
{
	m_overlayTitleText = i_titleText;
}

inline void PVZ2UIAccessoryObjectDisplayer::SetDescription(SexyString i_description)
{
	m_objectDescription = i_description;
}

inline void PVZ2UIAccessoryObjectDisplayer::SetName(SexyString i_name)
{
	m_objectName = i_name;
}

class PVZ2UIRewardAvatarObjectDisplayer : public PVZ2UIRewardObjectDisplayer
{
public:
	PVZ2UIRewardAvatarObjectDisplayer(ObjectTypeDescriptorPtr i_objectType, const std::string& objectName, const std::string& objectDesc, bool i_starReward = false, int i_starNum = 0, PlantAvatarType eAvatar = E_AVATAR_NONE);
	virtual ~PVZ2UIRewardAvatarObjectDisplayer();

	void SetAvatarIndex(int i_avatarIndex);
};

// Displays the currently selected plant above the seed chooser

class PVZ2UISeedChooserPlantPotButton : public PVZ2UIButton
{
public:
	PVZ2UISeedChooserPlantPotButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White) : PVZ2UIButton(i_id, i_listener, i_buttonName, i_fontColor){}
	virtual void MouseDown(int i_x, int i_y, int i_btnNum, int i_clickCount);
	virtual void MouseUp(int i_x, int i_y, int i_btnNum, int i_clickCount);
};

class PVZ2UISeedChooserPreviewDisplay : public Sexy::Widget, Sexy::ButtonListener
{
public:
	PVZ2UISeedChooserPreviewDisplay(ObjectTypeDescriptorPtr i_objectType);
	virtual ~PVZ2UISeedChooserPreviewDisplay();
	
	virtual void Draw(Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);

	// Hacky way to refresh our animrig because we're not part of a real widget manager
	void ManualUpdate();
	void SetDescriptionText(const SexyString& i_text);
	
	void InitializeButton();
	void CheckPlantPotButtonPress(const int i_mouseX, const int i_mouseY);
	void CheckPlantPotButtonDepress(const int i_mouseX, const int i_mouseY);
	virtual void ButtonDepress(int i_id);
	void UpdateTimeLabel();
	void addBuyPlantButton(int theX, int theY, int theWidth, int theHeight);
	void showBuyPlantUI();
	void updateButtonUI();
	bool isCurPlantAlreadyBuy();
	void OnChangeButton();

	void SetIsShowFamilyDes(bool i_flg);
	void SetIsShowLevelIcon(bool i_flg);
	void SetIsShowPlantPot(bool i_flg);
	void HideAvatar();


private:
	SexyString m_objectName;
	SexyString m_objectDescription;
	PVZ2UIGameObjectCard* m_objectCard;
	Image* m_placardImage;
	PVZ2UISeedChooserPlantPotButton* m_accessoryButton;
	ObjectTypeDescriptorPtr m_objectType;
    
    SexyString m_familyProperties;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	PVZ2UIButton* m_buyPlantButton;
	PVZ2UIButton* m_changeAvatarButton;

	bool m_isShowFamilyDes = true;
	bool m_isShowLevelIcon = true;
	bool m_isShowPlantPot = true;
};

// Contains a PVZ2UIGameObjectCard that shows the animated object on top of a lawn,
// and composites this on top of the appropriately sized and colored placard

class PVZ2UIAlmanacObjectDisplayer : public Sexy::Widget
{
public:
	PVZ2UIAlmanacObjectDisplayer(ObjectTypeDescriptorPtr i_objectType);
	virtual ~PVZ2UIAlmanacObjectDisplayer();
	
	virtual void Draw(Sexy::Graphics* i_g);
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
private:
	bool m_needPurchase;
	SexyString m_objectName;
	PVZ2UIGameObjectCard* m_objectCard;
	Image* m_placardImage;
};

class PVZ2UIAwakenObjectDisplayer : public Sexy::Widget
{
public:
    PVZ2UIAwakenObjectDisplayer(ObjectTypeDescriptorPtr i_objectType);
    virtual ~PVZ2UIAwakenObjectDisplayer();
    
    virtual void Draw(Sexy::Graphics* i_g);
    
    virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
private:
    bool m_needPurchase;
    SexyString m_objectName;
    PVZ2UIGameObjectCard* m_objectCard;
    Image* m_placardImage;
};

// Contains a GameObjectCard that shows the upgrade and draws the upgrade card art around it

class PVZ2UIAlmanacUpgradeDisplayer : public Sexy::Widget
{
public:
	PVZ2UIAlmanacUpgradeDisplayer(ObjectTypeDescriptorPtr i_upgradeType);
	virtual ~PVZ2UIAlmanacUpgradeDisplayer();
	
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
	void OnBought();
	
private:
	SexyString m_objectName;
	SexyString m_objectInfo;
	PVZ2UIGameObjectCard* m_objectCard;
	Image* m_placardImage;
    
    PrimeTypeface* m_nameTextWidget;
    PrimeTypeface* m_infoTextWidget;
    
    bool m_firstInit;
};

//

class PVZ2UIAlmanacStat : public Sexy::Widget
{
public:
	PVZ2UIAlmanacStat(bool i_isZombie, const SexyString& i_name, const SexyString& i_textValue, Image* i_icon, float i_fillPct, bool bShowZombieLevelUp = false,
			Color i_valueColor = Color::White);
	virtual ~PVZ2UIAlmanacStat();
	
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
private:
	bool m_isZombie;
	SexyString m_name;
	SexyString m_textValue;
	float m_fillPct;
    bool m_bShowZombieLevelUp;
	
	Image* m_icon;

	Color m_valueColor;
};

// Draws description text, does NOT do any scrolling by itself (use a holder for that!)

class PVZ2UIAlmanacDescription : public Widget
{
public:
	PVZ2UIAlmanacDescription(const SexyString& i_header, const SexyString& i_descriptionText);
	virtual ~PVZ2UIAlmanacDescription();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
private:
	int m_descriptionYStart;
	SexyString m_header;
	SexyString m_descriptionText;
    
    void CreateTextMeshes();
    void DrawTextMeshes(Graphics* i_g);
    PrimeGlyphMesh* m_headerMesh;
    PrimeGlyphMesh* m_descriptionMesh;
    int m_textCacheVersion;
};
class PVZ2UIAlmanacDescriptionHolder : public Widget, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UIAlmanacDescriptionHolder(const SexyString& i_header, const SexyString& i_descriptionText);
	virtual ~PVZ2UIAlmanacDescriptionHolder();
	
	virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
	
private:
	PVZ2UIAlmanacDescription* m_descriptionWidget;
	PVZ2UIScrollingWidget* m_scrollingWidget;
};

// Displays a series of stat widgets on top and a big description text box on bottom

class PVZ2UIAlmanacInfoDisplayer : public Sexy::Widget
{
public:
    PVZ2UIAlmanacInfoDisplayer(ObjectTypeDescriptorPtr i_objectType, bool bShowDesc = true, bool bShowZombieLevelUp = false, bool bBoardIntro = false);
	virtual ~PVZ2UIAlmanacInfoDisplayer();
	
	virtual void Update();
	
	virtual void Draw(Sexy::Graphics* i_g);
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
private:
	SexyString colorizeDescription(const SexyString& i_description);
	float getStatBarPct(BoardEntityStatValue i_statValue);
	Image* getStatIconFromEnum(BoardEntityStatType i_statType);
	SexyString getStringFromEnum(BoardEntityStatType i_statType);
	SexyString getStringFromValue(BoardEntityStatValue i_statValue);
	Color getValueColor(BoardEntityStatValue i_statValue);
	
	std::vector<PVZ2UIAlmanacStat*> m_statWidgets;
	PVZ2UIAlmanacDescriptionHolder* m_description;
	
	bool m_isZombie;
    
    bool m_bShowZombieLevelUp;
    
    bool m_isBoardIntro;

    int m_numZombieStats;
};

// Displays a store item, a title, a description, and a 'buy me' button

class PVZ2UIBestDealBanner : public Sexy::Widget
{
public:
	PVZ2UIBestDealBanner();
	
	virtual void Draw(Sexy::Graphics* i_g);
};

class PVZ2UIStoreItemDisplayer : public Sexy::Widget
{
public:
	PVZ2UIStoreItemDisplayer(MagentoProductPropsPtr i_props, int i_buttonId, ButtonListener* i_listener);
    //PVZ2_CHINESE_START PlantBag
	PVZ2UIStoreItemDisplayer(int i_buttonId, ButtonListener* i_listener);
    //PVZ2_CHINESE_END
	virtual ~PVZ2UIStoreItemDisplayer();
    void OnChangeButton();
    void OnNotifyFreeItemGot(const std::string& i_type);
//PVZ2_CHINESE_START	
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
//PVZ2_CHINESE_END
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	
	MagentoProductPropsPtr GetProps() const
	{
		return m_props;
	}
    
    void SetTimingFreeInSmallWindow(bool flag);//PVZ2_CHINESE

    void SetIgnoreShowPieces(bool i_ignoreShowPieces);
	
private:
    
    void CloseCurrentGemProductNotice(const std::string & sSku);
    void onADFinished(int i_type);
    
	MagentoProductPropsPtr m_props;
	
	PVZ2UIGameObjectCard* m_objCard;
	class PurchaseItemWidget* m_purchaseWidget;
	PVZ2UIButton* m_buyButton;
    Image* m_imgObtain;
	Image* m_backgroundImage;
    Image* m_imgBanner;
    Image* m_imgIsPlantlocked;
    Image* m_imgIcon;
	Image* m_imgTimingFree;

	SexyString m_headerLabel;
	SexyString m_descriptionLabel;
	int m_headerHeightScaled;
    
	//PVZ2_CHINESE_START
    Sexy::Point m_iconPos;
    DrawStringJustification m_drawAlign;
    
    bool  m_bHasPieces;
    bool  m_bIgnoreShowPieces;
    float m_progress;
    
    //PVZ2_CHINESE_START PlantBag
    Image* m_imgPlantBag;
    bool   b_IsPlantBag;
    //PVZ2_CHINESE_END
    
    SexyString  m_labelProgess;
    Sexy::Rect  m_rectProgress;
    int         m_button_width;
    Sexy::Rect  m_rectObtain;
    uint64      m_nextTimingFree;
    
    bool        m_TimingFreeInSmallWindow;
    //PVZ2_CHINESE
	//PVZ2_CHINESE_END
};

#endif
