//
//  PlantFamilyMgr.h
//  PlantsVersusZombies2
//
//  Created by shizf on 2016/11/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantFamilyMgr_h
#define PlantFamilyMgr_h

#include "PVZTypes.h"
#include "Singleton.h"
#include "PlantFamilyPropertySheet.h"

struct PlantFamilyBoostValue
{
    std::string Type;
    float Value = 0;
    std::string ReplaceType;
    float ReplaceValue = 0;
    std::string MD5;
    bool Lock = false;
};

struct PlantFamilyDisplayValue
{
    std::string curProperty;
    std::string replaceProperty;
    int curPropertyRare = 0;
    int replacePropertyRare = 0;
    PlantFamilyBoostValue boostValue;
};

struct PlantFamilyOptionalDisplayValue
{
    std::string name;
    std::string property;
};

struct PlantFamilyInfo
{
    int FamilyID = -1;
    std::vector<PlantFamilyBoostValue> BoostsValue;
    std::vector<PlantBoost> Boosts;
};

class PlantFamilyMgr : public LazySingleton<PlantFamilyMgr>
{
public:
    PlantFamilyMgr();
    ~PlantFamilyMgr();
    
    static PlantFamilyPropertySheetPtr GetFamilyByID(int i_id);
    
    std::vector<PlantFamilyInfo*> GetPlantFamily(int i_plantID);
    std::vector<PlantFamilyInfo*> GetPlantFamily(const PlantTypePtr i_plantType);
    
    void GetFamilyBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    
    void PlantFamilyReset();
    bool PlantFamilyIsEnable();
    void EnableFamily();
    
    static bool SortFamilyList(const PlantFamilyInfo& lhs, const PlantFamilyInfo& rhs);
    static std::vector<PlantFamilyInfo> GetPlantFamilyListWithSort();
    
    static bool IsPlantFamilyActivated(int familyID);
    static int GetActivatedPlantFamilyCount();
    
    static int GetPlantFamilyLevel(int familyID);
    static int GetFamilyQuality(int familyID);
    static int PlantRareProvideLevel(const std::string& plantName);
    static int PlantLevelProvideLevel(const std::string& plantName);
    static int PlantAvatarProvideLevel(const std::string& plantName);
    
    static const std::vector<PlantFamilyDisplayValue> GetPlantFamilyProperty(int familyID);
    static const std::vector<PlantFamilyDisplayValue> ClearReplacePropertyByIndex(int familyID);
    static const std::vector<PlantFamilyOptionalDisplayValue> GetPlantFamilyOptionalProperty(int familyID);
    
    // for rift validation
    static std::vector<std::string> GetPlantBoostInFamilyRaw(PlantTypePtr plantTypePtr);
    static std::vector<SexyString> GetPlantBoostInFamily(PlantTypePtr plantTypePtr);
    static std::string GetPropertyDisplay(const std::string& typeName, float value, int displayType);
    static std::string GetOptionalPropertyDisplay(float min, float max, float next, int displayType);
    
    static bool IsPlantFamilyTutorialActivated();
    static void FinishPlantFamilyTutorial();
    
    void ShowAD();
	int GetLeftADWatchCount();
	bool CanWatchAD();
	void SetADWatchCount(int i_count);
	void onADFinished(int i_type);

private:
    void CheckAndBuildFamily(PlantTypePtr i_plantType);
    void CheckAndBuildFamilyBoosts(PlantFamilyInfo* i_info);
    
    static PlantFamilyBoostPropertySheetPtr GetPlantFamilyBoostPropertySheet(const std::string& type);
    static float GetPlantFamilyPropertyMinValue(PlantFamilyBoostPropertySheet* prop, PlantBoost& plantBoost);
    static const PlantFamilyInfo GetPlantFamilyInfo(int familyID);
    static int GetPlantFamilyPropertyRare(PlantFamilyBoostPropertySheet* prop, float value);
    
private:
    std::unordered_map<std::string,std::vector<PlantFamilyInfo*>> m_plantFamilyInfos;
};

#endif /* PlantFamilyMgr_h */
