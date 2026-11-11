//
//  SkyCannonTypeUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.9
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SkyCannonTypeUI__
#define __PlantsVersusZombies2__SkyCannonTypeUI__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

class SkyCannonTypeUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(SkyCannonTypeUI, UIWidget, RtClass);
	
	SkyCannonTypeUI();
	virtual ~SkyCannonTypeUI();
	
	virtual void	Draw(Graphics* i_g) override;
	virtual bool	OnTouch(const Sexy::Touch& i_touch) override;
    
	bool				IsCoolDown();
	void				SetTypeID(int typeID);
	int				GetTypeID() const { return m_typeID; }
	void				SetSelect(bool setting);
	bool				IsSelect() const { return m_bSelect; }
    void				SetCoolDownTime(float i_coolDownTime) { m_fCoolDownTime = i_coolDownTime; }
	void				SetCost(int val) { m_cost = val; }
	void				SetCrazy(bool setting);
    
protected:
	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
	virtual void	onUpdate() override;

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing);
	OVERRIDE_STATE_ONENTER(WidgetState, NotReady);

	void 			onGameplayEnded();

	void				RefreshImages();
    
protected:
	float				m_fCoolDownTime;
	int                m_typeID;
	bool				m_bSelect;
	bool				m_bCrazy;
	int				m_cost;
	ImagePtr		m_pImageBack;
	ImagePtr		m_pImageCannon;
	ImagePtr		m_pImageCostbar;
	RtWeakPtr<class Effect_PopAnim> m_crazyEffect;
};

namespace Message
{
	void SkyCannonTypeSelected(int i_typeID);
}

#endif /* defined(__PlantsVersusZombies2__SkyCannonTypeUI__) */
