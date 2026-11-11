//
//  TLogCache.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-19.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TLogCache__
#define __PlantsVersusZombies2__TLogCache__

#include "Precompile.h"
#include "RtObject.h"

class TLogCache : public RtObject
{
public:
    RT_CLASS_DEFINE(TLogCache, RtObject, RtClass);
    
    TLogCache();
    virtual ~TLogCache();
    
    std::string getLastCache();
    
    void AddCache(const std::string& str);
    
private:
    std::vector<std::string> m_cacheList;
};

typedef RtWeakPtr<class TLogCache> TLogCachePtr;

#endif /* defined(__PlantsVersusZombies2__TLogCache__) */
