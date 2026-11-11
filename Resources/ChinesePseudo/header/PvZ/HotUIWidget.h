//
//  HotUIWidget.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 9/10/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HotUIWidget__
#define __PlantsVersusZombies2__HotUIWidget__

#include <cstddef>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Common.h"
#include "Insets.h"
#include "PropertySheetBase.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "RtId.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TodDebug.h"
#include "Widget.h"
#include "WidgetContainer.h"
#include <cstdlib>
#include "TimeMgr.h"

class HotUIWidget;
class HotUIWidgetProperties;
namespace Sexy {
class Graphics;
class ModalFlags;
}  // namespace Sexy

typedef RtWeakPtr<class HotUIWidget> HotUIWidgetPtr;
typedef RtWeakPtr<class HotUIWidgetProperties> HotUIWidgetPropertiesPtr;
typedef RtWeakPtr<class HotUIComponent> HotUIComponentPtr;
typedef RtWeakPtr<class HotUIComponentProperties> HotUIComponentPropertiesPtr;
typedef std::map<std::string, std::string> HotUIStringMap;

enum DynamicSizeType
{
	DYNAMIC_SIZE_POINTS,			// Value is in points, will be scaled to fit the screen
	DYNAMIC_SIZE_PERCENT,			// Value is percentage of parent widget width.
	DYNAMIC_SIZE_CONTENT_SIZE,		// Value calculated from content
	DYNAMIC_SIZE_IMAGE_WIDTH,		// Value calculated from image width
	DYNAMIC_SIZE_IMAGE_HEIGHT,		// Value calculated from image height
	DYNAMIC_SIZE_PIXELS,			// Value is in pixels, never scaled. 2 pixels will look SMALL on iPad3 and large on iPad2. Only really used if we want hairline padding...
};

struct DynamicSizeData
{
	DynamicSizeData()
	{
		StringValue = "0.0";
		Type = DYNAMIC_SIZE_POINTS;
		Value = 0.0f;
	}

	// Serialized (Front facing value)
	std::string			StringValue;

	// Not-Serialized (Data that is filled out from the parced StringValue)
	DynamicSizeType		Type;
	float				Value;

	const std::string& GetData()
	{
		return StringValue;
	}

	void SetData(const std::string& i_input)
	{
		std::string lowercaseInput = StringToLower(i_input);

		// Ensure our data is saved out in lowercase, consistancy...
		StringValue = lowercaseInput;

		// Check for content_size
		if (lowercaseInput.find("content_size") != std::string::npos)
		{
			Type = DYNAMIC_SIZE_CONTENT_SIZE;
			Value = 0.0f;
		}
		// Check for image width
		else if (lowercaseInput.find("image_width") != std::string::npos)
		{
			Type = DYNAMIC_SIZE_IMAGE_WIDTH;
			Value = 0.0f;
		}
		// Check for image height
		else if (lowercaseInput.find("image_height") != std::string::npos)
		{
			Type = DYNAMIC_SIZE_IMAGE_HEIGHT;
			Value = 0.0f;
		}
		// Otherwise, check for percentage, point, or pixel
		else
		{
			int signLoc = (int) lowercaseInput.find('%');
			int pixelLoc = (int) lowercaseInput.find('p');

			// Percentage based
			if (signLoc != -1)
			{
				// Percentage is clamped within 0.0 - 1.0
				std::string valueString = lowercaseInput.substr(0, signLoc);

				Type = DYNAMIC_SIZE_PERCENT;
				Value = ((float) atof(valueString.c_str())) / 100.0f;
				Value = max(0.0f, min(1.0f, Value));
			}
			else if (pixelLoc != -1)
			// Pixel based
			{
				std::string valueString = lowercaseInput.substr(0, pixelLoc);

				Type = DYNAMIC_SIZE_PIXELS;
				Value = (float) atof(valueString.c_str());
			}
			// Point based
			else
			{
				Type = DYNAMIC_SIZE_POINTS;
				Value = (float) atof(lowercaseInput.c_str());
			}
		}
	}
};

enum HotAnchorType
{
	Anchor_None,			// If specified for the ParentAnchorPoint, will use the anchor point as the normal AnchorPoint
	Anchor_TopLeft,			// Default AnchorPoint if none is specified
	Anchor_Top,				// Horizontally centered at the top
	Anchor_TopRight,
	Anchor_Left,			// Vertically centered at the left
	Anchor_Center,
	Anchor_Right,			// Vertically centered at the right
	Anchor_BottomLeft,
	Anchor_Bottom,			// Horizontally centered at the bottom
	Anchor_BottomRight,
};

struct AnchorDescriptor
{
	AnchorDescriptor()
	{
		AnchorPoint = Anchor_None;
		ParentAnchorPoint = Anchor_None;
		Parent = Sexy::RtId{0};
		ParentWidgetPtr = HotUIWidgetPtr();
	}

	// Serialized
	HotAnchorType			AnchorPoint;
	HotAnchorType			ParentAnchorPoint;
	RtId					Parent;
	DynamicSizeData			OffsetX;
	DynamicSizeData			OffsetY;

	// Not serialized
	HotUIWidgetPtr			ParentWidgetPtr;
};


