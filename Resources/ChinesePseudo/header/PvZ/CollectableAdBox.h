/*
 * CollectableAdBox.h
 *
 *  Created on: 2018-11-29
 *      Author: Administrator
 */

#ifndef COLLECTABLEADBOX_H_
#define COLLECTABLEADBOX_H_

#include "Collectable.h"
#include "CollectableType.h"
#include "PVZTypes.h"
#include "RtObject.h"

STATE_ENUM_CHILD_BEGIN(BoxState, CollectableState)
BoxState_INIT,
BoxState_RIGHT,
BoxState_LEFT,
BoxState_UP,
BoxState_DOWN,
STATE_ENUM_END(BoxState);

class CollectableAdBox : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableAdBox, Collectable, RtClass);

	CollectableAdBox();

	void SetState(BoxState i_state);
	void InitNodes(const SexyVector3& i_start);

protected:
    bool onTouchEvent(const Sexy::Touch& i_touch) override;
    virtual void onUpdate() override;
    bool CanChangeColorState() override;
private:
    // Box State Machine
    DECLARE_STATE_FUNCTIONS(CollectableState, INIT);
	DECLARE_STATE_FUNCTIONS(CollectableState, RIGHT);
	DECLARE_STATE_FUNCTIONS(CollectableState, LEFT);
	DECLARE_STATE_FUNCTIONS(CollectableState, UP);
	DECLARE_STATE_FUNCTIONS(CollectableState, DOWN);

	std::vector<Point> m_nodes;
};


#endif /* COLLECTABLEADBOX_H_ */
