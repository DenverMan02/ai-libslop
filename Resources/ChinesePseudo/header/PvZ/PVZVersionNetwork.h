//
//  PVZCachedNetworkTable.h
//  PlantsVersusZombies2
//
//  Created by David Siems 4/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZVERSIONNETWORK_H__
#define __PVZVERSIONNETWORK_H__

#include "NetworkServiceManager.h"
#include "PVZDB.h"
#include "PVZVersion.h"

#define PVZ2_VERSION_FILE ("pvz2_v.txt")

namespace Message
{
    void FetchVersionComplete();
}

enum VersionState
{
    VersionState_Null = 0,
    VersionState_Need,
    VersionState_Force    
};

class PVZVersionNetworkManager : public Sexy::NetworkServiceListener
{
public:
    PVZVersionNetworkManager();
	void CheckForUpdates(int i_retries = 0);
    void TryRequest();
    void OnRequestFinished(std::string i_json);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);
    
    static int GetVersionToInt(std::string i_version);
    
    VersionState CheckVersionApp();
    bool IsRvsEnable();
    std::string GetUpdateUrl();
    
    void CheckVersionFiles();
    
private:
    
    int         LoadLocalVersionInfo();
    void        SaveVersionInfoToLocal(int theInfo);
    
    void ComparePVZVersion(const PVZVersion& local_version,const PVZVersion& net_version);

    int         m_retriesLeft;
    bool        m_rvsEnable;
    int         m_versionApp;
    std::string m_updateUrl;
};

#endif
