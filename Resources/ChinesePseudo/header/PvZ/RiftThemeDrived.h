#ifndef __RiftThemeDrived__
#define __RiftThemeDrived__

#include"GridItemAnimation.h"


class RiftThemePlantSeedAnimationProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(RiftThemePlantSeedAnimationProps, GridItemAnimationProps, RtClass);

    std::vector<std::string> PlantBlackList;
};

class RiftThemePlantSeedAnimation : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(RiftThemePlantSeedAnimation, GridItemAnimation, RtClass);

    RiftThemePlantSeedAnimation();
    virtual int CalcRenderOrder() const override;
    virtual void onGridItemInitialize() override;
	virtual void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    void onAnimationDone(const std::string& i_tabel);
    void SpawnPlant();

private:
    float m_endTime;
};



class GridItemZombieChangerProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemZombieChangerProps, GridItemAnimationProps, RtClass);

    GridItemZombieChangerProps()
    :SuccessRate(0.5),
    ChangerTime(10)
    {

    }

    float SuccessRate;
    float ChangerTime;
    std::vector<std::string> SuccessList;
    std::vector<std::string> FailureList;
};

enum ZombieChangerState : int
{
    ChangerState_Invild,
    ChangerState_Idle,
    ChangerState_ChangeStart,
    ChangerState_Changing,
    ChangerState_ChangEnd1,
    ChangerState_ChangEnd2,
};

class GridItemZombieChanger : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemZombieChanger, GridItemAnimation, RtClass);

    GridItemZombieChanger();
    ~GridItemZombieChanger();

	virtual bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    virtual bool IsDamageableByPlants() const override;

	virtual int	CalcRenderOrder() const override;
    virtual void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	virtual void KillGridItem() override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;

protected:
	virtual void onGridItemInitialize() override;
	virtual void onUpdate() override;
	virtual void onTakeDamage(const DamageInfo& i_damage) override;

    void SetChangerState(ZombieChangerState i_state);

private:
    bool CanChangeZombie(Zombie* i_zombie);
    void SpawnZombie(bool i_success);
    void onAnimationDone(const std::string& i_tabel);

    ZombieChangerState m_state;
    pvztime_t m_changeTimer;

};


#endif
 