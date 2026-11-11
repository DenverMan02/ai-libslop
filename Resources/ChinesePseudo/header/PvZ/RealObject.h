//
//  RealObject.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/3/14.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __REALOBJECT_H__
#define __REALOBJECT_H__

#include "core.h"

#include "GameObject.h"
#include "ZombieEnums.h"
#include "Renderable.h"

enum TeamFlags
{
	PVZ_BEGIN_FLAG_ENUM(TEAM_),
	PVZ_FLAG(TEAM_PLANTS),
	PVZ_FLAG(TEAM_ZOMBIES),
	PVZ_END_FLAG_ENUM(TEAM_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(TeamFlags);
bool TeamsAreOpposing(TeamFlags i_attacker, TeamFlags i_defender);

enum RealObjectFlags
{
	PVZ_BEGIN_FLAG_ENUM(ROFLAG_),
	PVZ_FLAG(ROFLAG_UseGroundClipRect),			// Clip drawing to ground
	PVZ_FLAG(ROFLAG_DisableSnapToGround),		// Avoid all snapping to ground (use for effects)
	PVZ_FLAG(ROFLAG_Hidden),					// Visibly hidden
	PVZ_END_FLAG_ENUM(ROFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(RealObjectFlags);

class RealObject : public GameObject, public Renderable
{
public:
	RT_CLASS_DEFINE(RealObject, GameObject, RtClass);

protected:
	RealObject();
public:
	virtual ~RealObject();

	// Values
	virtual void SetPosition(const SexyVector3& i_newPosition);
    inline const SexyVector3 &GetPosition() const;
	inline SexyVector2 GetPosition2D() const; // returns the 2.5 dimensional position of the object. v = (x, y - z)
	
	// Visual
	bool IsHidden() const;
	virtual void SetHidden(bool i_hidden);
	
	// Team
	TeamFlags GetTeamFlags() const;
	void SetTeamFlags(TeamFlags i_teams);
	bool IsOnTeam(TeamFlags i_team) const;
	void JoinTeam(TeamFlags i_team);
	void LeaveTeam(TeamFlags i_team);
	bool IsOnOpposingTeam(const RealObject* i_entity) const;
	bool IsOnOpposingTeam(TeamFlags i_teams) const;
	
	// ClipRect
	inline void			SetUseGroundClipRect(const bool i_useGroundClipRect);
    inline bool         IsUseGroundClipRect() const;
	Sexy::Rect			GetDrawClipRect(bool& o_needsClipRect);
	
	// Drawing
	virtual void AddToRenderQueue(class RenderQueue* i_queue);
	//	- Calls virtual onDraw()
	void Draw(class Sexy::Graphics* i_g) override;
	// DrawShadow
	//	- Calls virtual onDrawShadow()
	void DrawShadow(class Sexy::Graphics* i_g);
	virtual bool ShouldDrawShadow() const;
	// Ground
	float CalcGroundZHeight(const Sexy::SexyVector3 &i_position);
	virtual bool ShouldClipWithWater() const;
	bool IsOnWaterTile(const SexyVector3& i_position) const;
	virtual void SnapToGround(bool i_snapOnlyUnderGround);
	void SetDisableSnapToGround(const bool i_snapDisable);
	
	// Collision
	virtual Sexy::Rect calcCollisionRect();
	
	// CollidesWithTypes
	//	- Returns 'true' if this projectile can potentially collide with each of the types in the given bitmask
	virtual bool CollidesWithType(CollisionTypeFlags testTypes) const;
	virtual CollisionTypeFlags GetCollisionFlags() const;

	/// Virtual Interface Public
	virtual int GetRenderOrder() const { return 0; }
	
	// GetGridExtents
	//	- Returns the footprint of this entity in grid-squares
	//	- An entity's m_position will be in their lower-left-most gridsquare,
	//  so that increased GridExtents expand them rightwards and upwards on the grid
	virtual Sexy::Point GetGridExtents() const;
	
	// Sound
	// PlayPositionalSound
	//	- Plays a sound effect and tells wwise how to pan it properly
	void PlayPositionalSound(const std::string& i_eventName, float i_throttleTime = 0.f);
	// Sets the audio position for this object
	void SendPositionalAudioValue();

protected:
	/// Virtual Interface
	virtual void onChangeTeams(TeamFlags i_oldTeams, TeamFlags i_newTeams)
	{}
	virtual void onHiddenChanged(bool i_hidden, bool i_oldhidden)
	{}
	virtual void onDraw(class Sexy::Graphics* i_g)
	{}
	virtual void onDrawShadow(class Sexy::Graphics* i_g)
	{}
	
	/// Inherited implementation
	virtual void onApplyDrawClipRect(class Sexy::Graphics *i_g);
	virtual float getTideDepthHeightMaxPct();
	virtual float calcTideDepth(const SexyVector3& i_position, float i_additionalWaterDepth);

protected:
	// Serialized
	SexyVector3			m_position;
	
	TeamFlags			m_teamFlags;
	
	RealObjectFlags		m_realObjectFlags;
    
    bool                m_bSpecialSplitRect;
#ifdef _DEBUG
	// this exists to make sure we don't draw twice in the same loop since plants are dumb
	// and it's gross code that can be accidentally called
	bool		m_inDrawFunc;
#endif
};

/// Inlines

inline const SexyVector3 & RealObject::GetPosition() const
{
	return m_position;
}

inline SexyVector2 RealObject::GetPosition2D() const
{
	return SexyVector2(m_position.x, m_position.y - m_position.z);
}

inline TeamFlags RealObject::GetTeamFlags() const
{
	return m_teamFlags;
}

inline void RealObject::SetTeamFlags(TeamFlags i_teams)
{
	m_teamFlags = i_teams;
}

inline void RealObject::SetUseGroundClipRect(const bool i_useGroundClipRect)
{
	SetFlag(m_realObjectFlags, ROFLAG_UseGroundClipRect, i_useGroundClipRect);
}

inline bool RealObject::IsUseGroundClipRect() const
{
	return TestFlag(m_realObjectFlags, ROFLAG_UseGroundClipRect);
}

inline void RealObject::SetDisableSnapToGround(const bool i_snapDisable)
{
	SetFlag(m_realObjectFlags, ROFLAG_DisableSnapToGround, i_snapDisable);
}

inline void RealObject::SetHidden(const bool i_hidden)
{
	onHiddenChanged(i_hidden, TestFlag(m_realObjectFlags, ROFLAG_Hidden));
	SetFlag(m_realObjectFlags, ROFLAG_Hidden, i_hidden);
}

inline bool RealObject::IsHidden() const
{
	return TestFlag(m_realObjectFlags, ROFLAG_Hidden);
}

inline Sexy::Point RealObject::GetGridExtents() const
{
	return Sexy::Point(1, 1);
}

inline bool RealObject::CollidesWithType(CollisionTypeFlags testTypes) const
{
	return false;
}

inline CollisionTypeFlags RealObject::GetCollisionFlags() const
{
	return COLLIDE_None;
}


#endif // __REALOBJECT_H__
