//
//  Projectile.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/20/11.
//  Copyright (c) 2011 PopCap Games. All rights reserved.
//

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

//#include "Precompile.h"
//#include "LawnApp.h"
#include "ProjectileEnums.h"
#include "ProjectilePropertySheet.h"
#include "SexyVector.h"
#include "DamageInfo.h"
#include "EntityComponent.h"
#include "BoardEntity.h"
#include "AttachedEffectManager.h"

typedef RtWeakPtr<class Projectile> ProjectilePtr;

class Projectile : public RealObject
{
public:
	RT_CLASS_DEFINE(Projectile, RealObject, RtClass);

    CollisionTypeFlags  m_collideType;
    
    bool                m_critical;
    
protected:
	Projectile();
public:
	virtual ~Projectile();

	// Inheritable Interface
public:
	virtual bool OnCollideEntity(BoardEntity* i_entity);
	virtual bool OnCollideGround();
	virtual bool OnCollideRoof();
    virtual void OnHeadShot(BoardEntity* i_entity) {}
    virtual void onProjectileConverted() {}
    virtual bool ignoreDeathBox() { return false; }
    
    void SetCollisionRect(FRect i_rect) { m_collisionRect = i_rect; }
    FRect GetCollisionRect() const;

protected:
    virtual void onSetInstigator(BoardEntity* i_instigator) {}
	virtual void onUpdate(pvztime_t i_dt) {}
    virtual void onPostUpdate() {}
	virtual void onProjectileInitialized() {}
	virtual void moveThroughTime(pvztime_t i_dt);
	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL);
    virtual void radiateSplashDamage(BoardEntity* i_impactedEntity);
    virtual void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL);
    virtual std::string getImpactPam();

	// Non-inheritable Interface
