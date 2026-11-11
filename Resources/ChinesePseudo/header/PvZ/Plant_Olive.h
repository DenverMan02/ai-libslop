#ifndef __PLANT_OLIVE_H__
#define __PLANT_OLIVE_H__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GameObject.h"
#include "GameSubSystem.h"
#include "GridItemAnimation.h"

enum GridItemOliveOilLabel{
    OLIVEOIL_LABEL_LEFT,
    OLIVEOIL_LABEL_MID,
    OLIVEOIL_LABEL_RIGHT
};

enum GridItemOliveOilState{
	PVZ_BEGIN_ENUM(OliveOilSTATE_),
	OliveOilSTATE_UNKNOWN,
	OliveOilSTATE_SPAWNING,
	OliveOilSTATE_IDLE,
    OliveOilSTATE_FIRE,
	OliveOilSTATE_DISAPPEAR_NORMAL,
    OliveOilSTATE_DISAPPEAR_FIRE,
	OliveOilSTATE_DEAD,
    PVZ_END_ENUM(OliveOilSTATE_)
};

class GridItemOliveOil : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemOliveOil, GridItemAnimation, RtClass);

    GridItemOliveOil();

    virtual int CalcRenderOrder() const override;

    void SetInfo(GridItemOliveOilLabel i_label, bool i_burn);
    bool TakeFire();
    GridItemOliveOilState GetState(){
        return m_state;
    }
protected:
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    void SetState(GridItemOliveOilState i_state);
	
private:
    void onAnimationDone(const std::string& i_labelName);

    GridItemOliveOilLabel m_label;
    GridItemOliveOilState m_state;
    pvztime_t m_idleEnd;
    pvztime_t m_fireEnd;
    bool m_directBurn;
};

typedef RtWeakPtr<GridItemOliveOil> GridItemOliveOilPtr;

class OliveOilUnit : public GameObject
{
public:
    RT_CLASS_DEFINE(OliveOilUnit, GameObject, RtClass);

    OliveOilUnit();
    virtual ~OliveOilUnit();

    void InitUint(Sexy::Point i_point);
    bool CanDestroy();
    bool IsThereOil(Sexy::Point i_point);

    void onRemoveOil(GridItemOliveOil* i_oil);
private:
    void OnDamageZombie(Zombie* i_zombie, const DamageInfo& i_damage);
    bool CanAddOliveOilAt(Sexy::Point i_point);

    RtWeakPtr<GridItemOliveOil> m_left;
    RtWeakPtr<GridItemOliveOil> m_mid;
    RtWeakPtr<GridItemOliveOil> m_right;
    pvztime_t m_endTime;
    bool m_isBurning;
};

class OliveOilSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(OliveOilSystem, GameSubSystem, RtClass);

    void CreateOliveUnit(Sexy::Point i_point);
    void RemoveUnit(RtWeakPtr<OliveOilUnit> i_unit);

    bool IsThereOil(Sexy::Point i_point);

protected:
    void Update() override;

private:
   std::vector<RtWeakPtr<OliveOilUnit>> m_vec;
};

enum OliveOilFireState{
	PVZ_BEGIN_ENUM(OliveOilFireSTATE_),
	OliveOilFireSTATE_UNKNOWN,
	OliveOilFireSTATE_SPAWNING,
	OliveOilFireSTATE_IDLE,
	OliveOilFireSTATE_DISAPPEAR,
	OliveOilFireSTATE_DEAD,
    PVZ_END_ENUM(OliveOilFireSTATE_)
};

class OliveOilFire : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(OliveOilFire, GridItemAnimation, RtClass);

    OliveOilFire();

    virtual int CalcRenderOrder() const override;

    void InitFire(const DamageInfo& i_damageInfo, float i_duration);
    void RefreshFire();

protected:
    virtual void onUpdate() override;
    virtual void onDestroy() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    void setState(OliveOilFireState i_state);
    void takeEffect();
    void onAnimationDone(const std::string& i_tabel);

    float m_duration;
    OliveOilFireState m_state;
    DamageInfo m_damageInfo;
    pvztime_t m_endTime;
    pvztime_t m_updateTime;
    RtWeakPtr<class Effect_PopAnim> m_effect;
};

class PlantOlive : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantOlive, PlantFramework, RtClass);

    PlantOlive();

	virtual void	Initialize() override;
    virtual void	UpdateActions() override;

	bool CanBeShoveled() override { return false; }
	bool CanBeTargeted() override { return false; }
	bool IsInvincible() const override { return true; }
private:
    void Explode();

    pvztime_t m_idleEnd;
    RtWeakPtr<OliveOilSystem> m_systemPtr;
};

class OliveProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(OliveProps, PlantPropertySheet, RtClass);

    OliveProps()
    {

    }

};

class GridItemOliveOilProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemOliveOilProps, GridItemAnimationProps, RtClass);

	GridItemOliveOilProps():
    DamagePerSecond(100),
    Duration(4)
    {

    }
    float DamagePerSecond;
    float Duration;
};

#endif