struct DynamicPadding
{
	DynamicSizeData		Left;
	DynamicSizeData		Top;
	DynamicSizeData		Right;
	DynamicSizeData		Bottom;
};

enum ResizeState
{
	RS_DIRTY,
	RS_WAITING_ON_PARENT,
	RS_WAITING_ON_CONTENT,
	RS_READY,
};

enum DynamicAnchorState
{
	AS_DIRTY,		// Needs to be processed
	AS_WAITING,		// Waiting for more information
	AS_READY		// Anchor is set
};

struct DynamicResizeState
{
	DynamicResizeState()
	{
		SizeData = NULL;
		MinSizeData = NULL;
		MaxSizeData = NULL;
		State = RS_DIRTY;
		Value = NULL;
		ParentIsScreen = false;
		ScreenValue = 0;
	}

	DynamicResizeState(const DynamicSizeData* i_sizeData, const DynamicSizeData* i_minSizeData, const DynamicSizeData* i_maxSizeData, int* i_value, bool i_parentIsScreen, int i_screenValue)
	{
		SizeData = i_sizeData;
		MinSizeData = i_minSizeData;
		MaxSizeData = i_maxSizeData;
		State = RS_DIRTY;
		Value = i_value;
		ParentIsScreen = i_parentIsScreen;
		ScreenValue = i_screenValue;
	}
	
	bool UsesDynamicSizeType(const DynamicSizeType& i_type)
	{
		return i_type == SizeData->Type || i_type == MinSizeData->Type || i_type == MaxSizeData->Type;
	}
	
	const DynamicSizeData*	SizeData;
	const DynamicSizeData*	MinSizeData;
	const DynamicSizeData*	MaxSizeData;
	ResizeState				State;
	int*					Value;
	bool					ParentIsScreen;
	int						ScreenValue;
};

struct DynamicLayoutState
{
	DynamicLayoutState()
	{
		LayoutWidget = nullptr;
	}

	HotUIWidget*			LayoutWidget;
	DynamicResizeState		WidthState;
	DynamicResizeState		HeightState;
	DynamicAnchorState		AnchorState;
};

typedef Delegate2<class Graphics*, class HotUIWidget*> HotUIWidgetRenderDelegate;

class HotUIWidget: public Widget
{
public:

	RT_CLASS_DEFINE(HotUIWidget, Widget, RtClass);

	HotUIWidget()
	{
		m_layoutDirty = true;
		m_anchorDirty = false;
		m_anchorDescriptorOverriden = false;
		m_resourceGroupsLoaded = false;
		m_darkenBackgroundPct = 0.f;
	};

	virtual ~HotUIWidget()
	{
		// If we have widgets, remove them (but don't delete them, since
		// our UI system is currently doing that.

		if (mWidgets.size())
		{
			DBG_ASSERT_MSG(false, "HotUIWidget::~HotUIWidget - We shouldn't need to RemoveAllWidgets right here. This could be bad. Please ensure all widgets are removed and deleted before you hit this point. Thanks.");
			RemoveAllWidgets(false, true);
		}

		// Ensure these bad boys are gone
		UnloadResources();
	};
/*
	// Override the WidgetContainer functions we care about
*/
	void					AddWidget(Widget* i_widget) override;
	void					RemoveWidget(Widget* i_widget) override;

	void					DrawAll(ModalFlags* i_modalFlags, Graphics* i_g) override;

	void					Draw(Graphics* i_g) override; // Already translated

	void					Update() override;

	// Initialization
	void					InitializeWidget(HotUIWidgetPtr i_thisPtr, HotUIWidgetPropertiesPtr i_props);
	void					InitializeWidget(HotUIWidgetPtr i_thisPtr, HotUIWidgetPropertiesPtr i_props, const HotUIStringMap& i_stringMap);

	// Layout and Anchors
	bool					LayoutWidget();
	bool					LayoutWidgetViaContent();
	virtual bool			CalculateAnchorLocation();
	void					MarkLayoutDirty();
	void					MarkAnchorDirty();
	bool					IsDirty() const;
	const AnchorDescriptor&	GetAnchorDescriptor() const;
	void					OverrideAnchorDescriptor(const AnchorDescriptor& i_anchorDescriptor);
	void					ClearAnchorDescriptorOverride();
	void					SetAnchorChild(HotUIWidgetPtr i_child, bool i_isFromOverridenDescriptor = false);
	void					RemoveAnchorChild(HotUIWidgetPtr i_child, bool i_isFromOverridenDescriptor = false);
	void					SetAnchorParent(HotUIWidgetPtr i_parent, bool i_isFromOverridenDescriptor = false);
	void					ClearAnchorParent();
	void					FinalizeLayout();
	void					SetDarkenBackground(const float i_darkenPct);

	const DynamicPadding&	GetPadding() const;

	// Resource management
	void					LoadResources();
	void					UnloadResources();

	// Render delegate
	void					SetRenderDelegate(HotUIWidgetRenderDelegate i_renderDelegate);
	void					ClearRenderDelegate();

	// Props wrapping
	std::string				GetName() const;

