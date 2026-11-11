//
//  Collectable.h
//  PlantsVersusZombies2
//
//  Created by jsola on 11/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Collectable_h
#define PlantsVersusZombies2_Collectable_h

#include "BoardEntity.h"
#include "Curve.h"
#include "CollectableType.h"
#include "PVZTypes.h"
#include "StandaloneEffect.h"
#include "StateMachine.h"

typedef RtWeakPtr<class Collectable> CollectablePtr;

enum CollectableFlags
{
	PVZ_BEGIN_FLAG_ENUM(COLLECTABLE_),
	PVZ_FLAG(COLLECTABLE_StartCollectAfterMotion),
	PVZ_FLAG(COLLECTABLE_FinishCollectAfterMotion),
	PVZ_FLAG(COLLECTABLE_StartExpireAfterMotion),
	PVZ_FLAG(COLLECTABLE_NeverExpire),
	PVZ_FLAG(COLLECTABLE_Banked),
	PVZ_FLAG(COLLECTABLE_KeepOnBoard),
	PVZ_FLAG(COLLECTABLE_DisableCollection),
	PVZ_FLAG(COLLECTABLE_DisableTouch),
	PVZ_FLAG(COLLECTABLE_EndOfLevelReward),
	PVZ_FLAG(COLLECTABLE_Flashing),
	PVZ_END_FLAG_ENUM(COLLECTABLE_),
};
PVZ_MAKE_ENUM_BIT_OPERATORS(CollectableFlags);

STATE_ENUM_BASE_BEGIN(CollectableState)
	CS_Idle,
	CS_Collecting,
STATE_ENUM_END(CollectableState)

enum CollectableMotion
{
	PVZ_BEGIN_ENUM(MOTION_),
	MOTION_Idle,					// No motion
	MOTION_Newtonian,				// Simulates newtonian motion using velocity, acceleration, and drag
	MOTION_Drunk,					// Floaty effect, used for plantfood
	MOTION_Interpolate,				// Interp from one point to another, using a given interp method
	MOTION_InterpolateAndScale,		// Interp from one point to another, and scale from the initial to final scale
	MOTION_ScaleOut,				// Scale to 0 over time
	PVZ_END_ENUM(MOTION_),
};

class Collectable : public BoardEntity
{
public:
	RT_CLASS_DEFINE(Collectable, BoardEntity, RtClass);

	/// Construction
	Collectable();
	virtual ~Collectable();

	/// Initialization
	void CollectableInitialize(CollectableTypePtr i_newType);
    
    static StandaloneEffect* CreateRenderEffect(const CollectableType* i_type);
	
	void SetMotionIdle();
	void SetMotionNewtonian(const SexyVector3& i_velocity, const SexyVector3& i_acceleration, bool i_stopOnHitGround);
	void SetMotionDrunk();
	void SetMotionInterpolate(const SexyVector3& i_initialPosition, const SexyVector3& i_finalPosition, pvztime_t i_duration, CurveType i_interpMethod);
	void SetMotionInterpolateAndScale(const SexyVector3& i_initialPosition, const SexyVector3& i_finalPosition, float i_initialScale, float i_finalScale, pvztime_t i_duration, CurveType i_interpMethod);
	void SetMotionScaleOut(pvztime_t i_duration, CurveType i_interpMethod);
	
	void SetKeepOnBoard(bool i_keepOnBoard);
	void SnapToBoard();
	
	void StartExpirationTimer();
	void StartExpirationTimerAfterMotion();
    void SetPauseExpirationTimer(bool i_paused);

	void StartCollectAfterMotion();
	
	float GetScale() const { return m_scale; }
	void GetMotionNewtonianValues(SexyVector3& o_velocity, SexyVector3& o_acceleration, bool& o_stopOnHitGround) const;
	
	/// Board interaction
	virtual Sexy::Rect calcCollisionRect() override;
	
    bool IsTouchable() const;
	bool IsCollectable() const;
	bool IsCollecting() const;
	bool IsBanked() const;
	
	void ForceUpdateEffect();
	
	// TryToCollect does nothing on its own other than send out an event
	// It's up to an event catcher to call StartCollect and set motion parameters
	void TryToCollect();
    void TryToInstantUse();
	void StartCollect(bool i_finishOnMotionComplete);
	void FinishCollect();
	void CancelFinishCollectAfterMotion();
	
	void SetFadeOutOnCollectDuration(pvztime_t i_fadeTime);
	
