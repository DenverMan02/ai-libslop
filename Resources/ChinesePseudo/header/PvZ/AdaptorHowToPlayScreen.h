//
//  AdaptorHowToPlayScreen.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 9/25/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorHowToPlayScreen_h
#define AdaptorHowToPlayScreen_h

#include <vector>
#include <string>
#include "HotUIAdaptor.h"
#include "ObjectTypeDescriptor.h"

class HotUIButton;
class HotUIImage;
class HotUILabel;
class AdaptorCarouselDots;

struct HowToPlayScreenEntry
{
    std::string        ImageId;
    std::string        Subtitle;
    std::string        Description;
};

struct HowToPlayScreenData : public ObjectTypeDescriptor
{
    RT_CLASS_DEFINE(HowToPlayScreenData, ObjectTypeDescriptor, RtClass);
    
    std::vector<HowToPlayScreenEntry> Entries;
    int Version;
};

class HowToPlayScreen : public HotUIAdaptor
{
    RT_CLASS_DEFINE(HowToPlayScreen, HotUIAdaptor, RtClass);
public:
    virtual ~HowToPlayScreen();
    
    void ButtonDepress(int i_buttonID) override;
    void SetData(const HowToPlayScreenData& i_data);
    
    void Close();
    void SetOnCloseAction(std::function<void()> i_onClose);
    
protected:
    void onLoadUIView() override;
    void onLinkToUIViewCreated() override;
    void onLayoutFinished() override;
    
    
    bool OnBackButtonPressed() override;
    
protected:
    void RefreshButtonVisibility();
    void ShowPage(int pageNum);
    
    HotUIButton* m_prevButton = nullptr;
    HotUIButton* m_nextButton = nullptr;
    HotUIImage* m_imageWidget = nullptr;
    HotUILabel* m_descLabelWidget = nullptr;
    HotUILabel* m_subtitleLabelWidget = nullptr;
    AdaptorCarouselDots* m_carouselDots = nullptr;
    
    HowToPlayScreenData m_data;
    int m_curPage = 0;
    
    std::function<void()> m_onCloseCallback;
};

#endif
