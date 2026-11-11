//
//  Plant_FireGourd.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-11-29.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_FireGourd__
#define __PlantsVersusZombies2__Plant_FireGourd__

#include "PlantFramework.h"
#include "RtObject.h"
#include "GridItemGourdFire.h"
#include <vector>


enum FireGourdState
{
	FIREGOURD_STATE_FIRING = STATE_FRAMEWORK_BEGIN,
	FIREGOURD_STATE_RECOVER_LOOP1,
    FIREGOURD_STATE_RECOVER_LOOP2,
    FIREGOURD_STATE_RECOVER_LOOP3,
    FIREGOURD_STATE_START_FIRE,
	FIREGOURD_STATE_RECOVER_REST,
	FIREGOURD_STATE_RECOVER_RETURN,
};


class PlantFireGourd : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantFireGourd, PlantFramework, RtClass);
	PlantFireGourd();
    virtual ~PlantFireGourd();
    virtual void	SetPopAnimDelegates(class PlantAnimRig* i_rig) override;
    
	virtual void	Initialize() override;
    
	virtual bool	CanApplyPlantfood() override;
	virtual void	ApplyPlantfood() override;
	virtual void	CancelPlantfood() override;
	virtual void	UpdatePlantfood() override;
    
	//virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
	virtual bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
    virtual bool    OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
	//virtual void	onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect);

    void    UpdateActions() override;
    
    virtual void		onAnimStoppedCallback(const std::string& i_animCommand) override;
    
    virtual void        Draw(Graphics* g) override;
    
    virtual void    onDestroy() override;
    virtual void	OnRelocating(Sexy::SexyVector2 plantPos) override;
    virtual void    onThrown();
    virtual void    AutoFire() override;
    void Idle() override;
private:
    
    void setState(int i_newState);

	bool			m_hasStartedPlantfoodAttack;
    //void fireProjectileCallback(pvztime_t i_atTime);
    
    bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();
    void GetPrimaryTarget(std::vector<BoardEntity*>& target);
    virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
    Sexy::TouchID	m_touchIdent;
    
    bool isReadyToFire();
    void willStartFiringAnimation();
    void CalcDamageGridAndAmount();
    
    int         damageGrid;
    float       statusCD1;
    float       statusCD2;
    float       statusCD3;
    
    float       damageAmount;
    
    pvztime_t   burnEndedTime;
    pvztime_t   m_nextLaserDamageTime;
    
    std::vector<RtWeakPtr<BoardEntity> > m_hitEntities;
    
    void OnUseSpecialAnimCommand(pvztime_t i_timeStamp);
	void OnUseActionAnimCommand(pvztime_t i_timeStamp);

    RtWeakPtr<GridItemGourdFire>  m_gridFireAnim;
    RtWeakPtr<class Effect_PopAnim> m_firingAnim;
    int		CalcFiringAnimRenderOrder();
};

namespace Message
{
	void FireGourdIsHit(PlantFireGourd* i_fireGourd);
}



#endif /* defined(__PlantsVersusZombies2__Plant_FireGourd__) */
