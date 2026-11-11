//
//  DifficultyLevelInfo.h
//  PlantsVersusZombies2
//
//  Created by Matt Westhoff on 10/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DifficultyLevelInfo__
#define __PlantsVersusZombies2__DifficultyLevelInfo__

#include "Precompile.h"

namespace Message
{
	void WinLossRatioComputed(float i_ratio, short i_level);
}

class DifficultyLevelInfo
{
public:
	DifficultyLevelInfo();
	virtual ~DifficultyLevelInfo() {}
	
	void RecordWin();
	void RecordLoss();
	void IncreaseLevel();
	void DecreaseLevel();
	int GetLevel() const;
	float CalculateRatio();
	bool HasResults();
	
private:
	void addResult(int i_result);
	void updateLevel();
	
public: //for serialization
	short mLevel;
	short mStreak;
	std::vector<short> mResults;
};

#endif /* defined(__PlantsVersusZombies2__DifficultyLevelInfo__) */
