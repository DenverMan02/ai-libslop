//
//  DComponent.h
//  DCore
//
//  Created by lzjseed on 16/2/26.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DComponent_h
#define DComponent_h

#include "DRef.h"
#include <string>
#include <unordered_map>

class DTransformNode;

class DComponent:public DRef
{
public:
    bool isEnabled() const { return m_bEnabled; }
    virtual void setEnabled(bool enabled);
    
    const std::string& getName() const { return m_name; }
    virtual void setName(const std::string& name) { m_name = name; }
    
    DTransformNode* getOwner() const { return m_pOwner; }
    virtual void setOwner(DTransformNode *owner);
    
    virtual void onUpdate();
    virtual void onAdd();
    virtual void onRemove();
    
protected:
    DTransformNode* m_pOwner;
    std::string m_name;
    bool    m_bEnabled;
};

class DComponentContainer
{
protected:
    DComponentContainer(DTransformNode* node);
    
public:
    ~DComponentContainer();
    
    DComponent* get(const std::string& name) const;
    
    bool add(DComponent *com);
    bool remove(const std::string& name);
    bool remove(DComponent *com);
    void removeAll();
    void visit();
    
    bool isEmpty() const { return m_componentMap.empty(); }
private:
    std::unordered_map<std::string, DComponent*> m_componentMap;
    DTransformNode *m_pOwner;
    
    friend class DTransformNode;
};

#endif
