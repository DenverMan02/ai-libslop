//
//  PVZGameInfo.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PVZGameInfo_H__
#define __PVZGameInfo_H__

#include "Precompile.h"
#include "RtObject.h"

class PVZGameInfo : public RtObject
{
public:
	RT_CLASS_DEFINE(PVZGameInfo, RtObject, RtClass);
	
	PVZGameInfo()
	{};
	
	PVZGameInfo(const std::string& i_gameName, const std::string& i_buildInfo, uint32 i_launchTime)
	{
		GameName = i_gameName;
		BuildInfo = i_buildInfo;
		m_launchTime = i_launchTime;
	}
	
public:
	std::string 	GameName;		// Name of our game
	std::string 	BuildInfo;		// Build version information
	
	uint64 GetUptimeMS() const;		// Returns the number of milliseconds that have elapsed since the game was launched

private:
	uint64			m_launchTime;	// Time at which we started the game
};

#endif // __PVZGameInfo_H__
