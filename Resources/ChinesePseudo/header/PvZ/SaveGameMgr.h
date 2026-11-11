//
//  SaveGameMgr.h
//  PlantsVersusZombies2
//
//  Created by jsola on 4/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SaveGameMgr_h
#define PlantsVersusZombies2_SaveGameMgr_h

#include "Core.h"
#include "PVZVersion.h"

class SaveGameHeader : public RtObject
{
public:
	RT_CLASS_DEFINE(SaveGameHeader, RtObject, RtClass);
	
	SaveGameHeader() : PlayerIndex(-1), ProfileVersion(-1), HardMode(false)
	{}

	bool VersionCheck(const SaveGameHeader& i_other);
	
	/// Verify level
	std::string		LevelName;
    bool            HardMode;
	std::vector<std::string> ResourceGroups;

	/// Verify profile state and version
	std::string 	PlayerID;
	int32_t			PlayerIndex;
	int32			ProfileVersion;
	
	/// Verify game data version
	PVZVersion		AppVersion;
	PVZVersion		RSBVersion;
	bool			IsFullRSB;
};

class SaveGameMgr : public LazySingleton<SaveGameMgr>
{
public:
	bool DoesSaveGameExist(bool i_special);
	bool IsSaveGameValidForCurrentPlayerID(bool i_special);
	
	bool CanLoadGame(bool i_special);
	
	bool TrySaveGame(bool i_special);
	bool TryLoadGame(bool i_special);
	void ClearSaveGame(bool i_special);
	
	bool GetResourceGroupsRequiredForLoad(std::vector<std::string>& o_resourceGroups, bool i_special);
	
private:
	std::string getSaveLocationFor(const std::string& i_fileName, bool i_special) const;
	SaveGameHeader generateHeaderForCurrentProfile();
	bool loadSaveGameHeader(SaveGameHeader& o_header, bool i_special);
	bool saveSaveGameHeader(const SaveGameHeader& i_header, bool i_special);
};

#endif
