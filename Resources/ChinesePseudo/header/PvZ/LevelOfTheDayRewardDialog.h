//
//  LevelOfTheDayRewardDialog.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LevelOfTheDayRewardDialog__
#define __PlantsVersusZombies2__LevelOfTheDayRewardDialog__

#include <vector>

#include "PinataManager.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "Widget.h"
#include "LevelOfTheDayConfigInfo.h"

class Effect_FloatingText;
namespace Sexy {
class Graphics;
struct Touch;
}  // namespace Sexy

class LevelOfTheDayRewardDialog : public Sexy::Widget
{
public:
	//RT_CLASS_DEFINE(LevelOfTheDayRewardDialog, Sexy::Widget, Sexy::RtClass) {}
	
	LevelOfTheDayRewardDialog();
	virtual ~LevelOfTheDayRewardDialog();
	
	void Update() override;
	void Draw(Sexy::Graphics* i_g) override;
	void DrawOverlay(Sexy::Graphics* i_g, int i_priority) override;

	void TouchEnded(const Sexy::Touch& i_touch) override;

	void BeginRewardSequence(Sexy::Delegate0 i_onCompleted);
    
protected:
    
    void DoRewardDrop();

private:
    
	void onAllPinatasOpened();
	void onNarrationFinished();
	
	void displayRewardHeader();
	void displayRewardFooter();
	
	void cheatsPopLodNarratives();
	
	Sexy::Delegate0 m_onCompleted;
	int m_frameCycle;
	bool m_playedAudio;
	
	PinataManager m_pinataManager;
	std::vector<Effect_FloatingText*> m_floatingTexts;
    Sexy::Point m_stCacheLocation;
};

#endif /* defined(__PlantsVersusZombies2__LevelOfTheDayRewardDialog__) */
