//
//  ViewFormationWidget.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 13-8-1.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ViewFormationWidget__
#define __PlantsVersusZombies2__ViewFormationWidget__

#include "PVZ2UIButton.h"
#include "SocialInfo.h"
#include "PVZTypes.h"

class ViewFormationWidget : public Widget, Sexy::ButtonListener
{
public:
    ViewFormationWidget(std::string i_levelName, std::vector<GameRankInfo> i_gameRankInfos);
    ~ViewFormationWidget();
    
    void ViewFormation(int i_index);
    void ClearPlants();
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void Update();
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
private:
    void InitView();
    std::vector<int>                    m_plankRows;
    
    std::vector<PVZ2UIButton *>         m_tabButtons;
    PVZ2UIButton*                       m_closeButton;
    Image*                              m_imgFormation;
    std::vector<Image *>                m_imgPlanks;
    
    std::vector<class PlantAnimRig*>    m_plants;
    std::vector<PlantTypePtr>           m_plantTypes;
    std::vector<Rect>                   m_rectRigs;
    std::vector<Rect>                   m_rectPlants;
    std::vector<Rect>                   m_rectPlanks;
    
    Rect    m_rectDialog;
    Rect    m_rectInternal;
    Rect    m_rectBG;
    Rect    m_rectFormation;
    
    int     m_selectIndex;
    std::string m_levelName;
    std::vector<GameRankInfo> m_gameRankInfos;
    
};

#endif /* defined(__PlantsVersusZombies2__ViewFormationWidget__) */
