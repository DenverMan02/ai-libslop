//
//  SunBombChallenge.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SunBombChallenge_h
#define PlantsVersusZombies2_SunBombChallenge_h

#include <set>
#include <string>

#include "LevelModule.h"
#include "RtObject.h"

namespace Sexy {
class SexyVector2;
}  // namespace Sexy

class SunBombChallengeModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(SunBombChallengeModule, LevelModule, RtClass);
	 
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
     
private:
	void onCoinClicked(class Collectable* i_collectable);
	void onPlayerWon();
    void explosion(SexyVector2 screenPos);

	bool m_tutorialActive;
	int m_totalExplodedBombs;
	int m_consecutiveExplodedBombs;
};
 
class SunBombChallengeProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(SunBombChallengeProperties, LevelModuleProperties, RtClass);
     
    virtual RtClass* GetModuleClass() const override
    {
        return SunBombChallengeModule::StaticGetClass();
    }
 
    SunBombChallengeProperties()
    {
		PlantBombExplosionRadius = 25.f;
        ZombieBombExplosionRadius = 80.f;
		PlantDamage = 1000.0f;
		ZombieDamage = 500.f;
    }
	
    float PlantBombExplosionRadius;
    float ZombieBombExplosionRadius;
	float PlantDamage;
	float ZombieDamage;
};
#endif
