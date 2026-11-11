//
//  WorldMap_KeyBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 2/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_KeyBank_h
#define PlantsVersusZombies2_WorldMap_KeyBank_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "PVZTypes.h"
#include "GameEventMgr.h"

class WorldMap_KeyBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_KeyBank, UIWidget, RtClass);	

	enum KeyBankSlidingState
	{
		STATE_INVALID,
		STATE_IDLE,
		STATE_SLIDING_IN,
		STATE_SLIDING_OUT,
		STATE_WAITING,
	};
	
	WorldMap_KeyBank();
	virtual ~WorldMap_KeyBank();
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
	virtual void			SlideIn();
	virtual void			SlideOut();

protected:	

	OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
	OVERRIDE_STATE_UPDATE(WidgetState, Ready)

	// Protected Interface (Inheritable)

	virtual void			initLoadingResourcesGroupList() override;
	virtual void			syncKeyCurrency();
	
	KeyCurrency				m_keyCurrency;
	ImagePtr				m_keyImage;
	ImagePtr				m_queuedKeyImage;
	
private:	

	// Private Interface
	
	void					onKeyCurrencyChanged();
    void					onSwitchedWorlds(class WorldData* i_world);
	void					onWorldLoaded();
	
	// Private member (not serialized)
	
	pvztime_t				m_slideTimeStart;
	pvztime_t				m_slideTimeDuration;
	KeyBankSlidingState		m_slidingState;
	KeyBankSlidingState		m_queuedSlidingState;
	
    bool                    m_bShow;
};

#endif
