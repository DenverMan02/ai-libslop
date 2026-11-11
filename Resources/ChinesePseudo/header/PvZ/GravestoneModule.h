//
//  GravestoneModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GravestoneModule_h
#define PlantsVersusZombies2_GravestoneModule_h

#include "LevelModule.h"
#include "MTRand.h"

class GridItemGravestone;

struct GravestoneForceSpawnData
{
    GravestoneForceSpawnData()
    {
        TypeName = "";	// empty names use the stage's default gravestones
        GridX = -1;
        GridY = -1;
    }
    
    std::string		TypeName;
    int				GridX;
    int				GridY;
};

class GravestoneModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(GravestoneModule, LevelModule, RtClass);
    
    std::string				GetDefaultGravestoneTypeName() const;

	GridItemGravestone* AddAGraveStone(int i_gridX, int i_gridY);
	void addGraveStones(const std::string& i_gravestoneTypeName, int i_minGridX, int i_maxGridX, int i_count, MTRand &i_levelRNG);
	
protected:
    virtual void initializeModule() override;
	virtual void registerForEvents() override;

private:
	void spawnGravestones();
    
    bool areAllZombieSpawnersDestroyed();
	void onGravestoneCreated(GridItemGravestone* i_gravestone);
	void onGravestoneDestroyed(GridItemGravestone* i_gravestone);
	
	int32 m_numSpawnerGravestonesActive;
	bool  m_hasRegisteredWinCondition;
};

class GravestoneProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(GravestoneProperties, LevelModuleProperties, RtClass);
    
    RtClass* GetModuleClass() const override
    {
        return GravestoneModule::StaticGetClass();
    }
    
    GravestoneProperties()
    {
        GravestoneTypeName = "";	// empty names use the stage's default gravestones
        GravestoneCount = 0;
        GravestoneCountIncludesForceSpawns = false;
        SpawnColumnStart = 0;
        SpawnColumnEnd = 0;
    }
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    std::string	GetDefaultGravestoneTypeName() const;
    
    int	GetRemainingGravestonesToSpawn(int i_gravestonesAlreadySpawnedCount) const;
    
    std::string		GravestoneTypeName;
    int				GravestoneCount;
    bool			GravestoneCountIncludesForceSpawns;
    int				SpawnColumnStart;
    int				SpawnColumnEnd;
    
    std::vector<GravestoneForceSpawnData>	ForceSpawnData;
};


#endif
