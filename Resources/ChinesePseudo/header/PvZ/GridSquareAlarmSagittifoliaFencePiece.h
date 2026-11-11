//
//  GridSquareAlarmSagittifoliaFencePiece.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 2/4/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef GridSquareAlarmSagittifoliaFencePiece_h
#define GridSquareAlarmSagittifoliaFencePiece_h

#include <stdio.h>
#include "BoardEntity.h"
#include "GameSubSystem.h"

class GridSquareAlarmSagittifoliaFencePiece : public BoardEntity
{
public:
	RT_CLASS_DEFINE(GridSquareAlarmSagittifoliaFencePiece, BoardEntity, RtClass);
	
	GridSquareAlarmSagittifoliaFencePiece();
	
    std::string getPamName();
    std::string getAnimName();
    void StartEffect(Sexy::Point i_gridLocation);
	Point GetGridLocation() { return m_gridLocation; }
protected:
	RtWeakPtr<class Effect_PopAnim> createEffect();
	void onDestroy() override;

private:
	Point m_gridLocation;
	RtWeakPtr<class Effect_PopAnim> m_glowEffect;
};

class AlarmSagittifoliaAvatarSkill : public BoardEntity
{
public:
RT_CLASS_DEFINE(AlarmSagittifoliaAvatarSkill, BoardEntity, RtClass);
	AlarmSagittifoliaAvatarSkill();
	virtual ~AlarmSagittifoliaAvatarSkill(){};

	void takeEffect();
	void setInfo(pvztime_t i_endTime,const Point& i_point,const DamageInfo& i_damageInfo);
	pvztime_t getEndTime(){
		return m_endTime;
	};
protected:
	void onDestroy() override;
private:
	pvztime_t m_endTime;
	Point m_gridLocation;
	DamageInfo m_damageInfo;
	RtWeakPtr<class Effect_PopAnim> m_effect;
};

class AlarmSagittifoliaAvatarSkillSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(AlarmSagittifoliaAvatarSkillSystem, GameSubSystem, RtClass);
	AlarmSagittifoliaAvatarSkillSystem();
	virtual ~AlarmSagittifoliaAvatarSkillSystem();

	void CreateEffect(pvztime_t i_endTime, const Point& i_point, const DamageInfo& i_damageInfo);
protected:
	void Update() override;
private:
	pvztime_t											m_timeUpdate;
	std::vector<AlarmSagittifoliaAvatarSkill>			m_pieces;
};

#endif