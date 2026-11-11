//
//  FestivalManager.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__FestivalManager__
#define __PlantsVersusZombies2__FestivalManager__

#include "Singleton.h"
#include "LawnAppEnums.h"
#include "MagentoService.h"
#include "ActivityLevels.h"

struct ChristmasProtectInfo
{
    int wave;
    std::vector<std::string> plants;
    
    ChristmasProtectInfo()
    {
        wave = 0;
    }
};

typedef std::map<FestivalGameReward, int> FestivalRewardMap;

class FestivalManager : public LazySingleton<FestivalManager>
{
public:
    FestivalManager();
    virtual ~FestivalManager();
    
    bool IsFestivalLevel(const std::string& i_level,FestivalGameMode i_mode = FestivalGameMode_None);
    bool IsSummerVacationLevel(const std::string& i_level);
    void DisplaySaleAnnoucement(bool i_visible);
    void SetSpringFestivalButtonVisible(bool i_visible);
    
    void SetCurFestivalGameMode(FestivalGameMode i_mode)    { m_curFestivalGameMode = i_mode;   }
    FestivalGameMode GetCurFestivalGameMode() const         { return   m_curFestivalGameMode;   }
    
    void SetCurFestivalGameLevel(FestivalGameLevel i_level) { m_curFestivalGameLevel = i_level; }
    FestivalGameLevel GetCurFestivalGameLevel() const       { return m_curFestivalGameLevel;    }
    
    FestivalGameMode GetFestivalGameModeByCloud(ICloud_FestivalGameMode i_mode) { return FestivalGameMode(i_mode - ICloud_FestivalGameMode_None); }
    ICloud_FestivalGameMode GetCloudFestivalGameMode(FestivalGameMode i_mode) { return ICloud_FestivalGameMode(i_mode + ICloud_FestivalGameMode_None); }
    
    
    MagentoProductPropsPtr GetWishProps() const
	{
		return m_FestivalWishprops;
	}
    void SetWishProps(MagentoProductPropsPtr i_props)
    {
        m_FestivalWishprops = i_props;
    }
    void ResetWishProps()
    {
        m_FestivalWishprops = MagentoProductPropsPtr();
    }
    
    void GetFestivalRewardMap(FestivalRewardMap& i_map,FestivalGameLevel i_level);
    
    void ResetSpeaker();
    void ShowSpeaker(const std::string& string, const std::string& colorName, int i_displayCount, float i_scrollSpeed, float i_durationToDelay);
    void ShowSpeakerByID(const std::string& stringID, const std::string& colorName, int i_displayCount, float i_scrollSpeed, float i_durationToDelay);
    
    //For Christmas Protect
    void LoadChristmasProtectGroups();
    std::string GetChristmasProtectDropPlantName(int i_wave);
    
private:
    
    FestivalGameMode                    m_curFestivalGameMode;
    
    FestivalGameLevel                   m_curFestivalGameLevel;
    
    MagentoProductPropsPtr              m_FestivalWishprops;
    
    std::vector<ChristmasProtectInfo>   m_christmasProtectInfos;
    
//for online
public:
    void FestivalInit();
    
    bool IsFestivalOpen(FestivalGameMode i_mode = FestivalGameMode_None);
    bool IsFestivalActive(FestivalGameMode i_mode = FestivalGameMode_None);
    bool HasGameModeToday(FestivalGameMode i_mode);
    int GetCanBuyTimes(FestivalGameMode i_mode);
    int GetCurrentBuyPrice(FestivalGameMode i_mode);
    std::vector<int> GetOpenDays(FestivalGameMode i_mode);
    
    Activity_Level_Data* GetChooseByMode(FestivalGameMode i_mode);
    
private:
    void RefreshData(class ActiveItem* i_item);
    bool HasData();
    
private:
    ActivityLevelsData m_data;
};

#endif /* defined(__PlantsVersusZombies2__FestivalManager__) */
