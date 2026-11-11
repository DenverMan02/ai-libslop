//
//  PVZ2UIAwardScreen.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/23/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UIAwardScreen_h
#define PlantsVersusZombies2_PVZ2UIAwardScreen_h

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"

namespace ProfileUtils
{
	struct ChallengeStatusHolder;
}

enum AwardScreenState
{
	AWARDSCREENSTATE_INVALID = -1,
	AWARDSCREENSTATE_WaitingToStart,
	AWARDSCREENSTATE_FadeIn,
	AWARDSCREENSTATE_Showing,
	AWARDSCREENSTATE_ZombieNote,
	AWARDSCREENSTATE_BetweenScreens,
	AWARDSCREENSTATE_FadeOut,
	AWARDSCREENSTATE_DONE,
};

enum AwardScreenZombieNoteSequence
{
    AWARDSCREENNOTE_FadeIn,
    AWARDSCREENNOTE_WaitForConversation,
    AWARDSCREENNOTE_Conversation,
    AWARDSCREENNOTE_WaitForFadeOut,
    AWARDSCREENNOTE_FadeOut,
};

enum AwardScreenStarMode
{
	AWARDSCREENSTAR_Unawarded,
	AWARDSCREENSTAR_AwardedThisTime,
	AWARDSCREENSTAR_AwardedPreviously,
	AWARDSCREENSTAR_PreviewOnly
};

enum AwardScreenBackgroundType
{
	AWARDSCREEN_BG_NONE,
	AWARDSCREEN_BG_DARKENED,
	AWARDSCREEN_BG_GRASS,
	AWARDSCREEN_BG_SPACESPIRAL,
};

enum AwardScreenObjective
{
	AWARDSCREENOBJECTIVE_Unmet,
	AWARDSCREENOBJECTIVE_MetThisTime,
	AWARDSCREENOBJECTIVE_MetPreviously
};

using AwardScreenButtonFlags = int;

enum class AwardScreenButton : AwardScreenButtonFlags
{
	None           = 0,
	Continue       = 1 << 0,
	NextLevel      = 1 << 1,
	ExitToMap      = 1 << 2,
	ExitToMenu     = 1 << 3,
	NextChallenge  = 1 << 4,
	GoToZenGarden  = 1 << 5,
	GoToQuestMenu = 1 << 6
};

class PVZ2UIAwardScreen : public Sexy::Widget, public Sexy::ButtonListener
{
public:

	/// Local types

	enum ScreenType
	{
		AWARDSCREENTYPE_INVALID = -1,
		AWARDSCREENTYPE_PlantReward,
		AWARDSCREENTYPE_Collectable,
		AWARDSCREENTYPE_Prize,
		AWARDSCREENTYPE_Presents,
		AWARDSCREENTYPE_Stars,
		AWARDSCREENTYPE_Note,
		AWARDSCREENTYPE_Objective,
		AWARDSCREENTYPE_RewardObjectDisplay,
		AWARDSCREENTYPE_ChooseObjective,
		AWARDSCREENTYPE_UnchartedModeTips,
		AWARDSCREENTYPE_UnchartedModeDifficultyTips,
	};

	struct RewardObjectDisplayConfig
	{
		ImagePtr Image;
		SexyString Title;
		SexyString Header;
		SexyString Description;
	};
    
	struct AwardScreenConfig
	{
		AwardScreenConfig()
		{
			DialogWidth = -1;
			DialogHeight = -1;
			TopLabelHeight = -1;
		}

		AwardScreenConfig(int i_DialogWidth, int i_DialogHeight, int i_TopLabelHeight)

			: DialogWidth(i_DialogWidth), DialogHeight(i_DialogHeight), TopLabelHeight(i_TopLabelHeight)

		{}

		int DialogWidth;
		int DialogHeight;
		int TopLabelHeight;
	};

	struct ScreenEntry
	{
		ScreenEntry()
        {
			Type = AWARDSCREENTYPE_INVALID;
			StarCount = 0;
			ActiveStarIndex = 0;
			ActiveStarAwarded = AWARDSCREENSTAR_Unawarded;
			ActiveObjectiveAwarded = AWARDSCREENOBJECTIVE_Unmet;
			DialogSizeOverrideConfig = AwardScreenConfig(-1, -1, -1);

//PVZ2_CHINESE_BEGIN

			 UseTables			= true;

//PVZ2_CHINESE_END

		}

		ScreenType	Type;
		SexyString	Label;
		SexyString	HeaderLabel;
		SexyString	FooterLabel;

		// _PlantReward members
		RtWeakPtr<const class PlantType>		PlantType;
		RtWeakPtr<const class CollectableType>	CollectableType;

        // _Prize members
		ImagePtr	PrizeImage;
		// _Present members
		//PVZ2_CHINESE_BEGIN
		bool											  UseTables;
		//PVZ2_CHINESE_END
		std::vector<RtWeakPtr<const class PresentTable> > PresentTables;
		std::vector<RtWeakPtr<const class PresentType> > PresentContents;
        
        // _Stars
		int 					StarCount;					// Number of stars to show on the screen
		int 					ActiveStarIndex;			// Which star is the latest
		AwardScreenStarMode 	ActiveStarAwarded;			// Whether we were awarded that star on this playthrough
		std::vector<SexyString> ChallengeDescriptions;		// Challenge description text.
		std::vector<bool>		ChallengeFailureStates;		// If the challenge has failed or not.

		// _Bonus Objectives
		std::vector<SexyString> BonusChallengeDescriptions;	// Bonus objective description text.
		std::vector<bool>		BonusChallengeFailureStates; //If bonus objective has failed or not.

		// _Objectives
		AwardScreenObjective ActiveObjectiveAwarded; // Whether we were awarded that objective on this playthrough

