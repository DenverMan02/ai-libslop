#ifndef VITARENDEREFFECT_H_INCLUDED
#define VITARENDEREFFECT_H_INCLUDED

#include "drivers/graphics/BasePopFXRenderEffect.h"
#include "drivers/graphics/vita/VitaRenderDevice.h"

#include <gxm.h>

namespace Sexy
{

	struct VitaRenderEffectPass
	{
		SceGxmShaderPatcherId mVertexProgram;
		SceGxmShaderPatcherId mFragmentProgram;

		const SceGxmProgram* mOrigVertexProgram;
		const SceGxmProgram* mOrigFragmentProgram;
	};

	typedef BasePopFXRenderEffect<VitaRenderEffectPass> BaseVitaRenderEffect;

	class VitaRenderEffect : public BaseVitaRenderEffect
	{
	public:
		typedef BaseVitaRenderEffect super;

		VitaRenderEffect(VitaRenderDevice* theDevice, RenderEffectDefinition* theDefinition);

		virtual void SetShadersForPass(VitaRenderEffectPass &pass);
		virtual bool InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData);
		virtual void UpdateParams();

		void UpdateUniformData(SceGxmContext* theContext, void* vertexUniformData, void* fragmentUniformData);
	};
};

#endif
