//
//  FiregourdTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 12/19/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FiregourdTutorialIntro_h
#define PlantsVersusZombies2_FiregourdTutorialIntro_h

#include "StandardLevelIntro.h"
#include "StateMachine.h"

STATE_ENUM_BASE_BEGIN(FTIState)
	FTIState_START_TUTORIAL,
	FTIState_DAVE_INTRO,
	FTIState_ARMRACKS,
	FTIState_EPILOG,
STATE_ENUM_END(FTIState);

//forward declaration
class AnimationMgr;
class Effect_BouncingArrow;
class PlantFireGourd;
class GridItemArmrack;
class PlantFireGourd;

class FiregourdTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(FiregourdTutorialIntro, StandardLevelIntro, RtClass);

protected:
	virtual void	initializeModule() override;
	virtual void	registerForEvents() override;

	void			OnIntroStarted();
	void 			OnUpdate();
	void 			OnNarrationFinished();
	void 			OnLevelEnded();
	void 			OnFiregourdHit(PlantFireGourd* i_firegourd);

	DECLARE_STATE_FUNCTIONS(FTIState, START_TUTORIAL);
	DECLARE_STATE_FUNCTIONS(FTIState, DAVE_INTRO);
	DECLARE_STATE_FUNCTIONS(FTIState, ARMRACKS);
	DECLARE_STATE_FUNCTIONS(FTIState, EPILOG);

private:
	void        setState(FTIState i_newState);
	bool        isInState(FTIState i_state) const;
    
    int32 getFiregourdTutorialStateSerialization();
    void setFiregourdTutorialStateSerialization(int32 i_state);

	void 		startGame();
	void		setupDaveProlog();
	void 		introduceDave();
	void 		setupArmracks();
	void 		setupWaitForHitFiregourd();

	RtWeakPtr<AnimationMgr>   					m_animationMgr;
	RtWeakPtr<Effect_BouncingArrow>				m_arrow;
	std::vector<RtWeakPtr<GridItemArmrack> >	m_armracks;

	StateMachine<FTIState> 						m_FTIState;
};

class FiregourdTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(FiregourdTutorialIntroProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return FiregourdTutorialIntro::StaticGetClass();
	}
};

#endif
