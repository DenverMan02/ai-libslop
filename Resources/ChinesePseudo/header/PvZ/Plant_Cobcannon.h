//
//  Plant_Cobcannon.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 2016/11/28.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_Cobcannon_h
#define Plant_Cobcannon_h

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "StandardLevelIntro.h"
#include "Effect_BouncingArrow.h"
#include "BananaTargetCursor.h"
#include "GameSubSystem.h"
#include "PopingWidget.h"

namespace Message
{
    void CobcannonSelected();
    void CobcannonLaunched();
    void CobcannonTappedOnCooldown();
}

enum CobcannonState
{
    CB_STATE_SELECTED = STATE_FRAMEWORK_BEGIN,
    CB_STATE_FIRING,
    CB_STATE_RECOVERING,
    CB_STATE_RECOVERING_END,
};

struct BulletTargetCounter
{
    BoardEntity* target;
    int choosedTimes;
};

class CBTutorialUI : public PopingWidget, public ButtonListener
{
public:
    CBTutorialUI();
    ~CBTutorialUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    
private:
    
private:
    bool m_inited = false;
    bool m_tutorial = false;
    
    int m_index = 0;
    
    Rect m_hintRect;
    Rect m_buttonRect;
    Rect m_closeRect;
    
    class PVZ2UIButton* m_switchBtn = nullptr;
    class PVZ2UIButton* m_closeBtn = nullptr;
};

class PlantTypeCobcannon : public PlantType
{
public:
    RT_CLASS_DEFINE(PlantTypeCobcannon, PlantType, RtClass) {}
    
    void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool CanPlantOnPlant(Plant* i_plant) const override { return true; };
};

class PlantCobcannon;

class CannonTargetCursor : public BaseCursor
{
public:
    RT_CLASS_DEFINE(CannonTargetCursor, BaseCursor, Sexy::RtClass) {}
    
    CannonTargetCursor() {}
    explicit CannonTargetCursor(const Sexy::Touch& i_boardSpaceTouch, PlantCobcannon* i_cannonPlant);
    virtual ~CannonTargetCursor();
    
    const PlantCobcannon* GetCobcannonPlant() const { return m_cannonPlant; }
    
protected:
    Sexy::SexyVector2 getCursorAnimOffset() const override;
    bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
    
private:
    void OnPlantDied(Plant* i_plant);
    
private:
    Sexy::SexyVector2 m_cursorOffset;
    PlantCobcannon* m_cannonPlant;
};

class CobcannonProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(CobcannonProps, PlantPropertySheet, RtClass);
    
    int NumPlantFoodBullet = 30;
    int ZombieMaxBulletTimes = 5;
    int MiniGunLevel = 5;
    pvztime_t FireTime = 1.0f;
    pvztime_t BulletInterval = 0.12f;
    SexyVector2 TargetOffset = { 0, 0 };
    std::vector<pvztime_t> RecoverTime;
};

class PlantCobcannon : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantCobcannon, PlantFramework, RtClass);
    
    PlantCobcannon();
    
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
    void Initialize() override;
    void UpdateActions() override;
    
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    
    void SetCanOnlyTargetZombies(bool i_x) { m_onlyTargetZombies = i_x; }
    void SetFireIgnoreBoardState(bool i_x) { m_fireIgnoreBoardState = i_x; }
    
    void FireCannon(const Sexy::Point& i_targetLocation);
    void NotifySetHidden(bool i_newValue, bool i_oldValue) override;
    Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    bool CanBeTarget(BoardEntity* i_entity);
    void Idle() override;
    void Draw(Graphics* g) override;
    
private:
    
    void registerForEvents() override;
    void unregisterForEvents() override;
    
    bool onTouchEvent(const Sexy::Touch& i_touch);
    void onCursorDestroyed(BaseCursor* i_cursor);
    
    void onAnimStoppedCallback(const std::string& i_animName) override;
    
    void setState(const int i_newState);
    bool select();
    void deselect();
    bool canFire() const;
    
    void LaunchTarget(const Point& i_targetLocation);
//    void AddBullet(BoardEntity* i_target, int& io_shot);
    void LaunchPlantFoodTarget(const Point& i_targetLocation, std::vector<BoardEntity*>& i_targets);
//    void LaunchPlantFoodTarget(BoardEntity* i_target, pvztime_t i_launchTime, const Point& i_targetLocation);
    
    bool CanShootMiniGun();
    
private:
    bool m_hasMiniGun;
    bool m_onlyTargetZombies;
    bool m_fireIgnoreBoardState;
    // not serialized
    BoardEntityPtr m_target = nullptr;
    class CannonTargetCursor* m_targetCursor;
};

class CBMiniRocketProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(CBMiniRocketProps, ProjectilePropertySheet, RtClass);
    
    float MaxRotationsPerSecond = 1.0;
};

class CBMiniRocket : public Projectile
{
public:
    RT_CLASS_DEFINE(CBMiniRocket, Projectile, RtClass);
    
    CBMiniRocket();
    
