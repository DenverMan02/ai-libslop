#ifndef LEVELEDITOR_BOARDMODULE_H
#define LEVELEDITOR_BOARDMODULE_H

#include "LevelEditorDefine.h"
#include "LevelEditorUtil.h"
#include "LevelEditorConfig.h"
#include "UISingletonDialog.h"
#include "ButtonListener.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "functional"
#include "LevelEditorStatueMaze.h"


/*---------------------Board 场景编辑------------------------------*/

//场景格子
class LevelEditorBoardGrid : public Widget
{
public:
    LevelEditorBoardGrid(int i_row, int i_column);
    virtual ~LevelEditorBoardGrid();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void Init();
    virtual void Reload();
    virtual void ClearData();
    virtual void SetData(const LevelEditorCardInfo& i_data);
    void SetSelected(bool i_selected) { m_selected = i_selected; }
    bool GetSelected() { return m_selected; }

protected:
    int m_touchId;
    int m_row;
    int m_column;
    bool m_selected;
    LevelEditorCardInfo m_data;
    Sexy::DeviceImage* m_seedPacketImage;
private:
    void OnTutorialCreated();
};

//点击场景格子出现的： 地面 地表 物体放置界面
class LevelEditorBoardGridBehavior : public Widget, public ButtonListener
{
public:
    LevelEditorBoardGridBehavior();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

public:
    void Init(int i_row, int i_column, std::function<void(const LevelEditorCardInfo&)> i_cardfunc);
    void TriggerTutorial();

private:
    int m_row;
    int m_column;
    class PVZ2UIButton* m_groundButton;
    class PVZ2UIButton* m_surfaceButton;
    class LevelEditorGroundSetting* m_groundWidget;
    class LevelEditorSurfaceSetting* m_surfaceWidget;
};

//可放置元素，场景元素，植物，地形元素
class LevelEditorCardItem : public Widget
{
public:
    LevelEditorCardItem();
    ~LevelEditorCardItem();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetData(const LevelEditorCardInfo& i_data);
    LevelEditorCardInfo GetData() { return m_data; }
    void SetClickFunction(std::function<void(const LevelEditorCardInfo&)> i_func) { m_clickFunction = i_func; };

protected:
    int m_touchId;
    LevelEditorCardInfo m_data;
    Sexy::DeviceImage* m_seedPacketImage;
    std::function<void(const LevelEditorCardInfo&)> m_clickFunction;
};

class LevelEditorCardPlantInterface
{
public:
    LevelEditorCardPlantInterface()
    :m_rare(0)
    {

    }
    
    void SetRare(int i_rare){ m_rare = i_rare; };
    int GetRare(){ return m_rare; }
private:
    int m_rare;
};

class LevelEditorCardPlant : public LevelEditorCardItem, public LevelEditorCardPlantInterface
{

};

class LevelEditorPlantRare : public Widget
{
public:
    LevelEditorPlantRare();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    int GetRare(){ return m_rare; }
    void SetRare(int i_rare){ m_rare = i_rare; }
    bool IsSelected(){ return m_selected; }
    void SetSelected(bool i_selected){ m_selected = i_selected; }
    void SetCallBack(std::function<void()> i_func){ m_callBack = i_func; }
private:
    bool m_selected;
    int m_touchId;
    int m_rare;
    std::function<void()> m_callBack;
};

class LevelEditorGroundSetting : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    LevelEditorGroundSetting();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init(int i_row, int i_column, std::function<void(const LevelEditorCardInfo&)> i_cardfunc);
    void TriggerTutorial();
    
private:
    int m_row;
    int m_column;
    class PVZ2UIButton* m_senceButton;
    class PVZ2UIButton* m_plantButton;
    class Widget* m_sences;
    class Widget* m_plants;
    std::vector<LevelEditorCardPlant*> m_cardList;
    std::vector<LevelEditorPlantRare*> m_rareList;
    class LevelEditorCardItem* m_tutorialCard;
};

class LevelEditorSurfaceSetting : public Widget,  public Sexy::ScrollWidgetListener
{
public:
    LevelEditorSurfaceSetting();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init(std::function<void(const LevelEditorCardInfo&)> i_cardfunc);
};

//关卡名称显示和设置
class LevelEditorLevelName : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    void Init();
    virtual void Reload();
private:
    SexyString m_levelName;
};

