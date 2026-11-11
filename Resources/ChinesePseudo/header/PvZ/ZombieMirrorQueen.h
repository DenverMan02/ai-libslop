/*
 * 	ZombieMirrorQueen.h
 *
 * 	Created on: 2022-6-7
 * 		Author: kkdud
 */

#ifndef PLANTSVERSUSZOMBIES_PVZ2_ZOMBIEMIRRORQUEEN_H_
#define PLANTSVERSUSZOMBIES_PVZ2_ZOMBIEMIRRORQUEEN_H_

#include "DamageInfo.h"
#include "GameSubSystem.h"
#include "GridItemBreakableTarget.h"
#include "GravestoneAnimRig.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieAnimRig_BeachBasic.h"
#include "ZombieGeneralActions.h"
#include "ZombieWithActions.h"

class ZombieMirrorQueenProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenProps, ZombieWithActionsProps, RtClass);

	pvztime_t	LifetimeSeconds = 0;
	int			Phase = 0;
	float 		ActionIntervals = 5.0f;
	std::vector<std::string> CannotSeckillPlantTypeName;
	std::vector<std::string> CannotSeckillZombieTypeName;
};

class ZombieMirrorQueen : public ZombieWithActions
{
public:
    RT_CLASS_DEFINE(ZombieMirrorQueen, ZombieWithActions, RtClass);

	void SetLifetime(pvztime_t i_lifetime);

private:
	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }

	OVERRIDE_STATE_UPDATE(ZombieState, ZombiePickNextAction);

	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
	void onApplyCondition(ZombieConditions i_condition) override;

	bool CanBeHypnotized() const override { return false; }
	bool CanBeMowed() const override { return false; }
	bool CanBeBlovered() const override { return false; }
	bool CanBeFlickedOff() const override { return false; }
	bool CanBeTossedByPlants(ZombieTossedPower i_tossStrength) const override { return false; }
	bool CanDropArm() const override;
	void SetIdleState() override {}
	void SetWalkingState() override {}
	void SetGrabbedState() override {}
	bool isImmuneToShrinking() override { return true; }
	bool hasHeadParticle() const override { return false; }
    bool IsValidRangedTarget(Plant* plant) override;

	bool shouldSeckillPlant(Plant* plant);
	bool shouldSeckillZombie(Zombie* zombie);
	void trySeckillTargets();

	pvztime_t	m_timeToRetreat;
	pvztime_t 	m_nextActionTime;
};

class ZombieAnimRig_MirrorQueen : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_MirrorQueen, ZombieAnimRig, RtClass) {}

	const std::string getSkillIdleAnimationName() { return "idle"; }
	const std::string getSkillMirrorAnimationName() { return "skill3"; }
	const std::string getSkillAppleAnimationName() { return "skill2"; }
	const std::string getSkillSummonAnimationName() { return "skill1"; }
};

class GridItemZombieMirrorQueenPoisonApplePuree : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombieMirrorQueenPoisonApplePuree, GridItemAnimation, RtClass);

	GridItemZombieMirrorQueenPoisonApplePuree();
	virtual ~GridItemZombieMirrorQueenPoisonApplePuree();

	bool IsDamageable() const override { return false; }
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

	void onGridItemInitialize() override;
	void onUpdate() override;
	void KillGridItem() override;
	int CalcRenderOrder() const override;

	void releasePoison();
	void stopReleasingPoison();
	void setValues(PlantPtr i_plantPtr, float i_duration, float i_poisonDps);
	void setValuesZombie(ZombiePtr i_zombiePtr, float i_duration, float i_poisonDps);
	void setValuesGridItem(GridItemPtr i_gridItemPtr, float i_duration, float i_poisonDps);

protected:
	void OnCleanPoison(int x, int y, bool i_fromPlant);// water mist created, post message to callback
	void poisonTarget();
	void cleanTargetPoison();

protected:
	pvztime_t m_timeToDie = PVZ_EOT();
	float m_poisonDps;
	PlantPtr m_plantPtr;
	ZombiePtr m_zombiePtr;
	GridItemPtr m_gridItemPtr;
};


class ZombieMirrorQueenPoisonAppleProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenPoisonAppleProjectileProps, ProjectilePropertySheet, RtClass);

	float DamageAmountPerSecond = 200.0f;
	float Duration = 10.0f;
};

class ZombieMirrorQueenPoisonAppleProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ZombieMirrorQueenPoisonAppleProjectile, Projectile, RtClass);

protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool OnCollideGround() override;
    virtual void createApplePuree(BoardEntityPtr i_entityPtr);

    BoardEntityPtr m_entPtr;
};

class CardGameZombieMirrorQueenPoisonAppleProjectile : public ZombieMirrorQueenPoisonAppleProjectile
{
public:
    RT_CLASS_DEFINE(CardGameZombieMirrorQueenPoisonAppleProjectile, ZombieMirrorQueenPoisonAppleProjectile, RtClass);

protected:
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool OnCollideGround() override;
    void createApplePuree(BoardEntityPtr i_entityPtr);
};

enum GridItemZombieMirrorQueenMirrorUnitState
{
	UNIT_STATE_TELEPORT_INVALID,
	UNIT_STATE_TELEPORT_OUT,
	UNIT_STATE_TELEPORT_DISAPPEARED,
	UNIT_STATE_TELEPORT_IN,
	UNIT_STATE_TELEPORT_DONE
};

class GridItemZombieMirrorQueenMirrorUnit
{
public:
	enum WarpType
	{
		WARPIN_AND_WARPOUT,
		WARPIN_ONLY
	};

	GridItemZombieMirrorQueenMirrorUnit()
	: m_state(UNIT_STATE_TELEPORT_INVALID)
	, m_warpType(WARPIN_AND_WARPOUT)
	{}

	RtWeakPtr<Zombie> m_zombiePtr;
	SexyVector3 m_startPos;
	SexyVector3 m_endPos;
	pvztime_t m_disappearTime;
	pvztime_t m_warpInTime;
	pvztime_t m_doneTime;
	WarpType m_warpType;
	GridItemZombieMirrorQueenMirrorUnitState m_state;
	std::function<void(RtWeakPtr<Zombie>)> m_completeCallback;
};

class GridItemZombieMirrorQueenMirrorSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(GridItemZombieMirrorQueenMirrorSubSystem, GameSubSystem, RtClass);

	void Update() override;

	void addZombie(RtWeakPtr<Zombie> i_zombiePtr, SexyVector3 i_startPos, SexyVector3 i_endPos, std::function<void(RtWeakPtr<Zombie>)> i_callback = nullptr);
	void addZombieWarpInOnly(RtWeakPtr<Zombie> i_zombiePtr, SexyVector3 i_endPos, std::function<void(RtWeakPtr<Zombie>)> i_callback = nullptr);

	GridItemZombieMirrorQueenMirrorUnit* findTeleportingGameObject(Zombie* i_zombie);

private:
	void warpOutZombie(GridItemZombieMirrorQueenMirrorUnit& i_unit);
	void disappearZombie(GridItemZombieMirrorQueenMirrorUnit& i_unit);
	void warpInZombie(GridItemZombieMirrorQueenMirrorUnit& i_unit);
	void recoverZombie(GridItemZombieMirrorQueenMirrorUnit& i_unit);

	std::vector<GridItemZombieMirrorQueenMirrorUnit> m_teleportingZombies;
	std::vector<GridItemZombieMirrorQueenMirrorUnit> m_newTeleportingZombies;
	std::vector<Zombie*> m_deleteZombies;
};

class GridItemZombieMirrorQueenMirrorProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemZombieMirrorQueenMirrorProps, GridItemAnimationProps, RtClass);

    std::vector<std::string> CannotCopyZombieTypeName;
    float ZombieOutDelay = PVZ_EOT();
    int DamageStateCount = 0;
};

