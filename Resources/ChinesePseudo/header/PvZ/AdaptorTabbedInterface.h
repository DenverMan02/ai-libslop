//
//  AdaptorTabbedInterface.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 1/22/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorTabbedInterface_h
#define AdaptorTabbedInterface_h

#include "RtObject.h"
#include "HotUIAdaptor.h"
#include "Image.h"

class AdaptorTabbedInterface : public HotUIAdaptor
{
public:
    RT_CLASS_DEFINE(AdaptorTabbedInterface, HotUIAdaptor, Sexy::RtClass);
    
    AdaptorTabbedInterface();
    virtual ~AdaptorTabbedInterface();
	
	void ButtonDepress(int i_buttonID) override;
    bool OnBackButtonPressed() override;
    
    void Close();
	void SetOnCloseAction(std::function<void()> i_onClose);
    
protected:
    void onLinkToUIViewCreated() override;
//    void onLoadUIView() override; <- Should be overwritten by subclasses to set correct file.
	
private:
	void setup();
	
	void showTab(int i_tabID);
    void updateTabImages(int i_activeTab);

    void ShowTips();// zhousen
	
	std::string m_currentTab;
    
	std::vector<ImagePtr> m_inactiveTabImages;
	std::vector<ImagePtr> m_activeTabImages;
    
    std::vector<class HotUIButton*> m_tabs;
	
	std::function<void()> m_onCloseCallback;

	class AdaptorPerkLibraryTips* m_perkLibraryTips;// zhousen for tips ui
};

class AdaptorJoustTabbedInterface : public AdaptorTabbedInterface
{
	RT_CLASS_DEFINE(AdaptorJoustTabbedInterface, AdaptorTabbedInterface, Sexy::RtClass);
protected:
	void onLoadUIView() override;
};

class AdaptorPerkLibraryTabbedDialog : public AdaptorTabbedInterface
{
	RT_CLASS_DEFINE(AdaptorPerkLibraryTabbedDialog, AdaptorTabbedInterface, Sexy::RtClass);
    AdaptorPerkLibraryTabbedDialog();
    virtual ~AdaptorPerkLibraryTabbedDialog();
    
protected:
	void onLoadUIView() override;
};

class AdaptorPerkLibraryTips : public HotUIAdaptor
{
public:
    RT_CLASS_DEFINE(AdaptorPerkLibraryTips, HotUIAdaptor, Sexy::RtClass);

    AdaptorPerkLibraryTips();
    virtual ~AdaptorPerkLibraryTips();

	void ButtonDepress(int i_buttonID) override;

protected:
	void onLoadUIView() override;
    void onLinkToUIViewCreated() override;

};

#endif /* AdaptorTabbedInterface_h */
