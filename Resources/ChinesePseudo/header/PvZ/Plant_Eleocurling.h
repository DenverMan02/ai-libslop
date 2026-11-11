#ifndef PlantsVersusZombies2_Plant_Eleocurling_h
#define PlantsVersusZombies2_Plant_Eleocurling_h

#include "DamageInfo.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemBreakableTarget.h"


class EleocurlingProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(EleocurlingProps, PlantPropertySheet, RtClass);

    EleocurlingProps()
    :SmallCurlingLaneGenerateRate(0.4f),
    SmallCurlingLaneGenerateRateLv2(0.7f),
    NormalLaneExistenceTime(2.0f),
    AvatarPlantfoodLaneExistenceTime(5.0f),
    PlantRecoverTime(5.0f),
    PlantRecoverTimeLv3(3.0f),
    Level5SkillRate(0.7f)
    {

    }

    float SmallCurlingLaneGenerateRate;
    float SmallCurlingLaneGenerateRateLv2;
    float NormalLaneExistenceTime;
    float AvatarPlantfoodLaneExistenceTime;
    float PlantRecoverTime;
    float PlantRecoverTimeLv3;
    float Level5SkillRate;
    
};

STATE_ENUM_CHILD_BEGIN(EleocurlingState, PlantState)
    ELEOCURLING_IDLE1,
    ELEOCURLING_ATTACK1,
    ELEOCURLING_IDLE2,
    ELEOCURLING_ATTACK2,
    ELEOCURLING_RECOVER_LOOP,
    ELEOCURLING_RECOVER_END,
STATE_ENUM_END(EleocurlingState);

class CurlingItem;
class PlantEleocurling : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEleocurling, PlantFramework, RtClass);
	
	virtual void Initialize() override;
    virtual void UpdateActions() override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;

    virtual void Idle() override;
    virtual bool CanBeWatered() override;
    virtual void onWatered(bool watered) override;
    
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual class Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;


    void SetState(const uint i_state);
    uint GetState();

    void SetTargetItem(RtWeakPtr<CurlingItem> i_target);
    RtWeakPtr<CurlingItem> GetTargetItem();

    virtual void onAnimStoppedCallback(const std::string& i_animCommand);

private:
    pvztime_t m_resetTimer;
    RtWeakPtr<CurlingItem> m_targetItem;
};

class PlantAnimRig_Eleocurling : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Eleocurling, PlantAnimRig, RtClass);

	PlantAnimRig_Eleocurling();
    void setPlant(RtWeakPtr<Plant> i_plant) {m_waternut = i_plant;};

	void setIdleTag(const std::string& i_tag);
    virtual std::string getIdleAnimationName() override;

    bool PlayRecoverLooped();
    
private:
	std::string m_idleTag;
	RtWeakPtr<Plant> m_waternut;
};


class CurlingProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CurlingProjectile, Projectile, RtClass);

    CurlingProjectile();

    virtual void onUpdate(pvztime_t i_dt) override;
    void SetIsGenerateIceLane(bool i_flag);
    void SetIceLaneExistenceTime(float i_time);
    void SetIsSpeedUp(bool i_flag);
    void SetAvatarIndex(int i_avatarIndex);
    int GetAvatarIndex();

protected:
    virtual void onProjectileInitialized() override;
    void CreateCurlingAt(const std::string& i_typename, const Sexy::Point& i_point, bool i_isLevel5 = false);
    void BeakBackZombie(BoardEntity* i_entity);
    void DamageGridZombies(BoardEntity* i_entity, bool i_beakBack);
    bool ProcessCurlingCollision(BoardEntity* i_entity);

protected:
    int m_avatarIndex;
    bool m_isBegin;
    bool m_isSpeedUp;
    bool m_isGenerateIceLane;
    float m_existenceTime;
    Sexy::Point m_currentGrid;
};

class CurlingCollidableProjectile : public CurlingProjectile
{
public:
	RT_CLASS_DEFINE(CurlingCollidableProjectile, CurlingProjectile, RtClass);
};

class EleocurlingSmallProjectile : public CurlingProjectile
{
public:
	RT_CLASS_DEFINE(EleocurlingSmallProjectile, CurlingProjectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class EleocurlingBigProjectile : public CurlingCollidableProjectile
{
public:
	RT_CLASS_DEFINE(EleocurlingBigProjectile, CurlingCollidableProjectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class EleocurlingSmallLv5Projectile : public CurlingCollidableProjectile
{
public:
	RT_CLASS_DEFINE(EleocurlingSmallLv5Projectile, CurlingCollidableProjectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class EleocurlingBigLv5Projectile : public CurlingCollidableProjectile
{
public:
	RT_CLASS_DEFINE(EleocurlingBigLv5Projectile, CurlingCollidableProjectile, RtClass);

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

class EleocurlingPlantfoodProjectile : public CurlingProjectile
{
public:
	RT_CLASS_DEFINE(EleocurlingPlantfoodProjectile, CurlingProjectile, RtClass);

    EleocurlingPlantfoodProjectile();

    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void SetLevel(int i_plantLevel) {m_plantLevel = i_plantLevel;}
private:
    std::vector<BoardEntityPtr> m_hitted;
    int m_plantLevel;
};

class EleocurlingPenetrateProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(EleocurlingPenetrateProjectile, Projectile, RtClass);

    EleocurlingPenetrateProjectile();

    virtual void onUpdate(pvztime_t i_dt) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void SetIsGenerateIceLane(bool i_flag);
    void SetAvatarIndex(int i_avatarIndex);
    int GetAvatarIndex();

private:
    bool m_generateIceLane;
    int m_avatarIndex;
    Sexy::Point m_currentGrid;
    std::vector<BoardEntityPtr> m_hitted;
};

class CurlingItem : public GridItemBreakableTarget
{
public:
    RT_CLASS_DEFINE(CurlingItem, GridItemBreakableTarget, RtClass);

    CurlingItem();

    void SetRenderAndCollisionOffset(const SexyVector2& i_vec);
    virtual int CalcRenderOrder() const override;
    virtual bool OverrideProjectileCollision(class Projectile* i_projectile) override;
    virtual bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }
    void SetDamageRate(float i_damageRate);
    float GetDamageRate();
    void SetAvatarIndex(int i_avatarIndex);
    int GetAvatarIndex();
    void SetGenerateIceLane(bool i_flag);
    bool GetGenerateIceLane();

protected:
    virtual void onGridItemInitialize() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    virtual SexyVector2	getRenderOffset() override;
    virtual Rect calcCollisionRect() override;

private:
    bool m_generateIceLane;
    int m_avatarIndex;
    float m_damageRate;
    SexyVector2 m_overallOffset;
};

class CurlingIceLane : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(CurlingIceLane, GridItemAnimation, RtClass);

    CurlingIceLane();

    virtual int CalcRenderOrder() const override;
    void StartEffect(float i_existenceTimer);
    void SetIsBegin(bool i_flag);
    void ResetTimer(bool i_isBegin, pvztime_t i_resetTimer);
    
protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onAnimationDone(const std::string& i_labelName);

private:
    bool m_isBegin;
    float m_existenceTime;
    pvztime_t m_endTime;
};

#endif
