//
//  OfflineDataPersistor.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__OfflineDataPersistor__
#define __PlantsVersusZombies2__OfflineDataPersistor__

#include <string>
#include "IDataPersistor.h"
#include "PVZDB.h"

class OfflineDataPersistor : public IDataPersistor
{
public:
	OfflineDataPersistor(const char* i_filename = "pp.dat", PVZDB::TableIndex tableIndex = PVZDB::TABLE_PLAYER_PROFILES);
	void Load();
	void LoadWithNotify();
	bool Save();
	bool IsFileExist();

protected:
	virtual std::string getOfflineFilename();
	virtual bool saveTableToFile(const std::string& i_filename);
	virtual void loadTableFromFile(const std::string& i_filename);
	virtual void notifyDataLoaded();
	
	std::string m_filename;
	PVZDB::TableIndex m_tableIndex;

	static bool s_ppSave;
};

namespace Message
{
	void PersistorLoadComplete();
}

#endif /* defined(__PlantsVersusZombies2__OfflineDataPersistor__) */