//设置初始阳光
class LevelEditorStartingSunMoney : public Widget, public ButtonListener
{
public:
    LevelEditorStartingSunMoney();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init();
    virtual void Reload();
    void SetValue(int i_value);
    virtual void DealData();
protected:
    int m_sunMoneyValue;
};

//Tower Defend Start SunMoney
class LevelEditorTowerDefendStartingSunMoney : public LevelEditorStartingSunMoney
{
public:
	LevelEditorTowerDefendStartingSunMoney();

    virtual void Reload() override;
    virtual void DealData() override;
};

//设置初始能量豆
class LevelEditorStartingPlantfood : public Widget, public ButtonListener
{
public:
    LevelEditorStartingPlantfood();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void Init();
    virtual void Reload();
    virtual void SetValue(int i_value);

protected:
    int m_plantfoodValue;
};

//塔防模式下的普通能量豆
class LevelEditorTowerDefendStartingPlantfood : public LevelEditorStartingPlantfood
{
public:
	LevelEditorTowerDefendStartingPlantfood();

    void Reload() override;
    void SetValue(int i_value) override;
};

//左侧普通植物卡片选择集合
class LevelEditorNormalSeedBank : public Widget, public ButtonListener
{
public:
    LevelEditorNormalSeedBank();
    virtual ~LevelEditorNormalSeedBank();
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void Reload();
    void onGlobalLevelChange(int i_level);
private:
    void OnTutorialCreated();

    std::vector<class LevelEditorNormalSeedPacket*> m_normalSeedPackets;
};
//僵尸迷阵右边框
class LevelEditorStatueMazeRotationWidget : public Widget, public ButtonListener, public SliderListener
{
public:
	LevelEditorStatueMazeRotationWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void SliderVal(int theId, double theVal) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int wave);
    void SetTitle(const SexyString& i_title) {m_title = i_title;}

    void Reload();
    void SetDescription(const SexyString& i_description) {m_description = i_description;}
    void SetDescription1(const SexyString& i_description) {m_description1 = i_description;}

    void SetSliderValue(int i_value) {m_sliderValue = i_value;}
	void SetMaxSliderValue(int i_value) {m_maxValue = i_value;}
	void SetSliderValue1(int i_value) {m_sliderValue1 = i_value;}
	void SetMaxSliderValue1(int i_value) {m_maxValue1 = i_value;}

    void SetConfirmCallBack(std::function<void(int,int,int)> i_confirmCallback) {m_confirmCallback = i_confirmCallback;}
    void SetConfirmCallBack1(std::function<void(int,bool)> i_confirmCallback) {m_confirmCallback1 = i_confirmCallback;}
    void SetConfirmCallBack2(std::function<void(int,int,bool)> i_confirmCallback) {m_confirmCallback2 = i_confirmCallback;}

    int focues_wave = 0;
    std::vector<StatueDirection*> m_direction;

    std::vector<PVZ2UIButton*> Button_Group;
    std::vector<PVZ2UIButton*> Button_Group1;
    std::vector<PVZ2UIButton*> Button_Group2;

private:
    int m_wave;

    int m_maxValue;
	int m_sliderValue;
	int m_maxValue1;
	int m_sliderValue1;

    SexyString m_title;
    SexyString m_description;
    SexyString m_description1;

    std::function<void(int,int,int)> m_confirmCallback;
    std::function<void(int,bool)> m_confirmCallback1;
    std::function<void(int,int,bool)> m_confirmCallback2;

    Sexy::Slider* m_sliderWidget;
    Sexy::Slider* m_sliderWidget1;
};


