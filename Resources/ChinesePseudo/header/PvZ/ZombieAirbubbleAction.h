#ifndef ZOMBIEAIRBUBBLEACTION_H_
#define ZOMBIEAIRBUBBLEACTION_H_

#include "Wave.h"

class ZombieAirbubbleAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(ZombieAirbubbleAction, WaveAction, RtClass);

	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
};

class ZombieAirbubbleActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(ZombieAirbubbleActionProps, WaveActionProperties, RtClass);

	ZombieAirbubbleActionProps() {}
	RtClass* GetActionClass() const override { return ZombieAirbubbleAction::StaticGetClass(); }

    int BubbleNumber;
    float BubbleHealth;
    float SpeedRangeMin;
	float SpeedRangeMax;
};


#endif /* ZOMBIEAIRBUBBLEACTION_H_ */
