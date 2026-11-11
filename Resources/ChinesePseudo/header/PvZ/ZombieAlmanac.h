//
//  ZombieAlmanac.h
//  PlantsVersusZombies2
//
//  Created by Ross Baker on 5/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAlmanac__
#define __PlantsVersusZombies2__ZombieAlmanac__

#include <vector>
#include <map>
#include "NameMapper.h"

class ZombieAlmanac : public NameMapperBase
{
public:
	ZombieAlmanac(std::vector<int>& killedZombies);
	virtual ~ZombieAlmanac() {}
    
    static ZombieAlmanac& GetInstance()
    {
        static std::vector<int> k_EmptyKilled;
        static ZombieAlmanac instance(k_EmptyKilled);
        return instance;
    };
	
	void AssignKilledZombiesCollection(std::vector<int>& killedZombies);
	bool SetKilledZombie(const std::string& i_zombieTypeName);
	bool IsKilledZombie(const std::string& i_zombieTypeName);
private:
	bool isCamelType(const std::string& i_zombieTypeName);
	
	std::vector<int>* m_killedZombies;
	
	const static int ID_CAMEL_ALMANAC;
	const static int ID_CAMEL_ONEHUMP;
	const static int ID_CAMEL_SEGMENT_TOUCH;
};


#endif /* defined(__PlantsVersusZombies2__ZombieAlmanac__) */
