//
//  AdaptorJoustResultsScreen.h
//  PlantsVersusZombies2
//
//  Created by Knapp, Randy on 8/28/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustResultsScreen_h
#define AdaptorJoustResultsScreen_h

#include <string>

#include "HotUIAdaptor.h"
#include "HotUISeedPacket.h"
#include "HotUIWidget.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "TimeLine.h"

typedef RtReflectionDelegate<Delegate0> ButtonDelegate;

class HotUIJoustResultsScreenProperties : public HotUIWidgetProperties
{
public:
    RT_CLASS_DEFINE(HotUIJoustResultsScreenProperties, HotUIWidgetProperties, RtClass);
    
    float ScoreFillStartDelay = 0.0f;
    float ScoreFillLength = 0.0f;
    float ShieldBreakLength = 0.0f;
    float CrownFillStartDelay = 0.0f;
    float CrownFillLength = 0.0f;
    float CrownFillEffectLength = 0.0f;
};

struct AdaptorJoustResultsScreenParams
{
	AdaptorJoustResultsScreenParams()
		: Win(false)
		, PlayerScore(0)
		, OpponentScore(0)
		, PlayerAvatar(0)
		, OpponentAvatar(0)
		, EarnedCrowns(0)
	{}
	
	bool Win;
	int EarnedCrowns;
	ButtonDelegate DismissFunction;
	
	SexyString PlayerName;
	int PlayerScore;
	int PlayerAvatar;
	std::vector<HotUISeedPacketConfig> PlayerLoadout;

	SexyString OpponentName;
	int OpponentScore;
	int OpponentAvatar;
	std::vector<HotUISeedPacketConfig> OpponentLoadout;
};

class AdaptorJoustResultsScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustResultsScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Dismiss,
		Continue,
		Back,
	};
	
public:
	AdaptorJoustResultsScreen();
	virtual ~AdaptorJoustResultsScreen();

	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
	void EnableFullScreenDismiss(bool i_enable);

	void SetParams(const AdaptorJoustResultsScreenParams& i_params);
    
    void Update() override;
	
	void Close();
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
private:
	void setup();
	void refresh();
	void onContinueClick();
    
    void startWinScoreFillFirstHalf(pvztime_t i_atTime);
    void startWinScoreFillSecondHalf(pvztime_t i_atTime);
    void startLossScoreFill(pvztime_t i_atTime);
    void startCrownFill(pvztime_t i_atTime);
    void startShieldBreak(pvztime_t i_atTime);
    void sendBarFillStartAudio(pvztime_t i_unusedTime);
    void sendBarFillStopAudio(pvztime_t i_unusedTime);
    void sendCrownFillOnWinAudio(pvztime_t i_unusedTime);
    
    void onCrownIntroAnimStopped(const std::string& i_animName);
    void onCrownBumpAnimStopped(const std::string& i_animName);
    
    std::string getWinLossAnimLabelSuffix() const;
    class AdaptorJoustPlayMeterHUD* getJoustMeterAdaptor() const;
	
	AdaptorJoustResultsScreenParams m_params;
    
    TimeLine m_effectSequencer;
    
    pvztime_t m_scoreLerpStart;
    int m_startingScoreDisplay;
    int m_targetScoreDisplay;
    pvztime_t m_crownLerpStart;
    int m_crownRemainingBumps;
};

#endif
