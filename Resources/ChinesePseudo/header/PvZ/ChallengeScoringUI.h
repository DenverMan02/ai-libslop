//
//  ChallengeScoringUI.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery 2/10/16.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeScoringUI_h
#define PlantsVersusZombies2_ChallengeScoringUI_h

#include "ChallengeUI.h"
#include "JoustDataPackets.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

class ChallengeScoringUI : public ChallengeUI
{
public:
    enum ScoreMultiplierFormat
    {
        MULTIPLIER_FULL,
        MULTIPLIER_BARE_NUMBER
    };

public:
	RT_CLASS_DEFINE(ChallengeScoringUI, ChallengeUI, RtClass);
	
	ChallengeScoringUI();
	virtual ~ChallengeScoringUI();

	void SetMeterValue(float i_meterValue) { m_meterValue = i_meterValue; }
	void SetMeterSolidPortion(float i_meterSolidPortion) { m_meterSolidPortion = i_meterSolidPortion; }
	
	void SetScore(ScoreType i_score) { m_score = i_score; }
	void SetMultiplier(int i_multiplier) { m_multiplier = i_multiplier; }

	void SetFrenzyMode(bool i_isFrenzyMode) { m_frenzyMode = i_isFrenzyMode; }
	
    void SetShowScoreValue(bool i_showScoreValue, bool i_showScoreBox) { m_showScoreValue = i_showScoreValue; m_showScoreBox = i_showScoreBox; updateDrawBoxVisibility(); }
    void SetShowMultiplierSphere(bool i_showMultiplierSphere) { m_showMultiplierSphere = i_showMultiplierSphere; }

    void SetScoreFormatString(SexyString i_scoreDisplayFormat) { m_scoreFormat = i_scoreDisplayFormat; updateDrawBoxVisibility(); }
    void SetMultiplierFormatString(SexyString i_multiplierDisplayFormat) { m_multiplierFormat = i_multiplierDisplayFormat; updateDrawBoxVisibility(); }

    void SetRiftBonusMode(bool i_isBonusMode) { m_riftBonusMode = i_isBonusMode; }

protected:
	void postDraw(Graphics* i_g) override;
    void updateDrawBoxVisibility();
    void onUpdate() override;

    void drawMultiplierArea(Graphics* i_g, Color& i_fontColor);
    void drawScore(Graphics* i_g, Color& i_fontColor);

private:
    void onScoreChallengeCompleted();

	float	m_meterSolidPortion;
	float	m_meterValue;
	ScoreType	m_score;
	int		m_multiplier;
	bool	m_frenzyMode;
	bool	m_showScoreValue;
    bool    m_showScoreBox;
    bool    m_showAsCompletedChallenge;
    bool    m_showMultiplierSphere;
    bool    m_riftBonusMode;

    SexyString m_scoreFormat;
    SexyString m_multiplierFormat;

    class PopAnimRig* mPopAnimRig;

};



#endif
