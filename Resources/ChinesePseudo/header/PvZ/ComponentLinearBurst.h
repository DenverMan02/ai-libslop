#ifndef __PlantsVersusZombies2__ComponentLinearBurst__
#define __PlantsVersusZombies2__ComponentLinearBurst__

#include "ComponentBase.h"
#include "PropertySheetBase.h"
#include "StandaloneEffect.h"
#include "EntityFinder.h"
#include "DamageInfoProps.h"
#include "TargetInfoProps.h"

class Plant;
class BoardEntity;

#define INITIAL_PLANT_LEVEL 1

class DamageWithWeight
{
public:
    int Weight;
    int PlantLevel;
    DamageInfoProps DamageProps;
    
    DamageWithWeight()
    : Weight(100)
    , PlantLevel(1)
    {}
};

class ComponentLinearBurstProps
{
public:
    ComponentLinearBurstProps()
    : TimeBetweenGridHits{0.f}
    , InitialDelay{0.0f}
    {}
    
    Rect GridAreaForAnimation;
    Rect BoardAreaForDamage;
    float TimeBetweenGridHits;
    float InitialDelay;
    TargetInfoProps TargetProps;
    std::string  PopAnimLinearEffectName;
    std::string  PopAnimSquareEffectName;
    
    std::vector<DamageWithWeight> DamagePropsVec;
};

class ComponentLinearBurst : public ComponentBase
{
public:
    RT_CLASS_DEFINE(ComponentLinearBurst, ComponentBase, RtClass);

    
    ComponentLinearBurst()
    :m_distanceOfBurst(0)
    {}
    
    void SetProps(const ComponentLinearBurstProps& i_props);
    void StartPulse();
    
    void GetPlantsInArea(std::vector<BoardEntity*>& o_touchedEntities);
    void GetGridItemsInArea(std::vector<BoardEntity*>& o_touchedEntities);
    void GetZombiesInArea(std::vector<BoardEntity*>& o_touchedEntities);
    
protected:
    void getEntitiesInArea(std::vector<BoardEntity*>& o_touchedEntities, BoardEntityTypeFlag i_acceptedTypes);
    
    void onBegin() override;
    void onUpdate() override;
    
private:
    Rect calcCurrentDamageArea();
    Rect calcCurrentAnimationArea();
    
    void createValidEffectsFor(Rect gridArea, std::string popAnimName);
    
    bool shouldAdvanceColumn();
    
    Rect advanceColumn();
    Rect calculateWhichColumnToEffect();
    
    void damageEntities();
    DamageInfo createDamageInfo();
    void accountForDealingDamageEachColumnDraw(DamageInfo& damageInfo);
    
    void createLineOfSquareEffects(Rect area);
    void createEffectAt(Rect origin, const std::string& i_popanimName);
    
    pvztime_t m_nextCreateColumnEffectTime;
    int	m_distanceOfBurst;
    ComponentLinearBurstProps m_props;
    
};

#endif /* defined(__PlantsVersusZombies2__ComponentLinearBurst__) */
