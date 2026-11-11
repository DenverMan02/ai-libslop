//
//  AutoTest.hpp
//  PlantsVersusZombies2
//
//  Created by shizf on 16/2/17.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef AutoTest_h
#define AutoTest_h

#include "Core.h"
#include "RtDb.h"
#include "RtObject.h"
#include "PVZTypes.h"
#include "DamageInfo.h"

namespace Message {
    void changeAutoTestStartLevel(const std::string& i_level);
    void changePlantsVsZombiesStartWorld(const std::string& i_world);
    void changeAutoTestStartUnlockLevel(const std::string& i_level);
    
    void AutoTestStartAllLevel();
    void AutoTestShowOverWinUINotify();
    void AutoTestShowOverLoseUINotify();
    void AutoTestCloseOverUINotify();
    
    void AutoTestClosePreviewDialog();
    void AutoTestConfirmStartMiniGame();
    
    void AutoTestLevelWinFinishNotify();
    void AutoTestLevelLoseFinishNotify();
    
    void AutoTestPlantUIShow();
    void AutoTestPlantSelected();
    void AutoTestPlantUnLock();
    void AutoTestPlantLevelUpOver();
    
    void AutoTestShowWorldPreview();
    void AutoTestEnterWorldMap();
    void AutoTestUpdateLevelUnlockState();
}

class MapEventItem;

//----------------

class AutoTest : public RtObject
{
public:
    RT_CLASS_DEFINE(AutoTest, RtObject, RtClass) {}
    
    /// Creation / Initialization
    AutoTest()
    :m_isOn(false)
    {}
    
    virtual ~AutoTest(){setIsOn(false);};
    
    bool getIsOn() const
    {
        return m_isOn;
    }
    
    void setIsOn(bool i_value);
    
protected:
    virtual void updateState(bool i_isOn){};
    
private:
    bool m_isOn;//test is open
};

//--------------

class BoardEntity;
class Zombie;
class Plant;


class AutoTestAllLevel : public AutoTest
{
public:
    RT_CLASS_DEFINE(AutoTestAllLevel, AutoTest, RtClass) {}
    
    AutoTestAllLevel();
    virtual ~AutoTestAllLevel();
    
protected:
    virtual void updateState(bool i_isOn) override;
    
    void SkipSeedChooser();
    void SkipPooyan();
    
    void AutoEnterLevel();
    void AutoEnterWorld();
    void ChangeStartLevel(const std::string& i_level);
    

    void ForceFinishLevel();
    void AutoStartFirstLevel();
    void AutoStartNextLevel();
    void AutoStartLevelFight();
    void AutoTestInitPlantPlace(std::string LevelType);
    
    void AutoFinishWinLevel();
    void AutoFinishLoseLevel();
    void ConfirmStartMiniGame();
    void AutoTestPLantDie(Plant* i_plant);
    void AutoTestZombieCloseToHouse(Zombie* i_zmobie);
    void AutoTestSkyCityDamage(float i_Percent);
    
    void AutoConfirmOver();
    
private:
    void  StartCurrentLevel(std::string strLevel);
    void  RefreshNewLevelList(std::vector<std::string>& vecLevel);
    const MapEventItem* m_currentLevel;
    const MapEventItem* m_needChangeLevel;
    std::vector<std::string> m_vecLevel;
    std::vector<std::string> m_vecWorldMap;
    int m_curWorldIndex;
    int m_curLevelIndex;
    std::string m_strAimUsePlant;
    std::string m_strLevelName;
    std::vector<std::string> m_vecIgnoreLevel;
};
//--------------------------


class AutoTestPlantsVsZombies : public AutoTest
{
public:
    RT_CLASS_DEFINE(AutoTestPlantsVsZombies, AutoTest, RtClass) {}
    
    AutoTestPlantsVsZombies();
    virtual ~AutoTestPlantsVsZombies();
    
protected:
    virtual void updateState(bool i_isOn) override;
    
