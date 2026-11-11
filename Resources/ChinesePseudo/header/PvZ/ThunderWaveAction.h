//
//  ThunderWaveAction.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-11.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ThunderWaveAction__
#define __PlantsVersusZombies2__ThunderWaveAction__

#include "Wave.h"

enum ThunderType
{
	ThunderType_Positive,
    ThunderType_Negative
};

struct ThunderDescription
{
	ThunderDescription()
	{
        Type = ThunderType_Positive;
    }
	
	ThunderType Type;
};

class ThunderWaveAction : public WaveAction
{
public:
	RT_CLASS_DEFINE(ThunderWaveAction, WaveAction, RtClass);
	
	void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
	void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void WaveEnd(int i_waveNumber, Sexy::MTRand &i_random) override;
    
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
private:

    void takeThunder();
    void FlashScreen();
    
private:
	int   m_index;
	float m_nextThunderTime;
    float m_thunderTipTime;
    bool  m_active;
    bool  m_postEnd;
};

class ThunderWaveActionProps : public WaveActionProperties
{
public:
	RT_CLASS_DEFINE(ThunderWaveActionProps, WaveActionProperties, RtClass);
	
	ThunderWaveActionProps()
	: KillRate(0){}
	RtClass* GetActionClass() const override { return ThunderWaveAction::StaticGetClass(); }
    
    std::vector<ThunderDescription>  Thunders;
    float KillRate;
};

#endif /* defined(__PlantsVersusZombies2__ThunderWaveAction__) */
