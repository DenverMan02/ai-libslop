//
//  PrimeText_PotentialTypeface.h
//  PlantsVersusZombies2
//
//  Json data wrapper which defines a potential instance of a typeface.
//  These lazily construct PrimeTypefaces as accessed to cache used entries for speed.
//
//  Created by Jason Emery on 10/28/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PrimeText_PotentialTypeface__
#define __PlantsVersusZombies2__PrimeText_PotentialTypeface__

#include <cstddef>
#include <string>

#include "Color.h"
#include "ObjectTypeDescriptor.h"
#include "PrimeText_Effects_Game.h"
#include "RtDb.h"
#include "RtObject.h"

namespace Sexy {
class PrimeTypeface;
}  // namespace Sexy

typedef RtWeakPtr<class PrimeText_PotentialTypeface> PrimeText_PotentialTypefacePtr;

class PrimeText_PotentialTypeface : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(PrimeText_PotentialTypeface, ObjectTypeDescriptor, RtClass);
    
	PrimeText_PotentialTypeface()
	{
        Font = "";
        Size = 0;
        Color = Color::White;
        Effect = TypefaceEffect::FONT_EFFECT_NONE;
        EffectColor = Color::White;
        Smooth = false;
        FontIfShrunk = "";
        
        m_Typeface = NULL;
	}
    
    std::string Font;
    int Size;
	Sexy::Color::PredefinedColor Color;
    
    TypefaceEffect Effect;      // May want to convert to a string at a future date
	Sexy::Color::PredefinedColor EffectColor;
    
    bool Smooth;
    
    std::string FontIfShrunk;

public:
    PrimeTypeface*  Typeface();
    
private:
    PrimeTypeface*  m_Typeface;

};

class PrimeText_PotentialTypeface_Alias : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(PrimeText_PotentialTypeface_Alias, ObjectTypeDescriptor, RtClass);
    
	PrimeText_PotentialTypeface_Alias()
	{
        Font = "";
	}
    
    std::string Font;
};

class PrimeText_PotentialTypefaceDictionary
{
public:
    static void SetDefaultTypeface(const std::string& i_name);
    static PrimeTypeface* GetTypeface(const std::string& i_name);
    static PrimeText_PotentialTypeface* GetPotentialTypeface(const std::string& i_name);

    // TODO: Move this to a more general location
	static Sexy::Color& GetColor(const std::string& i_name);
};





#endif
