/*
 * WormHoleSystem.h
 *
 *  Created on: 2021-7-14
 *      Author: admin
 */

#ifndef WORMHOLESYSTEM_H_
#define WORMHOLESYSTEM_H_

#include "GameSubSystem.h"
#include "Core.h"
#include "BoardEntity.h"

namespace Message
{
	void NotifyTutorialWormHoleEnd();
}

enum WormState
{
	WORMSTATE_NONE,
	WORMSTATE_WRAPIN,
	WORMSTATE_TRANSFER,
	WORMSTATE_WRAPOUT,
	WORMSTATE_TUTORIAL_WARPIN,
	WORMSTATE_DONE
};

struct WormRecord
{
	WormRecord()
    :WrapInTime(0)
    ,WrapOutTime(0)
	,WrapInHeight(0)
    {}

    Point WrapInGridPoint;
    Point WrapOutGridPoint;
    float WrapInTime;
    float WrapOutTime;
    float WrapInHeight;
};

struct EntityWormData
{
	EntityWormData()
	:IsWarping(false)
	,FinalHeight(0)
	,WarpTime(0)
	,OriginalHeight(0)
	{}

	BoardEntityPtr Entity;
	bool IsWarping;
	float FinalHeight;
	float WarpTime;
	float OriginalHeight;
};

class WormHoleSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(WormHoleSubsystem, GameSubSystem, RtClass);

    void Generate(WormRecord i_record);
    void Update() override;
    void SetState(WormState i_state);
    void GenerateRandom();
    void GenerateTutorial();

protected:
    void onInitialized() override;
    void registerForEvents() override;
    void onDestroy() override;

private:
    void generateTutorial();
    void GetTutorialEntities(std::vector<BoardEntity*>& i_entities);
    void findTargets(std::vector<class BoardEntity*>& targets, const Point& i_gridPoint);
    void Warping(class BoardEntity* i_entity, pvztime_t i_warpTime, float i_finalHeight);
    void WarpTarget(class BoardEntity* i_entity, bool i_warpIn);
    bool IsWarpDone();
    void UpdateWarping(bool i_warpIn);
    void WarpingOut();
    void Transfer();
    void UpdateInitEndHeight(BoardEntityPtr i_entityPtr, float i_initHeight, float i_endHeight);
    void PlayWormEffectStart(const Point& i_gridPoint);
    void PlayWormEffect(bool i_warpIn);
    void PlayWormEffectEnd();
    void CreateWormEffect();
    void CreateTutorialWormEffect(const Point& i_grid);
    void onWormEffectDone(const std::string& i_animName);
    void FillGrids();
    bool IsValidWrapOutGrid(const Point& i_gridPoint);
    void CheckValidWrapOutGrid();

    std::vector<EntityWormData> m_entities;
    WormState m_state;
    pvztime_t m_elapsedTime;
    WormRecord m_record;
    RtWeakPtr<class Effect_PopAnim> m_wormEffect;
    std::vector<Point> m_validWarpInGrids;
    std::vector<Point> m_validWarpOutGrids;
};


#endif /* WORMHOLESYSTEM_H_ */
