
#ifndef _UI_SELECT_HARD_LEVEL_MODE_H_
#define _UI_SELECT_HARD_LEVEL_MODE_H_

#include "DNode/DNodeWidget.h"
#include "WorldMap.h"
#include "MapEventItem.h"

class UISelectHardLevelModeWidget:public DNodeWidget
{
public:
    enum LevelType
    {
        EASY = 0,
        HARD
    };
    
    enum State
    {
        NORMAL = 0,
        HARD_FIRST,
        EASY_FIRST
    };
    
    
    CREATE_FUNC(UISelectHardLevelModeWidget)
    
    static UISelectHardLevelModeWidget* create(WorldMap* worldMap,const std::string& levelName,State stat = NORMAL);
    
    UISelectHardLevelModeWidget();
    virtual ~UISelectHardLevelModeWidget();
    
    virtual void Initialize() override;
    
    virtual void Initialize(WorldMap* worldMap,const std::string& levelName,State stat);
    virtual void Update() override;
    
    void updateModeInfo();
    
    DRefPtr<DButton> createButton(const std::string& buttonImg,bool hasUnlock,bool isYetOpen,bool hard,bool pass,bool showPaoPao);
    
    void CheckShowTutorial();
    
protected:
    bool isYetHardLevel();
    bool isShowChestPop();
    bool isLockLevel(bool ishard);

    void ScaleForAds(DTransformNode* root);

private:
    WorldMap*   m_pWorldMap = nullptr;
    std::string m_levelName;
    LevelType   m_levelType = EASY;
    State       m_state = NORMAL;
    bool        m_bBoxIsOpen = false;
    
    std::vector<DSpriteNode*>   m_pZombieLevelIcons;
    DAnimNode*                  m_pLockAni;
    DAnimNode*                  m_pChest;
    
    std::vector<DTransformNode*> m_uiInfos;
    
    DSpriteNode*                m_pLockMask;
    std::vector<DAnimNode*>     m_hardStar;
    std::vector<DAnimNode*>     m_easyStar;
    
    static UISelectHardLevelModeWidget* s_pWidgetHandler;
    
    MapTutorialState    m_tutorialState = TUTORIAL_NONE;
    Rect                m_tutorialRect;
    float               m_tutorialTime = -1.0f;

    float				m_widgetScale = 1.0f;

    DRefPtr<DButton> closeBtn;
//    DRefPtr<DButton> btn1;
//    DRefPtr<DButton> btn2;
};

#endif
