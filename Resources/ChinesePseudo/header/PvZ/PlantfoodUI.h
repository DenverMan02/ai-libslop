//
//  PlantfoodUI.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/24/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  UI for the plantfood tool.

#ifndef __PLANTFOODUI_H__
#define __PLANTFOODUI_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "Effect_BouncingArrow.h"
#include "MagentoService.h"	//PVZ2_CHINESE_START
#include "Effect_PopAnim.h"

class Collectable;

class PlantfoodUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(PlantfoodUI, UIWidget, RtClass);
	
	PlantfoodUI();
	virtual ~PlantfoodUI();
	
	// Public Interface (Inheritable)
	
	virtual void					Draw(Graphics* i_g) override;
	virtual bool					OnTouch(const Sexy::Touch& i_touch) override;
	virtual bool					IsMouseOver(const int i_mouseX, const int i_mouseY) override;
	virtual const Sexy::Point		GetCenterPointOnScreen() override;

	void							SetForceShowPlus(bool i_show);
	
	Rect							CalcPlusButtonRect();
	Rect							CalcConfirmationRect();
	
	void							SetFreePlantfoodAddition(bool i_free);
	inline void						SetMaxPurchasesAllowed(const int8 i_maxPurchasesOnLevel);
    
    void                            SetBuyTutorialArrow(Effect_BouncingArrow* arrow);
	void								AddPlantFood(int num);

    void                            ShowForbiddenIcon(bool show);
    void                            SetTouchDelegate(Sexy::Delegate0wRet<bool> delegate);
    
    void							DoIntroPlantFood();
    int                         GetBuyCount();
    int                         GetPrice();
protected:
	
	// Protected Interface (Inheritable)
	
	virtual void					registerForEvents() override;
	virtual void					unregisterForEvents() override;
	
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState, Pressed);
	
	virtual void					onCursorDestroyed(class BaseCursor* i_cursor);
	virtual void					onPlantfoodCountChanged(int i_newCount);
    virtual void                    onCollectableCollectionFinished(Collectable* i_bankedCollectable);
    virtual void                    onPlantFoodGrabbed(Collectable* i_grabbedCollectable);

	void 							onGameplayEnded();
	
	virtual void					onUpdate() override;
	virtual void					initLoadingResourcesGroupList() override;

private:
	// Private Interface
	bool							handleTouch(const Sexy::Touch& i_touch);
	void							cancelTouch();
	
	void							doPlantfoodPurchase();
    
    void                            SetBuyTutorialArrowOffsetY(int offsetY);
    void                            OnServerGemCallBack(const bool& i_Success);
    void                            OnServerGemCallBack_Android_Convert_Ios(const bool& i_Success);

    void							DoPurchasePlantFood(int i_result);
	void							AddPlantFood_impl();
	
	// Private Members (serialized)
	int								m_purchasesLeft;
	int								m_count;
	bool 							m_levelEnded;
	bool							m_showPlusButton;
    int                             m_collecting;
    pvztime_t                       m_collectStartTime;
	
	// Private Members (not serialized)
	bool							m_freePlantfoodAddition;
	bool							m_plusButtonPrimed;
	bool							m_showingCoinStore;
	Sexy::TouchID 					m_touchIdent;
    
    Effect_BouncingArrow*           m_tutorialArrow;
    SexyVector2                     m_tutorialArrowBase;
    //PVZ2_CHINESE_START
    MagentoProductPropsPtr          m_plantfoodPropsPtr;
    int                             m_plantfoodTimers;
    int                             m_plantfoodBuyCount = 0;
	// cached for playing animation
	int								m_iAddNum;
	float								m_fTimerAdd;
    bool                            m_showForbid;
    Sexy::Delegate0wRet<bool>       m_delegate;
    bool							m_isSoccerGame;
	bool							m_isNostalgicGame;
    RtWeakPtr<Effect_PopAnim> 		m_soccerWarningEffect;
	//PVZ2_CHINESE_END
};

inline void	PlantfoodUI::SetMaxPurchasesAllowed(const int8 i_maxPurchasesOnLevel)
{
	m_purchasesLeft = i_maxPurchasesOnLevel;
}

namespace Message
{
	void PlantfoodPurchased(const std::string& name,int i_amont,int costFreeGems);
    void PlantfoodButtonPrimed();
}

#endif //__PLANTFOODUI_H__
