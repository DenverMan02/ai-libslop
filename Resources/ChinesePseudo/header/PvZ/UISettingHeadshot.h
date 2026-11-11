
#ifndef _UI_SETTING_HEADSHOT_H_
#define _UI_SETTING_HEADSHOT_H_

#include "DNode/DNodeWidget.h"
#include "UIHeadshot.h"

class UISettingHeadshot:public DNodeWidget
{
public:
    CREATE_SINGLETON_FUNC(UISettingHeadshot)
    
    virtual ~UISettingHeadshot();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    bool buyName();
    bool changeName(const std::string& name);
    
    void updateName();
    void getFilterString();
    bool checkNameIsVaild(const std::string& name);
private:
    UIHeadshotIcon *m_pHeadshotIcon = nullptr;
    std::string     m_name;
    std::vector<std::string> filterNameList;
    int m_previousColor = 0;
};

#endif
