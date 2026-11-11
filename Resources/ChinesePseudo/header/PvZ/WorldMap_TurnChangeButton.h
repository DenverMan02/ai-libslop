/*
 * WorldMap_TurnChangeButton.h
 *
 *  Created on: 2021-3-25
 *      Author: zhousen
 */

#ifndef WORLDMAP_TURNCHANGEBUTTON_H_
#define WORLDMAP_TURNCHANGEBUTTON_H_

#include "UIEasyButtonWidget.h"
#include "GameDefine.h"


class WorldMap_TurnChangeButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_TurnChangeButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_TurnChangeButton();
    virtual ~WorldMap_TurnChangeButton();
    
    virtual bool CheckActivated();
    virtual void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    void showOpenErrorDialog();

protected:
    void onUpdate() override;
    virtual void onButtonClicked();
    virtual void onWorldLoaded();
    virtual void onNotifyBackFromRift();
    virtual void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList);
    virtual void onWorldLoadedReal();
    virtual void onNotifyBackFromRiftReal();

protected:
    bool m_bRequested;
};

class WorldMap_OneYuanButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_OneYuanButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_OneYuanButton();
    virtual ~WorldMap_OneYuanButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_PiggyBankButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_PiggyBankButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_PiggyBankButton();
    virtual ~WorldMap_PiggyBankButton();
    
    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_DaveTreasureButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_DaveTreasureButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_DaveTreasureButton();
    virtual ~WorldMap_DaveTreasureButton();
    
    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_CallOfWishButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_CallOfWishButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_CallOfWishButton();
    virtual ~WorldMap_CallOfWishButton();
    
    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_ArtifactPresentButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_ArtifactPresentButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_ArtifactPresentButton();
    virtual ~WorldMap_ArtifactPresentButton();
    
    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_PVZ2UnchartedModeButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_PVZ2UnchartedModeButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_PVZ2UnchartedModeButton();
    virtual ~WorldMap_PVZ2UnchartedModeButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_GrowthPackageButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_GrowthPackageButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_GrowthPackageButton();
    virtual ~WorldMap_GrowthPackageButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_BattleOrderButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_BattleOrderButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_BattleOrderButton();
    virtual ~WorldMap_BattleOrderButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;

    void CheckThemeVersion();
};

class WorldMap_TenYearRecordButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_TenYearRecordButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_TenYearRecordButton();
    virtual ~WorldMap_TenYearRecordButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_LimitedSummonButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_LimitedSummonButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_LimitedSummonButton();
    virtual ~WorldMap_LimitedSummonButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_CarnivalButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_CarnivalButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_CarnivalButton();
    virtual ~WorldMap_CarnivalButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_NewYearGoods : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_NewYearGoods, WorldMap_TurnChangeButton, RtClass);

    WorldMap_NewYearGoods();
    virtual ~WorldMap_NewYearGoods();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_CornucopiaButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_CornucopiaButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_CornucopiaButton();
    virtual ~WorldMap_CornucopiaButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_InvitationButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_InvitationButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_InvitationButton();
    virtual ~WorldMap_InvitationButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_PlantCultivateButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_PlantCultivateButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_PlantCultivateButton();
    virtual ~WorldMap_PlantCultivateButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_GiftFoReturn : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_GiftFoReturn, WorldMap_TurnChangeButton, RtClass);

    WorldMap_GiftFoReturn();
    virtual ~WorldMap_GiftFoReturn();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

class WorldMap_PartyAssistButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_PartyAssistButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_PartyAssistButton();
    virtual ~WorldMap_PartyAssistButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};


class WorldMap_NewYearGiftBoxButton : public WorldMap_TurnChangeButton
{
public:
    RT_CLASS_DEFINE(WorldMap_NewYearGiftBoxButton, WorldMap_TurnChangeButton, RtClass);

    WorldMap_NewYearGiftBoxButton();
    virtual ~WorldMap_NewYearGiftBoxButton();

    bool CheckActivated() override;
    void onButtonClicked() override;
    void onNotifyRefreshActivityListReal(bool i_success, const std::set<int>& changeList) override;
};

#endif /* WORLDMAP_TURNCHANGEBUTTON_H_ */
