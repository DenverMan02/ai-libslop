/*
 * CustomLevelCreator.h
 *
 *  Created on: 2021-11-23
 *      Author: admin
 */

#ifndef CUSTOMLEVELCREATOR_H_
#define CUSTOMLEVELCREATOR_H_

#include "RtDb.h"
#include <vector>
#include <string>
#include "LevelDefinition.h"
#include "CustomLevelConfig.h"

using Sexy::RtObject;
using Sexy::RtWeakPtr;
using Sexy::RtClass;
using Sexy::RtId;

class CustomLevelCreator
{
public:
	CustomLevelCreator();

	void Reset();
	void CreateLevel(const CustomLevelParams& i_info);
	void SetLevelInfo(const CustomLevelParams& i_info);
	void AddModuleReference(const wchar_t* i_alias, const wchar_t* i_package);
	void SetLootModuleReference(const wchar_t* i_alias, const wchar_t* i_package);
	void SetStageModuleReference(const wchar_t* i_alias, const wchar_t* i_package);
	RtObject* AddModule(RtClass* i_class);
	RtWeakPtr<RtObject> AddAliasedObject(RtClass* i_class);
	std::string SaveLevelDef(const CustomLevelWorldParams& i_worldInfo);
	LevelDefinitionPtr LoadLevelDef(const std::string& i_levelName);
	void SetLevelDef(LevelDefinitionPtr i_levelPtr) { m_levelDef = i_levelPtr; }
	LevelDefinitionPtr GetLevelDef() { return m_levelDef; }
	const std::string& GetCustomLevelPrefix();

	template<typename T>
	T* AddModule();
	template<typename T>
	RtWeakPtr<T> AddAliasedObject();

private:
	LevelDefinitionPtr createLevelDefinition();
	RtId createAliasedObjectInLevel(Sexy::RtClass* i_class);
	Sexy::RtName getNextAlias();

	LevelDefinitionPtr m_levelDef;
	uint m_nextLevelAlias;
};

template<typename T>
T* CustomLevelCreator::AddModule()
{
	RtObject* obj = AddModule(T::StaticGetClass());
	return obj->CastChecked<T>();
}

template<typename T>
RtWeakPtr<T> CustomLevelCreator::AddAliasedObject()
{
	RtWeakPtr<T> typedPtr = AddAliasedObject(T::StaticGetClass());
	return typedPtr;
}

#endif /* CUSTOMLEVELCREATOR_H_ */
