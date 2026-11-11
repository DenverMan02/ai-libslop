#ifndef __PLANTFRAMEWORK_H__
#define __PLANTFRAMEWORK_H__

#include "Plant.h"
#include "TodCommon.h"
#include "RtObject.h"
#include "GridItem.h"
#include "PlantEnums.h"
#include "BoardConstants.h"
#include "PlantPot.h"

typedef RtWeakPtr<class Zombie> ZombiePtr;
class GameSubSystem;
class PlantAnimRig;

/*
=========================================================================
	Plant Framework

	This class is the framework for the plant types. Each function
	within this class is either virtual or pure virtual. All virtual 
	functions can be used as is for any plant type file, but any
	pure virtual class MUST be defined in the plant type class. This
	model allows for modular plant types and faster plant prototypes.
	This framework will use the parent Plant's functions for everything
	not overridden.
=========================================================================
*/

// Intention: These flags will be pulled in with an overall find system to provide configurability of the search routines.
// An alternative is to do it functionally, although layering on filters could be expensive.
//
// Filters are subtractive.  Therefore 'all' has no filters active.
//
enum FindTargetFilterFlags
{
	PVZ_BEGIN_FLAG_ENUM(FIND_TARGET_FILTER_),
	
	PVZ_FLAG(FIND_TARGET_FILTER_GRIDITEM_ONLY_FORWARD),
	PVZ_FLAG(FIND_TARGET_FILTER_ZOMBIES_ONLY),
	
	PVZ_END_FLAG_ENUM(FIND_TARGET_FILTER_),
	
	FIND_TARGET_ALL = 0
};
PVZ_MAKE_ENUM_BIT_OPERATORS(FindTargetFilterFlags);

class PlantFramework : public RtObject
{    
public:
	RT_CLASS_DEFINE(PlantFramework, RtObject, RtClass);

	// Standard constructor / destructor.
	PlantFramework();
	virtual ~PlantFramework() {};

	// Setup functions.
	virtual void	Initialize();
    virtual void	PostInitialize()			{ }
    virtual void	PostInitializeFromPropertySheet()	{ }
	virtual void	InitializeAnimRig();
    virtual void    AddPot(PlantPot* pot);
    PlantPot*		GetPot();

    int 	Rand();
    int		Rand(int range);
    float	Rand(float range);

	// Drawing functions
	virtual void	Draw(Graphics* g)                            { m_plant->internalPlantDraw(g); }
    virtual void    AddToRenderQueue(class RenderQueue* i_queue) { }
	virtual bool 	SetClipRect(Graphics* i_g)                   { return false; }

	virtual int		CalcRenderOrder();
	
	virtual float	GetAdditionalDrawHeightOffset()		{ return 0.f; }
	
	virtual void	SetPopAnimDelegates(class PlantAnimRig* i_rig);

	// Sound functions
	virtual void	PlayChewedOnSound();

