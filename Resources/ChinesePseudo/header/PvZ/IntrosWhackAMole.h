//
//  IntrosWhackAMole.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-1-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntrosWhackAMole__
#define __PlantsVersusZombies2__IntrosWhackAMole__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"

namespace Message
{
	void NotifyWhackGameBegin();
    void NotifyRandMole();
    void NotifyWhackGameEnd();
}

STATE_ENUM_BASE_BEGIN(MoleState)
MoleState_DownIdle,
MoleState_Up,
MoleState_Idle,
MoleState_Down,
STATE_ENUM_END(MoleState);

enum MoleType {
    Mole_none,
    Mole_Zombie,
    Mole_plant
};

struct MoleNonSpawnData
{
	MoleNonSpawnData()
    {
        GridX = -1;
        GridY = -1;
        spawnZombieRate = 0.5f;
        spawnHamsterTime = 2.0f;
    }

    int				GridX;
    int				GridY;
    float           spawnZombieRate;
    float           spawnHamsterTime;
};

class Effect_Mole: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_Mole, Effect_PopAnim, RtClass);
    void SetMoleType(MoleType moleType);
protected:
	virtual void onInitialized() override;
    void onNotifyGameEnd();
    void onMoleDownOver(StandaloneEffect* i_effect);
protected:
    MoleType    m_moleType;
};


class GridItemMoleProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemMoleProps, GridItemAnimationProps, RtClass);
	GridItemMoleProps() : changeSpaceTime(10.f), HardLevelchangeSpaceTime(10.f)  {}

    float changeSpaceTime;
    float HardLevelchangeSpaceTime;
};

class GridItemMole : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemMole, GridItemAnimation, RtClass);

    GridItemMole();
    ~GridItemMole();
    void        setState(MoleState i_newState);
	bool        isInState(MoleState i_state) const;

    MoleType        OnHandleTouched();
    Sexy::Rect calcTouchRect();

    void setSpawnZombieRate(float rate);
    void setSpawnHamsterTime(float time);

    void setStartTime(pvztime_t startTime);
    pvztime_t getStartTime() const { return m_gStartTime; };

    void setHardLevel(bool isHardLevel);
protected:
    void onGridItemInitialize() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    int CalcRenderOrder() const override;
    void		onUpdate() override;
    void		onDraw(Graphics* i_g) override;
    DECLARE_STATE_FUNCTIONS(MoleState, DownIdle);
    DECLARE_STATE_FUNCTIONS(MoleState, Up);
    DECLARE_STATE_FUNCTIONS(MoleState, Idle);
    DECLARE_STATE_FUNCTIONS(MoleState, Down);
    void onNotifyGameEnd();

    
    void onUpOver(StandaloneEffect* i_effect);
    void onDownOver(StandaloneEffect* i_effect);

    // void    onUpOver(const std::string &i_animName);
    // void    onDownOver(const std::string &i_animName);
    void onNotifyGameBegin();

    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    virtual void onDestroy() override;

private: 
    pvztime_t                         m_gStartTime;
    StateMachine<MoleState>      m_MoleState;
    MoleType    m_moleType;
    float m_fSpawnZombieRate;
    float m_fSpawnHamsterTime;
    Effect_Mole* m_pAnimalEffect;
    Effect_Mole* m_pPlantEffect;
    bool m_bIsGameStart;
    bool m_bIsGameEnd;
    float m_fSpaceTime;
    bool m_bIsHardLevel;
};


class WhackAMoleIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(WhackAMoleIntro, StandardLevelIntro, RtClass);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void spawnMoles();
    bool IsPlantDisabled(int i_x, int i_y);
    float GetSpwanZombieRate(int i_x, int i_y);
    float GetSpwanHamsterTime(int i_x, int i_y);
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    void            OnGameplayStarted();
    void            OnHandleTouchState();
    void            OnTouchOutBorderWorning();
    
    void         SetCanTouch(bool i_canTouch);
    
    void        randomMole();
    void onNotifyRandomMole();
    
private:
    std::vector<GridItemMole*> m_vecMole;
};


class WhackAMoleIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(WhackAMoleIntroProperties, StandardLevelIntroProperties, RtClass);
    
    WhackAMoleIntroProperties()
    {
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return WhackAMoleIntro::StaticGetClass();
	}
    
    std::vector<MoleNonSpawnData> setLocations;
    bool IsTutorial;
};

#endif /* defined(__PlantsVersusZombies2__IntrosWhackAMole__) */
