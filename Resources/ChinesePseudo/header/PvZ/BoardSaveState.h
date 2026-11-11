/*
 * BoardSaveState.h
 *
 *  Created on: 2021-7-2
 *      Author: admin
 */

#ifndef BOARDSAVESTATE_H_
#define BOARDSAVESTATE_H_

#include "GameObject.h"
#include "ArtifactMgr.h"
#include "MetricsCollector.h"
#include "BoardEnums.h"

///
/// BoardSaveState - All data required to bring our board and various systems back from the grave
///
class BoardSaveState : public GameObject
{
public:
	RT_CLASS_DEFINE(BoardSaveState, GameObject, RtClass);

	virtual bool Serialize(const RtSerializeContext& inContext) override;
public:
	/// Serializable variables go here
	pvztime_t CurrentTime;

	std::vector<int8> 	PlantRow;
	std::vector<pvztime_t> 	TimeRowGotLawnMowered;
	std::vector<TodSmoothArray> RowPickingArray;
	std::vector<int8>	GridSquareType;
	std::vector<int32>	GridSquareLocked;
	std::vector<int8>	MowerAllowedInRow;


	Point BoardPosition;

	GameplayMetrics		SavedMetrics;
	//PVZ2_CHINESE_BEGIN
    bool m_hardModule;

    bool m_bYetiDie;
    bool m_bYetiFlee;
    //xiezhen   don't save present, user can copy the game file for cheat
    //std::vector<std::string> m_pendingActivityRewards;

	std::string m_FriendPlantName;

    bool        m_bEventUnLockState;

    bool m_bImmediatePlantFood;

    // collect info save
    std::vector<SunGet> SunGetInfo;
    std::vector<int> SunConsumeInfo;
    std::vector<PlantfoodGet> PlantfoodGetInfo;
    std::vector<int> PlantfoodConsumeInfo;
    std::vector<int> PowerupConsumeInfo;
    std::vector<int> ChallengeCount;

    float				SunShovelOverridePercent;
    bool				SunShovelRefundDisabled;

    int				iFestivalGameMode;
    int				iFestivalGameLevel;

    bool            bIsBossLevel;

    std::string     sFestivalGameWishPlantName;
    int              m_redpacksCollected;
    int              m_specialCoinCollected;
    int              m_killZombieProductSunmoneyNum;
    int				 m_levelDefinitionRandomSetIndex;
    ArtifactData	 m_currentArtifact;
    //PVZ2_CHINESE_END
};


#endif /* BOARDSAVESTATE_H_ */
