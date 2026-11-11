#ifndef LEVELEDITOR_ZOMBIEMOUDLE_H
#define LEVELEDITOR_ZOMBIEMOUDLE_H

#include "Widget.h"
#include "ButtonListener.h"
#include "LevelEditorDefine.h"
#include "LevelEditorConfig.h"
#include "LevelEditorUtil.h"

//上方僵尸选择列表
class LevelEditorZombieSelectList : public Widget, public ButtonListener
{
public:
    LevelEditorZombieSelectList();
    virtual ~LevelEditorZombieSelectList();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void Init();
    virtual void OnSelectStage(const std::string& i_stage);
    virtual void SetCurrentPage(int i_page);

    void TriggerTutorial();
    void TriggerWaveEventTutorial();

protected:
    virtual void RefreshZombiesByPage();

protected:
    int m_minPage;
    int m_maxPage;
    int m_currentPage;
    RtWeakPtr<LevelEditorStageInfo> m_currentStagePtr;
    class Widget* m_zombieList;
    class PVZ2UIButton* m_zombieStageBtn;
    class PVZ2UIButton* m_leftBtn;
    class PVZ2UIButton* m_rightBtn;
    class LevelEditorZombieDraggable* m_tutorialDraggable;
};

//////////////////////////////////////////////
/// LevelEditorTowerDefendZombieSelectList
//////////////////////////////////////////////
class LevelEditorTowerDefendZombieSelectList : public LevelEditorZombieSelectList
{
public:
	LevelEditorTowerDefendZombieSelectList();

	void Init() override;

protected:
    virtual void RefreshZombiesByPage() override;

	void InitZombieList();
};

//////////////////////////////////////////////
/// LevelEditorSingleHandedZombieSelectList
//////////////////////////////////////////////
class LevelEditorSingleHandedZombieSelectList : public LevelEditorZombieSelectList
{
public:
	LevelEditorSingleHandedZombieSelectList();

	void Init() override;
};

//僵尸选择列表中的元素
class LevelEditorZombieDraggable : public Widget
{
public:
    LevelEditorZombieDraggable();
    ~LevelEditorZombieDraggable();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchMoved(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void TouchesCanceled() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
    void SetTutorialStage(int i_stage) { m_tutorialStage = i_stage; }
    void Init(const std::string& i_zombieName);

    Sexy::Image* m_almanacZombieImg;
    Sexy::DeviceImage* m_seedPacketImage;
    std::string m_zombieTypeName;

protected:
    bool m_cursorEnable;
    Sexy::Point m_cursorPoint;
    int m_tutorialStage;
};

//僵尸编辑
class LevelEditorZombieWaveEditor : public Widget, public ButtonListener
{
public:
    LevelEditorZombieWaveEditor();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void Init();
    void ChangeCurrentPage(int i_index);
    int GetMaxPageIndex();

protected:
    int m_pageIndex;
    class PVZ2UIButton* m_leftButton;
    class PVZ2UIButton* m_rightButton;
    std::vector<class LevelEditorWaveDisplay*> m_waveVector;
};

///////////////////////////////
/// Tower Defend Wave Editor
///////////////////////////////
class LevelEditorTowerDefendZombieWaveEditor : public LevelEditorZombieWaveEditor
{
public:
	LevelEditorTowerDefendZombieWaveEditor();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Init() override;
};

///////////////////////////////
/// Single Handed Wave Editor
///////////////////////////////
class LevelEditorSingleHandedZombieWaveEditor : public LevelEditorZombieWaveEditor
{
public:
	LevelEditorSingleHandedZombieWaveEditor();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Init() override;
};

//僵尸波数展示
class LevelEditorWaveDisplay : public Widget, public ButtonListener
{
public:
    LevelEditorWaveDisplay();
    virtual ~LevelEditorWaveDisplay();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void Init(int i_waveIndex);
    virtual void Reload();
    virtual void SetPlantfoodStateData(bool i_hasPlantfood);
    void SetPlantfoodState(bool i_hasPlantfood);

protected:
    int m_touchId;
    int m_waveIndex;
    bool m_hasPlantfood;
    int m_zombieNums[5];
    class PVZ2UIButton* m_plantfoodButton;
    Sexy::DeviceImage* m_zombieIcon;
    class LevelEditorWaveEvent* m_event;
    SexyString m_title;

private:
    void OnTutorialCreated();
    void OnDragFinished();
    void OnContainerFinished();
    void OnEditorClosed();

