//
//  AutoLock.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/7/11.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef AutoLock_h
#define AutoLock_h

class AutoLock
{
public:
    AutoLock(std::function<void()> lockfun, std::function<void()> unlockfun)
    : m_unlockfun(unlockfun)
    {
        if (lockfun)
        {
            lockfun();
        }
    }
    
    ~AutoLock()
    {
        if (m_unlockfun)
        {
            m_unlockfun();
        }
    }
    
private:
    std::function<void()> m_unlockfun;
};

class IFieldLock
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};

class AutoFieldLock
{
public:
    AutoFieldLock(IFieldLock* f)
    :m_field(f)
    {
        if(m_field)
        {
            m_field->lock();
        }
    }
    
    virtual ~AutoFieldLock()
    {
        if (m_field)
        {
            m_field->unlock();
        }
    }
    
private:
    IFieldLock *m_field;
};


#endif /* AutoLock_h */
