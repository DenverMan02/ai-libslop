#ifndef __PLANT_TORCHWOOD_H__
#define __PLANT_TORCHWOOD_H__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "ProjectilePropertySheet.h"
#include "RtDb.h"
#include "RtObject.h"
#include "ComponentWarmingRadius.h"
#include "ComponentProjectileConverter.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class TorchwoodProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(TorchwoodProps, PlantPropertySheet, RtClass);
    
    TorchwoodProps()
    {
        
    }
    
    ComponentWarmingRadiusProps NormalWarmingRadius;
    ComponentWarmingRadiusProps PlantfoodWarmingRadius;
    ComponentProjectileConverterProps ProjectileConverterProps;
    ComponentProjectileConverterProps GeneProjectileConverterProps;
};

class PlantTorchwood : public PlantFramework
{

public:
	RT_CLASS_DEFINE(PlantTorchwood, PlantFramework, RtClass);
	
    virtual void            Initialize() override;
	virtual void			UpdateActions() override;
	virtual bool			CanApplyPlantfood() override;
	virtual void			ApplyPlantfood() override;
	
private:
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
    RtWeakPtr<ComponentProjectileConverter> m_projectileConverter;
    RtWeakPtr<ComponentProjectileConverter> m_projectileConverterGene;
};

#endif //__PLANT_TORCHWOOD_H__
