//
//  MinecartTutorialIntro.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/7/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_MinecartTutorialIntro_h
#define PlantsVersusZombies2_MinecartTutorialIntro_h

#include "StandardLevelIntro.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "GameNotify.h"

class MinecartTutorialIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(MinecartTutorialIntro, StandardLevelIntro, RtClass);
	
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	virtual void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_BOARD_EDGE, bool i_special = false) override;

private:
	class Board* getBoard();
	void showTools(bool i_isShown);
	
	void startIntro();
	void onUpdate();
	void onEndLevel();
	void onStartIntro();

	void addToRenderQueue(class RenderQueue* i_queue);
	
    void onMinecartMoved(class GridItemRailcart* i_railcart);
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onPlantDied(Plant* i_plant);

	void setupWaitForPlantFoodApplication();
	void setupPlantFoodApplied();
	void setupZombies();
	void setupZombiesWaveOneDone();
    void placeLawnItems();

    virtual bool manualIntroStart() const override;
    
	enum State 
	{
		PVZ_BEGIN_ENUM(STATE_MCT_),
		STATE_MCT_START,
		STATE_MCT_WAIT_FOR_MINECART,
		STATE_MCT_WAIT_FOR_ZOMBIE_DEATH,
		STATE_MCT_PLAYING,
		PVZ_END_ENUM(STATE_MCT_),
	};
	void setState(State i_state);

	State                           m_state; 
	AnimationMgrWkPtr               m_animationMgr;
};

class MinecartTutorialIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(MinecartTutorialIntroProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return MinecartTutorialIntro::StaticGetClass();
	}
};

#endif
