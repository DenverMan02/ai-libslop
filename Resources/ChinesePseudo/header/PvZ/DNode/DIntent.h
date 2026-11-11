//
//  DIntent.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DIntent_h
#define DIntent_h

#include "DSingleton.h"
#include "DValue.h"
#include "DRef.h"

class DIntent :public DSingleton<DIntent>
{
public:
    void addValue(const std::string& key,const DValue& value);
    const DValue& getValue(const std::string& key);
    
    void  addBool(const std::string& key,const bool value);
    bool  getBool(const std::string& key,const bool defaultValue = false);
    void  addInt(const std::string& key,const int value);
    int   getInt(const std::string& key,const int defaultValue = 0);
    void  addFloat(const std::string& key,const float value);
    float getFloat(const std::string& key,const float defaultValue = 0.0f);
    void  addString(const std::string& key,const std::string& value);
    std::string getString(const std::string& key,const std::string& defaultValue = "");
    
    void clearValue();
    void removeValue(const std::string& key);
    
    void addRef(const std::string& key,DRef* value);
    DRef* getRef(const std::string& key);
    void clearRef();
    void removeRef(const std::string& key);
    
    void clear();
private:
    std::unordered_map<std::string,DValue> m_mapValue;
    std::unordered_map<std::string,DRef*>  m_mapRef;
};

#endif
