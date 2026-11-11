//
//  Zomboss.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 2/10/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//


#ifndef PlantsVersusZombies2_Zomboss_h
#define PlantsVersusZombies2_Zomboss_h

#include "Zombie.h"
#include "ZombieWithActions.h"

STATE_ENUM_CHILD_BEGIN(ZombossState, ZombieState)
	Zomboss_Intro,
	Zomboss_ChangeStage,
	Zomboss_Epilogue,
	Zomboss_Death,
 	Zomboss_None,
STATE_ENUM_END(ZombossState);

class ZombossProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombossProps, ZombiePropertySheet, RtClass);

	ZombossProps()
	{
		ZombossStageCount = 1;
	}

	int 		ZombossStageCount;
};

class Zomboss : public ZombieWithActions
{
public:
	RT_CLASS_DEFINE(Zomboss, Zombie, RtClass);

	typedef RtReflectionDelegate<Delegate0> OnActionFinished;

	void showBossProgressMeter(OnActionFinished i_onShowProgressMeterFinished);
	void setStartStageIndex(int i_startStagetIndex);

    virtual ImagePtr getHeadIcon();
	virtual void introduceMyself(OnActionFinished i_onIntroFinished);
	virtual void startFunctioning(){}

	virtual bool CanBeMowed() const override;
	virtual bool CanBeFlickedOff() const override;
    
	bool allowElectrocuteState() const override
	{
		return false;
	}
	bool allowAshState() const override
	{
		return false;
	}
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }
    
    virtual bool CanBePoisoned() const override
    {
        return false;
    }
    
    virtual bool CanBeBlovered() const override
    {
        return false;
    }

	virtual void TakeDamage(const DamageInfo& i_damage) override;
    
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    
    virtual bool IsInRow(int i_row) const;
    int GetStageIndex() { return m_currentStageIndex; }
    void chooseDeathState(const DamageInfo& i_deathBlow) override;
    virtual bool IsDying() const override;
protected:
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;

	//interfaces to override
	virtual void onChangeActiveStage(int i_activeStageIndex);
	virtual void onChangeStageAnimDone(const std::string& i_label){};
	virtual bool canChangeStage() const { return true; }
    bool isImmuneToShrinking() override { return true; }

	/// Change Stage or Die!
	bool tryChangeStage();
	bool shouldZombossDie() const;
	bool shouldZombossChangeStages() const;
	void setActiveStageIndex(int i_activeStageindex);

protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, Intro);
	DECLARE_STATE_FUNCTIONS(ZombieState, ChangeStage);
	DECLARE_STATE_FUNCTIONS(ZombieState, Epilogue);
	DECLARE_STATE_FUNCTIONS(ZombieState, Death);
	DECLARE_STATE_FUNCTIONS(ZombieState, None);

	OnActionFinished					m_onIntroFinished;
	int 								m_currentStageIndex;
	int 								m_finalStageIndex;

private:
	void onIntroAnimDone(const std::string& i_label);
	void onDieAnimDone(const std::string& i_label);
	void onEpilogueAnimDone(const std::string& i_label);

	void 		hideProgressMeter() const;
	void 		updateProgressMeter() const;

	OnActionFinished					m_onShowProgressMeterFinished;
	pvztime_t 							m_startHealthFillTime;
	pvztime_t 							m_endHealthFillTime;
};


#endif
