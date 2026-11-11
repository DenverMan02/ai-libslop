//
//  DAction.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DAction_h
#define DAction_h

#include "DNode.h"
#include <map>

class DTween
{
public:
    enum TweenType
    {
        CUSTOM_EASING = -1,
        
        Linear = 0,
        
        Sine_EaseIn,
        Sine_EaseOut,
        Sine_EaseInOut,
        
        
        Quad_EaseIn,
        Quad_EaseOut,
        Quad_EaseInOut,
        
        Cubic_EaseIn,
        Cubic_EaseOut,
        Cubic_EaseInOut,
        
        Quart_EaseIn,
        Quart_EaseOut,
        Quart_EaseInOut,
        
        Quint_EaseIn,
        Quint_EaseOut,
        Quint_EaseInOut,
        
        Expo_EaseIn,
        Expo_EaseOut,
        Expo_EaseInOut,
        
        Circ_EaseIn,
        Circ_EaseOut,
        Circ_EaseInOut,
        
        Elastic_EaseIn,
        Elastic_EaseOut,
        Elastic_EaseInOut,
        
        Back_EaseIn,
        Back_EaseOut,
        Back_EaseInOut,
        
        Bounce_EaseIn,
        Bounce_EaseOut,
        Bounce_EaseInOut,
        
        TWEEN_EASING_MAX = 10000
    };
    
    static float tweenTo(float time, TweenType type, const std::vector<float>& easingParam);
};

class DAction:public DRef
{
protected:
    DAction();
public:
    virtual ~DAction();
    
    virtual void setTarget(DTransformNode* target);
    virtual DTransformNode* getTarget()const;
    
    virtual void update(float dt);
    virtual void timeStep(float dt){};
    virtual bool isDone()const;
    
    inline size_t getRepeatTime() const {return m_repeatTime;}
    
    inline DAction&  setRepeatTime(size_t repeat)
    {
        m_repeatTime = repeat;
        
        return *this;
    }
    
    inline float getDelayTime() const {return m_delayTime;}
    
    inline DAction&  setDelayTime(float delay)
    {
        m_delayTime = delay;
        if(delay > 0.0f)
        {
            m_bDelayTime = true;
        }
        else
        {
            m_bDelayTime = false;
        }
        
        return *this;
    }
    
    inline DAction&  setDuration(float duration) { m_duration = duration; return *this;}
    
    inline float getDuration() const { return m_duration; }
    
    inline DAction& onDone(const std::function<void(DTransformNode*)> &func){m_function = func; return (*this);}
    
    inline DAction& setTween(DTween::TweenType type)
    {
        m_tweenType = type;
        if(m_tweenParams.size() > 0)
        {
            m_tweenParams.clear();
        }
        return *this;
    }
    
    inline DAction&  setTween(DTween::TweenType type,const std::vector<float>& params)
    {
        m_tweenType = type;
        m_tweenParams = params;
        
        return *this;
    }
    
    inline DAction& setTween(const std::function<float(float)>& func)
    {
        m_tweenFunction = func;
        return *this;
    }
    
public:
    DRefPtr<DAction> clone() const { auto b = _copy(); DRefPtr<DAction> a(b); return a; }
    
protected:
    virtual DAction* _copy() const { auto a = new DAction(); *a = *this; return a;}
    
protected:
    
    std::function<void(DTransformNode*)>   m_function;
    std::vector<float>                     m_tweenParams;
    DTween::TweenType                      m_tweenType;
    std::function<float(float)>            m_tweenFunction;
    size_t                                 m_repeatTime;
    float                                  m_delayTime;
    float                                  m_elapsed;
    float                                  m_duration;
    bool                                   m_bFirstTick;
    bool                                   m_bDelayTime;
    DTransformNode*                        m_pTarget;
    
    friend class DRefPtr<DAction>;
    friend class DSequence;
    friend class DSpawn;
};

