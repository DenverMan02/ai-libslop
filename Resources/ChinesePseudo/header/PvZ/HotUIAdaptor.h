//
//  HotUIAdaptor.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/22/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIAdaptor__
#define __PlantsVersusZombies2__HotUIAdaptor__

#include "RtObject.h"
#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/SliderListener.h"
#include "SexyAppFramework/Widget.h"
#include "HotUIFile.h"

class HotUIAdaptor : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::SliderListener
{
public:

	RT_CLASS_DEFINE(HotUIAdaptor, Sexy::Widget, Sexy::RtClass);

	HotUIAdaptor();
	HotUIAdaptor(HotUIWidget* parent, const std::string& fileToLoad);
	virtual ~HotUIAdaptor();
	
	void SetParentAndFile(HotUIWidget* parent, const std::string& fileToLoad);

	// Lifecycle
	void LoadWidget();
	void DeleteWidget();

	void LoadAndAddWidget();
	void RemoveAndDeleteWidget();
	
	template<class T> T* GetWidgetByName(const std::string& name)
	{
		return m_uiFile->GetWidgetByName<T>(name);
	}

	// Override for basic widgets
	bool				OnBackButtonPressed() override					{ return false; }
	
	void				Update() override;

	// Button handling events
	void				ButtonPress(int i_buttonID) override			{}
	void				ButtonDepress(int i_buttonID) override			{}

	// Slider handling events
	void				SliderVal(int i_sliderID, double i_value) override		{}
	void				SliderReleased(int i_sliderID, double i_value) override	{}
	
	void				SetVisible(bool i_visible) override;
	virtual bool		IsVisible();
	
	void SetDarkenBackground(const float i_darkenPct);
	HotUIWidget*		GetEntryPointWidget() const;
	
protected:

	// UI View Link Handling
	void				loadUIView();
	void				addLinkToUIFile(HotUIFile* i_uiFile);
	void				removeLinkToUIFile();
	bool				isUIFileLoaded() { return m_uiFile != nullptr; }

	// Handlers for UI linking
	virtual void		onLoadUIView()									{};
	virtual void		onLinkToUIViewCreated()							{};
	virtual void		onLayoutFinished()								{};

	HotUIFile*	getUIFile()	const { return m_uiFile; };
	
	// Helpers for button binding
	void bindHotUIButtonToTouchID(const std::string& i_buttonWidgetName, const int i_touchID);
	void replaceImageWidgetImage(const std::string& i_imageWidgetName, const std::string& i_newResourceID);
	void replaceImageWidgetImage(const std::string& i_imageWidgetName, ImagePtr i_image);

	// Helpers for setting various field types
	bool setLabelWidgetText(const std::string& i_labelWidgetName, const SexyString& i_newLabel);
	bool setLabelWidgetTextColor(const std::string &i_labelWidgetName, const Sexy::Color& i_textColor);
	bool setImageWidgetImage(const std::string& i_imageWidgetName, ImagePtr i_image);
	bool setImageWidgetImage(const std::string &i_imageWidgetName, const std::string& i_imageID);
	bool setWidgetVisibility(const std::string& i_widgetName, bool i_visible);
	bool setButtonWidgetImage(const std::string &i_buttonWidgetName, ImagePtr i_upImage, ImagePtr i_downImage);
	bool setButtonWidgetText(const std::string &i_buttonWidgetName, const SexyString &i_text);
	void setWidgetDisabled(const std::string &i_widgetName, bool i_disabled);

	void registerButton(const std::string& i_buttonWidgetName, const int i_touchID, bool i_startDisabled = false, bool i_startInvisible = false);

private:

	HotUIWidget*		m_parent;
	std::string			m_uiFileToLoad;
	HotUIFile*			m_uiFile;
	bool				m_isLayoutFinished;
	std::vector<std::string> m_buttonsRegistered;
};


#endif /* defined(__PlantsVersusZombies2__HotUIAdaptor__) */
