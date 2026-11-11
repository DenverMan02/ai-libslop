/*
 * WorldCupModule.h
 *
 *  Created on: 2018-4-17
 *      Author: Administrator
 */

#ifndef INTROWORLDCUP_H_
#define INTROWORLDCUP_H_

#include "StandardLevelIntro.h"
#include "Core.h"
#include "ButtonListener.h"
#include "GameNotify.h"
#include "PVZTypes.h"
#include "Plant.h"
#include "GridItemAnimation.h"
#include "AnimationMgr.h"
#include "Zombie.h"
#include "Effect_FloatingText.h"

namespace Message
{
	void NotifyGameBegin();
}

class BouncingArrow;

class GridItemObstacle : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemObstacle, GridItemAnimation, RtClass);

    GridItemObstacle();
    ~GridItemObstacle();

protected:
    void onGridItemInitialize() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    int CalcRenderOrder() const override;
    //PlantingReason GetCantPlantReason() const;
    //void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
};

enum IntroIconMotion
{
    PVZ_BEGIN_ENUM(Intro_Icon_Motion_),
    Intro_Icon_Motion_Idle,
    Intro_Icon_Motion_Interpolate,
    PVZ_END_ENUM(Intro_Icon_Motion_),
};

enum IntroIconStage
{
	Icon_Move_None,
	Icon_Move_Into,
	Icon_Move_Off
};

class IntroWorldCupIconWidget : public RealObject
{
public:
    RT_CLASS_DEFINE(IntroWorldCupIconWidget, RealObject, RtClass);

    IntroWorldCupIconWidget();
    virtual ~IntroWorldCupIconWidget();

    void            InitView();

    void            onDraw(Graphics* i_g) override;
    void            onUpdate();
    void            UpdateMotion();

    void SetMotionInterpolate(const SexyVector3& i_initialPosition, const SexyVector3& i_finalPosition, pvztime_t i_duration, CurveType i_interpMethod);

    void SetMotionIdle();
    void initializeRenderEffect(const std::string& i_type);
    bool IsFinished() { return m_finishMotion; }
    void SetIsHidden(bool i_hidden);

private:
    void onFinishMotion();
    StandaloneEffect* CreateSelfRenderEffect(const std::string& i_type);
private:

    IntroIconMotion 	m_motion;
    pvztime_t			m_motionStartTime;
    SexyVector3		m_interp_initialPosition;
    SexyVector3		m_interp_finalPosition;
    pvztime_t		m_interp_duration;
    CurveType		m_interp_method;

    bool            m_finishMotion;
    StandaloneEffectPtr m_renderEffect;
};

class IntroWorldCup : public StandardLevelIntro
{
public:
	enum TutorialState
	{
		PVZ_BEGIN_ENUM(TUTORIALSTATE_),
		TUTORIALSTATE_ADVICE_START_PLANT,
		TUTORIALSTATE_ADVICE_BALL_ZOMBIE_APPEARED,
		TUTORIALSTATE_ADVICE_BALL_KILL_BALL_ZOMBIE,
		TUTORIALSTATE_ADVICE_BALL_ZOMBIE_DIED,
		TUTORIALSTATE_ADVICE_BALL_AFTER_PLAYER_SHOT,
		TUTORIALSTATE_ADVICE_BALL_ROCK,
		PVZ_END_ENUM(TUTORIALSTATE_),
	};
	RT_CLASS_DEFINE(IntroWorldCup, StandardLevelIntro, RtClass);

protected:
	IntroWorldCup();

	virtual void initializeModule() override;
	virtual void registerForEvents() override;

	void onViewBoardOrZombiesButtonPressed();
	void onStartGameButtonPressed();
	void addToRenderQueue(class RenderQueue* i_queue);

	enum State
	{
		PVZ_BEGIN_ENUM(STATE_WC_),
		STATE_WC_START,
		STATE_WC_INTRO,
		STATE_WC_START_PLANTING,
		STATE_WC_PLANTING,
		STATE_WC_TEAM_INTRO,
		STATE_WC_PLAYING,
		PVZ_END_ENUM(STATE_WC_),
	};

public:
    bool isPlayingGame(){return m_worldCupState == STATE_WC_PLAYING;}
    int GetTutorialState() { return (int)m_tutorialstate; }
    int GetTutorialStateByType(int i_type);
    void SetCarrierForTutorial(RtWeakPtr<Zombie> i_carrier);
    bool IsTutorial();

private:

	virtual void bringUpSeedChooser() override;

	void spawnObstacles();
	void onLoadComplete() override;
	void startIntro();
	void onUpdate();
	void onGameplayStarted();
	void onEndLevel();
	void onViewZombiesComplete();

	void setState(State i_state);

	void setToolsState(const bool i_introState);
    void onPlantPlanted(Plant* i_plant);
    void onPlantShoveled(Plant* i_plant);
    int  GetPlantCount() const;
    void  setTutorialState(TutorialState tState);
    void onNotifyTutorialState(int i_type);
    Point GetCarrierOffset();
    void CreateIntroIcons();
    void MoveIntroIcons(int i_totalWidth, int i_totalHeight);
    void onDraw(Sexy::Graphics* i_g);
    void CreateIntroEffect();
    void OnEffectDone(class StandaloneEffect* i_effect);
    void OnCountDownEffectDone(class StandaloneEffect* i_effect);
    void MoveOffIntroIcons();
    void onNotifyLeft30Seconds();
    void CreateLeftTime();
    void CreateCountDownEffect();

	State m_worldCupState;
	pvztime_t m_stateEntryTime;
	bool m_isTutorial;
	TutorialState m_tutorialstate;
	RtWeakPtr<BouncingArrow>            m_bouncingArrow;
	AnimationMgrWkPtr                   m_animationMgr;
	RtWeakPtr<Zombie> m_carrier;
	std::vector<IntroWorldCupIconWidget*> m_icons;
	bool m_createdIntroEffect;
	StandaloneEffectPtr m_intro_effect;
	pvztime_t m_intro_endTime;
	IntroIconStage m_iconStage;
	RtWeakPtr<Effect_FloatingText> m_leftTimeText;
	bool m_hasStartLeftTime;
	pvztime_t m_endTime;
	float m_remainTime;
	StandaloneEffectPtr m_countdown_effect;
	StandaloneEffectPtr m_scoreText;
};

class WorldCupProperties : public StandardLevelIntroProperties
{
public:
	RT_CLASS_DEFINE(WorldCupProperties, StandardLevelIntroProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return IntroWorldCup::StaticGetClass();
	}

	WorldCupProperties()
	{
		StartingPlantfood = 0;
		IsTutorial = false;
	}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	int StartingPlantfood;
	bool IsTutorial;
};


#endif /* WORLDCUPMODULE_H_ */
