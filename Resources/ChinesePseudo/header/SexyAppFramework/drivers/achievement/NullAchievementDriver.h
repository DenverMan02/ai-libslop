#ifndef NULL_ACHIEVEMENT_DRIVER_H_INCLUDED
#define NULL_ACHIEVEMENT_DRIVER_H_INCLUDED

#include "IAchievementDriver.h"

namespace Sexy
{
	class NullAchievementDriver : public IAchievementDriver
	{
	public:
		bool Init(){ return true; }
		void Update(){}

		IAchievementContext* StartReadUnlockedAchievements( UserProfile* p ){ return NULL; };
		IAchievementContext* StartUnlockAchievement( UserProfile* p, AchievementId achievementId ){ return NULL; };
	};
};

#endif
