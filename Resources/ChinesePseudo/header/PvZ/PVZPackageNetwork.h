//
//  PVZCachedNetworkTable.h
//  PlantsVersusZombies2
//
//  Created by David Siems 4/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZPACKAGENETWORK_H__
#define __PVZPACKAGENETWORK_H__

#include "PVZDB.h"
#include "NetworkServiceManager.h"


struct WatchInfo;

class PVZPackageNetworkManager : public LazySingleton<PVZPackageNetworkManager>
{
public:
	PVZPackageNetworkManager()
	: m_completedRequests(0)
	{
		// Do nothing.
		//PVZ2_CHINESE_START
        m_watchInfos.clear();        
		//PVZ2_CHINESE_END
	}

//PVZ2_CHINESE_START
	void Watch(const std::string& i_name, PVZDB::TableIndex i_tableIndex, bool i_versioned, bool i_encypted=false);
//PVZ2_CHINESE_END
    void LoadPackageFile(bool i_local=false);
    void CleanPackageCache();
	
	void CheckForUpdates(int i_retries = 0);
	bool NetworkRequestsCompleted();

	void ApplyChanges();

private:
	void onRequestFinished(int i_index, const std::string& i_json);
	std::string getLocalPathForTable(PVZDB::TableIndex i_index);

//PVZ2_CHINESE_START
    std::vector<WatchInfo> m_watchInfos;
//PVZ2_CHINESE_END
	
	std::vector<PVZDB::TableIndex> m_indicesToApply;
	std::vector<std::string> m_jsonToApply;

	int m_completedRequests;
};

class PVZLevelNetworkManager : public LazySingleton<PVZLevelNetworkManager>,  public Sexy::NetworkServiceListener
{
public:
    
    void LoadLevel(std::string i_levelName);
    std::string GetLevelLocalPath(std::string i_levelName);
    
    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);    
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    // Unused. Ignore any data coming through this path.
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context) { }
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context) { }
    
private:
    std::string m_levelName;
};

#endif
