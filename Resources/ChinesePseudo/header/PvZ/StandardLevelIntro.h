//
//  StandardLevelIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StandardLevelIntro_h
#define PlantsVersusZombies2_StandardLevelIntro_h

#include "IntroModule.h"
#include "PVZTypes.h"

class ShowAdvice;
class PlayPAM;
class AnimationMgr;

namespace Message
{
	void IntroNarrativeStarted();
    void AddAnimationEvent(AnimationMgr* mgr, pvztime_t* end);
};

enum PreSeedchooserFlowType
{
	PRE_SEEDCHOOSER_NONE,
	PRE_SEEDCHOOSER_RIFT
};

class StandardLevelIntro : public IntroModule
{
public:
	RT_CLASS_DEFINE(StandardLevelIntro, IntroModule, RtClass);

	enum PanType
	{
		PAN_HOUSE_TO_BOARD_EDGE,
		PAN_GAME_START_TO_BOARD_EDGE,
		PAN_BOARD_EDGE_TO_ZOMBIES,
		PAN_BOARD_EDGE_TO_GAME_START,
		PAN_ZOMBIES_TO_GAME_START,
		PAN_GAME_START_TO_ZOMBIES,
        PAN_HOUSE_TO_ZOMBIES,
        PAN_HOUSE_TO_GAME_START,
        PAN_HOUSE_TO_GAME_START_SPECIAL,
        PAN_BOARD_EDGE_TO_GAME_START_SPECIAL,
        PAN_ZOMBIES_TO_GAME_START_SPECIAL
	};
	
	static void			GetPanLocations(PanType i_panType, int& o_posStart, int& o_posEnd);
	static ShowAdvice*	CreateLevelNameStringAdvice();
	
    virtual void OnIntroDone() {}
protected:
	virtual void		initializeModule() override;
	virtual void		registerForEvents() override;
    void            initBoardEntities();
	
	// If you derive from this, you may override this to return 'true' and then call
	// 'startStandardIntro()' yourself when you're ready for the board pan, etc.
	virtual bool		manualIntroStart() const;
	virtual bool		suppressReadySetGo() const;
	
	virtual void		bringUpSeedChooser();
	
	// Begins board pan etc.
    void				startStandardIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE);
    void				startStandardIntroWithoutNarration(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE);

    void				startPreSeedchooserIntro(PreSeedchooserFlowType i_preSeedchooserFlow);
    void				onPreSeedchooserIntroComplete();
	
	// Called when our sequence is finished
	// Will notify the board to start the level if not overridden by a child class
	virtual void		onStandardIntroComplete();

	bool				isFirstPlaythrough() const;

	bool				hasNarration();
	virtual void		startNarration(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE);
	virtual void		startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false);
	
    void				setupIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false);

	virtual void		onLoadComplete();

	virtual void		onFirstNarrationFinished();

	void				startPreview();

private:

	bool				canInit();
	void				bringUpPowerupChooser();
	bool 				checkWhetherCukeShouldBeUnlocked() const;

	void				onStarPreviewComplete();

	void				startStarPreview(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE);

	PanType				m_cachedStartingPanType;
};

class TutorialEntity
{
public:
    std::string         TypeName;
    BoardEntityTypeFlag EntityType;
    int32               Row = 0;
    int32               Column = 0;
    bool                PlantFood = false;
};

class StandardLevelIntroProperties : public IntroModuleProperties
{
public:
	RT_CLASS_DEFINE(StandardLevelIntroProperties, IntroModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return StandardLevelIntro::StaticGetClass();
	}
	
	StandardLevelIntroProperties()
	{
		PanStartOffset = 78.f;
		PanEndOffset = 468.f;
		PanRightDuration = 2.f;
		PanLeftDuration = 2.5f;
		NarrationID = -1;
		SubsequentPlayNarrationID = -1;
		SkipShowingStreet = false;
		PreSeedchooserFlow = PRE_SEEDCHOOSER_NONE;
	}
	
public:
	float	PanStartOffset;
	float	PanEndOffset;
	float	PanRightDuration;
	float	PanLeftDuration;
	int		NarrationID;
	int		SubsequentPlayNarrationID;
    std::vector<TutorialEntity> m_TutorialEntities;
    bool SkipShowingStreet;
    PreSeedchooserFlowType PreSeedchooserFlow;

};

#endif
