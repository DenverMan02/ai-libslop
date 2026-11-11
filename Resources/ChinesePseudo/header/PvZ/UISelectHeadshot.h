
#ifndef _UI_SELECT_HEADSHOT_H_
#define _UI_SELECT_HEADSHOT_H_

#include "DNode/DNodeWidget.h"
#include "UIHeadshot.h"

class UISelectHeadshot:public DNodeWidget
{
public:
    CREATE_SINGLETON_FUNC(UISelectHeadshot)
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void createHeadshotIdSelect(int headshotId);
    void selectHeadshotId(int headshotId);
    void changeHeadShot(int headshotId);
    void changeSubHeadShot(int headshotId);
    bool uploadHeadShot(int headshotId);
    void showSubUI(bool show);
    void enableChange(bool i_enable);
public:
    int    m_selectHeadshot = 0;
    int    m_initHeadshot = 0;
    DAnimNode* m_cursor1 = nullptr;
    DAnimNode* m_cursor2 = nullptr;
    bool   m_isUnlock = false;
    bool   m_bCreated = false;
};

#endif
