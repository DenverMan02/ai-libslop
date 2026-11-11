/*
 * ZombieFairyTaleGargantuar.h
 *
 *  Created on: 2022-3-15
 *      Author: admin
 */

#ifndef ZOMBIEFAIRYTALEGARGANTUAR_H_
#define ZOMBIEFAIRYTALEGARGANTUAR_H_

#include "GravestoneAnimRig.h"
#include "GridItemGravestone.h"
#include "ZombieGargantuar.h"
#include "ZombieAnimRig_Gargantuar.h"


class GridItemHeavyShieldProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemHeavyShieldProps, GridItemGravestonePropertySheet, RtClass);
};

class GridItemHeavyShield : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemHeavyShield, GridItemGravestone, RtClass);

	void CalcDamageState();
	PlantingReason GetCantPlantReason() const override;

protected:
	void onGridItemInitialize() override;
	void KillGridItem() override;
private:
	void onAnimStoppedCallback(const std::string& i_animLabel);
	bool m_hasPlayDieAnim;
};

class HeavyShieldAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(HeavyShieldAnimRig, GravestoneAnimRig, RtClass);

	HeavyShieldAnimRig();

	void PlayStationary();

    void SetDamageState(int i_damageState, bool i_isAnimated) override;

    void onAnimStopped() override;

private:
    int m_queuedDamageStateAnim;
    bool m_inIntroAnim;
};

class ZombieFairyTaleGargantuarProps : public ZombieGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieFairyTaleGargantuarProps, ZombieGargantuarProps, RtClass);

	ZombieFairyTaleGargantuarProps()
	{
		HasImp = false;
		SpawnShieldName = "heavy_shield";
	}

	bool HasImp;
	std::string SpawnShieldName;
};

class ZombieFairyTaleGargantuar : public ZombieGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieFairyTaleGargantuar, ZombieGargantuar, RtClass);

    void onTakeFatalDamage(const DamageInfo &i_lastDamageReceived) override;
    void onLostHead() override;

protected:
    void playDeathAnimation() override;
    virtual void onInitialized() override;
    virtual void onZombieInitialize() override;
    void showAmmoLayers(bool i_show);
    bool isImpReadyToBeThrown() override;
    void onStartBleeding() override;

private:
    GridItemHeavyShield* tryPlaceShield(const Point& i_gridPosition);
    Point getDefaultShieldSpawnPosition();
    void dropShield();
    void spawnShieldShatterEffect(const Point& i_targetPosition, const std::string& i_animationName);
    bool canSpawnBoardAt(const Point& i_targetPosition) const;
};

class ZombieAnimRig_FairyTaleGargantuar : public ZombieAnimRig_Gargantuar
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleGargantuar, ZombieAnimRig_Gargantuar, RtClass);

    ZombieAnimRig_FairyTaleGargantuar()
    {

    }

    virtual const std::vector<std::string>& getHeadLayerNames() override;
};

class ZombieFairyTaleArmedGargantuarProps : public ZombieFairyTaleGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieFairyTaleArmedGargantuarProps, ZombieFairyTaleGargantuarProps, RtClass);

	ZombieFairyTaleArmedGargantuarProps()
	{

	}
};

class ZombieAnimRig_FairyTaleArmedGargantuar : public ZombieAnimRig_FairyTaleGargantuar
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleArmedGargantuar, ZombieAnimRig_FairyTaleGargantuar, RtClass);

    ZombieAnimRig_FairyTaleArmedGargantuar()
    {

    }
};

class ZombieFairyTaleArmedGargantuar : public ZombieFairyTaleGargantuar
{
public:
	RT_CLASS_DEFINE(ZombieFairyTaleArmedGargantuar, ZombieFairyTaleGargantuar, RtClass);

    void onTakeFatalDamage(const DamageInfo &i_lastDamageReceived) override;
    void onLostHead() override;

protected:
    void playDeathAnimation() override;
    void onInitialized() override;
    void onZombieInitialize() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

private:
    void dropImp();
};


#endif /* ZOMBIEFAIRYTALEGARGANTUAR_H_ */
