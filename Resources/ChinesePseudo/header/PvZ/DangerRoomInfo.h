//
//  DangerRoomInfo.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan and Jos van Schagen on 12/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DangerRoomInfo__
#define __PlantsVersusZombies2__DangerRoomInfo__

#include "TimeMgr.h"
#include "PVZTypes.h"

namespace Message
{
	void DangerRoomCardPurchased(int i_cardCost);
}

// NOTE: New reward types should be added to DangerRoomReward functionality
enum DangerRoomRewardType
{
	DR_Reward_None,
	DR_Reward_Plant,
	DR_Reward_Small_Sun,		// +200
	DR_Reward_Medium_Sun,		// +400(?)	not implemented
	DR_Reward_Large_Sun,		// +600(?)	not implemented
	DR_Reward_Small_Plantfood,	// +1
	DR_Reward_Medium_Plantfood,	// +2	not implemented
	DR_Reward_Large_Plantfood,	// +3	not implemented
	DR_Reward_Small_Mower,		// +1
	DR_Reward_Medium_Mower,		// +2	not implemented
	DR_Reward_Large_Mower,		// +3	not implemented
	DR_Reward_PowerupWizardFingerUse,	// +1 wizard finger use.
	DR_Reward_PowerupFlickUse,			// +1 flick use.
	DR_Reward_PowerupSnowballUse		// +1 snowball use.
};

enum StoneDoubleStaus
{
    Not_Get,
    Already_Got,
};

struct DangerRoomPlantInfo
{
	DangerRoomPlantInfo()
	{
		Row = 0;
		Column = 0;
		Level = 1;
	}

	bool operator==(const DangerRoomPlantInfo& i_compareTo) const
	{
		if(Type == i_compareTo.Type && Row == i_compareTo.Row && Column == i_compareTo.Column)
		{
			return true;
		}

		return false;
	}

	PlantTypePtr Type;
	int Row;
	int Column;
	int Level;
};

typedef std::vector<DangerRoomPlantInfo> DangerRoomPlantInfos;

struct DangerRoomNewPlantInfo
{
	DangerRoomNewPlantInfo()
	{
		Row = 0;
		Column = 0;
		Level = 1;
		PlantId = 0;
	}

	bool operator==(const DangerRoomNewPlantInfo& i_compareTo) const
	{
		if(PlantId == i_compareTo.PlantId && Row == i_compareTo.Row && Column == i_compareTo.Column)
		{
			return true;
		}

		return false;
	}

	int Row;
	int Column;
	int Level;
	int PlantId;
};

typedef std::vector<DangerRoomNewPlantInfo> DangerRoomNewPlantInfos;

class DangerRoomRewardInfo
{
public:
	void ApplyReward(class DangerRoomInfo& i_dangerRoomInfo);
	
	DangerRoomRewardInfo()
	{
		m_type = DR_Reward_None;
		m_plantType = PlantTypePtr();
	}
	
	bool					IsImmediateReward();
	
	DangerRoomRewardType	m_type;
	PlantTypePtr			m_plantType;
};

struct DangerRoomInfo
{
	DangerRoomInfo()
	{
		WorldName = "";
		CurrentLevel = 0;
		HighestLevel = 1;
		PlantfoodCarryOver = 0;
		Lives = std::numeric_limits<uint8>::max(); // Roll over to fill all bits. Derp.
		SeedBank.clear();
		TimeStamp = 0;
		PrevLevel = 0;
		HasReward = true;
		HasMilestone = false;
		DangerRoomPlantList.clear();
        HasCompleted = false;
        CurrentScore = 0;
        TotalScore = 0;
        HistoryScore = 0;

        HistoryHighestScore = 0;
        CurrentSunMoney = 0;
        IsInProgress = false;
        ResetGemCost = 0;
        DangerRoomNewPlantList.clear();
	}
	
	DangerRoomInfo(const DangerRoomInfo& i_info)
	{
		WorldName = i_info.WorldName;
		CurrentLevel = i_info.CurrentLevel;
		HighestLevel = i_info.HighestLevel;
		PlantfoodCarryOver = i_info.PlantfoodCarryOver;
		Lives = i_info.Lives;
		SeedBank = i_info.SeedBank;
		TimeStamp = i_info.TimeStamp;
		PrevLevel = i_info.PrevLevel;
		HasReward = i_info.HasReward;
		HasMilestone = i_info.HasMilestone;
		DangerRoomPlantList = i_info.DangerRoomPlantList;
        HasCompleted = i_info.HasCompleted;
        CurrentScore = i_info.CurrentScore;
        TotalScore = i_info.TotalScore;
        HistoryScore = i_info.HistoryScore;

        HistoryHighestScore = i_info.HistoryHighestScore;
        CurrentSunMoney = i_info.CurrentSunMoney;
        IsInProgress = i_info.IsInProgress;
        ResetGemCost = i_info.ResetGemCost;

        DangerRoomNewPlantList = i_info.DangerRoomNewPlantList;
	}
    