//僵尸迷阵波次滑动条
class LevelEditorStatueMazeSliderWidget : public Widget, public ButtonListener, public SliderListener
{
public:
	LevelEditorStatueMazeSliderWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void SliderVal(int theId, double theVal) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int wave);
    void SetTitle(const SexyString& i_title) {m_title = i_title;}

    void SetDescription(const SexyString& i_description) {m_description = i_description;}
    void SetDescription1(const SexyString& i_description) {m_description1 = i_description;}
    void SetDescription2(const SexyString& i_description) {m_description2 = i_description;}
    void SetDescription3(const SexyString& i_description) {m_description3 = i_description;}
    void SetDescription4(const SexyString& i_description) {m_description4 = i_description;}
    void SetDescription5(const SexyString& i_description) {m_description5 = i_description;}
    void SetDescription6(const SexyString& i_description) {m_description6 = i_description;}

    void SetSliderValue(int i_value) {m_sliderValue = i_value;}
	void SetMaxSliderValue(int i_value) {m_maxValue = i_value;}
    void SetSliderValue1(int i_value) {m_sliderValue1 = i_value;}
	void SetMaxSliderValue1(int i_value) {m_maxValue1 = i_value;}
    void SetSliderValue2(int i_value) {m_sliderValue2 = i_value;}
	void SetMaxSliderValue2(int i_value) {m_maxValue2 = i_value;}
    void SetSliderValue3(int i_value) {m_sliderValue3 = i_value;}
	void SetMaxSliderValue3(int i_value) {m_maxValue3 = i_value;}
    void SetSliderValue4(int i_value) {m_sliderValue4 = i_value;}
	void SetMaxSliderValue4(int i_value) {m_maxValue4 = i_value;}
    void SetSliderValue5(int i_value) {m_sliderValue5 = i_value;}
	void SetMaxSliderValue5(int i_value) {m_maxValue5 = i_value;}
    void SetSliderValue6(int i_value) {m_sliderValue6 = i_value;}
	void SetMaxSliderValue6(int i_value) {m_maxValue6 = i_value;}

    void SetConfirmCallBack(std::function<void(int,int,int,int,int,int,int,int)> i_confirmCallback) {m_confirmCallback = i_confirmCallback;}
    void SetConfirmCallBack1(std::function<void(int)> i_confirmCallback) {m_confirmCallback1 = i_confirmCallback;}

private:
    int m_wave;
    int m_maxValue;
    int m_sliderValue;
    int m_maxValue1;
	int m_sliderValue1;
    int m_maxValue2;
	int m_sliderValue2;
    int m_maxValue3;
	int m_sliderValue3;
    int m_maxValue4;
	int m_sliderValue4;
    int m_maxValue5;
	int m_sliderValue5;
    int m_maxValue6;
	int m_sliderValue6;
    SexyString m_title;
    SexyString m_description;
    SexyString m_description1;
    SexyString m_description2;
    SexyString m_description3;
    SexyString m_description4;
    SexyString m_description5;
    SexyString m_description6;
    Sexy::Slider* m_sliderWidget;
    Sexy::Slider* m_sliderWidget1;
    Sexy::Slider* m_sliderWidget2;
    Sexy::Slider* m_sliderWidget3;
    Sexy::Slider* m_sliderWidget4;
    Sexy::Slider* m_sliderWidget5;
    Sexy::Slider* m_sliderWidget6;
    std::function<void(int,int,int,int,int,int,int,int)> m_confirmCallback;
    std::function<void(int)> m_confirmCallback1;
};


//僵尸迷阵波次选择
class LevelEditorStatueMazeWave: public Widget, public ButtonListener
{
public:
	LevelEditorStatueMazeWave();
    virtual void ButtonDepress(int i_id) override;

    void Init(std::vector<StatueMazeData*>  i_all_StatueMazeData);
    void Reload();
    void SetConfirmCallBack(std::function<void(int,int)> i_confirmCallback) {m_confirmCallback = i_confirmCallback;}

    int focues_wave = 0;
    std::vector<PVZ2UIButton*> Button_Group;
    std::vector<PVZ2UIButton*> Button_Group1;
    std::vector<PVZ2UIButton*> Button_Group2;
    std::vector<StatueMazeData*> all_StatueMazeData;
    std::function<void(int,int)> m_confirmCallback;
};

//僵尸迷阵单次波次点击

class LevelEditorSingleMazeWave : public Widget
{
public:
	LevelEditorSingleMazeWave();
    ~LevelEditorSingleMazeWave();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void Init(int i_index);
    void Reload();
    void SetTypeName(const std::string& i_typename);

private:
    int m_index;
    int m_touchId;
    std::string m_typeName;
    Sexy::DeviceImage* m_seedPacketImage;
};


//左侧传送带植物卡片选择集合
class LevelEditorConveyorSeedBank : public Widget
{
public:
    LevelEditorConveyorSeedBank();

    void Init();
    void Reload();
    void onGlobalLevelChange(int i_level);
private:
    std::vector<class LevelEditorConveyorSeedPacket*> m_conveyorSeedPackets;
};

