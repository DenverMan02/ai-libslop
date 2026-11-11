//
//  SeedChooser.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 7/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SeedChooser_h
#define PlantsVersusZombies2_SeedChooser_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "PVZTypes.h"
#include "SeedPacket.h"
#include "SeedBank.h"
#include "GameButton.h"
#include "ToolTipWidget.h"
#include "MagentoService.h"
#include "SlidingWidget.h"
#include "PlantBoostMgr.h"

//PVZ2_CHINESE_START
#include "PVZ2UIButton.h"
//PVZ2_CHINESE_END
#ifdef HOST_ANDROID
#include "EASquared.h"
#endif

//#include "BorrowPlantUI.h"  //PVZ2_CHINESE BorrowPlant

typedef struct ArtifactInfo Seed_ArtifactInfo;

namespace Message
{
	void SeedChooserSelectionFinalized();
	void SelectSeedChooserArtifactSelectWidget(int i_artifactId);
}

STATE_ENUM_BASE_BEGIN(PacketState)
	PS_InChooser,
	PS_Moving,
	PS_InBank,
	PS_Blacklisted,
	PS_Purchasable,
	PS_Empty,
    PS_NotEnough,
STATE_ENUM_END(PacketState)

struct ChooserPacketData
{
	SexyVector2			Position;
	pvztime_t			MovingStartTime;
	pvztime_t			MovingEndTime;
	SexyVector2			MovePositionStart;
	SexyVector2			MovePositionEnd;
	int					SeedTypeIndex;
	int					SeedBankIndex;
	SeedPacketPtr		AttachedSeedPacket;
	PacketState			State;
	bool				IsImitaterPacket;
	MagentoProductPropsPtr ProductProps;
};

typedef std::vector<ChooserPacketData>	ChooserPacketVector;
typedef std::vector<PlantTypePtr>		PlantTypeVector;

enum SeedChooserButtons
{
    SEEDCHOOSERBUTTON_PurchasePlant = 101,
	SEEDCHOOSERBUTTON_FavoritePlants = 107,
    SEEDCHOOSERBUTTON_SelectionReset,
	SEEDCHOOSERBUTTON_SelectArtifact,
	SEEDCHOOSERBUTTON_SelectArtifactDetails,
	SEEDCHOOSERBUTTON_SelectArtifactConfirm,
	SEEDCHOOSERBUTTON_SelectArtifactClose,
};

class Plant;

class PlantTypeList
{
public:
	std::vector<PlantTypePtr>& GetList() { return Plants; };
	void Add(PlantTypePtr i_plantTypePtr);

private:
	std::vector<PlantTypePtr> Plants;
};

class SeedChooser : public SlidingWidget, public ButtonListener
{
	
public:
	RT_CLASS_DEFINE(SeedChooser, UIWidget, RtClass);	
	
	SeedChooser();
	virtual ~SeedChooser();
	
	virtual void			SetSeedBankProperties(const class SeedBankProperties* i_propertySheet);

	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			ButtonPress(const int i_buttonID) override;
	virtual bool			IsMouseOver(const int i_mouseX, const int i_mouseY) override;
	
	virtual void			VerifyAndSelectSeeds();
    void                    AutoSelectSeedsAndFinalize();
    void					ForceSelection(const std::string& i_type);
	void					OverrideValidPlants(const std::vector<int>& i_plantTypeIds);
    void                SetSeedPacketType(const RtName seedPacketType);
    void                SetSpecialSeedPacketType(const RtName seedPacketType);
    void                SetChosenPacketCountMax(uint8 iVal) { m_chosenPacketCountMax = iVal; }
    void				GetSelectedPlantTypes(std::vector<PlantTypePtr>& o_plantTypes);


	void					refreshCurrentArtifact();
	void					ShowSeedChooserArtifactSelectWidget();
	void					CloseSeedChooserArtifactSelectWidget();

protected:
	
	// Protected Interface (Inheritable)

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
	OVERRIDE_STATE_UPDATE(WidgetState, Initializing);
	OVERRIDE_STATE_ONEXIT(WidgetState, Initializing);
	OVERRIDE_STATE_ONENTER(WidgetState, Ready);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	OVERRIDE_STATE_ONEXIT(WidgetState, Ready);

