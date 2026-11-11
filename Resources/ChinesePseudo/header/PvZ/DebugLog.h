//
//  DebugLog.hpp
//  PlantsVersusZombies2
//
//  Created by shizf on 16/3/17.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DebugLog_h
#define DebugLog_h

#include "common.h"
#include "Singleton.h"
#include "Core.h"

enum DebugLogFlags
{
    PVZ_BEGIN_FLAG_ENUM(DebugLogFlags_),
    PVZ_FLAG(DebugLog_Error),
    PVZ_FLAG(DebugLog_NetMessage),
    PVZ_FLAG(DebugLog_BIData),
    PVZ_FLAG(DebugLog_LoadGroup),
    PVZ_END_FLAG_ENUM(DebugLogFlags_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(DebugLogFlags);


enum DebugPathType
{
    PVZ_BEGIN_FLAG_ENUM(DebugPathType_),
    PVZ_FLAG(DebugPath_LogCat),
    PVZ_FLAG(DebugPath_File),
    PVZ_FLAG(DebugPath_NetWork),
    PVZ_END_FLAG_ENUM(DebugPathType_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(DebugPathType);


class DebugLog : public LazySingleton<DebugLog>
{
public:
    
    DebugLog();
    virtual ~DebugLog();
    
    void SendLog(const std::string& i_log,
                 DebugLogFlags i_flag = DebugLog_Error,
                 DebugPathType i_type = DebugPath_LogCat,
                 const std::string& i_tag = "PvZ2Debug"
                 );
    
    
    bool LogFile(const std::string& i_file, const std::string& i_mode, const std::string& i_log);
    
    
    bool ReadFile(const std::string& i_file,
                  const std::string& i_mode,
                  std::string& i_content);
    
private:
    std::string GetExternalFolder();
    
private:
    DebugLogFlags   m_Flags;
    
    std::string     m_pathLogCat;
};

#define gDebugLog (DebugLog::GetInstancePtr())

//#define DEBUG_FUNC_LOG(file,mode,msg) DebugLog::DebugLogFile((file),(mode),(msg),__FILE__,__LINE__,__FUNCTION__)

//#define DEBUG_INVAILD_LOG(msg) DEBUG_FUNC_LOG("invalid_log.txt","a+",(msg))

#endif /* DebugLog_h */
