//
//  ComponentObjectImpactor.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/7/21.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ComponentObjectImpactor_h
#define ComponentObjectImpactor_h

#include "ComponentBase.h"
#include "PropertySheetBase.h"
#include "TimeMgr.h"
#include <deque>
#include "EntityFinder.h"
#include "Projectile.h"

class ComponentObjectImpactorProps : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(ComponentObjectImpactorProps, PropertySheetBase, RtClass);
    ComponentObjectImpactorProps()
    {
        ImpactProjectiles.clear();
        ImpactEffects.clear();
        ImpactGridItems.clear();
    }
    
    std::vector<std::string> ImpactProjectiles;
    std::vector<std::string> ImpactEffects;
    std::vector<std::string> ImpactGridItems;
    
private:
    
};

class ComponentObjectImpactor : public ComponentBase
{
public:
    RT_CLASS_DEFINE(ComponentObjectImpactor, ComponentBase, RtClass);
    
    void SetImpactorProps(const ComponentObjectImpactorProps& i_props) { m_props = i_props; }
    void SetDisabled(const bool& i_disabled) { m_disabled = i_disabled; }
    
protected:
    void onBegin() override;
    void onUpdate() override;
    
    
private:
    void checkProjectileImpact();
    void checkEffectImpact();
    void checkGridItemImpact();
    void calcEffectRectInBoardSpace(const Effect_PopAnim* i_effect, Rect& i_rect, const std::string& i_animName);
    Rect finalizeEffectCollisionRect(const std::string& i_name, Rect i_rect);
    bool isEffectMoving(const std::string& i_name);
    
    
private:
    std::vector<RtWeakPtr<class Projectile> >       m_affectedProjectiles;
    std::vector<RtWeakPtr<class Effect_PopAnim> >   m_affectedEffects;
    std::vector<RtWeakPtr<class GridItem>>          m_affectedGridItems;
    ComponentObjectImpactorProps                    m_props;
    bool                                            m_disabled;
    
};

#endif /* ComponentObjectImpactor_h */
