//
//  UIWidget.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  A base UIWidget that stores location and size data and can be attached
//  to other UIWidgets as well as recieve mouse/touch input. This object does
//  not draw itself to the screen, unless you call its debug draw functions
//  in order to see the area on the screen the widget takes up. 
//  
//  While it can be used on its own, this class is meant to be inherited by other
//  fleshed-out classes that act as a UIWidget.
//

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "core.h"
#include "RtObject.h"
#include "GameObject.h"
#include "StateMachine.h"
#include "UIWidgetSheet.h"
#include "UIWidgetAnchorEnums.h"
#include "Renderable.h"
#include "RenderQueue.h"

STATE_ENUM_BASE_BEGIN(WidgetState)
	WS_Loading,					// Loading assets
	WS_Initializing,			// Assets are loaded, setting up the widget
	WS_Ready,					// Widget is in a ready state (waiting to be pressed, enabled, off cooldown, etc)
	WS_NotReady,				// Widget is in a not-ready state (disabled, cooldown, etc)
	WS_Pressed,					// Widget is currently pressed with input (finger, mouse, etc)
	WS_Paused,					// Widget is in a paused state, basically frozen in time and non-interactable
STATE_ENUM_END(WidgetState)

enum UIWidgetFlags
{
	PVZ_BEGIN_FLAG_ENUM(UIFLAG_),

	// VISIBLE
	//  - Set when our widget is visible (if not visible, this ALSO makes us not clickable)
	PVZ_FLAG(UIFLAG_VISIBLE),

	// MANUAL_DRAW
	//  - Set our widget to require a manual draw call instead of automatically being drawn
	//	via adding all widgets to the drawing queue.
	PVZ_FLAG(UIFLAG_MANUAL_DRAW),
	
	// CLICKABLE
	//	- Set when our widget can be clickable and accepts mouse input
	PVZ_FLAG(UIFLAG_CLICKABLE),

	// IGNORE_PARENT_VISIBLE
	//  - Set when our widget ignore's the visibility state of its parent for click and draw features
	PVZ_FLAG(UIFLAG_IGNORE_PARENT_VISIBLE),
	
