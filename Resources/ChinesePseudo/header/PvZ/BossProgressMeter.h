//
//  BossProgressMeter.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2/21/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BossProgressMeter__
#define __PlantsVersusZombies2__BossProgressMeter__

#include <vector>

#include "Image.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "UIWidget.h"
#include "Wave.h"
#include "dtypes.h"

namespace Sexy
{
	class Graphics;
}

namespace Message
{
	void BossShowProgressMeter();
	void BossShowFillSpark(bool i_show);
	void BossSetPhaseCount(int i_phaseCount);
	void BossSetCurrentPhase(int i_currentPhaseNumber, int i_scoreValue);
	void BossSetAbsoluteFillPercentage(float i_percentage);
	void BossSetPhasePercentage(float i_percentage);
	void BossFlashDamage();
	void BossChangePhase();
	void BossProgressMeterStageCountdown();
	void BossProgressMeterUnlimited(bool i_unlimited);
}

class BossProgressMeter : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(BossProgressMeter, UIWidget, RtClass);	
	
	BossProgressMeter();
	
	// Public Interface (Inheritable)
	
	void	Draw(Graphics* i_g) override;
	void	AddToRenderQueue(class RenderQueue* i_queue) override;
	
	// Public Interface (Core)
	void SetSparkActive(bool i_active);
	void FlashDamage();
    void SetHeadIcon(ImagePtr i_headIcon);
    void SetEliminateModule(bool i_eliminateModule);
    float GetTotalPercent();
protected:
	// Protected Interface (Inheritable)

	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	void		initLoadingResourcesGroupList() override;
	void		registerForEvents() override;
	
	class ChallengeScoringUI* getStageCounterUI();

	virtual float       drawCalcFillPercent(int i_phaseNumber, float i_prevPhasePercentage);
	virtual ImagePtr    getMeterFillImage();

private:	
	
	// Private Interface
	void				setPhaseCount(const int i_phaseCount);
	void				setPhasePercentage(const float i_phasePercentage);
	void				snapPhasePercentages();
	void				setCurrentPhase(const int i_currentPhase);
	void                updatePhaseUI();
	
	void createSparkEffect();
	void setSparkLocation(SexyVector2 i_location);

	// Event handling
	void				showBossMeter();
	void                onBossProgressMeterUnlimited(bool i_unlimited);
	void				onSetPhaseCount(int i_phaseCount);
	void				onSetCurrentPhase(int i_currentPhase, int i_scoreValue);
	void				onChangePhase();
	void				onSetPhasePercentage(float i_percentage);
	void				onSetAbsoluteFillPercentage(float i_percentage);
	void				onGamePaused();
	void				onGameUnpaused();
	void                onSetStageCountdown();

	// Private Members (serialized)
	int					m_currentPhase;
	int                 m_currentPhaseScoreValue;
	int					m_phaseCount;
	std::vector<float>	m_phasePercents;
	std::vector<float>	m_targetPhasePercents;
	
	RtWeakPtr<class Effect_PopAnim> m_spark;
	pvztime_t			m_sparkVisibilityChangeStartTime;
	bool				m_sparkShown;
	
	pvztime_t			m_damageFlashStartTime;
    RtWeakPtr<Image>    m_bossHeadIcon;
    
    bool                m_isEliminateModule;

    bool                m_phaseCountdown;
    bool                m_unlimitedPhases;
	
	// Private Members (not serialized)
	
};

#endif /* defined(__PlantsVersusZombies2__BossProgressMeter__) */
