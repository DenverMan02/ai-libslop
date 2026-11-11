//
//  PlantHeadshot.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/5/25.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantHeadshot_h
#define PlantHeadshot_h

#include "Widget.h"
#include "string.h"
#include "Image.h"
#include "Rect.h"

class PlantHeadshot : public Sexy::Widget
{
public:
    PlantHeadshot(std::string i_plantName);
    ~PlantHeadshot();
    
    void Draw(Sexy::Graphics* i_g) override;
    void Resize(const Sexy::Rect& theRect) override;
    void Resize(int theX, int theY, int theWidth, int theHeight) override;
    void SetNeedLock(bool i_lock);
    
private:
    bool m_needLock;
    
    Sexy::Rect m_plantRect;
    Sexy::Rect m_frameRect;
    Sexy::Rect m_rareFrameRect;
    Sexy::Rect m_unlockRect;
    
    Sexy::ImagePtr m_plantImg;
    Sexy::ImagePtr m_frameImg;
    Sexy::ImagePtr m_rareFrameImg;
    Sexy::ImagePtr m_unlockImg;
//    std::string m_plantName;
    
public:
    static const std::string PlantPrefix;       // need add group UI_HeadShot_Plant
    static const std::string PlantBigPrefix;    // need add group UI_HeadShot_BigPlant
    static const std::string AvatarBigPrefix; 		// need add group UI_HeadShot_BigAvatar
    static const std::string UpdateAvatarBigPrefix;		// need add group UPDATE_UI_HeadShot_BigAvatar
};

#endif /* PlantHeadshot_h */
