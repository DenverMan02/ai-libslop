//
//  PVPSkillEnergyUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.27
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVPSkillEnergyUI__
#define __PlantsVersusZombies2__PVPSkillEnergyUI__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "GridItemBrain.h"

class Effect_PopAnim;

class AddEnergyEffect : public GameObject
{
public:
    typedef Delegate1<float> StoppedDelegate;

public:
    RT_CLASS_DEFINE(AddEnergyEffect, GameObject, RtClass);
    
    AddEnergyEffect();
    virtual void Play();
    virtual void Update();
    virtual void SetStartPosition(const SexyVector2& screenSpace);
    virtual void SetEndPosition(const SexyVector2& screenSpace);
    virtual void SetEnergy(float energy);
    virtual void SetDelegate(const StoppedDelegate& delegate);

protected:
    virtual void OnEffectDone(class StandaloneEffect* i_effect);
    virtual void CalacBezierParameter();
    virtual Effect_PopAnim* CreateEffect();
    
protected:
    int m_state;
    SexyVector2 m_start;
    SexyVector2 m_current;
    SexyVector2 m_p1;
    SexyVector2 m_end;
    RtWeakPtr<Effect_PopAnim> m_effect;
    pvztime_t m_startTime;
    float m_energy;
    StoppedDelegate m_delegate;
};


// Cthulhu eyeball effect
class AddCthulhuEnergyEffect : public AddEnergyEffect
{
public:
    RT_CLASS_DEFINE(AddCthulhuEnergyEffect, AddEnergyEffect, RtClass);

    AddCthulhuEnergyEffect();
    ~AddCthulhuEnergyEffect();

    void Play() override;
    void Update() override;

protected:
    Effect_PopAnim* CreateEffect() override;

protected:
};

class PVPSkillEnergyUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(PVPSkillEnergyUI, UIWidget, RtClass);
	
	PVPSkillEnergyUI();
	virtual ~PVPSkillEnergyUI();
	
	virtual void	Draw(Graphics* i_g) override;
	//virtual bool	OnTouch(const Sexy::Touch& i_touch);

    void        InitEnergy(int iCurVal, int iMaxVal);
    void        SetCurEnergy(int iVal);
    int         GetCurEnergy() const { return m_iCurEnergy; }
    
    void        SetMaxEnergy(int iVal);
    int         GetMaxEnergy() const { return m_iMaxEnergy; }
    
    void        SetLostPlantAddEnergy(int iVal) { m_lostPlantAddEnergy = iVal; }
    void        SetLostBrainAddEnergy(int iVal) { m_lostBrainAddEnergy = iVal; }

protected:
	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
	virtual void	onUpdate() override;
    void     	onDestroy() override;
    void        onPVPSkillUsed(class Zombie* pSkill, int iCost);
    void        onPlantLost(class Plant * i_plant);
    void        onBrainLost(GridItemBrain * i_brain);
    void        onAddEnergy(float energy);
    void        PlayAddEnergyEffect(float energy, const SexyVector2& start);
protected:
    int m_iCurEnergy;
    int m_iMaxEnergy;
    
    int m_iAnimEnergy;
    int m_iAnimStep;
    
    int m_lostPlantAddEnergy;
    int m_lostBrainAddEnergy;
    std::vector<RtWeakPtr<AddEnergyEffect>> m_effect;
};


namespace Message
{
    void PVPSkillEnergyChanged(int curEnergy);
}


#endif /* defined(__PlantsVersusZombies2__PVPSkillEnergyUI__) */
