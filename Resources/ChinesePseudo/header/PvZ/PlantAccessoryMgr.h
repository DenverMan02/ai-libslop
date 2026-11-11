//
//  PlantAccessoryMgr.h
//  PlantsVersusZombies2
//
//  Created by shizf on 2016/11/10.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantAccessoryMgr_h
#define PlantAccessoryMgr_h

#include "PVZTypes.h"
#include "Singleton.h"
#include "PlantAccessoryPropertySheet.h"

namespace Message
{
    void AccessorySaleComplete();
    void ExchangeComplete(bool i_success);
    void ActionComplete();
    void OnSoldTargetAccessory(int32 id);
    void OnSteadySuccess(int32 id);
    void OnResetSuccess(int32 id);
}


struct PlantAccessoryInfo
{
    PlantAccessoryInfo()
    {
        PlantID = -1;
        Type = "";
        AccessoryId = 0;
        Level = 0;
    }
    
    inline bool operator == (const PlantAccessoryInfo &rhs) const
    {
        return (rhs.PlantID == PlantID)
        && (rhs.Type == Type);
    }
    
    inline bool operator == (const std::string& i_type) const
	{
		return (i_type == Type);
	}

    int32	PlantID;
    // Aliases in property sheet
    std::string Type;
    int64 AccessoryId;
    int32 Level;
};

enum BindAccessoryReason
{
    Reason_OK,
    Reason_Failed,
    Reason_Occupied,
    Reason_Not_Enough_Level,
    Reason_Binded,
    Reason_Unuseble
};

enum AccessoryUsedResult
{
    Result_Error,
    Result_Used_By_Others,
    Result_Used_By_Self,
    Result_Not_Used
};

struct AccessoryUIInfo
{
    AccessoryUIInfo()
    {
        Name = "";
        Description = "";
        BoostDescription = "";
        DisplayImageName = "";
        Quality = QUALITY_NORMAL;
        RequiredLevel = 0;
        RequiredPieces = 0;
        PurchasePrice = 0;
        SalePrice = 0;
    }
    
    std::string Name;
    std::string Description;
    std::string BoostDescription;
    std::string DisplayImageName;
    AccessoryQuality Quality;
    int RequiredLevel;
    int RequiredPieces;
    int PurchasePrice;
    int SalePrice;
};

// Accessory general properties
class AccessoryGeneralPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(AccessoryGeneralPropertySheet, PropertySheetBase, RtClass);
    
    AccessoryGeneralPropertySheet()
    {
        MaxOwnedAccessory = 0;
    }
    
    int MaxOwnedAccessory;
};

class PlantAccessoryMgr : public LazySingleton<PlantAccessoryMgr>
{
public:
    // Accessory Management
    const PlantAccessoryInfo* GetAccessoryForPlant(int i_plantID);
    const PlantAccessoryInfo* GetAccessoryForPlant(PlantTypePtr i_plantType);
    AccessoryUsedResult IsTargetAccessoryUsed(int i_accessoryId, PlantTypePtr i_plantType);
    void BindTargetAccessory(int i_accessoryId, PlantTypePtr i_plantType);
    void UnbindTargetAccessory(int i_accessoryId);
    BindAccessoryReason CanAccessoryBindTargetPlants(int i_accessoryId, PlantTypePtr i_plantType);
    bool IsTargetPlantDisabled(PlantTypePtr i_plantType, const std::string& i_type);
    const SexyString GetTargetAccessoryPlantName(int i_accessoryId);
    const std::string GetTargetAccessoryTypeById(int i_accessoryId);
    // Check current binded accessory for target plant
    AccessoryUIInfo GetAccessoryInfoForPlantType(PlantTypePtr i_plantType);
    
    PlantTypePtr GetBindedPlantTypeForTargetAccessory(int i_accessoryId);
    
    static RtWeakPtr<class AccessoryGeneralPropertySheet> GetAccessoryGeneralPropertySheet();
    
    const int GetNumOwnedAccessories();
    bool CanExchangeAccessory();
    const int GetMaxOwnedAccessories();
    
    bool IsAccessoryPiecesFull(const std::string& i_type);
    const int GetAccessoryPurchasePrice(const std::string& i_type);
    void ExchangeTargetAccessory(const std::string& i_type);
    const int GetOwnedPieces(const std::string& i_type);
    void SoldTargetAccessory(const std::string& i_type, int i_accessoryId);
    void SortOwnedAccessories();
    const std::string GetAccessoryPieceDisplayImage(const std::string& i_typeName);
    
    // Accesory UI
    const SexyString GetAccessoryDisplayName(const std::string& i_type);
    const SexyString GetAccessoryDescription(const std::string& i_type);
    const SexyString GetAccessoryBoostDescription(const std::string& i_type);
    Image* GetAccessoryDisplayImage(const std::string& i_type);
    
    AccessoryUIInfo GetAccessoryUIInfo(const std::string& i_type);
    
    // Accessory extras
    AccessoryAvatarInfo GetAccessoryAvatarInfo(const std::string& i_type);
    const std::vector<std::string> GetAccessoryDisabledPlants(const std::string& i_type);
    const int GetAccessoryRequiredLevel(const std::string& i_type);
    void OnSoldTargetAccessory(const std::string& i_type, int i_accessoryId);
    
    PlantTypePtr GetCurrentPlantType() { return m_plantType; }
    void SetCurrentPlantType(PlantTypePtr i_type) { m_plantType = i_type; }
    PlantAccessoryPropertySheetPtr GetAccessoryByType(const std::string& i_type);
    
    void GetAccessoryBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    const std::vector<PlantBoost>& FindBoostsForAccessoryType(const std::string& i_accessoryType, int i_plantID);
    const SexyString GetPlantDisplayName(int i_plantID);
    
    bool IsTargetASuperAccessory(int i_accessoryId);
    bool IsTargetASuperAccessory(const std::string& i_type);

    std::vector<SteadyMaterial> GetSuperAccessoryResetReturn(int i_accessoryId);

    void ResetTargetAccessory(const std::string& i_type, int i_accessoryId);
    void OnResetTargetAccessory(const std::string& i_type, int i_accessoryId);
    void SteadyTargetAccessory(const std::string& i_type, int i_accessoryId);
    void OnSteadyTargetAccessory(const std::string& i_type, int i_accessoryId);

private:
    // Current plant type, for sort uses
    PlantTypePtr m_plantType;
};

#endif /* PlantAccessoryMgr_h */
