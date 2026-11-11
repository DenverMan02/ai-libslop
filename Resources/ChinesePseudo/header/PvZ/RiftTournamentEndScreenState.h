/*
 * RiftTournamentEndScreenState.h
 *
 *  Created on: 2020-6-16
 *      Author: Administrator
 */

#ifndef RIFTTOURNAMENTENDSCREENSTATE_H_
#define RIFTTOURNAMENTENDSCREENSTATE_H_

#include "PVZGameState.h"

class RiftTournamentEndScreenState : public PVZHotUIGameState
{
public:
	RT_CLASS_DEFINE(RiftTournamentEndScreenState, PVZHotUIGameState, RtClass);

protected:
	void onHotUILoaded(HotUIAdaptor* i_adaptor) override;

	RtClass* getTopHudControllerClass() override { return nullptr; }
	RtClass* getHotUIAdaptorClass() override;
};


#endif /* RIFTTOURNAMENTENDSCREENSTATE_H_ */
