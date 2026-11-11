//
//  AutoTestHelp.hpp
//  PlantsVersusZombies2
//
//  Created by shizf on 16/2/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef AutoTestHelp_h
#define AutoTestHelp_h

#include <vector>

class MapEventItem;

namespace AutoTestHelp {
    
    const MapEventItem* GetNextMainLineItem(const MapEventItem* i_level);
    const MapEventItem* GetStartMainLineItem(const MapEventItem* i_item);
    std::vector<std::vector<std::string>> GetAllWorldLevels();
}

#endif /* AutoTestHelp_h */
