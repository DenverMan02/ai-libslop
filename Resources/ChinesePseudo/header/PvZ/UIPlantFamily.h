//
//  PlantFamily.h
//  PlantsVersusZombies2
//
//  Created by xiao on 16/11/17.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIPlantFamily_h
#define UIPlantFamily_h

#include "Widget.h"
#include "CUIDialog.h"

class PlantFamilyUI : public Sexy::Widget
{
public:
    
    PlantFamilyUI(int i_type);
    virtual ~PlantFamilyUI();
    
    void InitView(int i_type);
    static void CloseView();
    
    virtual void	Update() override;
    virtual void	Draw(Sexy::Graphics* i_g) override;
    
private:
    Lua::CUIDialog* m_pDlg = nullptr;
    static int m_type;
};

#endif /* UIPlantFamily_h */
