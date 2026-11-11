//
//  DNodeWidget.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DNodeWidget_h
#define DNodeWidget_h

#include "Widget.h"
#include "DEngine.h"

class DEditorNode:public DTransformNode
{
protected:
    DEditorNode() = default;
public:
    virtual ~DEditorNode();
    
    friend class DRefPtr<DEditorNode>;
    
    void load(const std::string& configName,bool editorMode);
    void reload(const std::string& configName);
    void reload();
    
    void loadGroup(const std::string& name);
    void removeAllLoadedGroups();
    
    void setRootName(const std::string& name) {m_rootName = name;}
    const std::string& getRootName()const {return m_rootName;}
    
    DNodeLoaderConfig& getLoader(){return loader;}
    
    bool isEditorMode() const {return m_isEditorMode;}
    
protected:
    
    DNodeLoaderConfig        loader;
    std::string              m_rootName = "root";
    std::string              m_configName;
    bool                     m_isEditorMode = false;
    std::vector<std::string> m_loadGroupNames;
};

#define CREATE_FUNC(type) \
public: \
static type* create(bool focus = true)\
{\
    auto p = new type();\
    if(p)\
    {\
        p->Initialize();\
        p->UserInit();\
        p->addToWidgetManager(focus);\
    }\
    return p;\
}

#define CREATE_SINGLETON_FUNC(type) \
public: \
static type* create(bool focus = true)\
{\
    if(!s_pSingleton) \
    { \
        auto p = new type();\
        if(p)\
        {\
            p->Initialize();\
            p->UserInit();\
            p->addToWidgetManager(focus);\
            s_pSingleton = p;\
        }\
        return p;\
    } \
    else \
    {\
        return s_pSingleton;\
    }\
}\
static bool isActive() {return s_pSingleton != nullptr;}\
static void remove()\
{\
    if(s_pSingleton)\
    {\
        s_pSingleton->removeFromWidgetManager();\
        s_pSingleton = nullptr;\
    }\
}\
static type* s_pSingleton;

#define INIT_SINGLETON(type) type* type::s_pSingleton = nullptr;

class DNetwork: public DSingleton<DNetwork>
{
public:
	DNetwork();
	virtual ~DNetwork();

    bool  requestMsg(const std::string& msgId,std::map<std::string,std::string>& params,float timeout,const std::function<void(const std::string&)>& response,bool wait=true,
    		bool requestPid=true, const std::string& i_hint = "[NET_CONNECTING]", int i_reconnectTimes = 0);
    void removeRequestMsg(const std::string& msgId);
    void flush(const std::string& msgId);

private:
    bool requestNetworkMsg(const std::string& msgId, std::map<std::string,std::string>& params, float timeout, const std::function<void(const std::string&)>& response, bool wait, bool requestPid);
    void onServerMsgError(const std::string& i_reqID);

    std::map<std::string, int> m_reconnectInfos;
};

class DNodeWidget : public Sexy::Widget
{
    RT_CLASS_DEFINE(DNodeWidget, Widget, RtClass);
public:
    CREATE_FUNC(DNodeWidget)
    
    DNodeWidget();
    
    virtual ~DNodeWidget();
    
    void load(const std::string& configName, bool editorMode);
    void reload(const std::string& configName);
    void debugBtn();
    void reload();
    
    virtual void Initialize();
    
    virtual void UserInit();
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    
    virtual DVec2 getWinSize();
    
    virtual void  setRect(int x,int y ,int w,int h);
    virtual void  setRect2(int x,int y ,int w,int h);
    
    virtual void  addToWidgetManager(bool focus = true);
    virtual void  addToWidgetManager(bool focus,bool bringToFront);
    virtual void  removeFromWidgetManager();
    
    virtual void  OnGestureLongPress(Sexy::Point i_startingLocation);

    virtual void  TouchBegan( const Sexy::Touch& touch ) override;
    virtual void  TouchMoved( const Sexy::Touch& touch ) override;
    virtual void  TouchEnded( const Sexy::Touch& touch ) override;
    virtual void  TouchesCanceled() override;
    
    virtual void setTouchEnable(bool enable){m_bTouchEnable = enable;}
    virtual bool isTouchEnable()const{return m_bTouchEnable;}
    
    virtual void addChild(DTransformNode* child,int tag,int zOrder);
    virtual void addChild(DTransformNode* child,int zOrder);
    virtual void addChild(DTransformNode* child);
    virtual DTransformNode* getChildByTag(int tag);
    virtual DTransformNode* getChildByName(const std::string& name);
    
    virtual void removeAllChildren(bool cleanup = true);
    virtual void removeChild(DTransformNode* child,bool cleanup = true);
    virtual void removeChildByTag(int tag,bool cleanup = true);
    virtual void removeChildByName(const std::string& name,bool cleanup = true);
    
    void setRootName(const std::string& name) {mainNode->setRootName(name);}
    const std::string& getRootName()const {return mainNode->getRootName();}
    
    void loadGroup(const std::string& name);
    DNodeLoaderConfig& getLoader(){return mainNode->getLoader();}
    
protected:
    DRefPtr<DEditorNode>     mainNode;
    DTouchEventDispatcher    m_touchDispatcher;
    bool                     m_bTouchEnable = true;
};

#endif
