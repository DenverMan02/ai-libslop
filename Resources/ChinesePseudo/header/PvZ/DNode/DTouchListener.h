//
//  DTouchListener.h
//  DCore
//
//  Created by lzjseed on 16/4/14.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DTouchListener_h
#define DTouchListener_h

#include "DSingleton.h"
#include "SexyAppFramework/SexyAppBase.h"
#include "DNode.h"

using namespace Sexy;

class DTouchListener:public DRef
{
public:
    
    typedef std::function<bool(const Sexy::Touch& touch)> TouchBeganCallback;
    typedef std::function<void(const Sexy::Touch& touch)> TouchCallback;

    TouchBeganCallback onTouchBegan = nullptr;
    TouchCallback      onTouchMoved = nullptr;
    TouchCallback      onTouchCancelled = nullptr;
    TouchCallback      onTouchEnded = nullptr;
    TouchCallback	   onTouchLongPress = nullptr;
    
    void               setSwallowed(bool isSwallowed){m_isSwallowed = isSwallowed;}
    bool               isSwallowed()const {return m_isSwallowed;}
    void               setRegister(bool isRegister){m_isRegister = isRegister;}
    bool               isRegister()const {return m_isRegister;}
    
    void               setFixedPriorty(int priorty) {m_fixedPriority = priorty;}
    int                getFixedPriorty()const {return m_fixedPriority;}
    
    bool               checkAvailable()
    {
        if (onTouchBegan == nullptr && onTouchMoved == nullptr
            && onTouchEnded == nullptr && onTouchCancelled == nullptr && onTouchLongPress == nullptr)
        {
            return false;
        }
        
        return true;
    }
    
private:
    int                 m_fixedPriority = 0;
    bool                m_isRegister = false;
    bool                m_isSwallowed = false;
    std::vector<Touch> m_claimedTouches;
    DTouchListener(){}
    
    friend class DRefPtr<DTouchListener>;
    friend class DTouchEventDispatcher;
};

enum DTouchEvent
{
    DTOUCH_BEGAN = 0,
    DTOUCH_MOVED,
    DTOUCH_ENDED,
    DTOUCH_CANCELLED,
    DTOUCH_LONGPRESS
};

class DTouchEventDispatcher
{
public:
    void touchHandle(const Touch& touch,DTouchEvent event);
    
    void addTouchListenerWithFixedPriority(DTouchListener* listener, int fixedPriority);
    
    void addTouchListener(DTouchListener* listener);
    
    void removeTouchListener(DTouchListener* listener);
    
    void clean();
    
protected:
    void sortTouchListeners();
    void forceAddTouchListener(DTouchListener* listener);
    void forceRemoveTouchListener(DTouchListener* listener);
private:
    std::vector<DTouchListener*> m_touchListeners;
    std::vector<DTouchListener*> m_addListeners;
    std::vector<DTouchListener*> m_removeListeners;
    bool m_isInHandle = false;
};


#endif
