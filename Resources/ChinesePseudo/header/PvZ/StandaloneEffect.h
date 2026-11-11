//
//  StandaloneEffect.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/18/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StandaloneEffect_h
#define PlantsVersusZombies2_StandaloneEffect_h

#include "GameObject.h"
#include "Core.h"
#include "RtReflectionDelegate.h"

typedef RtWeakPtr<class StandaloneEffect> StandaloneEffectPtr;

typedef RtReflectionDelegate<Delegate1<class StandaloneEffect*> > OnStandaloneEffectCompleted;

enum EffectFlags
{
	PVZ_BEGIN_FLAG_ENUM(EFFECTFLAG_),

	// DESTROYED
	//	- Set when our entity is done being a part of the game, but has not yet
	// 	had its memory cleaned up. Destruction of DEAD objects happens simultaneously
	//	of each game Update().
	PVZ_FLAG(EFFECTFLAG_DESTROYED),

	// ATTACHED
	//	- Set if we should change our position based on another target BoardEntity's
	// position each update.
	PVZ_FLAG(EFFECTFLAG_ATTACHED),

	// ATTACHED_SYNC_CLIPRECT
	//	- Set if we should also attempt to inherit the clip rect from our target
	PVZ_FLAG(EFFECTFLAG_ATTACHED_SYNC_CLIPRECT),

	// CANCELDESTRUCTION
	//	- Used to allow recipients of the CompletionCallback to prevent destruction
	//	this one time
	PVZ_FLAG(EFFECTFLAG_INTRIGGERCOMPLETIONCALL),
	PVZ_FLAG(EFFECTFLAG_CANCELCOMPLETION),

	// KEEPALIVE
	//	- If set, we never Destroy() ourselves on completion
	//	- Completion events are still fired off
	PVZ_FLAG(EFFECTFLAG_KEEPALIVE),

	// MANUALDRAW
	//	- The effect doesn't draw itself. It is force drawn by something else.
	PVZ_FLAG(EFFECTFLAG_MANUALDRAW),

	// SCREENSPACE
	//	- This effect is drawn in screen space and should not have board scaling applied
	PVZ_FLAG(EFFECTFLAG_SCREENSPACE),

	// DESTROYWHENUNATTACHED
	//	- This effect is destroyed when its attachment goes away.
	PVZ_FLAG(EFFECTFLAG_DESTROYWHENUNATTACHED),

