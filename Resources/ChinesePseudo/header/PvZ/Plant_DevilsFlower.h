/*
 * Plant_DevilsFlower.h
 *
 *  Created on: 2023-7-10
 *      Author: zhousen
 */

#ifndef PLANT_DEVILSFLOWER_H_
#define PLANT_DEVILSFLOWER_H_

#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "GridItemAnimController.h"
#include "GameSubSystem.h"
#include "TimeMgr.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GameSubSystem.h"
#include "CthulhuSubSystem.h"
#include "ZombieGargantuar.h"
#include "ZombieAnimRig_Gargantuar.h"
#include "Plant_PrimalRafflesia.h"

namespace Message
{
	void DevilsParasiteTurnBack(Plant* parent, bool isBig, bool isAbsorb);
}

enum DevilsParasiteType {
	DevilsParasite_Invalid = -1,
	DevilsParasite_Small,
	DevilsParasite_Super,
	DevilsParasite_Max,
};

struct DevilsParasiteParam
{
	float Damage;
	float Speed;
	pvztime_t ParalyticDuration;
};

typedef RtWeakPtr<DevilsParasiteParam> DevilsParasiteParamPtr;
////////////////////////////////////////
/// DevilsFlowerProps
////////////////////////////////////////
class DevilsFlowerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(DevilsFlowerProps, PlantPropertySheet, RtClass);

	DevilsFlowerProps() {
		SpawnSuperDevilParasiteRatio = 0.4f;
		SpawnParasiteLoopDuration = 3.0f;
		ParasiteAttackDuration = 1.5f;
		ParasiteAttackDurationLevel5 = 3.0f;
		ParasiteAbsorbDuration = 5.0f;
		ParasiteAbsorbDurationLevel5 = 3.5f;
		ParasiteAttackDamage = 200.0f;
		ParasiteAttackDamageLevel5 = 400.0f;
		ParasiteFlySpeed = 2.0f;// fly 2 blocks in 1 second
		ParasiteFlySpeedLevel5 = 2.0f;
	}

public:
	float SpawnSuperDevilParasiteRatio;
	std::vector<std::string> ZombieBlacklist;

	pvztime_t SpawnParasiteLoopDuration;
	pvztime_t ParasiteAttackDuration;
	pvztime_t ParasiteAttackDurationLevel5;
	pvztime_t ParasiteAbsorbDuration;
	pvztime_t ParasiteAbsorbDurationLevel5;
	float ParasiteAttackDamage;
	float ParasiteAttackDamageLevel5;
	float ParasiteFlySpeed;
	float ParasiteFlySpeedLevel5;
};


////////////////////////////////////////
/// PlantTypeDevilsFlower
////////////////////////////////////////
class PlantTypeDevilsFlower : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeDevilsFlower, PlantType, RtClass) {}

    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    int GetRefundSunCount() const override;
};


////////////////////////////////////////
/// PlantDevilsFlower
////////////////////////////////////////
class PlantDevilsFlower : public PlantFramework
{
public:
	enum DevilsFlowerState
	{
		STATE_DEVILSFLOWER_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_DEVILSFLOWER_SPAWN_START,
		STATE_DEVILSFLOWER_SPAWN_LOOP,
		STATE_DEVILSFLOWER_SPAWN_PARASITE,
		STATE_DEVILSFLOWER_PARASITE_STANDBY,
		STATE_DEVILSFLOWER_ABSORB_START,
		STATE_DEVILSFLOWER_ABSORB_LOOP,
		STATE_DEVILSFLOWER_ABSORB_END,
		STATE_DEVILSFLOWER_ABSORB_FAIL,
	};

	RT_CLASS_DEFINE(PlantDevilsFlower, PlantFramework, RtClass);

