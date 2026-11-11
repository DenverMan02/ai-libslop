//
//  JoustStatus
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/13/17.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JoustStatus__
#define __PlantsVersusZombies2__JoustStatus__

//#include "CurrentProfileTracker.h"
#include "JoustDataPackets.h"
#include "Singleton.h"

class JoustLeaderboardData
{
public:
	std::vector<JoustPlayerData>	Players;
	
	JoustLocalPlayerData			LocalPlayer;
};

class JoustStatus : public LazySingleton<JoustStatus>
{
public:
	JoustStatus();
	
	void DoFirstInit() {}

	JoustLeaderboardData&	GetLeaderboardData()			{ return LeaderboardData; }
	
	void SetCurrentMatch(JoustAPIResponseMatch& i_match);
	void ClearCurrentMatch()								{ CurrentMatchSet = false; }
	bool HasCurrentMatch() const							{ return CurrentMatchSet; }
	JoustAPIResponseMatch* GetCurrentMatch();
	
	bool HasPCPIDOverride()									{ return !PCPIDOverride.empty(); }
	const std::string& GetPCPIDOverride()					{ return PCPIDOverride; }
	void SetPCPIDOverride(const std::string& i_override)	{ PCPIDOverride = i_override; }

	bool HasURLOverride()									{ return !URLOverride.empty(); }
	const std::string& GetURLOverride()						{ return URLOverride; }
	void SetURLOverride(const std::string& i_override)		{ URLOverride = i_override; }
	
	void SetMatchCompleteData(JoustAPIResponseMatchComplete& i_data)	{ MatchCompleteData = i_data; }
	const JoustAPIResponseMatchComplete& GetMatchCompleteData()			{ return MatchCompleteData; }
	bool HasMatchCompleteAward()										{ return MatchCompleteData.NeedsAward; }
	void ClearMatchCompleteAward()										{ MatchCompleteData.NeedsAward = false; }

	int	GetLevelEndExtensions()								{ return LevelEndExtensions; }
	void AddLevelEndExtension()								{ LevelEndExtensions++; }
	void ClearLevelEndExtensions()							{ LevelEndExtensions = 0; }

	bool HasLeagueChangeEvent()								{ return LeagueChangeEvent.HasLeagueChangeEvent; }
	const JoustAPIResponseLeagueChange& GetLeagueChangeEvent()	{ return LeagueChangeEvent; }
	void SetLeagueChangeEvent(JoustAPIResponseLeagueChange& i_leagueChange)		{ LeagueChangeEvent = i_leagueChange; }
	void ClearLeagueChangeEvent()							{ LeagueChangeEvent.HasLeagueChangeEvent = false; }
	
	JoustTournamentData& GetTournamentData()				{ return TournamentData; }

private:
	//void onProfileCreated(const PlayerInfoPtr& i_playerInfo);
	
	JoustLeaderboardData			LeaderboardData;
	
	bool							CurrentMatchSet;
	JoustAPIResponseMatch			CurrentMatch;
	
	std::string						PCPIDOverride;
	std::string						URLOverride;
	
	JoustAPIResponseMatchComplete	MatchCompleteData;
	int								LevelEndExtensions;

	JoustAPIResponseLeagueChange	LeagueChangeEvent;
	
	JoustTournamentData				TournamentData;
	
};

#endif
