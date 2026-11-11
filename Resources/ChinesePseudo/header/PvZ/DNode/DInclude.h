//
//  DInclude.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DInclude_h
#define DInclude_h

#include "TodDebug.h"

#define USE_STD_UNORDERED_MAP 1

#define DASSERT             DBG_ASSERT_MSG
#define DLOG                OutputDebug

#define BREAK_IF(cond)      if(cond) break

#if 0
    #define DYNAMIC_CAST    dynamic_cast
#else
    #define DYNAMIC_CAST    static_cast
#endif

#define READ_ONLY_PROPERTY(typeName,varName,defaultVar) \
protected:\
    typeName m_##varName = defaultVar;\
public:\
    typeName get##varName() const {return m_##varName;}

#define READ_WRITE_PROPERTY(typeName,varName,defaultVar) \
protected:\
    typeName m_##varName = defaultVar;\
public:\
    typeName get##varName() const {return m_##varName;}\
    void     set##varName(typeName v) {m_##varName = v;}

#define READ_ONLY_REF_PROPERTY(typeName,varName,defaultVar) \
protected:\
    typeName m_##varName = defaultVar;\
public:\
    const typeName& get##varName() const {return m_##varName;}

#define READ_WRITE_REF_PROPERTY(typeName,varName,defaultVar) \
protected:\
    typeName m_##varName = defaultVar;\
public:\
    const typeName& get##varName() const {return m_##varName;}\
    void  set##varName(const typeName& v) {m_##varName = v;}

#endif
