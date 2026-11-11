//
//  JoustNetworkOverrides.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/13/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef JoustNetworkOverrides_hpp
#define JoustNetworkOverrides_hpp

#ifndef WANTS_CHEATS_DISABLED

#include "JoustDataPackets.h"
#include "StructuredData.h"

namespace JoustNetworkOverrides
{
	enum NetFlowOverride
	{
		Joust_Flow_Override_None,
		Joust_Flow_Override_TournamentEndSame,
		Joust_Flow_Override_TournamentEndAdvance,
		Joust_Flow_Override_TournamentEndDecline,
		Joust_Flow_Override_TournamentFTUE,
		Joust_Flow_Override_MatchBadResponse
	};

	std::string GetCurrentOverride();
	Sexy::StructuredData* GetOverrideData();
	
	bool CreateOverride(Sexy::StructuredData& i_requestData, JoustAPIContext i_context);  // Returns true if override created
	

	
	// Specific Overrides
	bool CreateOverride_NewTournament(Sexy::StructuredData& i_requestData, JoustAPIContext i_context, int i_prevLeague, int i_newLeague);
	bool CreateOverride_MatchBadResponse(Sexy::StructuredData& i_requestData, JoustAPIContext i_context);

}

#endif

#endif

