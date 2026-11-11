//
//  BeghouledWaveProgressMeter.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 6/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BeghouledWaveProgressMeter__
#define __PlantsVersusZombies2__BeghouledWaveProgressMeter__

#include <vector>

#include "Image.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "UIWidget.h"
#include "PrimeTextWidget.h"
#include "Wave.h"
#include "dtypes.h"

namespace Sexy {
	class Graphics;
}  // namespace Sexy
struct RenderItem;

namespace Message {
	void BeghouledProgressMeterSetWinCount(int i_matchesToWin);
	void BeghouledProgressMeterSetMatchCount(int i_matchCount);
}

class BeghouledWaveProgressMeter : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(BeghouledWaveProgressMeter, UIWidget, RtClass);
	
	BeghouledWaveProgressMeter();
	
	// Public Interface (Inheritable)
	
	void Draw(Graphics* i_g) override;
	void AddToRenderQueue(class RenderQueue* i_queue) override;
	
	// Public Interface (Core)
	
protected:
	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	void initLoadingResourcesGroupList() override;
	void registerForEvents() override;
	
private:
	
	// Private Interface
	void						setFillPercentage(const int i_fillPercentage);
	
	// Event handling
	void						onWaveStart(int i_wave, WaveType::WaveType i_type, bool i_isFinal); // New wave generator.
	void						onSetMatchCount(int i_matchCount);
	void						onSetWinCount(int i_winCount);
	void						onGamePaused();
	void						onGameUnpaused();
	
	// Private Members (serialized)
	float						m_currentDisplayPercent;
	uint8						m_targetFillPercent;
	const void					drawText(Graphics* i_g);
	int32						m_currentMatches;
	int32						m_matchesToWin;
	
	// Private Members (not serialized)
	PrimeTextWidget*            m_textWidget;
	
};


#endif /* defined(__PlantsVersusZombies2__BeghouledWaveProgressMeter__) */
