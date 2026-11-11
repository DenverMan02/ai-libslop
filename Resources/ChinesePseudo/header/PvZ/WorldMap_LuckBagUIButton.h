#ifndef __PlantsVersusZombies2__WorldMap_LuckBagUIButton__
#define __PlantsVersusZombies2__WorldMap_LuckBagUIButton__

#include "UIEasyButtonWidget.h"

class WorldMap_LuckBagUIButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_LuckBagUIButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_LuckBagUIButton();
    virtual ~WorldMap_LuckBagUIButton();
    
    bool CheckActivated();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void showOpenErrorDialog();
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();
    void onNotifyBackFromRift();
private:
    bool m_thisRequest;
};

#endif
