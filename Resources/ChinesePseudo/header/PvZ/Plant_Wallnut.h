#ifndef __PLANT_WALLNUT_H__
#define __PLANT_WALLNUT_H__

#include "PlantFramework.h"
#include "Shield.h"
#include "RtObject.h"

/*
============================================================== 
Refer to the PlantFramework class to determine what functions
you can override.

If you plan to add specific members to this specific zombie
framework, remember to, you know ... include a constructor.
==============================================================
*/

class WallnutProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(WallnutProps, PlantPropertySheet, RtClass);
    
    bool    IsPrimal = false;
    float 	PlantFoodShieldHitpoints = 0.0f;
    float   HPIncPercentInHomeWorld = 0.f;
    float   ChargeTime = 20.f;
    
    std::vector<ShieldProps> PfShieldProps;
};

typedef enum WallNutBallsType
{
    WNB_Front,
    WNB_Back
}WallNutBallsType;

typedef enum WallNutBallsState
{
    WBS_None,
    WBS_RECOVERING,
    WBS_3,
    WBS_2,
    WBS_1,
    WBS_0,
    WBS_COUNT
}WallNutBallsState;

class PlantWallnut : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantWallnut, PlantFramework, RtClass);

    ~PlantWallnut();
    
	virtual void	Initialize() override;
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual void	PlayChewedOnSound() override;
	
	virtual DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
    
    virtual void TakeSmashAttack(ZombiePtr i_instigator);
	virtual bool TryBlockZombossRush(Zombie* i_zombie) override;
    
    virtual void onKilled(bool i_instantKill) override;
    bool CanBeWatered() override;
    
    virtual void Draw(Graphics* g) override;
    
    void SetBaby(bool i_baby) { m_baby = i_baby; }
    bool IsBaby() { return m_baby; }
    void OnAnimStopped(const std::string &i_animName);
    
    virtual void PlayAttackAnimation()override;
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile*	 Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
protected:
    //	virtual void updateShieldLayers();
    void UpdateActions() override;
    
    void tossZombie(Zombie* i_zombie);
    void tossEnded(Zombie* i_zombie);
    
    void DieExplode();
    
    RtWeakPtr<Shield> m_shield;
    
private:
    int GetBallsCount();
    void RecoverAllBalls();
    void ShotOneBall();
    
    bool NeedCharge();
    void DoCharge();
    
    void UpdateFrontBall();
    void UpdateBackBall();
    // void RenderBalls(Graphics *i_g);
    
    RtWeakPtr<GameObject> LoadBallsRig(WallNutBallsType i_ballsType);
    RtWeakPtr<class Effect_PopAnim> GetFrontBallsRig();
    RtWeakPtr<class Effect_PopAnim> GetBackBallsRig();
    
private:
    bool m_baby = false;
    bool m_needCharge = false;
    bool m_isCharging = false;
    pvztime_t m_chargeEndTime = 0.f;
    
    WallNutBallsState m_ballsState = WBS_None;
    RtWeakPtr<class Effect_PopAnim> m_ballsFrontRig = nullptr;
    RtWeakPtr<class Effect_PopAnim> m_ballsBackRig = nullptr;
};

#endif //__PLANT_WALLNUT_H__
