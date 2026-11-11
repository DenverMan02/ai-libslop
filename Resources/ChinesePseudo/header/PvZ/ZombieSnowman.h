// ZombieSnowman.h
// create by lfy on 2023.3.21
// 

#ifndef __ZOMBIESNOWMAN_H__
#define __ZOMBIESNOWMAN_H__

#include "Zombie.h"

// class ZombieSnowmanProps : public ZombiePropertySheet
// {
// public:
// 	RT_CLASS_DEFINE(ZombieSnowmanProps, ZombiePropertySheet, RtClass);

// };


class ZombieSnowman : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieSnowman, Zombie, RtClass);
protected:
	void onUpdate() override;
	void onAttackAnimStopped(const std::string& i_animLabel);
	BoardEntity *findTarget() override { return nullptr; }
	bool ShouldDrawShadow() const override { return false; }
	bool hasHeadParticle() const { return false; }
	bool hasArmParticle() const { return false; }
	// onDrawShadow
private:
    void onZombieInitialize() override;
	std::string getSnowmanType();
	// std::string m_originTypeName;
	int m_isInit = false;
};


class ZombieAnimRig_Snowman : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Snowman, ZombieAnimRig, RtClass);

	// DarkWizard specific functionality
	bool PlayBecomeSnowman(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}); 
	AnimHandle PlayDie() override;
	bool PlayWalk(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	const std::string getDieAnimationName() override { return "snowman_die"; }

protected:
	
private:
	bool m_isInit = false;
};


#endif



