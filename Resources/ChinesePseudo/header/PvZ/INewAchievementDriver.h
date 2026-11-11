/*
 * INewAchievementDriver.h
 *
 *  Created on: 2023-3-15
 *      Author: admin
 */

#ifndef INEWACHIEVEMENTDRIVER_H_
#define INEWACHIEVEMENTDRIVER_H_

#include <string>

struct AchievementInfo
{
	AchievementInfo()
	: AchievementId("")
	, AchievementName("")
	, AchievementExplain("")
	, ReachNumLimit(0)
	, Type(0)
	, ReachValue(0)
	{

	}

	AchievementInfo(const std::string& i_id, const std::string& i_name, const std::string& i_explain, int i_numLimit, int i_type, double i_value)
	: AchievementId(i_id)
	, AchievementName(i_name)
	, AchievementExplain(i_explain)
	, ReachNumLimit(i_numLimit)
	, Type(i_type)
	, ReachValue(i_value)
	{

	}

	std::string AchievementId;
	std::string AchievementName;
	std::string AchievementExplain;
	int ReachNumLimit;
	int Type;
	double ReachValue;
};

class INewAchievementDriver
{
public:
    static INewAchievementDriver* CreateNewAchievementDriver();

    virtual ~INewAchievementDriver() {}

    virtual void Initialize() = 0;

    virtual void SetAchievement(const std::string& i_id, int i_type, double i_value, std::function<void(bool)> i_callback) = 0;

    virtual void QueryAllAchievement(std::function<void(std::vector<AchievementInfo>)> i_callback) = 0;
};


#endif /* IACHIEVEMENTDRIVER_H_ */