public:
	// Draw
	//  - Render this projectile to the screen at its current location
	//	- Base class implementation will draw our current frame at our current location
	//  - [additional information about the graphics state as it is passed in]
    void onDraw(Graphics* i_g) override;
	void onDrawShadow(Graphics* i_g) override;
    bool ShouldDrawShadow() const override;

	//	- Must be done before this projectile can be used
	//	- Requires a property sheet, can also pass in an optional listener.
	//	- If 'autoDeleteListener' is true, then this Projectile will delete the given listener when it is deleted
	void InitializeProjectile(ProjectilePropertySheetPtr i_propertySheet, float i_attackLevel, float i_normalDamage, float i_specialDamage);

	//	- Base level update function, called from Board::Update
	void Update();
	void SetUpdateTimeOverride(pvztime_t i_newTimeStep);
	float GetUpdateTimeOverride() const { return m_timeStepOverride; }
    
	//void SetCollisionFlagsOverride(CollisionTypeFlags i_newFlags);
	//CollisionTypeFlags GetCollisionFlags() const override;
	virtual bool CollidesWithType(CollisionTypeFlags testTypes) const override;
    
    void SetCollideType(CollisionTypeFlags types);
    
    virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const;

	// SetPropertySheet
	//	- Sets the property sheet to use. Can be called on already initialized projectiles to change its type
	void SetPropertySheet(ProjectilePropertySheetPtr i_propertySheet);
    
    // NotifyDeflection
	// - Informs the projectile that something has deflected it and altered its path
	// - Immediately dispatches to derived classes through onDeflection()
	void NotifyDeflection(class BoardEntity* i_deflector) { onDeflection(i_deflector); }

    // LaunchAt
	//	- Sets the projectile's Velocity and Acceleration parameters so that it hits the target location at the specified time.
    void LaunchAt(const SexyVector3& i_target, float i_apexHeight, pvztime_t i_timeToHit);
    void LaunchAtFromProps(const Sexy::SexyVector3 &i_target, const class PultProjectileProps& props);
    
	/// Public Accessors
    const ProjectilePropertySheet* GetProps() const { return getProps(); }
    RtWeakPtr<ProjectilePropertySheet> getPropsNoCache();
	bool IsPaused() const { return TestFlag(m_propertyFlags, PROJECTILE_FLAG_PAUSED); }
	bool HasShadow() const { return !TestFlag(m_propertyFlags, PROJECTILE_FLAG_HIDESHADOW); }

	int GetRow() const { return m_boardRow; }
	void SetRow(int i_row) { m_boardRow = i_row; }
	int GetRowHeight() const { return m_boardRowHeight; }
	void SetRowHeight(int i_rowHeight) { m_boardRowHeight = i_rowHeight; }
	class PopAnimRig* GetAnimRig() const { return m_attachedAnimRig; }
	void SetAnimRigOffset(const SexyVector2& i_offset) { m_attachedAnimRigOffset = i_offset; }
    
	int CalcRenderOrder() const override { return m_renderOrder; }
	void SetRenderOrder(int i_renderOrder) { m_renderOrder = i_renderOrder; }
	virtual int GetRenderOrder() const override { return CalcRenderOrder(); }
    
	const SexyVector3 & GetVelocity() const { return m_velocity; }
	const SexyVector3 & GetAcceleration() const { return m_acceleration; }
	const SexyVector3 & GetVelocityScale() const { return m_velocityScale; }
	const SexyVector3 & GetPreviousPosition() const { return m_previousPosition; }
	float GetRotation() const { return m_rotation; }
	float GetAngularVelocity() const { return m_angularVelocity; }
	
	bool  IsSkipAdditionalAngularVelocity();

	void SetPosition(const SexyVector3& i_newPos) override { SetPosition(i_newPos.x, i_newPos.y, i_newPos.z); }
	void SetPosition(MATH_TYPE i_x, MATH_TYPE i_y, MATH_TYPE i_z);
    virtual void InitialSetPosition(const float i_x, const float i_y, const float i_z);

	void SetVelocity(const SexyVector3& i_newVel) { m_velocity = i_newVel; }
	void SetVelocity(MATH_TYPE i_x, MATH_TYPE i_y, MATH_TYPE i_z)
	{
		m_velocity.x = i_x;
		m_velocity.y = i_y;
		m_velocity.z = i_z;
	}

    void ApplyRotationToVelocity(const SexyTransform2D& i_rotationTransform);
    
	void SetAcceleration(const SexyVector3& i_newAccel) { m_acceleration = i_newAccel; }
	void SetAcceleration(MATH_TYPE i_x, MATH_TYPE i_y, MATH_TYPE i_z)
	{
		m_acceleration.x = i_x;
		m_acceleration.y = i_y;
		m_acceleration.z = i_z;
	}
	
	void SetVelocityScale(const SexyVector3& i_newVelScale) { m_velocityScale = i_newVelScale; }
	void SetVelocityScale(MATH_TYPE i_x, MATH_TYPE i_y, MATH_TYPE i_z)
	{
		m_velocityScale.x = i_x;
		m_velocityScale.y = i_y;
		m_velocityScale.z = i_z;
	}
	
	void SetRotation(float i_rotation) { m_rotation = i_rotation; }
	void SetAngularVelocity(float i_theta) { m_angularVelocity = i_theta; }
	void SetRotatedVelocity(float i_magnitude);
	void RotateTowardTarget();

	void SetPaused(bool i_paused);
	void SetShadow(bool i_showShadow);

	class BoardEntity* GetInstigator() const { return m_instigator; }
	RtWeakPtr<class BoardEntity> GetInstigatorPtr() { return m_instigator; }
	void SetInstigator(class BoardEntity* i_instigator);
	
	DamageTypeFlags GetDamageFlags() const { return m_damageFlags; }
	void SetDamageFlags(DamageTypeFlags i_damageFlags) { m_damageFlags = i_damageFlags; }

    bool GetAffectsTarget() const { return m_shouldAffectTarget; }
    void SetAffectsTarget(bool i_shouldAffectTarget) { m_shouldAffectTarget = i_shouldAffectTarget; }
    
	void SetTarget(const RtWeakPtr<class BoardEntity>& i_target) { m_target = i_target; }
	virtual class BoardEntity* GetTarget() { return m_target; }

	//	- Returns the collision rectangle (in board space)
	Rect CalcCollisionRectBoardSpace() const;
    Rect CalcSweptCollisionRectBoardSpace() const;

    bool IsLobbed() const;
    
	void SetRenderImage(ImagePtr i_image)
	{
		m_renderImage = i_image;
	}
    
    void SnapToGround(bool i_snapOnlyUnderGround) override;
    
    bool GetMirrored() const { return m_mirrored; }
	void SetMirrored(bool i_mirrored) { m_mirrored = i_mirrored; }
    
    void SetCollideLeftToRight(bool i_collideLeftToRight) { m_collideLeftToRight = i_collideLeftToRight; };

    float GetAttackLevel() const
    {
        return m_attackLevel;
    }
    void SetAttackLevel(float i_AttackLevel)
	{
    	m_attackLevel = i_AttackLevel;
	}
    void SetPierceCount(int i_count)    { m_pierceCount = i_count; }
    int  GetPierceCount() const         { return m_pierceCount; }
    void SetMaxPierceCount(int i_count) { m_maxPierceCount = i_count; }
	int GetMaxPierceCount() const { return m_maxPierceCount; }
    
    float GetBaseDamageAmount() const               { return m_damageAmount;           }
	void  SetBaseDamageAmount(float i_damageAmount) { m_damageAmount = i_damageAmount; }

	float GetSplashDamageAmount() const { return m_splashDamage; }
	void SetSplashDamageAmount(float i_splashDamageAmount) { m_splashDamage = i_splashDamageAmount; }
    
    float GetDamageAmount();
    
    void SetStunDuration(float i_stunDuration) { m_stunDurationAmount = i_stunDuration; }
    float GetStunDuration() { return m_stunDurationAmount; }

    bool IsHeadShot() const;
    
    void CreateCriticalEffect();
    bool CanBeBlocked() { return getProps()->ProjectileType == "CanBlock"; }
    
    void SetAppendExtraDamage(float iExtra) { m_iAppendExtraDamage = iExtra; }
    float GetDamageRate() { return m_normalDamage * m_specialDamage * m_attackLevel * m_iAppendExtraDamage; }
    int GetInstigatorLevel() const { return m_instigatorLevel; }
    void SetBaseRotation(float rotation) { m_baseRotation = rotation; }
    float GetBaseRotation() { return m_baseRotation; }
	float GetSpecialDamageRate() const { return m_specialDamage; }
    
    void SetScale(float i_scale)
    {
        m_scale = i_scale;
    }
    float GetScale() { return m_scale; }

	std::vector<ZombieConditionEntry> GetDamageConditions() const { return m_damageConditions; }
	void SetDamageConditions(std::vector<ZombieConditionEntry> i_damageConditions) { m_damageConditions = i_damageConditions; }
	void SetForceCollision(bool i_collision) { m_forceCollision = i_collision; }
	bool GetForceCollision() { return m_forceCollision; }
	void SetShouldKeepRoofZ(bool i_flag);
	void ShouldDestroyOnOutOfStage(bool i_flag) { m_destroyOnOutOfStage = i_flag; };

	// AttachedEffects
	AttachedBoardEntityNode* GetOrCreateAttachedBoardEntity(const std::string& i_entityName);
	AttachedBoardEntityNode* GetAttachedBoardEntity(const std::string i_entityName);
	AttachedEffect& AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset = 1, bool iPlayOnce = false, bool iDisableDynamicScaling = false, const AnimSelectionMethod i_method = SELECT_RANDOM_INDEX);
	void RemoveAttachedEffect(const char* i_entityName);

	void SetNotifyCollideEntity(bool i_notify) { m_needNotifyCollideEntity = i_notify; }

