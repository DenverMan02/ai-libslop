/*
 * RichManScreenTopHUD.h
 *
 *  Created on: 2019-12-19
 *      Author: Administrator
 */

#ifndef RICHMANSCREENTOPHUD_H_
#define RICHMANSCREENTOPHUD_H_

#include "PVZGameStateTopHUDController.h"

class RichManScreenTopHUD : public PVZGameStateTopHUDController
{
public:
	RT_CLASS_DEFINE(RichManScreenTopHUD, PVZGameStateTopHUDController, Sexy::RtClass);

	void Open() override;
};


#endif /* RICHMANSCREENTOPHUD_H_ */
