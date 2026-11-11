/*
 * PlantAnimRig_Oakshooter.h
 *
 *  Created on: 2014-9-28
 *      Author: jianglc
 */

#ifndef PLANTANIMRIG_OAKSHOOTER_H_
#define PLANTANIMRIG_OAKSHOOTER_H_

#include "PlantAnimRig.h"
#include "OakTrainModule.h"

class PlantAnimRig_Oakshooter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Oakshooter, PlantAnimRig, RtClass);

    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
    
	void		 SetAdvanced(bool i_advanced);
    
    void         SetArrowType(oak_arrow_type i_type);
    int          GetArrowType() const;
    
    bool PlayArrowAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
    std::vector<std::string> GetMiniGameLayers();
    
public:
	bool	m_isAdvanced;
    int     m_arrow_type;
    
protected:
    virtual void onPopAnimInitialized() override;
};


#endif /* PLANTANIMRIG_OAKSHOOTER_H_ */
