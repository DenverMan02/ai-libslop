

#ifndef EffectObject_DinoTread_hpp
#define EffectObject_DinoTread_hpp

#include "EffectObject.h"
#include "Plant.h"

class EffectObject_DinoTreadProps : public EffectObjectPropertySheet
{
public:
    RT_CLASS_DEFINE(EffectObject_DinoTreadProps, EffectObjectPropertySheet, RtClass);
    
    EffectObject_DinoTreadProps()
    {
        TreadStayTime = 5.0f;
        TreadDamage = 2000;
    }
    pvztime_t	TreadStayTime;
    float TreadDamage;
};

class EffectObject_DinoTread : public EffectObject
{
public:
    RT_CLASS_DEFINE(EffectObject_DinoTread, EffectObject, RtClass);
    EffectObject_DinoTread();
    ~EffectObject_DinoTread();
    
    void	onUpdate() override;
    void    onDestroy() override;
    void	onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
    void	applyDamage();
protected:
    void registerForEvents() override;
    void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
private:
    std::string pickBrambleAnim(const int& i_plantY);
    
    pvztime_t	m_timeToApplyDamage;
    pvztime_t   m_timeToPullBramble;
    int m_row;
    int m_column;
    
    PlantPtr m_cachedBramble;
};

#endif
