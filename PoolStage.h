#pragma once
#include "Reflection/CRefManualSymbolBuilder.h"
#include "StageModule.h"
#include "Effect_PopAnim.h"
#include <Reflection/ReflectionBuilder.h>

class PoolStage : public StageModule {
public:
	void OnLoadCompleted();
	void RegisterEvents();
	void OnPostLoad();
	RtWeakPtr<Effect_PopAnim> m_poolAnim;
	DECLARE_STATIC_RT_CLASS_MEMBERS(PoolStage)

	RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(PoolStage, 0x820C10);
	RT_CLASS_CONSTRUCT_FUNCTION_END();

	RT_CLASS_BUILD_SYMBOLS_BEGIN(StageModule);
	RT_CLASS_REGISTER_CLASS_RTWEAKPTR_PROPERTY(PoolStage, m_poolAnim, Effect_PopAnim)
	RT_CLASS_BUILD_SYMBOLS_END();
	RT_CLASS_REGISTER_CLASS_FUNCTION(PoolStage)
	RT_CLASS_GET_CLASS_FUNCTION(PoolStage, 0x8201FC);
};



class PoolStageProperties : public StageModuleProperties {
public:
	Color PoolAnimColor = {0, 0, 0, 255};
	DECLARE_STATIC_RT_CLASS_MEMBERS(PoolStageProperties)

	RT_CLASS_CONSTRUCT_FUNCTION_BEGIN(PoolStageProperties, 0x681B0C);
	RT_CLASS_CONSTRUCT_FUNCTION_END();

	RT_CLASS_BUILD_SYMBOLS_BEGIN(StageModuleProperties);
	RT_CLASS_REGISTER_CLASS_PROPERTY(PoolStageProperties, Color, PoolAnimColor)
	RT_CLASS_BUILD_SYMBOLS_END();

	RT_CLASS_REGISTER_CLASS_FUNCTION(PoolStageProperties)
	RT_CLASS_GET_CLASS_FUNCTION(PoolStageProperties, 0x81D9B0);
};