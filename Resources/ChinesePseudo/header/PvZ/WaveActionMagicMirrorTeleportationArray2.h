/*
 *	WaveActionMagicMirrorTeleportationArray2.h
 *
 *		Created on: 2023-3-14
 *			Author: kkdud
 */

#ifndef PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY2_H_
#define PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY2_H_

#include "Wave.h"
#include "Zombie.h"

struct MagicMirrorTeleportationArrayData2
{
	MagicMirrorTeleportationArrayData2()
	{
		MirrorExistDuration = 5.0f;
		TypeIndex = 1;
		BlingInterval = 1.0f;
    }

	int Mirror1GridX;
	int Mirror1GridY;
	int Mirror2GridX;
	int Mirror2GridY;
	float MirrorExistDuration;
	int TypeIndex;
	float BlingInterval;
};


class WaveActionMagicMirrorTeleportationArray2 : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionMagicMirrorTeleportationArray2, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class WaveActionMagicMirrorTeleportationArrayProps2 : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionMagicMirrorTeleportationArrayProps2, WaveActionProperties, RtClass);

	WaveActionMagicMirrorTeleportationArrayProps2() {}
	RtClass* GetActionClass() const override { return WaveActionMagicMirrorTeleportationArray2::StaticGetClass(); }

	std::vector<MagicMirrorTeleportationArrayData2> MagicMirrorTeleportationArrays;
};



#endif /* PLANT2VERSUSZOMBIES2_PVZ2_WAVEACTIONMAGICMIRRORTELEPORTATIONARRAY2_H_ */
