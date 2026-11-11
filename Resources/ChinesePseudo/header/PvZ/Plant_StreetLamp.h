//
//  Plant_StreetLamp.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-10.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_StreetLamp_h
#define PlantsVersusZombies2_Plant_StreetLamp_h

#include "PlantFramework.h"
#include "GamePropertySheet.h"

namespace Message
{
    void StreetLampApplyFood();
    void StreetLampEndFoodEffect();
    void StreetLampSheep(Plant* i_plant);
    void NotifyWhenChanged(PlantFramework* i_plant, int i_state);
};

class PlantStreetLamp : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantStreetLamp, PlantFramework, RtClass);
    
    std::vector<Point>& GetLightUpGrid();
    
    virtual void onKilled(bool i_instantKill) override;
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void	NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    
    std::vector<Point>& GetLightUpPoints() { return m_vLightUpGridVec; }
    
    void DoPlantFoodEffect();
    
    
protected:
    
    void    Initialize()        override;
    bool	CanApplyPlantfood() override;
	void	ApplyPlantfood()    override;
	void	CancelPlantfood()   override;
    void    UpdateActions()     override;
	void onApplyCondition(PlantConditions i_condition) override;
	virtual void onEndCondition(PlantConditions i_condition) override;
private:
    
    void    FindAllZombiesAndStunned();
    
    bool                m_bFoodEffect = false;
    pvztime_t           m_iFoodEndTime = PVZ_EOT();
    std::vector<Point>  m_vLightUpGridVec;
};

class StreetLampPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(StreetLampPropertySheet, PlantPropertySheet, RtClass);
    
    StreetLampPropertySheet()
    {
        iFoodEffectRunningTime = 10.f;
    }
    
    float iFoodEffectRunningTime;
};

class PlantAnimRig_StreetLamp : public PlantAnimRig
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_StreetLamp, PlantAnimRig, RtClass);
    
    PlantAnimRig_StreetLamp() {}
    
    void SetPlantStreetLamp(class Plant* pPlant) { m_pPlantStreetLamp = pPlant->GetPtr(); }
    
    RtWeakPtr<Plant>& GetPlantStreetLamp() { return m_pPlantStreetLamp; }
    
protected:
    
    std::string getIdleAnimationName() override;
    
	std::string getPlantFoodMainAnimName() override;
    
private:
    
    RtWeakPtr<Plant> m_pPlantStreetLamp;
	
};


#endif