	void Initialize() override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	void onKilled(bool i_instantKill) override;
	void ApplyPlantfood() override;
	bool CanApplyPlantfood() override;
	void CancelPlantfood() override;
	void UpdateActions() override;
	float GetRefundSunAmount() override;
	BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override;
	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	std::vector<Zombie*> FindAttackTargets(Rect searchRect);
	bool IsLv5() { return m_isLv5; }
	bool IsInParasiteStandby();

	const std::string GetIdleName();

protected:
	void SetState(int i_plantState);
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

	void OnPlantMoving(Plant* i_plant, Point& i_targetGridLocation);
	void PlayDarkEffect(const SexyVector2& start);
	void DarkEffectFlyEnd(float value);
	bool IsAbsorbTarget(const ZombiePtr& i_potentialZombie);
	bool IsZombieBlacklisted(const ZombiePtr i_zombie, const std::vector<std::string>& i_blacklist);
	pvztime_t CalcAbsorbDuration(bool isBig);
	void DevilsParasiteTurnBack(Plant* parent, bool isBig, bool isAbsorb);

	void GenerateParasite(bool isBig, BoardEntityPtr target);
	DevilsParasiteType CalcParasiteType(bool isBig);
	DevilsParasiteParam CalcParasiteParam(bool isBig);

	void SpawnDevilsGargantuar();
	bool CalcSuperParasiteEnable();

	const std::string GetSpawnStartName();
	const std::string GetSpawnLoopName();
	const std::string GetSpawnParasiteName();
	const std::string GetParasiteStandbyName();
	const std::string GetAbsorbStartName();
	const std::string GetAbsorbLoopName();
	const std::string GetAbsorbEndName();
	const std::string GetAbsorbFailName();

protected:
	RtWeakPtr<class AddCthulhuEnergyEffect> m_darkEffect;
	pvztime_t m_spawnStartEndTime;
	pvztime_t m_absorbEndTime;
	bool m_isLv5;
	int avatartype;
};



////////////////////////////////////////
/// PlantAnimRig_DevilsFlower
////////////////////////////////////////
class PlantAnimRig_DevilsFlower : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_DevilsFlower, PlantAnimRig, RtClass);

	void SetPlantPtr(PlantPtr ptr) { m_plantPtr = ptr; }
	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

protected:
	void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
	std::string getPlantFoodMainAnimName() override;

protected:
    PlantPtr m_plantPtr;
};


/// DevilParasite
STATE_ENUM_BASE_BEGIN(DPEState)
DPEState_INIT,
DPEState_FLYTOTARGET,
DPEState_ATTACK,
DPEState_FLYAWAY,
DPEState_TURNBACK,
DPEState_END,
STATE_ENUM_END(DPEState);




class DevilsParasiteEntity : public BoardEntity
{
public:
	RT_CLASS_DEFINE(DevilsParasiteEntity, BoardEntity, RtClass);

	DevilsParasiteEntity();
	virtual ~DevilsParasiteEntity();

    void DevilsParasiteInitialize(DevilsParasiteType type,
    		DevilsParasiteParam param, PlantPtr parent);

    int  CalcRenderOrder()  const override;
    bool ShouldDrawShadow() const override { return false; }

    void MoveToTarget(SexyVector2 i_endPosition);
    void SetTarget(BoardEntityPtr i_target);

protected:
    virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	void onPostLoad() override;

	void UpdateEntityPos();

    DECLARE_STATE_FUNCTIONS(DPEState, INIT);
    DECLARE_STATE_FUNCTIONS(DPEState, FLYTOTARGET);
    DECLARE_STATE_FUNCTIONS(DPEState, ATTACK);
    DECLARE_STATE_FUNCTIONS(DPEState, FLYAWAY);
    DECLARE_STATE_FUNCTIONS(DPEState, TURNBACK);
    DECLARE_STATE_FUNCTIONS(DPEState, END);

    void setState(DPEState i_newState);
    bool isInState(DPEState i_state) const;

    int32 getStateSerialization();
    void  setStateSerialization(int32 i_state);

