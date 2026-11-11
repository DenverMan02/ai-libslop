//
//  ZombieModernSuperfanImp.hpp
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 1/6/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ZombieModernSuperfanImp_hpp
#define ZombieModernSuperfanImp_hpp

#include "StateMachine.h"
#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"


STATE_ENUM_CHILD_BEGIN(ZombieModernSuperfanImpState, ZombieStateImp)
ZMSIZS_CheerForTheEnd,
STATE_ENUM_END(ZombieModernSuperfanImpState);

class ZombieModernSuperfanImpProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieModernSuperfanImpProps, ZombiePropertySheet, RtClass);

	int		MinTriggerColumn = 0;
	int		MaxTriggerColumn = 2;

	float	ExplosionDamage = 200;
	float	ExplosionRadius = 50;
};

class ZombieModernSuperfanImp : public ZombieImp
{
public:
	RT_CLASS_DEFINE(ZombieModernSuperfanImp, ZombieImp, RtClass);

	void SetFlyingDestinationWithTravelTime(const SexyVector3 i_destination, const float i_timeToTravel, const float i_apex = 64.0f, bool i_invincibleWhileInAir = false) override;

protected:;
		  OVERRIDE_STATE_UPDATE(ZombieState, Walk);
		  DECLARE_STATE_FUNCTIONS(ZombieState, CheerForTheEnd);

		  void onPlaceOnBoard() override;

		  bool canInitiateCheeringForTheEnd();

		  void onLandingAnimStopped(const std::string& i_animLabel) override;
		  void onCheerForTheEndAnimStopped(const std::string& i_animLabel);
		  void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

private:
	int m_selectedTriggerColumn;
};



class ZombieAnimRig_ModernSuperfanImp : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ModernSuperfanImp, ZombieAnimRig_Imp, RtClass);

	bool GetKicked() { return m_kicked; }
	void SetKicked(bool i_kicked) { m_kicked = i_kicked; }

	bool PlayGetUp(AnimStoppedReflectionDelegate i_onAnimStopped) override;

	void CheerForTheEnd(AnimStoppedReflectionDelegate i_onAnimStopped);

	bool PlayLand(AnimStoppedReflectionDelegate i_onAnimStopped) override;

private:
	bool m_kicked;
};

#endif /* ZombieModernSuperfanImp_hpp */
