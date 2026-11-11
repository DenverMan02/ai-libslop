#ifndef __CRAZYNPC_H__
#define __CRAZYNPC_H__

#include "core.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "PopAnimRig.h"
#include "CrazyNPCManager.h"
#include "Renderable.h"

class LawnApp;
class PopAnimRig;

STATE_ENUM_BASE_BEGIN(CrazyNPCState)
	CNPC_Loading,					// Loading assets
	CNPC_Initializing,				// Assets are loaded, setting up the NPC
	CNPC_Ready,						// NPC is ready to be used (off screen)
	CNPC_State_Entering,			// Entering the screen
	CNPC_State_Leaving,				// Exiting the screen
	CNPC_State_Idle,				// Idling in place
	CNPC_State_Talking,				// Talking
	CNPC_State_HoldingEnter,		// Pull out something to hold
	CNPC_State_HoldingIdle,			// Holding something while idle
	CNPC_State_HoldingTalking,		// Holding something while talking
	CNPC_State_HoldingEat,			// Eats the item they are holding and enters normal idle
	CNPC_Dead,						// NPC is dying (unloading and terminating)
STATE_ENUM_END(CrazyNPCState)

enum CrazyNPCMood
{
	CNPC_Mood_General,		// 'SAY' or 'GENERAL' or 'NORMAL'
	CNPC_Mood_Excited,		// 'EXCITED'
	CNPC_Mood_Playful,		// 'PLAYFUL'
	CNPC_Mood_Tired,		// 'TIRED'
	CNPC_Mood_Shout,		// 'SHOUT' or 'CRAZY'
	CNPC_Mood_Special1,		//  Special dialog strings - these play very specific audio that has been designed for
	CNPC_Mood_Special2,		//		specific moments. Length is not specifiable on these
	CNPC_Mood_Special3,
	CNPC_Mood_Special4,
	CNPC_Mood_Special5,
	CNPC_Mood_Special6,
	CNPC_Mood_Special7,
	CNPC_Mood_Special8,
	CNPC_Mood_Special9,
	CNPC_Mood_Special10,
	CNPC_Mood_Special11,
	CNPC_Mood_Special12,
	CNPC_Mood_Special13,
	CNPC_Mood_Special14,
	CNPC_Mood_Special15,
	CNPC_Mood_Special16,
	CNPC_Mood_Special17,
};

enum CrazyNPCLineLength
{
	CNPCLL_Automatic,		// Default value, if no override specified
	CNPCLL_Short,			// 'SHORT'
	CNPCLL_Medium,			// 'MED'
	CNPCLL_Long				// 'LONG'
};

// -- Description
// Implements an animated dialog portrait.
// Contains functionality for drawing dialog text and analyzing for vocal sounds.
//
class CrazyNPC: public RtObject, public Renderable
{

public:	

	RT_CLASS_DEFINE(CrazyNPC, RtObject, RtClass);
	
	CrazyNPC();
	virtual ~CrazyNPC();

	// Public Interface (Inheritable)

    virtual void							Init();
	virtual void							Update();
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							Terminate();

	// Public Interface (Core)

	void									SetNPCSheet(const NPCDataSheetPtr i_sheetPtr);

	inline void								SetNPCMood(const CrazyNPCMood& i_mood);
	inline const CrazyNPCMood&				GetNPCMood() const;
	inline const std::string&				GetNPCName() const;
	inline void								SetForceDialogLength(CrazyNPCLineLength i_length);
	inline CrazyNPCLineLength				GetForceDialogLength() const;
	inline const bool&						IsInitialized() const;
	inline void								SetDialogMessage(const SexyString& i_dialogMessage);
	
	// Resource management
	void									PrepForLoading();
	void									StartLoad();
	bool									IsLoaded();
	bool									IsLoadComplete();
	void									CompleteLoad();
	void									UnloadResources();

	// State/Appearance Switching
	void									Enter();
	void									Leave();
	void									Die();
	void									StartEating(const std::string& i_itemToEat);
	void									StartTalking(const SexyString& i_message);
	void									StopTalking();
	void									StartHolding(const std::string& i_itemToHold);
	void									StopHolding();
	inline const bool						IsTalking();
	inline const bool						IsLeaving();
	inline const bool						IsEntering();
	inline const bool						IsDead();
	inline const bool						IsHoldingItem();

	void									SetDescriptionMesh();

protected:

	// Protected Interface (Inheritable)
	
	// Resource management
	virtual void							initLoadingResourcesGroupList();
	virtual void							addToLoadingResourcesGroupList(const std::string& i_groupName);
	
