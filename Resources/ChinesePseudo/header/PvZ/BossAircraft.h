//
//  BossAircraft.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-7.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BossAircraft__
#define __PlantsVersusZombies2__BossAircraft__

#include "BoardEntity.h"
#include "GridItem.h"

enum EBossAircraftType
{
    EBossAircraftType_Down = 0,
    EBossAircraftType_Up,
    EBossAircraftType_Count
};

enum EBossAircraftState
{
    EBossAircraftStateInit = 0,
    EBossAircraftStateForward,
    EBossAircraftStateTransform,
    EBossAircraftStateAttack,
    EBossAircraftState_Count
};

class BossAircraft : public GridItem
{
public:
	RT_CLASS_DEFINE(BossAircraft, GridItem, RtClass);
    
	BossAircraft();
	virtual ~BossAircraft();
    
    virtual Sexy::Rect calcCollisionRect() override;
    Rect GetAttackRect();
    
    bool CollidesWithType(CollisionTypeFlags testTypes) const override;
    
    bool IsDamageable() const                   override;
    bool IsDamageableByPlants() const           override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    
    void BossAircraftInitialize(EBossAircraftType i_type,int i_IndexAircraft, float hitpoints, float damage);
    
    int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override { return false; }

    int  GetIndexAircraft() const;
    
protected:
    
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate()  override;
	virtual void onDestroy() override;
    void onKilled()          override;
    virtual void onTakeDamage(const DamageInfo& i_damage) override;
    
    void         onTransformAnimDone(const std::string& i_label);
    
    void         onAircraftSeparateDone(int i_IndexAircraft);
    void         onAircraftDisconnect(int i_IndexAircraft);
    
private:
    
    EBossAircraftType           m_eType;
    EBossAircraftState          m_eState;
    
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    int                         m_IndexAircraft;
    float                       m_damage;
    
    pvztime_t                   m_attackInterval;
    
    bool                        m_onFlash;
    float                       m_flashTime;
    float                       m_flashSpan;
};

///////////////////////////


class AircraftLine : public BoardEntity
{
public:
	RT_CLASS_DEFINE(AircraftLine, BoardEntity, RtClass);
    
	AircraftLine();
	virtual ~AircraftLine();
    
    Rect GetAttackRect();
    
    void AircraftLineInitialize(int i_IndexAircraft,
                                bool i_isShort,
                                float damage);
    
    int CalcRenderOrder() const override;
    bool ShouldDrawShadow() const override { return false; }
    
protected:
    
	virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
    
    void         onLineSeparateAnimDone(const std::string& i_label);
    
    void         onAircraftSeparateDone(int i_IndexAircraft);
    void         onAircraftDisconnect(int i_IndexAircraft);
    
private:
    
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    bool                        m_isShort;
    bool                        m_inForward;
    float                       m_scale_y;
    int                         m_IndexAircraft;
    pvztime_t                   m_attackInterval;
    float                       m_damage;
};

namespace Message
{
	void AircraftSeparateDone(int i_IndexAircraft);
    void AircraftDisconnect(int i_IndexAircraft);
}

#endif /* defined(__PlantsVersusZombies2__BossAircraft__) */
