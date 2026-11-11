//
//  PlantAnimRig_Holonut.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Holonut_h
#define PlantsVersusZombies2_PlantAnimRig_Holonut_h

#include "PlantAnimRig_Wallnut.h"
#include "AnimRigLayerSet.h"

class PlantAnimRig_Holonut : public PlantAnimRig
{
public:
	static const std::string k_totalshieldLayerSetName;
	static const std::string k_halfshieldLayerSetName;
	static const std::string k_normalLayerSetName;

public:
	RT_CLASS_DEFINE(PlantAnimRig_Holonut, PlantAnimRig, RtClass);
	
	virtual bool PlayIdleLooped() override;
	
	void SetDownedState(bool i_downed)
	{
		m_downed = i_downed;
	}
	
	void AddLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowLayerSet(std::string setName);

	bool PlayZenGardenIdleAnim() override;
	bool PlayPreviewAnim(bool bHideLayer) override;

	bool PlayPlanted();
	bool PlayRecover();
	bool PlayDie();
	
protected:
	virtual void onPopAnimInitialized() override;
	
	bool m_downed;
	AnimRigLayerSet m_layerSet;
};

#endif
