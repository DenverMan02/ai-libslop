//
//  IDataPersistor.h
//  PlantsVersusZombies2
//
//  Created by PopCap User on 1/17/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_IDataPersistor_h
#define PlantsVersusZombies2_IDataPersistor_h

#include "RtSerial.h"

class IDataPersistor
{
public:
	virtual ~IDataPersistor() {}
	virtual void Load() = 0;
	virtual void LoadWithNotify() = 0;
	virtual bool Save() = 0;
	virtual bool IsFileExist() = 0;
};
#endif