template<typename T1,typename T2>
class DChangeAble
{
public:
    virtual T1& from(const T2& start)
    {
        m_start = start;
        m_startType &= ~ByXY;
        return static_cast<T1&>(*this);
    }
    virtual T1& to(const T2& end)
    {
        m_end = end;
        m_endType &= ~ByXY;
        m_bIsOffset = false;
        return static_cast<T1&>(*this);
    }
    virtual T1& by(const T2& delta)
    {
        m_delta = delta;
        m_bIsOffset = true;
        return static_cast<T1&>(*this);
    }
protected:
    void setInfo(float p1)
    {
        if(m_startType & ByXY)
        {
            m_start = p1;
        }
        
        if(m_bIsOffset)
        {
            m_end = m_start + m_delta;
        }
        else
        {
            if(m_endType & ByXY)
            {
                m_end = p1;
            }
            m_delta = m_end - m_start;
        }
    }
    void setInfo(float p1,float p2)
    {
        if(m_startType & ByX)
        {
            m_start.x = p1;
        }
        if(m_startType & ByY)
        {
            m_start.y = p2;
        }
        if(m_bIsOffset)
        {
            m_end = m_start + m_delta;
        }
        else
        {
            if(m_endType & ByX)
            {
                m_end.x = p1;
            }
            if(m_endType & ByY)
            {
                m_end.y = p2;
            }
            
            m_delta = m_end - m_start;
        }
    }
protected:
    DChangeAble():m_startType(ByXY),m_endType(ByXY),m_bIsOffset(false){}
    enum
    {
        ByNone = 0,
        ByXY = 3,
        ByX = 1,
        ByY = 2
    };
    
    int    m_startType;
    int    m_endType;
    bool   m_bIsOffset;
    T2     m_start;
    T2     m_end;
    T2     m_delta;
};

class DMove:public DAction,public DChangeAble<DMove,DVec2>
{
public:
    virtual DMove& fromX(float x);
    virtual DMove& fromY(float y);
    virtual DMove& toX(float x);
    virtual DMove& toY(float y);
    
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
 
public:
    DRefPtr<DMove> clone() const { auto b = _copy(); DRefPtr<DMove> a(b); return a; }
    
protected:
    virtual DMove* _copy() const override { auto a = new DMove(); *a = *this; return a;}
    
    friend class DRefPtr<DMove>;
};

class DBezier : public DAction
{
public:
    virtual DBezier& from(const DVec2& start);
    virtual DBezier& controlPointsTo(const DVec2& controlPoint1,const DVec2& controlPoint2);
    virtual DBezier& controlPointsBy(const DVec2& controlPoint1,const DVec2& controlPoint2);
    virtual DBezier& to(const DVec2& end);
    virtual DBezier& by(const DVec2& end);
    
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DBezier> clone() const { auto b = _copy(); DRefPtr<DBezier> a(b); return a; }
    
protected:
    virtual DBezier* _copy() const override { auto a = new DBezier(); *a = *this; return a;}
    
    friend class DRefPtr<DBezier>;
    
    DBezier():m_bIsOffset(false),m_startType(false),m_endType(false){}
    
protected:
    bool   m_startType;
    bool   m_endType;
    bool   m_bIsOffset;
    DVec2  m_start;
    DVec2  m_end;
    DVec2  m_controlPoint_1;
    DVec2  m_controlPoint_2;
    DVec2  m_endOffset;
    DVec2  m_controlPointOffset_1;
    DVec2  m_controlPointOffset_2;
};

class DRotate:public DAction,public DChangeAble<DRotate,float>
{
public:
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DRotate> clone() const { auto b = _copy(); DRefPtr<DRotate> a(b); return a; }
    
protected:
    virtual DRotate* _copy() const override { auto a = new DRotate(); *a = *this; return a;}
    
    friend class DRefPtr<DRotate>;
};

class DScale:public DAction,public DChangeAble<DScale,DVec2>
{
public:
    virtual DScale& fromX(float startX);
    virtual DScale& toX(float endX);
    
    virtual DScale& fromY(float startY);
    virtual DScale& toY(float endY);
    
    virtual DScale& fromScale(float start);
    virtual DScale& toScale(float end);
    virtual DScale& byScale(float delta);
    
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DScale> clone() const { auto b = _copy(); DRefPtr<DScale> a(b); return a; }
    
protected:
    virtual DScale* _copy() const override { auto a = new DScale(); *a = *this; return a;}
    
    friend class DRefPtr<DScale>;
};

class DJump : public DAction,public DChangeAble<DJump,DVec2>
{
public:
    virtual DJump& setHeight(float height);
    
    virtual DJump& setJumpCount(int jumps);
    
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DJump> clone() const { auto b = _copy(); DRefPtr<DJump> a(b); return a; }
    
protected:
    virtual DJump* _copy() const override { auto a = new DJump(); *a = *this; return a;}
    
    friend class DRefPtr<DJump>;
    
protected:
    DVec2           m_previousPos;
    float           m_height = 5;
    int             m_jumps = 1;
};

class DChangeColor:public DAction
{
public:
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DChangeColor> clone() const { auto b = _copy(); DRefPtr<DChangeColor> a(b); return a; }
    
protected:
    virtual DChangeColor* _copy() const override { auto a = new DChangeColor(); *a = *this; return a;}
    
