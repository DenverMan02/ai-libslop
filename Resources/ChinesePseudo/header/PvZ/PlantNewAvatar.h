#ifndef __PlantsVersusZombies2__PlantNewAvatar__
#define __PlantsVersusZombies2__PlantNewAvatar__

#include "PropertySheetBase.h"
#include "PlantBoostPropertySheet.h"
#include "Image.h"

typedef RtWeakPtr<class PlantNewAvatar> PlantNewAvatarPtr;
typedef RtWeakPtr<class PrimitiveAvatar> PrimitiveAvatarPtr;

class PlantNewAvatar : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantNewAvatar, PropertySheetBase, RtClass);

    int                         AvatarType;
    std::string                 PlantName;
    std::string                 NewAvatarName;
    int                         ExchangeNum;
    std::vector<PlantBoost>     Boosts;
    std::string                 ShortDescription;
    std::string                 Description;
    std::string                 SourceGet;

    PlantNewAvatar():
    AvatarType(-1),
    ExchangeNum(0)
    {
    }

    int GetNewAvatarID();
    int GetNewAvatarPieceID();
};

class PrimitiveAvatar : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(PrimitiveAvatar, PropertySheetBase, RtClass);

    std::string                 PlantName;
    std::vector<PlantBoost>     Boosts;

};

namespace NewAvatar
{
    int GetPlantIDByAvatarID(int i_newAvatarId);
    int GetPlantIDByAvatarPieceID(int i_newAvatarPieceId);
    std::string GetPlantNameByAvatarID(int i_newAvatarId);
    std::string GetPlantNameByAvatarPieceID(int i_newAvatarPieceId);
    PlantNewAvatarPtr GetAvatarInfoByAvatarId(int i_newAvatarID);
    PlantNewAvatarPtr GetAvatarInfoByAvatarPieceId(int i_newAvatarPieceID);
    void GetListByPlantName(const std::string& i_plantName, std::vector<PlantNewAvatarPtr>& resultVec);
    void GetNewAvatarBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    void GetPrimitiveAvatarBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    int GetAvatarIndexForPlant(const std::string& i_plantName);
    int GetAvatarIndexForAvatarID(int i_avatarId);
    bool HasAnyUnlockedAvatar(const std::string& i_plantName);

    bool IsAvatarUnlocked(int i_AvatarId);
    SexyString GetAvatarName(int i_AvatarId);
    SexyString GetAvatarDescription(int i_AvatarId);
    SexyString GetAvatarGetWay(int i_AvatarId);
    int GetAvatarPieceNum(int i_AvatarId);
    int GetAvatarPieceMaxNum(int i_AvatarId);

    Sexy::Image* GetAvatarImage(int i_AvatarId);
    Sexy::Image* GetAvatarTinyImage(int i_AvatarId);
    Sexy::Image* GetNewAvatarPieceImage(int i_newAvatarPieceId);
    bool NeedShowTips();
    bool IsAnyNewAvatarPieceFull(const std::string& i_plantName);
    int Common_GetAvatarPieceNum(int i_avatarPieceId);
    std::vector<int> Common_GetPlantAvatarPiecesIdList(const std::string& i_plantName);
    Sexy::Image* Common_GetAvatarPieceImage(int i_avatarPieceId);
    int Common_GetAvatarPieceFullNumber(int i_avatarPieceId);
    bool Common_GetAvatarUnlocked(int i_avatarPieceId);
    std::string Common_GetPlantNameByAvatarPieceID(int i_avatarPieceId);
    int Common_GetAvatarIDbyAvatarPieceID(int i_avatarPieceId);
    bool IsPlantAvatarExistence(const std::string& i_plantName);
    float GetGeneralBoostValueByNewAvatarName(const std::string& i_newAvatarName);

    PlantNewAvatarPtr GetFirstAvatarInfoByClass(const RtClass* inClass);
}

#endif