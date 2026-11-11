//
//  Plant_Sunshroom.cpp
//  PlantsVersusZombies2
//
//  Created by erydeman on 08/20/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Sunshroom_h
#define PlantsVersusZombies2_Plant_Sunshroom_h

#include "Plant_Sunflower.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "PlantAnimRig_Sunflower.h"

class PlantSunshroom : public PlantSunflower
{
public:
	RT_CLASS_DEFINE(PlantSunshroom, PlantSunflower, RtClass);
    
	PlantSunshroom();
	virtual ~PlantSunshroom();
	
	void	Initialize() override;
	void	UpdateActions() override;
	void	ApplyPlantfood() override;
	
	void	ProduceSun(const PlantAction& i_fromAction) override;
	
	void	NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    void	 onKilled(bool i_instantKill) override;
    
protected:
	void			onAnimStoppedCallback(const std::string&) override;
	void			onPlantGrowthPaused();
	void			onPlantGrowthResumed();
	float			GetGrowthTime(int iStage);
	
private:
	const int		getMaxGrowthStage();
	void			setGrowthStage(int i_growthStage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = PopAnimRig::AnimStoppedReflectionDelegate());
	bool			isFullyGrown();
	
	pvztime_t m_swapForOtherPlantTime;
	pvztime_t m_growthPauseStartTime;
	uint8 m_currentGrowthStage;
	
	std::string getCollectableTypeName() override;
};

class PlantAnimRig_Sunshroom : public PlantAnimRig_Sunflower
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_Sunshroom, PlantAnimRig_Sunflower, RtClass);
	
	PlantAnimRig_Sunshroom()
	{
		m_currentGrowthStage = 0;
	}
    
    std::string GetPriviewAnim();
    bool PlayPreviewAnim(bool bHideLayer = false) override;
    
	void SetGrowthStage(uint8 i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onGrowthAnimComplete = PopAnimRig::AnimStoppedReflectionDelegate());
    
	
private:
	std::string getIdleAnimationName() override;
	std::string getSpecialAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	
	void growthAnimComplete(const std::string& i_anim);
	virtual void InitAnimRig_ZenGarden() override;
	
	uint8 m_currentGrowthStage;
};
#endif
