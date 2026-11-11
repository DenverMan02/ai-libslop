#ifndef PlantsVersusZombies2_CollectableSpacetimeEnergy_h
#define PlantsVersusZombies2_CollectableSpacetimeEnergy_h

#include "Collectable.h"

class CollectableSpacetimeEnergyType : public CollectableType
{
	RT_CLASS_DEFINE(CollectableSpacetimeEnergyType, CollectableType, RtClass);

};

class CollectableSpacetimeEnergy : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableSpacetimeEnergy, Collectable, RtClass);

	CollectableSpacetimeEnergy();

	void setEnergyValue(int i_energyValue);

protected:
	virtual void onFinishMotion() override;

private:
	int EnergyValue;
};

#endif