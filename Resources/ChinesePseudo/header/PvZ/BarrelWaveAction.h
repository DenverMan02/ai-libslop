//
//  BarrelWaveAction.h
//  PlantsVersusZombies2
//
//

#ifndef BARRELWAVEACTION_H
#define BARRELWAVEACTION_H

#include "Wave.h"
#include "BoardConstants.h"
#include "GridItemBarrel.h"

enum BarrelType
{
	BarrelType_Empty,
	BarrelType_Moster,
	BarrelType_powder,
};

struct BarrelDescription
{
	BarrelDescription()
	{
		Row = Rand() % BoardConstants::NUMBER_OF_ROWS();
		Type = "barrelempty";
    }

	int 					Row;
	std::string				Type;
	GriditemBarrelParams	Params;
};

class BarrelWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(BarrelWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	void SpawnBarrel(BarrelDescription des);
	static void SpawnBarrelStatic(BarrelDescription des);

private:
//    void FlashScreen();

private:
	int   m_index;
	float m_nextBarrelTime;
    float m_barrelTipTime;
    bool  m_active;
    bool  m_postEnd;
};

class BarrelWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(BarrelWaveActionProps, WaveActionProperties, RtClass);

	BarrelWaveActionProps() {}
//	: KillRate(0){}
	RtClass* GetActionClass() const override { return BarrelWaveAction::StaticGetClass(); }

	pvztime_t Interval = 0;
    std::vector<BarrelDescription>  Barrels;
//    float KillRate;
};

#endif /* BARRELWAVEACTION_H */
