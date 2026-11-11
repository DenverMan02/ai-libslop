//
//  ZombieCamel.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIECAMELTOUCH_H__
#define __ZOMBIECAMELTOUCH_H__

#include "ZombieCamel.h"
#include "CamelMinigame.h"
#include "StandaloneEffect.h"

STATE_ENUM_CHILD_BEGIN(ZombieCamelTouchState, ZombieCamelState)
	ZS_CAMELTOUCH_WaitingToRise,
	ZS_CAMELTOUCH_RisingFromGround,
	ZS_CAMELTOUCH_Stunned,
STATE_ENUM_END(ZombieCamelTouchState);

class ZombieCamelTouch : public ZombieCamel
{
public:
	RT_CLASS_DEFINE(ZombieCamelTouch, ZombieCamel, RtClass);
	
	// Public Interface (Inheritable)

	virtual void			BecomeHeadZombie(ZombieTypePtr i_camelType) override;
	
	// Public Interface (Core)

	void					SetIsTutorialCamel(bool i_isTutorial);
	void					RiseFromGround(const SexyVector3& i_fromLocation, float i_riseDelay);
	void					FlipCard(bool i_displayCard);
	void					TriggerMatched();
	bool 					HasBeenMatched();
	
	void					SetCardType(CardType i_index);
	CardType				GetCardType();
    bool					ShouldDrawShadow() const override;

protected:

	// Protected Interface (Inheritable)

	DECLARE_STATE_FUNCTIONS(ZombieState, WaitingToRise);
	DECLARE_STATE_FUNCTIONS(ZombieState, RisingFromGround);
	DECLARE_STATE_FUNCTIONS(ZombieState, Stunned);

	virtual void			registerForEvents() override;
	virtual void			unregisterForEvents() override;
	virtual void			onZombieInitialize() override;
	virtual void			onDraw(class Sexy::Graphics* i_g) override;
	virtual void			onDrawShadow(class Sexy::Graphics* i_g) override;
	virtual void			onPlaceOnBoard() override;
	virtual void			onPlaceOnStreet() override;

	virtual bool			onTouchEvent(const Sexy::Touch& i_touch);
	
	// Protected Interface (Core)
	
	void					onCardMatched();
	void					onMatchedAnimationFinished(StandaloneEffect* i_effect);
	std::string				getSegmentTypeName(ZombieCamelSegmentType i_type) override;
	void					hideUnderLayers();
	void					prepDeath();
	void					showPanelSymbol(CardType i_index);

private:

	enum CardState
	{
		PVZ_BEGIN_ENUM(STATE_CARD_),
		STATE_CARD_NORMAL,
		STATE_CARD_FLIPPED,
		STATE_CARD_MATCH,
		STATE_CARD_NO_MATCH,
		PVZ_END_ENUM(STATE_CARD_),
	};

	// Private Members (serialized)
	
	CardType				m_cardType;
	CardState				m_cardState;
	pvztime_t				m_riseFromGroundDelay;
	pvztime_t				m_shadowFadeInStartTime;
	bool					m_isTutorialCamel;
	StandaloneEffectPtr		m_signHolder;
	bool					m_hasBeenMatched;
	
	bool					m_isStreetZombie;
	
};

#endif
