//
//  SnakeModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-12-25.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SnakeModule__
#define __PlantsVersusZombies2__SnakeModule__

#include "LevelModule.h"
#include "Snake.h"
#include "ReviveUI.h"
#include "InitialGridItemPlacer.h"

class SnakeModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(SnakeModule, LevelModule, RtClass);
    
    SnakeModule();
    
    SnakeNode * GetSnakeHead();
    
    void        setCanTouch(bool i_canTouch);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void postInitialize() override;
    
    bool         handleTouch(const Sexy::Touch& i_touch);
	void         cancelTouch();
    
private:
    
    void        onUpdate();
    
    void        loadComplete();
    void        levelStarted();
    void        gameplayStarted();
    bool        preventSave();
    
    void        onReviveCancel();
    void        onReviveOK();

    void        onZombieSpawned(class Zombie * i_zombie);
    void        onZombieRiseFromGround(class Zombie* i_zombie);
    void        onZombieCloseToHouse(class Zombie* i_zombie);
    void        onLawnMowerDie(class LawnMower* i_mower);
    
    void        onSnakeAdd();
    void        onSnakeHitBlock();
    void        onSnakeHeadHitBody();
    void        onSnakeRunOutBorder();
    void        onSnakeSlowDown();
    
    void        stopAllSnake();
    
    void        adjustZombie(class Zombie * i_zombie);

    void        onAnimDone_RunOutBorder(class StandaloneEffect* i_effect);
    
private:
    
    SnakeNode * snakeHead;
    SnakeNode * snakeTail;
    
    bool        m_GameStarted;
    
    Sexy::TouchID m_touchIdent;
	SexyVector2   m_touchStart;
    bool          m_touchIsMove;
    bool          m_bCanTouch;
    
    int           m_snakeCount;
    float         m_snakeStep;
    
    std::vector<int> m_BlueInfos;
    
    ReviveMode       m_revive_mode;
    
    bool             m_needMower;
    int              m_MowerRow;
    
    bool             m_InReviveUI;
    
    pvztime_t        m_TimeSlowDown;
    pvztime_t        m_TimeFailure;
};


class SnakeProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SnakeProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SnakeModule::StaticGetClass();
	}
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
    SnakeProperties()
    {
        SnakeDamage = 20;
    }
    
    int SnakeDamage;
    std::vector<int>                            BlueInfos;
    std::vector<int>                            HPShows;
    std::vector<float>                          HPCurWave;
    std::vector<GridItemPlacementProperties>	BlockPlacements;
};

#endif /* defined(__PlantsVersusZombies2__SnakeModule__) */
