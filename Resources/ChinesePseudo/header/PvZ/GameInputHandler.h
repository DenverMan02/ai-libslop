//
//  GameInputHandler.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GameInputHandler__
#define __PlantsVersusZombies2__GameInputHandler__

#include "RtDb.h"
#include "SexyAppBase.h"
#include "BoardEntity.h"
#include "BaseCursor.h"

// higher priority goes first
enum TouchPriority
{
	TOUCHPRIORITY_GESTURE = 0,
	TOUCHPRIORITY_GRIDITEM,
	TOUCHPRIORITY_PLANT,
	TOUCHPRIORITY_ZOMBIE,
	TOUCHPRIORITY_POWERUP,
	TOUCHPRIORITY_CURSOR,
    TOUCHPRIORITY_CURSOR_SPAWNING_PLANT,
    TOUCHPRIORITY_CURSOR_SPAWNING_PLANT_VINE,
	TOUCHPRIORITY_CACHEDCURSOR,
	TOUCHPRIORITY_UI,
    TOUCHPRIORITY_BOARD,
	TOUCHPRIORITY_COLLECTABLE,
    TOUCHPRIORITY_TUTORIAL,
	TOUCHPRIORITY_EDITOR,
};

typedef Sexy::Delegate1wRet<bool, const Sexy::Touch&> GameInputDelegate;
typedef Sexy::Delegate0 CancelInputDelegate;
typedef Sexy::Delegate3<const Sexy::Point&, int, float> GestureDelegate;
typedef Sexy::Delegate1<const Sexy::Point&> LongPressDelegate;

struct GameInputListenerInfo
{
	GameInputListenerInfo(GameInputDelegate i_touchDelegate, const int i_priority, BoardEntityPtr i_boardEntity, CancelInputDelegate i_cancelDelegate)
	{
		DBG_ASSERT(i_touchDelegate != GameInputDelegate());
		DBG_ASSERT(i_priority >= 0);

		m_touchDelegate = i_touchDelegate;
		m_cancelDelegate = i_cancelDelegate;
		m_priority = i_priority;
		m_boardEntity = i_boardEntity;
		m_renderOrder = 0;
	}
	
	bool operator<(const GameInputListenerInfo &i_rhs) const;
	bool operator==(const GameInputListenerInfo &i_rhs) const;

	GameInputDelegate m_touchDelegate;
	CancelInputDelegate m_cancelDelegate;
	int m_priority;
	BoardEntityPtr m_boardEntity;
	int m_renderOrder;
};

class GameInputHandler
{
public:
	GameInputHandler()
	{

	}
	~GameInputHandler()
	{

	}

	void RegisterTouchGameplayObject(GameInputDelegate i_touchDelegate, const int i_priority, BoardEntityPtr i_boardEntity, CancelInputDelegate i_cancelDelegate);
	void UnregisterTouchGameplayObject(void* i_touchOwner);
	void ChangePriority(void* i_touchOwner, const int i_priority);
	bool OnGameplayTouchEvent(const Sexy::Touch& i_touch);

	void RegisterGesture(GestureDelegate i_gestureDelegate);
	void UnregisterGesture(void* i_gestureOwner);
	void OnGestureEvent(Sexy::Point i_gestureLocation, int i_distanceBetweenFingersSquared, float i_scaleDelta);

	void RegisterLongPress(LongPressDelegate i_longPressDelegate);
	void UnregisterLongPress(void* i_longPressOwner);
	void OnLongPress(Sexy::Point i_location);

	// this send out a cancel to everyone except the specified ignoredDelegateOwner
	void CancelTouch(const Sexy::Touch& i_touch, void* i_ignoredDelegateOwner);
	void SendCancelDelegate();

private:
	std::vector<GameInputListenerInfo> m_gameInputListeners;
	std::vector<GestureDelegate> m_gestureListeners;
	std::vector<LongPressDelegate> m_longPressListeners;
};

#endif /* defined(__PlantsVersusZombies2__GameInputHandler__) */