    class TouchCloseContainer* m_tutorialContainer;
};

///////////////////////////////
/// Tower Defend Wave Display
///////////////////////////////
class LevelEditorTowerDefendWaveDisplay : public LevelEditorWaveDisplay
{
public:
	LevelEditorTowerDefendWaveDisplay();

    virtual void Init(int i_waveIndex) override;
    virtual void Reload() override;
	virtual void TouchEnded(const Sexy::Touch& i_touch) override;
	virtual void SetPlantfoodStateData(bool i_hasPlantfood) override;
};

///////////////////////////////
/// Single Handed Wave Display
///////////////////////////////
class LevelEditorSingleHandedWaveDisplay : public LevelEditorWaveDisplay
{
public:
	LevelEditorSingleHandedWaveDisplay();

    virtual void Init(int i_waveIndex) override;
    virtual void Reload() override;
	virtual void TouchEnded(const Sexy::Touch& i_touch) override;
	virtual void SetPlantfoodStateData(bool i_hasPlantfood) override;
};

//僵尸波数设置
class LevelEditorWaveZombieSetting : public Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;

    virtual void Init(int i_waveIndex);

protected:
    int m_waveIndex;
};

////////////////////////////////////////
/// Tower Defend Wave Zombie Setting
////////////////////////////////////////
class LevelEditorTowerDefendWaveZombieSetting : public LevelEditorWaveZombieSetting
{
public:
	LevelEditorTowerDefendWaveZombieSetting();

	virtual void Init(int i_waveIndex) override;
};

////////////////////////////////////////
/// Single Handed Wave Zombie Setting
////////////////////////////////////////
class LevelEditorSingleHandedWaveZombieSetting : public LevelEditorWaveZombieSetting
{
public:
	LevelEditorSingleHandedWaveZombieSetting();

	virtual void Init(int i_waveIndex) override;
};

class LevelEditorWaveZombie : public LevelEditorZombieCursorSlot
{
public:
    LevelEditorWaveZombie(int i_row, int i_column);
    virtual ~LevelEditorWaveZombie();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void OnSlotAccept(const Sexy::Point& i_point, const std::string& i_typeName) override;

    virtual void Init(int i_waveIndex);
    virtual void Reload();
    virtual void ChangeZombieType(const std::string& i_typename);

protected:
    int m_touchId;
    int m_row;
    int m_column;
    int m_level;
    int m_waveIndex;
    std::string m_zombieTypeName;
    Sexy::DeviceImage* m_seedPacketImage;

private:
    void OnTutorialCreated();
};


//////////////////////////////
/// Tower Defend Wave Zombie
//////////////////////////////
class LevelEditorTowerDefendWaveZombie : public LevelEditorWaveZombie
{
public:
	LevelEditorTowerDefendWaveZombie(int i_row, int i_column);

    virtual void Reload() override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void OnSlotAccept(const Sexy::Point& i_point, const std::string& i_typeName) override;
};

//////////////////////////////
/// Single Handed Wave Zombie
//////////////////////////////
class LevelEditorSingleHandedWaveZombie : public LevelEditorWaveZombie
{
public:
	LevelEditorSingleHandedWaveZombie(int i_row, int i_column);

    virtual void Reload() override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void OnSlotAccept(const Sexy::Point& i_point, const std::string& i_typeName) override;
};

class LevelEditorWaveEvent : public Widget
{
public:
    LevelEditorWaveEvent();
    virtual ~LevelEditorWaveEvent();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetCurrentEvent(int i_event);
    void Init(int i_waveIndex);
    void Reload();
    void SettingCurrentEvent();
private:
    void OnDragEventFinished();

    int m_waveIndex;
    int m_touchId;
    int m_currentEvent;
    class TouchCloseContainer* m_tutorialContainer;
};

class LevelEditorWaveEventSelect : public Widget, public ButtonListener
{
public:
    LevelEditorWaveEventSelect();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init();
    void SetSelectEvent(std::function<void(int)> i_event);
    void TriggerTutorial();
    
private:
    std::function<void(int)> m_selectEvent;
    class PVZ2UIButton* m_tutorialBtn;

};

class LevelEditorWaveEventStorm : public Widget, public ButtonListener
{
public:
	LevelEditorWaveEventStorm();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();
    void SetTitle(const SexyString& i_title) { m_title = i_title; }

