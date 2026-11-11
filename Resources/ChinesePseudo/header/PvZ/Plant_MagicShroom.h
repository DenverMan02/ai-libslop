//
//  Plant_MagicShroom.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-6-9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_MagicShroom__
#define __PlantsVersusZombies2__Plant_MagicShroom__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "StateMachine.h"

namespace Message
{
	void MagicCardReturn(Plant * parent,int index);
}

STATE_ENUM_BASE_BEGIN(MSState)
MSState_IDLE,
MSState_ATTACK,
STATE_ENUM_END(MSState);

STATE_ENUM_BASE_BEGIN(MSCState)
MSCState_INIT,
MSCState_FLYTOTARGET,
MSCState_ATTACK,
MSCState_FLYAWAY,
MSCState_END,
STATE_ENUM_END(MSCState);

enum EMagicCardType
{
	EMagicCardType1 = 0,
	EMagicCardType2,
	EMagicCardType_Count
};

class MagicCard : public BoardEntity
{
public:
	RT_CLASS_DEFINE(MagicCard, BoardEntity, RtClass);

	MagicCard();
	virtual ~MagicCard();

    void    MagicCardInitialize(EMagicCardType i_magicCardType,
                                     PlantPtr i_parent,
                                     int i_index);

    int  CalcRenderOrder()  const override;
    bool ShouldDrawShadow() const override { return false; }

    void MoveToTarget(SexyVector2 i_endPosition);
    void DealDamage();
    void SetTargetPos(const SexyVector3& i_pos) { m_targetPos = i_pos; }

protected:

    virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

    DECLARE_STATE_FUNCTIONS(MSCState, INIT);
    DECLARE_STATE_FUNCTIONS(MSCState, FLYTOTARGET);
    DECLARE_STATE_FUNCTIONS(MSCState, ATTACK);
    DECLARE_STATE_FUNCTIONS(MSCState, FLYAWAY);
    DECLARE_STATE_FUNCTIONS(MSCState, END);

    void setState(MSCState i_newState);
    bool isInState(MSCState i_state) const;

    int32 getMagicCardStateSerialization();
    void  setMagicCardStateSerialization(int32 i_state);

    void onFlyToTargetDone(BoardEntity * target);
    void onFlyAwayDone(BoardEntity * target);

    //void onAttackAnimDone(const std::string& i_label);
   void onAttackAnimDone(class StandaloneEffect* i_effect);

    void onAnimCommand(const std::string& i_animLabel,
                       pvztime_t i_timeStamp,
                       const std::string& i_animCommand,
                       const std::string& i_animCommandParam);

private:
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    StateMachine<MSCState> 		m_MSCState;

    SexyVector2                 m_posLast;
    float                       m_angle;
    bool                        m_mirrorX;

    SexyVector3                 m_posTakeOff;
    EMagicCardType              m_magicCardType;
    PlantPtr                    m_parent;
    int                         m_nIndex;
    int                         m_currentLevel;
    SexyVector3					m_targetPos;
    float						m_damage;
};

class MagicShroomProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(MagicShroomProps, PlantPropertySheet, RtClass);
    MagicShroomProps();
    std::vector<float> AdvancedAttackProbability;
    float SuperStarRate;
    float ImpactDamage;
};

class PlantMagicShroom : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantMagicShroom, PlantFramework, RtClass);
    bool	 CanApplyPlantfood() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    bool	 FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    void	 UpdateActions() override;
    void	 onAnimStoppedCallback(const std::string& i_animCommand) override;
    PlantMagicShroom();
    virtual ~PlantMagicShroom();
    void Initialize() override;
protected:
    DECLARE_STATE_FUNCTIONS(MSState, IDLE);
	DECLARE_STATE_FUNCTIONS(MSState, ATTACK);

	void setState(MSState i_newState);
	bool isInState(MSState i_state) const;

	int32 getPlantMagicshroomStateSerialization();
	void  setPlantMagicshroomStateSerialization(int32 i_state);

	void registerForEvents() override;
	void unregisterForEvents() override;
private:
    int GetAdvancedFireCount();
    int CalcHatColumn(int row);
    bool FindTargetLeft();
    bool TrigerAdvancedAttack();
    void InternalFire(int projectileIndex);
    void DropHat(int row, int column);
    ZombieTypePtr GetZombieType();
    ZombiePtr FindLeftMostZombie(int i_row);
    void onTakeOffAnimDone(const std::string& i_label);
    void onAttackOffAnimDone(const std::string& i_label);
    void TakeOff();
    void onMagicCardReturn(Plant * parent,int index);
private:
    int m_fireCount;
    int m_fireTotalCount;
    StateMachine<MSState>                       m_MSState;
    pvztime_t                                   m_timeAttack;
    int                                         m_IndexCard;
    std::vector<RtWeakPtr<class MagicCard>> m_cards;
};

class PlantAnimRig_MagicShroom : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_MagicShroom, PlantAnimRig, RtClass);
    bool PlayTakeOff(const std::string& i_animLabel,AnimStoppedDelegate i_onAnimStopped);
    bool PlayAttackOff(const std::string& i_animLabel,AnimStoppedDelegate i_onAnimStopped);
    bool PlayAttackLoop();
};

class MagicHat : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(MagicHat, Effect_PopAnim, RtClass);
    void SetSpawnZombie(const ZombieTypePtr& type, const Point& location, int level);
    MagicHat();
protected:
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
private:
    int m_zombieLevel;
    Point m_zombieLocation;
    ZombieTypePtr m_zombieType;
};

#endif /* defined(__PlantsVersusZombies2__Plant_MagicShroom__) */
