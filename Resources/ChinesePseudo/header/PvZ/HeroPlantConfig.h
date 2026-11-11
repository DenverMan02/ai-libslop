#ifndef HeroPlantConfig_H_
#define HeroPlantConfig_H_

#include "Precompile.h"
#include "PVZDB.h"
#include "PropertySheetBase.h"

#include<string>

struct HeroPlantGradeUp
{
    float AttackUP = 0;//升级获得的加成
    float HealthUP = 0;//升级获得的加成
    int TalentPoints = 0;//升级获取的天赋点
    int ExpRequired = 9999;//升级需要的经验
};

struct HeroPlantGradeRange
{
    int MinGrade = 1;//初始等级
    int MaxGrade = 1;//最大等级
};

struct HeroPlantTalent
{
    std::string TalentName;
    std::string TalentIcon;
    std::string TalentDescription;

    int MaxLevel = 0;
    std::vector<int> LevelUpCost;
};


class HeroPlantPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(HeroPlantPropertySheet, PropertySheetBase, RtClass);


    HeroPlantPropertySheet()
    :SunRequired(9999),
    TimeRequired(999),
    RechargeTime(999),
    RespawnTime(999)
    {

    }

	std::string                             PlantName;
    int                                     SunRequired;
    float                                   TimeRequired;
    float                                   RechargeTime; //大招CD
    float                                   RespawnTime; //复活CD

    std::vector<HeroPlantGradeUp>           GradeUP;//升级获得相应的属性
    std::vector<HeroPlantGradeRange>        GradeRange;//初始等级和等级上限
    std::vector<HeroPlantTalent>            Talent;//天赋
};


#endif
