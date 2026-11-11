//
//  Plant_Pamegranate.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 14-11-5.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Pamegranate__
#define __PlantsVersusZombies2__Plant_Pamegranate__

#include "PlantFramework.h"
#include "Projectile.h"

//enum PamegranateBulletType
//{
//	BULLET_NORMAL,
//	BULLET_PLANTFOOD,
//	BULLET_AVATAR_PLANTFOOD
//};

class PamegranateProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PamegranateProjectile, Projectile, RtClass);

	void SetTargetLoc(const SexyVector2& i_targetLoc) { m_targetPosition = i_targetLoc; }
	const SexyVector2 & GetTargetLoc() const { return m_targetPosition; }

protected:
	virtual void onUpdate(pvztime_t i_dt) override;
    virtual void onDeflection(class BoardEntity* i_deflector) override;
private:
	SexyVector2 m_targetPosition;
};

class PlantPamegranate : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPamegranate, PlantFramework, RtClass);
    PlantPamegranate();
    virtual ~PlantPamegranate();
//    virtual void onKilled(bool i_instantKill);
    virtual void	Initialize() override;
    virtual void	UpdateActions() override;
    virtual bool	CanApplyPlantfood() override;
    virtual void	ApplyPlantfood() override;
    virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual void    onPlantfoodStarted() override;
    virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
private:
//    void PlayBulletEffect(int weaponType);
//    void PlayHitEffect(PlantWeapon bulletType, BoardEntityPtr target);
//    void FindTarget(PlantWeapon weapon, std::vector<BoardEntity*>& target);
//    void FindTargetInGridSquare(PlantWeapon weapon, const Rect& gridSquare, std::vector<BoardEntity*>& target);
//    void ClipAttackRect(Rect& rect);
//    void LockTarget(PlantWeapon weapon);
//    void UnLockTarget();
//    void DamageTarget(int targetBatch);
//    void DamageTargetAtGridSquare(int row, int column, BoardEntity* ignoreTarget, const DamageInfo& damage);
//    static bool TargetIsBetter(BoardEntity* target1, BoardEntity* target2);
//    DamageInfo GetSingleBulletDamage(PlantWeapon weapon);
//    SexyVector3 GetEntityCenter(BoardEntityPtr entity);
    void PlayFireSound(PlantWeapon weapon);
    bool FindTarget();
    bool FindTargetInGridSquare(PlantWeapon weapon, int row, int column);
    bool GridSquareIsInBoard(int row, int column);
    int GetFireCountEachTarget(PlantWeapon weapon);
    void BeginPushZombie();
    void EndPushZombie();
    void UpdatePushZombie();
    void BeginFire(PlantWeapon weapon);
    void PrivateFire(PlantWeapon weapon);
    void LaunchProjectile(PlantWeapon projectile, const SexyVector3& target);
    void GetAttackRectInGridSquare(PlantWeapon weapon, std::vector<SexyVector2>& result);
    pvztime_t GetTotalFireTime(PlantWeapon weapon);
    std::vector<SexyVector2> GetAttackTarget(PlantWeapon weapon);
    Projectile* FireProjectileAt(PlantWeapon i_type, SexyVector3 i_targetLoc);
private:
//    int m_damageCount;
//    int m_bulletCount;
//    PlantWeapon m_lockWeapon;
//    RtWeakPtr<Effect_PopAnim> m_bulletEffect;
//    std::vector<BoardEntityPtr> m_hitSequence;
    
    int m_fireCountEachTarget;
    int m_fireCountAlready;
    pvztime_t m_fireInterval;
    pvztime_t m_fireElapsed;
    PlantWeapon m_weapon;
    std::vector<ZombiePtr> m_pushZombie;
    std::vector<SexyVector2> m_fireTarget;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Pamegranate__) */
