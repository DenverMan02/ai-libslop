/*
 * CollectableAdBoxMgr.h
 *
 *  Created on: 2018-11-29
 *      Author: Administrator
 */

#ifndef COLLECTABLEADBOXMGR_H_
#define COLLECTABLEADBOXMGR_H_

#include "Singleton.h"
#include "TimeMgr.h"
#include "NetworkData.h"

enum NodeType
{
	N_UPPER_LEFT,
	N_DOWN_LEFT,
	N_DOWN_RIGHT,
	N_UPPER_RIGHT,
	N_MAX_NUMBER
};

class NetworkBoxReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkBoxReward, INetworkData, RtClass);

public:
    NDLoginRewardBonus reward;
};

class CollectableAdBoxMgr : public LazySingleton <CollectableAdBoxMgr>
{
public:
	CollectableAdBoxMgr();
    ~CollectableAdBoxMgr();

    void TrySpawnAdBox();
    void SpawnAdBox();
    Point GetTargetNode(NodeType i_type) { return m_nodes[i_type]; }
    void PopUpRewardUI();
    void ContinueGame();
    bool CanSpawnAdBoxInLevel();
    bool NeedSpawnAdBox();
    void ResetSpawns();
    void Update();
    bool HasAdService();
    void RequestNetwork();
    const NDLoginRewardBonus& GetReward() { return m_reward; }
    bool CheckLoadResource();
    std::string GetResourceGroupName() { return "Effects_AdBox"; }
    void LoadAdService();
private:
    class CollectableAdBox* AddAdBox(const SexyVector3& i_position);
    bool IsNormalAwardLevel();
    void onLevelEnded();

    Point m_nodes[N_MAX_NUMBER];

    NDLoginRewardBonus m_reward;
    bool m_hasAdService;
};

#endif /* COLLECTABLEADBOXMGR_H_ */
