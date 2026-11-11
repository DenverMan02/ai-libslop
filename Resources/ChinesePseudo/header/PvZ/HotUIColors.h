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

#ifndef __PlantsVersusZombies2__HotUIColors__
#define __PlantsVersusZombies2__HotUIColors__

#include <cstddef>
#include <string>

#include "Color.h"
#include "ObjectTypeDescriptor.h"
#include "RtDb.h"
#include "RtObject.h"

class HotUIColor : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(HotUIColor, ObjectTypeDescriptor, RtClass);
    
	HotUIColor()
	{
        ColorValue = Sexy::Color::White;
	}
    
    Sexy::Color ColorValue;

public:
    Sexy::Color&  GetColor();
    
};

class HotUIColorAlias : public ObjectTypeDescriptor
{
public:
    RT_CLASS_DEFINE(HotUIColorAlias, ObjectTypeDescriptor, RtClass);
    
	HotUIColorAlias()
	{
        Color = "";
	}
    
    std::string Color;
};

class HotUIColor_Dictionary
{
public:
    static const void SetDefaultColor(const std::string& i_name);
    static const Sexy::Color& GetColor(const std::string& i_name);
};





#endif
