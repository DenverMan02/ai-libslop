/*
 * static_text.h
 *
 *  Created on: 2013-9-9
 *      Author: chenyc
 */

#ifndef STATIC_TEXT_H_
#define STATIC_TEXT_H_

#include "Precompile.h"

class staticText : public Sexy::Widget
{
public:
	staticText( const SexyString& string, const Rect& rc, Sexy::PrimeTypeface* font, const Color& color, DrawStringJustification justification );
	virtual~staticText();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* g);
	void setString( const SexyString& string ){strView_ = string;}

private:
	SexyString strView_;
	Rect       rcView_;
	Color      color_;
	DrawStringJustification justification_;
	Sexy::PrimeTypeface* font_;
};



#endif /* STATIC_TEXT_H_ */
