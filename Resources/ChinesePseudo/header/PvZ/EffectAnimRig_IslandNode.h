//
//  EffectAnimRig_IslandNode.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/4/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_IslandNode__
#define __PlantsVersusZombies2__EffectAnimRig_IslandNode__

#include "EffectAnimRig_DelayReplayAnim.h"

class EffectAnimRig_IslandNode : public EffectAnimRig_DelayReplayAnim
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_IslandNode, EffectAnimRig_DelayReplayAnim, RtClass);
	
	EffectAnimRig_IslandNode()
		: m_IDRegistered(false)
	{}
	virtual ~EffectAnimRig_IslandNode();

	void PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps) override;
	
	void RegisterAudioID();
	void UnregisterAudioID();
	void* GetAudioID() const;
	
private:
	bool m_IDRegistered;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_IslandNode__) */
