/*
 * NewPlantUI.h
 *
 *  Created on: 2023-3-16
 *      Author: admin
 */

#ifndef NEWPLANTUI_H_
#define NEWPLANTUI_H_

#include "Singleton.h"
#include "UIUtil.h"
#include "PVZGameState.h"
#include "MacroStateMachine.h"
#include "PVZGameStateTopHUDController.h"
#include "HotUIAdaptor.h"
#include "HotUIImage.h"
#include "HotUILabel.h"
#include "WarMistModule.h"
#include "HotUIAnim.h"

typedef std::map<std::string, RtWeakPtr<class MagentoProductProps>>	StringToProductMap;

enum NewPlantUISortType
{
	SortType_Sun,
	SortType_Range,
	SortType_Warrior,
	SortType_Protector,
	SortType_Support,
	SortType_Specialist,
	SortType_Rare4,
	SortType_Rare3,
	SortType_Rare2,
	SortType_Rare1,
	SortType_Rare0,
	SortType_Count,
	SortType_AllType,
	SortType_AllRare
};

enum NewPlantUISortValue
{
	SortValue_None = -1,
	SortValue_HP,
	SortValue_Attack,
	SortValue_Range,
	SortValue_Plant,
	SortValue_Support,
	SortValue_Control,
	SortValue_Level,
	SortValue_Count
};

enum NewPlantUITagColor
{
	TagColor_Green,
	TagColor_Red,
	TagColor_Blue,
	TagColor_Yellow
};

struct EntrySortValue
{
	EntrySortValue()
	: UnlockedValue(-1)
	, FavouriteValue(-1)
	, PlantName("")
	, CanLevelUpValue(0)
	, CanUnlockValue(0)
	, CanUnlockAvatarValue(0)
	{

	}

	int UnlockedValue;
	int FavouriteValue;
	std::string PlantName;
	int CanLevelUpValue;
	int CanUnlockValue;
	int CanUnlockAvatarValue;
};

struct AdaptorSeedPacketEntryConfig
{
	AdaptorSeedPacketEntryConfig()
	: Type(-1)
	, Rare(0)
	, Level(1)
	, PieceNum(-1)
	, RequiredPieceNum(-1)
	, Unlocked(false)
	{

	}

	int Type;
	int Rare;
	int Level;
	int PieceNum;
	int RequiredPieceNum;
	bool Unlocked;
	EntrySortValue SortValue;
};

class HotUIWidgetSeedPacketProgressBar: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIWidgetSeedPacketProgressBar, HotUIWidget, RtClass);

	HotUIWidgetSeedPacketProgressBar();

	virtual ~HotUIWidgetSeedPacketProgressBar();

	void SetInfo(const AdaptorSeedPacketEntryConfig& i_info);

protected:
	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

private:
	void drawProgress(Graphics* i_g);
	void init();

	AdaptorSeedPacketEntryConfig m_info;
	SexyString m_pieceStr;
};

class HotUIWidgetSeedPacketProgressBarProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetSeedPacketProgressBarProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetSeedPacketProgressBarProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetSeedPacketProgressBar::StaticGetClass();
	}
};

class HotUIWidgetValueProgressBar: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIWidgetValueProgressBar, HotUIWidget, RtClass);

	HotUIWidgetValueProgressBar();

	virtual ~HotUIWidgetValueProgressBar();

	void SetRank(int i_rank, int i_maxRank);

protected:
	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

private:
	void drawProgress(Graphics* i_g);
	void init();

	int m_rank;
	int m_maxRank;
	float m_percent;
};

class HotUIWidgetValueProgressBarProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetValueProgressBarProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetValueProgressBarProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetValueProgressBar::StaticGetClass();
	}
};

struct SeedPacketInfo
{
	SeedPacketInfo()
	: Type(-1)
	, Rare(0)
	, Level(1)
	, Unlocked(false)
	, CanUnlockValue(0)
	, CanLevelUpValue(0)
	, CanUnlockAvatarValue(0)
	, FavouriteValue(0)
	{

	}

