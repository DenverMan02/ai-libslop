#ifndef ArtifactSkateBoard_H_
#define ArtifactSkateBoard_H_

#include "Artifact.h"
#include "Projectile.h"
#include "GridItemBreakableTarget.h"


class SkateProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SkateProjectile, Projectile, RtClass);

	SkateProjectile()
	: m_extraDamageValue(0.0f)
	{

	}

	virtual void onProjectileInitialized() override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    float m_extraDamageValue;
};

class SkateGridItem : public GridItemBreakableTarget
{
public:
    RT_CLASS_DEFINE(SkateGridItem, GridItemBreakableTarget, RtClass);

    virtual int CalcRenderOrder() const override;
    virtual bool ShouldClipWithWater() const override;
    virtual void onUpdate() override;

protected:
    virtual void onGridItemInitialize() override;
};

class SkateBoardMower : public BoardEntity
{
public:
	RT_CLASS_DEFINE(SkateBoardMower, BoardEntity, RtClass);

    virtual void onInitialized() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onDraw(Graphics* i_g) override;
	virtual void onDrawShadow(Graphics* i_g) override;
    virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

    void InitSkatePlant(const std::string& i_plantName, int i_artifactLevel);

protected: 

    void OnAnimStoppedCallback(const std::string& i_animLabel);
    void OnUseActionAnimCommand(pvztime_t i_timeStamp);
    void OnUseSpecialAnimCommand(pvztime_t i_timeStamp);

    class SkatePlant* m_skatePlant;

private:
    void initPopAnim();
    bool onTouchEvent(const Sexy::Touch& i_touch);

	RtWeakPtr<class PopAnimRig>	m_popAnimRig;

    Sexy::TouchID m_touchID;
    Sexy::Point m_startPoint;
    pvztime_t m_mowerCooldwon;
    int m_artifactLevel;
};


class SkatePlant
{
public:
    SkatePlant(SkateBoardMower* i_skateMower);
    virtual ~SkatePlant();

    virtual void Initialize(const std::string& i_typeName);
    virtual void UpdateAction();
    virtual void onDraw(Graphics* i_g);

    virtual void OnAnimStoppedCallback(const std::string& i_animLabel) {}
    virtual void OnUseActionAnimCommand(pvztime_t i_timeStamp) {}
    virtual void OnUseSpecialAnimCommand(pvztime_t i_timeStamp) {}

    virtual float GetDamageAmount();

public:
    class SkateBoardMower* m_skateMower;
    PlantTypePtr m_plantType;
    PlantPropsPtr m_plantProps;
    class PlantAnimRig* m_plantAnimRig;
    SexyVector2 m_plantAnimRigOffset;
    int m_level;
    float m_extraDamageValue;
};


class SkatePlant_StarFruit : public SkatePlant
{
public:
    SkatePlant_StarFruit(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;

    virtual void OnAnimStoppedCallback(const std::string& i_animLabel) override;
    virtual void OnUseActionAnimCommand(pvztime_t i_timeStamp) override;
    virtual float GetDamageAmount() override;

public:
    void Fire();

    pvztime_t m_timer;
    pvztime_t k_attackInterval;
    int m_bulletStep;
    int k_bulletRestrict;
};


class SkatePlant_PinkStarFruit : public SkatePlant
{
public:
    SkatePlant_PinkStarFruit(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;
    virtual float GetDamageAmount() override;

public:
    void Fire();

    pvztime_t m_timer;
    pvztime_t k_attackInterval;
    int m_bulletStep;
    int k_bulletRestrict;
    float m_rotation;
};


class SkatePlant_HomingThistle : public SkatePlant
{
public:
    SkatePlant_HomingThistle(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;
    virtual float GetDamageAmount() override;

public:
    void Fire();

    pvztime_t m_timer;
    pvztime_t k_attackInterval;
    int m_bulletStep;
    int k_bulletRestrict;
    int m_pfShotIndex;
};


class SkatePlant_Nekotail : public SkatePlant
{
public:
    SkatePlant_Nekotail(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;
    virtual void onDraw(Graphics* i_g) override;
    virtual float GetDamageAmount() override;

public:
    //base
    RtWeakPtr<GameObject> LoadLaserEffect(std::string i_name, int i_laserType);
    SexyVector2 GetLaserShooterPos();
    SexyVector2 CollsionCenter(BoardEntity* i_target);
    float CalcAngleForVector(const SexyVector2& i_vector);

    RtWeakPtr<class Effect_PopAnim> GetLaserRig() { return m_laserRig; }
    RtWeakPtr<class Effect_PopAnim> GetLaserImapctRig() { return m_laserImpactRig; }
    RtWeakPtr<class Effect_PopAnim> GetLaserSplashRig() { return m_laserSplashRig; }

    //action
    void LaserHitBlasting(BoardEntity* i_entity);
    void ApplyLaserDamage(BoardEntity* i_entity);

    //find target
    BoardEntity* FindLaserTarget();
    BoardEntity* FindLaserTargetByType(BoardEntityTypeFlag i_type, float& targetDistSqr);
    bool CanBeTarget(BoardEntity* i_entity);


public:
    SexyVector2 m_laserPos;
    SexyVector2 m_laserTargetPos;
    BoardEntityPtr m_laserTarget = nullptr;

    RtWeakPtr<class Effect_PopAnim> m_laserRig;
    RtWeakPtr<class Effect_PopAnim> m_laserImpactRig;
    RtWeakPtr<class Effect_PopAnim> m_laserSplashRig;
};


class SkatePlant_ElectricBlueberry : public SkatePlant
{
public:
    SkatePlant_ElectricBlueberry(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;
    virtual float GetDamageAmount() override;

public:
    void Fire();

    pvztime_t m_timer;
    pvztime_t k_attackInterval;
    int m_bulletStep;
    int k_bulletRestrict;
};


class SkatePlant_Citron : public SkatePlant
{
public:
    SkatePlant_Citron(SkateBoardMower* i_skateMower);

    virtual void Initialize(const std::string& i_typeName) override;
    virtual void UpdateAction() override;
    virtual float GetDamageAmount() override;

public:
    void Fire();

    pvztime_t m_timer;
    pvztime_t k_attackInterval;
    int m_bulletStep;
    int k_bulletRestrict;
};

#endif
