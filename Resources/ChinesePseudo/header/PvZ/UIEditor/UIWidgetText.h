//
//  UIWidgetImage.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIWidgetText_h_
#define _UIWidgetText_h_

#include "Widget.h"
#include "TodCommon.h"
#include "PrimeText_PotentialTypeface.h"

class UIWidgetText : public Sexy::Widget
{
public:
	enum
	{
		Color_Text = 0,
	};
public:
	//UIWidgetText(const SexyString& string, Sexy::PrimeTypeface* font, const Color& color, DrawStringJustification justification);
	UIWidgetText(const SexyString& str);
	virtual~UIWidgetText();

	virtual void					Update();
	virtual void					Draw(Sexy::Graphics* i_g);

    void                                SetString(const std::string& rStr);
	void								SetString(const SexyString& str);
	const SexyString&		GetString() const { return m_text; }

	void								SetFont(Sexy::PrimeTypeface* theFont) { m_pFont = theFont; }
    void								SetFont(PrimeText_PotentialTypeface* theFont) { m_pFont = theFont->Typeface(); }

    Sexy::PrimeTypeface*            GetFont() { return m_pFont; }
    void                            SetFontIndex(int idx);  // for UIEditor
    int                             GetFontIndex();     // for UIEditor
	void								SetAlign(int val) { m_align = val; }
    int                             GetAlign() const { return m_align; }
    void                            FormatByWidth();
    void                            FormatByHeight();
    void                            SetViewRect(Rect i_rect) { m_viewRect = i_rect; }
    void                            SetOptimize(bool i_optimize) { m_optimize = i_optimize; }
    
protected:

private:
	SexyString						m_text;
	int                             m_align;
	Sexy::PrimeTypeface*			m_pFont;
    bool                            m_optimize;
    Rect                            m_viewRect;
};



#endif /* STATIC_TEXT_H_ */
