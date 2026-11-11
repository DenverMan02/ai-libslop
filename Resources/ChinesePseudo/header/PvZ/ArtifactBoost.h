/*
 * ArtifactBoost.h
 *
 *  Created on: 2023-9-6
 *      Author: admin
 */

#ifndef ARTIFACTBOOST_H_
#define ARTIFACTBOOST_H_

//
//  PlantBoostPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 1/7/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.

#include "PropertySheetBase.h"
#include "RtObject.h"

//Do not delete or reorder these.  You will break live saved player datas
enum ArtifactBoostType
{
	Boost_None,
	Improved_Damage,
	Improved_Duration,
	Improved_Control,
	Improved_TriggerCD,
	Improved_UseTimes,
	Improved_Passive2CD,
	Improved_Passive1,
	Global_Passive1,
	Bonus_Starting_Sun,
	Start_No_CD,
	Start_Free_Plant,
	ArtifactBoostType_Max
};

struct ArtifactBoostValueInfo
{
	ArtifactBoostValueInfo()
	: Min(0.0f)
	, Max(0.0f)
	{

	}

	float Min;
	float Max;
};

struct NetworkArtifactBoostData
{
	NetworkArtifactBoostData()
	: Type(Boost_None)
	, Id(-1)
	, Rare(0)
	{

	}

	int Id;
	int Rare;
	ArtifactBoostType Type;
	ArtifactBoostValueInfo Value;
};

struct NetworkArtifactBoostConfig
{
	NetworkArtifactBoostConfig()
	: ArtifactId(0)
	{

	}

	int ArtifactId;
	std::vector<int> EnabledBoostInfos;
};

typedef RtWeakPtr<class ArtifactBoostPropertySheet> ArtifactBoostPropertySheetPtr;

class ArtifactBoostPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(ArtifactBoostPropertySheet, PropertySheetBase, RtClass);

    ArtifactBoostPropertySheet()
    : Name("")
    , Description("")
    , Type(Boost_None)
    , Rare(0)
    , Id(0)
    {

    }

    void Sync(const NetworkArtifactBoostData& i_info);

    std::string Name;
    std::string Description;

    ArtifactBoostType Type;
    int Rare;
    int Id;
    ArtifactBoostValueInfo ValueRange;
};

typedef RtWeakPtr<class ArtifactImprovedPropertySheet> ArtifactImprovedPropertySheetPtr;

class ArtifactImprovedPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(ArtifactImprovedPropertySheet, PropertySheetBase, RtClass);
    void Copy(const ArtifactImprovedPropertySheet& src);
    void SyncNetwork(const std::vector<NetworkArtifactBoostData>& i_infos);

    ArtifactImprovedPropertySheet()
    : ArtifactId(-1)
    , Name("")
    , Description("")
    {

    }

    int ArtifactId;
    std::string Name;
    std::string Description;

    std::vector<ArtifactBoostPropertySheetPtr> EnabledBoost;

private:
    bool syncBoost(const NetworkArtifactBoostData& i_info);
};

#endif /* ARTIFACTBOOST_H_ */
