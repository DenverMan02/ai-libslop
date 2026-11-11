#ifndef XBOX360_ACHIEVEMENT_DRIVER_H_INCLUDED
#define XBOX360_ACHIEVEMENT_DRIVER_H_INCLUDED

#include "IAchievementDriver.h"

#include "Buffer.h"

namespace Sexy
{
	class UserProfile;

	//
	//
	//
	class Xbox360AchievementContext : public IAchievementContext
	{
	public:
		virtual ~Xbox360AchievementContext();

		bool IsDone();
		bool HasError();

		void Update();

		void Destroy();

		virtual void SetListener( IAchievementListener* listener ){ mListener = listener; };
		const AchievementList& GetUnlockedAchievements(){ return mAchievements; };
	private:
		friend class IAchievementListener;
		friend class Xbox360AchievementDriver;
		Xbox360AchievementContext( UserProfile *p );

		IAchievementListener* mListener;

		enum AchievementWriteState
		{
			ACH_ERROR = -1,
			ACH_IDLE,
			ACH_READ_PENDING,
			ACH_READING,
			ACH_WRITE_PENDING,
			ACH_WRITING,
			ACH_DONE
		} mState;

		UserProfile* mUser;

		//Writing
		DWORD mAchievementId;
		
		//Reading
		AchievementList mAchievements;

		Buffer mAchievementBuffer;
		HANDLE mAchievementHandle;
		XOVERLAPPED mOverlapped;
	};

	//
	//
	//
	class Xbox360AchievementDriver : public IAchievementDriver
	{
	public:
		static const int NUM_ACHIEVEMENTS = 12;

		~Xbox360AchievementDriver();

		bool Init();
		void Update();

		IAchievementContext* StartReadUnlockedAchievements( UserProfile* p );
		IAchievementContext* StartUnlockAchievement( UserProfile* p, AchievementId achievementId );

	protected:
		friend class Xbox360AchievementContext;
		void RemoveContext( Xbox360AchievementContext *c );

	private:
		friend class IAchievementDriver;
		friend class IAchievementListener;
		Xbox360AchievementDriver();

		typedef std::vector<Xbox360AchievementContext*> ContextList;
		ContextList mContexts;
	};
};

#endif
