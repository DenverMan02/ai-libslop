//
//  PlantAnimRig.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_H__
#define __PLANTANIMRIG_H__

#include "Precompile.h"
#include "PopAnimRig.h"
#include "RtDelegate.h"
#include "PlantEnums.h"
#include "PVZTypes.h"
#include "PlantType.h"
#include "ProbabilitySet.h"

enum PlantAnimRigState 
{
	PLANTANIM_NOTPLAYING,
	PLANTANIM_IDLE,
	PLANTANIM_ATTACK,
	PLANTANIM_PLANTFOOD_ON,
	PLANTANIM_PLANTFOOD,
	PLANTANIM_PLANTFOOD_OFF,
    
    PLANTANIM_HELPED_ON,
    PLANTANIM_HELPED,
    PLANTANIM_HELPED_OFF,
    
    PLANTANIM_EXHAUSTED_ON,		// Non-interruptable
    PLANTANIM_EXHAUSTED,		// Non-interruptable loop
    PLANTANIM_EXHAUSTED_OFF,	// Non-interruptable
    
    // NOTE: It is my hope that we can evolve Plant to allow a data-driven way to automatically switch to a state like Charging or Exhausted after attacking.
	PLANTANIM_CYCLING,			// cycle through stages
    PLANTANIM_WATER,
	// Leave at end
	PLANTANIM_USERDEFINED
};

struct PlantCustomLayers
{
	PlantCustomLayers()
	{}
	PlantCustomLayers(const std::string &i_baseName) : m_baseName(i_baseName)
	{}
	bool operator<(const PlantCustomLayers &i_rhs) const
	{
		return m_baseName < i_rhs.m_baseName;
	}
	std::string m_baseName;
	std::set<std::string> m_layerNames;
};

typedef RtWeakPtr<class PlantAnimRig> PlantAnimRigPtr;

class PlantAnimRig : public PopAnimRig
{
public:
    static const std::string kAttackAnim;
    static const std::string kIdlekAnim;
    static const std::string kDamageAnim;
    static const std::string kGrowAnim;
    
    static const std::string kUseSpecial;
    static const std::string kUseAction;
    
public:
	RT_CLASS_DEFINE(PlantAnimRig, PopAnimRig, RtClass);

	// UseSpecialDelegate / UseActionDelegate
	//	- Called when our animation hits a 'use_special' or 'use_action' anim command
	typedef Delegate1<pvztime_t> UseSpecialDelegate;
	typedef Delegate1<pvztime_t> UseActionDelegate;
	
	// PlantFoodMainAnimStarted
	//	- Fired off once each time the 'plantfood' animation has started. 
	//	- Note that this can happen multiple times if the 'plantfood' animation is looped
	typedef RtReflectionDelegate<Delegate0> PlantFoodMainAnimStartedDelegate;
	typedef RtReflectionDelegate<Delegate0> PlantFoodMainAnimLoopedDelegate;
	// PlantFoodMainAnimsEnded
	//	- Fired off once all desired 'plantfood' animations have finished.
	typedef RtReflectionDelegate<Delegate0> PlantFoodMainAnimEndedDelegate;
	
	PlantAnimRig();
	virtual ~PlantAnimRig();
	
	void ClearPlantDelegates();
	void SetPlantDelegates(UseSpecialDelegate i_onUseSpecial, UseActionDelegate i_onUseAction);

	PlantAnimRigState 	GetState();
	void 				SetState(PlantAnimRigState i_newState);
	int					GetStateAnimsCompleted() const { return m_stateAnimsCompleted; }
    
