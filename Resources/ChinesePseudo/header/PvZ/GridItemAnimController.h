/*
 * GridItemAnimController.h
 *
 *  Created on: 2022-8-22
 *      Author: zhousen
 */

#ifndef GRIDITEMANIMCONTROLLER_H_
#define GRIDITEMANIMCONTROLLER_H_

#include "BoardEntity.h"
#include "EntityComponent.h"
#include "SexyAppFramework/SexyVector.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "BoostTracker.h"

STATE_ENUM_BASE_BEGIN(GridItemAnimControllerState)
	GRID_ITEM_STATE_INIT,
	GRID_ITEM_STATE_START,
	GRID_ITEM_STATE_LOOP,
	GRID_ITEM_STATE_END,
	GRID_ITEM_STATE_DESTROY,
	GRID_ITEM_STATE_CUSTOM_BEGIN,
STATE_ENUM_END(GridItemAnimControllerState);


// GridItemAnimControllerProps
class GridItemAnimControllerProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemAnimControllerProps, GridItemAnimationProps, RtClass);

	GridItemAnimControllerProps();

	std::string StartAnim;
	std::string LoopAnim;
	std::string EndAnim;
	pvztime_t Duration;// live duration.
};

// GridItemAnimController
class GridItemAnimController : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemAnimController, GridItemAnimation, RtClass);

	GridItemAnimController();
	virtual ~GridItemAnimController();

	void onGridItemInitialize() override;
	void onUpdate() override;

	void SetDuration(pvztime_t duration);

protected:
	virtual void PlayStartAnim();
	virtual void PlayLoopAnim();
	virtual void PlayEndAnim();

	virtual void OnStartAnimDone(const std::string& name);
	virtual void OnEndAnimDone(const std::string& name);

protected:
	int m_state;
	pvztime_t m_lifeEndTime;
	pvztime_t m_duration;
};

#endif /* GRIDITEMANIMCONTROLLER_H_ */
