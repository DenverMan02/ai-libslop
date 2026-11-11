//  ZombieBungee
//  Created by lfy
//  2023.10.31

#ifndef __ZOMBIEBUNGEE_H__
#define __ZOMBIEBUNGEE_H__

#include "Zombie.h"
#include "Effect_PopAnim.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"


STATE_ENUM_CHILD_BEGIN(ZombieBungeeState, ZombieState)
	ZS_BUNGEE_Hint,
	ZS_BUNGEE_Falling,
	ZS_BUNGEE_Idle,
	ZS_BUNGEE_Grab,
	ZS_BUNGEE_Rise,
STATE_ENUM_END(ZombieBungeeState);

struct plantInfo
{
    plantInfo()
    {
        plant = BoardEntityPtr();
        cost = -1;
        isCob = false;
        isSun = false;
    }
    BoardEntityPtr plant;
    int cost;
    bool isCob;
    bool isSun;
};

class ZombieBungee : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBungee, Zombie, RtClass);
    
    bool CanBeMowed() const override { return false; }
    bool ShouldDrawShadow() const override { return false; }
    bool CanBeBlovered() const override { return false; }
protected:    
    void onZombieInitialize() override;
    void onPlaceOnBoard() override;
    void onDestroy() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    int CalcRenderOrder() const override;
    // SexyVector2 GetShadowScaling() const override;
    bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;
    // void onApplyCondition(ZombieConditions i_condition) override;
    std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BUNGEE_ASH"; }
	std::string getElectrocutePAMName() const  override { return "POPANIM_EFFECTS_ZOMBIE_BUNGEE_SHOCK"; }
    void onElectrocuted() override;
    void onTurnedToAsh() override;
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;   
    void onPlaceOnStreet() override;
    bool hasArmParticle() const override;

    // states
    DECLARE_STATE_FUNCTIONS(ZombieState, Hint);	
	DECLARE_STATE_FUNCTIONS(ZombieState, Falling);
	DECLARE_STATE_FUNCTIONS(ZombieState, BungeeIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, Grab);
	DECLARE_STATE_FUNCTIONS(ZombieState, Rise);	

private:	    
	
    BoardEntityPtr findGrabPlant();
    void playHintEffect(Point i_pos);	
    PlantPtr GetPlantToPick(PlantGroupPtr i_plantGroup);
    void killPickPlant();    
    void onStopCallback(const std::string& i_animName);	
    // bool isNotValidGrid(Point i_point);    
    void destroyEffect();

    RtWeakPtr<class Effect_PopAnim> m_hint;
    RtWeakPtr<class Effect_PopAnim> m_shadow;
    RtWeakPtr<class BoardEntity> m_cacheEntity;
    Point m_pos;
    int idleCnts;    
    pvztime_t m_durations;
    bool m_isOnStreet;
};


class ZombieAnimRig_Bungee : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Bungee, ZombieAnimRig_Basic, RtClass);

	bool PlayFalling(AnimStoppedReflectionDelegate i_onAnimStopped, const std::string& i_animName = "fall");
    bool PlayGrabing(AnimStoppedReflectionDelegate i_onAnimStopped, const std::string& i_animName = "grab");
    bool PlayIdle(AnimStoppedReflectionDelegate i_onAnimStopped, const std::string& i_animName = "idle");
    bool PlayRise(AnimStoppedReflectionDelegate i_onAnimStopped, const std::string& i_animName = "grab02");
    bool PlayStopAnimation(const std::string& i_animName, AnimStoppedReflectionDelegate i_onAnimStopped = {});
    // const std::string GetHeadParticleName() override { return "particles"; }
protected:
    const std::string getDieAnimationName() override { return "death"; }
    virtual const std::vector<std::string>& getHeadLayerNames();
};

bool plantsOrder(const plantInfo lhs, const plantInfo rhs);


class BungeeCounterSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(BungeeCounterSubSystem, GameSubSystem, RtClass);
    bool GetValidGrid(Point& i_point);
    void removeUseNum(int i_num);
    void addUseNum(int i_num);
    bool isValidNum(int i_num);
protected:
    void onInitialized() override;
private:
    bool isNotValidGrid(Point i_point);

    std::set<int> m_storePositions;
};


#endif  // __ZOMBIEBUNGEE_H__
