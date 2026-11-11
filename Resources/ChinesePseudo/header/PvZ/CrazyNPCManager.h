//
//  CrazyNPCManager.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_CrazyNPCManager_h
#define PlantsVersusZombies2_CrazyNPCManager_h

#include "core.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "GameNotify.h"

static float k_delayPerNarrative = 0.4f;

enum NPCTextType
{
	NPCTEXT_SPEECHBUBBLE,			// Full speech bubble from the character's mouth
	NPCTEXT_BANNER,					// Simple text banner similar to advice text
	NPCTEXT_TOPBANNER,				// Simple text banner similar to advice text, but for the top of the screen
};

enum NPCFontType
{
	NPCFONT_BRIANNE,
	NPCFONT_PICO,
	NPCFONT_ASHLEY,
};

struct NPCDataSheet: public Sexy::RtObject
{
	RT_CLASS_DEFINE(NPCDataSheet, Sexy::RtObject, RtClass);
	
	NPCDataSheet()
	{
		PopAnim = "";
		SoundBankPrefix = "";
		LoadResourceGroups.clear();
		ArtCornerPosition = Sexy::Point(0,0);
		ArtIsMirrored = false;
		DialogStyle = NPCTEXT_SPEECHBUBBLE;
        FontType = NPCFONT_BRIANNE;
	}
	
	std::string					PopAnim;		// If set, we use an animated talking fullscreen character
	std::string					StaticImage;	// If set, we use a simple static image icon
	
	NPCTextType					DialogStyle;
    NPCFontType                 FontType;
	
	std::string					SoundBankPrefix;
	std::string					Name;
	Sexy::Point					ArtCornerPosition;
	bool						ArtIsMirrored;
	std::vector<std::string>	LoadResourceGroups;
};

enum HeroShotType
{
	HEROSHOT_NONE,
//	HEROSHOT_TACO,
//	HEROSHOT_WINNIE,
};

enum ScreenFadeType
{
	FADE_NONE,
	FADE_IN,
	FADE_OUT,
};

STATE_ENUM_BASE_BEGIN(CrazyNPCManagerState)
	CNM_Loading,				// Loading assets
	CNM_Initializing,			// Assets are loaded, initializing NPCs
	CNM_Ready,					// Everything is in a ready state (can interact with it)
	CNM_Paused,					// Everything is paused. Basically frozen in time and non-interactable
	CNM_HeroShotLoading,		// Loading assets
	CNM_HeroShotReady,			// Everything is in a ready state (can interact with it)
	CNM_HeroShotUnloading,		// Unloading the hero shot and going back to ready
	CNM_Finished,				// Narration is finished. Just waiting to be spun up again.
STATE_ENUM_END(CrazyNPCManagerState)


//class RenderItem;
class CrazyNPC;

// -- Description
// Manager for character dialog narration.
//
class CrazyNPCManager :  public Widget
{
	
public:
	RT_CLASS_DEFINE(CrazyNPCManager, RtObject, RtClass) {}

	typedef Delegate0 NarrativeFinishedDelegate;
	
	CrazyNPCManager();
	virtual ~CrazyNPCManager();
	
	// Public Interface (Inheritable)
	
	virtual void							Draw(Graphics* i_g) override;
	virtual void							TouchBegan(const Sexy::Touch& i_touch) override;
	virtual void							Update() override;
	
	bool									IsNarrationActive() const;
	
	// Public Interface (Core)

	void									StartFadeIn();
	void									StartFadeOut();
	inline void								SetSkipAllNarration(bool i_skipAll);
	void									ContinueNarration();
	void									SetNarrativePaused(bool i_paused);
	
	// Narrative management
	void									StartNarrativeID(const std::string& i_narrativeID, NarrativeFinishedDelegate i_onNarrativeFinished, const std::string& replaceContent = "");
	void									SetTutorialMarkerDelegate(Delegate0 i_onTutorialMarker);
	void									ForceEndNarrative();
    
    void StartNarrativeIDWithLUA(const std::string& i_narrativeID, int i_luaHandler, const std::string& replaceContent = "");
	
	// Resource management
	void									PrepForLoading();
	void									StartLoad();
	bool									IsLoaded();
	void									CompleteLoad();
	void									UnloadResources();
    
    void									FinisAllTalking();
    
    int32                                   GetCurrentNarrativeID() { return m_currentNarrativeID; }
    
    void                                    MakeSureNotInModel();
    void			clearCurrentNarrativeData();	
protected:
	
	// Protected Interface (Inheritable)

	// Resource management
	virtual void							initLoadingResourcesGroupList();
	virtual void							addToLoadingResourcesGroupList(const std::string& i_groupName);

