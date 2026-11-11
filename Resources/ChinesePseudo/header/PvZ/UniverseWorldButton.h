//
//  UniverseWorldButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 1/16/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_UniverseWorldButton_h
#define PlantsVersusZombies2_UniverseWorldButton_h

#include "core.h"
#include "WorldMapEventAlert.h"
#include "GameEventMgr.h"

enum ButtonFlags
{
	PVZ_BEGIN_FLAG_ENUM(BUTTONFLAG_),

	// PRESSED
	//	- It's pressed in
	PVZ_FLAG(BUTTONFLAG_PRESSED),

	// UNLOCKED
	//	- It's not grayscale (different animation/art is used)
	PVZ_FLAG(BUTTONFLAG_UNLOCKED),
	
	// COMING_SOON
	//	- It's coming soon (different animation/art is used)
	PVZ_FLAG(BUTTONFLAG_COMING_SOON),
	
	// REVEALED
	//	- It's not using a dotted outline (different animation/art is used)
	PVZ_FLAG(BUTTONFLAG_REVEALED),

	// SELECTED
	//	- It's selected, as in, the current world we're in (different animation/art is used)
	PVZ_FLAG(BUTTONFLAG_SELECTED),

	// UNLOCKABLE
	//	- It can be unlocked
	PVZ_FLAG(BUTTONFLAG_UNLOCKABLE),
	
	// UNIVERSE_BUTTON
	//  - It is a button on the universe map
	PVZ_FLAG(BUTTONFLAG_UNIVERSE),
	
	PVZ_END_FLAG_ENUM(BUTTONFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ButtonFlags);

class PopAnimRig;

class UniverseWorldButton: public Sexy::ButtonWidget
{

public:

	UniverseWorldButton(const int i_buttonID = 0, ButtonListener* i_listener = NULL);
	virtual ~UniverseWorldButton();
	
	void						Init(Sexy::Rect i_hitRect, const std::string& i_worldName);
	virtual void				Draw(Sexy::Graphics* i_g);
	virtual void				Update();

	void						SetPressed(const bool i_isPressed);
	void						SetUnlocked(const bool i_isUnlocked);
	void						SetIsComingSoon(const bool i_isComingSoon);
	void						SetIsRevealed(const bool i_isRevealed);
	void						SetIsSelected(const bool i_isSelected);
	void						SetIsUnlockable(const bool i_isUnlockable);
	void						SetIsUniverseButton(const bool i_isUniverseButton);
    void						SetWorldMapEventAlert(WorldMapEventAlert* i_worldMapEventAlert, Rect i_parentDrawRect = Rect(0,0,0,0));
    void						RemoveWorldMapEventAlert();

	void						PlayOnPressAudio();
	void						PlayOnReleaseAudio();
	
	inline const bool			IsPressed() const;
	inline const bool			IsUnlocked() const;
	inline const bool			IsComingSoon() const;
	inline const bool			IsRevealed() const;
	inline const bool			IsSelected() const;
	inline const bool			IsUnlockable() const;
	inline const bool			IsUniverseButton() const;
	inline const bool			IsMouseOver(const int i_mouseX, const int i_mouseY) const;
    inline const bool			HasEventAlert() const;
	inline const Sexy::Rect&	GetHitRect() const;

	inline void					SetUniverseIconOffset(const Sexy::Point i_offset);
	inline const Sexy::Point&	GetUniverseIconOffset() const;
	
	inline void					SetWorldID(const int i_worldID);
	inline const int			GetWorldID() const;
    inline WorldMapEventAlert*	GetWorldMapEventAlert();

	inline void					SetHitRect(const Rect& i_rect);

	inline const Sexy::Point&	GetStartPoint() const;

	bool						NeedPlayUnlockAnim();
	bool						NeedPlayRevealAnim();

	void						SetPlayUnlockAnim(bool i_play);
	void						SetPlayRevealAnim(bool i_play);

    inline void					SetHideDetails(const bool i_isHiding);
    inline bool					IsHidingDetails() const;
    inline void					SetDetailsAlpha(int i_alpha);
    inline void					SetScaleFactor(float i_scaleFactor);
    inline void					SetAlpha(int i_alpha);
    inline void					GrayOut(int i_brightness);
    inline void					Brighten();
    inline void					SetIsDangerRoom(bool i_dangerRoom);
    inline bool 				IsDangerRoom();

    std::string                 GetWorldName() { return m_worldName; }

private:
	
	void					syncIdleAnimation();

	void					onTouchedInAnimStopped(const std::string& i_animLabel);
	void					onTouchedOutAnimStopped(const std::string& i_animLabel);
    void					onYetiRemoved();
    void					onUniverseMapOpened();
	void					onWorldMapSwitchedWorlds(class WorldData* i_world);

