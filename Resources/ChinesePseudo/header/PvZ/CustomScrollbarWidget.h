#ifndef __CUSTOMSCROLLBARWIDGET_H__
#define __CUSTOMSCROLLBARWIDGET_H__

#include "SexyAppFramework/ScrollbarWidget.h"

class LawnApp;

namespace Sexy
{
	class ScrollbarWidget;
	class ScrollbuttonWidget;
	class ScrollListener;
}

class CustomScrollbarWidget : public ScrollbarWidget
{
public:
	CustomScrollbarWidget(int i_id, ScrollListener *i_scrollListener);
	virtual ~CustomScrollbarWidget();

	virtual void ResizeScrollbar(int i_x, int i_y, int i_width, int i_height);
	virtual void ClampValue();
	virtual int GetTrackSize();

	void RemoveScrollButtons();

//	virtual void			ResizeScrollbar(int i_x, int i_y, int i_width, int i_height);
};

#endif //__CUSTOMSCROLLBARWIDGET_H__
