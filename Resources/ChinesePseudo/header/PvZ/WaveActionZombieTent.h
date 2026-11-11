#ifndef WaveActionZombieTent_h_
#define WaveActionZombieTent_h_

#include "Wave.h"
#include "Zombie.h"

struct ZombieTentData
{
	ZombieTentData()
	{
		Column = 8;
		Row = 2;
		Hitpoints = 2000.0;
		ProductionInterval = 2.0;
		TentType = "zombie_tent";
    }

	int 			Column;
	int				Row;
	float 			Hitpoints;
	float 			ProductionInterval;
	std::string		TentType;
	std::vector<struct TentZombieWeights> ZombieTypesToSpawn;
};


class WaveActionZombieTent : public WaveAction
{
public:
	RT_CLASS_DEFINE(WaveActionZombieTent, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class WaveActionZombieTentProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(WaveActionZombieTentProps, WaveActionProperties, RtClass);

	WaveActionZombieTentProps() {}
	RtClass* GetActionClass() const override { return WaveActionZombieTent::StaticGetClass(); }

	std::vector<ZombieTentData> ZombieTents;
};


#endif /* WaveActionZombieTent_h_ */
