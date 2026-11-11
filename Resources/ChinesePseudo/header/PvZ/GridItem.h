// GridItem.h

#ifndef __GRIDITEM_H__
#define __GRIDITEM_H__

#include "PvZ2IDs.h"
#include "Plant.h"
#include "BoardEntity.h"
#include "BoardEnums.h"
#include "GridItemConditionTracker.h"
#include "AttachedEffectManager.h"
#include "GridItemType.h"

class LawnApp;

namespace Message
{
	void GridItemDestroyed(const std::string& i_gridItemType);
}

typedef RtWeakPtr<class GridItem> GridItemPtr;

class GridItem : public BoardEntity
{
public:
	RT_CLASS_DEFINE(GridItem, BoardEntity, RtClass);
	
	/// Construction
	GridItem();
	virtual ~GridItem();
	
	/// Initialization
	void GridItemInitialize(GridItemTypePtr i_newType, int i_gridX, int i_gridY, int i_level);
    void GridItemInitializeUnbounded(GridItemTypePtr i_type, int i_gridX, int i_gridY, int i_level);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return false; }
    
    virtual BoardEntityHeight GetEntityHeight() const override;

	virtual float	GetHitpoints() const;
	inline void		SetHitpoints(float i_hitpoints);
	virtual float	GetMaxHitpoints() const;
	inline void		SetMaxHitpoints(float i_maxHitpoints);
	
	virtual void TakeDamage(const DamageInfo& i_damage) override;
	bool IsInvincible() const;
	virtual void TakeCure(int value, bool playEffect = true);
	virtual void TakeFatalDamage(const DamageInfo& i_damage) override;
	void SetInvincible(bool is_invincible, bool is_needEffect, pvztime_t i_time);
	float			GetExtraHitPointsmodifier() const;

	/// Accessors
	inline GridItemTypePtr GetType() const;
	inline GridItemPropsPtr GetProps() const;
	template <class T> inline const T* GetProps() const;
    
    inline Sexy::Point GetGridLocation() const;
    virtual void       SetGridLocation(Sexy::Point i_gridLocation, const bool i_recalculatePosition = true);
    void			SetGridLocationUnbounded(Point i_gridLocation, const bool i_recalculatePosition = true);
    
	inline int GetGridX() const;
	inline int GetGridY() const;
	inline void SetGridLocation(int i_gridX, int i_gridY);
    
    virtual bool IsDamageable() const;
	virtual bool IsDamageableByPlants() const;
	virtual bool IsDamageableByZombies() const;
    
	virtual bool IsDamageableByPlant(const Plant* i_plant) const;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const { return true; }
//    virtual bool ShouldClipWithWater() const {return true;}
    virtual bool ShouldBlockLevelCompletion() const { return false; }
    
    virtual void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons) const;
    
    virtual void KillGridItem();
    
    virtual SexyVector3 CalcPlantProjectileTargetLocation(float i_inTime = 0.f);

    /// Conditions
	void NotifyApplyCondition(GridItemConditions i_condition);
	void NotifyEndCondition(GridItemConditions i_condition);
	void NotifyConditionEvent(GridItemConditions i_condition) {}
	EntityCondition& ApplyCondition(GridItemConditions i_condition, pvztime_t i_duration);
	void EndCondition(GridItemConditions i_condition);
	void ClearConditions();
	bool HasCondition(GridItemConditions i_condition) const;
    GridItemConditionTracker& GetConditionTracker();
    
    AttachedEffectManager& GetAttachedEffectManager() { return m_attachedEffects; }
    AttachedBoardEntityManager& GetAttachedBoardEntityManager() { return m_attachedBoardEntities; }

    virtual void DrawCollisionInfo(Graphics* g);
    
    bool MatchesAny(const GridItemTestFlag i_flags) const;
    bool MatchesAny(const GridItemTestFlag i_flags, const class BoardEntity* i_entity) const;
    
    void SetConditionTracker(GridItemConditions i_condition, float i_additionalValue)
	{
		m_conditionTracker.SetAdditionalValue(i_condition, i_additionalValue);
	}

    virtual void 	StartLossLife(pvztime_t duration, float percentOfMaxHealth);
    virtual void 	EndLossLife();

    virtual void SetIsSleepping(bool i_isSleepping, float durationTime = -1.0f);
    bool IsSleepping() const { return m_isSleepping; }

public:
	bool m_isOnBoard;

protected:
    
    void registerForEvents() override;
	void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
    virtual bool isSameLocation(const Sexy::Point& i_atLocation);

	virtual void onGridItemInitialize();
	virtual void onGridItemPostInitialize() {}
    virtual void onTakeDamage(const DamageInfo& i_damage) {}
    virtual void onKilled() {}
    void onUpdate() override;
	void onDestroy() override;

    virtual Sexy::Rect calcCollisionRect() override;
    
    GridItemConditionTracker m_conditionTracker;
    
private:
	GridItemTypePtr		m_type;
	float				m_health = 0.0f;
	float				m_healthMax = 0.0f;
	Sexy::Point			m_gridLocation;
	bool   				m_bIsInvincible = false;
	float 				m_InvincibleTime = PVZ_EOT();
    
    AttachedEffectManager m_attachedEffects;
	AttachedBoardEntityManager m_attachedBoardEntities;

    pvztime_t m_tLossLifeTime;// the time that loss life in poison
	bool	 m_bIsLossLife;// check in loss life state
	float	 m_iLossLifePerFrame;// the loss of life in each frame

	bool    m_isSleepping;
    pvztime_t m_sleepingEndTime;
	
};

inline GridItemTypePtr GridItem::GetType() const
{
	return m_type;
}

inline GridItemPropsPtr GridItem::GetProps() const
{
	DBG_ASSERT(m_type.IsValid());
	return m_type->Properties;
}
template<class T> inline const T* GridItem::GetProps() const
{
	GridItemPropsPtr gridItemProps = GetProps();
	const T* typedProps = gridItemProps->Cast<const T>();
	return typedProps;
}

inline float GridItem::GetHitpoints() const
{
	return m_health;
}

inline float GridItem::GetMaxHitpoints() const
{
	return m_healthMax;
}

inline void GridItem::SetMaxHitpoints(float i_maxHitpoints)
{
	m_healthMax = i_maxHitpoints;
}

inline void GridItem::SetHitpoints(float i_hitpoints)
{
	m_health = i_hitpoints;
}

inline Sexy::Point GridItem::GetGridLocation() const
{
    return m_gridLocation;
}

inline int GridItem::GetGridX() const
{
    return m_gridLocation.mX;
}

inline int GridItem::GetGridY() const
{
    return m_gridLocation.mY;
}

inline void GridItem::SetGridLocation(int i_gridX, int i_gridY)
{
    SetGridLocation(Sexy::Point(i_gridX, i_gridY));
}

inline bool GridItem::IsDamageable() const
{
	return GetMaxHitpoints() > 0;
}
inline bool GridItem::IsDamageableByPlants() const
{
	return IsDamageable() && (IsOnTeam(TEAM_ZOMBIES));
}

inline bool GridItem::IsDamageableByZombies() const
{
	return IsDamageable() && (IsOnTeam(TEAM_PLANTS));
}

#endif //__GRIDITEM_H__
