//
//  TimeLevelData.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-11-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TimeLevelData_h
#define PlantsVersusZombies2_TimeLevelData_h

#include "Precompile.h"
#include "RtObject.h"

struct TimeLevelNodeInfo
{
    int         iLevelID;
    std::string strLevelName;
    uint32      iDuration;
    
    TimeLevelNodeInfo() {}
};

class TimeLevelData : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(TimeLevelData, Sexy::RtObject, RtClass);
    
    const std::vector<TimeLevelNodeInfo> & GetData() { return m_vTimeLevelDataArray; }
    
    uint32& GetAgainDuration() { return m_iTimeLevelAgainDuration; }
    
private:
    
    uint32                         m_iTimeLevelAgainDuration;
    
	std::vector<TimeLevelNodeInfo> m_vTimeLevelDataArray;
};


#endif
