//
//  PVZ2UILotteryResult.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 16-7-22.
//  Copyright (c) 2016年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PVZ2UILotteryResult__
#define __PlantsVersusZombies2__PVZ2UILotteryResult__

#include "Precompile.h"

#include "Widget.h"
#include "RtObject.h"
#include "Core.h"
#include "Effect_PopAnim.h"
#include "PlantType.h"
#include "SexyAppFramework/PerfTimer.h"
#include "Curve.h"
#include "SalesUI.h"

namespace Message
{
    void NotifyFinishMotion();
}

enum IconMotion
{
    PVZ_BEGIN_ENUM(Icon_Motion_),
    Icon_Motion_Idle,
    Icon_Motion_InterpolateAndScale,
    PVZ_END_ENUM(Icon_Motion_),
};

enum LotteryInfoIndex
{
    LOTTERY_INFO_INDEX_FIRST,
    LOTTERY_INFO_INDEX_SECOND,
    LOTTERY_INFO_INDEX_COUNT
};

struct LotteryResultIconInfo
{
    LotteryResultIconInfo()
    {
        Type = "";
        Scale = 1.0f;
    }
    // If type is a plant piece, using "plant_piece_...", else using standaloneimage like "IMAGE_ENDLEVEL_..."
    std::string Type;
    SexyVector3 StartPoint;
    SexyString Description;
    float Scale;
};

class LotteryResultProgressBar : public RealObject
{
public:
    LotteryResultProgressBar();
    ~LotteryResultProgressBar();
    
    void OnUpdate();
    void OnDraw(Graphics* i_g);
    
    void SetVisible(bool i_visible);
    
    void InitView(Rect i_rect);
    void InitAnims();
    void StartToShow();
    void OnRefresh();
    
    void RefreshAdvanceProgress();
    void MoveAdvanceProgressTo(int i_pieces);
    
    bool IsLevelUp();
    int GetCurrentLevel();
    int GetAdvanceLevel();
    int GetCurrentPieces();
    int GetAdvancePieves();
    
    Rect GetStartRect() { return m_progressStartRect; }
    
    void SetRewardPlantType(const std::string& i_type) { m_rewardPlantType = i_type; }
    
    void SetPlantRewardPiece(int i_pieces) { m_plantRewardPieces = i_pieces; }
    
private:
    void SetProgress(int i_pieces);
    void SetAdvanceProgress(int i_pieces);
    
    void RefreshProgress();
    void MoveProgressTo(int i_pieces);
    
    void StartProgressTimer();
    void StartAdvanceProgressTimer();
    
    void UpdatePieceToShow();
    void UpdateAdvancePieceToShow();
    
    void HandleAdvanceProgress();
    void InitProgressBar();
    void Resize(Rect i_rect);
    
    void OnAnimOn(const std::string& i_animLabel);
    
private:
    bool m_visible;   
    
    int m_maxLevel;
    int m_maxPieces;
    int m_currentLevel;
    int m_realLevel;
    int m_advanceLevel;
    int m_lastRealLevel;
    int m_lastAdvanceLevel;
    
    Rect m_progressRect;
    Rect m_percentRect;
    Rect m_advancePercentRect;
    Rect m_progressStartRect;
    
    Point m_progresslevelPoint[5];
    
    ImagePtr m_progressBarBG;
    ImagePtr m_advanceProgressBar;
    ImagePtr m_progressBar;
    ImagePtr m_progressStart;
    ImagePtr m_seprator;
    
    EffectAnim_UIAnim m_levelAnim[5];
    
    int m_pieces;
    int m_advancePieces;
    int m_piecesShow;
    int m_advancePiecesShow;
    int m_lastPieces;
    int m_lastAdvancePieces;
    
    SalesTimer m_advanceProgressTimer;
    
    std::map<int, int> m_levelUp;
    
    std::string     m_rewardPlantType;
    
    int m_plantRewardPieces;
};

class LotteryResultIconWidget : public RealObject
{
public:
    RT_CLASS_DEFINE(LotteryResultIconWidget, RealObject, RtClass);
    
    LotteryResultIconWidget();
    virtual ~LotteryResultIconWidget();
    
    void            InitView();
    
    void            onDraw(Graphics* i_g) override;
    void            onUpdate();
    void            UpdateMotion();
    
    void SetMotionInterpolateAndScale(const SexyVector3& i_initialPosition, const SexyVector3& i_finalPosition, float i_initialScale, float i_finalScale, pvztime_t i_duration, CurveType i_interpMethod);
    
    void SetMotionIdle();
    
    StandaloneEffectPtr GetResultBGEffect() { return m_result_bg_effect; }
    
    void ShowResultEffect(bool i_show);   
    
    void initializeRenderEffect(const std::string& i_type);
    
    void initializeBackgroundRenderEffect();
    
    void SetType(LotteryInfoIndex i_type) { m_type = i_type; }
    
    void SetInitScale(float i_scale) { m_initScale = i_scale; }
    
    float GetInitScale() { return m_initScale;}
    
    void SetDescription(const SexyString& i_description) { m_description = i_description; }
    
private:
    void onFinishMotion();
    StandaloneEffect* CreateSelfRenderEffect(const std::string& i_type);
    StandaloneEffect* CreateResultBGEffect();
private:
    
    IconMotion 	m_motion;
    pvztime_t			m_motionStartTime;
    SexyVector3		m_interp_initialPosition;
    SexyVector3		m_interp_finalPosition;
    float			m_interp_initialScale;
    float			m_interp_finalScale;
    pvztime_t		m_interp_duration;
    CurveType		m_interp_method;
    
    float           mCurAnimScale;
    StandaloneEffectPtr m_result_bg_effect;
    StandaloneEffectPtr m_renderEffect;
    LotteryInfoIndex m_type;
    float           m_initScale;
    bool            m_finishMotion;
    SexyString      m_description;
};

class PVZ2UILotteryResult: public Sexy::Widget
{
public:
    PVZ2UILotteryResult(int iWidth, int iHeight);
    virtual ~PVZ2UILotteryResult();    
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;
    
    void SetLotteryInfo(LotteryInfoIndex i_index, const LotteryResultIconInfo& i_info);
    
    void InitViews(int progressStartX, int width);
    void SetProgressPieces(int i_pieces);
    int  GetNumIcons() { return (int)m_icons.size(); }
    void SetRewardPlantType(const std::string& plant);
protected:
    virtual	void TouchEnded(const Sexy::Touch& touch) override;
private:
    void CreateIcons();
    void MoveIcons();
    void onNotifyFinishMotion();
    
    // LotteryResultProgressBar    m_progress;
    Rect                        m_progressRect;
    std::vector<LotteryResultIconWidget*>    m_icons;
    std::string                 m_rewardPlantType;
    LotteryResultIconInfo       m_lotteryInfos[LOTTERY_INFO_INDEX_COUNT];
    bool                        m_canDrawTitle;
};

#endif /* defined(__PlantsVersusZombies2__PVZ2UILotteryResult__) */
