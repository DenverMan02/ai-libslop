/*
 * UIPVZ1ModeCredits.h
 *
 *  Created on: 2021-8-2
 *      Author: zhousen
 */

#ifndef UIPVZ1MODECREDITS_H_
#define UIPVZ1MODECREDITS_H_

#include "PVZDB.h"
#include "Singleton.h"
#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "core.h"
#include "PVZTypes.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "UISingletonDialog.h"
#include "UIUtil.h"

enum {
	PVZ1Mode_Credits_Play = 1000,
	PVZ1Mode_Credits_BackToMain,
};

///
/// PVZ1 Mode Credits Screen
///
class UIPVZ1ModeCredits : public UISingletonDialog<UIPVZ1ModeCredits>
{
public:
	UIPVZ1ModeCredits();
	~UIPVZ1ModeCredits();

	virtual bool OnCreate() override;
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual std::string GetLayoutName() override { return "UIPVZ1ModeCredits"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView();
	void PlayEndFunc();

private:
};


#endif /* UIPVZ1MODECREDITS_H_ */
