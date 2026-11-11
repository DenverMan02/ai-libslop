//
//  ZombieAnimRig.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_H__
#define __ZOMBIEANIMRIG_H__

#include "Precompile.h"
#include "PopAnimRig.h"
#include "RtObject.h"
#include "ZombieParticle.h"
#include "PopAnim.h"

class ZombieAnimRig;

enum ZombieAnimRigState
{
	ZOMBIEANIM_NOTPLAYING,
	ZOMBIEANIM_IDLE,
	ZOMBIEANIM_WALK,
	ZOMBIEANIM_EAT,
	ZOMBIEANIM_DIE,
	ZOMBIEANIM_ATTACK,
    ZOMBIEANIM_STUN,
    ZOMBIEANIM_RANGED_ATTACK,
	
	// Keep this one last
	ZOMBIEANIM_USERDEFINED,
};

typedef RtWeakPtr<class ZombieAnimRig> ZombieAnimRigPtr;

class ZombieAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig, PopAnimRig, RtClass);
	
	// The following functions will more or less work if your Zombie is fairly standard
	virtual bool PlayStreetIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayReverseWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayEat();
	virtual bool PlayAttack(AnimStoppedReflectionDelegate i_onAnimStopped);
    virtual bool PlayStunned();
    virtual bool PlayRangedAttack(AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual AnimHandle PlayDie();
	virtual bool PlayResilienceBreak(const std::string& i_animLabel, AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual bool PlayResilienceStandstill(const std::string& i_animLabel);
	virtual bool PlayResilienceRecover(const std::string& i_animLabel, AnimStoppedReflectionDelegate i_onAnimStopped);
    
    // override.
    virtual AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, AnimStoppedDelegate i_onAnimStopped = AnimStoppedDelegate());
    virtual AnimHandle PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped);

    virtual class ZombieParticle* DropHead(class Zombie* i_zombie);
    virtual class ZombieParticle* SpawnHead(ZombieAnimRig* i_originalZombieAnimRig);
	virtual class ZombieParticle* CreateProjectileParticle();
	class ZombieParticle* SpawnProjectileParticle();
	virtual void HideHead();
	virtual SexyVector2 GetHeadOffset();
	virtual const std::string GetHeadParticleName();

	virtual class ZombieParticle* DropArm(class Zombie* i_zombie);
    virtual void HideArm();
    virtual void HideArmStub();
    virtual void ShowArm();
	virtual const std::string GetArmParticleName();

	void SetButterVisibility(bool i_visible);
    void SetInkVisibility(bool i_visible);

    float GetImageScale();
    float GetDesiredVelocity() { return m_desiredVelocity; }
	
	// Non-virtual functions
	void ZombieUpdateAnim(bool i_calcGroundTrackOffset);

	void SetGroundTrackName(const std::string& i_groundTrackName);
	const std::string GetGroundTrackName();
	float GetGroundTrackTranslation() const;
	void HideGroundTrack();
	
	void SetDesiredWalkVelocity(float i_newDesiredWalkVel);
	void SetAnimRateModifier(float i_modifier);
    int GetAnimRateModifier();
	
	void SetNeedsToDie();
	bool IsReadyToDie();

	bool IsPlaying(ZombieAnimRigState i_anim);
    virtual bool hasHat(){return false;}
    
    virtual const std::string getIdleAnimationName();
 	virtual const std::string getAttackAnimationName();
 	virtual const std::string getWalkAnimationName();

	//zhRed add
	void SetLayerSet(std::string i_zombieType);
	virtual void SetLayerVisibilityForCurrentState();
	virtual void SetAlmanacArmor(std::vector<RtWeakPtr<class ArmorPropertySheet>> armorProps) {};
protected:
    const std::vector<std::string>& getEmptyLayerNames() const;
	
    // Override these in your child class!
	virtual void onPopAnimInitialized() override;
	virtual void onAnimSequenceContinued() override;
	virtual void onNeedsToDie() {}

	virtual const std::vector<std::string>& getHeadLayerNames();
	virtual const std::vector<std::string>& getArmLayerNames();
	virtual const std::vector<std::string>& getArmReplacementPairNames();
	
	virtual const std::string getWalkReverseAnimationName();;
	virtual const std::string getEatAnimationName();
    virtual const std::string getRangedAttackAnimationName();
	virtual const std::string getDieAnimationName();
    virtual const std::string getStunAnimationName();
	virtual const std::string getButterName();
    virtual const std::string getInkName();
    virtual const bool getDieShouldBlend() { return true; }
	
	void setAnimRateForWalkAnim(const std::string& i_animLabel);
	
	void setReadyToDie();

	ZombieAnimRigState m_state;
	std::string m_groundTrackName;
	float m_lastGroundTrackOffset;
	float m_desiredVelocity;
	float m_animRateModifier;
	pvztime_t m_needsToDieRequestedTime;
	bool m_readyToDie;
	//zhRed add zombies
	std::string m_zombieType;
    
private:
    void setArmVisibility(bool i_visible);
};

inline float ZombieAnimRig::GetImageScale()
{
    PopAnim* pam = getPAM();
    
    if (pam)
    {
        return pam->mImgScale;
    }
    
    return 1.0f;
}

#endif // __ZOMBIEANIMRIG_H__
