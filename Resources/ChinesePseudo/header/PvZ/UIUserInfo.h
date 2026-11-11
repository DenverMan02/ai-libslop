
#ifndef _UI_USER_INFO_H_
#define _UI_USER_INFO_H_

#include "DNode/DNodeWidget.h"

class UIUserInfo:public DNodeWidget
{
public:
    virtual ~UIUserInfo();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    
    bool validTel(const std::string& i_tel);
    
    bool validEmail(const std::string& i_email);
    
    static UIUserInfo* create(bool focus);
    
public:
    static UIUserInfo* s_pWidgetHandler;
};

#endif
