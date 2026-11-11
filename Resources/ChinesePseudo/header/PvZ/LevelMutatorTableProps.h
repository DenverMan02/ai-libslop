//
//  LevelMutatorTableProps.hpp
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 8/24/16.
//  Stolen by Jason Emery on 5/30/19 for Rifts.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef LevelMutatorTableProps_h
#define LevelMutatorTableProps_h

#include "ObjectTypeDescriptor.h"

enum GridMapType
{
	GridMapType_NONE = 0,
	GridMapType_MOLD,
	GridMapType_GRIDITEMS,
	
	GridMapType_COUNT
};

struct MutatorGridEntry
{
	std::string Grid;
	GridMapType Type;
	std::string Subtype;
};

enum MutatorModuleType
{
    MutatorModuleDefault,
    MutatorModuleBonusChallenge,
	MutatorModuleMainChallenge
};

struct MutatorTable
{
	int Level;  // Difficulty Level
    int LevelVersion = -1;
    std::vector<MutatorGridEntry>   GridMaps;
    std::vector<RtId>               Modules;
    MutatorModuleType               ModuleType;
};

class LevelMutatorTableProps : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(LevelMutatorTableProps, ObjectTypeDescriptor, RtClass);
	
	std::vector<MutatorTable> Tables;
};
typedef RtWeakPtr<LevelMutatorTableProps> LevelMutatorTablePropsPtr;

namespace LevelMutatorTableHelper
{
    const MutatorTable* Find(RtWeakPtr<LevelMutatorTableProps>& i_tablePtr, int i_difficultyLevel, int i_levelVersion);
};

#endif /* LevelMutatorTableProps_h */
