//
//  AdaptorJoustPlayMeterHUD.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/29/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustPlayMeterHUD_h
#define AdaptorJoustPlayMeterHUD_h

#include "HotUIAdaptor.h"
#include "Curve.h"

class AdaptorJoustPlayMeterHUD : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorJoustPlayMeterHUD, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorJoustPlayMeterHUD() :
	m_leftScore(0),
	m_rightScore(0),
	m_desiredCenterScoreRatio(0.5),
	m_previousCenterScoreRatio(0.5),
	m_currentCenterScoreRatio(0.5),
	m_endScoreRatioLerp(PVZ_EOT()),
	m_startScoreRatioLerp(PVZ_EOT()),
    m_lerpCurveType(CurveType::CURVE_EASE_IN_OUT),
    m_scoreLerpDelay(3.0)
	{}
	
	void SetLeftScore(int i_score);
	void SetRightScore(int i_score);
    void SetLeftScoreTarget(int i_score);
    void SetLeftScoreText(int i_score);
    void SetLerpCurveType(CurveType i_curveType);
    void SetScoreLerpDelay(pvztime_t i_delay);
    
	bool IsLocalPlayerWinning() { return m_leftScore > m_rightScore; }
	
	void SetTimer(int i_secondsRemaining);
	void SetTimerVisible(bool i_visible);
    
    void SetAvatarIndices(int i_leftAvatar, int i_rightAvatar);
    void SetAvatarsVisible(bool i_visible);
    
    void SnapScoresToCurrentValues();
	
	void Update() override;
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
private:
	
	void updateScoreLerpTarget();
	void setScoreLerpTarget(float i_center);
	void updateScoreLerp();
	void updateUIScoreCenter(float i_center);
	float getScoreLerpDelay() { return m_scoreLerpDelay; }
	
	int m_leftScore;
	int m_rightScore;
	
	float m_previousCenterScoreRatio;
	float m_desiredCenterScoreRatio;
	float m_currentCenterScoreRatio;
	
	pvztime_t m_startScoreRatioLerp;
	pvztime_t m_endScoreRatioLerp;
    pvztime_t m_scoreLerpDelay;
    CurveType m_lerpCurveType;
};

#endif
