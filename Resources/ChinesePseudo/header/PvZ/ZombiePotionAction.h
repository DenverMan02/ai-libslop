/*
 * ZombiePotionAction.h
 *
 *  Created on: 2021-7-20
 *      Author: admin
 */

#ifndef ZOMBIEPOTIONACTION_H_
#define ZOMBIEPOTIONACTION_H_

#include "Wave.h"

struct PotionData
{
	PotionData()
	{
        Type = "";
    }

	Point Location;
	std::string Type;
};

class ZombiePotionAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(ZombiePotionAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void CheckGridPlants(int i_gridX, int i_gridY);
};

class ZombiePotionActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(ZombiePotionActionProps, WaveActionProperties, RtClass);

	ZombiePotionActionProps() {}
	RtClass* GetActionClass() const override { return ZombiePotionAction::StaticGetClass(); }

    std::vector<PotionData> Potions;
};

// ZombieBoundTileAction
class ZombieBoundTileAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(ZombieBoundTileAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    void CheckGridPlants(int i_gridX, int i_gridY);
};

class ZombieBoundTileActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(ZombieBoundTileActionProps, WaveActionProperties, RtClass);

	ZombieBoundTileActionProps() {}
	RtClass* GetActionClass() const override { return ZombieBoundTileAction::StaticGetClass(); }

    std::vector<PotionData> Tiles;
};


#endif /* ZOMBIEPOTIONACTION_H_ */
