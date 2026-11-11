//
//  IntroCinema.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__IntroCinema__
#define __PlantsVersusZombies2__IntroCinema__

#include <set>
#include <string>
#include <vector>

#include "PVZTypes.h"
#include "RtObject.h"
#include "StandardLevelIntro.h"
#include "TimeMgr.h"
#include "ObjectTypeDirectory.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

struct ZombieSpawnLoc
{
	ZombieSpawnLoc()
	{
//		ZombieType = 0;
		PosX = 0;
		PosY = 0;
	}

	ZombieSpawnLoc(const ZombieTypePtr i_zombieType, const int i_posX, const int i_posY)
	{
		ZombieType = i_zombieType;
		PosX = i_posX;
		PosY = i_posY;
	}

	ZombieTypePtr	ZombieType;
	int				PosX;
	int				PosY;
};

struct PFTrigger
{
	PFTrigger()
	{
		TimeToPlantfood = 0.f;
		GridX = 0;
		GridY = 0;
		Triggered = false;
	}

	PFTrigger(const pvztime_t i_timeToPlantfood, const int i_gridX, const int i_gridY)
	{
		TimeToPlantfood = i_timeToPlantfood;
		GridX = i_gridX;
		GridY = i_gridY;
		Triggered = false;
	}
			  
	pvztime_t	TimeToPlantfood;
	int			GridX;
	int			GridY;
	bool		Triggered;
};

class IntroCinema: public StandardLevelIntro
{
public:
	
	enum IntroStates
	{
		INTRO_FIRST_BLACK_SCREEN,
		INTRO_FADE_IN_POPCAP,
		INTRO_DISPLAY_POPCAP,
		INTRO_FADE_OUT_POPCAP,
		INTRO_PREVIEW_CINEMA_BEFORE_LOGO,
		INTRO_PREVIEW_CINEMA_WITH_LOGO,
		INTRO_FADE_FROM_GAME,
		INTRO_CINEMA_FINISHED
	};
	
	RT_CLASS_DEFINE(IntroCinema, StandardLevelIntro, RtClass);
	
	IntroCinema();
	virtual ~IntroCinema();
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:

	virtual void				initializeModule() override;
	virtual void				registerForEvents() override;
	
	virtual bool				manualIntroStart() const override;
	virtual void				startStandardIntro();
	
private:

	void						onDraw(Sexy::Graphics* i_g);
	
	void						onLoadComplete() override;
	void						onUpdate();
	void						onAddToRenderQueue(class RenderQueue* i_queue);

	void						spawnIntroPlants();
	void						spawnIntroZombies();
	void						setupPlantfoodSequence();
	void						setupCinematicPan();
	
	std::vector<ZombieTypePtr>	m_zombiesToUse;
	std::vector<PlantTypePtr>	m_plantsToUse;
	
	IntroStates					m_introState;
	pvztime_t					m_introStateStartTime;
	pvztime_t					m_introStateEndTime;
	std::vector<PFTrigger>		m_plantfoodTriggers;
	int							m_plantsPlantfooded;
	
};

class IntroCinemaProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(IntroCinemaProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return IntroCinema::StaticGetClass();
	}
	
//	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const;
};

#endif /* defined(__PlantsVersusZombies2__IntroCinema__) */
