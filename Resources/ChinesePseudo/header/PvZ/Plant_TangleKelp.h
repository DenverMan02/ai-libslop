//
//  Plant_TangleKelp.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 6/18/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_TangleKelp__
#define __PlantsVersusZombies2__Plant_TangleKelp__

#include "PlantFramework.h"
#include "Effect_PopAnim.h"
#include "GameSubSystem.h"

class Transform2
{
public:
    SexyVector3 position;
    float rotation;
    Transform2() { rotation = 0; }
    Transform2(const SexyVector3& position, float rotation);
};


class TransfromKeyFrameSystem : public RtObject
{
public:
    	RT_CLASS_DEFINE(TransfromKeyFrameSystem, RtObject, RtClass);
private:
    class Item
    {
    public:
        void Update(pvztime_t dt);
        bool IsEnd();
        const ZombiePtr& GetEntity() { return m_entity; }
        Item(const ZombiePtr& entity,
             const std::vector<Transform2>& keyFrame,
             const std::vector<uint32> frameCount);
        Item();
    public:
        std::vector<Transform2> m_keyFrame;
        std::vector<pvztime_t> m_frameTime;
        int m_sectionIndex;
        pvztime_t m_elapseTime;
        ZombiePtr m_entity;
    };
public:
    void Update(pvztime_t dt);
    void Add(const ZombiePtr& entity,
             const std::vector<Transform2>& keyFrame,
             const std::vector<uint32> frameCount);
    void Remove(const ZombiePtr& entity);
    void RemoveAll();
    bool EntityExist(const ZombiePtr& entity);
private:
    std::vector<Item> m_item;
};

class ZombieRepulseSystem : public RtObject
{
public:
    RT_CLASS_DEFINE(ZombieRepulseSystem, RtObject, RtClass);
private:
    class Item
    {
    public:
        void Update(pvztime_t dt);
        bool IsEnd();
        const ZombiePtr& GetEntity() { return m_zombie; }
        Item(const ZombiePtr& zombie, MATH_TYPE speed, pvztime_t time);
        Item();
    public:
        float m_speed;
        pvztime_t m_totalTime;
        pvztime_t m_elapseTime;
        ZombiePtr m_zombie;
    };
public:
    void Update(pvztime_t dt);
    void Add(const ZombiePtr& zombie, MATH_TYPE speed, pvztime_t time);
    bool ZombieExist(const ZombiePtr& zombie);
    void Remove(const ZombiePtr& zombie);
private:
    std::vector<Item> m_item;
};

enum TangledKelpState
{
	TANGLEKELP_IDLE = STATE_FRAMEWORK_BEGIN,
	TANGLEKELP_SUBMERGED,
	TANGLEKELP_EMERGING
};

namespace Message
{
    void TangleKelpSwallowedZombie(Zombie* i_zombie);
}

class PlantTangleKelp : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantTangleKelp, PlantFramework, RtClass);

	void Initialize() override;

	void UpdateActions() override;
	bool CanApplyPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;

	void SetPopAnimDelegates(class PlantAnimRig *i_rig) override;
	bool HasShadow() override { return false; }
	bool CanBeTargeted() override;

	void ApplyPlantfood() override;
	void CancelPlantfood() override;

protected:

private:
	void setState(uint i_plantState);

	bool zombieIsBlacklisted(const Zombie* i_zombie) const;

    void finishSwallowingZombie(pvztime_t i_atTime);
    void spawnPlantFoodTentacles(pvztime_t i_atTime);
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
    bool IsInDeepWater(const ZombiePtr& zombie);
	RtWeakPtr<class Zombie> m_targettedZombie;
};

class PlantAnimRig_TangleKelp : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_TangleKelp, PlantAnimRig, RtClass);

	bool PlayZenGardenIdleAnim() override;
};

class PlantTypeTangleKelp : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeTangleKelp, PlantType, RtClass) {}
	
	// Tanglekelp is only plantable on the tide
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
};

// -----------
// Tentacles!
// -----------

class PlantTangleKelpTentacle  :  Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(PlantTangleKelpTentacle, Effect_PopAnim, RtClass);

	void SwallowZombie(RtWeakPtr<class Zombie> i_zombie, int attackLevel, float repulseDamage);
	void SlapZombie(RtWeakPtr<class Zombie> i_zombie, float i_slapDamage);
	void SpawnAtPosition(const Sexy::SexyVector3& i_position);
protected:
    virtual void onUpdate() override;
    virtual void onPostLoad() override;
private:
	RtWeakPtr<class Zombie> m_zombieToEat;
	RtWeakPtr<class Zombie> m_zombieToSlap;
	float m_slapDamage = 0;
    int m_attackLevel = 1;
    TransfromKeyFrameSystem m_keyFrameSystem;
    ZombieRepulseSystem m_repulseSystem;

	void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
    std::string GetAttackName(int level);
    void BeginUpdateZombieTransform(const ZombiePtr& zombie, int attackLevel);
    void DamageAndRepulseEntityInRect(const Rect& rect, BoardEntity* ignore);
    bool CanbeDamaged(const Zombie* target);
    Rect CalcZombieRepulseRect(const ZombiePtr& zombie);
};

#endif /* defined(__PlantsVersusZombies2__Plant_TangleKelp__) */