    void ChangeStartColumn(int i_start);
    void ChangeEndColumn(int i_end);
    void UpdateButtonState();
    void TriggerTutorial();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;
    class PVZ2UIButton* m_endSubtractBtn;
    class PVZ2UIButton* m_endAddBtn;

    int m_waveIndex;
    int m_startValue;
    int m_endValue;
    SexyString m_title;
};

class LevelEditorWaveEventStormZombie : public LevelEditorZombieCursorSlot
{
public:
    LevelEditorWaveEventStormZombie();
    ~LevelEditorWaveEventStormZombie();
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void OnSlotAccept(const Sexy::Point& i_point, const std::string& i_typeName) override;

    void Init(int i_waveIndex, int i_zombieIndex);
    void Reload();

private:
    int m_touchId;
    int m_waveIndex;
    int m_zombieIndex;
    std::string m_zombieTypeName;
    Sexy::DeviceImage* m_seedPacketImage;
};

// Spider Rain
class LevelEditorWaveEventSpiderRain : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;
    class PVZ2UIButton* m_endSubtractBtn;
    class PVZ2UIButton* m_endAddBtn;

    int m_waveIndex;
    int m_startValue;
    int m_endValue;
    Rect m_btnLeftRect1;
	Rect m_btnRightRect1;
	Rect m_valueRect1;
	Rect m_btnLeftRect2;
	Rect m_btnRightRect2;
	Rect m_valueRect2;
	Rect m_textRect1;
	Rect m_textRect2;
};

// Raiding Party
class LevelEditorWaveEventRaidingParty : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;

    int m_waveIndex;
    int m_startValue;
    Rect m_btnLeftRect;
    Rect m_btnRightRect;
    Rect m_valueRect;
};

// Parachute Rain
class LevelEditorWaveEventParachuteRain : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;

    int m_waveIndex;
    int m_startValue;
    Rect m_btnLeftRect;
    Rect m_btnRightRect;
    Rect m_valueRect;
};

// Black Hole
class LevelEditorWaveEventBlackHole : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;

    int m_waveIndex;
    int m_startValue;
    Rect m_btnLeftRect;
    Rect m_btnRightRect;
    Rect m_valueRect;
};

// Dino Strike
class LevelEditorWaveEventDinoStrike : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;
    class PVZ2UIButton* m_endSubtractBtn;
    class PVZ2UIButton* m_endAddBtn;

    int m_waveIndex;
    int m_startValue;
    int m_endValue;
    Rect m_btnLeftRect1;
	Rect m_btnRightRect1;
	Rect m_valueRect1;
	Rect m_btnLeftRect2;
	Rect m_btnRightRect2;
	Rect m_valueRect2;
	Rect m_textRect1;
	Rect m_textRect2;
};

// Portal
class LevelEditorWaveEventPortal : public Widget, public ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_waveIndex);
    void Reload();

protected:
    int GetWorldIndex(std::string worldmap);

private:
    class PVZ2UIButton* m_startSubtractBtn;
    class PVZ2UIButton* m_startAddBtn;
    class PVZ2UIButton* m_endSubtractBtn;
    class PVZ2UIButton* m_endAddBtn;
    class PVZ2UIButton* m_worldSelectBtn;

    int m_waveIndex;
    int m_startValue;
    int m_endValue;
    int m_worldValue;
    std::string m_worldName;
    std::vector<SexyString> m_worldNameList;
    std::vector<Image*> m_worldImageList;

    Rect m_btnLeftRect1;
	Rect m_btnRightRect1;
	Rect m_valueRect1;
	Rect m_btnLeftRect2;
	Rect m_btnRightRect2;
	Rect m_valueRect2;
	Rect m_textRect1;
	Rect m_textRect2;

    Rect m_worldSelectBtnRect;
	Rect m_worldTitleRect;
	Rect m_worldTextRect;

	class LevelEditorWaveEventPortalPanel* m_panel;
	Rect m_panelRect;
	std::vector<std::string> m_mapList;
};

class LevelEditorWaveEventPortalPanel : public Widget
{
public:
	LevelEditorWaveEventPortalPanel();
    virtual void Draw(Sexy::Graphics* i_g) override;

    void SetBgImage(Image* bg);

protected:
    Image* m_bg;
};

#endif
