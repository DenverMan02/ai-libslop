//
//  BoardZombieAlmanacUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/7/28.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef BoardZombieAlmanac_h
#define BoardZombieAlmanac_h

#include "Widget.h"
#include "ButtonWidget.h"
#include "PVZTypes.h"
#include "PopAnimRigHelper.h"
#include "MagentoService.h"
#include "PVZ2UIPlantCard.h"
#include "Zombie.h"

class RecommendPlantUI : public Sexy::Widget
{
public:
    RecommendPlantUI(ZombieTypePtr i_zombieType, const Rect& i_rect);
    virtual ~RecommendPlantUI();
    
    void Draw(Graphics* i_g) override;
    
private:
    std::vector<std::string> m_plantList;
};

class BoardZombieAlmanacUI : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    enum
    {
        Button_Continue,
    };    

    BoardZombieAlmanacUI(const std::vector<std::string>& i_zombieList);
    virtual ~BoardZombieAlmanacUI();
    
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void AddAlmanacZombie(const std::string& i_zombieName) { m_zombieList.push_back(i_zombieName); }
    
    ZombieTypePtr GetObjectType() const { return m_zombieType; }
    
private:
    void showNextZombie();
    
private:
    PVZ2UIAlmanacInfoDisplayer* m_infoDisplayer;
    PVZ2UIAlmanacObjectDisplayer* m_objectDisplayer;
    RecommendPlantUI* m_recommendPlantUI;
    
    std::vector<std::string> m_zombieList;
    
    ZombieTypePtr m_zombieType;

    class PVZ2UIButton* m_confirmButton;
    
    Rect m_dialogRect;
    
};

#endif /* BoardZombieAlmanacUI_h */
