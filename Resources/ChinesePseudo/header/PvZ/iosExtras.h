//
//  iosExtras.h
//  PlantsVersusZombies2
//
//  Created by Terrry Franguiadakis on 9/23/11.
//  Copyright 2011 PopCap. All rights reserved.
//
#pragma once

#include "Precompile.h"

bool IsDeviceIPad();

// convert an string ip address to byte string.
void StrIPAddressToBytes(const std::string& i_ipAddressString, unsigned char o_ipAddress[4]);

class UserPrefs 
{
    public:
    static void					SetString(const std::string &i_key, std::string i_value);
    static const std::string	GetString(const std::string& i_key, std::string i_defaultValue = "");
    static bool              	GetBool(const std::string& i_key, bool defaultValue = false);
	static int					GetInt(const std::string& i_key, int defaultValue = 0);
    static void                 SetInt(const std::string& i_key, int i_value);
	static void SetBool(const std::string& i_key, bool i_value);

    static void Synchronize();
    //PVZ2_CHINESE_BEGIN
    static std::string GetDeviceType();
    //PVZ2_CHINESE_END
};
