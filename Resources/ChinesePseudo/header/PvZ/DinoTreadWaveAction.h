
#ifndef DinoTreadWaveAction_hpp
#define DinoTreadWaveAction_hpp

#include "Wave.h"

class DinoTreadWaveAction : public WaveAction
{
public:
    RT_CLASS_DEFINE(DinoTreadWaveAction, WaveAction, RtClass);
    
    void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
    void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
protected:
    void SpawnShadow();
private:
    pvztime_t m_timeToSpawnShadow;
};

class DinoTreadActionProps : public WaveActionProperties
{
public:
    RT_CLASS_DEFINE(DinoTreadActionProps, WaveActionProperties, RtClass);
    
    DinoTreadActionProps()
    {
        WaveStartMessage = "[WARNING_DINO_TREAD]";
        GridY = 3;
        GridXMin = 2;
        GridXMax = 6;
        TimeInterval = 2.0;
    }
    RtClass* GetActionClass() const override { return DinoTreadWaveAction::StaticGetClass(); }
    
    SexyString GetWaveStartMessage() const;
    
    std::string WaveStartMessage;
    int GridY;
    int GridXMin;
    int GridXMax;
    pvztime_t TimeInterval;
};

#endif /* DinoTreadWaveAction_hpp */
