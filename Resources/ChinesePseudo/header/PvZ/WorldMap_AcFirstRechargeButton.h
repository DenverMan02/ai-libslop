//
//  WorldMap_AcFirstRechargeButton.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_AcFirstRechargeButton__
#define __PlantsVersusZombies2__WorldMap_AcFirstRechargeButton__

#include "UIEasyButtonWidget.h"
#include "LawnAppEnums.h"
#include "Effect_PopAnim.h"

namespace Message
{
	void AcFirstRechargeSuc(bool i_success);

}

struct stFirstChargeAward
{
    int m_nAwardID = 0;
    int m_nAwardNum = 0;
};

class FirstChargeAwardConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(FirstChargeAwardConfig, RtObject, RtClass);
	FirstChargeAwardConfig() {}

public:
	std::vector<stFirstChargeAward> m_vecAwardList;
};

class WorldMap_AcFirstRechargeButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_AcFirstRechargeButton, UIEasyButtonWidget, RtClass);
    
	WorldMap_AcFirstRechargeButton();
    virtual ~WorldMap_AcFirstRechargeButton();
    
    void Draw(Sexy::Graphics* i_g) override;

    void OnNotyFirstRechargeSuc(bool i_success);
    void BackToMap();
    
    bool CheckActivated();
protected:
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    
private:
    void onUpdate() override;
    void onButtonClicked();
    void onWorldLoaded();

    void InitShinningAnim();
    bool CheckEnable();// check if show the icon

    Effect_PopAnim * m_shinningAnim;
    bool m_isClickButton;

};


//-----------------------------------------------------------------
// AcFirstRechargeManager
//-----------------------------------------------------------------
class AcFirstRechargeManager : public LazySingleton<AcFirstRechargeManager>
{
public:
    AcFirstRechargeManager() : m_bIsAlreadyRecharge(false) {}
    void setIsAlreadyRecharge(bool isAlreadyRecharge);
    bool getIsAlreadyRecharge() const;
private:
    bool m_bIsAlreadyRecharge;
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_AcFirstRechargeButton__) */
