//
//  ProbabilityConfig.h
//  PlantsVersusZombies2
//

#ifndef __PlantsVersusZombies2__ProbabilityConfig__
#define __PlantsVersusZombies2__ProbabilityConfig__

#include "RtObject.h"

class ProbabilityConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(ProbabilityConfig, Sexy::RtObject, Sexy::RtClass);
    
	static const RtWeakPtr<ProbabilityConfig> GetProbabilityConfig(const SexyString& aliases);
	
    bool GetKeyValue(uint32 index, std::string& key, float& value);
	uint32 GetSize();
	const std::string& GetTitle() { return title; }
    
private:
    std::vector<std::string> keys;
    std::vector<float> values;
    std::string title;
};

#endif /* defined(__PlantsVersusZombies2__ActivityConfig__) */
