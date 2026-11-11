//
//  DefineIDMgr.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 16-2-25.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DefineIDMgr__
#define __PlantsVersusZombies2__DefineIDMgr__

#include "Singleton.h"

class DefineIDMgr : public LazySingleton<DefineIDMgr>
{
public:
    
    DefineIDMgr();
    virtual ~DefineIDMgr();
    
    std::string GetUserDefineID();
    
    std::string GetNewUserDefineID();

    std::string GetSignature();

    void        ClearSaveDefineID();
};

#endif /* defined(__PlantsVersusZombies2__DefineIDMgr__) */
