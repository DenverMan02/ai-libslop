/*
 * GridItemCardGameZombie.h
 *
 *  Created on: 2022-6-7
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIE_H_
#define GRIDITEMCARDGAMEZOMBIE_H_

#include "GridItemBreakableTarget.h"
#include "GridItemPropertySheet.h"
#include "RtDb.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include "StoneLottery.h"

typedef Delegate0 ZombieActionCallback;

// CardGameZombieIntentionType
enum CardGameZombieIntentionType
{
	ZombieIntention_Invalid = -1,
	ZombieIntention_Summon,
	ZombieIntention_Attack,
	ZombieIntention_Special,
	ZombieIntention_Max,
};

// GridItemCardGameZombieActionData
struct GridItemCardGameZombieActionData
{
	GridItemCardGameZombieActionData() {
		IntentionType = ZombieIntention_Invalid;
		Ratio = 100;
		IntentionRound = 0;
		CoolDownRound = 0;
		Desc = "";
		ShowIntention = false;
	}

	CardGameZombieIntentionType IntentionType;// intention type
	int Ratio;// happen ratio
	int IntentionRound;// happen after how many rounds.
	int CoolDownRound;// cool down rounds.
	std::string Desc;// intention description string
	bool ShowIntention;// show intention
};

// GridItemCardGameZombieProps
class GridItemCardGameZombieProps : public GridItemBreakableTargetProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieProps, GridItemBreakableTargetProps, RtClass);

    GridItemCardGameZombieProps();

    std::string PopAnimAttackName;// play attack name
    std::string PopAnimIntentionName;// play itention name
    std::vector<GridItemCardGameZombieActionData> Actions;// zombie actions data
};


// GridItemCardGameZombieAction
class GridItemCardGameZombieAction
{
public:
	GridItemCardGameZombieAction();

	virtual void Init(int index, GridItemCardGameZombieActionData data);
	virtual void StartAction();
	virtual void EndAction();
	virtual void RoundResume();
	virtual void WaitIntention();

	void Reset();
	bool IsReady();
	bool IsDone();
	bool IsIntention();
	bool IsCooldown();
	bool IsShowIntention();

	int GetIndex() const;
	int GetRatio() const;
	int GetIntentionRound() const;
	int GetCooldownRound() const;
	int GetCurrentIntentionRound() const;
	int GetCurrentCooldownRound() const;
	SexyString GetDescription();
	Image* GetIntentionImage();

	void SetCallbackFunc(ZombieActionCallback func);

protected:
	int m_index;// action index
	int m_intentionCountDown;// action real intention count down
	int m_coolDownRound;// action real cool down round
	GridItemCardGameZombieActionData m_data;// action data.
	ZombieActionCallback m_func;// action execute
	bool m_isDone;// action done
};


// GridItemCardGameZombie
class GridItemCardGameZombie : public GridItemBreakableTarget
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombie, GridItemBreakableTarget, RtClass);

	virtual ~GridItemCardGameZombie();

	virtual float	GetMaxHitpoints() const override;

	virtual void PickCardStart(int round);
	virtual void EnemyActionStart();
	virtual void EnemyActionEnd();
	virtual void RoundFinishStart();

	virtual void PlayIdleAnim();
	virtual void PlayAttackAnim();
	virtual void PlayIntentionAnim();
	virtual void PlayDeathAnim();

	void EnableDrawHealthBar(bool draw);
	void SetIntentionCountDown(int round);

	bool ShouldBlockLevelCompletion() const override { return true; }
	bool IsCurrentActionDone();

protected:
	virtual void registerEvents();
	virtual void GenerateZombieActions();
	virtual GridItemCardGameZombieAction* PickAction();
	virtual void DoAction(GridItemCardGameZombieAction* action);
	virtual void EndAction(GridItemCardGameZombieAction* action);

//	virtual void Action();

	void onGridItemInitialize() override;
	void onDraw(class Sexy::Graphics* i_g) override;

	virtual void DrawHealthBar(class Sexy::Graphics* i_g);
	virtual void DrawIntention(class Sexy::Graphics* i_g);

	virtual bool onTouchEvent(const Sexy::Touch& i_touch);
    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchMoved( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );
	virtual void TouchesCanceled();

	virtual void onTakeDamage(const DamageInfo& i_damage) override;
	virtual void onUpdate() override;

	virtual void onAttackAnimDone(const std::string& name);
	virtual void onIntentionAnimDone(const std::string& name);

	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param);

	virtual void ShowIntentiontips(GridItemCardGameZombieAction* action);
	virtual void CloseIntentiontips();

	virtual void SetLayerVisibility(std::string layerName, bool show);

protected:
	int m_round;// current round
	int m_intentionCountDown;// the intention count down.before real action start.
	bool m_drawHealthBar;// if should draw health bar.

	Sexy::TouchID	m_owningTouchIdent;
	bool			m_touchHovering;

	std::vector<GridItemCardGameZombieAction*> m_zombieActions;
	GridItemCardGameZombieAction* m_currentAction;

    class StoneLotteryItemTipUI* m_tipUI;
};


#endif /* GRIDITEMCARDGAMEZOMBIE_H_ */
