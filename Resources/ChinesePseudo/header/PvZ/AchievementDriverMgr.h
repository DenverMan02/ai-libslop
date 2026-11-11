/*
 * AchievementDriverMgr.h
 *
 *  Created on: 2023-3-15
 *      Author: admin
 */

#ifndef ACHIEVEMENTDRIVERMGR_H_
#define ACHIEVEMENTDRIVERMGR_H_

#include "core.h"
#include "Singleton.h"
#include "INewAchievementDriver.h"

class AchievementDriverMgr : public LazySingleton<AchievementDriverMgr>
{
public:
	AchievementDriverMgr();
	~AchievementDriverMgr();

    void InitializeSDK();

    void SetAchievement(const std::string& i_id, int i_type, double i_value, std::function<void(bool)> i_callback);
    void SubmitOneShotAchievement(const std::string& i_id);


    void QueryAllAchievement(std::function<void(std::vector<AchievementInfo>)> i_callback);

private:
    INewAchievementDriver* m_achievementDriverMgr;
};


#endif /* ACHIEVEMENTDRIVERMGR_H_ */
