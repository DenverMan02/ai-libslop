#ifndef ILEADERBOARDDRIVER_H_INCLUDED
#define ILEADERBOARDDRIVER_H_INCLUDED

#include "LeaderboardManager.h"
#include "IAsyncTask.h"

/*
	Low level leaderboard data abstraction.
	Not intended for game use -- games should use the LeaderboardManager.
*/
namespace Sexy
{
	class Buffer;
	class UserProfile;

	//
	// The context for a read request.
	// Contains mNumEntries of leaderboard entries starting at mStartRank.
	//
	class LeaderboardReadContext : public IAsyncTask
	{
	public:
		virtual ~LeaderboardReadContext() {};

		virtual bool IsDone() = 0;
		virtual bool HasError() = 0;

		virtual void Destroy() = 0;

		uint32 GetStartRow(){ return mStartRank; };
		uint32 GetNumRows(){ return mNumEntries; };

		uint32 GetTotalNumRows(){ return mTotalNumEntries; };

		virtual uint32 GetUserRow(){ return -1; };

		const LeaderboardEntry& GetRow( uint32 index ){ return mData[index]; };

	protected:
		friend class LeaderboardManager;
		friend class Leaderboard;

		uint32 mStartRank;
		uint32 mNumEntries;

		uint32 mTotalNumEntries;

		typedef std::vector<LeaderboardEntry> LeaderboardData;
		LeaderboardData mData;
	};

	class LeaderboardWriteContext : public IAsyncTask
	{
	public:
		virtual ~LeaderboardWriteContext(){};

		virtual bool IsDone() = 0;
		virtual bool HasError() = 0;

		virtual void Destroy() = 0;

		// If the rank of the posted score will be better than the previous entry this will contain an estimate of your new rank.
		// otherwise, returns -1
		virtual uint32 GetEstimatedRank() = 0;
	};

	//
	// The leaderboard driver provides a low level interface for reading and writing stats.
	//
	// Additional functionality can be found in the platform independant LeaderboardManager
	// which handles staggered loading for smooth scrolling of a large list of entries.
	//
	class ILeaderboardDriver
	{
	public:
		static ILeaderboardDriver* CreateLeaderboardDriver();

		virtual ~ILeaderboardDriver() {};

		virtual bool Init() = 0;
		virtual void Update() = 0;

		virtual void RegisterSchema( LeaderboardId id, LeaderboardSchema *schema ) = 0;
		virtual const LeaderboardSchema *GetSchema( LeaderboardId id ) = 0;

		//How many entries can be returned in a single request for the current platform
		virtual uint32 MaxReadEntries() = 0;

		virtual LeaderboardWriteContext* StartWriteScore( UserProfile* player, LeaderboardId leaderboardId, const std::string& secondaryId, LeaderboardEntry* entry ) = 0;
		virtual LeaderboardReadContext* StartReadScores( UserProfile* player, LeaderboardId leaderboardId, const std::string& secondaryId, Leaderboard::Type type, uint32 startRank = 0, uint32 maxEntries = (uint32)-1 ) = 0;
	};
};

#endif
