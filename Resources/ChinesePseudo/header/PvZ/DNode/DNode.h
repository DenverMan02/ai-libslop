//
//  DNode.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DNode_h
#define DNode_h

#include "DInclude.h"
#include "Color.h"
#include "Graphics.h"
#include "DMath.h"
#include "DArray.h"
#include "DComponent.h"
#include <stack>
#include "SexyAppFramework/SexyAppBase.h"
#include "SexyAppFramework/RenderEffect.h"

using namespace Sexy;

#define D_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define D_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define D_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define D_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)

class DColor
{
public:
    DColor()
    :m_color(Color::White)
    ,m_displayColor(Color::White)
    {}
    virtual DColor& setColor(const Color& color)
    {
        m_color = color;
        m_displayColor = color;
        
        return *this;
    }
    
    virtual DColor& setColor(int r,int g,int b,int a)
    {
        m_color.mRed = r;
        m_color.mGreen = g;
        m_color.mBlue = b;
        m_color.mAlpha = a;
        
        m_displayColor = m_color;
        
        return *this;
    }
    
    virtual DColor& setRGB(int r,int g,int b)
    {
        m_color.mRed = r;
        m_color.mGreen = g;
        m_color.mBlue = b;
        
        m_displayColor = m_color;
        return *this;
    }
    
    virtual DColor& setAlpha(int a)
    {
        m_color.mAlpha = a;
        
        m_displayColor = m_color;
        return *this;
    }
    
    virtual const Color& getColor()const {return m_color;}
    
protected:
    Color       m_color;
    Color       m_displayColor;
};

class DTransformNode:public DRef,public DColor
{
protected:
    DTransformNode();
public:
    virtual ~DTransformNode();
    
    virtual void visit(Graphics* i_g) final;
    virtual void visit(const DMatrix& parentMatrix,Graphics* i_g,bool isDirty);
    virtual void addChild(DTransformNode* child,int tag,int zOrder);
    virtual void addChild(DTransformNode* child,int zOrder);
    virtual void addChild(DTransformNode* child);
    virtual DTransformNode* getChildByTag(int tag);
    virtual DTransformNode* getChildByName(const std::string& name);
    
    template<typename  T>
    inline  T getChildByTag(int tag){ return DYNAMIC_CAST<T>(getChildByTag(tag));}
    
    template<typename  T>
    inline  T getChildByName(const std::string& name){ return DYNAMIC_CAST<T>(getChildByName(name));}
    
    
    virtual std::vector<DTransformNode*> getChildrenByTag(int tag);
    virtual std::vector<DTransformNode*> getChildrenByName(const std::string& name);
    
    virtual DTransformNode* getChildRecursionByName(const std::string& name);
    
    template<typename  T>
    inline  T getChildRecursionByName(const std::string& name){ return DYNAMIC_CAST<T>(getChildRecursionByName(name));}
    
    virtual void removeFromParent(bool cleanup = true);
    virtual void removeAllChildren(bool cleanup = true);
    virtual void removeChild(DTransformNode* child,bool cleanup = true);
    virtual void removeChildByTag(int tag,bool cleanup = true);
    virtual void removeChildByName(const std::string& name,bool cleanup = true);
    
    virtual void draw(const DMatrix& mat,Graphics* i_g);
    
    virtual const DMatrix& getNodeTransform();
    virtual DMatrix getNodeToParentTransform(DTransformNode* ancestor);
    virtual DMatrix getNodeToWorldTransform();
    virtual DMatrix getWorldToNodeTransform();
    
    virtual DVec2   convertTouchToNodeSpace(const Sexy::Touch& touch);
    virtual DVec2   convertToNodeSpace(const DVec2& worldPoint);
    virtual DVec2   convertToWorldSpace(const DVec2& nodePoint);
    
    virtual DVec2   getAlign(const DVec2& alignPoint);
    virtual DVec2   getAlign(float x,float y);
    
    virtual DTransformNode& setVisible(bool visible);
    virtual bool isVisible() const;
    
