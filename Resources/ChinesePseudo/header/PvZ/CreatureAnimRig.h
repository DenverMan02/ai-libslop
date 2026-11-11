//
//  CreatureAnimRig.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __CREATUREANIMRIG_H__
#define __CREATUREANIMRIG_H__

#include <map>
#include <string>
#include <vector>

#include "PopAnim.h"
#include "PopAnimRig.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"

class CreatureAnimRig;

enum CreatureAnimRigState
{
	PVZ_BEGIN_ENUM(CREATUREANIM_),
	
	CREATUREANIM_NOTPLAYING,
	CREATUREANIM_IDLE,
	CREATUREANIM_WALK,
	CREATUREANIM_MELEE,
	
	CREATUREANIM_USERDEFINED,
	
	PVZ_END_ENUM(CREATUREANIM_)
};

typedef RtWeakPtr<class CreatureAnimRig> CreatureAnimRigPtr;

class CreatureAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(CreatureAnimRig, PopAnimRig, RtClass);
	
	// The following functions will more or less work if your Zombie is fairly standard
	virtual bool PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayMelee(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
    // override.
    //virtual AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, AnimStoppedDelegate i_onAnimStopped = AnimStoppedDelegate());
    //virtual AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped);

    float GetImageScale();
    float GetDesiredVelocity() { return m_desiredVelocity; }
	
	// Non-virtual functions
	void CreatureUpdateAnim(bool i_calcGroundTrackOffset);

	void SetGroundTrackName(const std::string& i_groundTrackName);
	float GetGroundTrackTranslation() const;
	void HideGroundTrack();
	
	void SetDesiredWalkVelocity(float i_newDesiredWalkVel);
	void SetAnimRateModifier(float i_modifier);
	
	bool IsPlaying(CreatureAnimRigState i_anim);

protected:
    const std::vector<std::string>& getEmptyLayerNames() const;
	
	// Override these in your child class!
	void onPopAnimInitialized() override;
	void onAnimSequenceContinued() override;

	virtual const std::string getIdleAnimationName();
	virtual const std::string getWalkAnimationName();
	virtual const std::string getMeleeAnimationName();
	
	void setAnimRateForWalkAnim(const std::string& i_animLabel);
	
	CreatureAnimRigState m_state;
	std::string m_groundTrackName;
	float m_lastGroundTrackOffset;
	float m_desiredVelocity;
	float m_animRateModifier;
	
};

inline float CreatureAnimRig::GetImageScale()
{
    PopAnim* pam = getPAM();
    
    if (pam)
    {
        return pam->mImgScale;
    }
    
    return 1.0f;
}

#endif // __CREATUREANIMRIG_H__
