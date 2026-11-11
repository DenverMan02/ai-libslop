#ifndef PS3RENDEREFFECT_H_INCLUDED
#define PS3RENDEREFFECT_H_INCLUDED

#include "drivers/graphics/BasePopFXRenderEffect.h"
#include "drivers/graphics/ps3/PS3RenderDevice.h"

#include <cell/gcm.h>

namespace Sexy
{


	struct PS3RenderEffectPass
	{
		PS3RenderEffectPass()
		{
			mVertexProgram = NULL;
			mFragmentProgram = NULL;
		}

		CGprogram mVertexProgram;
		CGprogram mFragmentProgram;
	};

	typedef BasePopFXRenderEffect<PS3RenderEffectPass> BasePS3RenderEffect;

	class PS3RenderEffect : public BasePS3RenderEffect
	{
	public:
		typedef BasePS3RenderEffect super;

		PS3RenderEffect(PS3RenderDevice* theDevice, RenderEffectDefinition* theDefinition);

		virtual void SetShadersForPass(PS3RenderEffectPass &pass);
		virtual bool InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData);
		virtual void UpdateParams();
	private:

	};
};

#endif
