
#ifndef _UI_BUY_CRYSTAL_H_
#define _UI_BUY_CRYSTAL_H_

#include "DNode/DNodeWidget.h"
#include "MagentoService.h"

class UIBuyCrystal:public DNodeWidget
{
public:
    CREATE_FUNC(UIBuyCrystal)
    
    static UIBuyCrystal* create(const std::string& category, bool focus = true)
    {
        auto p = new UIBuyCrystal();
        if(p)
        {
            p->m_categoryName = category;
            p->Initialize();
            p->UserInit();
            p->addToWidgetManager(focus);
            
        }
        return p;
    }
    
    virtual ~UIBuyCrystal();
    
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    static UIBuyCrystal* s_pWidgetHandler;
    void buyItem(int index);
private:
private:
    std::string m_categoryName;
    MagentoCategoryPropsPtr m_category;
};

#endif