    friend class DRefPtr<DChangeColor>;
    
public:
    virtual DChangeColor& from(const DVec3& start)
    {
        m_start = start;
        m_startType &= ~ByXY;
        return (*this);
    }
    virtual DChangeColor& to(const DVec3& end)
    {
        m_end = end;
        m_endType &= ~ByXY;
        m_bIsOffset = false;
        return (*this);
    }
    virtual DChangeColor& by(const DVec3& delta)
    {
        m_delta = delta;
        m_bIsOffset = true;
        return (*this);
    }
protected:
    void setInfo(const DVec3& p1)
    {
        if(m_startType & ByXY)
        {
            m_start = p1;
        }
        
        if(m_bIsOffset)
        {
            m_end = m_start + m_delta;
        }
        else
        {
            if(m_endType & ByXY)
            {
                m_end = p1;
            }
            m_delta = m_end - m_start;
        }
    }
    
protected:
    DChangeColor():m_startType(ByXY),m_endType(ByXY),m_bIsOffset(false){}
    enum
    {
        ByNone = 0,
        ByXY = 3,
        ByX = 1,
        ByY = 2
    };
    
    int    m_startType;
    int    m_endType;
    bool   m_bIsOffset;
    DVec3  m_start;
    DVec3  m_end;
    DVec3  m_delta;
};

class DFade:public DAction,public DChangeAble<DFade,float>
{
public:
    virtual void setTarget(DTransformNode* target) override;
    
    virtual void timeStep(float dt) override;
    
public:
    DRefPtr<DFade> clone() const { auto b = _copy(); DRefPtr<DFade> a(b); return a; }
    
protected:
    virtual DFade* _copy() const override { auto a = new DFade(); *a = *this; return a;}
    
    friend class DRefPtr<DFade>;
};

class DRemoveSelf:public DAction
{
public:
    virtual void update(float dt) override;
    virtual bool isDone()const override;
    virtual DRemoveSelf& setCleanup(bool clean) {m_bCleanup = clean;return *this;}
    
public:
    DRefPtr<DRemoveSelf> clone() const { auto b = _copy(); DRefPtr<DRemoveSelf> a(b); return a; }
    
protected:
    virtual DRemoveSelf* _copy() const override { auto a = new DRemoveSelf(); *a = *this; return a;}
    
protected:
    DRemoveSelf():m_bCleanup(true){}
private:
    bool    m_bCleanup;
    
    friend class DRefPtr<DRemoveSelf>;
};

class DVisible:public DAction
{
public:
    virtual void update(float dt) override;
    virtual bool isDone()const override;
    virtual DVisible& setVisible(bool show) {m_bVisible = show;return *this;}
    
public:
    DRefPtr<DVisible> clone() const { auto b = _copy(); DRefPtr<DVisible> a(b); return a; }
    
protected:
    virtual DVisible* _copy() const override { auto a = new DVisible(); *a = *this; return a;}
    
protected:
    DVisible():m_bVisible(true){}
private:
    bool    m_bVisible;
    
    friend class DRefPtr<DVisible>;
};

class DSchedule:public DAction
{
public:
    virtual void update(float dt) override;
    
    inline DSchedule& onUpdate(const std::function<void(float)> &func){m_updateFunc = func; return (*this);}
    
    DRefPtr<DSchedule> clone() const { auto b = _copy(); DRefPtr<DSchedule> a(b); return a; }
    
protected:
    virtual DSchedule* _copy() const override { auto a = new DSchedule(); *a = *this; return a;}
protected:
    DSchedule(){}
    
    std::function<void(float)> m_updateFunc = nullptr;
    
    friend class DRefPtr<DSchedule>;
};

class DUpdateAction:public DAction
{
public:
    virtual void update(float dt) override;
    virtual bool isDone()const override;
    
    virtual DUpdateAction& setUpdate(void* data,const std::function<bool(void*,float)> &func){m_cb = func; m_pData = data; return (*this);}
    
    DRefPtr<DUpdateAction> clone() const { auto b = _copy(); DRefPtr<DUpdateAction> a(b); return a; }
    
protected:
    virtual DUpdateAction* _copy() const override { auto a = new DUpdateAction(); *a = *this; return a;}
protected:
    DUpdateAction():m_pData(nullptr),m_isDone(true),m_cb(nullptr){}
private:
    std::function<bool(void*,float)> m_cb;
    void*                            m_pData;
    bool                             m_isDone;
    
    friend class DRefPtr<DUpdateAction>;
};

class DUpdateNumberAction:public DAction
{
public:
    virtual void timeStep(float dt) override;
    