class GridItemZombieMirrorQueenMirror : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemZombieMirrorQueenMirror, GridItemAnimation, RtClass);

    class CopyZombieParams
    {
    public:
    	std::string m_zombieTypeName;
    	int m_zombieLevel = 1;
    	pvztime_t m_walkOutTime = PVZ_EOT();
    	ZombiePtr m_clonedZombiePtr = nullptr;
    };

    void onGridItemInitialize() override;
    void TakeDamage(const DamageInfo& i_damage) override;
    void onTakeDamage(const DamageInfo& i_damage) override;

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;

    void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

    void onUpdate() override;
    void onDraw(Graphics* i_g) override;
    void registerForEvents() override;
    void refreshStats();
    virtual bool canCoypZombie(Zombie* i_zombie);

protected:
    int calcDamageState();
    bool IsDamageable() const override { return !m_hasBroken; }
    Sexy::Rect calcCollisionRect() override;
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return !m_hasBroken; }
    int CalcRenderOrder() const override;
    void onDestroy() override;
    void copyZombie(Zombie* i_zombie);
    void walkOutZombie(CopyZombieParams& i_params);
    void playSpawnAnim();
    void playIdleAnim();
    void playCopyAnim();
    void playZombieOutAnim();
    void playBrokenAnim();

    void onAnimationDone(const std::string& i_animLabel);
    std::string getSpawnAnimLabel() { return "showup"; }
    std::string getIdleAnimLabel() { return "undamaged"; }
    std::string getCopyAnimLabel() { return "zombiepass"; }
    std::string getWalkOutAnimLabel() { return "zombiepass"; }
    std::string getBrokenAnimLabel() { return "die"; }

protected:
    std::vector<CopyZombieParams> m_copyZombies;
    std::vector<ZombiePtr> m_copiedZombies;
    int m_currDamageState = 0;
    bool m_hasBroken = false;
};

// CardGameGridItemZombieMirrorQueenMirror
class CardGameGridItemZombieMirrorQueenMirror : public GridItemZombieMirrorQueenMirror
{
public:
    RT_CLASS_DEFINE(CardGameGridItemZombieMirrorQueenMirror, GridItemZombieMirrorQueenMirror, RtClass);
    bool canCoypZombie(Zombie* i_zombie) override;
};

class GridItemZombieMirrorQueenMirrorAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemZombieMirrorQueenMirrorAnimRig, GravestoneAnimRig, RtClass) {}

	void SetDamageState(int i_damageState, bool i_isAnimated) override;
};

class ZombieMirrorQueenMirrorMagicActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenMirrorMagicActionDefinition, ZombieActionDefinition, RtClass);

	ZombieMirrorQueenMirrorMagicActionDefinition() {}

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	bool pickAPointToPlaceAMirror(Point& i_point) const;
};

class ZombieMirrorQueenMirrorMagicActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenMirrorMagicActionHandler, ZombieActionHandler, RtClass);

	ZombieMirrorQueenMirrorMagicActionHandler()	{}

	void setGridPosition(Point i_gridPosition);

protected:
	void onStartAction() override;
	void onUpdateAction() override;
	void onEndAction() override;

private:
	void createBeamEffect();
	void onAnimationDone(const std::string& i_animLabel);
	void showMirrorAppearLight();

	Point m_gridPosition = Point(-1, -1);
};




class ZombieMirrorQueenIdleActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenIdleActionDefinition, ZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

	float Duration = 5.0f;
};

class ZombieMirrorQueenIdleActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenIdleActionHandler, ZombieActionHandler, RtClass);

protected:
	void onStartAction() override;
	void onUpdateAction() override;

private:
	pvztime_t m_endTime = PVZ_EOT();

};


class ZombieMirrorQueenSummonActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenSummonActionDefinition, ZombieActionDefinition, RtClass);

	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;

	std::string	ZombieTypeName = "dark_cavalry";
	int ZombieNum = 1;
};

class ZombieMirrorQueenSummonActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombieMirrorQueenSummonActionHandler, ZombieActionHandler, RtClass);

protected:
	void onStartAction() override;

private:
	void onAnimationDone(const std::string& i_animLabel);
	void summonZombies();

	pvztime_t m_endTime = PVZ_EOT();
};

#endif /* PLANTSVERSUSZOMBIES_PVZ2_ZOMBIEMIRRORQUEEN_H_ */
