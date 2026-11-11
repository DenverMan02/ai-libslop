//
//  DangerRoomStatScreen.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 3/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomStatScreen__
#define __PlantsVersusZombies2__DangerRoomStatScreen__

#include <cstddef>
#include <vector>

#include "ButtonListener.h"
#include "DangerRoomInfo.h"
#include "PVZTypes.h"
#include "PlantType.h"
#include "PlatformAutodetect.h"
#include "PlayerInfo.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "SexyString.h"
#include "SexyVector.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "PlayerInfoLocalSaveData.h"
#include "ProfileUtils.h"
#include "core.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

class PVZ2UIButton;
class PVZ2UIDialog;
class PlantAnimRig;
class PlantNameMapper;
namespace Sexy {
class Graphics;
}  // namespace Sexy


class PVZ2UIScrollingWidget;
struct PacketRenderData;

class DangerRoomRewardCard
{
public:
	void ApplyReward(DangerRoomRewardType i_type, DangerRoomInfo& i_dangerRoomInfo);
	
public:
		
	DangerRoomRewardCard()
	{
		m_animRig = NULL;
		m_hitRect = Rect(0,0,0,0);
		m_selected = false;
		m_flipScale = 1.0f;
		m_isFlipped = false;
		m_isPurchasable = false;
		m_weight = 0;
	}
	virtual ~DangerRoomRewardCard();
	
	DangerRoomRewardInfo	m_info;
	PlantAnimRig*			m_animRig;
	Rect					m_hitRect;
	float					m_flipScale;
	bool					m_selected;
	bool					m_isFlipped;
	bool					m_isPurchasable;
	int32					m_weight;    
};

struct CashOutData
{
	int				MilestonesCashedOut;
	CoinCurrency	CashOutCoinAmount;
	int				LevelReached;
};

enum CardState
{
	CARD_IN_HAND,
	CARD_TRAVELING_TO_MIDDLE,
	CARD_FLIPPING,
	CARD_IN_MIDDLE,
	CARD_IN_MIDDLE_SELECTED,
	CARD_UNFLIPPING,
	CARD_TRAVELING_TO_HAND,
    CARD_IN_HAND_WAITING_FOR_RESET
};

struct FanCardData
{
	Sexy::SexyVector2		StartPosition;
	Sexy::SexyVector2		Position;
	float					StartRotation;
	float					Rotation;
	CardState				State;
	int						RewardID;
};

class DangerRoomSeedBank: public Widget
{
public:
	DangerRoomSeedBank()			{};
	virtual ~DangerRoomSeedBank()	{};
	
	void		AddSeed(PlantTypePtr i_plantType);
    void        RemoveSeed(PlantTypePtr i_plantType);
	void		Draw(Sexy::Graphics* i_g);
	
private:
	
	void		drawPacket(Sexy::Graphics* i_g, const PacketRenderData& i_renderData, const bool i_drawAsEmpty);
	
	std::vector<PlantTypePtr>	m_seedTypes;
};

class DangerRoomStatScreen : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{

	typedef Delegate0 ScreenCloseDelegate;
	typedef Delegate0 PauseDelegate;
	
public:

	enum DangerRoomDialogType
	{
		DR_Dialog_NewGame,
		DR_Dialog_WelcomeBack,
		DR_Dialog_Success,
		DR_Dialog_SuccessWithMilestone,
		DR_Dialog_Failure,
		DR_Dialog_GameOver,
	};
	
	enum Result
	{
		DR_ScreenResults_None,
		DR_ScreenResults_Start,
		DR_ScreenResults_BackToWorldMap,
	};

	enum TutorialState
	{
		DR_Tutorial_None,
		DR_Tutorial_WaitingOnCards,
		DR_Tutorial_DealingCards,
		DR_Tutorial_FlippingCards,
		DR_Tutorial_UnflippingCards,
		DR_Tutorial_ReturningCards,
		DR_Tutorial_FinalizingSelection,
		DR_Tutorial_DaveComplementingSelection,
		DR_Tutorial_WorldIntro,
		DR_Tutorial_SeedBankIntro,
		DR_Tutorial_SeedBankHighlight,
		DR_Tutorial_SeedBankOutro,
		DR_Tutorial_MowersIntro,
		DR_Tutorial_MowersHighlight,
		DR_Tutorial_PlantfoodHighlight,
		DR_Tutorial_PlantfoodOutro,
		DR_Tutorial_FadeIntoGame,
        DR_Tutorial_UnflippingCardsForReset,
        DR_Tutorial_ReturningCardsForReset
	};
    