	// Game updates
	virtual void		DoSpecial(int i_extraParam = 0)										{ }
	virtual class Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon)	{ return m_plant->Fire(targetZombie, i_row, i_plantWeapon); }
    virtual float		GetLaunchDelayMultiplier() { return 1.0f; }
    virtual float		GetReducedLaunchDelay() { return 0.0f; }
	virtual std::vector<BoardEntityPtr> FindAllTargets(FindTargetFilterFlags i_findFlags, const ZombieTestFlag i_appendZombieTestFlags);
	virtual std::vector<BoardEntityPtr> FindAllTargets(FindTargetFilterFlags i_findFlags);
    
    ZombiePtr FindTargetZombie(PlantWeapon i_plantWeapon);
    ZombiePtr FindTargetZombie(PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams);
    virtual ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams);
    virtual ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams);
    virtual ZombiePtr FindTargetZombieInRow(int i_row, PlantWeapon i_plantWeapon, int* io_zombieWeight, PlantTargetParams& i_targetParams, Rect i_attackRect);
    virtual ZombiePtr FindTargetZombieInGridRegion(Rect& i_gridRegion, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams);
    virtual GridItemPtr FindTargetDamageableGridItem(PlantWeapon i_plantWeapon);
    virtual GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon);
    virtual int calcZombieTargetWeight(Zombie* i_zombie, PlantTargetParams& i_targetParams);

    
    std::vector<BoardEntityPtr>	FindTargets(int i_targetsToFind, std::vector<BoardEntityPtr> i_targetsToSkip);
	std::vector<SexyVector3>	FindTargetsGrid(int i_targetsToFind, std::vector<BoardEntityPtr> i_targetsToSkip);
    virtual SexyVector3 GetFireOriginOffset(const PlantAction& i_action, float i_plantScale);
    virtual int			GetPlantFoodPlayCount()												{ return m_plant->GetProps()->PlantFoodPlayCount; }

    virtual int			GetMaxHitpoints() { return m_plant->GetType()->GetMaxHitpoints(); }
    
    virtual void		onDestroy();
	virtual void		onKilled(bool i_instantKill)                                        { }
    virtual void        onHealed()                                                          { }
    virtual void        onWatered(bool watered)                                             { }
    virtual void        onSleeped(bool sleeped)                                             { }
    virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon);
	virtual void		UpdateUnconditionally()												{ }
    virtual void		UpdateShooting()													{ }
	virtual void		UpdateActions()														{ }
    virtual bool		CanEndPlantfood()													{ return (PVZ_T() > m_plant->m_plantFoodEndTime); }
	virtual void		UpdatePlantfood()                                                   { }
    virtual bool        IsInPlantFoodState() const                                          { return m_plant->IsInPlantFoodState(); }
	virtual bool		HandleDamageStateChanged()											{ return false; }
	virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon)					{ return (COLLIDE_ALL_ZOMBIES | COLLIDE_GRIDITEMS); }
	virtual DamageTypeFlags	GetDamageFlags(PlantWeapon i_plantWeapon)						{ return DAMAGE_NONE; }
	virtual void		PlayAttackAnimation()												{ m_plant->PlayAttackAnimation(); }
	virtual bool		CanBeShoveled()														{ return true; }
	virtual bool		CanBeTargeted()                                                     { return true; }
	virtual bool		CanBeRangeTargeted()                                                { return true; }
    virtual bool		CanBeTargetedBy(const BoardEntity* i_entity)								{ return true; }
	virtual bool		BlockRailcartMovement() const										{ return false; }
    virtual bool		ShouldClipWithWater() const											{ return false; }
	virtual float		GetTideDepthHeightMaxPct();
    virtual GroundEffectType	GetTideEffect()												{ return GROUND_EFFECT_Tide; }
	virtual void		ProduceSun(const PlantAction& i_fromAction)							{ }
	virtual bool		CanProduceSun();

	virtual bool 		OverrideProjectileCollision(class Projectile* i_projectile)			{ return m_plant->DefaultBoardEntityProjectileCollisionOverride(i_projectile); }

    virtual void		CurePlant(const PlantAction& i_fromAction)							{ }
    virtual bool		IgnoreCurrentAction(PlantActionType i_type)							{ return false; }
	
	virtual bool		CanApplyPlantfood()													{ return false; }
	virtual void		ApplyPlantfood();
	virtual void		CancelPlantfood();
    virtual void		ManualCancelPlantfood();
    virtual void 		DisplayAvatar();
    virtual void		TriggerBoost();
    virtual void		ApplyExhausted(float i_duration);
    virtual void		CancelExhausted();
    virtual bool		IsExhausted()														{ return (m_plant->m_state == STATE_EXHAUSTED); }
    virtual void		ApplyCycling();
    virtual void        ApplyPlantfoodEffectHeal()                                          { m_plant->FullHealth(); }
    virtual bool		HasPlantfoodShield()												{ return false; }
    
    virtual void		ApplyHelped();
    virtual bool		CanEndHelped()														{ return (m_plant->GetAnimRig()->GetState() != PLANTANIM_HELPED_ON) && (m_plant->GetAnimRig()->GetState() != PLANTANIM_HELPED); }
    virtual void		UpdateHelped()														{ }
    virtual void		CancelHelped();
    virtual bool		IsBeingHelped()														{ return (m_plant->m_state == STATE_BEING_HELPED); }
    
	
	virtual SexyVector2	GetShadowOffset()													{ return SexyVector2(); }
	virtual float		GetShadowScaling()													{ return 1.f; }
    virtual Sexy::Rect	GetPlantAttackGridRect(PlantWeapon i_plantWeapon);
    virtual Sexy::Rect	GetPlantAttackRect(PlantWeapon i_plantWeapon);
	virtual bool        HasShadow()                                                         { return true; }
	virtual void		DoChewedOnEffect(ZombiePtr i_srcZombie)								{ }
	virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) 								{ return i_damage; }
    virtual void        IsImpactedByObject(RtWeakPtr<RtObject> i_object)                    { }
    virtual void        NotifyDamagedEntity(BoardEntity *entity)                            { }
    virtual bool        TryApplyDamageToEntity(DamageInfo &damageInfo, BoardEntity *entity) { return false; }
    virtual void 		NotifyComponentOwner()												{ }

	virtual std::string GetFireSoundEvent() const;

    virtual BoardEntityHeight GetEntityHeight() const										{ return m_plant->GetProps()->Height; }
	
	virtual void		TakeSmashAttack(ZombiePtr i_srcZombie);
	virtual void		TakeGridItemSmashAttack(GridItemPtr i_srcGridItem);
	virtual bool		TryBlockZombossRush(Zombie* i_zomboss);
    
    virtual bool		AbsorbsSmashAttack()                                                { return false; }
    virtual bool        CanBeCrushed() const                                                { return !IsInvincible() && !m_plant->IsInPlantFoodState(); }
    virtual bool        CanBeConvertedByCondition()                                         { return true; }


	virtual bool		OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) { return false; }
    
	virtual bool        IsInvincible() const                                                { return false; }
	virtual bool		HandleProjectile()													{ return false; }
	virtual float		GetRefundSunAmount();
    virtual void		OnRelocationBegun()													{ }
	virtual void		OnRelocationComplete() { }
    virtual void		OnRelocating(Sexy::SexyVector2 plantPos){}
    
    virtual void		CancelOngoingEffects()												{ }
    virtual void		ShowPersistentEffects(bool i_show)									{ }
    
	inline PlantAnimRig* GetAnimRig()														{ return m_plant->GetAnimRig(); }
	
	virtual void		onAnimStoppedCallback(const std::string& i_animCommand)			{}
	virtual void		onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect){}
	virtual void        onPlantfoodStarted() {}
	virtual void		onPlantfoodLooped()	 {}
	virtual void		onPlantfoodEnded() {}
    virtual bool		onReceiveHelp(PlantHelpType i_helpType)								{ return false; }
	virtual void 		registerForEvents() {}
	virtual void 		unregisterForEvents() {}
    virtual void		onSetDuplicate(bool i_duplicate)									{ if(IsInPlantFoodState()) CancelPlantfood(); }
    virtual bool		CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon)		{ return true; }
    virtual bool		CanTargetGrid(const int i_gridX, const int i_gridY);
    virtual void		NotifySetHidden(bool i_newValue, bool i_oldValue)					{ }
    
    virtual             PlantTargetParams GetTargetParamsForWeapon(PlantWeapon i_plantWeapon);
    virtual             BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon);
    
    //PVZ2_CHINESE_BEGIN
	virtual void DoSpecialForAvatar(PlantAvatarType eAvatar);  // for avatar
    virtual int GetMiniLevel(){ return m_plant->GetMiniLevel(); }
    virtual int GetMaxLevel(){ return m_plant->GetMaxLevel(); }
	virtual void onPostLoad() {} // for postload
	//PVZ2_CHINESE_END
    virtual int GetMaxAffectZombieLevel(){ return m_plant->GetMaxAffectZombieLevel(); }

    virtual void        onBeThrown();
    virtual void        onBePushed() {}
    virtual void        stopSpecialEffect() {};
    virtual bool		IsDelayDestroy();
    
    void SetAvatarEnable(bool bAvatar);
	bool GetAvatarEnable(){ return m_plant->GetAvatarEnable(); }
    
    virtual void AutoFire() {}
    
    virtual bool		TryBlockPush()														{ return false; }
    virtual bool		TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction)	{ return false; }
    
    virtual void        DoEventCall(RealObject* pTarget) { }
    virtual void onApplyCondition(PlantConditions i_condition) {}
    virtual void onEndCondition(PlantConditions i_condition) {}
    virtual void Idle();
    virtual bool CanBeWatered();
    bool IsArenaBattle() const;
    
    virtual void		CustomizePlantActionDamage(const PlantAction &i_action, DamageInfo &io_damageInfo) { }
    
    virtual void OnTakeDamageDoneWithComponent() {}
    
    virtual void		DelayPlantfood() {}

    virtual bool HasGravity() { return false; }

    void 	GetFinalAttackRect(Rect& i_attackRect);

    virtual void UpgradePlant()  { }

    virtual pvztime_t GetTheLeastAttactDuration() { return 0; }

    virtual void OnKillZombie(Zombie* i_zombie) { }
    virtual void ShovelKill() {}
    virtual bool IsVine() {return false;}
    virtual bool IsIgnoreControlAndDmg() { return false; }