//禁用植物 卡片
class LevelEditorDiableCardItem : public LevelEditorCardItem, public LevelEditorCardPlantInterface
{
public:
    LevelEditorDiableCardItem()
    :m_clicked(false),
    m_bindWidget(nullptr)
    {

    }

    void SetClicked(bool i_flag) { m_clicked = i_flag; }
    bool GetClicked() { return m_clicked; }
    void SetBindWidget(LevelEditorDiableCardItem* i_bindWidget) { m_bindWidget = i_bindWidget; }
    LevelEditorDiableCardItem* GetBindWidget() { return m_bindWidget; }

protected:
    bool m_clicked;
    LevelEditorDiableCardItem* m_bindWidget;
};

//禁用植物
class LevelEditorDisablePlant : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	virtual ~LevelEditorDisablePlant();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init();
    void Reload();

    void DisablePlant(const std::string& i_typename);
    void EnablePlant(const std::string& i_typename);

private:
    Widget* m_disableWidget;
    class PVZ2UIScrollingWidget* m_disableScrollWidget;
    Widget* m_selectWidget;
    std::vector<LevelEditorDiableCardItem* > m_disableVec;
    std::vector<LevelEditorDiableCardItem* > m_selectVec;
    std::vector<LevelEditorPlantRare*> m_rareList;
};

//左侧植物卡片
class LevelEditorSeedPacket : public Widget
{
public:
    LevelEditorSeedPacket();
    ~LevelEditorSeedPacket();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    
    void Init(int i_index);
    virtual void Reload();
    void ChangeCardInfo(const LevelEditorCardInfo& i_cardInfo);
    void ClearCardInfo();
    void ChangeLevel(int i_level);

    virtual void onChangeCardInfo(){}
    virtual void onChangeLevel(){}

    void SetSelected(bool i_selected) { m_selected = i_selected; }
    bool GetSelected() { return m_selected; }

    LevelEditorCardInfo GetCardInfo() { return m_cardInfo; }

protected:
    int m_index;
    int m_level;
    int m_touchId;
    bool m_selected;
    LevelEditorCardInfo m_cardInfo;
    Sexy::DeviceImage* m_seedPacketImage;
};

//左侧植物卡片-普通
class LevelEditorNormalSeedPacket : public LevelEditorSeedPacket
{
public:
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    virtual void Reload() override;
    virtual void onChangeCardInfo() override;
    virtual void onChangeLevel() override;

public:
    void SetChangeGlobalLevelCallback(std::function<void(int)> i_callback){ m_callback = i_callback; }
private:
    std::function<void(int)> m_callback;
};

//左侧植物卡片-传送带
class LevelEditorConveyorSeedPacket : public LevelEditorSeedPacket
{
public:
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    virtual void Reload() override;
    virtual void onChangeCardInfo() override;
    virtual void onChangeLevel() override;
    void SetWeight(int i_weigth);
public:
    void SetChangeGlobalLevelCallback(std::function<void(int)> i_callback){ m_callback = i_callback; }
private:
    int m_weight;
    std::function<void(int)> m_callback;    
};

//植物选择界面
class LevelEditorSeedChooser : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init(std::function<void(const LevelEditorCardInfo&)> i_func);
    void Reload();
    void SetLevel(int i_level);
    void ConfirmSetting(class UIMessageBox* box, int buttonID);
    void SetChangeGlobalLevelCallback(std::function<void(int)> i_callback){ m_callback = i_callback; }
    void TriggerTutorial();
    void DisableCard(const LevelEditorCardInfo& i_info);
private:
    int m_level;
    class PVZ2UIButton* m_subtract;
    class PVZ2UIButton* m_add;
    std::vector<LevelEditorCardPlant*> m_cardList;
    std::vector<LevelEditorPlantRare*> m_rareList;
    std::function<void(int)> m_callback;
};

// Challenges

//左侧普通植物卡片选择集合
class LevelEditorEvilDaveStartingSunMoney : public LevelEditorStartingSunMoney
{
public:
	LevelEditorEvilDaveStartingSunMoney();
	void DealData() override;
	void Reload() override;
};

class LevelEditorDistanceSetting : public Widget, public ButtonListener
{
public:
	LevelEditorDistanceSetting();
	virtual ~LevelEditorDistanceSetting();
    virtual void Draw(Sexy::Graphics* i_g) override;
    void ButtonDepress(int i_id) override;