	SeedPacketInfo(int i_type, int i_rare, int i_level, int i_unlocked, int i_canUnlockValue, int i_canLevelUpValue, int i_canUnlockAvatarValue,
			int i_favouriteValue)
	: Type(i_type)
	, Rare(i_rare)
	, Level(i_level)
	, Unlocked(i_unlocked)
	, CanUnlockValue(i_canUnlockValue)
	, CanLevelUpValue(i_canLevelUpValue)
	, CanUnlockAvatarValue(i_canUnlockAvatarValue)
	, FavouriteValue(i_favouriteValue)
	{

	}

	int Type;
	int Rare;
	int Level;
	bool Unlocked;
	int CanUnlockValue;
	int CanLevelUpValue;
	int CanUnlockAvatarValue;
	int FavouriteValue;
};

class HotUIWidgetSeedPacket: public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUIWidgetSeedPacket, HotUIWidget, RtClass);

	HotUIWidgetSeedPacket();

	virtual ~HotUIWidgetSeedPacket();

	void SetInfo(const SeedPacketInfo& i_info);
	const SeedPacketInfo& GetInfo() { return m_info; }

	void SetSelected(bool i_selected);
	bool IsSelected() { return m_selected; }
	bool IsLocked() { return !m_info.Unlocked; }
	virtual bool CanDrawLocked() { return true; }

	virtual bool CanSelect() { return true;}
    void SetDrawScale(float i_scale) { m_drawScale = i_scale; }

protected:

	// Widget initialization
	void			onInitializeWidget() override;

	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	void 			onUpdate() override;

protected:
	virtual void drawPacket(Graphics* i_g) {}
	virtual void init();
	virtual void drawLocked(Graphics* i_g);

	void onNotifyPlantPacketSelected(bool i_inside, int i_type, bool i_selected, bool i_fromInside);

	bool m_unlocked;
	bool m_selected;
	SeedPacketInfo m_info;
	Sexy::DeviceImage* m_seedPacketImage;
    float m_drawScale;
};

class HotUIWidgetSeedPacketProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetSeedPacketProperties, HotUIWidgetProperties, RtClass);

	HotUIWidgetSeedPacketProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetSeedPacket::StaticGetClass();
	}
};

class HotUIWidgetPlantSeedPacket: public HotUIWidgetSeedPacket
{
public:
	RT_CLASS_DEFINE(HotUIWidgetPlantSeedPacket, HotUIWidgetSeedPacket, RtClass);

	HotUIWidgetPlantSeedPacket();

	virtual ~HotUIWidgetPlantSeedPacket();

protected:
	void drawPacket(Graphics* i_g) override;
	void drawPlantFavoriteIcon(Graphics* i_g);

	bool CanDrawLocked() override;

	PlantProfessions Professtions;
};

class HotUIWidgetPlantSeedPacketProperties : public HotUIWidgetSeedPacketProperties
{
public:
	RT_CLASS_DEFINE(HotUIWidgetPlantSeedPacketProperties, HotUIWidgetSeedPacketProperties, RtClass);

	HotUIWidgetPlantSeedPacketProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUIWidgetPlantSeedPacket::StaticGetClass();
	}
};

// Sort Bg
class HotUITouchCloseWidget: public HotUIWidget
{
public:

	RT_CLASS_DEFINE(HotUITouchCloseWidget, HotUIWidget, RtClass);

	HotUITouchCloseWidget();

	virtual ~HotUITouchCloseWidget();

	void SetAdaptor(class HotUIAdaptor* i_adaptor) { m_adaptor = i_adaptor; }

	void OnTouchBegan( const Sexy::Touch& touch ) override;

	void CheckTargetWidget(const std::string& i_widgetName, int i_x, int i_y);

	class HotUIAdaptor* m_adaptor;
};

class HotUITouchCloseWidgetProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUITouchCloseWidgetProperties, HotUIWidgetProperties, RtClass);

	HotUITouchCloseWidgetProperties()
	{}

	RtClass* GetWidgetClass() const override
	{
		return HotUITouchCloseWidget::StaticGetClass();
	}

	std::vector<std::string> TargetWidgets;
};

class AdaptorSeedPacketConfig
{
public:
	void Order();

	std::vector<AdaptorSeedPacketEntryConfig> Entries;
};

class AdaptorSeedPacketEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorSeedPacketEntry, HotUIAdaptor, Sexy::RtClass);

	enum ButtonID
	{
		Selected
	};

	AdaptorSeedPacketEntry();
	virtual ~AdaptorSeedPacketEntry();

	void Configure(WidgetContainer* i_parent, const AdaptorSeedPacketEntryConfig& i_config);

	void ButtonDepress(int i_buttonID) override;

	virtual void UnlockBtn(bool i_unlock);

	bool IsSelected();

	void SetConfig(const AdaptorSeedPacketEntryConfig& i_config);
	const AdaptorSeedPacketEntryConfig& GetConfig() { return m_config; }

	void Filter(const std::vector<NewPlantUISortType>& i_types);
	void Sort(int i_value);

	void unselect();
	virtual void select(bool i_notify = true, bool i_fromInside = false);

	HotUIWidgetSeedPacket* GetSeedPacket();

	void ShowProgressBar(bool i_visible);
	const EntrySortValue& GetSortValue() { return m_config.SortValue; }

	void SetIsInside(bool i_inside) { m_inside = i_inside; }

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

	void onSetConfig();
	void onNewPlantView_PlantLevelUp(int i_type);
	void onNotifyPlantFavouriteChange(bool i_on, int i_type);

	WidgetContainer* m_parent;
	AdaptorSeedPacketEntryConfig m_config;
	HotUIWidget* m_entryWidget;

	bool m_inside;
};

class AdaptorSeedPacketBoard : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorSeedPacketBoard, HotUIAdaptor, Sexy::RtClass);

	AdaptorSeedPacketBoard();
	virtual ~AdaptorSeedPacketBoard();

	void Configure(WidgetContainer* i_parent, const AdaptorSeedPacketConfig& i_config, bool i_inside);
	void UnloadEntries();

	const AdaptorSeedPacketEntryConfig& GetEntryConfigById(int i_type);
	bool ReplaceEntryConfigById(int i_type, const AdaptorSeedPacketEntryConfig& i_config);
	AdaptorSeedPacketEntry* GetSelectedEntry();
	void LocateSelectedEntry();

	// Set config and refresh
	void SetConfig(const AdaptorSeedPacketConfig& i_config);

	void UnlockBtns(bool i_unlock);
	void SelectEntry(int i_index);
	void SelectEntryById(int i_id, bool i_notify, bool i_fromInside);

	bool IsEmpty();
	void ShowProgressBar(bool i_visible);

	void TestFilter();
	void Filter(const std::vector<NewPlantUISortType>& i_types);
	void Sort(NewPlantUISortValue i_type, bool i_ascend);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	virtual void fillEntries();
	void RepositionChildren();
	void SortChildren();

	WidgetContainer* m_parent;
	std::vector<AdaptorSeedPacketEntry*> m_seedPacketEntries;
	bool m_inside;

private:

	AdaptorSeedPacketConfig m_config;
};

class AdaptorSeedPacketBoardAllPlants : public AdaptorSeedPacketBoard
{
public:
	RT_CLASS_DEFINE(AdaptorSeedPacketBoardAllPlants, AdaptorSeedPacketBoard, Sexy::RtClass);

	AdaptorSeedPacketBoardAllPlants();
	virtual ~AdaptorSeedPacketBoardAllPlants();

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
};

class AdaptorNewPlantUIAllPlantsScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorNewPlantUIAllPlantsScreen, HotUIAdaptor, RtClass);

	enum ButtonID
	{
		Back = 1000,
		SortByType,
		ConfirmSortByType,
		SortByValue,
		SortAscend
	};

	AdaptorNewPlantUIAllPlantsScreen();
	virtual ~AdaptorNewPlantUIAllPlantsScreen();

public:
	void ButtonDepress(int i_buttonID) override;

	void Update() override;

	void Close();
	void SetOnBackAction(std::function<void(const std::vector<NewPlantUISortType>&, NewPlantUISortValue, bool)> i_onBack);
	bool ReplaceEntryConfigById(int i_type, const AdaptorSeedPacketEntryConfig& i_config);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

