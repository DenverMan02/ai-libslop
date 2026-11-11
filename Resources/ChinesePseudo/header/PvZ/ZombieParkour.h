// ZombieParkour.h
// create by lfy
// 2023.06.02

#ifndef __ZOMBIEPARKOUR_H__
#define __ZOMBIEPARKOUR_H__

#include <stdio.h>
#include "ZombieAnimRig_Basic.h"
#include "ZombieBasic.h"
#include "ZombieEnums.h"


STATE_ENUM_CHILD_BEGIN(ZombieParkourState, ZombieState)
ZMASZS_Running,
ZMASZS_Climbing,
ZMASZS_Tackling,
STATE_ENUM_END(ZombieParkourState);


class ZombieParkourProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieParkourProps, ZombiePropertySheet, RtClass);
	
	ZombieParkourProps()
	{
		SmashDamage = 500.0f;
		RunningSpeedScale = 1.0f;
        LineBreakInterval = 2.0f;
        LineBreakHealPercent = 0.25f;
        LaneChangeTime = 0.6f;
        ContinuousLineBreakInterval = 1.0f;
        StunSelfDuration = 2.0f;
	}
	
	int		  SmashDamage;
	float	  RunningSpeedScale;
    pvztime_t LineBreakInterval;
    float     LineBreakHealPercent;
    pvztime_t LaneChangeTime;
    pvztime_t ContinuousLineBreakInterval;
    pvztime_t StunSelfDuration;
};


class ZombieParkour : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieParkour, ZombieBasic, RtClass);
	
    SexyVector3 CalcPositionInTime(pvztime_t i_time) override;
    
protected:    
	
	DECLARE_STATE_FUNCTIONS(ZombieState, Running);
	DECLARE_STATE_FUNCTIONS(ZombieState, Climbing);
	DECLARE_STATE_FUNCTIONS(ZombieState, Tackling);

    void onPlaceOnBoard() override;
    void onZombieInitialize() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onTackleAnimationStopped(const std::string& i_animStopped);
    void onClimbAnimationStopped(const std::string& i_animStopped);    

	std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_SHOCK"; }
	std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BIG_ASH"; }
private:

    bool canLineBreak();
    bool isBelowHealPercent();
    bool isOverTimestamp();
    void changeRow();
    bool goDown();
    bool goUp();
    bool goBesideRow(int i_row, int i_col);
    void searchAndTackle();
    bool isTallGrid(const std::vector<GridItem*>& i_gridItems);

    BoardEntity* findClimbTarget();
    
    pvztime_t m_lineBreakTimestamp;
    float     m_currentHealPercent;
    pvztime_t m_continuousLineBreakTimestamp;
    bool      m_climbingSingleGird;
};


class ZombieAnimRig_Parkour : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Parkour, ZombieAnimRig_Basic, RtClass);

	bool PlayRunning();
    bool PlayClimbing(AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayTackling(std::string i_popName, AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
    void onPopAnimInitialized() override;
private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif