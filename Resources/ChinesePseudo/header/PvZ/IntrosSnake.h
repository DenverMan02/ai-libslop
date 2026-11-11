//
//  IntrosSnake.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-1-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntrosSnake__
#define __PlantsVersusZombies2__IntrosSnake__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"

STATE_ENUM_BASE_BEGIN(SKIState)
SKIState_GestureZombie,
SKIState_GestureOutBorder,
SKIState_GestureBlock,
SKIState_START_GAME,
STATE_ENUM_END(SKIState);

class SnakeIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(SnakeIntro, StandardLevelIntro, RtClass);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    void            OnGameplayStarted();
    void            OnSnakeHandleTouchState(int direction);
    void            OnSnakeRunOutBorderWorning();
    
    DECLARE_STATE_FUNCTIONS(SKIState, GestureZombie);
    DECLARE_STATE_FUNCTIONS(SKIState, GestureOutBorder);
    DECLARE_STATE_FUNCTIONS(SKIState, GestureBlock);
    DECLARE_STATE_FUNCTIONS(SKIState, START_GAME);
    
private:
    
	void        setState(SKIState i_newState);
	bool        isInState(SKIState i_state) const;
    
    void        createGloveEffect();
    
private:
	StateMachine<SKIState>      m_SKIState;
    
    //PopAnimRigPtr                   m_handAnimation;
    ZombiePtr                         zombiePtr;
    RtWeakPtr<class Effect_PopAnim>   m_gloveEffect;
    pvztime_t                         m_gloveStartTime;
    SexyVector3                       m_gloveStartPos;
};


class SnakeIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(SnakeIntroProperties, StandardLevelIntroProperties, RtClass);
    
    SnakeIntroProperties()
    {
        SnakeStage = 1;
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return SnakeIntro::StaticGetClass();
	}
    
    int SnakeStage;
};

#endif /* defined(__PlantsVersusZombies2__IntrosSnake__) */
