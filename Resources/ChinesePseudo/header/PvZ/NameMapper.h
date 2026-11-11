//
//  PlantNameMapper.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 5/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantNameMapper__
#define __PlantsVersusZombies2__PlantNameMapper__

#include <map>

#ifndef PLANTNAME2ID_PROJ
#include "PVZTypes.h"
#endif

class NameMapperBase
{
public:
	int GetIdForName(const std::string&);
	std::string GetNameForId(int);
    bool ContainsId(int);
    bool ContainsName(const std::string&);
	virtual ~NameMapperBase(){};
	int GetMapSize(){ return static_cast<int>(m_map.size()); }
    const std::map<std::string, int>& GetMap();

protected:
	void CreateMD5Check();
	bool IsMapValid();

protected:
	NameMapperBase(){};
	std::map<std::string, int> m_map;
	std::string md5Check;

public:
    static const int GemServerID;
    static const int CoinServerID;
    static const std::string GemServerName;
    static const std::string CoinServerName;
};

class NarrationEventNameMapper : public NameMapperBase {
public:
    NarrationEventNameMapper();
	static NarrationEventNameMapper& GetInstance()
    {
        static NarrationEventNameMapper instance;
        return instance;
    };
};

class PlantNameMapper :public NameMapperBase{
public:
    PlantNameMapper();
    static PlantNameMapper& GetInstance()
    {
        static PlantNameMapper instance;
        return instance;
    };
    int GetMapSize() { return static_cast<int>(m_map.size()); }

#ifndef PLANTNAME2ID_PROJ
    int GetIdForType(PlantTypePtr i_plantType);
    int GetIdForType(const PlantType* i_plantType);
    PlantTypePtr GetTypeForID(int i_plantID);
#endif
    
    static bool IsIDValid(int i_id);    // quick check the id, instead 'for'
};


class PlantNameMapperServerID :public NameMapperBase{
public:
    PlantNameMapperServerID();
    
    static PlantNameMapperServerID& GetInstance()
    {
        static PlantNameMapperServerID instance;
        return instance;
    };

    #ifndef PLANTNAME2ID_PROJ
    int GetIdForType(PlantTypePtr i_plantType);
    int GetIdForType(const PlantType* i_plantType);
    PlantTypePtr GetTypeForID(int i_plantID);
#endif
    
    static bool IsIDValid(int i_id); 
};

class PlantChipNameMapperServerID :public NameMapperBase{
public:
    PlantChipNameMapperServerID();
    
    static PlantChipNameMapperServerID& GetInstance()
    {
        static PlantChipNameMapperServerID instance;
        return instance;
    };
};


class AvatarNameMapperServerID :public NameMapperBase{
public:
    AvatarNameMapperServerID();
    
    static AvatarNameMapperServerID& GetInstance()
    {
        static AvatarNameMapperServerID instance;
        return instance;
    };
};

class AvatarChipNameMapperServerID :public NameMapperBase{
public:
    AvatarChipNameMapperServerID();
    
    static AvatarChipNameMapperServerID& GetInstance()
    {
        static AvatarChipNameMapperServerID instance;
        return instance;
    };
};

class OtherServerNameMapper: public NameMapperBase {
public:
    OtherServerNameMapper();
    static OtherServerNameMapper& GetInstance()
    {
        static OtherServerNameMapper instance;
        return instance;
    };
    bool IsServerCoin(int i_id) {return (i_id > 4000 && i_id < 4100); }
    bool IsServerGem(int i_id) {return (i_id > 3000 && i_id < 3100); }
    bool IsServerKey(int i_id) {return (i_id > 2400 && i_id < 2500); }
    bool IsServerCuke(int i_id) {return i_id == 2209; }
};

class ConstraintNameMapper :public NameMapperBase{
public:
	ConstraintNameMapper();
    static ConstraintNameMapper& GetInstance()
    {
        static ConstraintNameMapper instance;
        return instance;
    };
};

