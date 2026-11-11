//
//  WorldMap_StarBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_StarBank_h
#define PlantsVersusZombies2_WorldMap_StarBank_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "PVZTypes.h"
#include "GameEventMgr.h"

class WorldMap_StarBank : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_StarBank, UIWidget, RtClass);
    
    //PVZ2_CHINESE_BEGIN
    enum StarBankSlidingState
	{
		STATE_INVALID,
		STATE_IDLE,
		STATE_SLIDING_IN,
		STATE_SLIDING_OUT,
		STATE_WAITING,
	};
    //PVZ2_CHINESE_END
	
	WorldMap_StarBank();
	virtual ~WorldMap_StarBank();
    
	//PVZ2_CHINESE_START
    void SetWorldMap(std::string i_worldName);
	//PVZ2_CHINESE_END
    
    void WaitForTutorialClick()
	{
		m_clicked = false;
	}
	bool WasClickedForTutorial()
	{
		return m_clicked;
	}
	
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
    virtual void			SlideIn();
	virtual void			SlideOut();
    
protected:
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
	OVERRIDE_STATE_UPDATE(WidgetState, Ready)

	// Protected Interface (Inheritable)

	virtual void			initLoadingResourcesGroupList() override;
    virtual void			syncStarCurrency();

	// Protected Members (not serialized)
	
	StarCurrency			m_starCurrency;
	
    ImagePtr				m_starImage;
	ImagePtr				m_queuedKeyImage;
	pvztime_t				m_slideTimeStart;
	pvztime_t				m_slideTimeDuration;
	StarBankSlidingState	m_slidingState;
	StarBankSlidingState	m_queuedSlidingState;

private:	

	// Private Interface
	
	void					onStarCurrencyChanged(StarCurrency i_newValue);
    void					onSwitchedWorlds(class WorldData* i_world);
	void					onWorldLoaded();
    
    //PVZ2_CHINESE_START
    void                    updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    //void                    setIsTutorial(bool i_tutorial);

    bool                    m_clicked;
    //bool                    m_isTutorial;
    //class BouncingArrow*    m_tutorialArrow;
    //std::string             m_worldName;
	//PVZ2_CHINESE_END
};


#endif
