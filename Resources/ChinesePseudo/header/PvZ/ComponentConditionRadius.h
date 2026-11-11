#ifndef __PlantsVersusZombies2__ComponentConditionRadius__
#define __PlantsVersusZombies2__ComponentConditionRadius__

#include "ComponentRadiusBurst.h"
#include "DamageInfoProps.h"

#include <deque>

class Plant;

class ComponentConditionRadiusProps : public ComponentRadiusBurstProps
{
public:
	ComponentConditionRadiusProps()
	:ComponentRadiusBurstProps()
	,PulseInitialDelay(0.0f)
	{}
	
	float	PulseInitialDelay;
	std::vector<PlantConditionEntry> Conditions;
};

class ComponentConditionRadius : public ComponentRadiusBurst
{
public:
	RT_CLASS_DEFINE(ComponentConditionRadius, ComponentRadiusBurst, RtClass);

	void SetRadiusProps(const ComponentConditionRadiusProps& i_props);
	
protected:
	void onBegin() override;
	void beginApply() override;
	void beginCoolDown() override;
    
private:
	void applyConditionTo(std::vector<BoardEntity*> touchedEntities);

	ComponentConditionRadiusProps m_condition_props;
};

#endif /* defined(__PlantsVersusZombies2__ComponentConditionRadius__) */
