//
//  PlantType.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTDESCRIPTOR_H__
#define __PLANTDESCRIPTOR_H__

#include "ObjectTypeDescriptor.h"
#include "Precompile.h"
#include "RtObject.h"
#include "BoardEnums.h"
#include "PlantEnums.h"
#include "SkillPropertySheet.h"
#include "PlantAccessoryPropertySheet.h"

class Board;
class Plant;

typedef RtWeakPtr<const class PlantPropertySheet> PlantPropsPtr;
typedef RtWeakPtr<const class HeroPlantPropertySheet> HeroPlantPropsPtr;

struct PlantAvatar
{
    PlantAvatar()
    {
        AvatarType = E_AVATAR_NONE;
        AvatarLayers.clear();
        CostNum = 0;
        PacketCooldownPercent = 1.0f;
    }
    
    PlantAvatarType AvatarType;
    std::vector<std::string> AvatarLayers;
    int CostNum;
    float PacketCooldownPercent;
};

enum PlantAttributeType
{
	AttributeType_HP,
	AttributeType_Attack,
	AttributeType_Range,
	AttributeType_Plant,
	AttributeType_Support,
	AttributeType_Control
};

enum PlantAttributeRank
{
	AttributeRank_None,
	AttributeRank_D,
	AttributeRank_C,
	AttributeRank_B,
	AttributeRank_A,
	AttributeRank_S,
};

struct PlantAttributeInfo
{
	PlantAttributeInfo()
	: Type(AttributeType_HP)
	, Rank(AttributeRank_None)
	{

	}

	PlantAttributeType Type;
	PlantAttributeRank Rank;
};

enum PlantTag
{
	Tag_Green,
	Tag_Heal,
	Tag_Support,
	Tag_Debuff,
	Tag_SunProduce,	
	Tag_Red,
	Tag_Pea,
	Tag_DPS,
	Tag_AOE,
	Tag_Burn,
	Tag_OneShot,
	Tag_Curve,
	Tag_Manual,
	Tag_Explode,
	Tag_Flame,
	Tag_Lightning,
	Tag_Cold,
	Tag_Magic,
	Tag_Poison,
	Tag_Shadow,
	Tag_Blue,
	Tag_Summon,
	Tag_Consume,
	Tag_Operate,
	Tag_Flying,
	Tag_Watering,
	Tag_Low,
	Tag_High,
	Tag_Armor,
	Tag_Yellow,
	Tag_Defence,
	Tag_Slow,
	Tag_Teleport,
	Tag_Control,	
};

struct PlantAttribute
{
	std::vector<PlantAttributeInfo> Attributes;
	std::vector<PlantTag> Tags;
};

class PlantType : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PlantType, ObjectTypeDescriptor, RtClass);

	// Default values
	PlantType();

	std::string 	PlantFramework;
	std::string		AnimRigClass;
	std::string 	PopAnim;
	PlantPropsPtr 	Properties;
	bool			Enabled;
    bool            PlantPieceEnabled;
    bool            AvatarEnabled;
	std::string		HomeWorld;
    std::string     PlantPieceImageName;
    std::string     AvatarPieceImageName;
    std::vector<PlantAvatar>    Avatars;
    
    std::vector<std::string> AdventureFlags;
	std::vector<std::string> PlantResourceGroups;
	mutable PlantAvatarType eCurAvatar;

    mutable std::vector<PlantBoost> CurBoosts;
    
	int				Rare;

    PlantProfessions Profession;
    PlantAttribute Attribute;

    int 			DisplayFamilyId;

	HeroPlantPropsPtr HeroProperties;

    virtual void AddResourceRequirements(std::set<std::string> &io_resGroupNames) const;
    
    virtual float GetMaxHitpoints() const;
    virtual void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const;
    
	PlantPropsPtr GetPropsPtr() const;
	const class PlantPropertySheet* GetProps() const;

	HeroPlantPropsPtr GetHeroPropsPtr() const;
	const class HeroPlantPropertySheet* GetHeroProps() const;
	bool IsHeroPlant() const;
    
    bool IsSunProducer() const;
    bool IsBlowProducer() const;
    
    virtual int GetCost(int level) const;
    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const;
    virtual int GetBeghouledCost() const;
    float GetPacketCoolDown(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const;
    void GetAvatarLayers(PlantAvatarType i_avatarType, std::vector<std::string>& i_avatarLayers) const;

    bool IsInsideRestrictedArea(const Sexy::Point &i_gridPosition) const;
    
    void UpdateAvatar() const;
    
    SkillPropertySheetPtr GetCurrentLevelSkillType(int i_level, bool bIsProperty = true) const;
    bool HasPlantAdventureFlag(std::string i_flag) const;
    
    virtual bool GetCanBeUsedOnStage(const std::string& i_stagePrefix) const;
    virtual bool CanPlantOnConvertedPlant(PlantPtr i_targetPlant) const { return false; }
    virtual bool CanPlantOnPlant(Plant* i_plant) const;
    
    Color GetRareColor() const;
    bool IsInHomeWorld() const;
    int GetSaveCostInHomeWorld() const;

    static std::string GetPlantProfessionName(PlantProfessions i_profession);
    static std::string GetPlantProfessionDescription(PlantProfessions i_profession);

    virtual int GetRefundSunCount() const { return 0; }
	virtual bool IsVine() const {return false;}
private:
    
    int GetCostOffset() const;
    
    bool canGiveFirstAidToPlant(Plant* i_plant) const;
};

#endif // __PLANTDESCRIPTOR_H__
