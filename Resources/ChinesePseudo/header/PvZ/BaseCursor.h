//
//  BaseCursor.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 11/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BaseCursor__
#define __PlantsVersusZombies2__BaseCursor__

#include "RtObject.h"
#include "RtDb.h"
#include "SexyAppBase.h"
#include "SexyVector.h"

class BaseCursor : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(BaseCursor, Sexy::RtObject, Sexy::RtClass) {}

	BaseCursor();
	BaseCursor(const Sexy::Touch& i_boardSpaceTouch);
	virtual ~BaseCursor();
	void DelayConstruct(const Sexy::Touch& i_boardSpaceTouch);

	void Update();
	void Draw(Sexy::Graphics* i_g);

	bool AssociatedWithTouch(const Sexy::Touch& i_touch);

	Sexy::Point GetUIWidgetPosition() const;
	Sexy::Point GetBoardPosition() const { return m_boardPosition; }
	void SetPositionFromBoardSpace(const Sexy::Point& i_boardSpacePos);

	void Destroy();
	bool IsDestroyed() const { return m_destroyed; }

	void ClearTouchIdentity() { m_touchIdent = Sexy::InvalidTouchID; }
	void SetWasCachedCursor() { m_wasCachedCursor = true; }
	bool WasCachedCursor() const { return m_wasCachedCursor; }

	bool HasMovedOutsideOriginRect() const { return m_hasMovedOutsideOriginRect; }
	void SetMovedOutsideOriginRect();

	virtual bool IsInsideOriginRect() const;

	bool IsCachedCursor() const;
    
    void SetMirrorX(bool i_mirrorX);
    bool GetMirrorX() { return m_mirrorX; }

    void SetVisible(bool i_visible) { m_visible = i_visible; }
    bool IsVisible() { return m_visible; }

    float GetScale() { return m_scale; }

protected:
	virtual bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) = 0;
	virtual void onUpdate() {}
	virtual void onDraw(Sexy::Graphics* i_g) {}
	virtual void onDestroy() {}

	void cacheOrDestroyCursor();

	void setAnimRig(class PopAnimRig* i_animRig);
	void setCursorBoardOrigin(const Sexy::Rect& i_cursorBoardOrigin);
	Sexy::Rect getCursorBoardOrigin() const { return m_cursorBoardOrigin; }
	virtual Sexy::SexyVector2 getCursorAnimOffset() const;

private:

	bool handleTouchEvent(const Sexy::Touch& i_touch);
	void updateScale();

	// both of these are in screen board space coordinates
	// that is different from game board space and still different from screen UIWidget space and screen space
	Sexy::Point m_boardPosition;
	Sexy::Rect m_cursorBoardOrigin;

    bool m_mirrorX = false;
	bool m_destroyed = false;
	bool m_wasCachedCursor = false;
	bool m_hasMovedOutsideOriginRect = false;

	class PopAnimRig* m_cursorAnimRig = nullptr;

	Sexy::TouchID m_touchIdent = Sexy::InvalidTouchID;
	bool m_visible = true;
	float m_scale = 1.0f;
};

namespace Message
{
	void CursorDestroyed(BaseCursor* cursor);
}

#endif /* defined(__PlantsVersusZombies2__BaseCursor__) */
