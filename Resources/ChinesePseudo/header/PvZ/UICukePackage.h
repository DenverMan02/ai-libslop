//
//  UICukePackage.hpp
//  PlantsVersusZombies2
//
//  Created by xiao on 16/9/14.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UICukePackage_h
#define UICukePackage_h

#include "DNode/DNodeWidget.h"
#include "MagentoService.h"

class UICukePackage : public DNodeWidget
{
public:
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    static UICukePackage* create();
    
    static UICukePackage* get();

    ~UICukePackage();
    virtual void Draw(Sexy::Graphics* i_g) override;
private:
    void OnCloseButtonClick();
    void OnConfirmButtonClick();
    
    void OnBuyCukePackgae(MagentoProductProps* i_props);
    void BuyCukePackgaeSuccess();
    void RemoveSelf();
    
private:
    MagentoProductPropsPtr m_product;
    static UICukePackage* s_pWidgetHandler;
};


#endif /* UICukePackage_h */