    enum ButtonTypes
	{
		BUTTON_START,
		BUTTON_CONTINUE,
		BUTTON_BACKTOMAP,
		BUTTON_RETRY,
		BUTTON_CASHOUT,
		BUTTON_PICKED_REWARD,
		BUTTON_PURCHASE_EXTRA_CARD,
        BUTTON_SHOW_LEADERBOARD,
        BUTTON_RESET_REWARD,
	};
    
    enum COST_LIFE_TIMING
    {
        COST_IN_INIT,
        COST_IN_START,
    };
	
	DangerRoomStatScreen();
	virtual ~DangerRoomStatScreen();
	
	inline void		SetHasReachedMilestone(const bool i_hasReachedMilestone);
	inline void		SetHasReachedNewHighestLevel(const bool i_hasReachedNewHighestLevel);
	inline void		SetHasFailed(const bool i_hasFailed);
	inline void		SetIsCashingOut(const bool i_isCashingOut);
	inline void		SetIsPickingReward(const bool i_isPickingReward);
	inline void		SetDangerRoomInfo(const DangerRoomInfo& i_dangerRoomInfo);
	inline void		SetScreenCloseDelegate(ScreenCloseDelegate i_screenCloseDelegate);
	inline void		SetPauseDelegate(PauseDelegate i_pauseDelegate);

	inline TutorialState	GetTutorialState()	{ return m_tutorialState; };
	
	void			DrawScreenFade(Sexy::Graphics* i_g);
	inline bool		IsFading();
	
	void			HighlightRewards();
	void			HighlightPlantfoodCount();
	void			HighlightMowers();
	
	void			StopHighlight();

	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void	MouseDown(const int i_mouseX, const int i_mouseY, const int i_clickCount);
	virtual void	MouseUp(const int i_mouseX, const int i_mouseY, const int i_clickCount);
	virtual void	MouseDrag(const int i_mouseX, const int i_mouseY);
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);
	virtual void	ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget);
	virtual void	ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget);
	virtual bool    OnBackButtonPressed();

	void			Init();

	void			ResetRewardList();
	
	void			SetupRewards();
	void			SetupCashout();
    
    void			startDangerRoom();
    void            ConsumeLife();
    void            OnBackToMap();
    void            OnStartDangerRoomPlay(bool i_success);
    
    void            SetScreenResult(Result r) { m_screenResult = r; }
	
	inline DangerRoomStatScreen::Result		GetResult() const;

	void			ResetCards_Debug();


