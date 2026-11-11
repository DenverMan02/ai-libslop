//
//  WaveProgressMeter.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __WAVEPROGRESSMETER_H__
#define __WAVEPROGRESSMETER_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "Wave.h"

class UIWidgetSheet;
class WaveDefinition;

class WaveProgressMeter : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WaveProgressMeter, UIWidget, RtClass);	
	
	WaveProgressMeter();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;
	virtual void	AddToRenderQueue(class RenderQueue* i_queue) override;
	
	// Public Interface (Core)

protected:
	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	
private:	
	
	// Private Interface
	void						setFlagCount(const int i_flagCount);
	void						setFillPercentage(const int i_fillPercentage);
    void                        setCurrentDisplayPercentage(const int i_fillPercentage);  //PVZ2_CHINESE Next_Wave
	void						setFlagsTriggered(const int i_flagsTriggered);

	// Event handling
	void						onFlagWaveTriggered(int i_flagWavesTriggered);
	void						onNewWaveStarting(int i_waveIndex, const WaveDefinition* i_wave);
    void						onWaveStart(int i_wave, WaveType::WaveType i_type, bool i_isFinal); // New wave generator.
	void						onSetPercentage(uint8 i_percentage);
    void						onSetCurrentDisplayPercentage(uint8 i_percentage);  //PVZ2_CHINESE Next_Wave
	void						onSetFlagCount(int i_flagCount);
	void						onGamePaused();
	void						onGameUnpaused();
	
	// Private Members (serialized)
	float						m_currentDisplayPercent;
	uint8						m_targetFillPercent;
	uint8						m_flagsTriggered;
	uint8						m_flagCount;
	bool						m_useHeadImage;
	std::vector<pvztime_t>		m_lerpFlagEndTime;
	

	// Private Members (not serialized)
	ImagePtr					m_flagImage;
	
};

#endif //__WAVEPROGRESSMETER_H__
