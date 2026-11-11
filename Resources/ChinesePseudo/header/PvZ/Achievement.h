
#ifndef _ACHIEVEMENT_MANAGER_H_
#define _ACHIEVEMENT_MANAGER_H_

#include "Precompile.h"

class GameCenterProxy;

namespace Achievement
{
	void Init(GameCenterProxy* i_gcp);
	void Shutdown();
	
	void Queue(const std::string& i_achievement, float i_percent);
	void SubmitAll();
	void ResetAll();
    
    void ShowAll();

    void SubmitOneShotAchievement(const std::string& i_achievement);
    bool IsNewAchievement(const std::string& i_achievement);
}

#endif