    void initByWorld();
    
    void PlantsVsZombiesStart();
    void PlantsVsZombiesUpdate();
    
    void onPlantDied(Plant* i_plant);
    void onZombieDied(Zombie* i_zmobie, const DamageInfo* i_deathBlow);
    void OnZombieCloseToHouse(Zombie* i_zmobie);
    
    void AutoEnterLevel();
    void QuitLevel();
    
    void GetZombies(std::vector<Zombie*>& o_zombieList, const std::function<bool(const BoardEntity*)>& accept);
    void GetPlants(std::vector<Plant*>& o_plantList, const std::function<bool(const BoardEntity*)>& accept);
    
    void checkAndAddPlant(int y);
    void checkAndAddZombie(int y);
    void checkAndTestNextPlant(bool i_force = false);
    
    void addPlant(int y);
    void addZombie(int y);
    
    void killZombie(Zombie* i_zombie);
    
    void setTestPlants(const std::vector<PlantTypePtr>& i_plants);
    void setTestZombies(const std::vector<ZombieTypePtr>& i_zombies);
    
    void changeStartWorld(const std::string& i_world);
    
    void AutoFinishWinLevel();
    void AutoStartNextLevel();
    void AutoTestSkyCityDamage(float i_Percent);
    
    void AutoConfirmOver();
private:
    bool getWorld();
    
private:
    std::vector<PlantTypePtr> m_plants;
    std::vector<ZombieTypePtr> m_zombies;
    size_t m_plantIndex;
    size_t m_zombieIndex;
    size_t m_worldIndex;
    bool m_delayCheck;
    
    pvztime_t m_changeTime;
};

//------------------------------------



class AutoTestAllLevelUnlock : public AutoTest
{
public:
    RT_CLASS_DEFINE(AutoTestAllLevelUnlock, AutoTest, RtClass) {}
    
    AutoTestAllLevelUnlock();
    virtual ~AutoTestAllLevelUnlock();
    
protected:
    virtual void updateState(bool i_isOn) override;

    void EnterUniverse();
    void ShowWorldPrebview();
    void EnterWorldMap();
    void EnterWorldMapFinish();
    void ChangeWorldMap(const std::string& i_world);
    void UpdateUnlockState();
    
    void AutoConfirmOver();
private:
    pvztime_t m_changeTime;
    int  m_curLevelIndex;
    int  m_curWorldIndex;
    std::string m_curWorldName;
    std::string m_changWorldName;
    bool m_bWorldmapFinish;
};


//-------------------------------


class AutoTestPlantLevelUp : public AutoTest
{
public:
    RT_CLASS_DEFINE(AutoTestPlantLevelUp, AutoTest, RtClass) {}
    
    AutoTestPlantLevelUp();
    virtual ~AutoTestPlantLevelUp();
    
protected:
    virtual void updateState(bool i_isOn) override;
    
    void PlantTestShowUI();
    void PlantTestSelectedOk();
    void PlantTestUnlockOver();
    void PlantTestLevelUpOver();
    void PlantTestAddPiceceToServer();
    void PlantTestSyncPlantFinish(bool i_success);
    
    void AutoConfirmOver();
private:
    int m_curPlantIndex;
    int m_curLevel;
    bool m_bLevelUping;
};

//--------------------------------


/// AutoTest Manager
class AutoTestManager : public LazySingleton<AutoTestManager>
{
public:
    AutoTestManager(){}
    
    void addAutoTest(const std::string& i_name,AutoTest* i_test);
    AutoTest* getAutoTest(const std::string& i_name) const;
    void setAutoTestEnable(const std::string& i_name,bool i_enable);
    bool getAutoTestIsEnable(const std::string& i_name) const;
    
private:
    std::map<std::string,AutoTest*> m_tests;
};

#define gAutoTestMgr (AutoTestManager::GetInstancePtr())

namespace PVZAutoTest {
    void SetupAutoTest();
};

#endif /* AutoTest_hpp */
