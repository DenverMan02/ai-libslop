#ifndef __CUSTOM_LEVEL_APPRAISE_UI__
#define __CUSTOM_LEVEL_APPRAISE_UI__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

class CustomLevelAppraiseUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(CustomLevelAppraiseUI, UIWidget, RtClass);

	CustomLevelAppraiseUI();
	virtual ~CustomLevelAppraiseUI();
	
	// Public Interface (Inheritable)
	virtual void	Draw(Graphics* i_g) override;
	virtual void	OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	virtual void	OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void	OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	//PVZ2_CHINESE_START
    virtual const Sexy::Rect GetHitRect() override;
	//PVZ2_CHINESE_END

	void Reported();
	bool IsReported();
	void PlayCoinObtained();
	bool IsPlayCoinObtained();
	void Supported();
	bool IsSupported();
	void NotSupported();
	bool IsNotSupported();


protected:
	// Protected Interface (Inheritable)

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
	
	// Protected Interface (Core)
	void			onGamePaused();
	void			onGameUnpaused();
	void 			onGameplayEnded();
	void			onLevelStarting();
	void			onLastStandStart();
	
	//PVZ2_CHINESE_START
	int GetAppraiseTouchIndex(const int i_mouseX, const int i_mouseY);
	void PressIndex(int i_index);
	void UnPress();

protected:	
	// Private Members (not serialized)
	bool			m_gameIsPaused;
	int				m_currentPress;
	int				m_pressIndex[4];
	bool			m_buttonState[4];
	float			m_countTimer;
	bool			m_timeCome;
};


#endif