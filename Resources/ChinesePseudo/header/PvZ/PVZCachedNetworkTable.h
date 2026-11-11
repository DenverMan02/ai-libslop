//
//  PVZCachedNetworkTable.h
//  PlantsVersusZombies2
//
//  Created by David Siems 4/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZCACHEDNETWORKTABLE_H__
#define __PVZCACHEDNETWORKTABLE_H__

#include "PVZDB.h"

//PVZ2_CHINESE_START
struct WatchInfo
{
    std::string watchName;
    PVZDB::TableIndex watchTable;
    bool watchIsVersioned;
    bool watchIsEncypted;
    bool isFetching;
};
//PVZ2_CHINESE_END

class PVZCachedNetworkTableManager
{
public:
	PVZCachedNetworkTableManager()
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

#endif