	// State management
	virtual void							setState(const CrazyNPCState i_newState);
	
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Loading);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Initializing);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Ready);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Entering);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Leaving);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Idle);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Talking);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, HoldingEnter);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, HoldingIdle);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, HoldingTalking);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, HoldingEat);
	DECLARE_STATE_FUNCTIONS(CrazyNPCState, Dead);

	// Protected Interface (Core)

	void									pickAndPlayTalkingAnimation();
	void									pickAndPlayTalkingVO(CrazyNPCMood i_mood, CrazyNPCLineLength i_dialogLength);
	
	void									drawSpeechBubbleStyle(Graphics* i_g);
	void									drawTextBannerStyle(Graphics* i_g);
	void									drawTextTopBannerStyle(Graphics* i_g);

	// Event handlers
	void									onEnteringAnimFinished(const std::string& i_animName);
	void									onLeavingAnimFinished(const std::string& i_animName);
	void									onCrazyTalkingAnimFinished(const std::string& i_animName);
	void									onYellTalkingAnimFinished(const std::string& i_animName);
	void									onScreamTalkingAnimFinished(const std::string& i_animName);
	void									onHoldingEnteringAnimFinished(const std::string& i_animName);
	void									onHoldingTalkingAnimFinished(const std::string& i_animName);
	void									onHoldingEatAnimFinished(const std::string& i_animName);
	void									onTalkAnimFinished(const std::string& i_animName);
	
	// State machine
	void									updateStateMachine();
	void									setStateHelper(const StateDefinition<CrazyNPCState>& i_newStateDefinition);
	CrazyNPCState							getState() const;
    bool									isInState(uint32 i_state) const;
	inline const pvztime_t					getStateEnterTime();
	inline void								setStateEnterTime(const pvztime_t i_newTime);
	
private:
    
	SexyString								m_messageText;			// Current dialog text being displayed
	PopAnimRig*								m_popAnimRig;			// PopAnimRig to use for the NPC
	CrazyNPCMood							m_mood;					// Current mood of the NPC
	CrazyNPCLineLength						m_nextLineLength;		// Force the length of our animation and audio to a certain length
	NPCDataSheetPtr							m_sheetPtr;				// NPC data sheet
	PopAnimRig::AnimStoppedDelegate			m_parentDelegate;		// the owner of the CrazyNPC
	pvztime_t								m_stateEnterTime;		// Time the state was entered
	StateMachine<CrazyNPCState>				m_stateMachine;			// Our state machine
	std::vector<std::string>				m_loadingResourcesList;	// List of all resources this NPC is using
	bool									m_initialized;			// States if we're initialized
	std::string								m_holdingItem;			// Item being help (is linked with animations)
};

namespace Message
{
	void NPCFinishedEntering(CrazyNPC* i_npc);
	void NPCFinishedExiting(CrazyNPC* i_npc);
}

inline void CrazyNPC::SetNPCMood(const CrazyNPCMood& i_mood)
{
	m_mood = i_mood;
}

inline const CrazyNPCMood& CrazyNPC::GetNPCMood() const
{
	return m_mood;
}

inline const std::string& CrazyNPC::GetNPCName() const
{
	return m_sheetPtr->Name;
}

inline void CrazyNPC::SetForceDialogLength(CrazyNPCLineLength i_length)
{
	m_nextLineLength = i_length;
}

inline CrazyNPCLineLength CrazyNPC::GetForceDialogLength() const
{
	return m_nextLineLength;
}

inline const bool& CrazyNPC::IsInitialized() const
{
	return m_initialized;
}

inline void CrazyNPC::SetDialogMessage(const SexyString& i_dialogMessage)
{
	m_messageText = i_dialogMessage;
}

inline const pvztime_t CrazyNPC::getStateEnterTime()
{
	return m_stateEnterTime;
}

inline void CrazyNPC::setStateEnterTime(const pvztime_t i_newTime)
{
	m_stateEnterTime = i_newTime;
}

inline const bool CrazyNPC::IsTalking()
{
	return (getState() == CNPC_State_Talking ||
			getState() == CNPC_State_HoldingTalking);
}

inline const bool CrazyNPC::IsLeaving()
{
	return (getState() == CNPC_State_Leaving ||
			getState() == CNPC_State_HoldingEat);
}

inline const bool CrazyNPC::IsEntering()
{
	return (getState() == CNPC_State_Entering ||
			getState() == CNPC_State_HoldingEnter);
}

// TODO: MF - Add a CrazyNPC::IsInNonInteractiveState() and move
// the HoldingEnter and HoldingEat out of IsLeaving/IsEntering.

inline const bool CrazyNPC::IsDead()
{
	return (getState() == CNPC_Dead);
}

inline const bool CrazyNPC::IsHoldingItem()
{
	return (getState() == CNPC_State_HoldingIdle ||
			getState() == CNPC_State_HoldingTalking);
}

typedef RtWeakPtr<CrazyNPC> CrazyNPCPtr;

#endif // __CRAZYNPC_H__
