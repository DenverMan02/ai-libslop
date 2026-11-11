
#ifndef PlantGeneEnhancement_H_
#define PlantGeneEnhancement_H_

#include "PropertySheetBase.h"
#include "PlantBoostPropertySheet.h"
#include "AdaptorHowToPlayScreen.h"

class PlantType;
typedef RtWeakPtr<class PlantGene> PlantGenePtr;
typedef RtWeakPtr<class PlantGeneConfig> PlantGeneConfigPtr;


enum PlantSkillBoost : int
{
    PlantSkillBoost_Invaild = 0,
    //白色植物
    PlantSkillBoost_White,
    Kernelpult_ButterRate,
    Puffshroom_SurviveTime,
    Magnetshroom_Recover,
    Peach_InvisibleTime,
    Stallia_ExtraDamage,
    Springbean_SkillBoost,
    Icelotus_TimeExtension,
    //绿色植物
    PlantSkillBoost_Green,
    Lightningreed_ExtraDamage,
    Melonpult_ExtraDamage,
    Magnifyinggrass_AttackCost,
    Empea_PalsyTime,
    Sapfling_ExtraSlow,
    Torchwood_FlameSplash,
    Peapod_OverlapAttck,
    Anthurium_AdvancedBulletDamage,
    //蓝色植物
    PlantSkillBoost_Blue,
    Laserbean_PlantfoodDamage,
    Holonut_RecoverTime,
    Chomper_RecoverTime,
    Pumpkinwitch_ReloadTime,
    Bonkchoy_PlantfoodDamage,
    Phatbeet_PlantfoodDamage,
    Chestnut_Respwan,
    Toadstool_ExtraSunmoney,
    Pumpkin_ExtraArmor,
    Heathseeker_Double,
    Squash_SkillRate,
    Homingthistle_SkillRate,
    Agave_SwordQi,
    //紫色植物
    PlantSkillBoost_Purple,
    Slingpea_ExtraDamage,
    Birthsunflower_BuffAttack,
    Chardguard_RecoverTime,
    Elaeocarpus_KillPercent,
    Aloes_ExtraBuff,
    Kiwifruit_ExtraTime,
    Shrinkingviolet_ExtraDamage,
    Draftodil_SkillRate,
    Shadowpeashooter_ExtraAttack,
    Boomflower_SkillRate,
    Imitater_ExtraAttributes,
    Byttneriameteorhammer_ChargeDamage,
    Hydrocotyledrummer_ExtraBandIncrease,
    //橙色植物
    PlantSkillBoost_Orange,
    Nekotail_PenetrateRate,
    Snapdragon_Area,
    Magicshroom_PFExtraSummon,
    Mulberry_GasRate,
    Olivepit_RecoverTime,
    Wintermelon_NewSkill,
    Bearberry_NewSkill,
    Lancerhoya_ReduceTime,
    Beanchemist_SnowRate,
    Powerplant_ReductCost,
    Cactus_PlantfoodSkill,
    Gatlingpea_AuxiliaryGun,
    Mangosteen_PlantfoodDamage,
    Crownflower_PlantfoodDamage,
    Burdockbatter_RateKeePFire,
};

struct GeneBoost
{
    std::string Description;    //使用 {Param_1},{Param_2}...表示公式对应列表的值
    std::vector<std::string> FormulaList;
    std::vector<PlantBoost> PlantBoosts;
    std::vector<PlantSkillBoost> SkillBoosts;

    SexyString GetDescription(int i_level);
    float GetFormulaValue(int i_level, int i_index);
};

class PlantGene : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantGene, PropertySheetBase, RtClass);

    int                         GeneID;
    RtWeakPtr<const PlantType>  GenePlantType;
    GeneBoost                   GeneAction;
};


class PlantGeneConfig : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantGeneConfig, PropertySheetBase, RtClass);

    std::vector<PlantGenePtr> WhiteGeneList;
    std::vector<PlantGenePtr> GreenGeneList;
    std::vector<PlantGenePtr> BlueGeneList;
    std::vector<PlantGenePtr> PurpleGeneList;
    std::vector<PlantGenePtr> OrangeGeneList;

    int AdditionVersion;
    std::vector<int> NewAddition;
    HowToPlayScreenData	HowToPlayData;

    PlantGenePtr GetGeneByID(int i_geneId);

};


namespace GeneEnhancement
{
    int FastGeneToEssence(int i_geneId);
    int FastEssenceToGene(int i_essenceId);
    int GeneToEssence(int i_geneId);
    int EssenceToGene(int i_essenceId);
    int TransToGeneValue(int i_value);
    int TransToEssenceValue(int i_value);

    bool IsGeneLocked(int i_geneId);
    void SetGeneLockState(int i_geneId, bool i_flag);

    //playerinfo
    int GetGeneFactorNumber();
    int GetGeneLevel(int i_geneId);
    bool CanGeneUpgrade(int i_geneId);

    int GetUnlockedGeneValue(int i_rare);
    int GetMaxGeneValue(int i_rare);

    PlantGeneConfigPtr GetGeneConfig();
    PlantGenePtr GetGeneByID(int i_geneId);

    SexyString GetGeneBoostDescription(int i_geneId, int i_level);
    SexyString GetGeneBoostDescription(PlantGenePtr i_gene, int i_level);

    void GetGeneEnhancementBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    float GetGeneEnhancementSkillBoost(const std::string& i_plantName);
    float GetGeneEnhancementSkillBoost(PlantSkillBoost i_skillBoost, int i_index = 0);

}


#endif