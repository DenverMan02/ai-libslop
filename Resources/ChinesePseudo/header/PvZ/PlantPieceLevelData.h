//
//  PlantPieceLevelData.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-5-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantPieceLevelData_h
#define PlantsVersusZombies2_PlantPieceLevelData_h

#include "Precompile.h"
#include "RtObject.h"

struct PlantPieceLevel
{
    std::string sPlantName;
    std::string sLevelName;
    std::string sLevelContent;
    
	PlantPieceLevel()
    {
        sPlantName = "";
        sLevelName = "";
        sLevelContent = "";
    }
};

class PlantPieceLevelData : public Sexy::RtObject
{
public:
	
    RT_CLASS_DEFINE(PlantPieceLevelData, Sexy::RtObject, RtClass);
    
    const std::vector<PlantPieceLevel> & GetData() { return m_PlantPieceLevelDataArray; }
    
private:
    
	std::vector<PlantPieceLevel> m_PlantPieceLevelDataArray;
};

#endif
