#pragma once
#include "Sexy/RtObject.h"
#include "LevelModule.h"
#include <vector>

namespace Sexy {
	class LevelModuleEvent {
	public:
		std::vector<void*> m_delegates;
		template <typename T>
		void AddDelegate(const T& delegate) {}
		template <typename T>
		void operator+=(const T& delegate) { AddDelegate(delegate); }
	};
}

class LevelModuleManager : public Sexy::RtObject
{
public:
	std::vector<Sexy::RtWeakPtr<LevelModule> > m_modules;
	std::vector<SexyString> m_loadedResourceGroups;
	char m_pad1[72];
	Sexy::LevelModuleEvent m_onLoadComplete;
	char m_pad2[544];
};

static_assert(sizeof(LevelModuleManager) == 696);
static_assert(offsetof(LevelModuleManager, m_modules) == 8);
static_assert(offsetof(LevelModuleManager, m_loadedResourceGroups) == 32);
static_assert(offsetof(LevelModuleManager, m_onLoadComplete) == 128);