/*
 * JuggledModule.h
 *
 *  Created on: 2021-7-19
 *      Author: admin
 */

#ifndef JUGGLEDMODULE_H_
#define JUGGLEDMODULE_H_

//#include "LevelModule.h"
#include "MTRand.h"
//#include "Precompile.h"
#include <vector>
#include "VictoryOutro.h"

class JuggledModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(JuggledModule, LevelModule, RtClass);

	JuggledModule();
	virtual ~JuggledModule();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;

	void onLoadComplete();
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class JuggledModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(JuggledModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return JuggledModule::StaticGetClass();
	}

	JuggledModuleProperties()
		: MaxProjectilesToJuggle(3)
		, JuggleLaunchDelay(2.0f)
		, MoveSpeedMultiplierWhileJuggling(0.8f)
		, CatchArcDegrees(120.0f)
	{}

	SexyVector3 LaunchVelocity;
	SexyVector3 LaunchAcceleration;
	ValueRange LaunchHeight;

	int MaxProjectilesToJuggle;
	float JuggleLaunchDelay;
	float MoveSpeedMultiplierWhileJuggling;
	float CatchArcDegrees;

	std::vector<std::string> JuggleableProjectiles;
	std::vector<std::string> UnthrowableProjectiles;
	std::vector<std::string> AngleAgnosticProjectiles;
};


#endif /* JUGGLEDMODULE_H_ */