    void SetOverrideTarget(BoardEntity* i_overrideTarget);
    void SetRotatedVelocity(float i_magnitude);
    void SetNumbInfo(float i_rate, float i_duration);
    void FindNewTarget();
    void SetTargetLocked(bool i_locked);
    void SetIsBigRocket(bool i_big);
    void SetKeepDown(pvztime_t i_downTime);
    virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
    
protected:
    void onDeflection(class BoardEntity* i_deflector) override;
    void moveThroughTime(pvztime_t i_dt) override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    BoardEntity* FindTargetWithFlag(BoardEntityTypeFlag i_flag);
    float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    bool CanBeTarget(BoardEntity* i_entity);
    SexyVector3 GetTargetPos(BoardEntity* i_target);
    void onFlyToTargetDone(BoardEntity * target);
    
private:
    bool TestOutWithoutTarget();
    
    
private:
    RtWeakPtr<BoardEntity> m_overrideTarget;
    pvztime_t m_keepDown = 0.f;
    bool m_isBigRocket = false;
    bool m_deflected = false;
    bool m_targetLocked = false;
};

class PlantAnimRig_Cobcannon : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Cobcannon, PlantAnimRig, RtClass);
    
    void SetMiniGunShown(bool i_shown);
    
    bool PlaySelected();
    bool PlayRecoverStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayRecoverLoop();
    bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
    bool PlaySpecialAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool PlayPlantFoodStart(int i_mainAnimPlayCount, PlantFoodMainAnimStartedDelegate i_onPlantFoodStarted, PlantFoodMainAnimEndedDelegate i_onPlantFoodLooped, PlantFoodMainAnimEndedDelegate i_onPlantFoodEnded) override;
    void ReadyForPlantFood(const std::string& i_animLabel);
    bool PlayWatering() override;
    
protected:
//    void onPopAnimInitialized() override;
    std::string getAttackAnimationName() override;
    
private:
    void SetReloading(bool i_reload);
    
private:
    bool m_mini = false;
    bool m_reloading = false;
};

struct BulletTarget
{
    BulletTarget() {}
    BulletTarget(Point& i_point, pvztime_t i_launchTime);
    
    Sexy::Point Target;
    pvztime_t LaunchTime;
};

class CBBigRocket : public Projectile
{
public:
    RT_CLASS_DEFINE(CBBigRocket, Projectile, RtClass);
    CBBigRocket();
    ~CBBigRocket();
    
    void SetAvatared(bool i_avatared);
    void SetPlantfood(bool i_plantfood);
    void SetExplodeHeight(float i_height);
    void SetOwner(PlantPtr i_owner);
    void AddTargets(std::vector<BulletTarget> i_targets);
    void PlayEnd();
    
protected:
    void onDeflection(class BoardEntity* i_deflector) override;
    void moveThroughTime(pvztime_t i_dt) override;
    
private:
    void DoOneShot();
    void DoShot(std::vector<BulletTarget>& i_targets, int index);
    void DropCore(const std::string &i_animLabelName);
    
private:
    bool m_avatared = false;
    bool m_plantfood = false;
    bool m_exploded = false;
    bool m_end = false;
    bool m_endPlayed = false;
    bool m_coreDroping = false;
    bool m_coreDroped = false;
    bool m_coreEnded = false;
    float m_explodeHeight = 0.f;
    pvztime_t m_coreDropingStartTime = 0.f;
    pvztime_t m_coreEndedTime = 0.f;
    
    PlantPtr m_owner = nullptr;
    RtWeakPtr<Effect_PopAnim> m_core = nullptr;
    RtWeakPtr<Projectile> m_coreRocket = nullptr;
    RtWeakPtr<const CobcannonProps> m_ownerProps = nullptr;
    std::vector<BulletTarget> m_targets;
};

class CBBullet : public Projectile
{
public:
    RT_CLASS_DEFINE(CBBullet, Projectile, RtClass);
    CBBullet();
    
    virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
    void SetTargetPos(Sexy::Point);
    
protected:
    void moveThroughTime(pvztime_t i_dt) override;
    void onDeflection(class BoardEntity* i_deflector) override;
    
private:
    bool m_deflected = false;
};

struct CannonEntry
{
    CannonEntry() {}
    CannonEntry(pvztime_t i_launchTime, const Point& i_target);
    
    void ResetBulletTargets();
    void SetGroundTarget(bool i_groundTarget);
    void SetAvatar(bool i_avatared);
    void SetOwner(PlantCobcannon* i_owner);
    void AddBulletTarget(BoardEntity* i_target);
    
    Point Target;
    pvztime_t LaunchTime = 0.f;
    PlantPtr Owner = nullptr;
    bool Avatared = false;
    bool GroundTarget = false;
    int BulletTargetCount = 0;
    std::vector<BulletTarget> Bullettargets;
    RtWeakPtr<const CobcannonProps> OwnerProps = nullptr;
};

class CannonEntrySubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(CannonEntrySubSystem, GameSubSystem, RtClass);
    
    CannonEntrySubSystem();
    CannonEntry* CreateShot(pvztime_t i_launchTime, const Point& i_target);
//    CobcannonPlantFoodLauncherEntry* GetLauncherEntry(int i);
    void Update() override;
    
private:
    void Launch(const CannonEntry* i_entry);
    
private:
    
    std::vector<CannonEntry> m_shots;
};

#endif /* Plant_Cobcannon_h */
