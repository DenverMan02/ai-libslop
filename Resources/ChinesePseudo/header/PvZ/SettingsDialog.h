//
//  SettingsDialog.h
//  PlantsVersusZombies2
//
//  Created by jsola on 4/30/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_SettingsDialog_h
#define PlantsVersusZombies2_SettingsDialog_h

#include "MainMenu.h"
#include "SliderListener.h"
#include "TimeLine.h"

/// Manages dialog panes
class SettingsDialog : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener, public Sexy::SliderListener, public Sexy::CheckboxListener
{
public:
	SettingsDialog();
	virtual ~SettingsDialog();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void CheckboxChecked(int i_id, bool i_checked);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) 		{}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) 	{}

	virtual void SliderVal(int theId, double theVal);
	virtual void SliderReleased(int theId, double theVal);

	static void SetEncryptIndex(int32 index) { s_encryptIndex = index; }
	static int32 GetEncryptIndex(){ return s_encryptIndex; }

	static void SetDisplayID(const std::string& id) { s_displayID = id; }
	static const std::string& GetDisplayID(){ return s_displayID; }

	static void SetDisplayUUID(const std::string& id) { s_displayUUID = id; }
	static const std::string& GetDisplayUUID(){ return s_displayUUID; }

	static void SetIsACheatProfile(bool i_flag) { s_isACheatProfile = i_flag; }
	static bool GetIsACheatProfile(){ return s_isACheatProfile; }

	static void SetHaveSendV202(bool i_flag) { s_haveSendV202 = i_flag; }
	static bool GetHaveSendV202(){ return s_haveSendV202; }

private:
	void scrollRight();
	void scrollLeft();

	class SettingsWidget* createButtonWidget(int i_id, const SexyString& i_label, Sexy::Image* i_arrowImage);
	class SettingsWidget* createCheckboxWidget(int i_id, const SexyString& i_label, bool i_startingState);
	class SettingsWidget* createSliderWidget(int i_id, const SexyString& i_label, float i_startingValue);

	void setupTextBoxPane(const SexyString& i_title, const SexyString& i_text, class Sexy::PrimeTypeface* i_font, const Sexy::Color& i_textColor, bool i_autoScroll = false);
	void setupDownloadPrefsPane();
	void setupSharingUsagePane();
    void setupUserIDPane();
    void setupContractUsPane();
    void setupAboutPane();
    void setupUUIDPane();
    void setupLogoutPane();
    
#ifdef HOST_ANDROID
    void setupDefineIDPane();
#endif
    void setupHelpPane();
	void setupCredits();

    void DrawDarkeningLayer(Graphics* i_g);
    
	std::vector<class SettingsDialogPane*> m_panes;

	class SettingsWidgetList* m_settingsList;
	class PVZ2UICreditsScreen* m_creditsScreen;

	TimeLineTrack<float> m_scrollTimeline;
	int m_depth;
	
	// Hacky workaround because I don't have time to care. Shipping games is rad.
	bool m_queuedSharingUsagePaneRefresh;

	static int32 s_encryptIndex;
	static std::string s_displayID;
	static std::string s_displayUUID;
	static bool s_isACheatProfile;
	static bool s_haveSendV202;
};

class SettingsDialogPane : public Sexy::Widget
{
public:
	SettingsDialogPane(SexyString i_title = _S(""));
	virtual ~SettingsDialogPane();

	void SetTitle(SexyString i_title);

	void SetContentsWidget(Widget* i_newWidget);

	virtual void Draw(Sexy::Graphics* i_g);

private:
	SexyString m_translatedTitle;

	Widget* m_contentsWidget;
};

class SettingsWidgetList : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
	SettingsWidgetList();
	virtual ~SettingsWidgetList();

	void AddSettingsWidget(class Widget* i_widget);
    void AddSettingsCustomWidget(class Widget* i_widget);

	virtual void Update();
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) 		{}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) 	{}

	void SetAutoScroll(bool i_autoScroll);

	void CancelScrollingWidgetDrag();
	void SetAllEnabled(bool i_enabled);

private:
	class PVZ2UIScrollingWidget* m_scrollingWidget;

	std::vector<class Widget*> m_widgets;

	bool m_autoScroll;

	pvztime_t m_autoScrollStartTime;
	bool m_autoScrollStarted;
	float m_autoScrollAccumulation;
};

class SettingsWidget : public Sexy::Widget
{
public:
	SettingsWidget(SexyString const & i_label);
	virtual ~SettingsWidget();

	virtual void Draw(Sexy::Graphics* i_g);

private:
	SexyString m_translatedLabel;
};

#define COMPLAIN_CLOSE_BTN (123)

class ComplainDialog
: public Sexy::Widget
, public Sexy::ButtonListener
{
public:
    
    ComplainDialog();
    
    virtual ~ComplainDialog() { RemoveAllWidgets(true, true); }
    
    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
};

class AgeTipDialog
: public Sexy::Widget
, public Sexy::ButtonListener
{
public:

	AgeTipDialog();

    virtual ~AgeTipDialog() { RemoveAllWidgets(true, true); }

    void Draw(Sexy::Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
};
#endif
