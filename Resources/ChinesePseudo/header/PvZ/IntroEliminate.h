//
//  IntroEliminate.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-5-22.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroEliminate__
#define __PlantsVersusZombies2__IntroEliminate__

#include "StandardLevelIntro.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "Zombie.h"
#include "Plant.h"
#include "Collectable.h"
#include "Effect_BouncingArrow.h"

STATE_ENUM_BASE_BEGIN(ELIIState)
ELIIState_BlockIntro,
ELIIState_ColorIntro,
ELIIState_GamePlaying,
STATE_ENUM_END(ELIIState);

class EliminateIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(EliminateIntro, StandardLevelIntro, RtClass);
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;
    
	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnLevelEnded();
    void            OnGameplayStarted();
    
    DECLARE_STATE_FUNCTIONS(ELIIState, BlockIntro);
    DECLARE_STATE_FUNCTIONS(ELIIState, ColorIntro);
    DECLARE_STATE_FUNCTIONS(ELIIState, GamePlaying);
    
private:
    
    void        setState(ELIIState i_newState);
	bool        isInState(ELIIState i_state) const;
    
    Effect_BouncingArrow* addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void				  clearBouncingArrows();
    
    void        onNarrationBlockFinished();
    void        onNarrationColorFinished();
    
    void        onEliminateBlocked(int i_row,int i_col);
    void        onZombieSpawned(Zombie* i_zombie);
    
private:
	StateMachine<ELIIState>  m_ELIIState;
    
    std::vector<StandaloneEffectPtr>  m_bouncingArrows;
    
    ZombiePtr                         m_zombieColor;
    
    bool m_blockIntro;
    bool m_colorIntro;
    
    bool m_updateArrows;
};


class EliminateIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(EliminateIntroProperties, StandardLevelIntroProperties, RtClass);
    
    EliminateIntroProperties()
    {
        
    }
    
	virtual RtClass* GetModuleClass() const override
	{
		return EliminateIntro::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__IntroEliminate__) */
