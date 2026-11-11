

#ifndef PlantTypeVine_h
#define PlantTypeVine_h

#include "RtObject.h"
#include "PlantType.h"
#include "Plant.h"
#include "PlantStatefulFramework.hpp"
#include "PlantUtils.h"
#include "Projectile.h"

class PlantTypeVine : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeVine, PlantType, RtClass);
    virtual bool CanPlantOnPlant(Plant* plant) const override;
    virtual void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const;
	virtual bool IsVine()const {return true;}


};

class PlantVineFramework : public PlantStatefulFramework
{
public:
    RT_CLASS_DEFINE(PlantVineFramework, PlantStatefulFramework, RtClass);
    PlantVineFramework();
    virtual                 ~PlantVineFramework();    
    virtual void            Initialize();
    virtual void            CheckMainPlant();
    virtual bool            IsVine()                        { return true; }
    virtual void            UpdateUnconditionally();
    PlantPtr                GetBasePlant()                  { return m_basePlant; }

protected:
    void         SetCheckDuration(pvztime_t i_checkDuration) {m_checkDuration = i_checkDuration;}    
    virtual void onPlantPlaced(Plant* i_plant) {}
    virtual void onPlantDied(Plant* i_plant) {}
    virtual void onBoostPlant(Plant* i_plant) {}
    
    PlantPtr  m_basePlant;    
    pvztime_t m_checkDuration;
    pvztime_t m_deadTime;
    pvztime_t m_flashTime;
private:    
    void plantPlaced(Plant* i_plant);
    void plantDied(Plant* i_plant);
    void getBasePlant();
};

#endif
