//
//  LevelMutatorModule.cpp
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 6/3/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelMutatorModule_h
#define PlantsVersusZombies2_LevelMutatorModule_h

#include <string>

#include "LevelModule.h"
#include "LevelMutatorTableProps.h"
#include "PVZTypes.h"
#include "RtObject.h"

class LevelMutatorModule : public LevelModule
{ 
public:
	RT_CLASS_DEFINE(LevelMutatorModule, LevelModule, RtClass) {}
	
protected:
    void registerForEvents() override;
	
	void postInitialize() override;
    
    void onLevelInitialized(RtWeakPtr<LevelDefinition>& io_level);
    
    void insertRiftEventMutations(RtWeakPtr<LevelDefinition>& io_level);
};


class LevelMutatorModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(LevelMutatorModuleProperties, LevelModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return LevelMutatorModule::StaticGetClass();
	}
	
	LevelMutatorModuleProperties()
	{
	}
    
    template<class T> T* GetLevelModule(int i_difficulty, int i_levelVersion) const
    {
        for (auto table : MutatorTables)
        {
            RtWeakPtr<LevelMutatorTableProps>    mutatorTablePropsPtr = table;
            if (mutatorTablePropsPtr.IsValid())
            {
                const MutatorTable* mutatorTable = LevelMutatorTableHelper::Find(mutatorTablePropsPtr, i_difficulty, i_levelVersion);
                if (mutatorTable)
                {
                    for (auto& module : mutatorTable->Modules)
                    {
                        LevelModulePropertiesPtr props = module;
                        if (props->IsA<T>())
                        {
                            return props->Cast<T>();
                        }
                    }
                }
            }
        }
        return nullptr;
    }
    
	void GatherDifficultyProps(std::vector<RtWeakPtr<LevelModuleDifficultyProps>>& io_difficultyProps, std::vector<RtWeakPtr<LevelModuleDifficultyUIProps>>& io_difficultyUI,
			bool i_riftTimed = false) const override;
	
    std::vector<RtId> MutatorTables;
};

#endif
