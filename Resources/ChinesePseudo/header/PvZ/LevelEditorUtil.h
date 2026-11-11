#ifndef LEVEL_EDITOR_UTIL_H
#define LEVEL_EDITOR_UTIL_H

#include "image.h"
#include "Widget.h"
#include "functional"
#include "LevelEditorDefine.h"
#include "Slider.h"
#include "SliderListener.h"
#include "LevelEditorBoardModule.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "EditListener.h"

/*--------------------------宏--------------------------------------*/

#define __TOUCH_CLOSE__ \
public:\
    virtual void TouchBegan(const Sexy::Touch& i_touch) override { m_touchID = (int)i_touch.ident;}\
    virtual void TouchEnded(const Sexy::Touch& i_touch) override { if(m_touchID == (int)i_touch.ident) { LevelEditorUtil::CloseDialog(this);} }\
private:\
    int m_touchID;\
public:\

class TouchCloseContainer;
class LevelEditorWorldSelect;
/*---------------------关卡编辑器工具------------------------------*/

namespace LevelEditorUtil
{
    void ShowDialog(Widget* i_widget);
    void CloseDialog(Widget* i_widget);
    Sexy::Image* GetStageLeftImage(const std::string& i_stage);
    Sexy::Image* GetStageCenterImage(const std::string& i_stage);
    Sexy::Image* GetStageRightImage(const std::string& i_stage);

    TouchCloseContainer* ShowDialogWithTouchClose(Widget* i_widget);
    std::vector<std::string> GetZombieListByStage(const std::string& i_stage);
    LevelEditorWorldSelect* ShowSelectWorldWidget(const std::vector<std::string>& i_stageList);
}

/*---------------------关卡编辑器 可复用工具界面------------------------------*/

//点击关闭
class TouchCloseContainer : public Widget
{
public:
    TouchCloseContainer();
    virtual ~TouchCloseContainer();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
public:
    void SetCallFunctionBeforeClose(std::function<void()> i_beforeCall) { m_beforeClose = i_beforeCall; }
    void SetTutorialStage(int i_stage) { m_tutorialStage = i_stage; }

private:
    int m_touchId;
    int m_tutorialStage;
    std::function<void()> m_beforeClose;
};

//
class LevelEditorMultifunctionAssembly : public Widget, public ButtonListener
{
public:
    LevelEditorMultifunctionAssembly();
    virtual ~LevelEditorMultifunctionAssembly();
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void ButtonDepress(int i_id) override;

    class PVZ2UIButton* AttachButton(int i_id, Rect i_absRect, std::function<void()> i_call, const std::string& i_name = "");
    class PVZ2UIButton* AttachButton(class PVZ2UIButton* i_button, std::function<void()> i_call);

    void TriggerTutorial();

private:
    int m_touchId;
    std::map<int, std::function<void()>> m_assembly;
    class PVZ2UIButton* m_tutorialBtn;
};

//board 世界切换，废弃
class LevelEditorBoardStageList : public Widget, public ButtonListener
{
public:
    LevelEditorBoardStageList();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(const std::vector<std::string>& i_stageList);
    void SetPageIndex(int i_index);
    int GetMaxPageIndex();

    void SetOnSelectStage(std::function<void(const std::string&)> i_stageSelect){ m_stageSelect = i_stageSelect;}

private:
    int m_pageIndex;
    class PVZ2UIButton* m_leftButton;
    class PVZ2UIButton* m_rightButton;
    std::vector<class PVZ2UIButton*> m_stageButtonList;
    std::function<void(const std::string&)> m_stageSelect;
};

//僵尸世界切换,废弃
class LevelEditorZombieStageList : public Widget, public ButtonListener
{
public:
    LevelEditorZombieStageList();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(const std::vector<std::string>& i_stageList);
    void SetPageIndex(int i_index);
    int GetMaxPageIndex();

    void SetOnSelectStage(std::function<void(const std::string&)> i_stageSelect){ m_stageSelect = i_stageSelect;}

private:
    int m_pageIndex;
    class PVZ2UIButton* m_leftButton;
    class PVZ2UIButton* m_rightButton;
    std::vector<class PVZ2UIButton*> m_stageButtonList;
    std::function<void(const std::string&)> m_stageSelect;
};

class LevelEditorWorldCard : public Sexy::Widget
{
public:
    LevelEditorWorldCard();
    ~LevelEditorWorldCard();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void Init(class LevelEditorWorldSelect* i_select, const std::string& i_stage);

public:
    bool m_picking;
    std::string m_stage;
private:
    int m_touchId;
    Sexy::Image* m_targetImg;
    class LevelEditorWorldSelect* m_worldSelect;
};

class LevelEditorWorldSelect : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    LevelEditorWorldSelect();
    ~LevelEditorWorldSelect();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached(Sexy::ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* scrollWidget) override {}
    void SetOnSelectStage(std::function<void(const std::string&)> i_stageSelect){ m_stageSelect = i_stageSelect;}

    void Init(const std::vector<std::string>& i_stageList);
    void SetSelectStage(const std::string& i_stage);
private:
    std::string m_currentStage;
    std::function<void(const std::string&)> m_stageSelect;
    std::vector<LevelEditorWorldCard*> m_cardList;
};


//名称编辑
class LevelEditorLevelNameEditor : public Sexy::Widget, public ButtonListener, public Sexy::EditListener
{
public:
    LevelEditorLevelNameEditor();
    ~LevelEditorLevelNameEditor();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void EditWidgetText(int theId, const SexyString& theString) override;

