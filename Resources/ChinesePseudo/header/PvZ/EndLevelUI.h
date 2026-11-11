//
//  StoreUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 8/31/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EndLevelUI__
#define __PlantsVersusZombies2__EndLevelUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "MagentoService.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "ActivityConfig.h"
#include "PVZ2UIButton.h"
#include "PopAnimRig.h"
#include "EASquared.h"

class EndLevelUI : public Widget, public ButtonListener
{
public:
    EndLevelUI();
    virtual ~EndLevelUI();
    virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
    virtual void Resize(int theX, int theY, int theWidth, int theHeight) override;
    
    virtual void			ButtonDepress(int theId) override;
    
    void setCollectableType(CollectableTypePtr collectable);
    CollectableTypePtr getCollectableType() { return m_collectableType; }
    void setNormalAwardCoinCount(int count);
    int getNormalAwardCoinCount() { return m_normalAwardCoinCount; }
    
    StandaloneEffect* createStandaloneEffect(const CollectableType* i_type);
    
    void OutState();
    
    void setFinished(bool finish) { m_finished = finish;}
    bool isFinished() { return m_finished;}
    class PVZ2UIButton* getContinueButton() { return m_continueBtn; }
    void GetChestRewards();
    bool isHardLevel() { return m_hardLevel; }
    void createAdsBtn();
    void generateAdsBtn();
    void ShowContinueBtnBg();
    void onGetReward(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    
    void onAdsAnimStopped(const std::string& i_animLabel);
    
    void SetRewardCoins(int coins);
    
    void OnCustomLevelEnd();
    void OnPennyClassroomEnd();
    void CoinIn();
    void DoubleCoinIn();
    
    void ShowAds();

    void setOtherReward(int itemId, int itemCount);

private:
    bool CheckEndlevelAdvertisement();// max 3 counts in one day
    void FinishEndlevelAdvertisement();
    void CreateCustomLevelRateMenu();

private:
    class DNodeWidget* m_content;
    
    class PVZ2UIButton*   m_continueBtn;
    class PVZ2UIButton*   m_reportBtn;
    class PVZ2UIButton*   m_collectBtn;
    class PVZ2UIButtonAds* m_adsBtn;
    class PopAnimRig* m_endLevelRig;
    CollectableTypePtr m_collectableType;
    StandaloneEffect* m_pieceAwardEffect;
    std::map<int, int> m_otherReward;
    
    bool m_hardLevel;
    bool m_showAds;
    int m_normalAwardCoinCount;
    bool m_finished;
    
    int m_doubleCoins;
    bool m_hasMedia;
    bool m_drawDoubleAdsImage;// if drwa ads_btn icon
    pvztime_t m_timePlay;
};

class PVZ2UIButtonAds : public PVZ2UIButton
{
public:
    PVZ2UIButtonAds(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
    virtual ~PVZ2UIButtonAds();
    
    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
    
    void SetAnimRig(const std::string& anim);
    void SetScale(float scale);
    float GetScale() { return m_scale; }
    void SetSize(int width,int height);
    void PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select = SELECT_EXACT, PopAnimRig::AnimStoppedDelegate i_onAnimStopped = PopAnimRig::AnimStoppedDelegate());
    
private:
    class PopAnimRig* m_adsEffect = nullptr;
    float m_scale = 1.f;
};


#endif
