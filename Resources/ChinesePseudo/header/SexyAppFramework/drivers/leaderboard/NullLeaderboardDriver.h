#ifndef NULLLEADERBOARDDRIVER_H_INCLUDED
#define NULLLEADERBOARDDRIVER_H_INCLUDED

#include "ILeaderboardDriver.h"

namespace Sexy
{
	class NullLeaderboardDriver : public ILeaderboardDriver
	{
	public:
		NullLeaderboardDriver();
		
		bool Init();
		void Update();

		void RegisterSchema( LeaderboardId id, LeaderboardSchema *schema );
		const LeaderboardSchema *GetSchema( LeaderboardId id );

		uint32 MaxReadEntries();

		LeaderboardWriteContext* StartWriteScore( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, LeaderboardEntry *entry );
		LeaderboardReadContext* StartReadScores( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, Leaderboard::Type type, uint32 startRank, uint32 maxEntries );
	};
};

#endif
