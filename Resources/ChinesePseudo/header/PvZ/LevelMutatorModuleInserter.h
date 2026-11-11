//
//  LevelMutatorModuleInserter.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 8/25/16.
//  Stolen by Jason Emery on 5/30/19 for Rifts.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef LevelMutatorModuleInserter_hpp
#define LevelMutatorModuleInserter_hpp

#include "RtDb.h"
#include "LevelMutatorTableProps.h"

struct DifficultyData;
class LevelDefinition;
class LevelModuleProperties;
class StarChallengeModuleProperties;
class BonusChallengeModuleProperties;

namespace DifficultyConstants
{
	static constexpr int k_NonDifficulty = -1;
}

// Not sure this really needs to be a class as it was originally written.
class LevelMutatorModuleInserter
{
public:
    void Execute(RtWeakPtr<LevelDefinition> io_level, const RtId& i_mutatorTable, int i_difficultyLevel, int i_levelVersion, int i_tableDebugIndex);
    void AddLevelModules(RtWeakPtr<LevelDefinition> io_level, const std::vector<RtId>& i_modules) const;

protected:
	void applyGridMutator(RtWeakPtr<LevelDefinition> io_level, const MutatorGridEntry& i_gridMutator);
    void addBonusChallengeModules(RtWeakPtr<LevelDefinition> io_level, const std::vector<RtId>& i_modules) const;
	void addMainChallengeModules(RtWeakPtr<LevelDefinition> io_level, const std::vector<RtId>& i_modules);

private:
    BonusChallengeModuleProperties* getOrCreateBonusChallengeModule(RtWeakPtr<LevelDefinition> io_level) const;
    
	StarChallengeModuleProperties* getOrCreateChallengeModule(RtWeakPtr<LevelDefinition> io_level);
	LevelModuleProperties* createNewChallenge(const std::string& i_boardGridMap, const int i_type, const std::string i_subtype) const;
	
};

#endif