		// _Note
		RtWeakPtr<const class CollectableType>	NoteType;
        
		// Dialog size override
		AwardScreenConfig		DialogSizeOverrideConfig;
		RewardObjectDisplayConfig   RewardDisplayConfig;

		// Uncharted Mode
		std::vector<SexyString> UnchartedModeTipsDescs;
		std::vector<SexyString> UnchartedModeDifficultyDescs;
	};

	PVZ2UIAwardScreen();
	virtual ~PVZ2UIAwardScreen();
    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void	DrawAll(Sexy::ModalFlags *theFlags, Sexy::Graphics *i_g);
    
    void			ShowAwardScreen();
    void			KillAwardScreen();

	// Setup functions
	void			AddPlantReward(RtWeakPtr<const class PlantType> i_plantType);
	void			AddPrizeReward(const SexyString& i_headerLabel, const SexyString& i_footerLabel, ImagePtr i_rewardImage);
	void			AddCollectableReward(RtWeakPtr<const class CollectableType> i_collectableType);
	void			AddPresentRewards(std::vector<RtWeakPtr<const class PresentTable> >& i_presentTables, std::vector<RtWeakPtr<const class PresentType> >& i_presentContents);

	void            AddJoustCoinReward(int i_coins);
	void            AddJoustGemReward(int i_gems);

	void 			AddJoustCHCoinReward(int i_coins);
	void            AddJoustCHGemReward(int i_gems);
	void            AddJoustCHMaterialReward(int i_id, int i_materials, bool isRift = false);
	void			AddJoustCHChestReward(int i_quantity);

	//PVZ2_CHINESE_BEGIN
	void 			AddPresentActivityRewards(std::vector<RtWeakPtr<const class PresentType> >& i_presentContents);

	//PVZ2_CHINESE_END
	void			AddNoteScreen(RtWeakPtr<const class CollectableType> i_noteType);
	void			AddStarScreenSingle(const ProfileUtils::ChallengeStatusHolder& i_challenge, AwardScreenStarMode i_awardedWhen);
	// TotalVisibleStars should include the current star, so it's always >= 1 and <= 3
	// All other parameters refer to the latest star, whether it's been completed or not
	void			AddStarScreenTriple(int i_totalVisibleStars, const ProfileUtils::ChallengeStatusHolder& i_challenge, AwardScreenStarMode i_awardedWhen);
	void			SetOnAwardSequenceCompleted(Delegate0 i_onCompleted);

	ScreenEntry* 	AddObjectiveScreen(const ProfileUtils::ChallengeStatusHolder& i_challenge, AwardScreenObjective i_awardedWhen);
	ScreenEntry* 	AddChooseObjectiveScreen(const ProfileUtils::ChallengeStatusHolder& i_challenge, AwardScreenObjective i_awardedWhen);
	ScreenEntry*	AddObjectiveScreen(const ProfileUtils::ChallengeStatusHolder& i_challenge, const ProfileUtils::ChallengeStatusHolder& i_bonusChallenge, AwardScreenObjective i_awardedWhen);

	void 			AddUnchartedModeTips();
	void 			AddUnchartedModeDifficultyTips(RtWeakPtr<const class LevelModifierDifficulty>  difficultyPtr);
    
    //Set Outter Headline Color
    void            SetHeadlineColor(Color m_color);

	// Do it!
	void			Start();
    
	// Getters / utility
	int				GetScreenCount() const;
    int              GetCurrentScreen() const;
	bool			GetReplayDesired() const;
    void			SetBackgroundType(const AwardScreenBackgroundType i_backgroundType);
	void			SetFadesOutOnEnd(const bool i_fadesOut);

	virtual void	MouseUp(int i_x, int i_y);
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void			SetButtonsToUseOnFinalScreen(AwardScreenButtonFlags i_buttons);
	void 			SetSpecialNeedNum(int i_num) { m_specialNeedNum = i_num; }
    
private:
	/// Private helper functions
	void			setState(AwardScreenState i_newState);
    void			advanceToNextScreen();
	void			removeCurrentScreen();
	void			setupScreen(const ScreenEntry& i_entry);
    
	//PVZ2_CHINESE_BEGIN
	void			refreshDialogToShareState();
	//PVZ2_CHINESE_END
    
	void			addCommonStarScreenInfo(ScreenEntry& i_screenEntry, const ProfileUtils::ChallengeStatusHolder& i_challenge);
	void			loadBackgroundGroups();
	void			deleteBackgroundGroups();

    /// Conversation support
	void			StartNoteConversation();
    void			onNarrationFinished();

    /// Reward Object Display support
    void            addRewardObjectDisplayScreen(ImagePtr i_image, const SexyString& i_title, const SexyString& i_header, const SexyString& i_description);

	/// Private member variables
	AwardScreenState				m_state;
	pvztime_t						m_stateStartTime;
	float							m_fadeAmount;
	PVZ2UIDialog*					m_dialog;
	SexyString						m_headerLabel;
	Delegate0						m_onCompleted;
	float							m_noteOpacity;
	bool							m_noteFadingOut;
	bool							m_presentsOpened;
	bool							m_replayDesired;
	AwardScreenBackgroundType		m_backgroundType;
	bool							m_fadesOutOnEnd;

	std::vector<ScreenEntry>		m_screens;
	int								m_screenIndex;
	int								m_specialNeedNum;

    AwardScreenZombieNoteSequence   m_noteStep;
    PrimeTextWidget*                m_tapToContinueTextWidget;
	AwardScreenConfig               m_currentDialogScreenConfig;
    Color                           m_headlineColor;
    PVZ2UIImageWidget* leafWidget;
    AwardScreenButtonFlags			m_finalScreenButtons;
    bool onNextStarClick();
    void addLeafHint();
};

#endif
