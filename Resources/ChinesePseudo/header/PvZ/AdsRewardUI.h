//
//  AdsRewardUI.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/8/29.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef AdsRewardUI_h
#define AdsRewardUI_h

#include "UISingletonDialog.h"

class AdsRewardUI : public UISingletonDialog<AdsRewardUI>
{
public:
    AdsRewardUI();
    virtual ~AdsRewardUI();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "AdsRewardUI"; }
    
    // ButtonListener
    virtual void ButtonDepress(int i_id) override;
    
    void setReward(int objectID,int quantity);
    
    void setTitleShow(bool bShow);
protected:
    void setQuantity(int quantity);
    
private:
    int m_objectID;
    int m_quantity;
    
    class Effect_PopAnim* m_lightEffect = nullptr;
};

class UIPlantPieceImage : public Sexy::Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    
    void SetPlantPiece(const std::string& plant_name);
    
    Sexy::Rect GetPlantRect();
private:
    std::string m_plantPieceName;
};

#endif /* AdsRewardUI_h */
