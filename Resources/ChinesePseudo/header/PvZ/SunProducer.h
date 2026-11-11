#ifndef __SUNPRODUCER_H__
#define __SUNPRODUCER_H__

#include "PowerPropertySheet.h"

class CollectableSun;

namespace Message
{
	void SunProducedByPlant(CollectableSun* i_sun);
	void SunProductionTriggered(BoardEntity* i_owner);
}

class PlantAction;
class BoardEntity;
class SunProducer
{
public:
	SunProducer(BoardEntity& owner, const PowerPropsSunProducer& props, SexyVector2 spawnOffset);
	virtual ~SunProducer(){}
	
	void Execute();
	static bool CanProduceSun();
	
private:
	BoardEntity& m_owner;
	const PowerPropsSunProducer& m_props;
	SexyVector2 m_spawnOffset;
	
};
#endif
