//
//  UniverseWorldInfo.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 16/3/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UniverseWorldInfo_h
#define UniverseWorldInfo_h

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "ResourceHelpers.h"
#include "WorldData.h"
#include "Widget.h"
//#include "PVZ2UIButton.h"
//#include "Effect_PopAnim.h"
#include "EffectAnim_UIAnim.h"
#include "WorldMap.h"
#include "UniverseMap.h"
#include "EASquared.h"

namespace
{
    const int k_world_difficulty = 5;
}

class PlantScrollPanel : public Widget
{
public:
    PlantScrollPanel(Sexy::Rect &i_rect, const std::vector<std::string>& i_nameList);
    virtual ~PlantScrollPanel();
    
private:
    void	InitView();
    
private:
    std::vector<std::string> m_contents;
};


class UniverseWorldInfo : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
    
public:
    UniverseWorldInfo(const std::string& i_worldName);
    virtual ~UniverseWorldInfo();
    
    void Draw(Graphics *i_g) override;
    void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;
    void Update() override;
    void ButtonDepress(int theId) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void CloseWorldInfo();
    
private:
    void InitView();

    void OnWorldNameAppeared(const std::string& i_animLabel);
    void OnLevelDetailClosed(const std::string& i_animLabel);
    void OnPlantDetailClosed(const std::string& i_animLabel);
    void OnDialogBgClosed(const std::string& i_animLabel);
    
    void OnWorldNameDisappeared(const std::string& i_animLabel);
    void OnDialogBgOpened(const std::string& i_animLabel);
    void OnHardDialogBgOpened(const std::string& i_animLabel);
    void OnLevelDetailOpened(const std::string& i_animLabel);
    void OnPlantDetailOpened(const std::string& i_animLabel);
    
    void DrawWorldImage(Graphics *i_g);
    void CalcWorldPosAndScale();
    
    void FadeOutWorldImage();

    void UnlockByStar();
    void UnlockByGem();
    void wrapPurchase();
    void DoPurchaseSuccess(MagentoProductPropsPtr i_props);
    void OnPurchaseConfirm(MagentoProductPropsPtr i_props);
    void OnPurchaseClosed();
    
    std::string GetCurrentWorldNameAppearAnim();
    std::string GetCurrentWorldNameIdleAnim();
    std::string GetCurrentWorldNameDisappearAnim();

    void HideWorlds();
    void ShowWorlds();
    void RecocerUniverseMap();
    
    void UnlockCancel();
    void GemUnlockConfirm();
    void StarUnlockConfirm();
    
    void DetailOpeningHard(const std::string& i_animLabel);
    void DetailLoopingHard(const std::string& i_animLabel);
    void DetailClosingHard(const std::string& i_animLabel);
    
    void DetailOpeningEasy(const std::string& i_animLabel);
    void DetailLoopingEasy(const std::string& i_animLabel);
    void DetailClosingEasy(const std::string& i_animLabel);
    
    void SolveMarks();
    
    void PlayTransitionEffect();
    void UpdateTransitionEffect();
    void DrawTransitionEffect(Graphics* i_g);
    
    void TransToWorld(const std::string& i_animLabel);

private:
    // World Data read from worldmaplist.json
    const MapListNode* m_worldData;
    
//    class Effect_PopAnim* m_backgroundAnim;
//    class Effect_PopAnim* m_plantDetailAnim;
    //    class Effect_PopAnim* m_levelDetailAnim;
    
#ifdef HOST_ANDROID
    void OnUnlockedByGemCallBack(const bool& i_success);
#else
    void OnUnlockedByGemCallBack(const bool& i_success);
#endif
    
    bool m_shouldDrawDetail;
    bool m_shouldDrawWidget;
    bool m_shouldShowHardLevel;
    
    bool m_plantshown;
    bool m_isHardShowing;
    bool m_worldMoving;
    bool m_entering;
    bool m_transing;
    bool m_unlocking;
    bool m_fading;
    
    bool m_starCupMarked;
    bool m_bossCupMarked;
    bool m_plantCupMarked;
        
    int m_worldDifficulty;
    int m_worldHardDifficulty;
    int m_starsWeHave;
    int m_starsRequiredToUnlock;
    
    float m_fadePercent;
    float m_worldScale;
    pvztime_t m_startingTime;
    pvztime_t m_startingFadeOutTime;
    pvztime_t m_startingClosingTime;
    
    UniverseMap* m_universeMap;
    bool m_unlocked;
    bool m_needPay;
    
    std::string m_worldName;
    
    Rect m_progressTitleRect;
    Rect m_progressStartRect;
    Rect m_progressBgRect;
    Rect m_progressRect;
    Rect m_progressEndRect;
    Rect m_progressPercentRect;
    
    Rect m_plantCupRect;
    Rect m_bossCupRect;
    Rect m_starCupRect;
    
    Point m_worldPos;
    Point m_worldStartPos;
    Point m_worldTargetPos;
    
    SexyString m_worldNameStr;
    SexyString m_progressPercent;
    
    ImagePtr m_worldImage;
    ImagePtr m_worldDescImage;
    
    ImagePtr m_progressTitle;
    ImagePtr m_progressStart;
    ImagePtr m_progressBar;
    ImagePtr m_progressEnd;
    ImagePtr m_progressBg;
    
//    ImagePtr m_plantCup;
//    ImagePtr m_bossCup;
//    ImagePtr m_starCup;
    
    class PVZ2UIButton* m_worldBtn;
    class PVZ2UIButton* m_closeBtn;
    class UIWidgetImage* m_gemImage;
    
    PVZ2UIScrollingWidget* m_scrollingWidget;
    
    EffectAnim_UIAnim m_backgroundAnim;
    EffectAnim_UIAnim m_worldNameAnim;
    EffectAnim_UIAnim m_plantDetailAnim;
    EffectAnim_UIAnim m_levelDetailAnim;
    EffectAnim_UIAnim m_starCupAnim;
    EffectAnim_UIAnim m_bossCupAnim;
    EffectAnim_UIAnim m_plantCupAnim;
    EffectAnim_UIAnim m_hardDifficulity[k_world_difficulty];
    // EffectAnim_UIAnim m_transitionAnim;
    PopAnimRig* m_transingEffect;
    
    const MapEventItem*	m_startStargateEvent;
    MagentoProductPropsPtr m_magentoCache;
};

#endif /* UniverseWorldInfo_h */
