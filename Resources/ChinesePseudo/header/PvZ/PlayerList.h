//
//  PlayerList.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 4/20/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlayerList__
#define __PlantsVersusZombies2__PlayerList__

#include <iostream>
#include <string>
#include <map>
#include "SexyAppFramework/Common.h"

// NOTE: This class is just a stub.

class UUIDCreator;

class PlayerList
{
public:
	PlayerList(UUIDCreator& i_uuidCreator);
    ~PlayerList();

	std::map<std::string, std::string>& Get();  // how do you know the current player
	std::string Create(std::string i_name);
	void Load(std::string i_pcp_id);  // handle offline mode
	void LoadViaFacebook();   // handle offline mode
	void Remove(std::string i_pcp_id);
	void Rename(std::string i_pcp_id, std::string i_name);  // offline, so we need to know about deltas
	void LogoutFacebook(std::string i_pcp_id);
	bool IsBoundToFacebook(std::string i_pcp_id);
	
private:

	UUIDCreator& m_UUIDCreator;
	std::map<std::string, std::string> idToName;
};

#endif /* defined(__PlantsVersusZombies2__PlayerList__) */