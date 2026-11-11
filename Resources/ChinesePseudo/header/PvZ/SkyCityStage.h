//
//  SkyCityStage.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-6-10.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SkyCityStage__
#define __PlantsVersusZombies2__SkyCityStage__

#include "StageModule.h"
#include "Projectile.h"
#include "Effect_BouncingArrow.h"

enum eBoardLevelType
{
    BoardType_Level1 = 1,
    BoardType_Level2,
    BoardType_Level3,
    BoardType_Count
};

enum eCannonLevelType
{
    CannonType_Level1 = 1,
    CannonType_Level2,
    CannonType_Level3,
    CannonType_Count
};

enum CannonIntroState
{
    CannonIntroState_Init,
    CannonIntroState_Use_Narrative,
    CannonIntroState_UISkyCannonArrow,
    CannonIntroState_ZombieArrow,
    CannonIntroState_Done
};

struct CloudImageInfo
{
    float       PosX;
    float       PosY;
    int         Type;
    float       Scale;
    float       Width;
    float       Step;
    
    CloudImageInfo();
    
    void Update();
    void Reset();
    void SetType(int i_type);
};

struct ShakeInDamagePercent
{
    float   Percent;
    bool    Shaked;
    
    ShakeInDamagePercent(float i_percent, bool i_shaked)
    {
        Percent = i_percent;
        Shaked  = i_shaked;
    }
    
    ShakeInDamagePercent()
    {
        Percent = 0.0f;
        Shaked  = false;
    }
};

class SkyCityStage : public StageModule
{
public:
	RT_CLASS_DEFINE(SkyCityStage, StageModule, RtClass);
    
    SkyCityStage();
	virtual ~SkyCityStage();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	void SetCannonPosition(const SexyVector2& pos);
	void SetCannonScale(float fScale);
	void SetCannonLevel(eCannonLevelType i_level);
	eCannonLevelType	GetCannonLevel() const { return m_cannonLevel; }
	void SetCanAutoFire(bool setting) { m_canAutoFire = setting; }
	bool FireCannon(const Sexy::Point &i_boardSpace, bool checkBoard = true);
	bool IsHaveGridItemAirShip() const;
    static int GetShipWidth();
protected:
    
    void initializeModule()  override;
	void registerForEvents() override;
    
    void renderBesiegeBG(Graphics* i_g);
    void renderRunBackground(Graphics* i_g);
    
    virtual void onLevelLoaded() override;
    
    void onProgressMeterSetFlagCount(int i_flagCount);
    
private:
    void addBackgroundToRenderQueue(class RenderQueue* i_queue);
    void onUpdate();
    void onStartGameButtonPressed();
    void onGameplayStarted();
    void onDrawSelectionOnBoard(Sexy::Graphics *i_g);
    void onRenderAirscrew(Sexy::Graphics *i_g);
    void onRenderCannon(Sexy::Graphics *i_g);

    void onReviveSucceed();
    void onReviveClose();
    
    void onThunderStart();
	void onThunderEnd();
    
    bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
    
    void onSkyCannonPressed();
    
    void onAirshipTakeDamage(float i_amount);
    
    void autoFire();
    
    void resetShakeInfos();
    
    void onCannonFireAnimCommand(const std::string& i_animLabel,
                                 pvztime_t i_timeStamp,
                                 const std::string& i_animCommand,
                                 const std::string& i_animCommandParam);
    
    void onCannonIntroNarrationFinished();
    void onCannonEndNarrationFinished();
    
    Effect_BouncingArrow * addBouncingArrow(const Sexy::SexyVector2 &i_screenLocation);
    void                   clearBouncingArrows();
    
    void                   addUISkyCannonArrow();
    
private:
    int                         m_offset_x;
    eCannonLevelType            m_cannonLevel;
    eBoardLevelType             m_boardLevel;
	SexyVector2                 m_cannonPosition;
	float						m_cannonScale;
    bool						m_cannonActive;
    bool						m_thunderActive;
    float						m_airShipHealth;
    float                       m_airShipHealthMax;
    int                         m_indexProjectile;
    bool                        m_playerLost;
    bool                        m_ignoreRevive;
    float                       m_hardScale;
    
    CannonIntroState            m_StateCannonIntro;
    bool                        m_IsCannonIntro;
    bool                        m_IsBoardIntro;
    
    pvztime_t m_timeAutoFire;
    bool      m_canAutoFire;
    bool      m_isAutoFire;
    
    bool      m_isGamestart;
    
    std::vector<CloudImageInfo>           m_CloudInfos;
    std::vector<ShakeInDamagePercent>     m_ShakeInfos;
    
    Sexy::TouchID                   m_touchIdent;
    Sexy::Point                     m_touchPos;
    
    RtWeakPtr<class Effect_PopAnim> m_cannonEffect;
    
    RtWeakPtr<class Effect_PopAnim> m_airscrewEffect1;
    Color                           m_effect1Color;
    
    RtWeakPtr<class Effect_PopAnim> m_airscrewEffect2;
    Color                           m_effect2Color;
    
    std::vector<StandaloneEffectPtr>m_bouncingArrows;
};

class SkyCityStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(SkyCityStageProperties, StageModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return SkyCityStage::StaticGetClass();
	}

	SkyCityStageProperties();
    
    float		MaxAirShipHealth;
	bool		HasGridItemAirShip;
	bool		HasCannon;
    
    float       AutoCannonDamage1;
    float       AutoCannonDamage2;
    float       AutoCannonDamage3;
    
    float       SkillCannonDamage2;
    float       SkillCannonDamage3;
    
    float       AutoFireInterval;
    float       SkillFireInterval;
};

class BoardRegionSky : public BoardRegion
{
public:
    RT_CLASS_DEFINE(BoardRegionSky, BoardRegion, RtClass) {}
    
    BoardRegionSky();
    
    void GatherPlantingRestrictions(const Sexy::Point &i_atLocation, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors) override;    
};

class CannonFireProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CannonFireProjectile, Projectile, RtClass);
    
    virtual int GetRenderOrder() const override { return RENDER_LAYER_ABOVE_UI; }
	virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
};

namespace Message
{
	void ThunderStart();
	void ThunderEnd();
}

#endif /* defined(__PlantsVersusZombies2__SkyCityStage__) */
