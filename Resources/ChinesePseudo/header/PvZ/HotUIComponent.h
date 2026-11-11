//
//  HotUIComponent.h
//  PvZ2
//
//  Created by Sola, Joseph on 11/1/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef HotUIComponent_h
#define HotUIComponent_h

#include "HotUIWidget.h"

class HotUIComponent : public RtObject
{
public:
    RT_CLASS_DEFINE(HotUIComponent, RtObject, RtClass);
    
    void InitializeComponent(HotUIComponentPtr i_thisPtr, HotUIComponentPropertiesPtr i_props);
    void AddTarget(HotUIWidgetPtr i_target);
    
    virtual void Update();
    
    HotUIComponentPtr GetPtr() const
    {
        return m_thisPtr;
    };
    const HotUIComponentProperties* GetProps() const
    {
        return getProps();
    };
    
protected:
    virtual void onInitializeComponent() {}
    
    const HotUIComponentPropertiesPtr getPropsPtr() const
    {
        DBG_ASSERT(m_propertySheetPtr.IsValid());
        return m_propertySheetPtr;
    }
    
    const HotUIComponentProperties* getProps() const
    {
        DBG_ASSERT(m_propertySheetPtr.IsValid());
        return m_propertySheetPtr.Get();
    }
    
    const std::vector<HotUIWidgetPtr>& getTargets() const
    {
        return m_targets;
    }
    
    template <typename T>
    inline const T* getProps() const;
    
private:
    HotUIComponentPtr               m_thisPtr;
    HotUIComponentPropertiesPtr     m_propertySheetPtr;
    std::vector<HotUIWidgetPtr>     m_targets;
};

class HotUIComponentProperties : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(HotUIComponentProperties, PropertySheetBase, RtClass);
    
    HotUIComponentProperties()
    {
        Name = "";
    }
    
    virtual RtClass* GetComponentClass() const
    {
        return HotUIComponent::StaticGetClass();
    }
    
    std::string         Name;
    std::vector<RtId>   Targets;
};

template <typename T>
inline const T* HotUIComponent::getProps() const
{
    const HotUIComponentProperties* props = getProps();
    const T* typedProps = props->CastChecked<const T>();
    return typedProps;
}

#endif /* HotUIComponent_h */
