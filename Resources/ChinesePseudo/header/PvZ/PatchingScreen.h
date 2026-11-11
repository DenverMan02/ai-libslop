//
//  PatchingScreen.h
//  PlantsVersusZombies2
//
//  Created by David Siems 3/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PATCHINGSCREEN_H__
#define __PATCHINGSCREEN_H__

#include "SexyAppFramework/Widget.h"
#include "core.h"
#include "PVZUpdater.h"

class PopAnimRig;
class PVZ2UIProgressBar;

enum PatchingState
{
    PVZ_BEGIN_ENUM(PATCHSTATE_),
    PATCHSTATE_NONE,
	PATCHSTATE_WAITING_FOR_CONFIRMATION,
    PATCHSTATE_DOWNLOADING,
    PATCHSTATE_VERIFYING,
	PATCHSTATE_PATCHING,
    PATCHSTATE_COMPLETE,
    PATCHSTATE_FAILED,
	PATCHSTATE_EXIT,
    PVZ_END_ENUM(PATCHSTATE_)
};

class ActivityIndicator
{
public:
	ActivityIndicator();
	~ActivityIndicator();
	
	void DrawActivityIndicator(Graphics* i_g);
	
	void SetScale(float i_scale);
	void SetPosition(int i_X, int i_Y);
	
private:
	void UpdateTransforms();
	
	PopAnimRig* m_loadingAnimFrontRig;
	PopAnimRig* m_loadingAnimBackRig;
	
	float m_scaling;
	int m_positionX;
	int m_positionY;
};

class PatchingScreen : public Sexy::Widget
{
public:
	PatchingScreen();
	~PatchingScreen();

	virtual void Update();
	virtual void Draw(Sexy::Graphics *i_g);	

private:
	void setState(PatchingState i_state);
	void onExit();
	void onEnter();
	void onUpdate();
	
	void DrawBackground(Graphics* i_g);
	
	void OnConfirmDownloadPermission();
	void OnRejectDownloadPermission();
	void onConfirmErrorPopup();

    PatchingState m_state;
	ActivityIndicator m_activityIndicator;
	
	PVZ2UIProgressBar* m_progressBar;
	std::string m_errorMsg;
};

#endif