private:
        
    void            GameCenterCreateButtons();
    
	void			createFannedOutCards(const int i_cardCount);
	void			startFadeIn();
	void			startFadeOut();
	void			clearFade();

	void			dealCards();
    void            dealCardsForReset();
    void            ResetCurrentRewards();
	void			flipCards();
	void			readyCards();
	void			unflipCards();
    void            unflipCardsForReset();
	void			returnCards();
    void            returnCardsForReset();
	void			finalizeRewardAndStartDangerRoom();
	void			finalizeReward();
	
	void			setActiveCardsToState(const CardState i_newState);
	
	long			getSeed();
    long            getRepickSeed();
	
	void			removeAllOwnedWidgets();
	void			setUpProgressDialog();
	void			setUpCardSelection();
	
	bool isMowerTutorial(int i_hitCount);
	bool isPlantFoodTutorial(int i_hitCount);
	
	bool			onPauseButtonPressed();
	
	void			onFirstNarrativeCompleted();
	void			onTutorialWrapupNarrativeCompleted();
	void			onTutorialNarrativeCompleted();
	void			onTutorialNarrativeTutorialMarker();
	void			onSuccessNarrativeCompleted();
	void			onSuccessNarrativeTutorialMarker();
    
    bool            onCardSelectedOrUnselected(bool i_selected);
	
	pvztime_t							m_tutorialMarkerLastHit;
	pvztime_t							m_tutorialPauseDuration;
	int									m_tutorialMarkerHitCount;
	TutorialState						m_tutorialState;
	pvztime_t							m_fadeInTime;
	pvztime_t							m_fadeOutTime;

	bool								m_hasReachedNewMilestone;
	bool								m_hasReachedNewHighestLevel;
	bool								m_hasFailed;
	bool								m_isCashingOut;
	bool								m_isPickingReward;
	
	int									m_milestonesReached;
	int									m_nextMilestoneAt;
    COST_LIFE_TIMING                    m_lifecost;
	
	DangerRoomStatScreen::Result		m_screenResult;
	
	DangerRoomInfo						m_dangerRoomInfo;
	
	ScreenCloseDelegate					m_onScreenClosed;
	PauseDelegate						m_onPauseButtonPressed;
	
	std::vector<DangerRoomRewardCard*>	m_rewardList;
	SexyString							m_rewardSelectedDescription;
	int									m_rewardDescriptionWidth;
	
	const class DangerRoomPropertySheet* m_dangerRoomProps;
	CashOutData							m_cashOutData;
	
	DangerRoomSeedBank*					m_seedBank;
	PVZ2UIScrollingWidget*				m_scrollingWidget;
	PVZ2UIButton*						m_buttonGameCenter;
	PVZ2UIButton*						m_pickRewardButton;
	PVZ2UIButton*						m_purchaseExtraCardButton;
    PVZ2UIButton*						m_startButton;
    PVZ2UIButton*						m_resetButton;
	PVZ2UIDialog*						m_dialog;
	SexyString							m_dialogLabel;
	
	std::vector<FanCardData>			m_fanCards;
	PlantNameMapper&					m_plantNameMapper;
	SexyVector2							m_coinWidgetOriginalOffset;
    
    int                                 m_currentNumberSelected;
    
    bool                                m_hasRepicked;
    int									m_totalPicks;
};

inline void DangerRoomStatScreen::SetHasReachedMilestone(const bool i_hasReachedMilestone)
{
	m_hasReachedNewMilestone = i_hasReachedMilestone;
}

inline void DangerRoomStatScreen::SetHasReachedNewHighestLevel(const bool i_hasReachedNewHighestLevel)
{
	m_hasReachedNewHighestLevel = i_hasReachedNewHighestLevel;
}

inline void DangerRoomStatScreen::SetHasFailed(const bool i_hasFailed)
{
	m_hasFailed = i_hasFailed;
	
	//reset random reward seed
	if (i_hasFailed)
	{
		LocalProfileSaveData::SetDangerRoomRandomSeed(ProfileUtils::Profile(), PVZ_RealT());
        LocalProfileSaveData::SetDangerRoomRepickSeed(ProfileUtils::Profile(), PVZ_RealT());
	}
}

inline void DangerRoomStatScreen::SetIsCashingOut(const bool i_isCashingOut)
{
	m_isCashingOut = i_isCashingOut;
}

inline void DangerRoomStatScreen::SetIsPickingReward(const bool i_isPickingReward)
{
	m_isPickingReward = i_isPickingReward;
}

inline void DangerRoomStatScreen::SetDangerRoomInfo(const DangerRoomInfo& i_dangerRoomInfo)
{
	m_dangerRoomInfo = i_dangerRoomInfo;
}

inline void DangerRoomStatScreen::SetScreenCloseDelegate(ScreenCloseDelegate i_screenCloseDelegate)
{
	m_onScreenClosed = i_screenCloseDelegate;
}

inline void DangerRoomStatScreen::SetPauseDelegate(PauseDelegate i_pauseDelegate)
{
	m_onPauseButtonPressed = i_pauseDelegate;
}

inline DangerRoomStatScreen::Result DangerRoomStatScreen::GetResult() const
{
	return m_screenResult;
}

inline bool DangerRoomStatScreen::IsFading()
{
	return (m_fadeInTime < PVZ_EOT() ||
			m_fadeOutTime < PVZ_EOT());
}

#endif /* defined(__PlantsVersusZombies2__DangerRoomStatScreen__) */
