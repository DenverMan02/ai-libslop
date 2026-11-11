/*
 * Plant_GroundCherry.h
 *
 *  Created on: 2015-7-24
 *      Author: jianglc
 */

#ifndef PLANT_GROUNDCHERRY_H_
#define PLANT_GROUNDCHERRY_H_

#include "PlantFramework.h"

namespace Message
{
	void PlantFoodByGroundCherry();
}

enum GroundCherryAnimState
{
	Anim_1st_Stage,
	Anim_2nd_Stage,
	Anim_3rd_Stage,
	Anim_death,
	Anim_Count
};

class PlantGroundCherry : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGroundCherry, PlantFramework, RtClass);

    std::vector<Point>& GetLightUpGrid();

    virtual void onKilled(bool i_instantKill) override;
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    void NotifySetHidden(bool i_newValue, bool i_oldValue) override;

    std::vector<Point>& GetLightUpPoints() { return m_vLightUpGridVec; }

    void DoPlantFoodEffect();
    bool CanBeTargeted() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) override;

protected:

    void    Initialize()        override;
    bool	CanApplyPlantfood() override;
	void	ApplyPlantfood()    override;
	void	CancelPlantfood()   override;
    void    UpdateActions()     override;

    void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:

    //void    FindAllZombiesAndStunned();

    bool                m_bFoodEffect;
    pvztime_t           m_iFoodEndTime;
    std::vector<Point>  m_vLightUpGridVec;
    pvztime_t 			m_startTime;
    GroundCherryAnimState m_state;
};

class GroundCherryPropertySheet : public PlantPropertySheet
{

public:

    RT_CLASS_DEFINE(GroundCherryPropertySheet, PlantPropertySheet, RtClass);

    GroundCherryPropertySheet()
    {
        iFoodEffectRunningTime = 10.f;
        iLiveTime = 60.0f;
    }

    float iFoodEffectRunningTime;
    float iLiveTime;
};

class PlantAnimRig_GroundCherry : public PlantAnimRig
{
public:

	RT_CLASS_DEFINE(PlantAnimRig_GroundCherry, PlantAnimRig, RtClass);

	PlantAnimRig_GroundCherry() {}

    void SetPlantGroundCherry(class Plant* pPlant) { m_pPlantGroundCherry = pPlant->GetPtr(); }

    RtWeakPtr<Plant>& GetPlantGroundCherry() { return m_pPlantGroundCherry; }

    void SetIdleLabel(std::string i_label) { m_idleLabel = i_label; }

protected:

    std::string getIdleAnimationName() override;

	std::string getPlantFoodMainAnimName() override;

	virtual void onPopAnimInitialized() override;

private:

    RtWeakPtr<Plant> m_pPlantGroundCherry;
    std::string m_idleLabel;

};


#endif /* PLANT_GROUNDCHERRY_H_ */
