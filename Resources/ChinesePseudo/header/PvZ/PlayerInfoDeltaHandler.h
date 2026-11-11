//
//  PlayerInfoDeltaHandler.h
//  PlantsVersusZombies2
//
//  Created by Jos van Schagen, Yang Han on 2/25/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlayerInfoDeltaHandler__
#define __PlantsVersusZombies2__PlayerInfoDeltaHandler__

#include "OfflineDataPersistor.h"
#include "ProfileMgr.h"

class PlayerInfoDeltaHandler : public OfflineDataPersistor
{
	
public:
	// Constructor
	PlayerInfoDeltaHandler();
	virtual ~PlayerInfoDeltaHandler() {}
	
	bool CreateDelta();
	virtual void UpdateFileIndex();
	
protected:
	virtual std::string getOfflineFilename();
	void FillCurrentMap(IndexToPlayerInfoMap& currentMap);
	void SnapshotToDelta(IndexToPlayerInfoMap& currentMap, IndexToPlayerInfoMap& snapshotMap);
	
private:
	int getOtherIndex() const;
	int m_offlineFilenameIndx;
}; // End of PlayerInfoDeltaHandler

#endif /* defined(__PlantsVersusZombies2__PlayerInfoDeltaHandler__) */
