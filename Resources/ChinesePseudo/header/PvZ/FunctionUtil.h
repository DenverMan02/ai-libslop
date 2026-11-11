//
//  FunctionUtil.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/4/8.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef FunctionUtil_h
#define FunctionUtil_h

#define BIND_MEMBER_FUNC(func,member) std::bind(func,std::bind(&member,std::placeholders::_1),std::bind(&member,std::placeholders::_2))

#endif /* FunctionUtil_h */
