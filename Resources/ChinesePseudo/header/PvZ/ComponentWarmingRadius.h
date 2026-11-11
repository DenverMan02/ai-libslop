//
//  ComponentWarmingRadius.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 10/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentWarmingRadius__
#define __PlantsVersusZombies2__ComponentWarmingRadius__

#include "ComponentRadiusBurst.h"
#include "PropertySheetBase.h"
#include "RestrictionSet.h"

#include <deque>

class Plant;

class ComponentWarmingRadiusProps : public ComponentRadiusBurstProps
{
public:
    ComponentWarmingRadiusProps()
    :ComponentRadiusBurstProps()
    ,PulseInitialDelay(0.0f)
    {}
    
    float	PulseInitialDelay;
    DamageInfoProps GridItemDamageProps;
    DamageInfoProps PlantDamageProps;
};

class ComponentWarmingRadiusGlobalProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ComponentWarmingRadiusGlobalProperties, PropertySheetBase, RtClass);
	
	GridItemRestrictionSet WarmableGridItems;
	std::vector<RtWeakPtr<const class LevelModuleProperties>> StagesThatEnableWarming;
};

class ComponentWarmingRadius : public ComponentRadiusBurst
{
public:
	RT_CLASS_DEFINE(ComponentWarmingRadius, ComponentRadiusBurst, RtClass);

    void SetRadiusProps(const ComponentWarmingRadiusProps &i_props);

protected:
	void onBegin() override;

	void beginApply() override;
	void beginCoolDown() override;
    
protected:
	RtWeakPtr<ComponentWarmingRadiusGlobalProperties> getGlobalProps() const;
	void thawGridItems();
    void thawPlants();
    bool shouldBeEnabledInCurrentLevel() const;
    
    ComponentWarmingRadiusProps m_warming_props;
};

#endif /* defined(__PlantsVersusZombies2__ComponentWarmingRadius__) */
