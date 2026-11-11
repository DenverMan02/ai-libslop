#ifndef NewYearFireCrackerWaveAction_h_
#define NewYearFireCrackerWaveAction_h_

#include "Wave.h"

struct FireCrackerData
{
	FireCrackerData()
	{
		Column = 8;
		Row = 2;
		Hitpoints = 2000.0f;
		ExplodeDamageAmount = 2000.0f;
    }

	int 			Column;
	int				Row;
	float 			Hitpoints;
	float 			ExplodeDamageAmount;
};


class NewYearFireCrackerWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(NewYearFireCrackerWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class NewYearFireCrackerWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(NewYearFireCrackerWaveActionProps, WaveActionProperties, RtClass);

	NewYearFireCrackerWaveActionProps() {}
	RtClass* GetActionClass() const override { return NewYearFireCrackerWaveAction::StaticGetClass(); }

	std::vector<FireCrackerData> FireCrackers;
};


#endif /* NewYearFireCrackerWaveAction_h_ */
