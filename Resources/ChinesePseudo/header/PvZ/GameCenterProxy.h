#ifndef __PlantsVersusZombies2__GameCenterProxy__
#define __PlantsVersusZombies2__GameCenterProxy__

#include "Precompile.h"
#include <string>
#include "SexyAppFramework/RtDelegate.h"

namespace Message
{
	inline void GameCenterAuthenticationChanged(bool /*i_connected*/) {}
}

class GameCenterProxy
{
public:
    GameCenterProxy();
    ~GameCenterProxy();
    
    bool IsConnected() const;
    bool IsLoginWindowVisible() const;
    bool IsBeingDisplayed() const;

    void Connect();
    void QueueAchievement(const std::string&);
    void QueueAchievement(const std::string&, float);
    void SubmitAchievements();
    void SubmitScoreToLeaderboard(int, const std::string&);
    void ResetAchievements();
	void FetchAchievements();

	void ShowAchievementView();
	void ShowLeaderboardView(const std::string&);
    
private:
    
    void* m_driver;
    void* m_delegate;
};

#endif // __PlantsVersusZombies2__GameCenterProxy__
