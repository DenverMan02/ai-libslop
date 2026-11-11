
#ifndef _UI_SELECT_BOSS_LEVEL_MODE_H_
#define _UI_SELECT_BOSS_LEVEL_MODE_H_

#include "DNode/DNodeWidget.h"
#include "WorldMap.h"

class UISelectBossLevelModeWidget:public DNodeWidget
{
public:
    enum State
    {
        NORMAL = 0,
        FIRST_PASS,
    };
    
    CREATE_FUNC(UISelectBossLevelModeWidget)
    
    static UISelectBossLevelModeWidget* create(WorldMap* worldMap,const std::string& levelName,State stat = NORMAL);
    
    UISelectBossLevelModeWidget();
    virtual ~UISelectBossLevelModeWidget();
    
    virtual void Initialize() override;
    
    virtual void Initialize(WorldMap* worldMap,const std::string& levelName,State stat);
    
    
protected:
    bool isLockLevel();
    bool isYetHardLevel();
    
private:
    WorldMap*   m_pWorldMap = nullptr;
    std::string m_levelName;
    State       m_state = NORMAL;
    bool        m_bBoxIsOpen = false;
    
    DAnimNode*                  m_pChest;
    std::vector<DAnimNode*>     m_hardStar;
    
    static UISelectBossLevelModeWidget* s_pWidgetHandler;
};

#endif
