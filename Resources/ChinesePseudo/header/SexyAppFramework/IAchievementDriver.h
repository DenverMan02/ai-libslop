#ifndef IACHIEVEMENT_DRIVER_H_INCLUDED
#define IACHIEVEMENT_DRIVER_H_INCLUDED

#include "IAsyncTask.h"

namespace Sexy
{
	class UserProfile;
	class IAchievementContext;
	class IAchievementListener;

	typedef uint32 AchievementId;
	typedef std::vector<AchievementId> AchievementList;

	/*
	* Context for read and write operations
	*/
	class IAchievementContext : public IAsyncTask
	{
	public:
		virtual ~IAchievementContext(){};

		virtual void SetListener( IAchievementListener* listener ) = 0;

		virtual const AchievementList& GetUnlockedAchievements() = 0;
	};

	/*
	* Listener interface for callback based operation
	*/
	class IAchievementListener
	{
	public:
		virtual ~IAchievementListener();

		virtual void AchievementUnlocked( IAchievementContext* context ) { context->Destroy(); };
		virtual void AchievementRead( IAchievementContext* context ) { context->Destroy(); };
	};

	/*
	* 
	*/
	class IAchievementDriver
	{
	public:
		static IAchievementDriver *CreateAchievementDriver();

		virtual ~IAchievementDriver() {}

		virtual bool Init() = 0;
		virtual void Update() = 0;

		virtual IAchievementContext* StartReadUnlockedAchievements( UserProfile* p ) = 0;
		virtual IAchievementContext* StartUnlockAchievement( UserProfile* p, AchievementId id ) = 0;
	};
};

#endif
