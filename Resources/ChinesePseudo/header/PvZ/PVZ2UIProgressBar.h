//
//  PVZ2UIProgressBar.h
//  PlantsVersusZombies2
//
//  Created by aschneider on 5/2/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UIProgressBar_h
#define PlantsVersusZombies2_PVZ2UIProgressBar_h

#include "Precompile.h"

class PopAnimRig;

struct ProgressBarDoodad
{
	ProgressBarDoodad() {}
	ProgressBarDoodad(float i_percent, int i_positionX, int i_positionY)
	{
		m_activatePercentage = i_percent;
		m_positionX = i_positionX;
		m_positionY = i_positionY;
		
		m_loaderDoodadAnimRig = NULL;
		m_wasActivated = false;
	}
	PopAnimRig* m_loaderDoodadAnimRig;
	float m_activatePercentage;
	int m_positionX;
	int m_positionY;
	bool m_wasActivated;
};

#define NUM_PROGRESS_BAR_DOODADS 4
class PVZ2UIProgressBar : public Sexy::Widget
{
public:
	PVZ2UIProgressBar();
	virtual ~PVZ2UIProgressBar();
	
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	void ResetAnimation();
	
	void SetProgressPercentage(float i_percent);
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	bool IsCompleted() { return m_completed && IsFinished(); }
	
private:
	bool IsFinished() { return m_currentPercentage >= 1.0f; }
	void onAnimComplete(const std::string& i_animLabel);
    
    float m_nstep;
	float m_currentPercentage;
	float m_targetPercentage;
	float m_widgetScale;
	bool m_completed;
	PopAnimRig* m_sodRollAnimRig;
	ProgressBarDoodad m_doodads[NUM_PROGRESS_BAR_DOODADS];
};

#endif