	virtual bool PlayInitialFrame();
	virtual bool PlayIdleLooped();
	virtual bool PlayWatering();
	virtual bool PlayWatering(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0);
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded);
	virtual bool PlayPlantFoodEnd();
    
    virtual void PlayHelpedStart();
    virtual void PlayHelped();
    virtual bool PlayHelpedEnd();

    virtual void PlayExhaustedStart();
    virtual void PlayExhausted();
    virtual bool PlayExhaustedEnd();
    
    virtual bool PlayCycling();
    
	virtual bool playPlantFoodOn();
	virtual bool playPlantFoodMain();
	virtual bool playPlantFoodOff();
    
	virtual bool PlayPreviewAnim(bool bHideLayer = false);
    virtual bool PlayZenGardenIdleAnim() { return PlayPreviewAnim(); }
	virtual void InitAnimRig_ZenGarden() {}
	
	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0);

	virtual int CalcDamageStateCount();
	void SetDamageStateIndex(int i_newDamageStateIndex);
    
    void HideAllAvatarLayers();
    void ShowAvatarLayers(PlantTypePtr i_plantType, PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL);
	void SetAvatarIndex(int i_avatarIndex);
	
    int GetCurrentDamageStateIndex() { return m_currentDamageStateIndex; }
    
    void SetAvatarEnable(bool bAvatar = false) { m_bAvatar = bAvatar; onAvatarUpdate(); }
    void SetPlantLevel(int level) { m_plantLevel = level; onLevelUpdate(); }
    
    std::string GetIdleAnimName() { return getIdleAnimationName(); }
    std::vector<PlantCustomLayers> GetCustomizableLayers() { return m_customizableLayers; }
    std::vector<std::string> GetAvatarLayers();
    
    void SetIdleAnimationWeights(std::map<std::string, int> weights);
    PlantAnimRigState GetAnimRigState() { return m_state; }

    bool IsWaterAnimAlive();

    Plant* m_plant;
protected:
	virtual void onPopAnimInitialized() override;
    virtual void onAvatarUpdate() {}
    virtual void onLevelUpdate() {}
	virtual void onAnimStopped() override;
	virtual void onAnimInterrupted() override;
	virtual void onDamageStateIndexChanged(int i_oldDamageIndex);
	virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
	void onPlantfoodLooped();
	
private:
	void prepForCustomizableLayers();
	void prepCustomizableLayers(PASpriteInst* io_curSprite);
    
    virtual std::string getIdleAnimationName() { return "idle"; }
    virtual std::string getAttackAnimationName() { return "attack"; }
	virtual std::string getDamageIdleAnimationName() { return "damage"; }
    virtual std::string getPlantFoodOnAnimName() { return "plantfood_on"; }
	virtual std::string getPlantFoodMainAnimName() { return "plantfood"; }
    virtual std::string getPlantFoodOffAnimName() { return "plantfood_off"; }
    virtual std::string getHelpedOnAnimName() { return "helped_on"; }
    virtual std::string getHelpedAnimName() { return "helped"; }
    virtual std::string getHelpedOffAnimName() { return "helped_off"; }
    virtual std::string getExhaustedOnAnimName() { return "reload"; }
    virtual std::string getExhaustedAnimName() { return "reload_loop"; }
    virtual std::string getExhaustedOffAnimName() { return "reload_end"; }
    virtual std::string getCyclingAnimName() { return "cycling"; }
    virtual std::string getWaterAnimName() { return "water"; }
    
    bool hasWeightIdleAnimations();
    std::string getWeightedIdleAnimationName();
    
/// Member Variables
protected:
	PlantAnimRigState m_state = PLANTANIM_NOTPLAYING;
	int m_stateAnimsCompleted = 0;
    bool m_bAvatar = false;
    int  m_plantLevel = 1;
	
	int m_plantFoodPlayCount = 0;
	int m_currentDamageStateIndex = 0;

	int m_avatarIndex;
	
	UseSpecialDelegate m_onUseSpecial;
	UseActionDelegate m_onUseAction;
	
	PlantFoodMainAnimStartedDelegate m_onPlantFoodMainStarted;
	PlantFoodMainAnimEndedDelegate m_onPlantFoodMainLooped;
	PlantFoodMainAnimEndedDelegate m_onPlantFoodMainEnded;
	
	std::vector<PlantCustomLayers> m_customizableLayers;
    
    ProbabilitySet<std::string> m_idleWeights;
};

#endif
