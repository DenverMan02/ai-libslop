//
//  DSingleton.h
//  DCore
//
//  Created by lzjseed on 16/4/14.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DSingleton_h
#define DSingleton_h

template <typename T>
class DSingleton
{
public:
    static T*   getInstance()
    {
        if(!s_pInstance)
        {
            s_pInstance = new T;
        }
        return s_pInstance;
    }
    static void purge()
    {
        if(s_pInstance)
        {
            delete s_pInstance;
            s_pInstance = nullptr;
        }
    }
    
protected:
    static T* s_pInstance;
};

template <typename T>
T* DSingleton<T>::s_pInstance = nullptr;

#endif
