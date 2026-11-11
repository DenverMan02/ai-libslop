//
//  BesiegeModule.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/7/30.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BesiegeModule__
#define __PlantsVersusZombies2__BesiegeModule__

#include "LevelModule.h"
#include "ReviveUI.h"
#include "UIWidget.h"
#include "InitialGridItemPlacer.h"
#include "Zombie.h"
#include "Plant.h"
#include "ChallengeUI.h"
#include "PopAnimRig.h"
#include "TowerDefendModule.h"
#include "BaseCursor.h" 
#include "PrimeTextWidget.h"
#include "SexyString.h"

class BesiegeProperties;

#define BESIEGE_MAP_HEIGHT (5 + 2)
#define BESIEGE_MAP_WIDTH (9 + 2)
#define NOT_SEARCH_GRID 1000
#define WALL_GRID 900
#define BOX_GRID 800

class BesiegeMazeMap
{
public:
    BesiegeMazeMap();
    ~BesiegeMazeMap();
    
    void ResetBesiegeGuide();
    void RemoveAllBesiegeGuide();
    bool HasInited() { return m_inited; }
    void InitMazeMap(std::vector<Point> startPoints, Point targetPoint, bool i_testBox = false);
    void calcMazeMapHeight(bool i_reset = true, bool i_testBox = false);
    int calcGridHeight(int gridX, int gridY) { return m_mazeMapHeight[gridX][gridY]; }
    void SetTestBox(int gridX, int gridY);
    
private:
    void ResetMazeMap();
    void SearchMazeGrid(int i_gridX, int i_gridY, int i_height, bool i_testBox = false);
    bool ShouldTryGrid(int i_gridX, int i_gridY, int i_height);
    
private:
    
    Point TestBox;
    bool m_inited;
    int m_mazeMapHeight[BESIEGE_MAP_WIDTH][BESIEGE_MAP_HEIGHT];
    std::vector<Point> m_startPoints;
    Point m_targetPoint;
};

enum ArrowDir
{
    arrowleft = 1,
    arrowright,
    arrowup,
    arrowdown,
};

class GridItemBesiegeGuide : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemBesiegeGuide, GridItemAnimation, RtClass);
    
    int		CalcRenderOrder() const override;
    void    SetIsStartPoint(bool i_startpoint);
    void    PlayArrow(ArrowDir i_dir);
    
protected:
    void    onDraw(Sexy::Graphics* i_g) override;
    void	registerForEvents() override;
    void	onGridItemInitialize() override;
};

class GridItemAnimRig_BesiegeGuide : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemAnimRig_BesiegeGuide, PlantAnimRig, RtClass);
    
    GridItemAnimRig_BesiegeGuide() {}
    virtual ~GridItemAnimRig_BesiegeGuide() {}
    
    void PlayIdle();
    void PlayArrow(ArrowDir i_dir);
    
protected:
};

class GridItemBesiegeBox : public GridItem
{
public:
    RT_CLASS_DEFINE(GridItemBesiegeBox, GridItem, RtClass);
    
    GridItemBesiegeBox();
    ~GridItemBesiegeBox();
    
    bool IsSteadyBox() { return m_steadyBox; };
    bool IsTargetBox();
    bool CanBeShoveled() override;
    int Shovel() override;
    
    void SetGridLocation(Sexy::Point i_gridLocation, const bool i_recalculatePosition = true) override;
    
protected:
    void onGridItemInitialize() override;
    void onDraw(Sexy::Graphics* i_g) override;
    void onAnimDone(StandaloneEffect* i_effect);
    int CalcRenderOrder() const override;
    
private:
    bool m_steadyBox;
};

class BesiegeModule : public LevelModule
{
public:
    
    RT_CLASS_DEFINE(BesiegeModule, LevelModule, RtClass);
    
    BesiegeModule();
    ~BesiegeModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

    void SetTutorial(bool i_tutorial);
    bool IsInTutorial();
    void SetInTutorialFirstStep(bool i_tutorialFirstStep);
    bool IsInTutorialFirstStep();
    void resetMazeMap();
    Point calcNextGrid(int gridX, int gridY, int i_hit = 1, bool i_zombie = true);
    bool TestIfCanPlantBesiegeBoxOn(int gridX, int gridY);
    
    BesiegeMazeMap *GetBesiegeMap() { return &m_besiegeMazeMap; }
    int GetPlantUpgradeSunSpend(Plant * i_plant);
    float GetPlantLaunchtimePercent(Plant * i_plant);
    std::string GetPlantUpgradeType(Plant * i_plant);
    
    const BesiegeProperties * GetBesiegeProps();
    
    bool IsBesiegeGameStarted() { return m_GameStarted; }
    int GetHomeHP() { return m_homeHP; }
    Sexy::PrimeTextWidget* GetHomeHPText() { return m_HomeHPText; }
    void GetHomeHPTextPtr(Sexy::PrimeTextWidget* textWidget) { m_HomeHPText = textWidget; }
    void SetHomeHPText(SexyString text) { m_HomeHPText->SetText(text); }
    void InitModule();
    void SolveBesiegeIntro(const Sexy::Touch& i_touch);
    
    bool IsInReviveUI() { return m_InReviveUI; }
    bool IsStartPoint(Point i_point);
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;
    
    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    
private:
//    bool checkWin();
    void onUpdate();
    
    void loadComplete();
    void levelStarted();
    void gameplayStarted();
    bool preventSave();
    
    void onReviveCancel();
    void onReviveOK();
    
    void onZombieSpawned(class Zombie * i_zombie);
    void onZombieKilled(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onPlantUpgradeTouch(const Point& i_pos);
    void onPlantPlanted(class Plant* i_plant);
    
private:
    
    int                                     m_homeHP;
    bool                                    m_GameStarted;
    bool                                    m_hasWon;
    bool                                    m_InReviveUI;
    bool                                    m_Tutorial;
    bool                                    m_TutorialFirstStep;
    
    pvztime_t                               m_TimeFailure;
    Sexy::PrimeTextWidget*                  m_HomeHPText;
    std::vector<Point>                      m_startPoints;
    Point                                   m_targetPoint;
    BesiegeMazeMap                          m_besiegeMazeMap;
};

struct BesiegeGrid
{
    BesiegeGrid()
    {
        X = -1;
        Y = -1;
    }
    
    int X;
    int Y;
};

class BesiegeProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(BesiegeProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return BesiegeModule::StaticGetClass();
    }
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
    BesiegeProperties()
    {
        StartingSun = 100;
        StartingPlantfood = 0;
        HomeHP = 0;
        HPIncrease = 0.f;
    }
    
    int                                         StartingSun;
    int                                         StartingPlantfood;
    int                                         HomeHP;
    float                                       HPIncrease;
    std::vector<TowerDefendPlantUpgradeTree>    Trees;
    std::vector<BesiegeGrid>                    StartGrid;
    BesiegeGrid                                 TargetGrid;
    std::vector<BesiegeGrid>                    InitialBoxGrid;
};

namespace Message
{
    void ShovelTutorial();
    void UseShovel();
    void PlantUpgrade();
    void ShoveledBesiegeBox();
}

#endif /* defined(__PlantsVersusZombies2__BesiegeModule__) */
