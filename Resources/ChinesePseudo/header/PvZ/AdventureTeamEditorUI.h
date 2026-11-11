//
//  AdventureTeamEditorUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AdventureTeamEditorUI__
#define __PlantsVersusZombies2__AdventureTeamEditorUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "PlantType.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "MagentoService.h"
#include "PlantAdventureUI.h"

enum AdventureTeamEditorUITutorialStep
{
	ATEUIT_Step0,
    ATEUIT_Step1,
    ATEUIT_Step2,
    ATEUIT_Step3,
    ATEUIT_Step4,
    ATEUIT_End,
};

enum TeamSeedType
{
    InTeam,
    InChooser,
};

class TeamSeed : public Sexy::Widget
{
public:
    TeamSeed(TeamSeedType i_seedType, PlantTypePtr i_plantType, int i_buttonId, ButtonListener * btnListener);
    ~TeamSeed();
    
    virtual void Update();
    virtual void Draw(Graphics* i_g);
    virtual void Resize(const Rect& theRect);
    
    void drawPacket(Sexy::Graphics* i_g);
    
    void InitView();
    void SetSelected(bool i_selected);
    const bool GetCurrentSelectedFlag() { return m_bSelected; }
    
    PlantTypePtr GetPlantType();
    int GetPlantId();
    int GetStartY();
    int GetButtonId();
    int GetRecoverGems();
    int CalcRecoverGems(int i_seconds);
    bool IsInAdventure();
    bool IsCoolingDown();
    
    void MouseDown(int x, int y, int theClickCount) override;


private:
    TeamSeedType m_seedType;
    bool m_coolingDown;
    bool m_inAdventure;
    bool m_bSelected;
    int m_buttonId;
    int m_recoverGems;
    uint32 m_endCDTime;
    
    PlantTypePtr m_plantType;
    
    PVZ2UIButton * m_btn;
    Sexy::Rect m_seedRect;
    Sexy::Rect m_timeLebelRect;
    SexyString m_timeLabel;
};

class TeamEditorScrollPanel : public Widget, public ButtonListener
{
public:
    TeamEditorScrollPanel(TeamSeedType i_type, Sexy::Rect &i_rect);
    virtual ~TeamEditorScrollPanel();
    
    void InitView();
    void ButtonDepress(int i_id);
    void SelectPlant(int i_id);
    void UnSelectPlant(int i_id);
    bool HasPlantInTeam(int i_plantId);
    
    int GetPlantTeamCount();
    int GetRecoverGems();
    void RefreshSeedTeam();
    
    void OnAddPlantToTeam(int i_plantId);
    void OnRemovePlantFromTeam(int i_plantId);
    
    bool HasPlantFlag(std::string i_flag);
    void RemoveLastSelected();
    TeamSeed* GetWidgetButtonId(int i_buttonId);
    std::vector<TeamSeed *> GetChoosedTeamSeed();
    std::vector<TeamSeed *> GetTeamChooser();
    void TriggerTutorial();
    void OnTutorialBtnPressed(int i_id);
    
private:
    int m_lastSelect;
    int m_buttonId;
    int m_recoverGems;
    bool m_isInAdventure;
    TeamSeedType m_seedType;
    Sexy::Rect m_widgetRect;
    PlantType m_plantType;
    pvztime_t m_cooldownRemain;
    std::vector<TeamSeed *> m_contents;
    std::vector<TeamSeed *> m_teamContents;
    Widget* m_tutorialWidget;
};

struct PlantRequire
{
    bool achived;
    std::string req;
    
    PlantRequire()
    {
        achived = false;
        req = "";
    }
};

class AdventureTeamEditorUI : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    AdventureTeamEditorUI(WorldDungeonInfo i_dungeonInfo);
    ~AdventureTeamEditorUI();
    
    virtual void Update();
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Draw(Graphics* i_g);
    virtual void ButtonDepress(int i_id);
    
    // implement of Sexy::ScrollWidgetListener
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}
    
    void InitView();
    void UpdateSpirit(Sexy::Graphics* i_g);
    void RefreshReq();
    const SexyString GetDungeonNameForShow(std::string i_name);
    bool IsAllReqAchieved();
    void AutoTeam();
    
    void OnStartExplore(bool i_success);
    void OnRecoverExplorePlant(bool i_success);
    void OnNeedRecoverExplorePlant(int i_costGems);
    
    void ConfirmBuy();
    void CancelBuy();
    void OnConfirmStartAdventure(bool i_success);
    
    void OnRefreshAll();
    
    TeamEditorScrollPanel* GetTeamPanelWidget() { return m_teamPanelWidget; }
    TeamEditorScrollPanel* GetTeamChooserPanelWidget() { return m_teamChooserPanelWidget; }
    
    void OnTutorialClicked();
    void TriggerTutorial();

private:
    AdventureTeamEditorUITutorialStep m_tutorialStep;
    
    int m_recoverGems;
    
    WorldDungeonInfo m_dungeonInfo;
    
    Sexy::Rect m_rectDialog;
    Sexy::Rect m_teamTitleRect;
    Sexy::Rect m_teamRect;
    Sexy::Rect m_teamReqRect;
    Sexy::Rect m_seedChooserRect;
    Sexy::Rect m_titleRect;
    Sexy::Rect m_countReq;
    Sexy::Rect m_plantReq;
    
    SexyString m_strTime;
    SexyString m_dungeonTitle;
    SexyString m_countReqDes;
    SexyString m_plantReqTitle;
    SexyString m_plantReqDes;
    
    PVZ2UIButton* m_startButton;
    PVZ2UIButton* m_closeButton;
    PVZ2UIButton* m_autoButton;
    
    PVZ2UIScrollingWidget * m_teamPanel;
    PVZ2UIScrollingWidget * m_teamChooserPanel;
    
    TeamEditorScrollPanel* m_teamPanelWidget;
    TeamEditorScrollPanel* m_teamChooserPanelWidget;
    
    std::vector<PlantRequire> m_plantReqList;
};

namespace Message
{
    void AddPlantToTeam(int i_plantId);
    void RemovePlantFromTeam(int i_plantId);
    void ConfirmStartAdventure(bool i_success);
    void TutorialClicked();
    void TutorialBtnPressed(int i_id);
}

#endif /* defined(__PlantsVersusZombies2__AdventureTeamEditorUI__) */
