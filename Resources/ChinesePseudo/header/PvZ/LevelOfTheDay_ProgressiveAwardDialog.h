//
//  LevelOfTheDay_ProgressiveAwardDialog.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 10/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDay_ProgressiveAwardDialog__
#define __PlantsVersusZombies2__LevelOfTheDay_ProgressiveAwardDialog__

#include <string>
#include <vector>

#include "ButtonListener.h"
#include "PinataRewardDrawer.h"
#include "Point.h"
#include "Rect.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "SexyString.h"
#include "TimeMgr.h"
#include "Widget.h"
#include "core.h"

namespace Sexy {
class Graphics;
class Image;
}  // namespace Sexy

enum LODBoxTransitionState
{
	PVZ_BEGIN_ENUM(LODBoxTransitionState_),
	LODBTS_Incomplete,
	LODBTS_Complete,
	LODBTS_WaitingToTransition,
	LODBTS_Transitioning,
	LODBTS_WaitingToTransitionGoalMet,
	LODBTS_CompleteGoalMet,
	PVZ_END_ENUM(LODBoxTransitionState_),
};

enum LODBoxState
{
	PVZ_BEGIN_ENUM(LODBoxState_),
	LODBS_Initializing,
	LODBS_SlideIn,
	LODBS_SlideOut,
	LODBS_Sliding,
	LODBS_Ready,
	PVZ_END_ENUM(LODBoxState_),
};

enum LODProgressiveButtons
{
	PROGRESSIVEBUTTON_Continue,
};

class LevelOfTheDay_ProgressiveAwardDialog : public Sexy::Widget, public ButtonListener
{
public:
	
	LevelOfTheDay_ProgressiveAwardDialog();
	~LevelOfTheDay_ProgressiveAwardDialog();

	void Update() override;
	void Draw(Sexy::Graphics* i_g) override;
	
	void ButtonDepress(int i_id) override;
	
	void DoFinalSequence();
	
	void OnProgressiveGoalMet();
	void OnProgressiveBoxesSlidOut();
	
	void RegisterCompletionCallback(Sexy::Delegate0 i_onCompleted) {m_onCompleteDelegate = i_onCompleted;}
	void DisableButtonAndUseTimeout(pvztime_t i_time) { m_timeout = i_time; m_disableButton = true; }
	
private:
	void layoutWidget();
	void layoutHeaderAndBoxes();
	void layoutFooter();
	void layoutButtons();
	
	class LevelOfTheDay_ProgressWidget* m_boxes;
	class PVZ2UIButton*					m_continueBtn;
	Sexy::Delegate0						m_onCompleteDelegate;
	bool 								m_disableButton;
	pvztime_t							m_timeout;
	pvztime_t							m_timeoutStartTime;
};

class LevelOfTheDay_LargePinataWidget : public Sexy::Widget
{
public:
	LevelOfTheDay_LargePinataWidget(Widget* i_topContainerWidget);
	virtual ~LevelOfTheDay_LargePinataWidget();
	
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void MouseUp(int x, int y);
	
private:
	void layoutWidget();
	
	void onPinataEnterStop(const std::string& i_anim);
	void onPinataHitStop(const std::string& i_anim);
	void setDamageStateIndex(int i_index);
	int  getDamageStateCount();
    PopAnim* getPinataAnimation();
    int getPinataHitsMax();
    const std::string& getSoundBreak(bool i_isLastBox, bool i_isConsolationReward);
    const std::string& getSoundDrop(bool i_isLastBox);
    
	void onNarrationFinished();
	
	class PopAnimRigRectDrawer*					m_zombieRig;
	int											m_hitCnt;
	LevelOfTheDay_ProgressiveAwardDialog*		m_topContainerWidget;
	PinataRewardDrawer							m_rewardDrawer;
	
	Effect_FloatingText*						m_floatingText;
};

class LevelOfTheDay_ProgressBoxWidget : public Sexy::Widget
{
public:
	LevelOfTheDay_ProgressBoxWidget(Rect i_extentsint, int i_boxNum, Widget* i_topContainerWidget);
	
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Update();
	
	void	StartCompleteTransition();
	const bool IsLastBox() const;
	
private:
	void layoutWidget();
	
	void setTransitionState(LODBoxTransitionState i_state);
	
    Image* getProgressImage();
    
    LODBoxTransitionState					m_transitionState;
	pvztime_t								m_transitionStartTime;
	Image*									m_image;
	Rect									m_scaledImageRect;
	Rect									m_scaledTextRect;
	SexyString								m_boxText;
	int										m_boxNum;
	LevelOfTheDay_ProgressiveAwardDialog*	m_topContainerWidget;
};

class LevelOfTheDay_ProgressWidget : public Sexy::Widget
{
public:
	LevelOfTheDay_ProgressWidget(Widget* i_topContainerWidget);
	~LevelOfTheDay_ProgressWidget();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	
	void		 SlideIn();
	void		 SlideOut();
	
	void		SetDestinationLocation(Point i_dest) {m_dest = i_dest; mY = m_dest.mY;}

private:
	void setState(LODBoxState i_state);
	void layoutWidget();
	
	void onSlideInComplete();
	void onSlideOutComplete();
	
	LODBoxState								m_state;
	Rect									m_scaledProgressBoxContainerRect;
	std::vector<LevelOfTheDay_ProgressBoxWidget*>	m_scaledProgressBoxWidgets;
	Point									m_dest;
	Point									m_startLoc;
	pvztime_t								m_transitionStartTime;
	Sexy::Delegate0							m_slideCompleteDelegate;
	LevelOfTheDay_ProgressiveAwardDialog*	m_topContainerWidget;
};

#endif /* defined(__PlantsVersusZombies2__LevelOfTheDay_ProgressiveAwardDialog__) */
