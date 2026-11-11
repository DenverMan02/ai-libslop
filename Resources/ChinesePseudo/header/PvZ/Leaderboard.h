
#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_

#include "Precompile.h"

class GameCenterProxy;

namespace Leaderboard
{
	void Init(GameCenterProxy* i_gcp);
	void Shutdown();
	
	void SubmitScore(const std::string& i_leaderboard, int i_score);
    void Show(const std::string& i_leaderboard);
}

#endif 
