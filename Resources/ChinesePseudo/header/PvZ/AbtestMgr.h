/*
 * AbtestMgr.h
 *
 *  Created on: 2020-2-10
 *      Author: Administrator
 */

#ifndef ABTESTMGR_H_
#define ABTESTMGR_H_

#include "Singleton.h"
#include "TimeMgr.h"

class AbtestMgr : public LazySingleton <AbtestMgr>
{
public:
	AbtestMgr();
    ~AbtestMgr();

    void CheckActivityInfos();
    int GetActivityInfos();
    int GetActivityAbtestId(int i_activityId);
    void Update();

private:
    void InitTestData();
    std::map<int, int> m_activityInfos;
    bool m_checkActivityInfosFinished;
    pvztime_t m_timeout;
};


#endif /* ABTESTMGR_H_ */
