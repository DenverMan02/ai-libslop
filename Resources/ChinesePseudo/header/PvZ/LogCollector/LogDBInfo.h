#ifndef __Load_DB_Info__
#define __Load_DB_Info__

#include "IFileDriver.h"
#include <unordered_map>
#include <vector>
#include "DNode/DString.h"
#include "DNode/DValue.h"

class LogDBInfo
{
public:
    
    static LogDBInfo* getInstance();
    
    typedef std::unordered_map<std::string,std::vector<DString>> TableInfo;
    
    bool loadDB();
    
    void sendMsg(const std::string& tableName,const DValue & value);
    
private:
    
    bool load(const std::string& fileName);
    
    LogDBInfo() = default;
    
    virtual ~LogDBInfo() = default;
    
private:
    TableInfo   m_tableInfos;
    static LogDBInfo* s_pInstance;
};


#endif