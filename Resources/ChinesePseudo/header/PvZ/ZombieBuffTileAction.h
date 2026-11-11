/*
 * ZombieBuffTileAction.h
 *
 *  Created on: 2021-8-10
 *      Author: admin
 */

#ifndef ZOMBIEBUFFTILEACTION_H_
#define ZOMBIEBUFFTILEACTION_H_

#include "Wave.h"
#include "GameSubSystem.h"

struct BuffTileData
{
	BuffTileData()
	{
        Type = "";
    }

	Point Location;
	std::string Type;
};

class ZombieBuffTileAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(ZombieBuffTileAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class ZombieBuffTileActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(ZombieBuffTileActionProps, WaveActionProperties, RtClass);

	ZombieBuffTileActionProps() {}
	RtClass* GetActionClass() const override { return ZombieBuffTileAction::StaticGetClass(); }

    std::vector<BuffTileData> BuffTiles;
};


#endif /* ZOMBIEBUFFTILEACTION_H_ */