	virtual void			TouchBegan( const Sexy::Touch& touch ) override;
	virtual void			OnTouchBegan( const Sexy::Touch& touch ) {}

	// Ptr and Props
	HotUIWidgetPtr					GetPtr() const
	{
		return m_thisPtr;
	};

	const HotUIWidgetProperties*	GetProps() const
	{
		return getProps();
	};

protected:

	// Overrides for widgets to use
	virtual void			onDraw(Sexy::Graphics* i_g) {};
	virtual void			onInitializeWidget() {};
	virtual void			onProcessStringReplaceMap(const HotUIStringMap& i_stringMap) {};
	virtual void			onUpdate() {};
	virtual void			onLayoutFinalized() {};

	virtual Insets			getContentBounds();
	virtual int				getImageWidthForResizeData()	{ return 0; };
	virtual int				getImageHeightForResizeData()	{ return 0; };

	// Internal helpers
	const std::string&		processStringReplaceMapHelper(const std::string& i_string, const HotUIStringMap& i_stringMap);

	// Layout and Anchors
	void					constructLayoutState();
	void					layoutAndPositionWidgetIfDirty();
	void					calculateResizeData(DynamicResizeState& io_resizeData);
	void					calculateResizeDataWithParentInsetPadding(DynamicResizeState& io_resizeData, int i_parentValue, int i_parentInsetPadding);
	void					calculateResizeDataWithContentSize(DynamicResizeState& io_resizeData, int i_contentSize);
	float					getValueForSizeData(const DynamicSizeData* i_sizeData, const int i_relativeValue);
	SexyVector2				getAnchorOffset(const WidgetContainer* i_widget, const HotAnchorType i_anchorType, const Insets& i_insets);
	SexyVector2				getExtraAnchorOffset(const AnchorDescriptor& i_anchorDescriptor, HotUIWidget* i_parentWidget, const Insets& i_parentInsets);
	HotUIWidgetPtr			getAnchorParent(bool i_forceFromPropSheet = false);
	HotUIWidget*			getParentHotUIWidget();
	bool					constructOverrideIfParentIsDifferent(HotUIWidgetPtr i_parent, bool i_isFromOverridenDescriptor = false);
	void					notifyAnchorListenersOfChange();
	
	std::vector<HotUIWidgetPtr>::iterator	getAnchorChildIterator(HotUIWidgetPtr i_child);

	// Ptr and Props
	const HotUIWidgetPropertiesPtr getPropsPtr() const
	{
		DBG_ASSERT(m_propertySheetPtr.IsValid());
		return m_propertySheetPtr;
	}

	const HotUIWidgetProperties* getProps() const
	{
		DBG_ASSERT(m_propertySheetPtr.IsValid());
		return m_propertySheetPtr.Get();
	}

	template <typename T>
	inline const T* getProps() const;

	// Serialized
	bool							m_anchorDirty;

private:

	// Serialized
	bool							m_layoutDirty;
	HotUIWidgetPtr					m_thisPtr;
	HotUIWidgetPropertiesPtr		m_propertySheetPtr;
	bool							m_anchorDescriptorOverriden;
	AnchorDescriptor				m_anchorDescriptor;
	HotUIWidgetPtr					m_anchorParent;
	std::vector<HotUIWidgetPtr>		m_anchorChildren;
	bool							m_resourceGroupsLoaded;
	std::vector<std::string>		m_resourceGroups;
	float							m_darkenBackgroundPct;

	// Non serialized
	DynamicLayoutState				m_layoutState;
	HotUIWidgetRenderDelegate		m_renderDelegate;
};

class HotUIWidgetProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(HotUIWidgetProperties, PropertySheetBase, RtClass);

	HotUIWidgetProperties()
	{
		Name = "";
		EntryPoint = false;
		IgnoreMouseInput = false;
		DarkenBackground = false;
		IgnoreClipRect = false;
		ClearClipRect = false;
		MaxWidth.Type = DYNAMIC_SIZE_PIXELS;
		MaxWidth.Value = MAXFLOAT;
		MaxHeight.Type = DYNAMIC_SIZE_PIXELS;
		MaxHeight.Value = MAXFLOAT;
	};

	virtual RtClass* GetWidgetClass() const
	{
		return HotUIWidget::StaticGetClass();
	}

	std::string								Name;
	DynamicSizeData							Width;
	DynamicSizeData							Height;
	DynamicSizeData							MinWidth;
	DynamicSizeData							MinHeight;
	DynamicSizeData							MaxWidth;
	DynamicSizeData							MaxHeight;
	DynamicPadding							Padding;
	std::vector<RtId>						Children;
	AnchorDescriptor						Anchor;
	bool									IgnoreMouseInput;
	bool									EntryPoint;
	bool									DarkenBackground;
	bool                                    IgnoreClipRect;
	bool									ClearClipRect;
	std::vector<std::string>				Resources;
};

template <typename T>
inline const T* HotUIWidget::getProps() const
{
	const HotUIWidgetProperties* props = getProps();
	const T* typedProps = props->CastChecked<const T>();
	return typedProps;
}

#endif /* defined(__PlantsVersusZombies2__HotUIWidget__) */
