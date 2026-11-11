//
//  HotUIImageBorder.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIImageBorder__
#define __PlantsVersusZombies2__HotUIImageBorder__

#include <string>

#include "HotUIImage.h"
#include "HotUIWidget.h"
#include "Image.h"
#include "RtDb.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

typedef RtWeakPtr<class HotUIImage> HotUIImageBorderPtr;
typedef RtWeakPtr<class HotUIImageProperties> HotUIImageBorderPropertiesPtr;

class HotUIImageBorder: public HotUIImage
{
public:

	RT_CLASS_DEFINE(HotUIImageBorder, HotUIImage, RtClass);
	
	HotUIImageBorder()
	{}
	
	virtual ~HotUIImageBorder()
	{}

	void SetBorderImage(ImagePtr i_image);

protected:

	// Widget initialization
	void			onInitializeWidget() override;
	void			onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	
	// Widget drawing
	void			onDraw(Graphics* i_g) override;
	
private:

	// Serialized
	
	// Not serialized
	std::string				m_processedBorderImageName;
	ImagePtr				m_borderImage;
};

class HotUIImageBorderProperties : public HotUIImageProperties
{
public:
	RT_CLASS_DEFINE(HotUIImageBorderProperties, HotUIImageProperties, RtClass);

	HotUIImageBorderProperties()
	{}

	RtClass* GetWidgetClass() const override
	{	
		return HotUIImageBorder::StaticGetClass();
	}
	
	UIImageType			BorderDrawType;
	UIImageDrawStyle	BorderDrawStyle;
	std::string			BorderImage;
	DynamicPadding		BorderInsets;
};

#endif /* defined(__PlantsVersusZombies2__HotUIImageBorder__) */
