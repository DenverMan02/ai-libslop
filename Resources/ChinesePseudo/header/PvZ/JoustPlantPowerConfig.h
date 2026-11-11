/*
 * JoustPlantPowerConfig.h
 *
 *  Created on: 2018-8-22
 *      Author: Administrator
 */

#ifndef JOUSTPLANTPOWERCONFIG_H_
#define JOUSTPLANTPOWERCONFIG_H_

#include "Precompile.h"
#include "RtObject.h"

struct PlantPowerSet
{
	int rareType;
    std::vector<int> levelPower;
    int avatarPower;

    PlantPowerSet()
    {
    	rareType = 0;
    	avatarPower = 0;
    }
};

class JoustPlantPowerConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(JoustPlantPowerConfig, Sexy::RtObject, RtClass);

    JoustPlantPowerConfig();
    ~JoustPlantPowerConfig();

    void Refresh();

    int GetTargetPlantPower(int i_level, int i_rare, bool i_avatar);

private:
    bool m_inited;
    std::vector<PlantPowerSet> m_setList;
};


#endif /* JOUSTPLANTPOWERCONFIG_H_ */
