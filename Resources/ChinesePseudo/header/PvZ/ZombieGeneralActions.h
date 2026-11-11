//
//  ZombieGeneralActions.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/7/18.
//  Copyright (c) 2018 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieGeneralActions_h
#define PlantsVersusZombies2_ZombieGeneralActions_h

#include "ZombieAction.h"

//
// Walk
//

class ZombieWalkActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieWalkActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombieWalkActionDefinition() {}
	
	float			StopAtColumn = -1;
	bool			WalkBackwards = false;
    bool            TransitionAtStart;
    std::string     TransitionAnimation;
    bool            HasTransition;
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieWalkActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieWalkActionHandler, ZombieActionHandler, RtClass);
	
	ZombieWalkActionHandler()	{}
    
	void onWalkAnimationCycle();

protected:
	
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
    
    void playTransition();
    
    bool m_isWalking;
	
};

//
// TimedAction Base
//

class ZombieTimedActionDefinition : public ZombieActionDefinition
{
	public:
	RT_CLASS_DEFINE(ZombieTimedActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombieTimedActionDefinition() {}
	
	float MinDuration;
	float MaxDuration;
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieTimedActionHandler : public ZombieActionHandler
{
	public:
	RT_CLASS_DEFINE(ZombieTimedActionHandler, ZombieActionHandler, RtClass);
	
	ZombieTimedActionHandler()	{}
	
	protected:
	
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
	pvztime_t m_timeToEnd;
};

// Note: Currently a timed thing for prototype.  Convert to animation if that is appropriate and re-subclass from TimedAction.
class ZombieIdleActionDefinition : public ZombieTimedActionDefinition
{
	public:
	RT_CLASS_DEFINE(ZombieIdleActionDefinition, ZombieTimedActionDefinition, RtClass);
	
	ZombieIdleActionDefinition() {}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombieIdleActionHandler : public ZombieTimedActionHandler
{
	public:
	RT_CLASS_DEFINE(ZombieIdleActionHandler, ZombieTimedActionHandler, RtClass);
	
	ZombieIdleActionHandler()	{}
	
	protected:
	
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
	//void onAnimationDone(const std::string& i_animName);
};

// Note: Currently a timed thing for prototype.  Convert to animation if that is appropriate and re-subclass from TimedAction.
class ZombiePlayAnimationActionDefinition : public ZombieActionDefinition
{
	public:
	RT_CLASS_DEFINE(ZombiePlayAnimationActionDefinition, ZombieActionDefinition, RtClass);
	
	ZombiePlayAnimationActionDefinition() {}
	
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	
	std::string	AnimationToPlay;
	int AnimationLoops = 0;
};

class ZombiePlayAnimationActionHandler : public ZombieActionHandler
{
	public:
	RT_CLASS_DEFINE(ZombiePlayAnimationActionHandler, ZombieActionHandler, RtClass);
	
	ZombiePlayAnimationActionHandler()	{}
	
	protected:
	
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;
	
	void onAnimationDone(const std::string& i_animName);

private:
	void startAnimation();
	
	int m_loopsRemaining = 0;
};

class ZombieStunActionDefinition : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombieStunActionDefinition, ZombieActionDefinition, RtClass);
    
    ZombieStunActionDefinition() {}
    
    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
    
    std::string StartingAnimation;
    std::string LoopingAnimation;
    std::string EndingAnimation;
};

class ZombieStunActionHandler : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombieStunActionHandler, ZombieActionHandler, RtClass);
    
    ZombieStunActionHandler() {}
    
    void onCycleComplete();
    
protected:
    void onStartAction() override;
    void onUpdateAction() override;
    
private:
    void playStart();
    void playLoop();
    void playEnd();
    
    pvztime_t m_stunStartTime;
	bool stunEnded;
};

#endif