protected:
    void playSound(class BoardEntity* i_entity);
	virtual void damageEntity(class BoardEntity* i_entity);
    virtual void healEntity(class BoardEntity* i_entity);
    virtual void onDeflection(class BoardEntity* i_deflector) {}
    virtual void onSplashDamageHitEntity(class BoardEntity* i_hitEntity) {}
    
    inline const ProjectilePropertySheet* getProps() const
	{
		// Return cached bare ptr, set it from RtPtr if NULL
		return (m_cachedPropertySheet ? m_cachedPropertySheet : (m_cachedPropertySheet = m_propertySheetPtr));
	}
    
    // Attached AnimRig. Will be deleted when this projectile is deleted
	RtWeakPtr<class PopAnimRig> 	m_attachedAnimRig;
	
	// Attached AnimRig's offset from the projectile
	SexyVector2 m_attachedAnimRigOffset;

	//	- Returns a potential offset for a splat effect
	//	- Value returned is RANDOM within a range, plan accordingly!
	void calcRandomSplatOffset(SexyVector2& o_offset);

	// Attached Effect
	void DetachAttachedEffect(const char* i_entityName);
	AttachedEffect* GetAttachedEffect(const std::string& i_entityName);
    AttachedEffectManager& GetAttachedEffectManager() { return m_attachedEffects; }
    AttachedBoardEntityManager& GetAttachedBoardEntityManager() { return m_attachedBoardEntities; }
	void clearAttachedEffects();
	virtual void onEffectAttached(AttachedEffect& i_effect, bool i_disableDynamicScaling);
	virtual void updateOverlayEffects();

