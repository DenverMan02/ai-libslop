#ifndef HeroPlantMgr_H_
#define HeroPlantMgr_H_

#include "Singleton.h"

class HeroPlantMgr : public LazySingleton<HeroPlantMgr>
{
public:
	HeroPlantMgr();
	virtual ~HeroPlantMgr();

    bool IsHeroPlantActivated();

    bool CheckEnableHeroPlantModule();
    void AddHeroPlantModuleIfNeeded();


    //TGA HeroPlant Log START
    void ResetLog();
    void LogCommon(const std::string& i_step, const std::string& i_plantName, const std::string& i_time = "");
    void LogAddHeroPlant(const std::string& i_plantName);
    void LogUnlockHeroPlantCard(const std::string& i_plantName);
    void LogHeroPlantCompletedConditions(const std::string& i_plantName);
    void LogHeroPlantTalentUP(const std::string& i_plantName, int i_talentIndex);
    void LogHeroPlantGradeUP(const std::string& i_plantName, int i_gradeLevel);
    void LogHeroPlantPlantfoodFinish(const std::string& i_plantName);
    void LogUnlockHeroPlantPlantfoodCard(const std::string& i_plantName);
    void LogUnchartedStart(const std::string& i_plantName);
    void LogHeroPlantDied(const std::string& i_plantName);
    void LogHeroPlantShoveled(const std::string& i_plantName);

    float m_timeLevelStart;
    bool m_firstAddHeroPlant;
    bool m_firstPlantfood;
    //TGA HeroPlant Log END
};


#endif