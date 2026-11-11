//
//  FileUtil.hpp
//  PlantsVersusZombies2
//
//  Created by shizf on 16/3/15.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef FileUtil_h
#define FileUtil_h

#include "common.h"
#include <memory>

class FileUtil
{
public:
    static std::shared_ptr<FILE> openFile(const std::string& i_name, const std::string& i_mode);
    static void writeFile(const std::shared_ptr<FILE>& i_file, const std::string& i_content);
    static bool readFile(const std::shared_ptr<FILE>& i_file, std::string& i_content);
    
    static std::string getTimeStr();
};

#endif /* FileUtil_h */