    void Init();
    void Reload();

private:
    Rect m_mainBGRect;
	Rect m_grayBGRect;
	Rect m_modifyBtnRectL;
	Rect m_modifyBtnRectR;
	Rect m_confirmBtnRect;
	Rect m_titleTxtRect;
	Rect m_valueTxtRect;
	Rect m_boxRect;

	class PVZ2UIButton* m_startSubtractBtn;
	class PVZ2UIButton* m_startAddBtn;
	class PVZ2UIButton* m_confirmBtn;
	int m_startValue;
};

class LevelEditorEvilDaveSeedBank : public Widget, public ButtonListener
{
public:
	LevelEditorEvilDaveSeedBank();
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void Reload();
    void AddTypeName(const std::string& i_typeName);
    void RemoveTypeName(const std::string& i_typeName);

    std::vector<std::string> m_existTypeNames;
};

//左侧植物卡片-普通
class LevelEditorEvilDaveSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorEvilDaveSeedPacket(LevelEditorEvilDaveSeedBank* i_bank);

    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void Reload() override;

    void Draw(Sexy::Graphics* i_g) override;

    virtual void onChangeCardInfo() override;

private:
    bool CanSetTypeName(const std::string& i_typeName);

    LevelEditorEvilDaveSeedBank* m_seedBank;
};

//植物选择界面
class LevelEditorEvilDaveSeedChooser : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init(std::function<void(const LevelEditorCardInfo&)> i_func);
    void Reload();
private:
    std::vector<LevelEditorCardItem*> m_cardList;
    Rect m_mainBGRect;
    Rect m_grayBGRect;
    Rect m_containerRect;
    Rect m_scrollViewRect;
};

//场景格子
class LevelEditorEvilDaveBoardGrid : public LevelEditorBoardGrid
{
public:
	LevelEditorEvilDaveBoardGrid(int i_row, int i_column);
    ~LevelEditorEvilDaveBoardGrid();

    void TouchEnded(const Sexy::Touch& i_touch) override;
    void SetData(const LevelEditorCardInfo& i_data) override;
    void ClearData() override;
    void Reload() override;
};

//////////////////////////////////////
/// LevelEditorSingleHandedSeedBank
//////////////////////////////////////
class LevelEditorSingleHandedSeedBank : public Widget, public ButtonListener
{
public:
	LevelEditorSingleHandedSeedBank();
	virtual ~LevelEditorSingleHandedSeedBank();

    virtual void Init();
    virtual void Reload();

    virtual bool CheckValidPlant(std::string name);
    virtual void AddPlant(std::string name, int i_index);
    virtual void RemovePlant(std::string name, int i_index);
    void OnRemoved(int i_index);

protected:
    std::vector<std::string> m_existPlantsNames;
    std::vector<class LevelEditorSingleHandedSeedPacket*> m_packets;
};

//////////////////////////////////////
/// LevelEditorSingleHandedSeedPacket
//////////////////////////////////////
class LevelEditorSingleHandedSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorSingleHandedSeedPacket(LevelEditorSingleHandedSeedBank* i_bank);
	virtual ~LevelEditorSingleHandedSeedPacket();

    void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;
    void Reload() override;
    void onChangeCardInfo() override;

    void onClearCardInfo();

    void SetDisabled(bool i_disabled) { m_disalbed = i_disabled; }
    bool IsDisabled() { return m_disalbed; }

    const LevelEditorCardInfo& GetCardInfo() { return m_cardInfo; }

    void ManualReload();

protected:
    void AddUpgradePlant(int index, std::string srcName, std::string typeName, int cost);

protected:
    LevelEditorSingleHandedSeedBank* m_seedBank;
    bool m_disalbed;
};

//////////////////////////////////////////////
/// LevelEditorSingleHandedLevelUpSeedPacket
//////////////////////////////////////////////
class LevelEditorSingleHandedLevelUpSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorSingleHandedLevelUpSeedPacket();
	virtual ~LevelEditorSingleHandedLevelUpSeedPacket();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;

    std::string GetCardTypeName() const { return m_cardInfo.TypeName; }

    void SetFunc(std::function<void(const LevelEditorCardInfo&)> i_cardfunc) { m_Function = i_cardfunc; };

    void onChangeCardInfo() override;

    const LevelEditorCardInfo& GetCardInfo() {return m_cardInfo; }

