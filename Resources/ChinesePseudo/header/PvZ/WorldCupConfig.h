/*
 * WorldCupConfig.h
 *
 *  Created on: 2018-4-23
 *      Author: Administrator
 */

#ifndef WORLDCUPCONFIG_H_
#define WORLDCUPCONFIG_H_

#include "Precompile.h"
#include "RtObject.h"

struct ObstacleNonSpawnData
{
	ObstacleNonSpawnData()
    {
        GridX = -1;
        GridY = -1;
    }

    int				GridX;
    int				GridY;
};

struct PlayerSet
{
    int setId;
    std::vector<ObstacleNonSpawnData> setLocations;

    PlayerSet()
    {
    	setId = 0;
    	setLocations.clear();
    }
};

class WorldCupConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(WorldCupConfig, Sexy::RtObject, RtClass);

    WorldCupConfig();
    ~WorldCupConfig();

    void Refresh();

    std::vector<PlayerSet> GetPlayerSetList();
    std::vector<ObstacleNonSpawnData> GetTargetSetLocations(int i_id);

private:
    bool m_inited;
    std::vector<PlayerSet> m_setList;
};


#endif /* WORLDCUPCONFIG_H_ */
