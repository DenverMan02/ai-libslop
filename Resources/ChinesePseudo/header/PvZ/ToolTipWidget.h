#ifndef __TOOLTIPWIDGET_H__
#define __TOOLTIPWIDGET_H__

#include "SexyAppFramework/Common.h"

typedef std::vector<SexyString> SexyStringStdVector;

class ToolTipWidget
{
public:	
	SexyString m_title;
	SexyString m_label;
	SexyString m_warningText;

    // TODO : these really shouldn't be ScreenResInts ..
	ScreenResInt m_x;        
	ScreenResInt m_y;

	int m_width;
	int m_height;
	bool m_visible;
	bool m_center;
	int m_minLeft;
	int m_maxBottom;
	int m_getsLinesWidth;
	int m_warningFlashCounter;

	ToolTipWidget();
    void Draw(Sexy::Graphics* g);
	void SetLabel(const SexyString &i_label);
	void SetTitle(const SexyString &i_title);
	void SetWarningText(const SexyString &i_warningText);
	void CalculateSize();
	void GetLines(SexyStringStdVector &lines);
	void FlashWarning();
	void Update();
};

#endif //__TOOLTIPWIDGET_H__
