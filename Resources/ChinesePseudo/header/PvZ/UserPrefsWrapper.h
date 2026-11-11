//
//  UserPrefsWrapper.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 3/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__UserPrefsWrapper__
#define __PlantsVersusZombies2__UserPrefsWrapper__

#include "Precompile.h"

#define INSTALL_DATE_KEY "UdIdCheck"

class UserPrefsWrapper {
public:
    static UserPrefsWrapper& GetInstance()
    {
        static UserPrefsWrapper instance;
        return instance;
    };
    
    virtual ~UserPrefsWrapper(){}
    virtual const std::string GetString(const std::string& i_key, std::string i_defaultValue = "");
    virtual const std::string GetStringEx(const std::string& i_key, std::string i_defaultValue = "");
    virtual void SetString(const std::string &i_key, std::string i_value);
    virtual void SetBool(const std::string& i_key, bool i_value);
    virtual const bool GetBool(const std::string& i_key);
    virtual const int GetInt(const std::string& i_key, int i_defaultValue = 0);
    virtual void SetInt(const std::string& i_key, int i_value);
    
    std::string GetPCPID();
    void SetPCPIDStrings(const std::string& i_value);
    
    std::string GetAge();
    void SetAge(const std::string& i_value);
    
    static const std::string pcpid_key;
    static const std::string age_key;
    static const std::string permanentLawnMowerTutorial_key;
};

#endif /* defined(__PlantsVersusZombies2__UserPrefsWrapper__) */
