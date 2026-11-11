
#ifndef WorldMap_OfflineBundleButton_hpp
#define WorldMap_OfflineBundleButton_hpp

#include "RtObject.h"
#include "UIEasyButtonWidget.h"

class WorldMap_OfflineBundleButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_OfflineBundleButton, UIWidget, RtClass);
    
    WorldMap_OfflineBundleButton();
    virtual ~WorldMap_OfflineBundleButton();
    
    // Public Interface (Inheritable)
    
    virtual void		Draw(Graphics* i_g) override;
    
    static bool         CheckVisibility();
    
protected:
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
    
    // Protected Interface (Inheritable)
    
    virtual void		initLoadingResourcesGroupList() override;
    //virtual void		updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed) override;;
    
private:
    
};

#endif
