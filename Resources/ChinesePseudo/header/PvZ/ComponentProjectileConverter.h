//
//  ComponentProjectileConverter.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/7/20.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ComponentProjectileConverter_h
#define ComponentProjectileConverter_h

#include "ComponentBase.h"
#include "PropertySheetBase.h"
#include "TimeMgr.h"
#include <deque>
#include "EntityFinder.h"
#include "Projectile.h"
#include "Plant.h"

struct ConvertProjectileNode
{
    ConvertProjectileNode()
    {
        InputType = NULL;
        OutputType = NULL;
        OutputTypePtr = ProjectilePropertySheetPtr();
        AdvOutputType = NULL;
        AdvOutputTypePtr = ProjectilePropertySheetPtr();
    }
    ProjectilePropertySheet*	InputType;			// source projectile sheet
    ProjectilePropertySheet*	OutputType;			// destination projectile sheet to turn into
    ProjectilePropertySheetPtr	OutputTypePtr;		// destination projectile sheet to turn into
    ProjectilePropertySheet*	AdvOutputType;		// destination projectile sheet to turn into while in advanced mode.
    ProjectilePropertySheetPtr	AdvOutputTypePtr;	// destination projectile sheet to turn into while in advanced mode.
};

class ComponentProjectileConverterProps : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(ComponentProjectileConverterProps, PropertySheetBase, RtClass);
    ComponentProjectileConverterProps()
    {
        ConvertProjectiles.clear();
    }
    
    std::vector<ConvertProjectileNameNode> ConvertProjectiles;
    
private:
    
};

enum ConverterLevel
{
    ConverterLevel_Normal = 0,
    ConverterLevel_Advanced,
    ConverterLevel_Avatar,
};

enum ConverterType
{
    ConverterType_Normal = 0,
    ConverterType_Gene,
};

class ComponentProjectileConverter : public ComponentBase
{
public:
    RT_CLASS_DEFINE(ComponentProjectileConverter, ComponentBase, RtClass);

    ComponentProjectileConverter();
    
    void SetConverterProps(const ComponentProjectileConverterProps& i_props) { m_props = i_props; }
    void SetDisabled(const bool& i_disabled) { m_disabled = i_disabled; }
    void SetPlantAttackRect(Plant* i_plant, PlantWeapon i_weapon);
    void SetConvererLevel(const ConverterLevel& i_level) { m_convererLevel = i_level; }
    void SetConvererType(const ConverterType& i_type) { m_convertType = i_type; }
    void SetExtraDamageRate(float i_extraRate) { m_extraDamageRate = i_extraRate; }
    void ClearProjectileConversionList() { k_convertProjectileList.clear(); }
    
protected:
    void onBegin() override;
    void onUpdate() override;
    
    
private:
    void buildProjectileConversionList();
    void convertProjectile(Projectile* i_projectile, ProjectilePropertySheetPtr i_newProperties);
    Rect getPlantCollisionRect(Plant* i_plant);
    
private:
    std::vector<RtWeakPtr<class Projectile> >		m_affectedProjectiles;
    std::vector<ConvertProjectileNode>              k_convertProjectileList;
    ComponentProjectileConverterProps               m_props;
    bool                                            m_disabled;
    Rect                                            m_attackRect;
    ConverterLevel                                  m_convererLevel;
    ConverterType                                   m_convertType;
    float                                           m_extraDamageRate;

};


#endif /* ComponentProjectileConverter_h */
