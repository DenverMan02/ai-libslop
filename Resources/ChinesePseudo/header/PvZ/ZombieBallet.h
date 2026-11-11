
#ifndef __ZOMBIEBALLET_H__
#define __ZOMBIEBALLET_H__

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "GameSubSystem.h"

namespace Message
{
	void NotifySlip();
}

STATE_ENUM_CHILD_BEGIN(ZombieState_Ballet, ZombieState)
	ZS_Ballet_Slip,	// slip down
	ZS_Ballet_Stand,// stand up
STATE_ENUM_END(ZombieState_Ballet)

class ZombieBallet : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBallet, Zombie, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Slip);
	DECLARE_STATE_FUNCTIONS(ZombieState, Stand);

	void StartWalk();
	void StopWalk();

	void setEndPosition(const Sexy::SexyVector3& i_vec3){
		m_endPosition = i_vec3;
	}
	Sexy::SexyVector3 getEndPosition(){
		return m_endPosition;
	}
    
	bool m_isDieWay2;
	bool m_skipLaneChange;
protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
    virtual void onUpdate() override;
	virtual SexyVector3 GetStunnedEffectOffset() const override;

private:
	void spawnInitialSegments();
	void collectionInit(RtWeakPtr<ZombieBallet> i_head);
	void onAnimStop(const std::string& i_animCommand);

	pvztime_t m_slipEndTime;
	Sexy::SexyVector3 m_endPosition;
	class ZombieBalletSubSystem* m_system;
};

typedef RtWeakPtr<ZombieBallet> ZombieBalletPtr;

class ZombieAnimRig_Ballet : public ZombieAnimRig
{
RT_CLASS_DEFINE_ABSTRACT(ZombieAnimRig_Ballet, ZombieAnimRig, RtClass);
public:
	void SetZombie(RtWeakPtr<ZombieBallet> i_zombie);
protected:
	virtual const std::string getDieAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
private:


	RtWeakPtr<ZombieBallet> m_zombie;
};

class ZombieBalletProps : public ZombiePropertySheet 
{
RT_CLASS_DEFINE_ABSTRACT(ZombieBalletProps, ZombiePropertySheet, RtClass);

	ZombieBalletProps():
	BalletSegmentOffset(50)
	{

	}

	float BalletSegmentOffset;
};

enum ZombieBalletSegmentType
{
	BALLET_INVALID,
	BALLET_HEAD,
	BALLET_BODY,
	BALLET_TAIL,
};

class ZombieBalletCollection
{
public:
	ZombieBalletCollection();
	ZombieBalletCollection(ZombieTypePtr i_type);

	bool ContainsZombie(RtWeakPtr<ZombieBallet> i_testZombie);
	int GetSize();
	ZombieBalletPtr GetHeadZombie();
	ZombieBalletPtr GetPreviousZombie(ZombieBalletPtr i_testZombie);
	ZombieBalletPtr GetNextZombie(ZombieBalletPtr i_testZombie);
	ZombieBalletPtr GetTailZombie(ZombieBalletPtr i_testZombie);
	int GetIndexForZombie(ZombieBalletPtr i_testZombie);
	void AddZombie(ZombieBalletPtr i_addZombie);
	bool RemoveZombie(ZombieBalletPtr i_removeZombie);

	bool RemoveNotTeamZombie();
	
	bool isChanging;
	pvztime_t m_endTime;
	pvztime_t m_nextChangeTime;
//private:
	ZombieTypePtr m_balletType;
	std::vector<ZombieBalletPtr> m_segments;
};

class ZombieBalletSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ZombieBalletSubSystem, GameSubSystem, RtClass);

	virtual void Update() override;
	virtual void OnZombieRemoved(Zombie* i_zombie);
	void OnBalletSegmentCreated(RtWeakPtr<ZombieBallet> i_headZombie, RtWeakPtr<ZombieBallet> i_segmentZombie);

	void onZombieEat(ZombieBalletPtr i_zombie);
	void onZombieEatEnd(ZombieBalletPtr i_zombie);

	bool IsAllBottomRow(ZombieBalletCollection& i_coll);
	bool IsAllTopRow(ZombieBalletCollection& i_coll);

protected:
	virtual void registerForEvents() override;
private:
	void updateLaneChange();

	ZombieBalletCollection* GetBalletForZombie(RtWeakPtr<ZombieBallet> i_testZombie);
	
	std::vector<ZombieBalletCollection> m_Ballets;
};

#endif
