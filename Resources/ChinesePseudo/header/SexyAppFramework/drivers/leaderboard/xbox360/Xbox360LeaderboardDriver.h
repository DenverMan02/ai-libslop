#ifndef XBOX360LEADERBOARDDRIVER_H_INCLUDED
#define XBOX360LEADERBOARDDRIVER_H_INCLUDED

#include "ILeaderboardDriver.h"

#include "drivers/app/xbox360/Xbox360AppDriver.h"

namespace Sexy
{
	class Xbox360LeaderboardReadContext : public LeaderboardReadContext
	{
	public:
		bool IsDone();
		bool HasError();

		void Destroy();

		uint32 GetUserRow();

	private:
		friend class Xbox360LeaderboardDriver;
		Xbox360LeaderboardReadContext();

		Xbox360LeaderboardDriver* mDriver;

		void Update();

		void FieldDataFromXUserData( LeaderboardEntry::FieldData& d, const XUSER_DATA& xd );

		enum
		{
			READ_ERROR = -1,
			READ_INIT,
			READ_PENDING,
			READ_FRIENDS,
			READ_STATS,
			READ_DONE,
			READ_CANCELED,
		} mState;

		UserProfile *mUser;

		LeaderboardId mLeaderboardId;
		Leaderboard::Type mType;

		Buffer mBuffer;
		Buffer mFriendsBuffer;
		std::vector<XUID> mFriendXuids;

		XUID mXuid;
		XUSER_STATS_SPEC mStatsSpec;

		HANDLE mHandle;
		XOVERLAPPED mOverlapped;
	};

	class Xbox360LeaderboardWriteContext : public LeaderboardWriteContext
	{
	public:
		bool IsDone();
		bool HasError();

		void Destroy();

		uint32 GetEstimatedRank(){ return mEstimatedRank; };
	private:
		friend class Xbox360LeaderboardDriver;
		Xbox360LeaderboardWriteContext();

		Xbox360LeaderboardDriver* mDriver;

		void Update();

		bool BuildWriteData( XSESSION_VIEW_PROPERTIES& outData, int64 &outScore, const PXUSER_STATS_READ_RESULTS prevResults, const LeaderboardEntry* newEntry, const LeaderboardSchema* schema );

		enum WriteState
		{
			WRITE_ERROR = -1,
			WRITE_INIT,
			WRITE_PENDING,
			WRITE_FETCH_CURRENT,
			WRITE_ESTIMATE_RANK,
			WRITE_WRITING_STATS,
//			WRITE_WRITING_CLIP,
			WRITE_DONE,
			WRITE_CANCELLED
		} mState;

		XOVERLAPPED mOverlapped;

		UserProfile *mUser;
		LeaderboardId mLeaderboardId;
		LeaderboardEntry *mNewEntry;

		uint32 mPrevRank;
		uint32 mEstimatedRank;

		//Read info
		XUSER_STATS_SPEC mReadSpec;
		Buffer mReadBuffer;//PXUSER_STATS_READ_RESULTS

		//Estimate info
		XUSER_RANK_REQUEST mRankRequest;
		Buffer mEstimateBuffer;//XUSER_ESTIMATE_RANK_RESULTS

		//Write info
		XUID mXuid;
		XSESSION_VIEW_PROPERTIES mWriteData;
		std::vector<XUSER_PROPERTY> mWriteProperties;

		//Replay data
	};

	class Xbox360LeaderboardDriver : public ILeaderboardDriver
	{
	public:
		Xbox360LeaderboardDriver();
		
		bool Init();
		void Update();

		void RegisterSchema( LeaderboardId id, LeaderboardSchema *schema );
		const LeaderboardSchema *GetSchema( LeaderboardId id );

		uint32 MaxReadEntries();

		LeaderboardWriteContext *StartWriteScore( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, LeaderboardEntry *entry );
		LeaderboardReadContext *StartReadScores( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, Leaderboard::Type type, uint32 startRank = 0, uint32 maxEntries = -1 );

	private:
		friend class Xbox360LeaderboardReadContext;
		friend class Xbox360LeaderboardWriteContext;

		Xbox360AppDriver* mAppDriver;

		void CancelRequest(Xbox360LeaderboardReadContext *r);
		void CancelRequest(Xbox360LeaderboardWriteContext *r);

		bool BuildStatsReadSpec( LeaderboardId leaderboardId, XUSER_STATS_SPEC &s );

		bool UpdateSession( int player_index = -1 );

		void EndSession();
		void CloseSession();

		typedef std::pair<LeaderboardId,LeaderboardSchema*> SchemaEntry;
		typedef std::vector<SchemaEntry> LeaderboardSchemaList;
		LeaderboardSchemaList mSchemas;

		typedef std::vector<Xbox360LeaderboardReadContext*> LeaderboardReadContextList;
		LeaderboardReadContextList mReadRequests;

		typedef std::vector<Xbox360LeaderboardWriteContext*> LeaderboardWriteContextList;
		LeaderboardWriteContextList mWriteRequests;

		enum StatsWriteState
		{
			STATS_ERROR = -1,
			STATS_IDLE,
			STATS_WRITING
		} mStatsState;

		enum SessionState
		{
			SESSION_ERROR = -1,
			SESSION_NONE,
			SESSION_CREATE,
			SESSION_JOIN,
			SESSION_START,
			SESSION_IN,
			SESSION_END,
			SESSION_DELETE
		} mSessionState;
		
		//Session related state
		static const BOOL mPrivateSlot = true;

		HANDLE			mSession;
		DWORD			mSessionOwner;
		ULONGLONG		mSessionNonce;
		XSESSION_INFO	mSessionInfo;
		XOVERLAPPED		mOverlapped;
	};
};

#endif
