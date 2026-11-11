/*
 * ArtifactMgr.h
 *
 *  Created on: 2021-5-31
 *      Author: admin
 */

#ifndef ARTIFACTMGR_H_
#define ARTIFACTMGR_H_

#include "Artifact.h"
#include "Singleton.h"
#include "PlantBoostPropertySheet.h"
#include "NetworkData.h"
#include "ArtifactBoost.h"

typedef RtWeakPtr<class Artifact> ArtifactPtr;

struct ArtifactData
{
	ArtifactData()
	{
		//PropsPtr = ArtifactPropertiesPtr();
		CurrentLevel = 1;
		CurrentStage = 0;
	}
	ArtifactPropertiesPtr PropsPtr;
	int CurrentLevel;
	int CurrentStage;
};

namespace ArtifactUtils
{
	template<typename T>
	inline T cal(T n1,T n2,char op)
	{
		T res;
		switch(op) {
			case '+':res=n1+n2;break;
			case '-':res=n1-n2;break;
			case '*':res=n1*n2;break;
			case '/':res=n1/n2;break;
			default:break;
		}
		return res;
	}

	struct node
	{
		node()
		{
			num = "";
			flag = false;
			op = 0;
		}

		std::string num;
		bool flag;
		char op;
	};

	std::string TransferMidExToPreEx(std::string& i_expression);
	float GetExpressionResult(std::string& i_expression);
	std::string ReplaceParameterEx(const std::string& i_expression, const std::string& i_replaceParameter, int i_replaceValue);
	void GetArtifactList(std::vector<ArtifactPropertiesPtr>& i_propertyList);
	ArtifactPropertiesPtr GetArtifactPropertyPtr(int i_artifactId);
	ArtifactDisplayActionsPropertyPtr GetArtifactDisplayActionsPropertyPtr(int i_artifactId);
	ArtifactCultivationPropertyPtr GetArtifactCultivationPropertyPtr(int i_artifactId);
	bool CanLevelUp(int i_artifactId);
	bool CanLevelUp(int i_artifactId, int i_rank, int i_level);
	bool CanRankUp(int i_artifactId);
	bool CanRankUp(int i_artifactId, int i_rank, int i_level);
	bool IsMaxLevel(int i_artifactId);
	bool IsMaxLevel(int i_artifactId, int i_rank, int i_level);
	float GetArtifactSkillValue(int i_artifactId, int i_rank, int i_level, FieldType i_type, int i_fieldIndex);
	std::vector<float> GetArtifactSkillValues(int i_artifactId, int i_rank, int i_level, FieldType i_type);
	SexyString GetArtifactSkillDescription(int i_artifactId, int i_rank, int i_level, FieldType i_type);
	SexyString GetArtifactSkillDescriptionForLevelUp(int i_artifactId, int i_rank, int i_level, FieldType i_type);
}

class NetworkTriggerArtifactInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkTriggerArtifactInfo, INetworkData, RtClass);

public:
	int m_usedTimes;
};

enum ArtifactBoostRarity
{
	BoostRarity_Normal,
	BoostRarity_Magic,
	BoostRarity_Epic,
	BoostRarity_Legend
};

struct CurrentArtifactBoostInfo
{
	CurrentArtifactBoostInfo()
	: Name("")
	, Description("")
	, Type(Boost_None)
	, Rare(0)
	, Id(-1)
	, Value(0.0f)
	{

	}

	CurrentArtifactBoostInfo(const std::string& i_name, const std::string& i_des, ArtifactBoostType i_type, int i_rare, int i_id, float i_value)
	: Name(i_name)
	, Description(i_des)
	, Type(i_type)
	, Rare(i_rare)
	, Id(i_id)
	, Value(i_value)
	{

	}

	std::string Name;
	std::string Description;

	ArtifactBoostType Type;
	int Rare;
	int Id;
	float Value;
};

class ArtifactMgr : public LazySingleton<ArtifactMgr>
{
public:
	ArtifactMgr();
	virtual ~ArtifactMgr();

	void InitDefaultImprovedProps();

	void SetArtifact(ArtifactData i_data) { m_currentArtifact = i_data; }
	ArtifactData GetArtifact();

	ArtifactData CreateArtifactData(std::string i_artifactName, int i_level, int i_stage);

	void TrySyncArtifact();
	void SyncArtifact(int i_id, int i_level = 1, int i_stage = 1);
	bool IsArtifactDisabled();
	void AddArtifactModuleIfNeeded();
	void RecomputeEntityValues();

	ArtifactPropertiesPtr GetArtifactByTypeId(int i_id);

	std::string GetArtifactName(int i_id);
	std::string GetArtifactDescription(int i_id);

	void CheatTestField(int i_id);
	void TriggerArtifact(int i_usedTimes);

	float CalculateFieldValue(FieldType i_type, int i_index);
	float CalculateFieldValue(ArtifactPropertiesPtr i_propsPtr, FieldType i_type, int i_index);
	void FillCommonData(CommonData& i_data);

	void GetArtifactBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
	void SetTempBoostValue(float i_value) { m_tempBoostValue = i_value; }

	void SetGlobalArtifactId(int i_id) { m_globalArtifactId = i_id; }

