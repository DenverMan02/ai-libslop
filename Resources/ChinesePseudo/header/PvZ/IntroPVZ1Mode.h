/*
 * IntroPVZ1Mode.h
 *
 *  Created on: 2021-8-25
 *      Author: admin
 */

#ifndef INTROPVZ1MODE_H_
#define INTROPVZ1MODE_H_

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "VictoryOutro.h"

STATE_ENUM_BASE_BEGIN(PVZ1IState)
	PVZ1IState_GAMEINIT,
	PVZ1IState_TUTORIAL,
	PVZ1IState_STARTGAME,
STATE_ENUM_END(PVZ1IState);

class PVZ1ModeIntro : public StandardLevelIntro
{
public:
    RT_CLASS_DEFINE(PVZ1ModeIntro, StandardLevelIntro, RtClass);

    PVZ1ModeIntro();

    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
    virtual void	initializeModule() override;
    virtual void	registerForEvents() override;

    void			OnIntroStarted();
    void 			OnUpdate();
    void 			OnLevelEnded();
    void            OnGameplayStarted();
    void 			onLoadComplete();
    void			onFirstNarrationFinished() override;

    DECLARE_STATE_FUNCTIONS(PVZ1IState, GAMEINIT);
    DECLARE_STATE_FUNCTIONS(PVZ1IState, TUTORIAL);
    DECLARE_STATE_FUNCTIONS(PVZ1IState, STARTGAME);


private:

    void        setState(PVZ1IState i_newState);
    bool        isInState(PVZ1IState i_state) const;

    void        ShowReady();
    void        ShowSet();
    void        ShowBreak();
    void 		StartGame();
    void		OnNotifyPVZ1HowToPlayClose();
private:
    StateMachine<PVZ1IState>      		m_PVZ1IState;

    pvztime_t                           m_startTime;
    float                               m_readyTime;
    float                               m_setTime;
    float                               m_breakTime;
    float                               m_goTime;
    bool                                m_readyShown;
    bool                                m_setShown;
    bool                                m_breakShown;
    bool                                m_started;
};

class PVZ1ModeIntroProperties : public StandardLevelIntroProperties
{
public:
    RT_CLASS_DEFINE(PVZ1ModeIntroProperties, StandardLevelIntroProperties, RtClass);

    PVZ1ModeIntroProperties()
    {
    	CurrentIntroStage = 0;
    }

    virtual RtClass* GetModuleClass() const override
    {
        return PVZ1ModeIntro::StaticGetClass();
    }

    int CurrentIntroStage;
};

class IntroPVZ1ModeVictoryOutroModule : public VictoryOutroModule
{
public:
    RT_CLASS_DEFINE(IntroPVZ1ModeVictoryOutroModule, VictoryOutroModule, RtClass);

    IntroPVZ1ModeVictoryOutroModule();

protected:
    void onCollectableFinishCollected(class Collectable* i_collectable) override;
    void registerForEvents() override;
    void onUpdate() override;
private:
    void onNotifyTutorialWormHoleEnd();
    void triggerEndLevelEffect();
    void triggerPortal();
    void spawnGridItem(Point i_gridLocation, GridItemTypePtr i_type, std::string i_spawnAnimationID, std::string i_spawnSoundID);

    pvztime_t m_endTime;
};

class IntroPVZ1ModeVictoryOutroProperties : public VictoryOutroProperties
{
public:
    RT_CLASS_DEFINE(IntroPVZ1ModeVictoryOutroProperties, VictoryOutroProperties, RtClass);

    IntroPVZ1ModeVictoryOutroProperties()
	{
    	NeedShowPortal = false;
	}

	RtClass* GetModuleClass() const override
    {
        return IntroPVZ1ModeVictoryOutroModule::StaticGetClass();
    }

	bool NeedShowPortal;
};

#endif /* INTROPVZ1MODE_H_ */
