//
//  EliminateModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-3-16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EliminateModule__
#define __PlantsVersusZombies2__EliminateModule__

#include "LevelModule.h"
#include "Core.h"
#include "GameEventMgr.h"
#include "EliminateItem.h"
#include "Plant.h"
#include "TimeLine.h"
#include "ReviveUI.h"
#include "PrimeTextWidget.h"
#include "Effect_FloatingText.h"
#include "AnimationMgr.h"
#include "Effect_BouncingArrow.h"

enum EliminateState
{
    PVZ_BEGIN_ENUM(ELIMINATESTATE_),
    ELIMINATESTATE_FALLITEM,
    ELIMINATESTATE_TOUCH,
    ELIMINATESTATE_ELIMINATE,
    ELIMINATESTATE_SHOOT,
    ELIMINATESTATE_FAIL,
    PVZ_END_ENUM(ELIMINATESTATE_)
};

struct EliminatePlacementProperties
{
	EliminatePlacementProperties()
	{
		GridX = 0;
		GridY = 0;
        
        EliminateType = 0;
        
        Block = false;
	}
	
	int                 EliminateType;
	int					GridX;
	int					GridY;
    bool                Block;
};

struct EliminateFenceProperties
{
	EliminateFenceProperties()
	{
		Row       = 0;
		Col       = 0;
        FenceType = 0;
	}
    
	int                 FenceType;
	int					Row;
	int					Col;
};

class EliminateModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(EliminateModule, LevelModule, RtClass);
    
    EliminateModule();
    virtual ~EliminateModule();
    
    int             GetEliminateCount();
    EEliminateType  GetSelectType();
    float           GetHitpointPercent();
    
    std::vector<EliminateFenceProperties> & GetEliminateFence();
    
    bool            CanFreezingWind();
    bool            CanSpawnShield();

    int             GetFreezingWindRow();
    int             GetPlantIndexStart();
    
    bool            NeedShowShieldTip(int i_type);
    
	virtual void    AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    
    bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
    
private:
	void onLoadComplete();
    void onUpdate();
    void onLevelStarted();
    void onGameplayStarted();
    bool preventSave();
    
    void addToRenderQueue(class RenderQueue* i_queue);
	void renderStep(Graphics* i_g);
    void renderHighLight(Graphics* i_g);
    
    void onInitFallDone(BoardEntity * target);
    void onReloadFallDone(BoardEntity * target);
    void onFallDone(BoardEntity * target);
    void onEliminateDone(BoardEntity * target);
    void onPlantFoodEliminateDone(BoardEntity * target);
    void onColorMoveDone(BoardEntity * target);
    
    void onPlantfoodButtonPrimed();
    void onToolAppliedPlantFood(class PlantGroup* i_plant);
    void onPlantFire();
    void onPlantFoodEnd(Plant* i_plant);
    void onZombossMechTakeDamage(const std::string& plant_name);
    
    void onSetCurrentStage(int i_currentStage, int i_scoreValue);
    
    void ontakeFreezingWind();
    void ontakeSpawnShield();
    
    void onMissionFinish();
    void onIntroNarrationFinished();
    void onNarrationFinished();
    
    void onZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
    void onZombieIceAgeChiefSpwanWind(int i_row);
    
    void onReviveCancel();
    void onReviveOK();
    
    void onCursorAdded(class BaseCursor* i_cursor);
    
    void onPlantDied(Plant* i_plant);
    void onHolonutWillDie();
    
    void onEliminateShieldDestroyed(int i_gridY);
    void onEliminateFenceDestroyed(int i_row,int i_col,int i_type);
    void onEliminateColorDisappear(int i_row,int i_col);
    
    void InitEliminates();
    void ReloadEliminates();
    
    bool canEliminate();
    void GetNearByItems(EliminateItem * item,
                        std::vector<EliminateItem*>& nearBys,
                        std::vector<EliminateItem*>& paths);
    
    std::vector<EliminateItem*> SearchNearBy(std::vector<EliminateItem*> nearBys,
                                             std::vector<EliminateItem*> paths,
                                             bool findEnd);
    
    void checkEliminateCount();
    
    bool checkHavePlantFood();
    bool checkHaveBlock();
    
    void checkPlantFoodNearBy();
    void checkBlockNearBy();
    void checkFenceNearBy();
    
    void setState(EliminateState state);
    
    void setNearByItemsAlpha(EliminateItem * cur_item);
    void clearItemsAlpha();
    void clearItemsShowTip();
    
    EliminateItem * GetItemFromTouch(const SexyVector2 &touch);
    
    bool addToSelectItems(EliminateItem * item);
    void clearSelectItems();
    
    int             rowHaveZombie(int row);
    EliminateItem * createEliminate(int row, int col);
    
    int  getDirection(EliminateItem * cur , EliminateItem * next);
    
    int  GetEmptyRowFromButtom(int col);
    void fillVacancies();
    
    void takeEliminate();
    void takeShoot();
    void takePlantFood();
    
    void FindAndPlayShowTip();
    
    void ResetGlovePosition();
    
    void changeMinColor(EEliminateType i_type,Zombie* i_zombie);
    
    Effect_BouncingArrow* addPlantfoodArrow();
    Effect_BouncingArrow* addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void				  clearBouncingArrows();
    Effect_BouncingArrow* addPlantArrow();
    Effect_BouncingArrow* addEliminatePlantFoodArrow(int row, int col);
    
