//
//  PowerTileIntro.h
//  PlantsVersusZombies2
//
//  Created by Andy Seavy on 9/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PowerTileIntro_h
#define PlantsVersusZombies2_PowerTileIntro_h

#include <set>
#include <string>
#include <vector>

#include "AnimationMgr.h"
#include "Core.h"
#include "RtObject.h"
#include "StandaloneEffect.h"
#include "StandardLevelIntro.h"

class Plant;
class Zombie;
namespace Sexy {
    class SexyVector2;
}  // namespace Sexy

class PowerTileIntro : public StandardLevelIntro
{
public:
	RT_CLASS_DEFINE(PowerTileIntro, StandardLevelIntro, RtClass);
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
	virtual void startLevelIntro(PanType i_startingPanType = PAN_HOUSE_TO_ZOMBIES, bool i_special = false) override;
    virtual void onStandardIntroComplete() override;
    
private:
	class Board* getBoard();
	void showTools(bool i_isShown);
	
	void startIntro();
	void onUpdate();
	void onEndLevel();
	
	void onPlantFoodApplied(class PlantGroup* i_plant);
    void onPlantDied(Plant* i_plant);
	
	void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
	void onCursorAdded(class BaseCursor *i_cursor);
	void onCursorDestroyed(class BaseCursor* i_cursor);
	void onNarrationFinished();
    
    
	void setupWaitForPlantFoodApplication();
	void setupPlantFoodApplied();
	
	void addPeashooter(int i_x, int i_y);
	void addFirstPeashooter();
	void addSecondPeashooter();
	
	void setupDaveFailed();
	
	virtual bool manualIntroStart() const override;
    
	class Effect_BouncingArrow*		addBouncingArrow(const SexyVector2& i_screenLocation);
	class Effect_BouncingArrow* 	addPlantfoodArrow();
	class Effect_BouncingArrow*		addPeashooterArrow();
	void							clearBouncingArrows();
    
	enum State
	{
		PVZ_BEGIN_ENUM(STATE_PTT_),
		STATE_PTT_START,
		STATE_PTT_DELAY_FOR_PLANTS,
		STATE_PTT_WAIT_FOR_PLANTFOOD,
		STATE_PTT_DELAY_FOR_POWERTILES,
		STATE_PTT_WAIT_FOR_ZOMBIE_DEATH,
		STATE_PTT_SHOWING_ADVICE,
		STATE_PTT_FAILED,
		STATE_PTT_PLAYING,
		PVZ_END_ENUM(STATE_PTT_),
	};
	void setState(State i_state);
    
	State                           m_state;
	float							m_timeInCurrentState;
	AnimationMgrWkPtr               m_animationMgr;
	
	std::vector<StandaloneEffectPtr>	m_bouncingArrows;
};

class PowerTileIntroProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(PowerTileIntroProperties, StandardLevelIntroProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return PowerTileIntro::StaticGetClass();
	}
	
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
};

#endif
