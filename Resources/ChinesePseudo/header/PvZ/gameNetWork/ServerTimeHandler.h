//
//  ServerHandler.h
//  PlantsVersusZombies2
//
//  Created by Zhou, Guohua on 14-10-21.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ServerHandler__
#define __PlantsVersusZombies2__ServerHandler__

#include "Precompile.h"

class CServerTimeHandler
{
public:
    CServerTimeHandler(){};
    virtual ~CServerTimeHandler(){};
    
    virtual void OnServerTimeGet(bool bRet,long serverTime)=0;
};

class CServerTimeHandler_Store:public CServerTimeHandler
{
protected:
    std::string m_strFocusCategory;
public:
    CServerTimeHandler_Store(const std::string& strFocusCategory);
    virtual ~CServerTimeHandler_Store();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

class CServerTimeHandler_Festival:public CServerTimeHandler
{
protected:
    int m_iIndex;
public:
    CServerTimeHandler_Festival(int iIndex);
    virtual ~CServerTimeHandler_Festival();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

class CServerTimeHandler_Challenge:public CServerTimeHandler
{
protected:
    int m_iIndex;
public:
    CServerTimeHandler_Challenge(int iIndex);
    virtual ~CServerTimeHandler_Challenge();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

class CServerTimeHandler_DailyReward:public CServerTimeHandler
{
public:
    CServerTimeHandler_DailyReward();
    virtual ~CServerTimeHandler_DailyReward();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

class CServerTimeHandler_LoginReward:public CServerTimeHandler
{
public:
    CServerTimeHandler_LoginReward();
    virtual ~CServerTimeHandler_LoginReward();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

class CServerTimeHandler_SingleGacha:public CServerTimeHandler
{
public:
    CServerTimeHandler_SingleGacha();
    virtual ~CServerTimeHandler_SingleGacha();
    
    virtual void OnServerTimeGet(bool bRet,long serverTime);
};

#endif /* defined(__PlantsVersusZombies2__ServerHandler__) */
