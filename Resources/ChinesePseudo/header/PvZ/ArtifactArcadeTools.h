

#ifndef ARTIFACT_ARCADE_TOOLS_H_
#define ARTIFACT_ARCADE_TOOLS_H_



#include <string>
#include "Graphics.h"
#include "GameSubSystem.h"
#include "TimeMgr.h"

enum ArtifactArcadeSubSystemState
{
    ArtifactArcadeState_Invaild = 0,
    ArtifactArcadeState_Idle,
    ArtifactArcadeState_Start,
    ArtifactArcadeState_Effect,
    ArtifactArcadeState_End,
};

class ArtifactArcadeSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ArtifactArcadeSubSystem, GameSubSystem, RtClass);

    ArtifactArcadeSubSystem();
    ~ArtifactArcadeSubSystem();

	virtual void Update() override;
	virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

    void setState(ArtifactArcadeSubSystemState i_state);

    void Start();

    //now we register touch event by self
    void registerHandTouchEvents();
    void unregisterHandTouchEvents();
protected:
    virtual void onDestroy() override;
private:
    void AddPlants();
    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    void onDrawEffectUIOnBoard(Sexy::Graphics *i_g);
    void onDrawSelectionOnBoard(Sexy::Graphics *i_g);

    void ResetScale();
    float GetScale();

    int m_counter;
    pvztime_t m_timer;
    ArtifactArcadeSubSystemState m_state;
    bool m_switchButton;
    pvztime_t m_switchTimer;

    pvztime_t m_cureStart;
}; 

#endif