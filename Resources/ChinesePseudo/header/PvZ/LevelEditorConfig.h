#ifndef LEVEL_EDITOR_CONFIG_H
#define LEVEL_EDITOR_CONFIG_H

#include "PropertySheetBase.h"
#include "LevelEditorDefine.h"

/*---------------------关卡编辑器 配置------------------------------*/

class LevelEditorStageInfo : public PropertySheetBase
{
    RT_CLASS_DEFINE(LevelEditorStageInfo, PropertySheetBase, RtClass);
public:

    std::string StageName;
    std::string BackgroundImagePrefix;
	std::string BackgroundImageLeft;
	std::string BackgroundImageMiddle;
	std::string BackgroundImageRight;
    std::vector<std::string> LoadGroups;
    std::vector<std::string> ZombieList;
};

struct LevelEditorCardInfo
{
    LevelEditorCardInfo()
    :CardType(InvalidCard),
    TypeName("")
    {
        
    }

    LevelEditorCardInfo(LevelEditorCardType i_cardType, const std::string& i_typename)
    :CardType(i_cardType),
    TypeName(i_typename)
    {

    }

    inline bool operator==(const LevelEditorCardInfo& i_cardInfo) const
    {
        return (CardType == i_cardInfo.CardType) && (TypeName == i_cardInfo.TypeName);
    }

    LevelEditorCardType CardType;
    std::string TypeName;
};


class LevelEditorConfig : public PropertySheetBase
{
    RT_CLASS_DEFINE(LevelEditorConfig, PropertySheetBase, RtClass);
public:

    std::vector<LevelEditorCardInfo> GroundCardList;
    std::vector<LevelEditorCardInfo> SurfaceCardList;
    std::vector<std::string> SunProductPlantBanList;
    std::vector<std::string> AshPlantBanList;
    std::vector<std::string> NormalGridPlantBlackList;
    std::vector<std::string> NormalSeedPlantBlackList;
    std::vector<std::string> SingleHandedPlantBlackList;

};

namespace LevelEditorUtil
{
    RtWeakPtr<LevelEditorStageInfo> GetStageInfoByName(const std::string& i_name);
}

#endif
