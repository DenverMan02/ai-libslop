//
//  PVZ2UICreditsScreen.h
//  PlantsVersusZombies2
//
//  Created by jsola on 5/12/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UICreditsScreen_h
#define PlantsVersusZombies2_PVZ2UICreditsScreen_h

#include "Widget.h"
#include "PVZ2UIButton.h"
#include "PrimeTextWidget.h"

enum CreditsState
{
	CREDITS_FADINGIN_OVERLAY,
	CREDITS_FADINGIN_CONTENT,
	CREDITS_DISPLAYING,
	CREDITS_FADINGOUT_CONTENT,
	CREDITS_FADINGOUT_OVERLAY,
	CREDITS_DONE,
};

class PVZ2UICreditsScreen : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PVZ2UICreditsScreen();
	virtual ~PVZ2UICreditsScreen();
	
	virtual void Update();
	virtual void DrawAll(ModalFlags* theFlags, Graphics* g);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	
	void SpawnRandomDebris(int i_count);
	void DrawSpaceDebris(Graphics* i_g);
	
	bool IsDone();
	
private:
	class PVZ2UICreditsScroller* m_credits;
	std::vector<class SpaceDebrisDrawer*> m_debris;
	
	CreditsState m_state;
	pvztime_t m_fadeStartTime;
};

class SpaceDebrisDrawer
{
public:
	SpaceDebrisDrawer(class PopAnimRig* i_popAnim, const SexyVector2& i_origin, const std::string& i_animName);
	SpaceDebrisDrawer(Sexy::Image* i_image, const SexyVector2& i_origin);
	~SpaceDebrisDrawer();
	
	void Update();
	void Draw(Graphics* i_g, float i_currScrollAmountScreen);
	
	// Lower is deeper into the screen
	float GetDrawZ();
	float GetScrollScale();
	
private:
	void initialize(const SexyVector2& i_origin);
	
	class PopAnimRig* m_rig;
	Sexy::Image* m_image;
	SexyVector2 m_screenOrigin; // Must be UI_S'ed()
	
	Color m_color;
	float m_scale;
	float m_parallaxFactor;
	float m_rotation;
	float m_rotationVelocity;
	float m_bobPhase;
};

class PVZ2UICreditsScroller : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
	RT_CLASS_DEFINE(PVZ2UICreditsScroller, Sexy::Widget, RtClass);
public:
	PVZ2UICreditsScroller();
	virtual ~PVZ2UICreditsScroller();
	
	void AddGameTitle(const SexyString& i_titleName);
	void AddTitle(const SexyString& i_titleName);
	void AddDisciplineTitle(const SexyString& i_titleName);
	void AddNameText(const SexyString& i_names);
#ifndef NDEBUG
    void AddGameTitleWithAllFonts();    //PVZ2_CHINESE add.
#endif
	void AddThankYouNoteName(const SexyString& i_person);
	void AddThankYouNoteMessage(const SexyString& i_message);
	void AddFooterImage();
	
	void AddSpacerSmall();
	void AddSpacerLarge();
	
	void AddCreditsWidget(Widget* i_widget);
	void DoWidgetLayout();

	virtual void Update();
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void Draw(Sexy::Graphics* i_g);
	
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) 		{}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) 	{}

	void CancelScrollingWidgetDrag();
	
	float GetScrollAmountScreen();
	float GetMaxScrollAmountScreen();

private:
	class Sexy::PrimeTextWidget* buildTextEntry(const SexyString& i_titleName, Sexy::PrimeTypeface* i_font, const Color& i_color, bool i_fullWidth);
    class Sexy::PrimeTextWidget* buildTextEntry(const SexyString& i_titleName, class PrimeText_PotentialTypeface* i_font, const Color& i_color, bool i_fullWidth);
    
    class Sexy::PrimeTextWidget* buildTextEntry(const SexyString& i_titleName, Sexy::Font* i_font, const Color& i_color, bool i_fullWidth);
	
	class PVZ2UIScrollingWidget* m_scrollingWidget;
	std::vector<class Widget*> m_widgets;
	
	pvztime_t m_autoScrollStartTime;
	bool m_autoScrollStarted;
	float m_autoScrollAccumulation;
};

#endif
