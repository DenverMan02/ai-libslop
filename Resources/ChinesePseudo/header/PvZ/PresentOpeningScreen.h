//
//  PresentOpeningScreen.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PresentOpeningScreen_h
#define PlantsVersusZombies2_PresentOpeningScreen_h

#include "PresentTable.h"
#include "TimeLine.h"

class PresentDisplayRect
{
public:
	PresentDisplayRect();
	~PresentDisplayRect();
	
	void Tap(const Point& i_location);
	
	void SetRect(const Rect& i_screenRect);
	void SetPAMScale(float i_basePAMScale);
	void SetContentsEffect(class StandaloneEffect* i_contentsEffect, float i_origScale);
	void BuildRig(class PopAnim* i_pam, const std::string& i_idleAnim, const std::string& i_openAnim);
	
	void Translate(const float i_x, const float i_y);
	
	void Update();
	bool IsDone() const;
	
	void Draw(Graphics* i_g);
	
private:
	void buildTimelines();
	
	enum PresentState
	{
		PS_Idle,
		PS_Opening,
		PS_Opened
	};
	PresentState m_state;
	
	Rect m_screenRect;
	
	class PopAnimRig* m_rig;
	std::string m_idleAnim;
	std::string m_openAnim;
	
	pvztime_t m_timeOpened;
	
	class StandaloneEffect* m_contentsEffect;
	float m_contentsEffectOrigScale;
	
	TimeLineTrack<float> m_contents_xOffset;
	TimeLineTrack<float> m_contents_yOffset;
	TimeLineTrack<float> m_contents_scale;
	
	float m_basePAMScale;
};

class PresentOpeningScreen
{
public:
	PresentOpeningScreen()
		: m_normalPAM(NULL)
		, m_shinyPAM(NULL)
		, m_basePAMScale(1.f)
		, m_firstPresentIndexDisplayed(0)
		, m_maxVisiblePresents(3)
		, m_state(POSS_WaitingForPresentsToBeOpened)
	{}
	~PresentOpeningScreen();
	
	/// Config
	
	void SetPAMs(class PopAnim* i_normalPAM, class PopAnim* i_shinyPAM);
	void SetAnimations(const std::string& i_idleAnim, const std::string& i_openAnim);
	void SetPresents(const std::vector<RtWeakPtr<const class PresentTable> >& i_presentTables, const std::vector<RtWeakPtr<const class PresentType> >& i_presentContents);
	void SetMaxVisiblePresents(int i_max);
	// SetRect
	//	- The images will be scaled to fill the entirety of the height of the rect.
	//  - The aspect ratio will remain consistent. The width is used only to clip.
	void SetRect(const Rect& i_screenRect);
	void SetPAMRenderScale(float i_scale);
	
	void Initialize();
	
	/// Runtime interaction
	
	void Tap(const Point& i_location);
	bool IsDone();

	/// Update / Render
	
	void Update();
	void Draw(Graphics* i_g);
	
private:

	enum PresentOpeningScreenState
	{
		POSS_Scrolling,
		POSS_WaitingForPresentsToBeOpened,
		POSS_Done
	};

	/// Parameters
	
	Rect m_screenRect;
	
	std::vector<RtWeakPtr<const class PresentTable> > m_presentTables;
	std::vector<RtWeakPtr<const class PresentType> > m_presentContents;
	std::string m_idleAnim;
	std::string m_openAnim;
	class PopAnim* m_normalPAM;
	class PopAnim* m_shinyPAM;
	float m_basePAMScale;
	int m_maxVisiblePresents;
	
	/// Run-time values
	
	std::vector<PresentDisplayRect*> m_presentDisplays;
	
	PresentOpeningScreenState m_state;
	float m_scrollProgress;
	
	// This tracks the present on the left of the lineup
	// We'll have up to m_maxVisiblePresents on display
	int m_firstPresentIndexDisplayed;
};

#if 0

class PresentOpeningScreen
{
public:
	PresentOpeningScreen()
		: m_normalPAM(NULL)
		, m_shinyPAM(NULL)
		, m_basePAMScale(1.f)
		, m_actualPAMRenderScale(1.f)
		, m_progress(0.f)
		, m_presentsOpened(0)
		, m_state(POSS_Idle)
	{}
	~PresentOpeningScreen();
	
	/// Config
	
	void SetPAMs(PopAnim* i_normalPAM, PopAnim* i_shinyPAM);
	void SetAnimations(const std::string& i_idleAnim, const std::string& i_openAnim);
	void SetPresents(const std::vector<RtWeakPtr<const class PresentTable> >& i_presentTables, const std::vector<RtWeakPtr<const class PresentType> >& i_presentContents);
	// SetRect
	//	- The images will be scaled to fill the entirety of the height of the rect.
	//  - The aspect ratio will remain consistent. The width is used only to clip.
	void SetRect(const Rect& i_screenRect);
	void SetPAMRenderScale(float i_scale);
	
	void Initialize();
	
	/// Runtime interaction
	
	void Tap();
	bool IsDone();

	/// Update / Render
	
	void Update();
	void Draw(Graphics* i_g);
	
private:

	enum PresentOpeningScreenState
	{
		POSS_Idle,
		POSS_Opening,
		POSS_DisplayingReward,
		POSS_Scrolling,
		POSS_Done
	};

	Rect m_screenRect;

	std::vector<RtWeakPtr<const class PresentTable> > m_presentTables;
	std::vector<RtWeakPtr<const class PresentType> > m_presentContents;
	
	PopAnim* m_normalPAM;
	PopAnim* m_shinyPAM;
	float m_basePAMScale;
	
	float m_actualPAMRenderScale;
	
	std::string m_idleAnim;
	std::string m_openAnim;
	
	std::vector<PopAnimRig*> m_rigs;
	
	PresentOpeningScreenState m_state;
	
	// Progress stores our current focus point in the line of lunchboxes
	// Each increment of 1.0 moves the row to the left one lunchbox
	float m_progress;
	// Presents opened is incremented after we've scrolled the present display to the left
	int m_presentsOpened;
};

#endif // 0

#endif