	PVZ_END_FLAG_ENUM(EFFECTFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(EffectFlags);

class StandaloneEffect : public GameObject
{
public:
	RT_CLASS_DEFINE(StandaloneEffect, GameObject, RtClass);

	StandaloneEffect();
	virtual ~StandaloneEffect() {}

	/// Use these functions to set your effect up after spawning it!

	// The completion callback will be fired when the effect decides it's done playing
	// From inside the callback, you may call CancelCompletion to prevent the effect from being Destroy'ed()
	void SetCompletionCallback(OnStandaloneEffectCompleted i_onCompletion);
	void CancelCompletion();
	// If set, completion will still be triggered, but we will not be destroyed
	void SetKeepAlive(bool i_keepAlive);

	// We only ever hold on to a screen-space origin and render layer,
	// SetBoardSpaceOrigin will instantaneously convert the parameters to screen space
	void SetScreenSpaceOrigin(const SexyVector2& i_origin, int i_renderLayer);
	const SexyVector2& GetScreenSpaceOrigin() const { return m_screenSpaceOrigin; }
    
	void SetBoardSpaceOrigin(const SexyVector3& i_origin, int i_renderLayerOverride = -1);
    const SexyVector2 GetBoardSpaceOrigin() const;

	void SetIsScreenSpaceEffect(bool i_isScreenSpaceEffect);
	bool IsScreenSpaceEffect() const;

	// Attaching this effect to something else will cause us to follow their position
	// and render layer during each Update()
	// This works reliably because these effects are ticked after BoardEntities in a separate pass
	void SetAttached(class RealObject* i_targetEntity, const SexyVector3& i_boardSpaceOffset, int i_renderLayerOffset = 1);
	void SetAttached(class RealObject* i_targetEntity, const SexyVector2& i_screenSpaceOffset, int i_renderLayerOffset = 1);
    SexyVector2 GetAttachmentOffset();
	void SetAttachmentOffset(const SexyVector3& i_boardSpaceOffset);
	void SetAttachedSyncClipRect(bool i_sync);
	void ClearAttachedTo();
	void SetDestroyWhenUnattached(bool i_x);
	class RealObject* GetAttachedTo() const;

	// It's up to your derived class to implement these
	virtual void SetColor(const Color& i_color)
	{
		DBG_HALT_MSG("SetColor not implemented on %s!", this->GetClass()->GetName());
	}
	virtual void SetScale(float i_scale)
	{
		DBG_HALT_MSG("SetScale not implemented on %s!", this->GetClass()->GetName());
	}

	void SetVisibility(bool i_show);
    bool GetVisibility() { return m_shouldDraw; }

	/// These functions are meant to be called by the managing system, you can probably just ignore them
	void Update();
	void Draw(class Graphics* i_g);
	void AddToRenderQueue(class RenderQueue* i_queue);
	
	void FollowAttachment();

	/// Simple accessors

	void SetManuallyDrawn(bool i_isManuallyDrawn);
	bool IsManuallyDrawn() const;

	inline void SetRenderLayerOverride(int i_renderLayer)
	{
		m_renderLayerOverride = i_renderLayer;
	}
	inline void ClearRenderLayerOverride()
	{
		m_renderLayerOverride = -1;
	}

	inline int GetRenderLayer() const;

	template<typename T> static T* CreateEffect()
	{
		Sexy::RtClass *i_effectClass = T::StaticGetClass();
		StandaloneEffect* effectObj = GameObject::Create(i_effectClass, PVZDB::TABLE_EFFECTS)->CastChecked<StandaloneEffect>();
		return effectObj->template CastChecked<T>();
	}

	void ClearClipRect();
	void SetClipRect(const Sexy::Rect& i_rect);

	virtual SexyVector2 GetDimensions() { return {}; }

	void SetIgnoreZForAttachment(bool i_ignoreZ) { m_ignoreZ = i_ignoreZ; }
	void SetUIUse(bool i_uiUse) { m_uiUse = i_uiUse; }

protected:
	// Virtual internal dispatches
	virtual void onInitialized() override
	{}
	virtual void onOriginChanged()
	{}
	virtual void onUpdate()
	{}
	virtual void onDraw(class Graphics* i_g)
	{}
	virtual void onDestroy() override
	{}

	virtual pvztime_t getT();
	virtual pvztime_t getDt();

	// Call this when you're done! The effect will be destroyed and cleaned up at the end of the frame
	void triggerCompletion();

	void syncAttachedClipRect();

private:
	/// Serialized
	EffectFlags m_standaloneEffectFlags;

	SexyVector2 m_screenSpaceOrigin;
	int m_renderLayerOverride;
	int m_renderLayer;

	RtWeakPtr<class RealObject> 	m_attachmentTarget;
	SexyVector2 					m_attachmentScreenSpaceOffset;
	int 							m_attachmentRenderLayerOffset;

	OnStandaloneEffectCompleted m_onCompletion;
	bool m_shouldDraw;

	Sexy::Rect m_clipRect;
	bool m_ignoreZ;
	bool m_uiUse;

	/// Transient
};

inline int StandaloneEffect::GetRenderLayer() const
{
	if (m_renderLayerOverride >= 0)
	{
		return m_renderLayerOverride;
	}
	return m_renderLayer;
}

inline void StandaloneEffect::SetAttachedSyncClipRect(bool i_sync)
{
	SetFlag(m_standaloneEffectFlags, EFFECTFLAG_ATTACHED_SYNC_CLIPRECT, i_sync);
	
	if (i_sync)
	{
		syncAttachedClipRect();
	}
}


#endif
