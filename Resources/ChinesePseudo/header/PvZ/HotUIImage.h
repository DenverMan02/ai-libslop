//
//  HotUIImage.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIImage__
#define __PlantsVersusZombies2__HotUIImage__

#include <string>
#include <vector>

#include "HotUIWidget.h"
#include "Image.h"
#include "Insets.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"

namespace Sexy {
class Graphics;
}  // namespace Sexy

typedef RtWeakPtr<class HotUIImage> HotUIImagePtr;
typedef RtWeakPtr<class HotUIImageProperties> HotUIImagePropertiesPtr;

enum UIImageType
{
//TODO: flip horizontal instead of mirror
//flip vert.
	UIIMAGE_TYPE_NORMAL,				// Image is drawn normally
	UIIMAGE_TYPE_MIRROR,				// Image is drawn mirrored
	UIIMAGE_TYPE_VERTICAL_MIRROR,		// Image is drawn mirrored vertically
	UIIMAGE_TYPE_TILED,					// Image is drawn, tiled
	UIIMAGE_TYPE_9SLICE,				// Image is drawn as a 9 slice (corner images, stretched middle and sides)
	UIIMAGE_TYPE_3SLICE_HORIZONTAL,		// Image is drawn as a 3 slice (corner images, stretched middle)
	UIIMAGE_TYPE_3SLICE_VERTICAL,		// Image is drawn as a 3 slice (corner images, stretched middle)
};

// Think about doing bitflags or... something better
enum UIImageDrawStyle
{
	UIIMAGE_DRAW_STYLE_NORMAL,			// Image is drawn normally, no stretching, can go in or out of bounds
	UIIMAGE_DRAW_STYLE_STRETCHED,		// Image is drawn to fill the specified width/height		(HotUIAnim: Uses set animation to calculate scale)
	UIIMAGE_DRAW_STYLE_SCALE_OVERRIDE,	// Image is drawn to the ScaleOverride size					(HotUIAnim: Supported)
	UIIMAGE_DRAW_STYLE_STRETCHED_MAINTAIN_ASPECT_RATIO_X,	// Image is drawn to fill the specified width/height maintain image aspect ratio based on width	(HotUIAnim: Supported)
	UIIMAGE_DRAW_STYLE_STRETCHED_MAINTAIN_ASPECT_RATIO_Y,	// Image is drawn to fill the specified width/height maintain image aspect ratio based on height	(HotUIAnim: Supported)
	UIIMAGE_DRAW_STYLE_STRETCHED_MAINTAIN_ASPECT_RATIO_X_BOTTOM, // As above but bottom-anchored
	UIIMAGE_DRAW_STYLE_STRETCHED_MAINTAIN_ASPECT_RATIO_BOTH
};

struct UIImageDrawInfo
{
	UIImageDrawInfo(ImagePtr i_image, UIImageType i_drawType, UIImageDrawStyle i_drawStyle, const Insets& i_insets)
	{
		DrawImage = i_image;
		DrawImageList = nullptr;
		DrawType = i_drawType;
		DrawStyle = i_drawStyle;
		DrawInsets = i_insets;
		DrawOffset = Rect(i_insets.mLeft, i_insets.mTop, -(i_insets.mRight + i_insets.mLeft), -(i_insets.mBottom + i_insets.mTop));
		DrawRotation = 0;
	}
	UIImageDrawInfo(ImagePtr i_image, UIImageType i_drawType, UIImageDrawStyle i_drawStyle, const Insets& i_insets, float i_rotation, float i_rotationCenterX, float i_rotationCenterY)
	{
		DrawImage = i_image;
		DrawImageList = nullptr;
		DrawType = i_drawType;
		DrawStyle = i_drawStyle;
		DrawInsets = i_insets;
		DrawOffset = Rect(i_insets.mLeft, i_insets.mTop, -(i_insets.mRight + i_insets.mLeft), -(i_insets.mBottom + i_insets.mTop));
		DrawRotation = i_rotation;
		DrawRotationCenterX = i_rotationCenterX;
		DrawRotationCenterY = i_rotationCenterY;
	}
	UIImageDrawInfo(std::vector<ImagePtr>& i_imageList, UIImageType i_drawType, UIImageDrawStyle i_drawStyle, const Insets& i_insets)
	{
		DrawImage = ImagePtr();
		DrawImageList = &i_imageList;
		DrawType = i_drawType;
		DrawStyle = i_drawStyle;
		DrawInsets = i_insets;
		DrawOffset = Rect(i_insets.mLeft, i_insets.mTop, -(i_insets.mRight + i_insets.mLeft), -(i_insets.mBottom + i_insets.mTop));
		DrawRotation = 0;
	}
	ImagePtr				DrawImage;
	std::vector<ImagePtr>*	DrawImageList;
	UIImageType				DrawType;
	UIImageDrawStyle		DrawStyle;
	Insets					DrawInsets;
	Rect					DrawOffset;
	float					DrawRotation;
	float					DrawRotationCenterX;
	float					DrawRotationCenterY;
};

