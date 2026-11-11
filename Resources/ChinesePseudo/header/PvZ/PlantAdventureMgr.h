/*
 * PlantAdventureMgr.h
 *
 *  Created on: 2020-6-20
 *      Author: zhousen
 */

#ifndef PLANTADVENTUREMGR_H_
#define PLANTADVENTUREMGR_H_

#include "Singleton.h"

class PlantAdventureMgr : public LazySingleton<PlantAdventureMgr>
{
public:
	PlantAdventureMgr();
	virtual ~PlantAdventureMgr();

    void OnGotExploreTeamStatus(bool i_success);
    void BackToMap();

    bool CheckActivated();
    void onButtonClicked();
};

#endif /* PLANTADVENTUREMGR_H_ */
