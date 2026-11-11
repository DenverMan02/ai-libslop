//
//  PVZGameState.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/28/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef PVZGameState_h
#define PVZGameState_h

#include "RtObject.h"
#include "MacroStateMachine.h"

STATE_ENUM_BASE_BEGIN(PVZGameStateLoadingState)
	GS_Loading,
	GS_Running,
STATE_ENUM_END(PVZGameStateLoadingState);

namespace Message
{
	void UILoadFinish();
}

class PVZGameState : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(PVZGameState, RtObject, Sexy::RtClass);
	
	PVZGameState();
	
	virtual bool IsFullyLoadedAndVisible() { return false; }
	
	virtual void Enter() {}
	virtual void Update() {}
	virtual void Exit() {}
	
	virtual std::string GetMusicStartEvent() { return ""; }
	virtual std::string GetMusicStopEvent() { return ""; }
};


class PVZHotUIGameState : public PVZGameState
{
public:
	RT_CLASS_DEFINE(PVZHotUIGameState, PVZGameState, Sexy::RtClass);
	
	PVZHotUIGameState();
	
	bool IsFullyLoadedAndVisible() override;
	
	virtual void Enter() override;
	void Update() override;
	void Exit() override;
	
	DECLARE_FSM_HANDLER_BASE(PVZGameStateLoadingState);
	void OnNotifyUILoadFinish();
protected:
	virtual RtClass* getTopHudControllerClass() = 0;
	virtual RtClass* getHotUIAdaptorClass() = 0;
	
	virtual void onHotUILoaded(class HotUIAdaptor* i_adaptor) {}
	
	Rect m_topHudRect;

private:
	void setupHotUI();
	void setupTopHud();
	
	DECLARE_FSM_STATE_VALUE(PVZGameStateLoadingState);
	class PVZGameStateTopHUDController* m_topHUD;
	class HotUIAdaptor* m_hotUI;
};


#endif /* PVZGameState_h */
