//
//  SkycityBossWarningInfo.h
//  PlantsVersusZombies2
//
//  Created by Wu, Song (Tiger) on 16/9/20.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef SkycityBossWarningInfo_h
#define SkycityBossWarningInfo_h

#include "Widget.h"
#include "Common.h"


class SkycityBossWarningInfo : public Sexy::Widget
{
public:
    SkycityBossWarningInfo();
    ~SkycityBossWarningInfo();
    
    virtual void Update() override;
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
    
    void DrawRedLayer(Sexy::Graphics* i_g);
    void DrawRedImg(Sexy::Graphics* i_g);
    
private:
    float   redlayerPer = 0.0f;
    bool    isUp = true;
};

#endif /* SkycityBossWarningInfo_h */