private:

	/// Internal helper functions
    
    FRect calcCollisionRectBoardSpace(const SexyVector3& i_pos) const;
	
	/// Internal accessors

	//	- Attaches a PopAnimRig animation to the location of the projectile, with specified offsets
	//	- The specified PAM will be DUPLICATE()'ed!!!
	void SetAttachedPAM(PopAnim* i_PAM, const SexyVector2 i_offset);
	   
    void updateGroundEffect();
	
	/// Member variables
protected:
	// Should this projectile affect the target it hits?
	bool m_shouldAffectTarget;
	int m_pierceCount;
	// Z-order for rendering
	int m_renderOrder;

protected:
	// Read-only properties
	mutable ProjectilePropertySheet*    m_cachedPropertySheet; 	// Transient
	RtWeakPtr<ProjectilePropertySheet> 	m_propertySheetPtr;		// Serialized

	// Entity that we are doing damage on the behalf of
	RtWeakPtr<class BoardEntity> m_instigator;
    int m_instigatorLevel;

	// Game time when we were spawned
	pvztime_t m_timeStepOverride;
    
    SexyVector3 m_previousPosition;
    SexyVector3 m_velocity;
	SexyVector3 m_acceleration;

	// Per-frame Velocity Scale - Position = Position + Velocity * VelocityScale
	SexyVector3 m_velocityScale;
	
    int m_boardRow;
    int m_previousBoardRow;
	int m_boardRowHeight;

	// Current image we're drawing from
	ImagePtr m_renderImage;
	
	// Rendering scale
	float m_scale;
	// Rendering rotation
	float m_rotation;
    float m_baseRotation;
	// Speed at which this projectile is rotating. Affects m_rotation each frame.
	float m_angularVelocity;
    // Initial height value to base the GroundZ offset from
	float m_initialHeight;
    
    //do Flip flag
    bool m_mirrored;
    
    // Sort collisions left to right or sort them right to left?
	bool m_collideLeftToRight;
	
    // Damage amount to do
	float m_damageAmount;

	// Amount of Stun
	float m_stunDurationAmount;
    
	// Damage type to do
	DamageTypeFlags m_damageFlags;

	// Damage conditions to apply
	std::vector<ZombieConditionEntry> m_damageConditions;

	// Bitmask of our property flags
	ProjectilePropertyFlag m_propertyFlags;

	RtWeakPtr<class BoardEntity> m_target;
    
    EntityComponent_GroundEffect m_groundEffect;

    AttachedEffectManager m_attachedEffects;
    AttachedBoardEntityManager m_attachedBoardEntities;

	float m_attackLevel;
    
    

    int m_maxPierceCount;
    
    float m_splashDamage;

    float m_normalDamage;
    float m_specialDamage;
    
    float m_iAppendExtraDamage;
    bool m_forceCollision;

	bool m_shouldKeepRoofZ;
	float m_keepRoofZ;

	bool m_destroyOnOutOfStage;

	bool m_needNotifyCollideEntity;

	FRect m_collisionRect;
};

namespace ProjectileHelpers
{
	void RandomizeVelocities(Projectile* i_projectile);
 
	//	- Sets the projectile's Velocity and Acceleration parameters so that it hits the target location at the specified time.
	void LaunchAt(Projectile* i_projectile, const SexyVector3& i_target, float i_apexHeight, pvztime_t i_timeToHit);

	// - Do a newtonian timestep.
	void Integrate(Projectile* i_projectile, pvztime_t i_dt);

	//	- Collision helpers.
	void CheckForCollisions(Projectile* i_projectile);

	SexyVector3 RandomizeVectorFromRange(const std::vector<ValueRange> &i_range);
    
    bool CheckForCritical(const Rect& i_projectileRect, const Rect& i_targetRect, const float& i_pos);
}

namespace Message
{
	void NotifyProjectileCreated(Projectile* i_projectile);
	void NotifyProjectileCollideEntity(Projectile* i_projectile, BoardEntity* i_entity);
}

#endif // __PROJECTILE_H__
