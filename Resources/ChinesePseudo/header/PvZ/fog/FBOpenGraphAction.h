//
//  FBOpenGraphAction.h
//  PlantsVersusZombies2
//
//  Created by Seth on 2013-05-02.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_FBOpenGraphAction_h
#define PlantsVersusZombies2_FBOpenGraphAction_h

#include "Common.h"

class FBOpenGraphAction
{
    public:
        FBOpenGraphAction(const SexyString& i_actionName);
        SexyString getActionName();
		void addStringParam(const SexyString& name, const SexyString& type, const SexyString& value);
		void addNumberParam(const SexyString& name, const SexyString& type, int value);
	
		std::vector<SexyString> m_actionStringParamNames;
		std::vector<SexyString> m_actionStringParamTypes;
		std::vector<SexyString> m_actionStringParamValues;
		
    private:
    SexyString m_actionName;
	
	
};

#endif
