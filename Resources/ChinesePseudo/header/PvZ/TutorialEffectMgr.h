/*
 * TutorialEffectMgr.h
 *
 *  Created on: 2021-4-1
 *      Author: admin
 */

#ifndef TUTORIALEFFECTMGR_H_
#define TUTORIALEFFECTMGR_H_

#include "Singleton.h"
#include "Core.h"
#include "ButtonListener.h"
#include "AnimationMgr.h"
#include "RealObject.h"
#include "SequentialActionRunner.h"

namespace Message
{
	void NotifyTutorialEffectEnd(int i_type);
}

enum TutorialIconType
{
	Icon_Type_Default,
	Icon_Type_DailyReward,
	Icon_Type_StarConvert,
	Icon_Type_Gacha,
	Icon_Type_Avatar,
	Icon_Type_TravelLog,
	Icon_Type_PlantFamily,
	Icon_Type_Challenge,
	Icon_Type_Joust,
	Icon_Type_DangerRoom,
	Icon_Type_CrystalStore,
	Icon_Type_Galaxy,
	Icon_Type_FirstRecharge,
	Icon_Type_PlantLevelup,
	Icon_Type_PlantAdventure,
	Icon_Type_PVP,
	Icon_Type_Transgenosis,
	Icon_Type_Rift,
	Icon_Type_PVZ1,
	Icon_Type_CustomLevel,
	Icon_Type_Artifact,
	Icon_Type_PennyClassroom,
	Icon_Type_CardGame,
	Icon_Type_NewPvP,
	Icon_Type_Gene,
	Icon_Type_NewplayerActivityCollection,
};

struct SpecialIconData
{
	SpecialIconData()
	{

	}

	SpecialIconData(int i_type, std::string i_imageType)
	:Type(i_type)
	,ImageType(i_imageType)
	{

	}

	int Type;
	std::string ImageType;
};

class TutorialIconEffect : public RealObject
{
public:
    RT_CLASS_DEFINE(TutorialIconEffect, RealObject, RtClass);

    TutorialIconEffect();
    virtual ~TutorialIconEffect();

    void            InitView();

    void            onDraw(Graphics* i_g) override;
    void            onUpdate();

    void initializeRenderEffect(const std::string& i_type);
    void initializeBackgroundRenderEffect(const std::string& i_type);
    void SetIsHidden(bool i_hidden);
    void ShowBackgroundEffect(bool i_show);
    void UpdateScale(float i_scale);

private:
    class StandaloneEffect* CreateSelfRenderEffect(const std::string& i_type);
    class StandaloneEffect* CreateBGEffect(const std::string& i_type);

    RtWeakPtr<class StandaloneEffect> m_renderEffect;
    RtWeakPtr<class StandaloneEffect> m_renderBgEffect;
};

class TutorialIconAppearAction : public RunnableAction
{
public:
	TutorialIconAppearAction(pvztime_t i_waitDurationSeconds, TutorialIconEffect* i_icon);
	void onBegin() override;
	void onUpdate() override;

protected:
	virtual void Prepare();
	virtual void UpdateAction() {}

	TutorialIconEffect* m_icon;

private:
	pvztime_t m_startTime;
	pvztime_t m_duration;
};

class TutorialIconShakeAction : public TutorialIconAppearAction
{
public:
	TutorialIconShakeAction(pvztime_t i_waitDurationSeconds, TutorialIconEffect* i_icon, float i_shakeOffset);
	//void onBegin() override;

protected:
	void Prepare() override;
	void UpdateAction() override;

private:
	float m_shakeOffset;
	SexyVector3 m_initPos;
};

class TutorialIconScaleAction : public RunnableAction
{
public:
	TutorialIconScaleAction(float i_initialScale, float i_finalScale, pvztime_t i_duration, CurveType i_interpMethod, TutorialIconEffect* i_icon);
	void onBegin() override;
	void onUpdate() override;

protected:
	virtual void beginOthers() {}
	virtual void updateOthers(float i_alpha) {}

	TutorialIconEffect* m_icon;
	CurveType		m_interp_method;

private:
	pvztime_t		m_motionStartTime;
	float			m_interp_initialScale;
	float			m_interp_finalScale;
	pvztime_t		m_interp_duration;

	bool            m_finishMotion;
};

class TutorialIconMoveScaleAction : public TutorialIconScaleAction
{
public:
	TutorialIconMoveScaleAction(float i_initialScale, float i_finalScale, pvztime_t i_duration, CurveType i_interpMethod, TutorialIconEffect* i_icon, const Sexy::SexyVector3 &i_finalPosition);
	void beginOthers() override;
	void updateOthers(float i_alpha) override;

	void onEnd() override;

private:
	SexyVector3		m_interp_initialPosition;
	SexyVector3		m_interp_finalPosition;
};

class TutorialEffectMgr : public LazySingleton <TutorialEffectMgr>
{
public:
	TutorialEffectMgr();
    ~TutorialEffectMgr();

    std::string GetImageTypeByIconType(TutorialIconType i_type);
    std::string GetImageTypeFromWidgetSheet();

    void TriggerIconEffect(TutorialIconType i_type);

    void Draw(Graphics* i_g);
    void Update();

    void SetDarkenBg(bool i_darken) { m_darkenBg = i_darken; }
    void TryRemoveIconEffect();
    void ShowOriginalIcon(bool i_visible);
    void NotifyTutorialEffectEnd();
    int GetActivityIdByIconType(TutorialIconType i_type);
    bool IsSpecialIconType(TutorialIconType i_type);
    int GetSpecialIconType(TutorialIconType i_type);
    void DisplayAdvice(const std::string& i_text);
    bool IsRunning() { return m_running; }
private:
    TutorialIconEffect* BuildIcon(TutorialIconType i_type);
    void BuildActions(TutorialIconType i_type);

    SexyVector3 GetIconPositionByIconType(TutorialIconType i_type);

    TutorialIconEffect* m_icon;
    ForeverSequentialActionRunner m_actionRunner;
    bool m_darkenBg;
    TutorialIconType m_currentType;
    AnimationMgr     m_animationMgr;
    bool m_running;
};

#endif /* TUTORIALEFFECTMGR_H_ */
