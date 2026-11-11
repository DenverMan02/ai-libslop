/*
 * RichManScreenState.h
 *
 *  Created on: 2019-12-19
 *      Author: Administrator
 */

#ifndef RICHMANSCREENSTATE_H_
#define RICHMANSCREENSTATE_H_

#include "PVZGameState.h"

class RichManScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(RichManScreenState, PVZHotUIGameState, RtClass);

protected:
	RtClass* getTopHudControllerClass() override;
	RtClass* getHotUIAdaptorClass() override;
};


#endif /* RICHMANSCREENSTATE_H_ */