class PlantAccessoryPieceMapper : public NameMapperBase {
public:
    PlantAccessoryPieceMapper();
    static PlantAccessoryPieceMapper& GetInstance()
    {
        static PlantAccessoryPieceMapper instance;
        return instance;
    };
};

class PlantAccessoryInfoMapper : public NameMapperBase {
public:
    PlantAccessoryInfoMapper();
    static PlantAccessoryInfoMapper& GetInstance()
    {
        static PlantAccessoryInfoMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// MaterialItemMapper
//-----------------------------------------------------------------
class MaterialItemMapper : public NameMapperBase
{
public:
    MaterialItemMapper();
    static MaterialItemMapper& GetInstance()
    {
        static MaterialItemMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// NewAvatarsMapper
//-----------------------------------------------------------------
class PlantNewAvatarMapper : public NameMapperBase
{
public:
    PlantNewAvatarMapper();
    static PlantNewAvatarMapper& GetInstance()
    {
        static PlantNewAvatarMapper instance;
        return instance;
    };
};

class PlantNewAvatarPieceMapper : public NameMapperBase
{
public:
    PlantNewAvatarPieceMapper();
    static PlantNewAvatarPieceMapper& GetInstance()
    {
        static PlantNewAvatarPieceMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// PerkMapper
//-----------------------------------------------------------------
class PerkMapper : public NameMapperBase
{
public:
	PerkMapper();
    static PerkMapper& GetInstance()
    {
        static PerkMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// ArtifactMapper
//-----------------------------------------------------------------
class ArtifactMapper : public NameMapperBase
{
public:
	ArtifactMapper();
    static ArtifactMapper& GetInstance()
    {
        static ArtifactMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// UnchartedBoostMapper
//-----------------------------------------------------------------
class UnchartedBoostMapper : public NameMapperBase
{
public:
	UnchartedBoostMapper();
    static UnchartedBoostMapper& GetInstance()
    {
        static UnchartedBoostMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// RankAvatarMapper
//-----------------------------------------------------------------
class RankAvatarMapper : public NameMapperBase
{
public:
	RankAvatarMapper();
    static RankAvatarMapper& GetInstance()
    {
        static RankAvatarMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// CollectionMapper
//-----------------------------------------------------------------
class CollectionMapper : public NameMapperBase
{
public:
	CollectionMapper();
    static CollectionMapper& GetInstance()
    {
        static CollectionMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// CardMapper
//-----------------------------------------------------------------
class CardMapper : public NameMapperBase
{
public:
	CardMapper();
    static CardMapper& GetInstance()
    {
        static CardMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// GeneMapper
//-----------------------------------------------------------------
class GeneMapper : public NameMapperBase
{
public:
	GeneMapper();
    static GeneMapper& GetInstance()
    {
        static GeneMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// GeneEssenceMapper
//-----------------------------------------------------------------
class GeneEssenceMapper : public NameMapperBase
{
public:
	GeneEssenceMapper();
    static GeneEssenceMapper& GetInstance()
    {
        static GeneEssenceMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// GeneTalentMapper
//-----------------------------------------------------------------
class GeneTalentMapper : public NameMapperBase
{
public:
	GeneTalentMapper();
    static GeneTalentMapper& GetInstance()
    {
        static GeneTalentMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// NewPVPZombiePieceMapper
//-----------------------------------------------------------------
class NewPVPZombiePieceMapper :public NameMapperBase
{
public:
	NewPVPZombiePieceMapper();

    static NewPVPZombiePieceMapper& GetInstance()
    {
        static NewPVPZombiePieceMapper instance;
        return instance;
    };
};

//-----------------------------------------------------------------
// ExpMapper
//-----------------------------------------------------------------
class ExpMapper :public NameMapperBase
{
public:
	ExpMapper();

    static ExpMapper& GetInstance()
    {
        static ExpMapper instance;
        return instance;
    };
};


#endif /* defined(__PlantsVersusZombies2__PlantNameMapper__) */
