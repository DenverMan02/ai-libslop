//
//  TestableSingletons.h
//  PlantsVersusZombies2
//
//  Created by PopCap User on 12/13/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TestableSingletons_h
#define PlantsVersusZombies2_TestableSingletons_h

#include "ProfileMgr.h"

class TestableProfileMgr : ProfileMgr
{
public:
    static void ResetInstance(){
        m_instance = NULL;
    }
};

class TestableTimeMgr : TimeMgr
{
public:
    static void ResetInstance(){
        m_instance = NULL;
    }
};

class TestablePVZDB : PVZDB
{
public:
    static void ResetInstance(){
        if(m_instance != NULL && m_instance->IsInitialized())
            m_instance->Shutdown();

        m_instance = NULL;
    }
};

class FakeResourceManager: public ResourceManager
{
public:
    FakeResourceManager():ResourceManager(gLawnApp)
    {
    }
    
    RtWeakPtr<BaseResource> GetResourceForStringId(ResourceInfoClass* theType, const std::string& theId, bool optional = false){
        return RtWeakPtr<BaseResource>();
    }
};

#endif
