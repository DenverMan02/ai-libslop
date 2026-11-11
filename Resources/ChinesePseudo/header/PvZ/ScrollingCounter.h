//
//  ScrollingCounter.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ScrollingCounter_h
#define PlantsVersusZombies2_ScrollingCounter_h

#include "Core.h"

class ScrollingCounter
{
public:
	ScrollingCounter()
	: m_textColor(Color::Black)
	, m_currentValue(0)
	, m_targetValue(0)
	, m_direction(0)
	, m_scrollStart(PVZ_EOT())
	, m_scrollEnd(PVZ_EOT())
    , m_spacing(0)
    , m_x(0)
    , m_y(0)
    , m_width(0)
    , m_height(0)
    , m_increment(0)
	{
	}

	int GetDisplayValue();
	void SetFont(PrimeTypeface* i_font, int i_spacingOverride = -1);
	void SetInitialValue(int i_value);
	void SetValue(int i_value);
	void SetTextColor(const Color& i_color);
	void Draw(Graphics* i_g);
	void SetRect(int i_x, int i_y, int i_width, int i_height);

private:
	void calculateDigits(int number, std::vector<int>& o_digits);
	void nextScroll();

	PrimeTypeface* m_font;
	Color m_textColor;

	int m_currentValue;
	int m_targetValue;
	std::vector<int> m_digits;
	std::vector<int> m_nextDigits;
	int m_direction;
	pvztime_t m_scrollStart;
	pvztime_t m_scrollEnd;
    int m_spacing;
    int m_increment;

    int m_x;
    int m_y;
    int m_width;
    int m_height;
};

#endif
