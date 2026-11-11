//
//  Plant_Chomper.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 4/7/14
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Chomper_h
#define PlantsVersusZombies2_Plant_Chomper_h

#include "PlantFramework.h"
#include "PlantAnimRig.h"

class PlantChomper : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantChomper, PlantFramework, RtClass);

	void Initialize() override;
	
    bool CanApplyPlantfood() override { return true; }
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool CanEndPlantfood() override;

	void UpdateActions() override;

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;

	void PlayAttackAnimation() override;
    GridItemPtr FindTargetDamageableGridItem(Rect& i_rect, PlantWeapon i_plantWeapon) override;

private:
	void setState(int i_state);

	void markSuctionZombies();
	void pullSuctionZombies();
	bool allSuctionZombiesAreWithinRange();
	void pushAllZombies();
    void PushFrontZombies();

	float calcSuctionDestination(const Zombie* i_zombie) const;
	bool canBeMovedByChomper(const Zombie* i_zombie) const;

	bool zombieIsBlacklisted(const Zombie* i_zombie) const;
	bool zombieIsInRange(const Zombie* i_zombie) const;
    
    void PlayBurpEffect(const std::string& label, const SexyVector2& offset);
    void DropMetal();
    bool CanPullHelmFrom(Zombie* zombie);
    
	pvztime_t m_animStartTime = PVZ_EOT();
    pvztime_t m_nextChewSoundTime = PVZ_EOT();
	std::vector<ZombiePtr> m_suctionZombies;
    int m_gulpZombieCount = 0;
};

class PlantAnimRig_Chomper : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Chomper, PlantAnimRig, RtClass);

	PlantAnimRig_Chomper()
	: m_currentAnimationHandle(ANIMHANDLE_NONE) {
		// Do nothing.
	}
	bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
	bool PlayPlantFoodEnd() override;
	bool PlayIdleLooped() override;

	bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	void PlayBiteToIdle();
	void PlayBiteToChewing();
	void PlayChewing();
	void PlaySwallow();
    void PlayAdvancedSwallow();

	void PlayBeginSucking();
	void PlayLoopSucking();
	void PlayEndSucking();
	void PlayLoopBurp();
	void PlayEndBurp();
    void PlayAvatarBurp();
    void PlayAvatarEndBurp();
    void PlayLevel5Attack();
    void PlayLevel5AttackGulpZombie();
    void PlayLevel5AttackGulpToIdle();
    
	bool CurrentAnimationIsFinished();
private:
	AnimHandle m_currentAnimationHandle;
};

#endif