class HotUIImage: public HotUIWidget
{
public:

	RT_CLASS_DEFINE(HotUIImage, HotUIWidget, RtClass);

	HotUIImage() :
	m_hasOverrideClipRect(false),
	m_drawGrayscale(false)
	{}

	virtual ~HotUIImage()
	{}

	void SetImage(ImagePtr i_image);
	
	void SetImageScale(float i_scale) { m_imageScale = i_scale; }
	float GetImageScale() { return m_imageScale; }
	
	void SetImageColor(Color i_color) { m_imageColor = i_color; }
	Color GetImageColor() { return m_imageColor; }
	
	void SetImageGrayscale(bool i_grayscale) { m_drawGrayscale = i_grayscale; }
	bool GetImageGrayscale() { return m_drawGrayscale; }

	void SetOverrideClipRect(const Rect& i_rect);
	void ClearOverrideClipRect();
	Rect GetClipRect() const override;

protected:

	// Widget initialization
	void	onInitializeWidget() override;
	void	onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) override;

	// Widget drawing
	void	onDraw(Graphics* i_g) override;
	void 	drawInternal(Graphics* i_g);

	// Function to pick the drawing type to be used based upon draw info
	void	drawImageHelper(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);

	// Drawing types
	void	drawImage(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	drawImageMirrored(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	drawImageVerticalMirrored(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	drawImageTiled(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	draw9SliceImage(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	draw3SliceHorizontalImage(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);
	void	draw3SliceVerticalImage(Graphics* i_g, const UIImageDrawInfo& i_drawInfo);

	// Widget layout
	Insets	getContentBounds() override;
	int		getImageWidthForResizeData() override;
	int		getImageHeightForResizeData() override;
	
	// Helper
	void	getImageAspectRatioStretchedData(UIImageDrawStyle i_drawStyle, ImagePtr i_image, float &io_width, float &io_height, float &io_x, float &io_y);
	void	preparePositionalDataForDraw(const UIImageDrawInfo& i_drawInfo, float &io_width, float &io_height, float &io_x, float &io_y);
	
private:

	// Serialized
	bool	m_hasOverrideClipRect;
	Rect	m_overrideClipRect;

	// Not serialized
	std::string					m_processedImageName;
	std::vector<std::string>	m_processedImageNameList;
	ImagePtr					m_image;
	std::vector<ImagePtr>		m_imageList;
	Color						m_imageColor;
	bool						m_drawGrayscale;
	
	// This value only works in stretched mode
	float						m_imageScale;
};

class HotUIImageProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUIImageProperties, HotUIWidgetProperties, RtClass);

	HotUIImageProperties()
	{
		DrawType = UIIMAGE_TYPE_NORMAL;
		DrawStyle = UIIMAGE_DRAW_STYLE_NORMAL;
		Rotation = 0;
		RotationCenterX = 0;
		RotationCenterY = 0;
        ImageScale = 1.0f;
	};

	RtClass* GetWidgetClass() const override
	{
		return HotUIImage::StaticGetClass();
	}

	UIImageType					DrawType;
	UIImageDrawStyle			DrawStyle;
	std::string					Image;
	std::vector<std::string>	ImageList;
	DynamicPadding				ImageInsets;
	
	float						Rotation;
	float						RotationCenterX;
	float						RotationCenterY;
    float                       ImageScale;
};

#endif /* defined(__PlantsVersusZombies2__HotUIImage__) */
