//
//  Plant_SweetPotato.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 10/3/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_SweetPotato__
#define __PlantsVersusZombies2__Plant_SweetPotato__

#include "GameSubSystem.h"
#include "PlantFramework.h"

class ZombieType;

class PlantSweetPotato : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSweetPotato, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

	bool CanAttractZombie(Zombie* i_zombie) const;

	bool CanApplyPlantfood() override;
    void ApplyPlantfoodEffectHeal() override;
	bool CanBeTargetedBy(const BoardEntity *i_entity) override;
	virtual void AddAttractionEffect(Zombie *i_zombie) {}
private:
	Rect calcBoardSpaceAttractRect(bool i_plantfood) const;
	void findZombiesInBoardSpaceRect(const Rect& i_rect, std::vector<Zombie*>& o_zombies) const;
};

class PlantAnimRig_SweetPotato : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_SweetPotato, PlantAnimRig, RtClass);

	bool PlayIdleLooped() override;
	int CalcDamageStateCount() override;
	std::string getDamageIdleAnimationName() override { return "idle_damage"; }
};

class SweetPotatoProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SweetPotatoProps, PlantPropertySheet, RtClass);

	SweetPotatoProps()
		: DrawAttractRects(false)
	{}

	bool IsZombieTypeBlackListed(const ZombieType* i_zombieType) const;

	std::vector<std::string> ZombieBlacklist;
	Rect NormalAttractRect;
	Rect PlantfoodAttractRect;

	float LaneChangeTime;

	bool DrawAttractRects;

private:
	void ensureBlacklistCacheIsBuilt() const;
};

///

class SweetPotatoSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(SweetPotatoSubsystem, GameSubSystem, RtClass);

	~SweetPotatoSubsystem();

	void RegisterSweetPotato(PlantSweetPotato* i_potato);
	void RegisterAttractions(PlantSweetPotato* i_potato, const std::vector<Zombie*>& i_attractedZombies);

	void Update() override;

private:
	void clearDeadPotatoes();
	bool isPotatoRegistered(PlantSweetPotato* i_potato) const;
	bool canPotatoPull(PlantSweetPotato* i_potato) const;
	PlantSweetPotato* pickAttractor(Zombie* i_zombie, const std::vector<PlantSweetPotato*>& i_potatoes) const;

	// serialized
	std::vector<RtWeakPtr<Plant>> m_sweetPotatoes;
	std::vector<RtWeakPtr<Zombie>> m_plantfoodAffectedZombies;

	// transient
	std::map<Zombie*, std::vector<PlantSweetPotato*>> m_zombieToAttractorsMap;
};

#endif /* defined(__PlantsVersusZombies2__Plant_SweetPotato__) */