    void Init();
    void SetOnConfirmText(std::function<void(const std::string&)> i_func) { m_confirm = i_func; }
    bool CheckNameFilter();

private:
    class EditWidget* m_editWidget;
    std::function<void(const std::string&)> m_confirm;
};


//僵尸接受器
class LevelEditorZombieCursorSlot : public Widget
{
    RT_CLASS_DEFINE(LevelEditorZombieCursorSlot, Widget, RtClass);

    virtual void OnSlotAccept(const Sexy::Point& i_absPoint, const std::string& i_typeName) {};
};

//阶数设置 [ 减号 数值 加号 ]
class LevelEditorLevelSetting : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void SetRange(int i_min, int i_max);
    void SetValue(int i_value);
    void SetTitle(SexyString i_title);
    void SetConfirmCallBack(std::function<void(int)> i_func);

private:
    int m_min;
    int m_max;
    int m_currentValue;
    SexyString m_title;

    class PVZ2UIButton* m_subtractBtn;
    class PVZ2UIButton* m_addBtn;
    class PVZ2UIButton* m_confirmButton;
    std::function<void(int)> m_confirmFunc;
};

//radio button
class LevelEditorRadioButton : public Widget
{
public:
    LevelEditorRadioButton();
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override; 
    virtual void Draw(Sexy::Graphics* i_g) override;

    bool GetRadioState(){return m_radio;}
    void SetSwitchRadioFunc(std::function<void(bool)> i_func){ m_switchRadio = i_func; }
private:
    int m_touchId;
    bool m_radio;
    std::function<void(bool)> m_switchRadio;
};

//初始阳光编辑
class LevelEditorSunMoneyEditor : public Sexy::Widget, public ButtonListener, public Sexy::EditListener
{
public:
	LevelEditorSunMoneyEditor();
    ~LevelEditorSunMoneyEditor();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void EditWidgetText(int theId, const SexyString& theString) override;

    void Init();
    void SetOnConfirmText(std::function<void(const std::string&)> i_func) { m_confirm = i_func; }
    bool CheckMoneyFormat();
    void SetMaxSunMoney(int i_maxSunMoney) { m_maxSunMoney = i_maxSunMoney; }
    void SetCurrentSunMoney(int i_currentMoney) { m_currentSunMoney = i_currentMoney; }
    
private:
    class EditWidget* m_editWidget;
    std::function<void(const std::string&)> m_confirm;
    int m_maxSunMoney;
    int m_currentSunMoney;
};

//滑动条
class LevelEditorSliderWidget : public Widget, public ButtonListener, public SliderListener
{
public:
    LevelEditorSliderWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void SliderVal(int theId, double theVal) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void Init();

    void SetTitle(const SexyString& i_title) {m_title = i_title;}
    void SetDescription(const SexyString& i_description) {m_description = i_description;}
    void SetSliderValue(int i_value) {m_sliderValue = i_value;}
    void SetMinSliderValue(int i_value) {m_minValue = i_value;}
    void SetMaxSliderValue(int i_value) {m_maxValue = i_value;}
    int GetMinSliderValue() { return m_minValue; }
    int GetMaxSliderValue() { return m_maxValue; }
    void SetConfirmCallBack(std::function<void(int)> i_confirmCallback) {m_confirmCallback = i_confirmCallback;}
    
protected:
    int m_minValue;
    int m_maxValue;
    int m_sliderValue;
    SexyString m_title;
    SexyString m_description;
    std::function<void(int)> m_confirmCallback;
    Sexy::Slider* m_sliderWidget;
    PVZ2UIButton* m_editorButton;
};

/////////////////////////////////////////
/// LevelEditorTowerDefendSliderWidget
/////////////////////////////////////////
class LevelEditorTowerDefendSliderWidget : public LevelEditorSliderWidget
{
public:
    LevelEditorTowerDefendSliderWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Init() override;
	virtual void SliderVal(int theId, double theVal) override;

    void SetFunc(std::function<void(int, std::string)> func) {m_func = func;}
    void SetLevelUpData(std::string plantName, int cost);

protected:
    std::string m_plantTypeName;
    SexyString m_levelupTitle;
    std::function<void(int, std::string)> m_func; 
    class LevelEditorTowerDefendLevelUpSeedPacket* m_levelUpPlantBtn;
};

/////////////////////////////////////////
/// LevelEditorSingleHandedSliderWidget
/////////////////////////////////////////
class LevelEditorSingleHandedSliderWidget : public LevelEditorSliderWidget
{
public:
	LevelEditorSingleHandedSliderWidget(class LevelEditorSingleHandedSeedPacket* i_packet);

	virtual ~LevelEditorSingleHandedSliderWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Init() override;
	virtual void SliderVal(int theId, double theVal) override;

    void SetFunc(std::function<void(int, std::string)> func) {m_func = func;}
    void SetLevelUpData(std::string plantName, int killNum);

protected:
    std::string m_plantTypeName;
    SexyString m_levelupTitle;
    std::function<void(int, std::string)> m_func;
    class LevelEditorSingleHandedLevelUpSeedPacket* m_levelUpPlantBtn;
    class LevelEditorSingleHandedSeedPacket* m_packet;
    PVZ2UIButton* m_confirmButton;
};


/*---------------------关卡编辑器 消息------------------------------*/

namespace Message
{
    void BoardStageChange(const std::string& i_stage);
    void ChangeSeedBankGlobalLevel(int i_level);
}

#endif
