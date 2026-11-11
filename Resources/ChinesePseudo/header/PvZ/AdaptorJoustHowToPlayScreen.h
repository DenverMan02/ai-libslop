//
//  AdaptorJoustHowToPlayScreen.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 9/25/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustHowToPlayScreen_h
#define AdaptorJoustHowToPlayScreen_h

#include <vector>
#include <string>
#include "HotUIAdaptor.h"
#include "ObjectTypeDescriptor.h"

class HotUIButton;
class HotUIImage;
class HotUILabel;
class AdaptorCarouselDots;

struct JoustHowToPlayScreenEntry
{
	std::string		ImageId;
	std::string		Description;
};

struct JoustHowToPlayScreenData : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(JoustHowToPlayScreenData, ObjectTypeDescriptor, RtClass);
	
	std::vector<JoustHowToPlayScreenEntry> Entries;
	int Version;
};

class AdaptorJoustHowToPlayScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustHowToPlayScreen, HotUIAdaptor, RtClass);
public:
	virtual ~AdaptorJoustHowToPlayScreen();
	
	void SetData(const JoustHowToPlayScreenData& i_data);
	
	void Close();
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
	void ButtonDepress(int i_buttonID) override;

	bool OnBackButtonPressed() override;
	
private:
	void RefreshButtonVisibility();
	void ShowPage(int pageNum);
	
	HotUIButton* m_prevButton = nullptr;
	HotUIButton* m_nextButton = nullptr;
	HotUIImage* m_imageWidget = nullptr;
	HotUILabel* m_descLabelWidget = nullptr;
	HotUILabel* m_stepNumberLabelWidget = nullptr;
	AdaptorCarouselDots* m_carouselDots = nullptr;
	
	JoustHowToPlayScreenData m_data;
	int m_curPage = 0;
};

#endif
