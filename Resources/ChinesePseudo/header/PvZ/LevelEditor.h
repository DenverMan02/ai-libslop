#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "UISingletonDialog.h"
#include "ButtonListener.h"
#include "SliderListener.h"
#include "LevelEditorDefine.h"
#include "LevelEditorUtil.h"
#include "CustomLevelConfig.h"


/*---------------------关卡编辑器------------------------------*/

class LevelEditor : public UISingletonDialog<LevelEditor>, public SliderListener
{
public:
    LevelEditor(); 
    virtual ~LevelEditor();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditor"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;
    virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;
    static UI::Dialog* 						CreateEditor(CustomLevelNetworkLevelMode i_mode);

private:
    LevelEditorSeedBankType m_seedType;

public:
    void Init();
    void Reload();

    void ChangeBoardStageByWorld(const std::string& i_world);
    void ChangeBoardStageArt(const std::string& i_stage);

    Sexy::Point GetZombieStageAbsPoint();

    void TriggerTutorial();
    void CloseEncourageTanhao();

private:
    void InitCommon();
    void InitBoardModule();
    void InitZombieModule();

    void SwitchToBoardModule();
    void SwitchToZombieMoudle();

    void OnTutorialCreated();
    void OnDragFinished();
private:
    class Widget* m_seedBank;
    class UIWidgetImage* m_currentStage;
    class UIWidgetImage* m_encourageTanhao;
    class PVZ2UIButton* m_boardStageSelect;

    Widget* m_boardMainWidget;
    Widget* m_zombieMainWidget;
    class PVZ2UIButton* m_tutorialSwitchBtn;
    class PVZ2UIButton* m_tutorialCloseBtn;
};

class LevelEditorEvilDave : public UISingletonDialog<LevelEditorEvilDave>, public SliderListener
{
public:
	LevelEditorEvilDave();
    virtual ~LevelEditorEvilDave();
    bool	                        		OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditorEvilDave"; }
    virtual void							ButtonDepress(int i_id) override;

public:
    void Init();
private:
    void SetWorld();
    void InitCommon();
    void InitBoardModule();
    void ChangeBoardStageArt(const std::string& i_stage);

    Widget* m_boardMainWidget;
};

/////////////////////////
/// Tower Defend
/////////////////////////
class LevelEditorTowerDefend : public UISingletonDialog<LevelEditorTowerDefend>, public SliderListener
{
public:
	LevelEditorTowerDefend();
    virtual ~LevelEditorTowerDefend();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditorTowerDefend"; }
    virtual void							ButtonDepress(int i_id) override;

    void Init();
    void Reload();

private:
    void InitBoardModule();
    void InitZombieModule();
    void SwitchToBoardModule();
    void SwitchToZombieMoudle();
    void ChangeBoardStageArt(const std::string& i_stage);

private:
    Widget* m_seedBank;
    Widget* m_boardMainWidget;
    Widget* m_zombieMainWidget;
};

/////////////////////////
/// Single Handed
/////////////////////////
class LevelEditorSingleHanded : public UISingletonDialog<LevelEditorSingleHanded>, public SliderListener
{
public:
	LevelEditorSingleHanded();
    virtual ~LevelEditorSingleHanded();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditorSingleHanded"; }
    virtual void							ButtonDepress(int i_id) override;

    void Init();
    void Reload();

private:
    void InitBoardModule();
    void InitZombieModule();
    void SwitchToBoardModule();
    void SwitchToZombieMoudle();
    void ChangeBoardStageArt(const std::string& i_stage);

private:
    Widget* m_seedBank;
    Widget* m_boardMainWidget;
    Widget* m_zombieMainWidget;
};

#define gLevelEditor LevelEditor::GetSingletonPtr()

class LevelEditorLoadGroupWidget : public Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    void Init();
};


#endif
