#ifndef PS3_ACHIEVEMENT_DRIVER_H_INCLUDED
#define PS3_ACHIEVEMENT_DRIVER_H_INCLUDED

#include "IAchievementDriver.h"
#include "Buffer.h"

#include <np.h>

#include "CritSect.h"


namespace Sexy
{
	class UserProfile;

	//
	// PS3AchievementContext
	//
	class PS3AchievementContext : public IAchievementContext
	{
	protected:
		const AchievementList& GetUnlockedAchievements(){ return mAchievements;};

		bool IsDone(){ return mState == ACH_DONE; };
		bool HasError(){ return mState == ACH_ERROR; };

		void Destroy(){};

		void SetListener( IAchievementListener *listener ){ mListener = listener; };

	private:
		friend class PS3AchievementDriver;
		PS3AchievementContext( UserProfile *p );

		IAchievementListener *mListener;

		UserProfile* mUser;

		// Writing
		SceNpTrophyId mId;

		// Reading
		AchievementList mAchievements;

		enum
		{
			ACH_ERROR = -1,
			ACH_IDLE,
			ACH_READING,
			ACH_WRITING,
			ACH_DONE
		} mState;
	};

	//
	// PS3AchievementDriver
	//
	class PS3AchievementDriver : public IAchievementDriver
	{
	public:
		virtual ~PS3AchievementDriver();

		bool Init();
		void Update();

		IAchievementContext* StartReadUnlockedAchievements( UserProfile* p );
		IAchievementContext* StartUnlockAchievement( UserProfile* p, AchievementId achievementId );

		void SetDisabled( bool disabled ){ mDisabled = disabled; };
	private:
		static void TrophyThreadProc( void *param );
		static int	TrophyInitCallback(	SceNpTrophyContext context, SceNpTrophyStatus status, int completed, int total, void *arg );

	private:
		friend class IAchievementDriver;
		friend class PS3AppDriver;

		PS3AchievementDriver();

		enum
		{
			STATE_ERROR = -1,
			STATE_INIT,
			STATE_INIT_SYNC,
			STATE_READY,
		} mState;

		bool mDisabled;

		SceNpTrophyContext mNpContext;
		SceNpTrophyHandle mNpHandle;

		typedef std::vector<PS3AchievementContext*> ContextList;

		CritSect mContextCritSect;
		Condition mTrophyCondition;
		Condition mTrophyShutdown;

		ContextList mContexts;
	};
};

#endif