	// State machine
	virtual void							setState(const CrazyNPCManagerState& i_newState);
	
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, Loading);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, Initializing);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, Ready);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, Paused);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, Finished);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, HeroShotLoading);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, HeroShotReady);
	DECLARE_STATE_FUNCTIONS(CrazyNPCManagerState, HeroShotUnloading);

	// Protected Interface (Core)
	
	// Narrative management
	bool									canAdvanceNarrative();
	bool									advanceNarrative();
	void									parseNarrativeCommands();
	void									parseSingleNarrativeCommand(const SexyString& i_command);
	void									parseSpecialNarrativeCommand(const std::string& i_command);
	void									setNarrativeID(int i_narrativeIndex);
	SexyString								getNarrativeText(int i_narrativeIndex);
	void									talkNarrative(const SexyString& i_message);
	void									finishNarrative();
	void									stopSound();
	inline void								CalculateNextNarrativeAdvanceTime();
	inline bool								IsInHeroShot();
	void									stopAllTalking();
	
	// Resource management
	bool									checkLoadComplete();
	void									startHeroShot(HeroShotType i_heroShot);
	void									endHeroShot();
	CrazyNPC*								createNPC(const std::string& i_npcName);
	void									killAllNPCs();
	void									killDeadNPCs();
	RtWeakPtr<const NPCDataSheet>			getNPCDataSheet(const RtName i_sheetName);
	RtWeakPtr<const NPCDataSheet>			getNPCDataSheetByNPCName(const std::string& i_npcName);
	CrazyNPC*								getActiveNPCByName(const std::string& i_npcName);
	
	// Events
	void									onEventNPCFinishedEntering(CrazyNPC* i_npc);
	void									onEventNPCFinishedExiting(CrazyNPC* i_npcn);

	// State machine
	void									updateStateMachine();
	void									setStateHelper(const StateDefinition<CrazyNPCManagerState>& i_newStateDefinition);
	CrazyNPCManagerState					getState() const;
    bool									isInState(const uint32& i_state) const;
	inline const pvztime_t					getStateEnterTime() const;
	inline void								setStateEnterTime(const pvztime_t i_newTime);
    
    void                                    onNarrativeFinishedWithLUA();
private:
	
	// Private Interface
	
	// Private Members (serialized)

	// Private Member (not serialized)
	std::vector<CrazyNPC*>					m_activeNPCs;
	std::vector<CrazyNPC*>					m_deadNPCs;
	
	SexyString								m_narrativePrefix;
	
	int32									m_currentNarrativeID;
    std::string                             m_replaceText;
	SexyString								m_narrativeText;
	SexyString								m_currentScriptText;
	CrazyNPC*								m_currentNPC;
	NarrativeFinishedDelegate				m_onNarrativeFinishedDelegate;
	Delegate0								m_onTutorialMarkerDelegate;
	pvztime_t								m_nextNarrativeAdvanceTime;
	HeroShotType							m_activeHeroShot;
	std::string								m_activeHeroShotResGroup;
	pvztime_t								m_heroShotFadeTimeEnd;
	pvztime_t								m_heroShotFadeTimeStart;
	ScreenFadeType							m_heroShotFadeType;
	bool									m_skipAllNarration;
	pvztime_t								m_skipNarrationTime;
	bool									m_haltNarration;
	bool									m_queueAdvanceNarrative;
	bool									m_isDialogMusicPlaying;

	pvztime_t								m_stateEnterTime;
	StateMachine<CrazyNPCManagerState>		m_stateMachine;
	std::vector<std::string>				m_loadingResourcesList;
    
    bool                                    m_bAddModal;
    
    int                                     m_luaHandler;
    std::string                             m_narrativeID;
	
};

namespace Message
{
	void NPCSpawnFakeCoins();
    void NPCDrawed(Graphics* i_g);
}

inline const pvztime_t CrazyNPCManager::getStateEnterTime() const
{
	return m_stateEnterTime;
}

inline void CrazyNPCManager::setStateEnterTime(const pvztime_t i_newTime)
{
	m_stateEnterTime = i_newTime;
}

inline void CrazyNPCManager::CalculateNextNarrativeAdvanceTime()
{
	m_nextNarrativeAdvanceTime = PVZ_T() + k_delayPerNarrative;
}

inline bool CrazyNPCManager::IsInHeroShot()
{
	return (getState() == CNM_HeroShotLoading ||
			getState() == CNM_HeroShotReady ||
			getState() == CNM_HeroShotUnloading);
}

inline void CrazyNPCManager::SetSkipAllNarration(bool i_skipAll)
{
	m_skipAllNarration = i_skipAll;
}

typedef RtWeakPtr<const NPCDataSheet> NPCDataSheetPtr;

#endif
