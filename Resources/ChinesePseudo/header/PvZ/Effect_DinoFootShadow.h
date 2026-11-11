
#ifndef DinoFootShadow_hpp
#define DinoFootShadow_hpp

#include "TimeLine.h"
#include "StandaloneEffect.h"

class Effect_DinoFootShadow : public StandaloneEffect
{
public:
    RT_CLASS_DEFINE(Effect_DinoFootShadow, StandaloneEffect, RtClass);
    Effect_DinoFootShadow();
    ~Effect_DinoFootShadow();
    
    void SetMoveEndPos(SexyVector2 pos);
    void StartMove();
protected:
    virtual void onInitialized() override;
    virtual void onDraw(class Graphics* i_g) override;
    virtual void onUpdate() override;
    
    void TryToFindBramble();
    
private:
    
    pvztime_t		m_moveStartTime;
    pvztime_t		m_moveEndTime;
    
    pvztime_t		m_scaleStartTime;
    pvztime_t		m_scaleEndTime;
    pvztime_t		m_treadTime;
    SexyVector2		m_startPos;
    SexyVector2		m_endPos;
    SexyVector2		m_shadowScale;
    float           m_scale;
    bool            m_moveStarted;
    
    bool            m_foundBramble = false;
};

#endif
