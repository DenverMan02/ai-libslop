//
//  LevelModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/29/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LevelModule_h
#define PlantsVersusZombies2_LevelModule_h

#include "PropertySheetBase.h"
#include "RtObject.h"
#include "RtDb.h"
#include "GameObject.h"
#include "MapEventItem.h"

/// LevelModuleDifficulty
///     - Used for displays that aggregate level modules for showing difficulty to the player.
///     - Was added when we wanted to start differentiating for player-selected difficulty when mutators were added.
class LevelModuleDifficultyProps : public PropertySheetBase
{
public:
    enum DifficultyDisplayPriority
    {
        DISPLAY_PRIORITY_NEVER,
        DISPLAY_PRIORITY_LOW,
        DISPLAY_PRIORITY_MEDIUM,
        DISPLAY_PRIORITY_HIGH
    };

    struct DisplayPriorityOverride
    {
        MapEventSubType EventSubType;
        DifficultyDisplayPriority DisplayPriority;
    };

    DifficultyDisplayPriority GetDisplayPriority(MapEventSubType i_eventSubType);

public:
    RT_CLASS_DEFINE(LevelModuleDifficultyProps, PropertySheetBase, RtClass);

	std::string Description;
	std::string Name;
    DifficultyDisplayPriority DisplayPriority;

    std::vector<DisplayPriorityOverride> DisplayPriorityOverrides;
};

class LevelModuleDifficultyUIProps : public GameObject
{
public:
	RT_CLASS_DEFINE(LevelModuleDifficultyUIProps, GameObject, RtClass);

	SexyString Description;
	SexyString Name;
	std::string IconImage;
	std::string IconText;
};

/// LevelModuleProperties
///		- Simple property sheet, imported in from JSON packages
///		- Must implement GetModuleClass, returning the LevelModule type to
///		spawn and associate with this property sheet on initialization
class LevelModuleProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(LevelModuleProperties, PropertySheetBase, RtClass);
	
	virtual RtClass* GetModuleClass() const 
	{ 
		DBG_HALT_MSG("LevelModule of class %s does not implement GetModuleClass!", GetClass()->GetName());
		return NULL; 
	}
	
	virtual SexyString GetDescription() const
	{
		DBG_HALT_MSG("We need a description in the inherited module");
		return _S("");
	}

	virtual SexyString GetDescriptiveName() const
	{
		DBG_HALT_MSG("We need a descriptive name in the inherited module");
		return _S("");
	}
    
    // Adds all resource groups in ResourceGroupNames to the outgoing set
	virtual void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
	
	virtual void GatherDifficultyProps(std::vector<RtWeakPtr<LevelModuleDifficultyProps>>& io_difficultyProps, std::vector<RtWeakPtr<LevelModuleDifficultyUIProps>>& io_difficultyUI,
			bool i_riftTimed = false) const;

	std::vector<std::string> ResourceGroupNames;
	RtId DifficultyProps;
	std::string IconImage;
	std::string IconText;
};

typedef RtWeakPtr<const class LevelModuleProperties> LevelModulePropertiesPtr;

/// LevelModule
///		- Instanced, one per LevelModuleProperties sheet specified in our LevelDefinition
///		- Must hook into LevelModuleManager events in registerForEvents
class LevelModule : public GameObject
{
public:
	RT_CLASS_DEFINE(LevelModule, GameObject, RtClass);
	
	void InitializeModule(LevelModulePropertiesPtr i_properties);
    
    // Called after InitializeModule, this is where you should return all
	// additional level modules you want this level module to spawn. They will be created and
	// instantiated immediately.
	virtual void GatherDependentModulePropertySheets(std::vector<LevelModulePropertiesPtr>& io_dependent)
	{}
	
	// AddResourceRequirements
	//	- Add ResourceGroup names to the array passed in, these groups
	//	will be loaded along with other level resources at Board initialization
	virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames);
	
	// Called after all other modules have been Initialized
	// If this is a Runtime-added module, it is called immediately after InitializeModule
	void PostInitialize();
    
    // Called after InitializeModule and PostInitialize, this is where you should return all
	// resource groups you'll need for this LevelModule
	virtual void GatherRuntimeResourceRequirements(std::set<std::string>& io_resGroupNames) const
	{}

	const LevelModulePropertiesPtr GetPropsPtr() const
	{
		return getPropsPtr();
	}

protected:
	
	// In lieu of a constructor, you may use this function to initialize variables after 
	// being added to a LevelModuleManager
	virtual void initializeModule()
	{}
	// postInitialize is called after ALL other level modules have been created
	// Use this to configure yourself based on properties of other level modules
	virtual void postInitialize()
	{}

	virtual void onPostLoad() override
	{}
	
	// This is your one chance to hook into LevelModuleManager callbacks!
	virtual void registerForEvents() override
	{}
	virtual void unregisterForEvents() override
	{}

	// Accessors
	class LevelModuleManager* getManager() const;
	
	const LevelModulePropertiesPtr getPropsPtr() const
	{
		DBG_ASSERT(m_propertySheetPtr.IsValid());
		return m_propertySheetPtr;
	}
	const LevelModuleProperties* getProps() const
	{
		DBG_ASSERT(m_propertySheetPtr.IsValid());
		return m_propertySheetPtr;
	}
	template <typename T>
	const T* getProps() const
	{
		const LevelModuleProperties* props = getProps();
		const T* typedProps = props->CastChecked<const T>();
		return typedProps;
	}
	
private:
	RtWeakPtr<LevelModuleProperties> m_propertySheetPtr;
};

typedef RtWeakPtr<class LevelModule> LevelModulePtr;

#endif