	void SetNeverExpire(bool i_neverExpire);
	void SetDisableCollection(bool i_disableCollection);
	void SetDisableTouch(bool i_disableTouch);
	
	void SetFlashing(bool i_flashing);
    bool ShouldDrawShadow() const override { return false; }
	
	void SetIsEndOfLevelReward(bool i_isReward);
	bool IsEndOfLevelReward() const;
    
    void StartInstantUseTimer();
	
	virtual int CalcRenderOrder() const override;
	
	void SetHidden(bool i_hidden) override;

	CollectableTypePtr GetType() const
	{
		return m_type;
	}
	
	pvztime_t GetAge() const
	{
		return PVZ_T() - m_creationTime;
	}

	void SetAutoSunCollectTime(pvztime_t t_SunFromSky)
	{
		m_AutoSunCollectTime = t_SunFromSky;
	}
	pvztime_t GetAutoSunCollectTime() const
	{
		return m_AutoSunCollectTime;
	}
    
    pvztime_t GetexpirationStartTime() const
    {
        return m_expirationStartTime;
    }

	inline CollectableMotion GetMotionType() const;
    
    bool IsTouched(const Sexy::Touch& i_touch);
    
    CollectableTypePtr 	m_type;
    StandaloneEffectPtr m_renderEffect;
    float				m_scale;
protected:
	void setState(CollectableState i_state);
	CollectableState getState() const;
	pvztime_t getTimeInState() const;
	
	void playSpawnedSound();
	void playCollectSound();
	void playHitGroundSound();
	
	DECLARE_STATE_FUNCTIONS(CollectableState, Idle);
	DECLARE_STATE_FUNCTIONS(CollectableState, Collecting);

	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
	virtual void onCollectableInitialize()
	{}
	virtual void onUpdate() override;
	
	virtual void updateMotion();
	virtual void updateEffect();
	virtual void onFinishMotion();

	virtual bool onTouchEvent(const Sexy::Touch& i_touch);
	
	inline StandaloneEffectPtr getRenderEffect() const;
	
	Color getDesiredEffectColor();
    virtual void initializeRenderEffect();
    virtual bool CanChangeColorState();
private:
	
	
	void updateExpirationEffects(pvztime_t i_timeUntilExpiration);
	void clearExpirationEffects();
	
	void updateDrunkMotion();
	
	int32 getCollectableStateSerialization();
	void setCollectableStateSerialization(int32 i_state);    
	
	/// Type info
	
	CollectableFlags 	m_collectableFlags;
	pvztime_t			m_creationTime;
	StateMachine<CollectableState>	m_state;
	pvztime_t			m_stateStartTime;
	pvztime_t			m_expirationStartTime;
	
	/// Visual properties
	
	pvztime_t			m_fadeOutOnCollectTime;
	
	
	/// End Of Level Reward properties
	StandaloneEffectPtr m_rewardSparkleEffect;
	StandaloneEffectPtr m_rewardRaysEffect;
	
	/// Motion properties
	CollectableMotion 	m_motion;
	pvztime_t			m_motionStartTime;
	// Motion_Newtonian
	SexyVector3 	m_newton_velocity;
	SexyVector3 	m_newton_acceleration;
	bool			m_newton_stopOnHitGround;
	// Motion_Interpolate and Motion_ScaleOut
	SexyVector3		m_interp_initialPosition;
	SexyVector3		m_interp_finalPosition;
	float			m_interp_initialScale;
	float			m_interp_finalScale;
	pvztime_t		m_interp_duration;
	CurveType		m_interp_method;
	// Motion_Drunk
	float               m_drunk_motionAngle;
	float               m_drunk_motionTurnAngle;
	float               m_drunk_motionTurnAngleSpeed;
	float               m_drunk_motionSpeed;
	bool                m_drunk_motionPushToCenter;

	pvztime_t 			m_AutoSunCollectTime;
    pvztime_t           m_instantUseStartTime;
};


namespace Message
{
	void CollectableTryToCollect(Collectable* i_collectable);
	void CollectableExpired(Collectable* i_collectable);
	void CollectableCollectionStarted(Collectable* i_collectable);
	void CollectableCollectionFinished(Collectable* i_collectable);
    void CollectableTryToInstantUse(Collectable* i_collectable);
    void CollectableFinishCollect();
    void CollectableHitGround(Collectable* i_collectable);
}

/// Inline functions

inline StandaloneEffectPtr Collectable::getRenderEffect() const
{
	return m_renderEffect;
}

inline CollectableMotion Collectable::GetMotionType() const
{
	return m_motion;
}

#endif