    virtual int   getTag()const {return m_tag;}
    virtual DTransformNode&  setTag(int tag) {m_tag = tag; return *this;}
    virtual int   getZOrder()const {return m_zOrder;}
    virtual DTransformNode&  setZOrder(int z);
    virtual DTransformNode&  setPosition(const DVec2& pos);
    virtual DTransformNode&  setPosition(float x,float y);
    virtual DTransformNode&  setPositionX(float x);
    virtual DTransformNode&  setPositionY(float y);
    virtual DTransformNode&  setAnchorPoint(const DVec2& anchor);
    virtual DTransformNode&  setAnchorPoint(float x,float y);
    virtual DTransformNode&  setContextRect(float x,float y,float width,float height);
    virtual DTransformNode&  setScale(float s);
    virtual DTransformNode&  setScale(float sx,float sy);
    virtual DTransformNode&  setScaleX(float sx);
    virtual DTransformNode&  setScaleY(float sy);
    virtual DTransformNode&  scaleToSize(float width,float height);
    virtual DTransformNode&  scaleToHeight(float height);
    virtual DTransformNode&  scaleToWidth(float width);
    virtual DTransformNode&  setRotation(float angle);
    virtual DTransformNode&  setRotationPoint(const DVec2& pos);
    virtual DTransformNode&  setRotationPoint(float x,float y);
    virtual DTransformNode&  resetRotationPoint();
    virtual DTransformNode&  ignoreAnchorPointForPosition(bool isIgnoreAnchorPoint);
    virtual DTransformNode&	 setNoCast(bool i_noCast);
    bool 					 isNoCast()const;
    virtual bool  isIgnoreAnchorPointForPosition()const;
    virtual const DVec2  getRotationPoint()const;
    virtual const DVec2& getPosition()const;
    virtual float getPositionX()const;
    virtual float getPositionY()const;
    virtual float getScaleX()const;
    virtual float getScaleY()const;
    virtual const DVec2& getScaleXY()const;
    virtual float getScale()const;
    virtual float getRotation()const;
    virtual const FRect& getContextRect()const;
    virtual const DVec2& getAnchorPoint()const;
    virtual const DVec2& getAnchorPointSize()const;
    
    virtual DTransformNode& setContentSize(const DVec2 & size);
    virtual DVec2 getContentSize() const ;
    
    virtual ssize_t getChildrenCount() const{return m_children.size();}
    virtual DArray<DTransformNode*>& getChildren() {return m_children;}
    virtual const DArray<DTransformNode*>& getChildren() const {return m_children;}
    virtual DTransformNode* getParent()const {return m_parent;}
    virtual DTransformNode& setParent(DTransformNode* parent) {m_parent = parent; return *this;}
    virtual DTransformNode&  setCascadeColorEnabled(bool isEnable) ;
    virtual bool  isCascadeColorEnabled()const ;
    virtual DTransformNode&  setCascadeOpacityEnabled(bool isEnable) ;
    virtual bool  isCascadeOpacityEnabled()const ;
    
    virtual DTransformNode&  setColor(const Color& color) ;
    virtual DTransformNode&  setColor(int r,int g,int b,int a) ;
    virtual DTransformNode&  setRGB(int r,int g,int b) ;
    virtual DTransformNode&  setAlpha(int a) ;
    
    const std::string& getName() const;
    DTransformNode& setName(const std::string& name);
    
    virtual bool isActionRunning();
    virtual size_t getActionNumber();
    virtual void runAction(class DAction* action);
    virtual void stopAction(DAction* action);
    virtual void stopAllActions();
    
    virtual DComponent* getComponent(const std::string& name);
    
    virtual bool addComponent(DComponent *component);
    
    virtual bool removeComponent(const std::string& name);
    
    virtual bool removeComponent(DComponent *component);
    
    virtual void removeAllComponents();
    
    virtual void setRenderEffect(RenderEffectDefinition* effect);
    virtual void setRenderEffect(const std::string& effectName);
    
    virtual DTransformNode& setResource(const std::string& name){return *this;}
    
    virtual void cleanup();
    virtual void setTouchDispatcher(class DTouchEventDispatcher* touchDispatcher);
    virtual class DTouchEventDispatcher* getTouchDispatcher();
    virtual void onActive();

    void SetTransformParentDirtyCall(bool i_transformParentDirtyCall)
	{
		m_bTransformParentDirtyCall = i_transformParentDirtyCall;
	}

	void SetNeedTransform(bool i_needTransform)
	{
		m_bNeedTransform = i_needTransform;
	}

protected:
    void sortAllChildren();
    virtual void _setCascadeColor(float r,float g,float b);
    virtual void _setCascadeOpacity(float a);
    virtual void ___setCascadeColor(float r,float g,float b);
    virtual void ___setCascadeOpacity(float a);
    
