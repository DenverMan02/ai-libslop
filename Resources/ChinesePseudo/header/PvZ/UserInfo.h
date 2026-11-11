
#ifndef _SYS_USER_INFO_H_
#define _SYS_USER_INFO_H_

#include "DNode/DEngine.h"

class UserInfo:public DSingleton<UserInfo>
{
public:
    UserInfo();
    ~UserInfo();
    
    READ_WRITE_REF_PROPERTY(std::string, Name,"")
    READ_WRITE_REF_PROPERTY(std::string, Phone,"")
    READ_WRITE_REF_PROPERTY(std::string, Email,"")
    
    READ_WRITE_PROPERTY(int, Age,0)
    READ_WRITE_PROPERTY(int, Sex,0)
    READ_WRITE_PROPERTY(bool,Reward,false)
    READ_WRITE_PROPERTY(bool,ChangeName,false)
    
public:
    int  getHeadShotId() {return HeadShotId;}
    void setHeadShotId(int a);
    void unlockHeadShotId(int a);
protected:
    int HeadShotId = 0;
};

#endif