//
//  DNodeLoader.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DNodeLoader_h
#define DNodeLoader_h

#include "DNode.h"
#include "DIniFile.h"
#include "PrimeText_Game.h"
#include "DSingleton.h"
#include "DAction.h"

class DNodeLoaderConfig;

class DActionBaseCreator
{
public:
    virtual ~DActionBaseCreator() = default;
    virtual DAction* create() = 0;
    virtual bool loadConfig(DAction* action,DIniField* field,const std::string& actionName,DNodeLoaderConfig* config) = 0;
};

#define DActionCreatorImp(name,parent) \
class name##Creator:public parent##Creator \
{ \
public: \
typedef parent##Creator SuperClass;\
virtual name* create() \
{ \
DRefPtr<name> a;\
a->ref();\
return a.get();\
} \
virtual bool loadConfig(DAction* action,DIniField* field,const std::string& actionName,DNodeLoaderConfig* config);\
name##Creator()\
{\
DNodeLoader::getInstance()->addActionCreator(#name,this);\
}\
};\
static name##Creator s_##name##Creator_instance

#define DActionCreatorImpBase(name) DActionCreatorImp(name,DActionBase)


class DNodeCreator
{
public:
    virtual ~DNodeCreator() = default;
    virtual DTransformNode* create() = 0;
    virtual bool loadConfig(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config) {return true;}
    virtual bool loadConfigAfter(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config) {return true;}
    DVec2 _percentPos,_position;
};

#define DNodeCreatorImp(name,parent) \
class name##Creator:public parent##Creator \
{ \
public: \
typedef parent##Creator SuperClass;\
virtual name* create() \
{ \
    DRefPtr<name> a;\
    a->ref();\
    return a.get();\
} \
virtual bool loadConfig(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config);\
virtual bool loadConfigAfter(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config){return SuperClass::loadConfigAfter(node,field,nodeName,config);}\
name##Creator()\
{\
DNodeLoader::getInstance()->addNodeCreator(#name,this);\
}\
};\
static name##Creator s_##name##Creator_instance

#define DNodeCreatorImp2(name,parent) \
class name##Creator:public parent##Creator \
{ \
public: \
typedef parent##Creator SuperClass;\
virtual name* create() \
{ \
DRefPtr<name> a;\
a->ref();\
return a.get();\
} \
virtual bool loadConfig(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config);\
virtual bool loadConfigAfter(DTransformNode* node,DIniField* field,const std::string& nodeName,DNodeLoaderConfig* config);\
name##Creator()\
{\
DNodeLoader::getInstance()->addNodeCreator(#name,this);\
}\
};\
static name##Creator s_##name##Creator_instance

#define DNodeCreatorImpBase(name) DNodeCreatorImp2(name,DNode)

class DNodeLoader:public DSingleton<DNodeLoader>
{
public:
    DNodeLoader();
    virtual ~DNodeLoader();
    
    void addNodeCreator(const std::string& name,DNodeCreator* creator);
    void addActionCreator(const std::string& name,DActionBaseCreator* creator);
    
    DActionBaseCreator* getActionCreator(const std::string& name);
    DNodeCreator*   getNodeCreator(const std::string& name);
    
    Sexy::PrimeTypeface* getFontType(const std::string& name);
    DTween::TweenType getTweenType(const std::string& name);
    
    void loadFontTypes();
    void loadTweenTypes();
    
    const DVec2& getScreenSize();
    const DVec2& getScreenOffsetPos();
    
private:
    void lazyInitSize();
private:
    std::unordered_map<std::string,PrimeText_PotentialTypeface*> _fontTypeDict;
    std::unordered_map<std::string,DTween::TweenType> _tweenTypeDict;
    std::unordered_map<std::string, DNodeCreator*> _factory;
    std::unordered_map<std::string, DActionBaseCreator*> _actionFactory;
    
    DVec2    _screenSize;
    DVec2    _screenOffsetPos;
    
    bool     _isLoadScreenSize = false;
    bool     _isLoadFontTypes = false;
    bool     _isLoadTweenTypes = false;
};

class DNodeLoaderConfig
{
public:
    DNodeLoaderConfig() = default;
    bool loadFromStringData(const std::string& stringData);
    bool loadFile(const std::string& fileName,bool isDocument = true);
    
    DRefPtr<DTransformNode> loadNode(const std::string& nodeName,DTransformNode* parent = nullptr);
    std::vector<std::string> getGroups(const std::string& group);
    template<class T>
    DRefPtr<T> loadNode(const std::string& nodeName,DTransformNode* parent = nullptr){return dynamic_pointer_cast<T>(loadNode(nodeName,parent));}
    
    DRefPtr<DAction> loadAction(const std::string& actionName);
    
    template<class T>
    DRefPtr<T> loadAction(const std::string& actionName){return dynamic_pointer_cast<T>(loadAction(actionName));}
    
    bool saveFile();
    
private:
    DIniFile _ini;
};

#endif
