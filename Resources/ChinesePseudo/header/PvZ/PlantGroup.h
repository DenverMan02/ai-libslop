//
//  PlantGroup.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 4/16/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantGroup__
#define __PlantsVersusZombies2__PlantGroup__

#include <string>
#include <vector>

#include "Core.h"
#include "BoardEntity.h"
#include "DamageInfoProps.h"
#include "PlantEnums.h"
#include "RestrictionSet.h"

class PlantsSortedByLayer
{
public:
    void AddPlant(PlantPtr i_plant);
    void RemovePlant(PlantPtr i_plant);
    bool HasPlant(PlantPtr i_plant);
    bool HasPlant(const std::string& i_typename);
    PlantPtr GetTopPlant();
    bool Empty() { return m_plants.empty(); }
    int Count() { return (int) m_plants.size(); }
    
    const std::vector<PlantPtr>& Plants() const { return m_plants; }
    
    std::vector<PlantPtr> m_plants;
};

class PlantGroup : public BoardEntity
{
public:
    RT_CLASS_DEFINE(PlantGroup, BoardEntity, Sexy::RtClass);

	PlantGroup();
	//virtual ~PlantGroup() {}

    void AddPlant(PlantPtr i_plant) { m_plants.AddPlant(i_plant); invalidateCollisionRect(); fixFrost(); }
    bool HasPlant(PlantPtr i_plant) { return m_plants.HasPlant(i_plant); };
    bool HasPlant(const std::string& i_typename);
    bool HasPlant(BoardEntity* i_plant);
    void RemovePlant(PlantPtr i_plant) { m_plants.RemovePlant(i_plant); invalidateCollisionRect(); };
    PlantPtr GetTopPlant() { return m_plants.GetTopPlant(); }
    PlantPtr GetPlantAtLayer(MultiPlantGridLayer i_layer);
    bool Empty() { return m_plants.Empty(); }
    int Count() { return m_plants.Count(); }
    int AliveCount();
	BoardEntityTypeFlag	GetBoardEntityType() override { return ENTITYTYPE_PLANTGROUP; }
    
    // Multi Targeting BoardEntity Support
    BoardEntityHeight GetEntityHeight() const override;
    void        TakeDamage(const DamageInfo& i_damage) override;
    void        TakeFatalDamage(const DamageInfo& i_damage) override;
	void		HealByAmount(float i_amount) override;
    bool        NeutralizeSplashDamage() override;
    bool        CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    bool        OverrideProjectileCollision(class Projectile* i_projectile) override;
    
    const std::vector<PlantPtr>& Plants() const { return m_plants.Plants(); }
    
    // Actions
    bool        RelocatePlantsOrKill();
    void        KillVulnerablePlants(DamageTypeFlags i_damageType, BoardEntityHeight i_minEntityHeight, bool i_stopAtInvulnerablePlant, BoardEntity* i_instigator = nullptr);
    void        KillPlants(DamageTypeFlags i_damageType, BoardEntityHeight i_minEntityHeight);
    void        TakeSmashAttack(BoardEntity* i_instigator);
	bool 		CanBeShoveled() override;
    PlantPtr    FindValidPlantToShovel();
    bool        CanApplyPlantfood();
    bool        CanHaveFrost()  { return canHaveFrost(); }
    void        ApplyPlantfood(bool i_broadcastPlantfoodUse);
    void        AttackRelocateGroup(Sexy::Point& i_relocationGrid, pvztime_t i_relocationDuration, float i_relocateApexHeight, RelocationEvent i_relocationEvent);
    void        SetProtectedFromShovel(bool i_protect);
	void 		ApplyConditions(std::vector<PlantConditionEntry>& i_conditions, float i_additionalValue = 0.0f);
    void        ApplyCondition(PlantConditions i_condition, pvztime_t i_duration, float i_additionalValue = 0.0f);
    void        ApplyConversionCondition(PlantConditions i_condition, pvztime_t i_duration = PVZ_EOT(), pvztime_t i_eventDelay = 0);
    void        RevertConversionCondition(PlantConditions i_groupCondition);
    bool        NeedsThawing();

    bool        HasPlantfoodedPlant();
    void        UpdatePlantfoodRendering();
    bool        HasNonRelocatingPlant();
    bool        HasAnyRestrictionSetInclusion(const PlantRestrictionSet& i_restrictionSet) const;
    bool        HasInvinciblePlant();
    bool        HasNoncrushablePlant();
    bool        IsFirstPlantInvincible();   // Possibly convert to CanAttackGroup to handle normal attacks if there are additional useful qualifiers.
    PlantPtr    GetPlantOfClass(std::string i_class) const;
    bool        CanAttackRelocateGroup(const BoardEntity* i_instigator);
    bool        CanBeRangeTargeted();
    bool        CanBeTargetedBy(const BoardEntity* i_entity, bool checkInvincible = false);
    void        PlayChewedOnSound();
    
    // Includelist - All plants match list \ Excludelist - No plants match list
    bool        DoAllPlantsMatchTypeList(const std::vector<std::string>& i_plantTypes, bool i_includelist);
    
    void        SetGridLocation(const Point& i_point);
    Point       GridLocation() { return Point(m_gridX, m_gridY); }
    int         GridX() { return m_gridX; }
    int         GridY() { return m_gridY; }
    bool        IsOnBoard() { return m_isOnBoard; }
    
    // Special Conditions
    bool        IsIceblocked();

    void GatherPlantingRestrictions(const Sexy::Point &i_gridPosition, const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors);

    void SetNewCollisionRect() { invalidateCollisionRect(); GetCollisionRect(); }

protected:
    Rect        calcCollisionRect() override;
    
    int         m_gridX;
    int         m_gridY;
    bool        m_isOnBoard = false;
    bool        m_groupPlantfoodRender = false;
    
private:
    
    void        rebuildCollision();
    bool        canHaveFrost();
    void        fixFrost();
    void        propagateConversionConditionToGroup(PlantConditions i_groupCondition, pvztime_t i_duration, pvztime_t i_eventDelay);

    PlantsSortedByLayer m_plants;
};

#endif
