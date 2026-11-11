//
//  AdaptorJoustMatchLoadingScreen.h
//  PvZ2
//
//  Created by Sola, Joseph on 10/10/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustMatchLoadingScreen_h
#define AdaptorJoustMatchLoadingScreen_h

#include "HotUIAdaptor.h"
#include "TimeLine.h"
#include "MacroStateMachine.h"

STATE_ENUM_BASE_BEGIN(MatchLoadingScreenState)
    MLSS_Intro,
    MLSS_Idle,
    MLSS_Outro,
    MLSS_Done,
STATE_ENUM_END(MatchLoadingScreenState);

struct AdaptorJoustMatchLoadingScreenConfig
{
    AdaptorJoustMatchLoadingScreenConfig()
        : PlayerAvatarIndex(0)
        , OpponentAvatarIndex(0)
        , CloseOnTransitionEnd(true)
    {}
    
    SexyString PlayerName;
    SexyString OpponentName;
    int PlayerAvatarIndex;
    int OpponentAvatarIndex;
    bool CloseOnTransitionEnd;
};

class AdaptorJoustMatchLoadingScreen : public HotUIAdaptor
{
public:
    RT_CLASS_DEFINE(AdaptorJoustMatchLoadingScreen, HotUIAdaptor, RtClass);
    
    void Setup(const AdaptorJoustMatchLoadingScreenConfig& i_config);
    void Update() override;
    
    void SetLoadingComplete();
    
protected:
    void onLoadUIView() override;
    void onLinkToUIViewCreated() override;
    void onLayoutFinished() override;
	
	bool OnBackButtonPressed() override;

    bool updateWidgetFromAnimation(const std::string& i_widgetName, const std::string& i_animName, pvztime_t i_time);
    bool isReadyToTransitionOut();
    void startHotUIAnim(const std::string& i_widgetName, const std::string& i_animName);
    void onHotUIAnimFinished(const std::string& i_animName);
    
    DECLARE_FSM_HANDLER_BASE(MatchLoadingScreenState);

    DECLARE_FSM_STATE_VALUE(MatchLoadingScreenState);
    
    AdaptorJoustMatchLoadingScreenConfig m_config;
    bool m_layoutFinished = false;
    bool m_forceReadyToTransition = false;
    bool m_hotUIAnimActive = false;
    pvztime_t m_animStartTime;
    CurveSequenceCollection<SexyVector2> m_anims;
};

#endif /* AdaptorJoustMatchLoadingScreen_h */