private:
	void setup();
	void onBack();
	void onSelectButton(NewPlantUISortType i_type);
	void onSelectValueButton(NewPlantUISortValue i_type);
	void onSortByType();
	void doSort(NewPlantUISortValue i_type);
	void showTouchCloseWidget(bool i_visible);
	void showSortByTypeMenu(bool i_visible);
	bool isSortByTypeMenuVisible();
	void onSortByValue();
	void showSortByValueMenu(bool i_visible);
	bool isSortByValueMenuVisible();
	void onConfirm();
	void getSelectTypes(std::vector<NewPlantUISortType>& i_types);
	void onSortAscend();
	void onClickSortAscendBtn();
	void onNotifyPlantPacketSelected(bool i_inside, int i_type, bool i_selected, bool i_fromInside);

	std::function<void(const std::vector<NewPlantUISortType>&, NewPlantUISortValue, bool)> m_onBackCallback;
	AdaptorSeedPacketBoard* m_seedPacketBoard;
	bool m_sortAscend;
	std::vector<NewPlantUISortType> m_cacheSortTypes;
	NewPlantUISortValue m_cacheSortValue;
};

// Plant Anim
enum HotUIPlantState
{
    PVZ_BEGIN_ENUM(HOTUIPLANTSTATE_),
    HOTUIPLANTSTATE_IDLE,
    HOTUIPLANTSTATE_WATER,
    PVZ_END_ENUM(HOTUIPLANTSTATE_)
};

class HotUIPlant : public HotUIAnim
{
public:
	RT_CLASS_DEFINE(HotUIPlant, HotUIAnim, RtClass);

	HotUIPlant();
	virtual ~HotUIPlant();

	// state
	void setState(HotUIPlantState i_state);
	HotUIPlantState getState();
	void SetPlantAndPlay(int i_plantId);

	void onWaterAnimStopped(const std::string& i_animName);

	bool IsWaterAnimAlive();

protected:
	Point GetAnimOffset() override;

private:
	bool IsInState(uint32 state) const { return m_state == state; }

	HotUIPlantState m_state;
	PlantTypePtr m_plantType;
};

class HotUIPlantProperties : public HotUIAnimProperties
{
public:
	RT_CLASS_DEFINE(HotUIPlantProperties, HotUIAnimProperties, RtClass);

	RtClass* GetWidgetClass() const override
	{
		return HotUIPlant::StaticGetClass();
	}
};

class AdaptorNewPlantUIEntryScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorNewPlantUIEntryScreen, HotUIAdaptor, Sexy::RtClass);

public:
	enum ButtonID
	{
		BackToMap = 1001,
		AllPlants,
		ClickPlant,
		SwitchToOld,
		LevelUp,
		GoToAvatar,
		GoToAccessory,
		AttributeDetail,
		ProfessionDetail,
		SwitchFavourite
	};

public:
	AdaptorNewPlantUIEntryScreen();
	virtual ~AdaptorNewPlantUIEntryScreen();

	void ButtonDepress(int i_buttonID) override;

	void Update() override;
	// void Draw(Graphics* g) override;
//	void DrawAll(ModalFlags* theFlags, Graphics* g) override;

	void RemovedFromManager(WidgetManager* i_widgetMgr) override;
	void SetPlant(const AdaptorSeedPacketEntryConfig& i_info);
	void RefreshPlant(int i_type);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	void setup();
	void close();

	void showTab(int i_tabID);
	void updateTabImages(int i_activeTab);
	bool canHandleInput();
	void createAllPlantsScreen();
	void onAllPlantsScreenBack(const std::vector<NewPlantUISortType>& i_types, NewPlantUISortValue i_value, bool i_ascend);
	void onEnterAllPlantsScreen();
	void onClickPlant();
	void onSwitchFavourite();
	void refreshFavourite();

	void initStats(HotUIStringMap& i_stringMap);
	const AdaptorSeedPacketEntryConfig& GetEntryConfigById(int i_type);
	bool ReplaceEntryConfigById(int i_type, const AdaptorSeedPacketEntryConfig& i_config);
	bool ReplaceInnerEntryConfigById(int i_type, const AdaptorSeedPacketEntryConfig& i_config);
	void onNotifyClickPlant(int i_type);
	void onNewPlantView_PlantLevelUp(int i_type);
	void onNewPlantView_SwitchAvatar(int i_type);
	void onNewPlantView_SwitchAccessory(int i_type);
	void onNewPlantView_UnlockAvatar(int i_type);
	void onChangePlantSuccess(const std::string& i_plantName);
	void onNotifyPlantPacketSelected(bool i_inside, int i_type, bool i_selected, bool i_fromInside);
	void changePlant(int i_id, bool i_fromInside = false);
	void onSetPlant(const AdaptorSeedPacketEntryConfig& i_info);

	AdaptorSeedPacketBoard* m_seedPacketBoard;
	AdaptorNewPlantUIAllPlantsScreen* m_allPlantsScreen;

	std::string m_currentTab;
	std::vector<ImagePtr> m_inactiveTabImages;
	std::vector<ImagePtr> m_activeTabImages;
	std::vector<class HotUIButton*> m_tabs;
	class UINewPlantView_SkillTab* m_skillTabContent;

	PlantTypePtr m_currenPlantType;
	int m_insideCachePlantId;