	void SetActivatedArtifact(ArtifactPtr i_artifact) { m_activatedArtifact = i_artifact; }
	ArtifactPtr GetActivatedArtifact();
	void RemoveActivatedArtifact();

	// for public
	float GetActivatedArtifactCooldown();
	float GetActivatedArtifactLeftTime();
	bool CanTriggerActivatedArtifact();
	int GetActivatedArtifactMaxUsedTime();
	int GetActivatedArtifactUsedTime();
	bool needRequestTriggerArtifact();
	bool IsDangerRoom();

	void SetBlessLegendLeftCount(int i_count) { m_blessLegendLeftCount = i_count; }
	int GetBlessLegendLeftCount() { return m_blessLegendLeftCount; }

	void SetFreePlantingLeftCount(int i_count) { m_freePlantingLeftCount = i_count; }
	int GetFreePlantingLeftCount() { return m_freePlantingLeftCount; }
	bool CanFreePlanting();

	void SetFreeNoCDLeftCount(int i_count) { m_freeNoCDLeftCount = i_count; }
	int GetFreeNoCDLeftCount() { return m_freeNoCDLeftCount; }
	bool CanFreeNoCD();

	// for network
	void RequestTriggerArtifact();
	void SetOrderId(const std::string& i_id) { m_orderId = i_id; }
	const std::string& GetOrderId() { return m_orderId; }
	ArtifactData m_currentArtifact;
	int m_gridX;
	int m_gridY;

	// Improved system
	const std::vector<class ArtifactImprovedPropertySheet*> GetProps();
	void InitProps(const class Network_ArtifactImprovedPropertySheet* props, int i_networkVersion);
	bool SyncLocalProps(const class Network_ArtifactImprovedPropertySheet* props, int i_artifactId, const std::vector<int>& i_infos);
	const NetworkArtifactBoostData& GetNetworkBoostById(const class Network_ArtifactImprovedPropertySheet* props, int i_id);
	void ConstructBoostInfos(const class Network_ArtifactImprovedPropertySheet* props, std::vector<NetworkArtifactBoostData>& i_outs, const std::vector<int>& i_ins);

	SexyString GetImprovedDescription(int i_artifactId);
	SexyString GetImprovedName(int i_artifactId);
	const std::vector<ArtifactBoostPropertySheetPtr>& GetEnabledBoostProps(int i_artifactId);
	const ArtifactBoostValueInfo& GetBoostValueRangeByBoostId(int i_artifactId, int i_boostId);
	int GetBoostRareByBoostId(int i_artifactId, int i_boostId);
	int GetBoostRareByBoostId(int i_boostId);
	ArtifactBoostType GetBoostTypeByBoostId(int i_artifactId, int i_boostId);

	float GetBoostValue(int i_artifactId, ArtifactBoostType i_type);
	float GetBoostValue(int i_artifactId, ArtifactBoostType i_type, int rare);
	bool IsGlobalBoost(const ArtifactBoostInfo& i_boost);
	std::vector<CurrentArtifactBoostInfo> GetCurrentBoostInfo(int i_artifactId, bool i_saved = true);
	std::vector<CurrentArtifactBoostInfo> GetCurrentGlobalBoostInfo(int i_artifactId);
	int GetGlobalExtraValue(float& i_outValue, int i_plantId, int i_type, int i_currentArtifactId);
	bool IsUnsharedBoost(ArtifactBoostType i_type);

private:
	class ArtifactImprovedPropertySheet* getArtifactImprovedPropsById(int i_artifactId);
	const ArtifactBoostPropertySheetPtr& getBoostById(const std::vector<ArtifactBoostPropertySheetPtr>& i_boosts, int i_id);
	const ArtifactBoostPropertySheetPtr& getBoostSheet(int i_artifactId, int i_boostId);
	std::vector<CurrentArtifactBoostInfo> getCurrentBoostInfo(int i_artifactId, const std::vector<ArtifactBoostInfo>& i_boostInfos, int i_rare);
	float getExtraValue(const std::string& i_plantName, int i_currentArtifactId, int i_boostType);
	bool hasPlantBoost(const std::vector<PlantBoost>& i_boosts, int i_boostType);

	bool artifactDisabled();
	void addArtifact(std::string i_artifactName, int i_level, int i_stage);

	float CalculateExpValue(std::string& i_srcField, int i_id = -1);
	void GetRealExpression(std::string& i_field, int i_id);

	std::string GetTargetFieldByFieldType(ArtifactPropertiesPtr i_propsPtr, FieldType i_type, int i_index);
	std::string GetBoostAliases(PlantBoostType i_boostType);

	void OnGetArtifactBoosts(int i_id, int i_type);


	float m_tempBoostValue;
	ArtifactPtr m_activatedArtifact;
	int m_globalArtifactId;

	std::string m_orderId;

	// Improved system
	std::vector<class ArtifactImprovedPropertySheet*> m_improvedProps;
	int m_currentPropVer;

	int m_blessLegendLeftCount;
	int m_freePlantingLeftCount;
	int m_freeNoCDLeftCount;
};


#endif /* ARTIFACTMGR_H_ */
