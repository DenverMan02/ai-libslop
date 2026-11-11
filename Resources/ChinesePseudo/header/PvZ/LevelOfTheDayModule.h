//
//  LevelOfTheDayModule.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 9/27/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelOfTheDayModule_h
#define PlantsVersusZombies2_LevelOfTheDayModule_h

#include <vector>

#include "LevelModule.h"
#include "RtDb.h"
#include "RtObject.h"

class WaveManagerProperties;
class ZombieType;
namespace Sexy {
class MTRand;
}  // namespace Sexy


class LevelOfTheDayModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(LevelOfTheDayModule, LevelModule, RtClass);

	LevelOfTheDayModule();
	virtual ~LevelOfTheDayModule();

	// Public Interface (Inheritable)
	void GatherRuntimeResourceRequirements(std::set<std::string>& io_resGroupNames) const override;

protected:

	// Protected Interface (Inheritable)

	void initializeModule() override;
	void registerForEvents() override;

	// Protected Interface (Core)

private:

	// Private Interface (Inheritable)

	// Private Interface (Core)
    bool preventSave();

	void onLevelInit();
	void onGameplayStarted();
	void onGameplayEnded();
	void onLevelEnded();
};

class LevelOfTheDayModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelOfTheDayModuleProperties, LevelModuleProperties, RtClass);

	LevelOfTheDayModuleProperties()
	{}

	RtClass* GetModuleClass() const override
	{
		return LevelOfTheDayModule::StaticGetClass();
	}
};

#endif //PlantsVersusZombies2_LevelOfTheDayModule_h