    void _detachChild(DArray<DTransformNode*>::iterator &iter,bool cleanup);
    
    int getOrderOfArrival() const
    {
        return m_orderOfArrival;
    }
    
    void setOrderOfArrival(int orderOfArrival)
    {
        m_orderOfArrival = orderOfArrival;
    }

protected:
    class DTouchEventDispatcher* m_touchDispatcher = nullptr;
    DComponentContainer m_componentContainer;
    bool        m_ignoreAnchorPointForPosition = false;
    bool		m_cascadeColorEnabled = false;
    bool        m_cascadeOpacityEnabled = false;
    std::string m_name;
    size_t      m_hashOfName = 0;
    DTransformNode* m_parent = nullptr;
    DArray<DTransformNode*> m_children;
    RenderEffectDefinition* m_renderEffect = nullptr;
    DVec2   m_anchorPoint;
    DVec2   m_anchorPointSize;
    DVec2   m_rotatePoint;
    FRect   m_contextRect;
    DVec2   m_pos;
    DVec2   m_scale;
    
    static int g_orderOfArrival;
    
    float   m_rotate = 0.0f;
    int     m_tag = -1;
    int     m_zOrder = 0;
    int     m_orderOfArrival = 0;
    bool    m_bTransformParentDirtyCall = true;
    bool    m_bTransformDirty = true;
    bool    m_bReorderChildDirty = false;
    bool    m_bNeedTransform = true;
    bool    m_bIsVisible = true;
    mutable DMatrix m_transform;
    mutable DMatrix m_modelViewTransform;
    
    class DActionManager* m_pActionMgr;
    bool 	m_noCast = false;
    //static  std::stack<DMatrix> s_matrixStack;
    
    friend class DRefPtr<DTransformNode>;
};

class DSpriteNode:public DTransformNode
{
public:
    DSpriteNode();
public:
    virtual ~DSpriteNode(){}
    virtual DSpriteNode& setResource(const std::string& name) override;
    virtual void draw(const DMatrix& mat,Graphics* i_g)override;
    
    virtual DSpriteNode& setResource(Image* img);
protected:
    Image*    m_pImage = nullptr;
    
    friend class DRefPtr<DSpriteNode>;
};

class DAtlasSpriteNode:public DSpriteNode
{
protected:
    DAtlasSpriteNode() = default;
public:
    virtual ~DAtlasSpriteNode(){}
    virtual void draw(const DMatrix& mat,Graphics* i_g)override;
    
    virtual const DMatrix& getNodeTransform()override;
    using DSpriteNode::setResource;
    virtual DAtlasSpriteNode& setResource(const std::string& name) override;
    virtual DAtlasSpriteNode& setResource(const std::string& name,bool isAtlas);
    virtual DAtlasSpriteNode& setResource(Image* img,const Rect& rect);
    virtual DAtlasSpriteNode& setResource(const std::string& name,const Rect& rect);
    
protected:
    FRect   m_realContextRect;
    DVec2   m_offsetPos;
    
    friend class DRefPtr<DAtlasSpriteNode>;
};

class DSprite9SliceNode:public DSpriteNode
{
protected:
    DSprite9SliceNode() = default;
public:
    virtual ~DSprite9SliceNode() = default;
    virtual DSprite9SliceNode& setResource(const std::string& name) override;
    virtual void draw(const DMatrix& mat,Graphics* i_g)override;
    
    virtual DSprite9SliceNode& setResource(Image* img) override;
    
    friend class DRefPtr<DSprite9SliceNode>;
};

class DLayer:public DTransformNode
{
protected:
    DLayer() = default;
public:
    virtual ~DLayer() = default;
    
    virtual void draw(const DMatrix& mat,Graphics* i_g) override;
    
    friend class DRefPtr<DLayer>;
};

class DSpriteStringNode:public DTransformNode
{
protected:
    DSpriteStringNode() = default;
public:
    virtual ~DSpriteStringNode() = default;
    
    virtual DSpriteStringNode& setResourceLib(const std::unordered_map<std::string, std::string>& lib);
    
    virtual DSpriteStringNode& setString(const char* string);
    
    virtual std::string getString(){return m_string;}
    
    friend class DRefPtr<DSpriteStringNode>;
    
protected:
    std::unordered_map<std::string, std::string> m_resConfig;
    std::string m_string;
};

#endif /* DNode_h */
