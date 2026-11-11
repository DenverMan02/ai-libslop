//
//  PVZGameStateTopHUDController.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/28/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef PVZGameStateTopHUDController_h
#define PVZGameStateTopHUDController_h

#include "RtObject.h"
#include "Widget.h"

class PVZGameStateTopHUDController : public Sexy::Widget
{
public:
	RT_CLASS_DEFINE(PVZGameStateTopHUDController, Sexy::Widget, Sexy::RtClass);
	
	PVZGameStateTopHUDController();
	virtual ~PVZGameStateTopHUDController();
	
	virtual void Open() = 0;
	
	bool IsLoaded();

	void Update() override;
	
	void Draw(Sexy::Graphics* i_g) override;
	
	void TouchBegan( const Sexy::Touch& touch ) override;
	void TouchMoved( const Sexy::Touch& touch ) override;
	void TouchEnded( const Sexy::Touch& touch ) override;
	void TouchesCanceled() override;
	void setOffset(int offset);
protected:
	virtual bool canHandleInput() const;
	
private:
	void onHideTopHUD();
	void onShowTopHUD();
	void updateHUDVisibility();
	bool isHidden() const;
	
	bool m_loadComplete;
	int m_hideRequestCount;
	int m_fOffset;
};

namespace Message
{
	void HideTopHUD();
	void ShowTopHUD();
}

#endif /* PVZGameStateTopHUDController_h */
