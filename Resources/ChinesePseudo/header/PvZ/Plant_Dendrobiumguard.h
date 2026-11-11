/*
 * Plant_Dendrobiumguard.h
 *
 *  Created on: 2020-12-14
 *      Author: zhousen
 */

#ifndef PLANT_DENDROBIUMGUARD_H_
#define PLANT_DENDROBIUMGUARD_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"

static const int NORMAL_LEAF_MAX = 2;
static const int JOINT_DEFENCE_MAX = 4;
static const int JOINT_DEFENCE_ONE = 1;
static const float ADD_LEAF_LIFE_RATIO = 0.25f;
static const int ADD_LEAF_COUNT_MAX = 2;

enum {
    DENDROBIUMGUARD_STATE_IDLE = STATE_FRAMEWORK_BEGIN,
    DENDROBIUMGUARD_STATE_REVIVE_LEAF,
    DENDROBIUMGUARD_STATE_BLOW_LEAF,
    DENDROBIUMGUARD_STATE_PLANTFOOD,
    DENDROBIUMGUARD_STATE_JOINTDEFENCE,
    DENDROBIUMGUARD_STATE_ATTACKZOMBIE,
};

///
/// PlantDendrobiumguardProps
///
class PlantDendrobiumguardProps : public PlantPropertySheet
{
public: 
    RT_CLASS_DEFINE(PlantDendrobiumguardProps, PlantPropertySheet, RtClass);

    PlantDendrobiumguardProps();

    pvztime_t ReviveLeafLevel2;// cd time level2
    pvztime_t ReviveLeafLevel3;// cd time level3 and above
    int AddLeafLifeTimes;// add leaf life times max
    pvztime_t Level5RecoveryTIme;// level 5 attack zombie CD
    float Level5AttackRatio;// level 5 attack zombie ratio
};

/// 
/// PlantDendrobiumguard 
///
class PlantDendrobiumguard : public PlantFramework
{
public: 
    RT_CLASS_DEFINE(PlantDendrobiumguard, PlantFramework, RtClass);

    PlantDendrobiumguard();
    ~PlantDendrobiumguard();

    void PostInitialize() override;
    void onDestroy() override;
    void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animCommand) override;
    int	GetMaxHitpoints() override;
    void onBeThrown() override;

    std::string GetThrowAnimName(int leafNum);
    int GetLeafCount() { return _leafCount; }// current leaf count
    void ReviveLeaf();// add leaf count
    bool CanAddLeafLife() { return _addLeafLifeTimes > 0; }
    void AddLeafLife(int leafNum);// only for joint defence
    void BlowPlant();// this should be a callback, lose a piece of leaf, play lose leaf anim
    pvztime_t GetReviveLeafTime();
    bool CheckAttackZombie();// if can attack zombie
    void AttackZombie();// level5 konck zombie back
    void KnockBackZombie();
    void SpecialPlantfood(bool isAvatar);// plantfood skill
    void JointDefencePlantfood(bool isAvatar);// joint defence plants plantfood skill
    void DoPlantfood(bool isAvatar);
    // void OnCreatePlant(Plant* plant);// make joint defence
    // void OnDestroyPlant(Plant* plant);// destroy joint defence
    void MakeJointDefence();
    void RemoveJointDefence();
    void AddJointDefencePlantList(int x, int y);
    void JointDefence(PlantDendrobiumguard* plant);
    void RemoveJointDefence(PlantDendrobiumguard* plant);
    void CreateJointDefenceEffect();
    void DestroyJointDefenceEffect();
    void PlayLineEffect();// when joint defence, main plant line effect play once
    void PlayReviveEffect();
    // void PlayShineEffect();// when joint defence, main plant and joint plants

protected:
    int _leafCount;// current leaf piece count
    int _leafCountMax;// leaf piece count max
    int _addLeafLifeTimes;// add leaf life times
    float _maxHealthRatio;// 1 leaf can add 25% life max
    pvztime_t _startReviveTime;// the start revive time
    pvztime_t _startLevel5AttackTime;// the start level5 attack time
    RtWeakPtr<GameObject> _jointDefenceEffect;// the joint defence mud effect
    std::vector<RtWeakPtr<BoardEntity> > _jointDefencePlantList;// joint definece plants
};

/// 
/// PlantAnimRig_Dendrobiumguard
///
class PlantAnimRig_Dendrobiumguard : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Dendrobiumguard, PlantAnimRig, RtClass);

	PlantAnimRig_Dendrobiumguard();

    void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getWaterAnimName() override;

    void SetLeafLayer(int leafNum);
    void SetJointDefenceStatus(bool isJointDefence);
    void SetPlantPtr(PlantPtr ptr) { _plantPtr = ptr; }
    
protected:
    PlantPtr _plantPtr;
};



#endif /* PLANT_DENDROBIUMGUARD_H_ */