private:
    
    Sexy::TouchID m_touchIdent;
    
    EliminateItem **m_matrix;
    
    EliminateState              m_state;
    
    EliminateItem             * m_curItem;
    std::vector<EliminateItem*> m_selectItems;
    EEliminateType              m_selectType;
    
    EEliminateType              m_changeColorType;
    
    std::vector<RtWeakPtr<Effect_PopAnim> >     m_Lines;
    
    int                         m_index_eliminate;
    
    int                         m_shootCount;
    std::vector<PlantPtr>       m_plants;
    
    int                         m_freezingRow;
    int                         m_freezingCol;
    
    EliminateItem *             m_plantfoodItem;
    bool                        m_usePlantFood;
    bool                        m_createPlantFood;
    
    int                         m_PlantFoodIndex;
    int                         m_createEliminateIndex;
    
    int                         m_nEliminateCount;
    int                         m_nEliminateMaxCount;
    
    bool                        m_bCanFreezingWind;
    bool                        m_bCanSpawnShield;
    
    pvztime_t                   m_TimeShowTip;
    bool                        m_InShowTip;
    
    bool                        m_gloveIntro;
    bool                        m_plantfoodIntro;
    bool                        m_eliminatePlantFoodIntro;
    bool                        m_playerWon;
    bool                        m_playerLost;
    
    bool                        m_showReviveUI;
    
    pvztime_t                   m_checkEliminateTime;
    
    RtWeakPtr<class Effect_PopAnim>   m_gloveEffect;
    TimeLineTrack<SexyVector3>        m_glovePosition;
    SexyVector3                       m_gloveStartPos;
    pvztime_t                         m_gloveStartTime;
    
    //TimeLine                          m_timeLineStep;
    //Sexy::PrimeTypeface*              m_StepFont;
    
    //float                             m_StepScale;
    //TimeLineTrack<int>                m_TrackStep;
    
    pvztime_t                         m_timeAddStep;
    
    int                               m_comboNum;
    bool                              m_comboGap;
    
    //Effect_StepText*                  m_StepText;
    
    Sexy::PrimeTextWidget*            m_StepTextWidget;
    
    
    float                             m_scale;
    float                             m_finalScale;
    float                             m_initScale;
    
    pvztime_t                         m_scaleStartTime;
    pvztime_t                         m_scaleEndTime;
    
    //AnimationMgrWkPtr                 m_animationMgr;
    std::vector<StandaloneEffectPtr>  m_bouncingArrows;
    
    std::vector<int>                  m_shields;
    
    std::vector<EliminateFenceProperties>     m_Fences;
    
    std::vector<PopAnimRig*>                  m_protectTileRigs;
    RtWeakPtr<class PopAnimRig>               m_protectTileRig;
};


class EliminateProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(EliminateProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return EliminateModule::StaticGetClass();
	}
	
	EliminateProperties()
	{
        NarrativeStageIndex  = 0;
		MaxStep              = 30;
        FreezingWindStep     = 6;
        PlantFoodProbability = 0.5;
        HitpointPercent      = 1;
        CanSpawnShield       = true;
        GloveIntro           = false;
        BossGameOver         = false;
        ProtectPlant         = "tallnut";
        ProtectPlantLevel    = 2;
	}
    
    int   MaxStep;
    int   FreezingWindStep;
    float PlantFoodProbability;
    float HitpointPercent;
    bool  CanSpawnShield;
    bool  GloveIntro;
    bool  BossGameOver;
    int   NarrativeStageIndex;
    
    std::string                               ProtectPlant;
    int                                       ProtectPlantLevel;
    
    std::vector<std::string>                  Plants;
    std::vector<EliminatePlacementProperties> Placements;
    std::vector<EliminateFenceProperties>     Fences;
};

namespace Message
{
	void EliminateOnce();
    void takeFreezingWind();
    void takeSpawnShield();
    void zombossMechTakeDamage(const std::string& plant_name);
    void EliminateBlocked(int i_row,int i_col);
}

#endif /* defined(__PlantsVersusZombies2__EliminateModule__) */
