/*
*****************************************************************************
*   SCC:Perforce SCM
*
*   $File:$                      
*
*   $Revision:$
*
*   $DateTime:$
*
*   $Author:$
*
*   $Id:$
*
*****************************************************************************
*
* Description: DX11 Shader Effects
*
*****************************************************************************
*
* The following text and routines are proprietary and protected by the
* following copyright:
*
* PopCap Games
* 2401 4th Ave, Suite 300
* Seattle, WA 98121
*
*****************************************************************************
*
* History-
*
* 06.23.12 	_SCL_	Initial Version
*
*****************************************************************************
*/

#ifndef __DX11_RENDEREFFECT_H__
#define __DX11_RENDEREFFECT_H__ 

#include "drivers/graphics/BasePopFXRenderEffect.h"
#include "drivers/graphics/Dx11/Dx11RenderDevice.h"

namespace Sexy
{


	struct Dx11RenderEffectPass
	{
		Dx11RenderEffectPass()
		{
			m_pVertexShader = nullptr;
			m_pPixelShader = nullptr;   
		}

		Dx11VertexShader *m_pVertexShader;
		#if defined(WINRT_CLUSTER)
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;	// Should only be ComPtr for WinRT
		#else
		ID3D11PixelShader *m_pPixelShader;	
		#endif
 		int m_nPixelShaderBaseParam;
		int m_nPixelShaderNumParams;

		int m_nVertexShaderBaseParam;
		int m_nVertexShaderNumParams;
	};

	typedef BasePopFXRenderEffect<Dx11RenderEffectPass> BaseDx11RenderEffect;

	class Dx11RenderEffect : public BaseDx11RenderEffect
	{
	public:
		typedef BaseDx11RenderEffect super;

		Dx11RenderEffect(Dx11RenderDevice* theDevice, RenderEffectDefinition* theDefinition);

		virtual void SetShadersForPass(Dx11RenderEffectPass &pass);
		virtual bool InitializePass(PopFXPass* thePass, RenderEffectTechnique& theTechData);
		virtual void UpdateParams();

		int GetNamedParameter(const char *pParamName, int nBaseParam, int nNumParams);

	private:

	};
};

#endif
//************************************************************************ End of Source *

