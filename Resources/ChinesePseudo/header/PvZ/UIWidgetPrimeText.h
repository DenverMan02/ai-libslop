//
//  WidgetPrimeText.h
//  PlantsVersusZombies2
//
//  Reusable text widget.  Please note this is a work in progress as
//  it does not yet take its configuration through constructor variables.
//
//  Created by Jason Emery on 4/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WidgetPrimeText__
#define __PlantsVersusZombies2__WidgetPrimeText__

#include "UIWidget.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"

class UIWidgetPrimeText : public UIWidget
{
    RT_CLASS_DEFINE(UIWidgetPrimeText, UIWidget, RtClass);
	
	UIWidgetPrimeText();
	virtual ~UIWidgetPrimeText();
    
	// Public Interface (Inheritable)
    
	
	// Public Interface (Core)
    
    void SetPosition(int x, int y);
    
    // Set this Widget with a pre-generated text glyphMesh for rendering.
    void SetGlyphMesh(PrimeGlyphMesh* glyphMesh);
	
private:
    
	// Private Members (not serialized)
	
    int mX;
    int mY;
//    PrimeTypeface* mFont;
    PrimeGlyphMesh* mGlyphMesh;
    
};

#endif /* defined(__PlantsVersusZombies2__WidgetPrimeText__) */



