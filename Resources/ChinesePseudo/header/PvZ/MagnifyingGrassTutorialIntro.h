//
//  MagnifyingGrassTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/28/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MagnifyingGrassTutorialIntro__
#define __PlantsVersusZombies2__MagnifyingGrassTutorialIntro__

#include "StandardLevelIntro.h"
#include "StandaloneEffect.h"
#include "Core.h"
#include "DamageInfo.h"

class MagnifyingGrassTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(MagnifyingGrassTutorialIntro, StandardLevelIntro, RtClass);

protected:
	void initializeModule() override;
	void registerForEvents() override;
	void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;
	bool manualIntroStart() const override;

private:
	void startIntro();
	void onPlantDied(class Plant* i_plant);
	void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
	void onUpdate();

	void showTools(bool i_isShown);
	void showSunBank(bool i_isShown);
	void showShovel(bool i_isShown);
	class Plant* placeOrGetMagnifyingGrass();
	void setupDaveFailed();
	void onNarrationFinished();
	class Effect_BouncingArrow* addBouncingArrow(const SexyVector2& i_screenLocation);
	class Effect_BouncingArrow* addArrowToPlant(class Plant* i_plant);
	void clearBouncingArrows();

	enum State
	{
		PVZ_BEGIN_ENUM(STATE_MGT_),
		STATE_MGT_START,
		STATE_MGT_DELAY_FOR_PLANTS,
		STATE_MGT_WAITING_FOR_ZOMBIE_DEATH,
		STATE_MGT_SHOWING_ADVICE,
		STATE_MGT_FAILED,
		STATE_MGT_PLAYING,
		PVZ_END_ENUM(STATE_MGT_),
	};
	void setState(State i_state);

	State								m_state;
	float								m_timeInCurrentState;
	std::vector<StandaloneEffectPtr>	m_bouncingArrows;
};

class MagnifyingGrassTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(MagnifyingGrassTutorialIntroProperties, StandardLevelIntroProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return MagnifyingGrassTutorialIntro::StaticGetClass();
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};


#endif /* defined(__PlantsVersusZombies2__MagnifyingGrassTutorialIntro__) */