protected:
    
    virtual ZombiePtr getBestZombieFromEntities(const std::vector<BoardEntity*> i_entities, PlantTargetParams& i_targetParams);
    virtual GridItemPtr getBestDamageableGridItemFromEntities(std::vector<BoardEntity*> entities);
    
    int damageEntitiesInBoardRect(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, Rect i_rect, bool i_sameTeam);
	int damageEntitiesInGridRadius(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, float i_gridradius, SexyVector3 i_origin, bool i_sameTeam);
	int damageEntities(DamageInfo& i_damage, BoardEntityTypeFlag i_acceptedTypes, std::vector<BoardEntity*> i_entities, bool i_sameTeam);
	virtual void onEntityDamaged(BoardEntity* i_entity) {}
    
	template<class T>
	inline const T* GetProps() const
	{
		PlantPropsPtr plantProps = m_plant->GetProps();
		const T* typedProps = plantProps->Cast<const T>();
		return typedProps;
	}
	inline PlantPropsPtr GetProps() const { return m_plant->GetProps(); }

	template<class T>
	inline T* GetRig() 
	{
		return m_plant->GetAnimRig()->Cast<T>();
	}
	inline PlantAnimRig* GetRig() { return m_plant->GetAnimRig(); }

	

	void SetCurrentLevel(int i_level){ m_plant->SetCurrentLevel(i_level); if (GetRig()) GetRig()->SetPlantLevel(i_level);  }
	int  GetCurrentLevel() const { return m_plant->GetCurrentLevel(); }
    bool IsOnLevel5() const { return m_plant->GetCurrentLevel() >= 5; }
    
    //PVZ2_CHINESE_BEGIN
	virtual void DoSpecialForAvatarNormal(){}  // for avatar
	//PVZ2_CHINESE_END

	/// Member Variables
public:
    bool m_callCancelPlantfood;
	// Pointer to our parent (the plant itself)
	Plant* m_plant;
	PlantPot* m_pot;
	PlantPotPtr m_potPtr;
};


/// Inline Implementation

inline GridItemPtr PlantFramework::FindTargetDamageableGridItem(PlantWeapon i_plantWeapon)
{
    Rect targetRect = Rect(m_plant->m_column, m_plant->m_row, BoardConstants::NUMBER_OF_COLUMNS(), 1);
    return FindTargetDamageableGridItem(
                                        targetRect,
                                        i_plantWeapon
                                        );
}

inline ZombiePtr PlantFramework::FindTargetZombie(PlantWeapon i_plantWeapon)
{
    PlantTargetParams targetParams = GetTargetParamsForWeapon(i_plantWeapon);
    
    return FindTargetZombie(i_plantWeapon, targetParams);
}

inline ZombiePtr PlantFramework::FindTargetZombie(PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams)
{
    Rect targetRect = GetPlantAttackGridRect(i_plantWeapon);
    
    return FindTargetZombie(targetRect, i_plantWeapon, i_targetParams);
}



#endif //__PLANTFRAMEWORK_H__
