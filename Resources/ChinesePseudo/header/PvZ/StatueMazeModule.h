/*
 * StatueMazeModule.h
 *
 *  Created on: 2019-11-9
 *      Author: Administrator
 */

#ifndef STATUEMAZEMODULE_H_
#define STATUEMAZEMODULE_H_

#include "LevelModule.h"
#include "MTRand.h"
#include "Precompile.h"
#include <vector>
#include "Core.h"

typedef RtWeakPtr<class GridItemMazeStatue> GridItemMazeStatuePtr;
typedef RtWeakPtr<class UIMazeMiniGameCredit> UIMazeMiniGameCreditPtr;
typedef RtWeakPtr<class UIMazeMiniGameLifeCounter> UIMazeMiniGameLifeCounterPtr;

namespace Message
{
    void NotifyStatueReveal();
    void NotifyStatueEnable(bool i_trigger);
    void NotifyStatueBreak();
}

enum MazeGameState
{
    PVZ_BEGIN_ENUM(MAZEGAMESTATE_),
    MAZEGAMESTATE_CREATING,
    MAZEGAMESTATE_REVEALING,
    MAZEGAMESTATE_ROTATING,
    MAZEGAMESTATE_PLAYING,
    MAZEGAMESTATE_CLEANING,
    MAZEGAMESTATE_ENDING,
    MAZEGAMESTATE_COMPLETE,
    PVZ_END_ENUM(MAZEGAMESTATE_)
};

enum MatrixRotateType
{
	Type_None,
	Type_Clockwise,
	Type_Anti_Clockwise
};

struct GameMatrixInfo
{
	GameMatrixInfo()
	{
		Clockwise = false;
		RotateTime = 0.0f;
		WaitDuration = 0.0f;
	}

	bool Clockwise;
	float RotateTime;
	float WaitDuration;
};

struct GameSetInfo
{
	GameSetInfo()
	{
		MatrixSize = 0;
		DisplayTime = 0.0f;
		TargetNum = 0;
		BonusLife = 0;
	}

	int MatrixSize;
	float DisplayTime;
	int TargetNum;
	int BonusLife;
};

class StatueMazeModule: public LevelModule
{
public:
	RT_CLASS_DEFINE(StatueMazeModule, LevelModule, RtClass);

	StatueMazeModule();
	virtual ~StatueMazeModule();

	void CheatRotateStatue();
	void setState(MazeGameState i_state);
	MazeGameState getState();
	void updateState();
	bool DisabledPlay();

protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

	virtual void initializeModule() override;
	void onLoadComplete();
	void gameplayStarted();
	void onUpdate();
	void onLevelEnded();

private:
	bool IsInState(uint32 state) const { return m_state == state; }
	void resetMazeStatues(int i_size);
	void createMazeStatues(int i_size);
	Sexy::Point	GetStatueLocationOffset(int i_size);
	Sexy::Point	GetStatueRealLocation(int i_index_1, int i_index_2, Point i_offset);
	Sexy::Point GetCenter(int i_size);
	float GetTargetDegree(const SexyVector3& i_start, const SexyVector3& i_end);
	float GetTargetRadius(const SexyVector3& i_start, const SexyVector3& i_end);
	bool IsCenter(int i_index_1, int i_index_2);
	void RecordCenterPosition(int i_size);
	void RotateMatrix(const std::vector<std::vector<GridItemMazeStatuePtr> >& i_matrix, bool i_clockwise);
	void onNotifyStatueHit(float i_x, float i_y);
	void onStatueDestroyed(class GridItemMazeStatue* i_statue);

	void TryRotateTargetStatue(GridItemMazeStatuePtr i_statue, const SexyVector3& i_center, bool i_clockwise, pvztime_t i_duration);

	void createHammerEffect();
	void generateHammerEffect(const SexyVector3& i_pos);
	void onHammerEffectDone(const std::string& i_animName);
	void createUIs();
	void onFillSets();
	void onNextSetStart();

	void resetingSets();
	void fillSets();
	void pickTargets();
	void setMatrixEnable(bool i_enable);
	void CreatingSets();
	void RevealingSets();
	void RotatingSets();
	void PlayingSets();
	void CleaningSets();

	void onCreatingDone();
	void onRevealingDone();
	void onRotatingDone();
	void onCleaningDone();

	void onFadedFinishedCallback(class StandaloneEffect* i_effect);

	void setChangeCredit(bool i_isTarget);
	bool finishCurrentSet();
	bool finishAllSet();
	bool costAllLife();
	void changeLife(bool i_add);

	bool checkWinCondition();
	void onReviveCancel();
	void onReviveOK();

	std::vector<std::vector<GridItemMazeStatuePtr> > m_matrix;
	SexyVector3 m_centerPt;
	UIMazeMiniGameCreditPtr m_creditUI;
	UIMazeMiniGameLifeCounterPtr m_lifeUI;
	MazeGameState m_state;
	int m_currentSetNum;
	int m_currentMatrixNum;
	std::vector<GameMatrixInfo> m_currentMatrixs;
	GameSetInfo m_currentSet;

	//Score
	int m_currentLeftNum;
	//Life
	int m_currentLife;
	bool m_InReviveUI;
	int m_currentHits;
	//Effects
	RtWeakPtr<class Effect_PopAnim> m_hammerEffect;
};

class StatueMazeModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(StatueMazeModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return StatueMazeModule::StaticGetClass();
	}

	struct MatrixInfo
	{
		MatrixInfo()
		{
			Type = Type_None;
			WaitDuration = 0;
			RotateTime = 0;
		}

		MatrixRotateType Type;
		float WaitDuration;
		float RotateTime;
	};

	struct SetInfo
	{
		SetInfo()
		{
			MatrixSize = 0;
			DisplayTime = 0;
			TargetNum = 0;
			BonusLife = 0;
		}

		int MatrixSize;
		float DisplayTime;
		int TargetNum;
		std::vector<MatrixInfo> MatrixInfos;
		int BonusLife;
	};

	StatueMazeModuleProperties()
	{

	}

	std::vector<SetInfo> SetInfos;
};


#endif /* STATUEMAZEMODULE_H_ */
