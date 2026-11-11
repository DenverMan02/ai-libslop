#ifndef SummerFireworksWaveAction_h_
#define SummerFireworksWaveAction_h_

#include "Wave.h"

struct SummerFireworksData
{
	SummerFireworksData()
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


class SummerFireworksWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(SummerFireworksWaveAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class SummerFireworksWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(SummerFireworksWaveActionProps, WaveActionProperties, RtClass);

	SummerFireworksWaveActionProps() {}
	RtClass* GetActionClass() const override { return SummerFireworksWaveAction::StaticGetClass(); }

	std::vector<SummerFireworksData> SummerFireworksGroup;
};


#endif /* SummerFireworksWaveAction_h_ */
