/*
 *	WaveActionMagicMirrorTeleportationArray.h
 *
 *		Created on: 2022-5-31
 *			Author: kkdud
 */

#ifndef PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY_H_
#define PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY_H_

#include "Wave.h"
#include "Zombie.h"

struct MagicMirrorTeleportationArrayData
{
	MagicMirrorTeleportationArrayData()
	{
		MirrorExistDuration = 5.0f;
    }

	int Mirror1GridX;
	int Mirror1GridY;
	int Mirror2GridX;
	int Mirror2GridY;
	float MirrorExistDuration;
};


class WaveActionMagicMirrorTeleportationArray : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionMagicMirrorTeleportationArray, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class WaveActionMagicMirrorTeleportationArrayProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionMagicMirrorTeleportationArrayProps, WaveActionProperties, RtClass);

	WaveActionMagicMirrorTeleportationArrayProps() {}
	RtClass* GetActionClass() const override { return WaveActionMagicMirrorTeleportationArray::StaticGetClass(); }

	std::vector<MagicMirrorTeleportationArrayData> MagicMirrorTeleportationArrays;
};



#endif /* PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY_H_ */
