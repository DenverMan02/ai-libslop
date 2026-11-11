
#ifndef ZombieDinoStealEgg_hpp
#define ZombieDinoStealEgg_hpp

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAnimRig_Basic.h"

class BoardEntity;
class Plant;

STATE_ENUM_CHILD_BEGIN(ZombieDinoStealEggState, ZombieState)
ZDBS_ThrowEgg,
ZDBS_FallGetUp,
STATE_ENUM_END(ZombieDinoStealEggState);

class ZombieDinoStealEggProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieDinoStealEggProps, ZombiePropertySheet, RtClass);
    
    ZombieDinoStealEggProps()
    {
        ThrowEggGridX = 5;
    }
    std::vector<EntityWeight> EggTypesToSpawn;
    int ThrowEggGridX;
};

class ZombieDinoStealEgg : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieDinoStealEgg, Zombie, RtClass);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, ThrowEgg);
    DECLARE_STATE_FUNCTIONS(ZombieState, FallGetUp);
    
    BoardEntity *findTarget() override;
protected:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
protected:
    std::string PickDinoEgg();
    std::string GetEggLayerName(const std::string &eggName);
    void PlaceEgg();
    void ThrowEgg();
    bool willDieToShrinking() override { return true; }
private:
    void onZombieInitialize() override;
    void onDestroy() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onThrowEggAnimDone(const std::string& i_animLabelName);
    void onFallGetUpAnimDone(const std::string& i_animLabelName);
    
    std::string m_carriedEgg;
    int m_TargetGridX;
};

#pragma mark - ZombieAnimRig_DinoBasic

class ZombieAnimRig_DinoStealEgg : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_DinoStealEgg, ZombieAnimRig_Basic, RtClass);
    ZombieAnimRig_DinoStealEgg();
    
    AnimHandle PlayDie() override;
    void SetHasEgg(bool i_hasEgg);
    
    void PlayThrowEgg(AnimStoppedReflectionDelegate i_onAnimStopped = {});
    void PlayFallGetUp(AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool hasEgg() { return m_hasEgg; }
    void SetCarriedEgg(const std::string &eggName);
    const std::string GetCarriedEgg() { return ""; }
protected:
    void onPopAnimInitialized() override;
    void HideAllEggs();
    const std::string getIdleAnimationName() override;
    const std::string getWalkAnimationName() override;
    const std::string getDieAnimationName() override;
private:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
    bool m_hasEgg;
};

#endif /* ZombieDinoStealEgg_h */