	PVZ_END_FLAG_ENUM(UIFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(UIWidgetFlags);

class UIWidgetSheet;

class UIWidget : public GameObject, public Renderable
{

public:
	RT_CLASS_DEFINE(UIWidget, GameObject, RtClass);	
	
	UIWidget();
	virtual ~UIWidget();
	
	// Public Interface (Inheritable)

	virtual void							Draw(Graphics* i_g) override;
	virtual void							AddToRenderQueue(class RenderQueue* i_queue);
	virtual void							OnMouseMove(const int i_mouseX, const int i_mouseY)		{}
	virtual void							OnMouseDown(const int i_mouseX, const int i_mouseY)		{}
	virtual void							OnMouseUp(const int i_mouseX, const int i_mouseY)		{}
	virtual bool							OnTouch(const Sexy::Touch& i_touch)							{ return false; }
	virtual bool							IsMouseOver(const int i_mouseX, const int i_mouseY);
	virtual const Sexy::Point				GetCenterPointOnScreen();

	// Public Interface (Core)
	
	void									Update();
	void									SetParentWidget(UIWidget* i_parentPtr);
	void									SetPropertySheet(const RtName i_sheetName);
	const Sexy::Rect						GetDrawRect();
//PVZ2_CHINESE_START
	virtual const Sexy::Rect				GetHitRect();
//PVZ2_CHINESE_END
	void									DetachFromParent();
	void									AddChildWidget(UIWidget* i_childPtr);
	void									RemoveChildWidget(UIWidget* i_childPtr);
	RtId									GetChildId(const int i_childIndex);
	void									DestroyChildren();

	void									StartLoad();
	bool									IsLoadComplete();
	void									CompleteLoad();
	void									PrepForLoading();
	void									UnloadResources();
	void									TryUnlock(const std::string& i_levelName);
	
	inline const int						GetChildCount();
	
	inline void								SetAtlasImageData(Image* i_atlasImage, const Sexy::Rect i_atlasSrcRect);
	inline Image*							GetAtlasImage();
	inline const Sexy::Rect&				GetAtlasSrcRect();
	
	const AnchorType						GetAnchorType();
	inline void								SetAnchorType(const AnchorType i_anchorType);

	const AnchorType						GetParentAnchorType();
	inline void								SetParentAnchorType(const AnchorType i_anchorType);
	
	inline const int						GetWidth();
	inline void								SetWidth(const int i_width);

	inline const int						GetHeight();
	inline void								SetHeight(const int i_height);
	
	const SexyVector2&						GetPositionOffset();
	void									SetPositionOffset(const SexyVector2 i_positionOffset);
	void									ClearPositionOffsetOverride();
    
	virtual bool							CanSetVisible() { return true; }
	void									SetVisible(const bool i_isVisible);
	const bool								IsVisible();

	inline void								SetIgnoreParentVisibility(const bool i_ignore);
	inline const bool						GetIgnoreParentVisibility();
	
	inline void								SetClickable(const bool i_isClickable);
	inline const bool						IsClickable();

	inline void								SetManuallyDrawn(const bool i_isManuallyDrawn);
	inline const bool						IsManuallyDrawn();
	
	inline void								SetInputPriority(const uint8 i_inputPriority);
	const uint8								GetInputPriority();

	inline void								SetMouseDownPos(const Sexy::Point& i_mousePoint);
	inline const Sexy::Point&				GetMouseDownPos();
	
	inline void								SetIsPressed(bool i_isPressed);
	inline bool								IsPressed();
	
	inline void								SetIsDragging(bool i_isDragging);
	inline bool								IsDragging();

	inline const Sexy::Rect&				GetRect();
	inline const RtWeakPtr<UIWidgetSheet>	GetPropertySheetPtr();
	inline RtName							GetPropertySheetPtrName();
	
	// Creates a new Widget by specifying both the widget class and property sheet to use and dumps it into the UI table
	static UIWidget*						CreateWidget(const std::string& i_widgetName, const RtName i_sheetName, bool  i_isVisible = true);
	// Creates a new Widget based upon the property sheet to use and dumps it into the UI table
	static UIWidget*						CreateWidget(const RtName i_sheetName, bool i_isVisible = true);

	// Prepares the UI table for a new UI layout (purges previous one)
	static void								ResetUI();
	// Get a pointer to a widget that is using the specified sheet name, if it is currently active
	static RtWeakPtr<UIWidget>				GetWidgetPtrBySheetName(const std::string& i_name);
	static UIWidget*						GetWidgetBySheetName(const std::string& i_name);
    static std::vector<UIWidget*>           GetWidgetGroupBySheetName(const std::string& i_name);
	// Checks all widgets in the UI and returns a widget that the mouse is currently over
	static UIWidget*						GetMouseOverWidget(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority = 200);
	// Processes the MouseDown for any widget that the mouse is over. Returns true if one was found, otherwise false.
	static bool								ProcessedMouseDown(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority = 200);
	// Processes the MouseUp for any widget that the mouse is over. Returns true if one was found, otherwise false.
	static bool								ProcessedMouseUp(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority = 200);
	// Processes the MouseMove for any widget that the mouse is over.
	static void								ProcessedMouseMove(const int i_mouseX, const int i_mouseY, const uint8 i_maxInputPriority = 200);
	static bool								ProcessedTouch(const Sexy::Touch& i_touch);
	// Updates all active UI widgets
	static void								UpdateUI();
	// Returns whether or not all the UI widgets are fully loaded
	static bool								IsLoadCompleteForAllWidgets();
	static void								GetLoadedResourceGroupsForAllWidgets(std::vector<std::string> &o_resourceGroups);
	// Adds all UI widgets to the render queue
	static void								AddToRenderQueueForAllWidgets(class RenderQueue* i_queue);
	// Gets the WidgetPtr of a widget based upon its RtId, if it exists
	static UIWidget*						GetUIWidgetByRtId(const RtId i_id);
	// Takes a PSD image offset and converts it to UI coordinate space
	static void								ConvertPSDImageOffsetToUISpace(int& io_offsetX, int& io_offsetY);
	// Takes a PSD image offset and converts it to UI coordinate space
	static void								ConvertPSDImageOffsetToUISpace(int& io_offsetX, int& io_offsetY, const float i_sourceArtSize);
	// Takes a rect and populates its data from the atlas information in the specified image
	static void								SetAtlasImageRectToRect(Sexy::Rect& io_rect, ImagePtr i_atlasedImage);
	
    static void                             ShowWidgets(bool bShow, ...);
    
    // Provides global scale value that is given to the UI
    static float							GetDeviceUIWidgetScaleValue();
    
    static void 							OnConsumedTouch(std::function<void()> i_func){ m_cosumedTouch = i_func; }

protected:

	// Protected Interface (Inheritable)

	virtual void							initLoadingResourcesGroupList();
	virtual void							addToLoadingResourcesGroupList(const std::string& i_groupName);
	virtual void                            onLoadComplete() {};
	virtual void							onUpdate()														{};
	virtual void							setState(const WidgetState i_newState);
	virtual void							onVisibleStateChange(bool i_visible) {}
    virtual void                            onClickableStateChanged() {};
	void									calculatePosition();
	virtual void							onDestroy() override;

	DECLARE_STATE_FUNCTIONS(WidgetState, Loading);
	DECLARE_STATE_FUNCTIONS(WidgetState, Initializing);
	DECLARE_STATE_FUNCTIONS(WidgetState, Ready);
	DECLARE_STATE_FUNCTIONS(WidgetState, NotReady);
	DECLARE_STATE_FUNCTIONS(WidgetState, Pressed);
	DECLARE_STATE_FUNCTIONS(WidgetState, Paused);
	
	// Protected Interface (Core)

	void									drawPSDImage(Graphics* i_g, const ImagePtr i_image, const int i_offsetX, const int i_offsetY);
	void									drawPSDImage(Graphics* i_g, const ImagePtr i_image, const int i_offsetX, const int i_offsetY, const int i_width, const int i_height);
	void									drawPSDImageTiled(Graphics* i_g, const ImagePtr i_image, const int i_offsetX, const int i_offsetY, const int i_width, const int i_height);
	void									updateStateMachine();
	void									setStateHelper(const StateDefinition<WidgetState>& i_newStateDefinition);
	WidgetState								getState() const;
    bool									isInState(uint32 i_state) const;
	void									translateToWidgetPosition(Graphics* i_g);
	inline const pvztime_t					getStateEnterTime();
	inline void								setStateEnterTime(const pvztime_t i_newTime);

	RtWeakPtr<UIWidget>						getParentPtr() const { return m_parentPtr; }
    
protected:

	int32									getWidgetStateSerialization();
	void									setWidgetStateSerialization(int32 i_state);

	// Private Interface
	void									initializeFromPropertySheet();
	const SexyVector2						getAnchorOffset(UIWidget* i_widgetPtr, const AnchorType i_anchorType);

	inline void								setRect(const Sexy::Rect i_rect);
	
	void									checkUnlocked();

	// Private Members (serialized)
	RtName									m_propertySheetName;
	RtWeakPtr<UIWidgetSheet>				m_propertySheetPtr;
	Sexy::Rect								m_boundingRect;
	AnchorType								m_overrideSelfAnchor;			// overrides prop sheet
	AnchorType								m_overrideParentAnchor;			// overrides prop sheet
	RtWeakPtr<UIWidget>						m_parentPtr;
	std::vector<RtId>						m_childIdList;
	UIWidgetFlags							m_flags;
	pvztime_t								m_stateEnterTime;
	SexyVector2								m_overridePositionOffset;		// overrides prop sheet
	SexyVector2								m_scaledPositionOffset;			// cached off scaled virtual coordinates
	bool									m_positionOffsetOverriden;
	uint8									m_overrideInputPriority;		// overrides prop sheet
	bool									m_inputPriorityOverriden;
	std::vector<std::string>				m_loadingResourcesList;
	ImagePtr								m_atlasImage;
	Sexy::Rect								m_atlasSrcRect;
    
	// Private Member (not serialized)
	StateMachine<WidgetState>				m_stateMachine;
	Sexy::Point								m_mouseDownPos;
	bool									m_mouseDown;
	bool									m_dragging;

	static RtWeakPtr<UIWidget>				m_mouseFocusWidget;
	bool 									m_unlocked;
	static std::function<void()> 			m_cosumedTouch;

};

inline const Sexy::Rect& UIWidget::GetRect()
{
	// Calculate the bounding rect and return it.
	calculatePosition();
	return m_boundingRect;
}

inline void	UIWidget::setRect(const Sexy::Rect i_rect)
{
	m_boundingRect = i_rect;
}

inline void	UIWidget::SetAnchorType(const AnchorType i_anchorType)
{
	m_overrideSelfAnchor = i_anchorType;
	calculatePosition();
}

inline void	UIWidget::SetParentAnchorType(const AnchorType i_anchorType)
{
	m_overrideParentAnchor = i_anchorType;
	calculatePosition();
}

inline const int UIWidget::GetWidth()
{
	return m_boundingRect.mWidth;
}

inline void UIWidget::SetWidth(const int i_width)
{
	m_boundingRect.mWidth = i_width;
}

inline const int UIWidget::GetHeight()
{
	return m_boundingRect.mHeight;
}

inline void UIWidget::SetHeight(const int i_height)
{
	m_boundingRect.mHeight = i_height;
}

inline void	UIWidget::SetIgnoreParentVisibility(const bool i_ignore)
{
	SetFlag(m_flags, UIFLAG_IGNORE_PARENT_VISIBLE, i_ignore);
}

inline const bool UIWidget::GetIgnoreParentVisibility()
{
	return TestFlag(m_flags, UIFLAG_IGNORE_PARENT_VISIBLE);
}

inline void	UIWidget::SetClickable(const bool i_isClickable)
{
	SetFlag(m_flags, UIFLAG_CLICKABLE, i_isClickable);
    onClickableStateChanged();
}

inline const bool UIWidget::IsClickable()
{
	return TestFlag(m_flags, UIFLAG_CLICKABLE);
}

inline void	UIWidget::SetManuallyDrawn(const bool i_isManuallyDrawn)
{
	SetFlag(m_flags, UIFLAG_MANUAL_DRAW, i_isManuallyDrawn);
}

inline const bool UIWidget::IsManuallyDrawn()
{
	return TestFlag(m_flags, UIFLAG_MANUAL_DRAW);
}

inline void UIWidget::SetInputPriority(const uint8 i_inputPriority)
{
	m_inputPriorityOverriden = true;
	m_overrideInputPriority = i_inputPriority;
}

inline const RtWeakPtr<UIWidgetSheet> UIWidget::GetPropertySheetPtr()
{
	return m_propertySheetPtr;
}

inline RtName UIWidget::GetPropertySheetPtrName()
{
	return m_propertySheetName;
}

inline void UIWidget::SetAtlasImageData(Image* i_atlasImage, const Sexy::Rect i_atlasSrcRect)
{
	m_atlasImage = i_atlasImage != NULL ? ImagePtr(i_atlasImage->GetRtId()) : ImagePtr();
	m_atlasSrcRect = i_atlasSrcRect;
}

inline Image* UIWidget::GetAtlasImage()
{
	return m_atlasImage;
}

inline const Sexy::Rect& UIWidget::GetAtlasSrcRect()
{
	return m_atlasSrcRect;
}

inline const int UIWidget::GetChildCount()
{
	return static_cast<int>(m_childIdList.size());
}

inline const pvztime_t UIWidget::getStateEnterTime()
{
	return m_stateEnterTime;
}

inline void UIWidget::setStateEnterTime(const pvztime_t i_newTime)
{
	m_stateEnterTime = i_newTime;
}

inline void UIWidget::SetMouseDownPos(const Sexy::Point& i_mousePoint)
{
	m_mouseDownPos = i_mousePoint;
}
									  
inline const Sexy::Point& UIWidget::GetMouseDownPos()
{
	return m_mouseDownPos;
}

inline void UIWidget::SetIsPressed(bool i_isPressed)
{
	m_mouseDown = i_isPressed;
}

inline bool	UIWidget::IsPressed()
{
	return m_mouseDown;
}

inline void UIWidget::SetIsDragging(bool i_isDragging)
{
	m_dragging = i_isDragging;
}

inline bool UIWidget::IsDragging()
{
	return m_dragging;
}

typedef RtWeakPtr<UIWidget> UIWidgetPtr;

#endif //__UIWIDGET_H__
