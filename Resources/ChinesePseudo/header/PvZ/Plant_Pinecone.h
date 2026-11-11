//
//  Plant_Pinecone.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/8/22.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_Pinecone_h
#define Plant_Pinecone_h

#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "BoardEntity.h"

enum NekoStabType
{
    NS_None = 0,
    NS_Normal,
    NS_Elec,
    NS_Huge
};

enum NTLaserState
{
    NTLS_INACTIVE,
    NTLS_WARMINGUP,
    NTLS_ACTIVE,
    NTLS_DISABLING
};

enum LaserType
{
    LT_Laser,
    LT_Impact,
    LT_Explode,
};

enum LaserShooter
{
    LSNone = 0,
    LSLevel1,
    LSLevel2,
    LSLevel3,
    LSLevelAvatar
};

enum BoardEntityPriority {
    BoardEntity_GridItem,
    BoardEntity_Normal,
    BoardEntity_MidSize,
    BoardEntity_BigSize,
    BoardEntity_Boss
};


class PineconeProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PineconeProps, PlantPropertySheet, RtClass);
    
    int ElecStabMinLevel = 2;
    int ElecStabRate = 15;
    int ElecStabRatePro = 10;
    float LaserDPS = 90.f;
    float AvatarLaserDPS = 105.f;
    float LaserLevelUpDPSPro = 15.f;
    float HugeStabRate = 0.001;
    float LaserAngleDegrees = 85.f;
    float LaserMaxDist = 900.f;
    float LaserRate = 2000.f;
    float NumbRate = 0.15f;
    float NumbRateProPerLevel = 0.05;
    float NumbDuration = 2.f;
    float AvatarLaserSplashDPS = 50.f;
    float AvatarLaserSplashRadius = 2.0736;
    float Level2Rate = 0.5f;
    float Level5Rate = 0.5f;
    SexyVector2 LaserEffectPos = { 105.f, 105.f };
    SexyVector2 LaserStarOffset = { 0.f, 98.f };
    SexyVector2 LaserEndOffset = { 200.f, 98.f };
};

class PineconeStab;

class PlantPinecone : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPinecone, PlantFramework, RtClass);
    
    PlantPinecone();
    ~PlantPinecone();
    
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    void Initialize() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanApplyPlantfood() override;
    void UpdateUnconditionally() override;
    void DoSpecial(int i_extraParam = 0) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void UpdateActions() override;
    virtual void AddToRenderQueue(class RenderQueue* i_queue) override;
    

    void SetNextSpecial(bool isNextSpecial);
    bool GetNextSpecial() const { return m_bIsNextSpecial; };
    
    void PlayAttackAnimation() override;

    bool IsInSkillState() { return m_bIsSkillAttack; }

private:
    BoardEntity* FindLaserTargetByType(BoardEntityTypeFlag i_type, float& targetDistSqr);
    BoardEntity* FindLaserTarget();
    
    bool LaserNeedLevelUp();
    bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    bool IsLaserInLevel(LaserShooter i_level);
    void LaserLevelUp();
    void UpdateLaserShooterLayer();
    void setLaserState(NTLaserState i_newState);
    void ApplyLaserDamage(BoardEntity* i_entity);
    void ApplyAvatarLaserSplashDamage(BoardEntity* i_entity);
    void LaserHitBlasting(BoardEntity* i_entity, const SexyVector2& i_laserPivotScreenSpace);
    void RenderLaser(Graphics *i_g);
    SexyVector2 GetLaserShooterPos();
    bool CanBeTarget(BoardEntity* i_entity);
    
    RtWeakPtr<class Effect_PopAnim> GetLaserRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserImapctRig();
    RtWeakPtr<class Effect_PopAnim> GetLaserSplashRig();
    RtWeakPtr<GameObject> LoadLaserEffect(std::string i_name, LaserType i_laserType);
    
private:
    NTLaserState m_laserState = NTLS_INACTIVE;
    
    NekoStabType m_stabType = NS_None;
    
    LaserShooter m_laserShooter = LSNone;
    
    pvztime_t m_laserStartTime = 0.f;
    
    BoardEntityPtr m_stabTarget = nullptr;
    BoardEntityPtr m_laserTarget = nullptr;
    
    SexyVector2 m_laserPos;
    SexyVector2 m_laserTargetPos;
    
    RtWeakPtr<class Effect_PopAnim> m_laserRig;
    RtWeakPtr<class Effect_PopAnim> m_laserImpactRig;
    RtWeakPtr<class Effect_PopAnim> m_laserSplashRig;
private:
    bool m_bIsNextSpecial;
    bool m_bIsSkillAttack;
    int m_nCurSkillIdx;
    int m_nFoodPlantNum;
    bool m_bIsSuperSkill;
};

class PlantAnimRig_Pinecone : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Pinecone, PlantAnimRig, RtClass);
    
    PlantAnimRig_Pinecone();
    void SetElec(bool i_elec);
    
private:
    std::string getAttackAnimationName() override;
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getIdleAnimationName() override;

private:
    bool m_elec = false;
};


class PineconeProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PineconeProjectile, Projectile, RtClass);
	virtual void onProjectileInitialized() override;
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void SetOwnerPlant(PlantPinecone* ownerPlant);
private:
	void onDestroy() override;
    PlantPinecone* m_pOwnerPlant;
};


class PineconeSpecialProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PineconeSpecialProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetExplosionParameters(float i_explodeAtLocation, float i_minimumSpeedScale, float i_numZombiesForMinScale);
    bool isShouldFlickOff(BoardEntity* i_entity);

    void SetIsSuperSkill(bool isSuperSkill);

    bool isBoardEntityCanToss(BoardEntity* i_entity);
    void SetOwnerPlant(PlantPinecone* ownerPlant);
protected:
	virtual void onInitialized() override;
private:
	void doExplosion(const std::string& i_animLabel);
	void handleExplosionDone(const std::string& i_animLabel);

	bool m_fuseLit;
	float m_explosionTargetX;
	float m_minScale;
	int m_numZombiesForMinScale;
    bool m_bIsSuperSkill;
    PlantPinecone* m_pOwnerPlant;
};


class PineconePlantfoodProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(PineconePlantfoodProjectileProps, ProjectilePropertySheet, RtClass);
    
    float MaxRotationsPerSecond = 1.0;
};

class PineconePlantfoodProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PineconePlantfoodProjectile, Projectile, RtClass);
    
    PineconePlantfoodProjectile();
    
    void SetOverrideTarget(BoardEntity* i_overrideTarget);
    void SetRotatedVelocity(float i_magnitude);
    void SetNumbInfo(float i_rate, float i_duration);
    BoardEntity* FindNewTarget();
    void SetTargetLocked(bool i_locked);
    void SetIsBigRocket(bool i_big);
    void SetKeepDown(pvztime_t i_downTime);
    virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities, const Rect& i_projectileRect) const override;
    int getBoardEntityPriority(BoardEntity* i_overrideTarget);
    bool compareSamePriority(BoardEntity* i_Target, BoardEntity* i_bestTarget);
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


#endif /* Plant_Pinecone_h */
