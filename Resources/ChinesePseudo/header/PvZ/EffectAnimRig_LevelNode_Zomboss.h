//
//  EffectAnimRig_LevelNode_Zomboss.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/6/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_LevelNode_Zomboss__
#define __PlantsVersusZombies2__EffectAnimRig_LevelNode_Zomboss__

#include "EffectAnimRig_LevelNode.h"

class EffectAnimRig_LevelNode_Zomboss : public EffectAnimRig_LevelNode
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LevelNode_Zomboss, EffectAnimRig_LevelNode, RtClass) {}
	
	EffectAnimRig_LevelNode_Zomboss();
	virtual ~EffectAnimRig_LevelNode_Zomboss();

	void PlayLockedIdle() override;
	void PlayUnlockingAnimation() override;
	void PlayUnlockedAnimation() override;
	void PlayCompletingAnimation(AnimStoppedDelegate i_onAnimStopped) override;
	void PlayCompletedAnimation() override;
	
	std::string GetLockedIdleAnim() override;
	std::string GetUnlockingAnim() override;
	std::string GetUnlockedAnim() override;
	std::string GetCompletingAnim() override;
	std::string GetCompletedAnim() override;

	void PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps) override;
	
	void SetOverlayNode(EffectAnimRig_LevelNode* i_overlay);
	EffectAnimRig_LevelNode* GetOverlayNode() const;
	
	void SetShouldPropogateCallToOverlayNode(bool i_shouldPropogateCall) { m_propogateCallToOverlayNode = i_shouldPropogateCall; }
	bool GetShouldPropogateCallTooverlayNode() const { return m_propogateCallToOverlayNode; }

protected:
	void onUpdate() override;

private:
	EffectAnimRig_LevelNode*	m_overlayNode;
	bool						m_propogateCallToOverlayNode;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_LevelNode_Zomboss__) */