private:
    std::function<void(const LevelEditorCardInfo&)> m_Function;
};





//////////////////////////////////////
/// LevelEditorTowerDefendSeedBank
//////////////////////////////////////
class LevelEditorTowerDefendSeedBank : public Widget, public ButtonListener
{
public:
	LevelEditorTowerDefendSeedBank();
	virtual ~LevelEditorTowerDefendSeedBank();

    virtual void Init();
    virtual void Reload();

    virtual bool CheckValidPlant(std::string name);
    virtual void AddPlant(std::string name);
    virtual void RemovePlant(std::string name);

protected:
    std::vector<std::string> m_existPlantsNames;
};

//////////////////////////////////////
/// LevelEditorTowerDefendSeedPacket
//////////////////////////////////////
class LevelEditorTowerDefendSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorTowerDefendSeedPacket(LevelEditorTowerDefendSeedBank* i_bank);
	virtual ~LevelEditorTowerDefendSeedPacket();

    void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;
    void Reload() override;
    void onChangeCardInfo() override;

    void onClearCardInfo();

protected:
    void AddUpgradeTree(int index, std::string typeName, int cost);

protected:
    LevelEditorTowerDefendSeedBank* m_seedBank;
};

//////////////////////////////////////////////
/// LevelEditorTowerDefendLevelUpSeedPacket
//////////////////////////////////////////////
class LevelEditorTowerDefendLevelUpSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorTowerDefendLevelUpSeedPacket();
	virtual ~LevelEditorTowerDefendLevelUpSeedPacket();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;

    std::string GetCardTypeName() const { return m_cardInfo.TypeName; }
};

/////////////////////////////////////////
/// LevelEditorTowerDefendBoardGrid
/////////////////////////////////////////
class LevelEditoTowerDefendBoardGrid : public LevelEditorBoardGrid
{
public:
	LevelEditoTowerDefendBoardGrid(int i_row, int i_column);
    ~LevelEditoTowerDefendBoardGrid();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void Reload() override;
    virtual void ClearData() override;
    virtual void SetData(const LevelEditorCardInfo& i_data) override;

    void SetClickEnable(bool enable) { m_enableClick = enable; }

protected:
    bool m_enableClick;// check if this board grid can be clicked.
    Image* m_gridBg;
};

//////////////////////////////////////////
/// LevelEditorTowerDefendRoadSetting
//////////////////////////////////////////
class LevelEditorTowerDefendRoadSetting : public Widget
{
public:
	LevelEditorTowerDefendRoadSetting();
	virtual ~LevelEditorTowerDefendRoadSetting();

    virtual void Draw(Sexy::Graphics* i_g) override;

    void Init(std::function<void(const LevelEditorCardInfo&)> i_cardfunc);

protected:
    SexyString m_title;
};

////////////////////////////////
/// LevelEditorTowerDefendRoad
////////////////////////////////
class LevelEditorTowerDefendRoad : public Widget
{
public:
	LevelEditorTowerDefendRoad();
	virtual ~LevelEditorTowerDefendRoad();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void Init(int index);

    void SetClickFunction(std::function<void(const LevelEditorCardInfo&)> func) { m_clickFunction = func; }

protected:
    int m_index;
    int m_touchId;
    Image* m_roadImage;
    LevelEditorCardInfo m_data;
    std::function<void(const LevelEditorCardInfo&)> m_clickFunction;
};

//////////////////////////////////
/// LevelEditorPlantSetting
//////////////////////////////////
class LevelEditorPlantSetting : public Widget, public Sexy::ScrollWidgetListener
{
public:
	LevelEditorPlantSetting();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void Init(std::function<void(const LevelEditorCardInfo&)> i_cardfunc);

    virtual void GatherOtherBlackList(std::vector<std::string>& i_list) {}

private:
    class Widget* m_plants;
    std::vector<LevelEditorCardPlant*> m_cardList;
    std::vector<LevelEditorPlantRare*> m_rareList;
    Rect m_mainBGRect;
	Rect m_grayBGRect;
	Rect m_containerRect;
	Rect m_scrollViewRect;
};

//////////////////////////////////////
/// LevelEditorSingleHandedPlantSetting
//////////////////////////////////////
class LevelEditorSingleHandedPlantSetting : public LevelEditorPlantSetting
{
public:
    void GatherOtherBlackList(std::vector<std::string>& i_list) override;
};

#endif