	virtual void			onCheatEnabled();
	virtual void			onCheatDisabled();
	virtual void			onDangerRoomInit();
    void                    onViewBoardOrZombiesButtonPressed();
	virtual void			onSlideInFinished() override;
	virtual void			onSlideOutFinished() override;
#ifdef HOST_ANDROID
	void					OnGameStartAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
#endif
	
	virtual void			drawTabContentsSeedChooser(Sexy::Graphics* i_g);
    
    
	virtual void			startMovingPacket(ChooserPacketData& i_packetData);
	virtual void			finalizeSelection();
	virtual void			initLoadingResourcesGroupList() override;
    virtual void         onLandInBank(ChooserPacketData& i_packetData) {}

	virtual void			setSeedPreview(ChooserPacketData& i_packetData);
	void					onItemPurchasedFromStore(class MagentoProductProps* i_props);
    
    void                    sendBorrowRequestBeforeFinalize();  //PVZ2_CHINESE BorrowPlant
	void 					showBuyPlantUI();
	bool 					isCurPlantExp();

	void					addToolToChooserPackets(const std::string& i_typeName);
	void 					addPlantToChooserPackets(PlantTypePtr plantTypePtr, int &seedsNeedingPurchase, std::vector<std::tuple<int, PlantTypePtr>>& availablePresetPlants, std::vector<MagentoProductPropsPtr>& purchasablePlants, bool isExp = false);
	bool isCurPlantAlreadyBuy();
protected:
	
	// Private Interface
	virtual void            rebuildValidPlantTypeList();
	void					initChooserPackets();
    void                	initButtons();
	void					calcPacketPositionInChooser(const int i_index, SexyVector2 &io_position);
	void					calcPacketPositionInBank(const int i_index, SexyVector2 &io_position);
	void					deleteChooserPackets();
	virtual bool			isBlacklisted(const std::string& i_seedName);
	void					toggleHideChooser();
	bool					checkForZombieTouch(const int i_mouseX, const int i_mouseY);
	void					initializeSeedPacket(SeedPacket* seedPacket, const PacketState i_packetState, const MagentoProductPropsPtr i_productProps, bool i_special = false);
	
	void					drawFavoriteButton(Sexy::Graphics* i_graphics) const;
	void					drawTranslatedWidget(Sexy::Graphics* i_graphics, Widget* i_widget) const;

	virtual void			drawArtifact(Sexy::Graphics* i_graphics) const;
	void					toggleSelectArtifact();
	void					ShowArtifactDetails();

	void 					setPlantPreview(PlantTypePtr i_plantTypePtr);
	Rect 					calcInfoCardRect();
	void 					reindexBankPackets();
	bool					isCurrentPlantFavorite() const;
	void					togglePlantFavorite();
	void					updateFavoriteButton();
	void					createFavoriteButton();
	void					updateFavoriteSorting();
	PlantTypeList 			createSortedPlantList();
	bool                    isFavoritesFeatureToggleEnabled();
	bool                    isPlantTypeAFavorite(const PlantType*) const;
	bool                    isPlantTypeAPvZ1Plant(const PlantType*) const;
	bool                    isPlantTypeATrialPlant(const PlantType*) const;

	int						findImitaterChooserPacketIndex() const;
	int 					findPlantTypeChooserPacketIndex(const std::string &i_plantTypeName) const;
	void					updateImitaterChooserPacketState();

	void					panBoardLeft();
	void					panBoardRight();
	void					onPanBoardLeftFinished();
	void					onPanBoardRightFinished();
	
	void					onRepickButtonPressed();
	void					onPlayButtonPressed();
	void					onBuyPlantButtonPressed();
    
    virtual void            initPlantFromRecord();
    void                    getBattleArrayType();
    
    //PVZ2_CHINESE_START BorrowPlant
//	void                    onBorrowPlantButtonPressed(FriendInfo * i_friendinfo,int buttonIndex);
    void                    onMsgError(int erroId);
	void                    onMsgBorrowFriendPlant(int32 i_userid);

	void					OnServerGemCallBack(bool i_Success);
	void					onPlantAccessoryActionComplete();
	void                    OnOrientationChanged();
	void 					onNarrationFinished();
    //PVZ2_CHINESE_END
    