    void					drawUniverseButton(Graphics* i_g, Image* i_buttonImage);
    void					drawCompletionIcon(Graphics* i_g, const Sexy::Rect& i_starBankRect);
    void					drawUniverseLock(Graphics* i_g, SexyVector2 i_position, float i_scale, float i_colorFade);
    void					drawWorldDetails(Graphics* i_g);
    void					drawPreviewButton(Graphics* i_g, Color i_fadeColor);
    void					drawCompletionStatus(Graphics* i_g, Color i_fadeColor);
    
	Sexy::Rect				m_hitRect;
	ButtonFlags				m_buttonFlags;
	int						m_worldID;
    std::string             m_worldName;
	Image*					m_buttonUp;
	Image*					m_buttonDown;
	Image*					m_buttonDisabled;
    WorldMapEventAlert*		m_worldMapEventAlert;
	Sexy::Point				m_universeOffset;
	SexyString				m_worldNameForDisplay;
	
	// Training Room
	SexyString				m_dangerRoomRecordLevel;

	pvztime_t				m_selectionChangeTime;
	
	std::string				m_audioOnPress;
	std::string				m_audioOnRelease;

	Sexy::Point				m_startPoint;
	bool					m_needPlayUnlock;
	bool					m_needPlayReveal;
    
    bool					m_hideDetails;
    int						m_detailsAlpha;
    float					m_scaleFactor;
    int						m_alpha;
    bool					m_dimmed;
    int						m_brightness;
    bool					m_isDangerRoom;
};

inline const bool UniverseWorldButton::IsPressed() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_PRESSED);
}

inline const bool UniverseWorldButton::IsUnlocked() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_UNLOCKED);
}

inline const bool UniverseWorldButton::IsComingSoon() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_COMING_SOON);
}

inline const bool UniverseWorldButton::IsRevealed() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_REVEALED);
}

inline const bool UniverseWorldButton::IsSelected() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_SELECTED);
}

inline const bool UniverseWorldButton::IsUnlockable() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_UNLOCKABLE);
}

inline const bool UniverseWorldButton::IsUniverseButton() const
{
	return TestFlag(m_buttonFlags, BUTTONFLAG_UNIVERSE);
}

inline const bool UniverseWorldButton::IsMouseOver(const int i_mouseX, const int i_mouseY) const
{
	return m_hitRect.Contains(i_mouseX, i_mouseY);
}

inline const bool UniverseWorldButton::HasEventAlert() const
{
	if (m_worldMapEventAlert)
    {
        return true;
    }

    return false;
}

inline const Sexy::Rect& UniverseWorldButton::GetHitRect() const
{
	return m_hitRect;
}

inline void	UniverseWorldButton::SetUniverseIconOffset(const Sexy::Point i_offset)
{
	m_universeOffset = i_offset;
}

inline const Sexy::Point& UniverseWorldButton::GetUniverseIconOffset() const
{
	return m_universeOffset;
}

inline void UniverseWorldButton::SetWorldID(const int i_worldID)
{
	m_worldID = i_worldID;
}

inline const int UniverseWorldButton::GetWorldID() const
{
	return m_worldID;
}

inline WorldMapEventAlert* UniverseWorldButton::GetWorldMapEventAlert()
{
	return m_worldMapEventAlert;
}

inline void UniverseWorldButton::SetHitRect(const Rect& i_rect)
{
	m_hitRect = i_rect;
}

inline const Sexy::Point& UniverseWorldButton::GetStartPoint() const
{
	return m_startPoint;
}

inline void UniverseWorldButton::SetHideDetails(const bool i_isHiding)
{
    m_hideDetails = i_isHiding;
}

inline bool UniverseWorldButton::IsHidingDetails() const
{
    return m_hideDetails;
}

inline void UniverseWorldButton::SetDetailsAlpha(int i_alpha)
{
    m_detailsAlpha = i_alpha;
}

inline void UniverseWorldButton::SetScaleFactor(float i_scaleFactor)
{
    m_scaleFactor = i_scaleFactor;
}

inline void UniverseWorldButton::SetAlpha(int i_alpha)
{
    m_alpha = i_alpha;
}

inline void UniverseWorldButton::GrayOut(int i_brightness)
{
    m_dimmed = true;
    m_brightness = i_brightness;
}

inline void UniverseWorldButton::Brighten()
{
    m_dimmed = false;
    m_brightness = 255;
}

inline void UniverseWorldButton::SetIsDangerRoom(bool i_dangerRoom)
{
	m_isDangerRoom = i_dangerRoom;
}

inline bool UniverseWorldButton::IsDangerRoom()
{
	return m_isDangerRoom;
}

#endif