    std::string ToString() const
    {
        return StrFormat("%s (cur %d/max %d) (Lives:%d) %s", WorldName.c_str(), CurrentLevel, HighestLevel, Lives, HasReward ? "Reward" : "NoReward");
    }

	bool operator==(const DangerRoomInfo& i_compareTo) const
	{
		bool preSeedBankCompare =
			(WorldName.compare(i_compareTo.WorldName) == 0) &&
			(i_compareTo.CurrentLevel == CurrentLevel) &&
			(i_compareTo.HighestLevel == HighestLevel) &&
			(i_compareTo.PlantfoodCarryOver == PlantfoodCarryOver) &&
			(i_compareTo.Lives == Lives) &&
			(i_compareTo.SeedBank.size() == SeedBank.size()) &&
			(i_compareTo.TimeStamp == TimeStamp) &&
			(i_compareTo.PrevLevel == PrevLevel) &&
			(i_compareTo.HasReward == HasReward) &&
			(i_compareTo.HasMilestone == HasMilestone) &&
			//(i_compareTo.DangerRoomPlantList.size() == DangerRoomPlantList.size()) &&
            (i_compareTo.HasCompleted == HasCompleted) &&
            (i_compareTo.CurrentScore == CurrentScore) &&
            (i_compareTo.TotalScore == TotalScore) &&
            (i_compareTo.HistoryScore == HistoryScore) &&

            (i_compareTo.HistoryHighestScore == HistoryHighestScore) &&
            (i_compareTo.CurrentSunMoney == CurrentSunMoney) &&
            (i_compareTo.DangerRoomNewPlantList.size() == DangerRoomNewPlantList.size()) &&
            (i_compareTo.IsInProgress == IsInProgress);

		if (!preSeedBankCompare)
		{
			return false;
		}
		
		// Now, do the longer compare on the seed bank
		for (size_t i = 0; i < SeedBank.size(); i++)
		{
			bool compareFound = false;
			for (size_t j = 0; j < i_compareTo.SeedBank.size(); j++)
			{
				if (i_compareTo.SeedBank[j] == SeedBank[i])
				{
					compareFound = true;
					break;
				}
			}
			if (!compareFound)
			{
				return false;
			}
		}

//		for (size_t i = 0; i < DangerRoomPlantList.size(); i++)
//		{
//			bool compareFound = false;
//			for (size_t j = 0; j < i_compareTo.DangerRoomPlantList.size(); j++)
//			{
//				if (i_compareTo.DangerRoomPlantList[j] == DangerRoomPlantList[i])
//				{
//					compareFound = true;
//					break;
//				}
//			}
//			if (!compareFound)
//			{
//				return false;
//			}
//		}

		for (size_t i = 0; i < DangerRoomNewPlantList.size(); i++)
		{
			bool compareFound = false;
			for (size_t j = 0; j < i_compareTo.DangerRoomNewPlantList.size(); j++)
			{
				if (i_compareTo.DangerRoomNewPlantList[j] == DangerRoomNewPlantList[i])
				{
					compareFound = true;
					break;
				}
			}
			if (!compareFound)
			{
				return false;
			}
		}

		// Made it this far, thus, we are the same
		return true;
	}
	
	inline void ApplyTimeStamp()
	{
		TimeStamp = gTimeMgr->GetDate();
	}
	
	void AddImmediateReward(class DangerRoomRewardInfo i_dangerRoomReward);
	void ClearImmediateRewards();
	void ApplyImmediateRewards();
	
	const bool	HasLawnMowerInRow(const int i_row) const;
	void		SetLawnMowerStatusInRows(const std::vector<uint8>& i_mowerStatusInRows);
	const bool	HasLostDangerRoom() const;
	void		SetHasLostDangerRoom(const bool i_status);
	int			GetLawnMowerCount() const;
	void		RestartRoom();
    void        EventRestartRoom();
	
	std::string					WorldName;
	int32						CurrentLevel;
	int32						HighestLevel;
	uint8						PlantfoodCarryOver;
	uint16						Lives;
	std::vector<int>			SeedBank;
	time_t						TimeStamp;
	int32						PrevLevel;
	bool						HasReward;
	bool						HasMilestone;
	
	// Immediate Rewards are saved
	std::vector<class DangerRoomRewardInfo>		ImmediateRewardList;
	DangerRoomPlantInfos		DangerRoomPlantList;
    bool                        HasCompleted;
    int                         CurrentScore;
    int                         TotalScore;
    int							HistoryScore;
    int                         ResetGemCost = 0;

    int                         HistoryHighestScore;
    int                         CurrentSunMoney;
    bool                        IsInProgress;
    DangerRoomNewPlantInfos		DangerRoomNewPlantList;
	
};

#endif /* defined(__PlantsVersusZombies2__DangerRoomInfo__) */
