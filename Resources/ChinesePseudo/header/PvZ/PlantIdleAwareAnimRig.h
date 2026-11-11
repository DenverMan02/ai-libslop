#ifndef PlantIdleAwareAnimRig_hpp
#define PlantIdleAwareAnimRig_hpp

#include "PlantAnimRig.h"
#include "IdleAnimationSelector.h"

class PlantIdleAwareAnimRig : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantIdleAwareAnimRig, PlantAnimRig, RtClass);
	virtual ~PlantIdleAwareAnimRig() {}
	
	bool PlayIdleLooped() override;
	
protected:
	void onPopAnimInitialized() override;
	
	IdleAnimationSelector m_idleSelector;
};

#endif /* PlantIdleAwareAnimRig_hpp */