	// Private Members (serialized)
	
	// Private Members (not serialized)
	bool						m_shouldDrawArtifact;
	ChooserPacketVector			m_chooserPackets;
	ChooserPacketVector			m_bankPackets;
	int							m_imitaterChooserPacketIdx;
	uint8						m_chosenPacketCount;
	uint8						m_chosenToolPacketCount;
	uint8						m_chosenPacketCountMax;
	uint8						m_requiredSelections;
	int							m_scrollOffset;
	int							m_scrollArea;
	bool						m_hideChooser;
	StretchableNewLawnButton*	m_buttonReady;
    PVZ2UIButton*               m_buttonReset;
	PVZ2UIButton*				m_buttonFavorite;
	PVZ2UIButton*				m_buttonArtifact;
	PVZ2UIButton*				m_buttonArtifactDetails;
	StretchableNewLawnButton*	m_buttonBuyPlant;

	class SeedChooserArtifactSelectWidget* m_artifactWidget;

	Sexy::Image* m_artifactImage;
	int m_artifactLevel;
	int m_artifactRank;
    
    StretchableNewLawnButton*   m_buttonHelp;   //PVZ2_CHINESE BorrowPlant
    
	//PVZ2_CHINESE_START
	//StretchableNewLawnButton*	m_buttonPurchase;
    PVZ2UIButton* m_buttonPurchase;
	//PVZ2_CHINESE_END
	MagentoProductPropsPtr		m_almanacPlantPurchaseProps;
	bool						m_overridenValidPackets;
	
	class PVZ2UISeedChooserPreviewDisplay* m_seedInfoWidget;
    
    bool						m_seedChooserFiveWide;
	
	const class SeedBankProperties*	m_seedBankProps;
	
	Sexy::Rect					m_seedPacketArea;
	Sexy::Rect					m_seedPacketAreaDraw;
	Sexy::Rect					m_powerupArea;
	Sexy::Rect					m_tabFrameRect;
	Sexy::Rect					m_tabFrameContentsRect;
	ToolTipWidget*				m_toolTip;
	SeedPacketPtr				m_selectedPacket;
    BattleArrayType             m_battleArrayType;
	
    //PVZ2_CHINESE_START BorrowPlant
	bool                        m_bIsLoading;
    int32                       m_BorrowFriendUserId;
    int                         m_BorrowPlantId;
    int                         m_BorrowButtonIndex;
    bool						m_hasSlideIn;
    uint32						m_chooserPacketIndex;
    //PVZ2_CHINESE_END
    
    RtName                      m_seedPacketType;
    RtName 						m_specialSeedPacketType;
    ImagePtr                    m_imageBankPacketEmpty;
	int							m_pvz1Segmentation;
};

class SeedChooserArtifactSelectWidgetItem : public Sexy::Widget
{
public:
	SeedChooserArtifactSelectWidgetItem();
	~SeedChooserArtifactSelectWidgetItem();

	virtual void Draw(Graphics* i_g) override;
	virtual void Update() override;
	virtual void TouchBegan(const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch ) override;

	void InitView(ArtifactInfo i_info);

public:
	int m_currentArtifactID;
	bool m_selected;
	int m_touchId;
	int m_artifactID;
    int m_rank;
    int m_level;
	Sexy::Image* m_image;
};

class SeedChooserArtifactSelectWidget : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	SeedChooserArtifactSelectWidget();
	~SeedChooserArtifactSelectWidget();

	virtual void Draw(Graphics* i_g) override;
	void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
	void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
	virtual void ButtonDepress(int i_id) override;

	void InitView();
	void OnSelectSeedChooserArtifactSelectWidget(int i_artifactId);
	void EquipArtifactChange(int i_artifactId);
	void SetSeedChooser(SeedChooser* i_seedChooser) {m_seedChooser = i_seedChooser; }

private:
	int m_currentSelect;
	SeedChooser* m_seedChooser;
	SexyString m_contentStr;
	PVZ2UIButton* m_btnButton;
	PVZ2UIButton* m_closeButton;
	std::vector<SeedChooserArtifactSelectWidgetItem*> m_vecItemList;
};



typedef RtWeakPtr<SeedChooser> SeedChooserPtr;

#endif
