/*
 * CthulhuSubSystem.h
 *
 *  Created on: 2023-7-10
 *      Author: zhousen
 */

#ifndef CTHULHUSUBSYSTEM_H_
#define CTHULHUSUBSYSTEM_H_


#include "UIEasyButtonWidget.h"

namespace Message
{
	void CthulhuAbsorbDark(Plant* parent);
}

typedef RtWeakPtr<class CthulhuPropertySheet> CthulhuPropertySheetPtr;
typedef RtWeakPtr<class Effect_PopAnim> EffectPopAnimPtr;
typedef RtWeakPtr<class CthulhuEasyButton> CthulhuEasyButtonPtr;

////////////////////////////////////////
///  CthulhuSubSystem
////////////////////////////////////////
class CthulhuSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(CthulhuSubSystem, GameSubSystem, RtClass);

	CthulhuSubSystem();
	~CthulhuSubSystem();

	void Update() override;

    CthulhuEasyButton* CreateCthulhuEasyButton(std::string name);
    void InitButton(std::string name, float plantAttackRatio);
    void LoadDangerroomInfo();
    class CthulhuDangerroomInfo GenerateDangerroomInfo();
    SexyVector2 GetButtonPosition();
    int GetEnergy();

protected:
    CthulhuEasyButtonPtr m_button;
};



////////////////////////////////////////
///  CthulhuEasyButton
////////////////////////////////////////
class CthulhuEasyButton : public BoardEntity
{
public:
	RT_CLASS_DEFINE(CthulhuEasyButton, BoardEntity, RtClass);

	CthulhuEasyButton();
	virtual ~CthulhuEasyButton();

    virtual void onUpdate() override;
    virtual void onDraw(Graphics* i_g) override;

    virtual void SetTypeName(const std::string name);
	virtual void Initialize();
	virtual void SetState(int state);
	virtual void Activiate();
	virtual void RebuildParams(const std::string name, bool overwrite = false);

	virtual void SetDangerroomInfo(CthulhuDangerroomInfo info);
	virtual void SetAttackRatioMap(std::string name, float ratio);
	virtual void SetPlantAttackRatio(float ratio);
	virtual float GetPlantAttackRatio() { return m_plantAttackRatio; }

	const std::string GetTypeName() const { return m_typeName; }
	const int GetEnergy() const { return m_energy; }
	const pvztime_t GetTriggerTimeSum() const { return m_triggerTimeSum; }

	virtual void OnAnimationStoppedCallback(const std::string& i_animLabel) {}
	virtual bool onTouchEvent(const Sexy::Touch& i_touch);
	virtual Rect GetDrawRect();

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	virtual int GetStage() { return 1; }

protected:
	std::string m_typeName;
	int m_energy;
	pvztime_t m_triggerTimeSum;
	int m_state;
	int m_stage;
	CthulhuPropertySheetPtr m_props;
	float m_plantAttackRatio;
	Rect m_collisionRect;
	std::map<std::string, float> m_attackRatioMap;
};

class CthulhuEyeballEasyButton : public CthulhuEasyButton
{
public:
	enum {
		CTHULHU_STATE_INVALID = -1,
		CTHULHU_STATE_HIDE,
		CTHULHU_STATE_EYECLOSE_SPAWN,
		CTHULHU_STATE_EYECLOSE_IDLE,
		CTHULHU_STATE_EYECLOSE_TURN_UPGRADE,
		CTHULHU_STATE_EYECLOSE_TURN_OPEN,
		CTHULHU_STATE_EYEOPEN_IDLE,
		CTHULHU_STATE_EYEOPEN_TURN_UPGRADE,
		CTHULHU_STATE_EYEOPEN_FIRE,
		CTHULHU_STATE_ABSORB_DARK,
		CTHULHU_STATE_MAX,
	};

	RT_CLASS_DEFINE(CthulhuEyeballEasyButton, CthulhuEasyButton, RtClass);

	CthulhuEyeballEasyButton();
	virtual ~CthulhuEyeballEasyButton();

    virtual void onUpdate() override;
    virtual void onDraw(Graphics* i_g) override;

	virtual void Initialize() override;
	virtual void SetState(int state) override;
	virtual void Activiate() override;
	virtual void RebuildParams(const std::string name, bool overwrite = false) override;
	virtual void SetDangerroomInfo(CthulhuDangerroomInfo info) override;
	virtual int GetStage() override;

	virtual void OnAnimationStoppedCallback(const std::string& i_animLabel) override;
	virtual bool onTouchEvent(const Sexy::Touch& i_touch) override;

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

	void PlaySingleAnimation(std::string anim);
	void PlayLoopAnimation(std::string anim);
	void PlayAbsorbEffect();

	virtual const std::string GetEyeCloseSpawnName();
	virtual const std::string GetEyeCloseIdleName();
	virtual const std::string GetEyeCloseTurnUpgradeName();
	virtual const std::string GetEyeCloseTurnOpenName();
	virtual const std::string GetEyeOpenIdleName();
	virtual const std::string GetEyeOpenTurnUpgradeName();
	virtual const std::string GetEyeOpenFireName();
	virtual const std::string GetAbsorbDarkName();

	bool IsShowEffect();
	bool IsEnableClick();
	void UpdateTriggerTimeSum();
	void DamageZombies();
	void CthulhuAbsorbDark(Plant* parent);
	void PlantDied(Plant* plant);
	SexyVector3 GenerateEffectPosition();

protected:
	RtWeakPtr<class CthulhuEyeballEffect> m_effect;
};


////////////////////////////////////////
///  CthulhuEyeballEffect
////////////////////////////////////////
class CthulhuEyeballEffect : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(CthulhuEyeballEffect, Effect_PopAnim, RtClass);

	CthulhuEyeballEffect();

	void SetCthulhuEasyButton(CthulhuEasyButtonPtr ptr);

protected:
    void onAnimStopped(const std::string& i_animLabel) override;

protected:
    CthulhuEasyButtonPtr m_button;
};

////////////////////////////////////////
///  CthulhuPropertySheet
////////////////////////////////////////
class CthulhuPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CthulhuPropertySheet, PropertySheetBase, RtClass);

	CthulhuPropertySheet() {
		TypeName = "";
		StageConditions = { 0, 20, 30 };
		TriggerTimeDuration = 60.0f;
		StageDamages = { 100, 200, 999999 };
		StageDamageRatios = { 0.3f, 0.6f, 0.6f };
	}

	std::string TypeName;
	std::vector<int> StageConditions;
	pvztime_t TriggerTimeDuration;
	std::vector<int> StageDamages;
	std::vector<float> StageDamageRatios;
};

class CthulhuEyeballPropertySheet : public CthulhuPropertySheet
{
public:
	RT_CLASS_DEFINE(CthulhuEyeballPropertySheet, CthulhuPropertySheet, RtClass);

	CthulhuEyeballPropertySheet() {
	}
};

namespace CthulhuUtils
{
	CthulhuPropertySheetPtr GetPropertySheetPtr(const std::string typeName);
	void CopyPropertySheetPtr(CthulhuPropertySheetPtr ptr1, CthulhuPropertySheetPtr ptr2, bool overwrite = true);
}


#endif /* CTHULHUSUBSYSTEM_H_ */