    virtual DUpdateNumberAction& setUpdate(int fromNum,int toNum,const std::function<bool(int)> &func){m_cb = func; m_fromNum = fromNum;m_toNum = toNum; m_deltaNum = toNum - fromNum ;return (*this);}
    
    DRefPtr<DUpdateNumberAction> clone() const { auto b = _copy(); DRefPtr<DUpdateNumberAction> a(b); return a; }
    
protected:
    virtual DUpdateNumberAction* _copy() const override { auto a = new DUpdateNumberAction(); *a = *this; return a;}
protected:
    DUpdateNumberAction(){}
private:
    std::function<bool(int)>         m_cb = nullptr;
    int                              m_fromNum = 0;
    int                              m_toNum = 0;
    int                              m_deltaNum = 0;
    
    friend class DRefPtr<DUpdateNumberAction>;
};

class DSpawn:public DAction
{
public:
    virtual DSpawn& pushAction(DAction* action);
    virtual void update(float dt) override;
    virtual bool isDone()const override;
    virtual void setTarget(DTransformNode* target) override;
public:
    DRefPtr<DSpawn> clone() const { auto b = _copy(); DRefPtr<DSpawn> a(b); return a; }
    
protected:
    virtual DSpawn* _copy() const override ;
    
private:
    DArray<DAction*> m_actionSpawn;
    std::list<DAction*> m_runActionSpawn;
    
    friend class DRefPtr<DSpawn>;
};

class DSequence:public DAction
{
public:
    virtual DSequence& pushAction(DAction* action);
    virtual void update(float dt) override;
    virtual bool isDone()const override;
    virtual void setTarget(DTransformNode* target) override;
public:
    DRefPtr<DSequence> clone() const { auto b = _copy(); DRefPtr<DSequence> a(b); return a; }
    
protected:
    virtual DSequence* _copy() const override ;
    
protected:
    DSequence();
private:
    DArray<DAction*> m_actionSeq;
    ssize_t          m_curActionIndex;
    
    friend class DRefPtr<DSequence>;
};

class DWake;
class DSleep;

class DWake:public DAction
{
protected:
    DWake(){}
public:
    virtual ~DWake(){}
public:
    virtual void update(float dt) override;
    virtual bool isDone()const override;
public:
    DRefPtr<DWake> clone() const { auto b = _copy(); DRefPtr<DWake> a(b); return a; }
    
protected:
    virtual DWake* _copy() const override;
    
private:
    DArray<DSleep*> m_sleepers;
    
    friend class DSleep;
    friend class DRefPtr<DWake>;
};

class DSleep:public DAction
{
protected:
    DSleep(){}
public:
    virtual ~DSleep(){}
public:
    virtual void update(float dt) override{}
    virtual bool isDone()const override;
    
    DRefPtr<DWake> wake()
    {
        DRefPtr<DWake> a;
        
        a->m_sleepers.pushBack(this);
        
        m_wakeners.pushBack(a);
        
        return a;
    }
    
public:
    DRefPtr<DSleep> clone() const { auto b = _copy(); DRefPtr<DSleep> a(b); return a; }
    
protected:
    virtual DSleep* _copy() const override;
    
private:
    DArray<DWake*> m_wakeners;
    
    friend class DWake;
    friend class DRefPtr<DSleep>;
};

class DActionManager
{
private:
    struct DActionElement
    {
        DArray<DAction*> actionList;
    };
    struct DActionDelay
    {
        enum Type
        {
            REMOVE_BY_ACTION,
            REMOVE_BY_TARGET,
            ADD_ACTION,
        };
        
        DActionDelay(DAction* a,DTransformNode* t,Type tp)
        :action(a)
        ,target(t)
        ,type(tp)
        {
            if(action)
            {
                action->ref();
            }
        }
        
        DActionDelay(const DActionDelay & a)
        {
            action = a.action;
            if(action)
            {
                action->ref();
            }
            target = a.target;
            type = a.type;
        }
        
        ~DActionDelay()
        {
            if(action)
            {
                action->unref();
                action = nullptr;
            }
        }
        Type type;
        DAction* action = nullptr;
        DTransformNode* target = nullptr;
    };
public:
    size_t getActionNumber(DTransformNode* target);
    void   update(float dt);
    void   addAction(DAction* action,DTransformNode* target);
    void   removeAction(DAction* action);
    void   removeAllActionFromTarget(DTransformNode* target);
private:
    std::map<DTransformNode*,DActionElement> m_actionMap;
    std::vector<DActionDelay>                m_actionDelayList;
    bool   m_isInLoop = false;
};


#endif
