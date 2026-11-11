//
//  BusyAnimationManager.h
//  PlantsVersusZombies2
//
//  Created by Alex Stajos on 5/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BusyAnimationManager__
#define __PlantsVersusZombies2__BusyAnimationManager__

#include "TimeLine.h"

class BusyAnimationManager : public Widget
{
public:
	BusyAnimationManager();
	~BusyAnimationManager();
	
	void StartBusyIcon();
	void StopBusyIcon();
	bool IsActive(){ return m_active; }
	
	// Inherited interface
	virtual void Draw(Graphics* i_g);
	virtual void DrawOverlay(Graphics* i_g);
	virtual void Update();
	virtual bool OnBackButtonPressed();

private:
	void InitializeData();
	void generateBounceTracks();
	void generateBounceTrack(TimeLineTrack<float>& i_intoTrack);
	
	class PopAnimRig* m_loadIconFront;
	class PopAnimRig* m_loadIconBack;
	
	// Each pair of tracks represents scaling in the x/y axes
	TimeLineTrack<float> m_bounceInAnim[2];
	
	pvztime_t m_stateChangeStartTime;
	int m_transitionCount;
	bool m_active;
	bool m_removeBusyIcon;
	bool m_isDataInitialized;
    bool m_bTransform;
};

#endif /* defined(__PlantsVersusZombies2__BusyAnimationManager__) */
