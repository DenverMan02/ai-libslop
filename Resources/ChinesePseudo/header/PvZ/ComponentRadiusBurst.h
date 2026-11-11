#ifndef __PlantsVersusZombies2__ComponentRadiusBurst__
#define __PlantsVersusZombies2__ComponentRadiusBurst__

#include "ComponentBase.h"
#include "PropertySheetBase.h"
#include "StandaloneEffect.h"
#include "TimeMgr.h"
#include "DamageInfo.h"
#include <deque>
#include "EntityFinder.h"
#include "DamageInfoProps.h"
#include "TargetInfoProps.h"

class Plant;
class BoardEntity;

class ComponentRadiusBurstProps
{
public:
    ComponentRadiusBurstProps()
    : RadiusInGridSquareWidths{0.f}
    , PulseCooldown{0.f}
    , PulsePropagationTime{0.f}
    , PopAnimScaleX{1.0f}
    , PopAnimScaleY{1.0f}
    , PopAnimOffset{Sexy::Point(0.f, 0.f) }
    , PopAnimEffectStartDelay{0.0f}
    , RenderAtEffectLayer{false}
    {}
    
    float	RadiusInGridSquareWidths;
    float	PulseCooldown;
    float	PulsePropagationTime;
    std::string  PopAnimEffectName;
    float	PopAnimScaleX;
    float	PopAnimScaleY;
    Sexy::Point	PopAnimOffset;
    float	PopAnimEffectStartDelay;
    TargetInfoProps TargetProps;
    bool RenderAtEffectLayer;
};

class ComponentRadiusBurst : public ComponentBase
{
public:
    RT_CLASS_DEFINE_ABSTRACT(ComponentRadiusBurst, ComponentBase, RtClass);
    
    ComponentRadiusBurst()
    : m_nextPropagateTime{PVZ_EOT()}
    , m_nextApplyTime{PVZ_EOT()}
    , m_nextAnimationStartTime{PVZ_EOT()}
    , m_isOriginDisplaced(false)
    , m_displacedOrigin(-1, -1)
    , m_completionCallback()
    {}
    
    void SetRadiusProps(const ComponentRadiusBurstProps& i_props);
    virtual void GetPlantsInRadius(std::vector<BoardEntity*>& o_touchedEntities);
    virtual void GetGridItemsInRadius(std::vector<BoardEntity*>& o_touchedEntities);
    virtual void GetZombiesInRadius(std::vector<BoardEntity*>& o_touchedEntities);
    virtual void GetPlantGroupsInRadius(std::vector<BoardEntity*>& o_touchedEntities);  
    
    void SetDisplacedOrigin(Sexy::Point i_gridOrigin);
    void SetBurstCompletionCallback(RtReflectionDelegate<Delegate0> i_callback) { m_completionCallback = i_callback; }
    
protected:
    virtual void beginCoolDown() = 0;
    virtual void beginApply() = 0;
    virtual void beginPropagate();
    virtual void onAnimationTriggered(){}
    
    void onBegin() override;
    void onUpdate() override;
    
    void getEntitiesInRadius(std::vector<BoardEntity*>& o_touchedEntities, BoardEntityTypeFlag i_acceptedTypes);
    void updateTimes(pvztime_t nextPropigate);
    void calculateTimeForNextPropigate();
    float radiusInBoardSpace();
    void pausePropagation();
    Sexy::Point getOwnerOrigin();
    
    void onBurstCompleted();
    
    bool m_isOriginDisplaced;
    Sexy::Point m_displacedOrigin;
    Sexy::Point	m_gridOrigin;
    
protected:
    bool calculateOrigin();
    void createRadiusEffect(Sexy::Point origin, const std::string& i_popanimName);
    
    RtReflectionDelegate<Delegate0> m_completionCallback;
    
    ComponentRadiusBurstProps m_props;
    pvztime_t	m_nextPropagateTime;
    pvztime_t	m_nextApplyTime;
    pvztime_t	m_nextAnimationStartTime;
};

#endif /* defined(__PlantsVersusZombies2__ComponentEffectRadius__) */
