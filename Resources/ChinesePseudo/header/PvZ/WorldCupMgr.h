/*
 * WorldCupMgr.h
 *
 *  Created on: 2018-4-19
 *      Author: Administrator
 */

#ifndef WORLDCUPMGR_H_
#define WORLDCUPMGR_H_

#include "NetworkData.h"
#include "Widget.h"
//#include "core.h"
#include "ButtonListener.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"

namespace Message
{
	void NotifyTutorialState(int i_type);
}

enum TutorialStateType
{
	Ball_Zombie_Appeared,
	Ball_Zombie_Died,
	Player_Shotted
};

class WorldCupMgr : public LazySingleton <WorldCupMgr>
{
public:
	WorldCupMgr();
    ~WorldCupMgr();

    void SetCurrentSetStartingSun(int i_sun) { m_currentSetStartingSun = i_sun; }
    int GetCurrentSetStartingSun() { return m_currentSetStartingSun; }
    const std::vector<std::string> GetCurrentSet() const { return m_currentSet; }
    void InitTestData();
    void NotifyTutorialState(TutorialStateType i_type);
    void SetCarrierForTutorial(RtWeakPtr<Zombie> i_carrier);
    bool IsPlantDisabled(int i_x, int i_y);
    Point GetRandomPlantSpotForTutorial();
    int GetCurrentSetSize();
    void SetCurrentSetId(int i_id) { m_currentSetId = i_id; }
    int GetCurrentSetId() { return m_currentSetId; }
    pvztime_t GetGameEndTime();
    int GetCurrentScore(bool i_zombie);
private:
    bool ShouldDoTutorial(TutorialStateType i_type);
    bool IsTutorial();

    int m_currentSetStartingSun;
    std::vector<std::string> m_currentSet;
    int m_currentSetId;
};


#endif /* WORLDCUPMGR_H_ */