    void onFlyToTargetDone(BoardEntity * target);
    void onFlyAwayDone(BoardEntity * target);
    void onTurnBackDone(BoardEntity * target);

    void onAttackAnimDone(const std::string& i_label);

    void onAnimCommand(const std::string& i_animLabel,
                       pvztime_t i_timeStamp,
                       const std::string& i_animCommand,
                       const std::string& i_animCommandParam);

    BoardEntity* FindTarget();
	SexyVector2 CalcMoveTarget(DevilsParasiteType type, Rect rect);
    bool IsBig();

    void GenerateMummyZombie(ZombiePtr zombie);
    void PlantDied(Plant* parent);
    bool CalcTargetFace(SexyVector3& pos);
    bool IsGotToFace(SexyVector3 p1, SexyVector3 p2);

    const std::string GetIdleName(bool isBack);
    const std::string GetAttackName();

private:
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    StateMachine<DPEState> 		m_DPEState;

    SexyVector2                 m_posLast;
    SexyVector3                 m_posTakeOff;
    float                       m_angle;
    bool                        m_mirrorX;

    DevilsParasiteType          m_type;
    BoardEntityPtr				m_target;
    SexyVector3					m_orginalTargetPosition;

    bool 						m_flyToParent;

    DevilsParasiteParam 		m_param;
    PlantPtr					m_parent;
    bool 						m_hasAbsorb;
    SexyVector3					m_speedVector;
    int							m_renderOrder;
};

/// SuperDevilParasite


/// GridItemDevilEgg
class GridItemDevilsEgg : public GridItemAnimController
{
public:
	RT_CLASS_DEFINE(GridItemDevilsEgg, GridItemAnimController, RtClass);

	GridItemDevilsEgg();
	virtual ~GridItemDevilsEgg();

	void onGridItemInitialize() override;
	void onUpdate() override;
	int CalcRenderOrder() const override;
    void KillGridItem() override;

    void SetLevel(int level) { m_level = level; }
    void SetAvatar(bool avatar) { m_isAvatar = avatar; }

    void SpawnZombie();

protected:
    int m_level;
    bool m_isAvatar;
};


/// DevilsAlienZombie
class ZombieDevilsAlienGargantuarProps : public ZombieGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieDevilsAlienGargantuarProps, ZombieGargantuarProps, RtClass);

	ZombieDevilsAlienGargantuarProps()
	{
		SpawnSlimeRatio = 0.0f;
		SpawnSlimeRect = { 1, -1, 3, 3 };
	}

	float SpawnSlimeRatio;
	Rect SpawnSlimeRect;
	ProjectilePropertySheetPtr Projectile;
};

class ZombieDevilsAlienGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieDevilsAlienGargantuar, ZombieGargantuar, RtClass);

    void onTakeFatalDamage(const DamageInfo &i_lastDamageReceived) override;
    void onLostHead() override;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

    void playDeathAnimation() override;
    void onInitialized() override;
	BoardEntity *findTarget() override;
    bool isImpReadyToBeThrown() override;

	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	ZombiePtr FindFireSlimeTarget(Rect search);


private:
    void SpawnSlime();

protected:
    bool m_isOutBoard;
};

class ZombieAnimRig_DevilsAlienGargantuar : public ZombieAnimRig_Gargantuar
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_DevilsAlienGargantuar, ZombieAnimRig_Gargantuar, RtClass);

    ZombieAnimRig_DevilsAlienGargantuar()
    {

    }

//    virtual const std::vector<std::string>& getHeadLayerNames() override;
};

/// AcidProjectile
class DevilsAlienSlimeProjectile : public PrimalRafflesiaProjectile
{
public:
    RT_CLASS_DEFINE(DevilsAlienSlimeProjectile, PrimalRafflesiaProjectile, RtClass);
    DevilsAlienSlimeProjectile(){}

protected:
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
};


#endif /* PLANT_DEVILSFLOWER_H_ */
