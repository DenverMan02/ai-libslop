#ifndef PS3LEADERBOARDDRIVER_H_INCLUDED
#define PS3LEADERBOARDDRIVER_H_INCLUDED

#include "ILeaderboardDriver.h"

#include <np.h>

namespace Sexy
{
	class PS3AppDriver;
	class PS3LeaderboardDriver;

	class PS3LeaderboardReadContext : public LeaderboardReadContext
	{
	public:

		bool IsDone();
		bool HasError();

		void Destroy();

		uint32 GetUserRow();

	private:
		friend class PS3LeaderboardDriver;
		PS3LeaderboardReadContext(PS3LeaderboardDriver* d);
		~PS3LeaderboardReadContext();

		PS3LeaderboardDriver* mDriver;

		void Update();

		bool BuildEntryFromResults( LeaderboardEntry &e, const SceNpScoreRankData& rankData, const SceNpScoreGameInfo* gameInfo, const LeaderboardSchema *schema );

		enum
		{
			READ_ERROR = -1,
			READ_IDLE,
			READ_PENDING,
			READ_PLAYER_STATS,
			READ_STATS,
			READ_DONE,
			READ_CANCELLED
		} mState;

		UserProfile* mUser;
		LeaderboardId mLeaderboardId;
		Leaderboard::Type mType;

		int32_t mTransactionId;
		Buffer mRankData;
		Buffer mGameInfo;//

		SceNpId mNpId;
		std::vector<SceNpId> mNpIds;

		CellRtcTick mLastUpdate;
		uint32_t mTotalRecords;
	};

	class PS3LeaderboardWriteContext : public LeaderboardWriteContext
	{
	public:

		bool IsDone();
		bool HasError();

		void Destroy();

		uint32 GetEstimatedRank(){ return mEstimatedRank; };
	private:
		friend class PS3LeaderboardDriver;
		PS3LeaderboardWriteContext(PS3LeaderboardDriver* d);
		~PS3LeaderboardWriteContext();

		PS3LeaderboardDriver* mDriver;

		void Update();

		template <class T> T Aggregate( T prevValue, T newValue, LeaderboardSchema::AggregationRule rule );
		bool BuildWriteData( SceNpScoreGameInfo& outData, const SceNpScorePlayerRankData* prevRank, const SceNpScoreGameInfo* prevInfo, const LeaderboardEntry* newData, const LeaderboardSchema* schema );

		enum
		{
			WRITE_ERROR = -1,
			WRITE_IDLE,
			WRITE_PENDING,
			WRITE_FETCH_CURRENT,
			WRITE_STATS,
			WRITE_DONE,
			WRITE_CANCELLED
		} mState;

		UserProfile* mUser;
		LeaderboardId mLeaderboardId;

		int32_t mTransactionId;

		SceNpId mNpId;
		Buffer mRankData;
		Buffer mGameData;

		SceNpScoreGameInfo mGameInfo;
		LeaderboardEntry* mNewEntry;

		CellRtcTick mLastUpdate;
		uint32_t mTotalRecords;

		int64_t mWriteScore;

		//rank and score from requesting previous
		uint32_t mPreviousRank;
		int64_t mPreviousScore;

		//estimated rank returned from score write
		uint32_t mEstimatedRank;
	};

	class PS3LeaderboardDriver : public ILeaderboardDriver
	{
		struct PreviousBest
		{
			PreviousBest()
			{
				rank = -1;
				score = 0;
				time.tick = 0;
			}
			uint32_t rank;
			int64_t score;
			CellRtcTick time;
			LeaderboardEntry entry;
		};
	public:
		PS3LeaderboardDriver();
		~PS3LeaderboardDriver();
		
		bool Init();
		void Update();

		void RegisterSchema( LeaderboardId id, LeaderboardSchema *schema );
		const LeaderboardSchema *GetSchema( LeaderboardId id );

		uint32 MaxReadEntries();

		LeaderboardWriteContext* StartWriteScore( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, LeaderboardEntry *entry );
		LeaderboardReadContext* StartReadScores( UserProfile *player, LeaderboardId leaderboardId, const std::string& secondaryId, Leaderboard::Type type, uint32 startRank, uint32 maxEntries );

	protected:
		friend class PS3LeaderboardReadContext;
		friend class PS3LeaderboardWriteContext;
		
		PS3AppDriver* mAppDriver;

		int32_t GetScoreContext(UserProfile *p);
		
		void CancelRequest(PS3LeaderboardReadContext* r);
		void CancelRequest(PS3LeaderboardWriteContext* r);

		//this is a cache of the highest score we've written that hasn't shown up yet in a read
		//  indexed by leaderboard id
		typedef std::map<LeaderboardId,PreviousBest> BestScores;
		BestScores mBestScores;

		bool HasPreviousBest( const LeaderboardId &id ){ return mBestScores.count(id); }

	private:
		typedef std::pair<LeaderboardId,LeaderboardSchema*> SchemaEntry;
		typedef std::vector<SchemaEntry> LeaderboardSchemaList;
		LeaderboardSchemaList mSchemas;

		typedef std::vector<PS3LeaderboardReadContext*> LeaderboardReadRequestList;
		LeaderboardReadRequestList mReadRequests;

		typedef std::vector<PS3LeaderboardWriteContext*> LeaderboardWriteRequestList;
		LeaderboardWriteRequestList mWriteRequests;

		int32_t mScoreCtxId;
	};
};

#endif
