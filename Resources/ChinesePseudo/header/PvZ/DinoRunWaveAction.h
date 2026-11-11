
#ifndef DinoRunWaveAction_hpp
#define DinoRunWaveAction_hpp

#include "Wave.h"

class DinoRunWaveAction : public WaveAction
{
public:
    RT_CLASS_DEFINE(DinoRunWaveAction, WaveAction, RtClass);
    
    void WaveStart(int i_waveNumber, WaveType::WaveType i_type, bool i_isFinal, MTRand& i_random) override;
    void WaveUpdate(int i_waveNumber, Sexy::MTRand &i_random) override;
    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
protected:
    void SpawnDinoRun();
private:
    pvztime_t m_timeToSpawnDinoRun;
};

class DinoRunActionProps : public WaveActionProperties
{
public:
    RT_CLASS_DEFINE(DinoRunActionProps, WaveActionProperties, RtClass);
    
    DinoRunActionProps()
    {
        WaveStartMessage = "[WARNING_DINO_RUN]";
        DinoRow = 3;
        TimeInterval = 2.0;
    }
    
    RtClass* GetActionClass() const override { return DinoRunWaveAction::StaticGetClass(); }
    
    SexyString GetWaveStartMessage() const;
    
    std::string WaveStartMessage;
    int DinoRow;
    pvztime_t TimeInterval;
};

#endif /* DinoRunWaveAction_hpp */
