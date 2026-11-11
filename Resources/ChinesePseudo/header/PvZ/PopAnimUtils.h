//
//  PopAnimUtils.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 3/28/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PopAnimUtils_h
#define PlantsVersusZombies2_PopAnimUtils_h

#include <string>

#include "TimeMgr.h"

namespace Sexy {
class PopAnim;
}  // namespace Sexy

void VSyncPopAnimUpdate(Sexy::PopAnim* i_pam, pvztime_t* o_stepTime, pvztime_t i_t, pvztime_t i_dt);

std::string GetActualImageName(std::string i_imageFilename);

#endif
