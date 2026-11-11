#ifndef __LEADERBOARDMANAGER_H__
#define __LEADERBOARDMANAGER_H__

#include "Common.h"

#include "Buffer.h"

#include "LeaderboardSchema.h"

#include <vector>
#include <string>
#include <utility>

namespace Sexy
{
	class UserProfile;
	class LeaderboardReadContext;
	class LeaderboardWriteContext;

	typedef std::string LeaderboardId;

	///////////////////////////////////////////////////////////////////////////
	// A single row of leaderboard data, used for both reading and writing
	///////////////////////////////////////////////////////////////////////////
	class LeaderboardEntry
	{
	public:
		struct FieldData
		{
		public:
			static const uint32 MAX_STRING_FIELD = 32;
			static const uint32 MAX_BINARY_FIELD = 64;

			FieldData();

			FieldData( int32 value );
			FieldData( int64 value );
			FieldData( float value );
			FieldData( double value );
			FieldData( const SexyString &value );
			FieldData( const Buffer &value );

			LeaderboardSchema::DataType type;

			union
			{
				int32 i;
				int64 i64;
				float f;
				double d;

				struct
				{
					uint32 sSize;
					SexyChar s[MAX_STRING_FIELD];
				};

				struct
				{
					uint32 bSize;
					uchar b[MAX_BINARY_FIELD];
				};
			};
		};

		bool HasField( const std::string &fieldId ) const;

		void SetField( const std::string &fieldId, const FieldData &d );
		const FieldData* GetField( const std::string &fieldId ) const;

		int32 GetIntValue( const std::string& fieldId ) const;
		int64 GetInt64Value( const std::string& fieldId ) const;
		float GetFloatValue( const std::string& fieldId ) const;
		double GetDoubleValue( const std::string& fieldId ) const;
		SexyString GetStringValue( const std::string& fieldId ) const;
		bool GetBinaryValue( const std::string& fieldId,  Buffer &b ) const;

	private:
		typedef std::pair< std::string, FieldData > FieldEntry;
		typedef std::vector<FieldEntry> FieldList;
		FieldList mFields;
	};

	///////////////////////////////////////////////////////////////////////////
	// High level leaderboard data access model
	///////////////////////////////////////////////////////////////////////////
	class Leaderboard
	{
	public:
		enum Type
		{
			OVERALL,
			FRIENDS,
			PLAYER_CENTER,
			PLAYER_ONLY,
			ESTIMATED,//takes an entry with an estimated rank, and sorts it in to the results
			//...
		};

		LeaderboardId GetId();
		Type GetType();

		SexyString GetName();

		bool IsInitialLoad();
		bool IsLoading();
		bool HasError();

		uint32 GetWindowStart();
		uint32 GetWindowSize();

		//XXX: Document me
		void SetWindowCenter( uint32 row );

		uint32 TotalNumRows();

		//locate the row containing the requesting user, or -1
		uint32 GetUserRow();

		//Document me
		const LeaderboardEntry *GetRow( uint32 row );

		void Destroy();

	protected:
		friend class LeaderboardManager;

		Leaderboard( UserProfile *p, LeaderboardId leaderboardId, const std::string& secondaryId, Type t, LeaderboardEntry* estimatedEntry = NULL );
		~Leaderboard();

		void Init();
		void FetchMoreData( uint32 windowStart );

		void Update();

	private:
		LeaderboardId mId;
		std::string mSecondaryId;

		Type mType;

		enum State
		{
			LB_ERROR = -1,
			LB_IDLE,
			LB_INIT_LOAD,
			LB_LOADING,
			LB_DONE,
			_NUM_LB_STATES
		} mState;

		UserProfile *mUser;

		uint32 mWindowStart;
		uint32 mWindowSize;

		bool mPendingRequest;
		uint32 mRequestedCenter;

		LeaderboardReadContext *mReadRequest;
		LeaderboardReadContext *mCurrentResults;

		LeaderboardEntry* mEstimatedEntry;
	};


	///////////////////////////////////////////////////////////////////////////////
	// LeaderboardManager - Don't extend this
	///////////////////////////////////////////////////////////////////////////////
	class LeaderboardManager
	{
	public:
		LeaderboardManager();
		~LeaderboardManager();
		
		void Update();
		
		void RegisterSchema( LeaderboardId id, LeaderboardSchema *schema );
		const LeaderboardSchema *GetSchema( LeaderboardId id );

		//for single player... will open and close a session as needed
		LeaderboardWriteContext* WriteStats( UserProfile *profile, LeaderboardId id, const std::string& secondaryId, LeaderboardEntry *e );

		//Create a leaderboard and start fetching the initial set of data.
		Leaderboard *CreateLeaderboard( UserProfile *profile, LeaderboardId viewId, const std::string &secondaryId, Leaderboard::Type type, LeaderboardEntry *estmatedEntry = NULL  );

		//How many rows to read at a time by default, defaults to driver max.  Could be per leaderboard?
		uint32 GetReadSize(){return mReadSize;}
		void SetReadSize(uint32 size){mReadSize = size;}
	protected:
		friend class Leaderboard;

		void RemoveLeaderboard( Leaderboard *l );
	private:
		uint32 mReadSize;

		typedef std::vector<Leaderboard*> LeaderboardList;
		LeaderboardList mLeaderboards;
	};
};

#endif
