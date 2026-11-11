/*
 * PVZ1ModeDataPacket.h
 *
 *  Created on: 2021-7-31
 *      Author: zhousen
 */

#ifndef PVZ1MODEDATAPACKET_H_
#define PVZ1MODEDATAPACKET_H_

enum class PVZ1ModeAPIContext
{
	None,
	Get_MainEntry,
	Post_StartPlay,
	Post_EndPlay
};

enum class PVZ1ModeAPIResponseStatus
{
	None,
	WaitingOnResponse,
	ResponseSuccess,// all challenges pass
	ResponseFailChallengeNetwork,// not all challenges pass
	ResponseFailNetwork,// time energy is over
	ResponseFailInvalidData
};

enum PVZ1ModeResultType
{
	PVZ1_Result_Type_Invalid = -1,
	PVZ1_Win = 0,
	PVZ1_ChallengeLoss,
	PVZ1_TimeEnergyLoss,
	PVZ1_EatBrain,
	PVZ1_Result_Type_Max,
};


enum PVZ1_HOW_TO_PLAY_TYPE
{
    PVZ1_HOW_TO_PLAY_TIME_ENERGY,
    PVZ1_HOW_TO_PLAY_MAIN_MODE,
    PVZ1_HOW_TO_PLAY_FIRST_HARD_LEVEL,
};

struct PVZ1ModeLevelBonusData
{
	PVZ1ModeLevelBonusData() {
		ItemID = 0;
		ItemCount = 0;
		IsFirstReward = false;
	}
    int ItemID;// bonus item id
    int ItemCount;// bonus item count
    bool IsFirstReward;// if item is first reward bonus
};

struct PVZ1ModeLevelChallengeBonusData
{
    std::vector<S2C_BonusInfo> BonusList;
};

struct PVZ1ModeLevelBonusNetworkData
{
	PVZ1ModeLevelBonusNetworkData() {
		BasicBonusList.clear();
		FirstRewardBonusList.clear();
		ChallengeBonusList.clear();
		TimeEnergyCost = 0;
		FirstRewardLevel = 0;
	}
	std::vector<PVZ1ModeLevelBonusData> BasicBonusList;
	std::vector<PVZ1ModeLevelBonusData> FirstRewardBonusList;
	std::vector<std::vector<S2C_BonusInfo> > ChallengeBonusList;
	int TimeEnergyCost;
	int FirstRewardLevel;// check if is first reward, 1 = yes, 0 = no.
};


// not use now
class PVZ1ModeChallengeProperty : public PropertySheetBase
{
public:
    PVZ1ModeChallengeProperty();
    virtual std::string GetPropertyDesc();

protected:
    std::string BaseDesc = "[PVZ1_CHALLENGE_0]";
};

namespace Message
{
	// Subscribe to handle the result of the PVZ1NetworkIssue dialog.
	void PVZ1ModeNetworkIssueDecision(int i_context, int i_decision);
	void PVZ1ModeNetworkResponseReceived(int i_context, int i_status);
}

#endif /* PVZ1MODEDATAPACKET_H_ */
