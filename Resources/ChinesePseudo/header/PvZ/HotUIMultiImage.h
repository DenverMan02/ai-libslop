//
//  HotUIMultiImage.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/18/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIMultiImage__
#define __PlantsVersusZombies2__HotUIMultiImage__

#include <string>
#include <vector>

#include "HotUIImage.h"
#include "HotUIWidget.h"
#include "Image.h"
#include "Insets.h"
#include "RtDb.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

typedef RtWeakPtr<class HotUIImage> HotUIMultiImagePtr;
typedef RtWeakPtr<class HotUIImageProperties> HotUIMultiImagePropertiesPtr;

class HotUIMultiImage: public HotUIImage
{
public:

	RT_CLASS_DEFINE(HotUIMultiImage, HotUIImage, RtClass);
	
	HotUIMultiImage()
	{
		
	};
	
	virtual ~HotUIMultiImage()
	{

	};

protected:

	// Widget initialization
	void				onInitializeWidget() override;
	void				onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;
	
	// Widget drawing
	void				onDraw(Graphics* i_g) override;

	// Widget layout
	Insets				getContentBounds() override;
	int					getImageWidthForResizeData() override;
	int					getImageHeightForResizeData() override;
	
private:
	
	// Serialized
	
	// Not serialized
	std::vector<std::string>	m_processedImageNameList;
	std::vector<ImagePtr>		m_imageList;
};

class HotUIMultiImageProperties : public HotUIImageProperties
{
public:
	RT_CLASS_DEFINE(HotUIMultiImageProperties, HotUIImageProperties, RtClass);

	HotUIMultiImageProperties()
	{}

	RtClass* GetWidgetClass() const override
	{	
		return HotUIMultiImage::StaticGetClass();
	}
	
	std::vector<std::string>	ImageList;
};


#endif /* defined(__PlantsVersusZombies2__HotUIMultiImage__) */