public:
	static StringToProductMap PlantProductMap;
	static StringToProductMap PlantAvatarProductMap;
};

namespace NewPlantUIUtils
{
	AdaptorSeedPacketConfig buildSeedPacketInfo();
	void addSeedPacketEntry(AdaptorSeedPacketConfig& io_config);

	int GetUnlockedPlantNum();
	int GetTotalPlantNum();
	bool IsPlantFavourite(const std::string& i_plantName);
	int GetSortValue(NewPlantUISortValue i_type, int i_id);
	int GetPlantTargetValueRank(int i_id, int i_valueType);
	NewPlantUITagColor GetTagColorByPlant(int i_tag);
	SexyString GetAvatarDescription(int i_AvatarId);
	ImagePtr GetAccessoryContentImage(int quality);
	bool IsProfessionValue(NewPlantUISortType i_type);
	PlantProfessions GetPlantProfessionValue(NewPlantUISortType i_type);
	int GetPlantRareValue(NewPlantUISortType i_type);
	bool IsRareValue(NewPlantUISortType i_type);
	RtWeakPtr<class MagentoProductProps> GetProductByName(const std::string& theName);
	RtWeakPtr<class MagentoProductProps> GetAvatarProductByName(const std::string& theName);
	bool canPlantUnlockAvatar(const std::string i_plantName);
	bool IsWaterPlant(PlantTypePtr i_type);
}

class NewPlantUIEntryScreenTopHUD : public PVZGameStateTopHUDController
{
public:
	RT_CLASS_DEFINE(NewPlantUIEntryScreenTopHUD, PVZGameStateTopHUDController, Sexy::RtClass);

	void Open() override;
};

class NewPlantUIEntryScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(NewPlantUIEntryScreenState, PVZHotUIGameState, RtClass);

protected:
	RtClass* getTopHudControllerClass() override;
	RtClass* getHotUIAdaptorClass() override;

	void Enter() override;

	std::string GetMusicStartEvent() override { return "Play_Joust_Dashboard_Music"; }
	std::string GetMusicStopEvent() override { return "Stop_Joust_Dashboard_Music"; }

};

enum PlantUIType
{
	PlantUIType_Old,
	PlantUIType_New
};

class NewPlantUIMgr : public LazySingleton <NewPlantUIMgr>
{
public:
	NewPlantUIMgr();
    ~NewPlantUIMgr();

    inline PlantUIType GetUIType() { return m_type; }
    inline void SetUIType(PlantUIType i_type) { m_type = i_type; }

    void Switch(PlantUIType i_type);
    bool IsNewUI();
    bool HasFinishedTutorial();

private:
    void confirmSwitch(class UIMessageBox* box, int buttonID);
    void cancelSwitch(UIMessageBox* box, int buttonID);

    PlantUIType m_type;
    PlantUIType m_typeToSwitch;
};

#define gNewPlantUIMgr NewPlantUIMgr::GetInstancePtr()

namespace Message
{
	void NotifyPlantPacketSelected(bool i_inside, int i_type, bool i_selected, bool i_fromInside);
	void NotifyPlantFavouriteChange(bool i_on, int i_type);
	void NotifyClickPlant(int i_type);
}

#endif /* NEWPLANTUI_H_ */
