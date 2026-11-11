#ifndef SEXYPIXELSHADER9_H
#define SEXYPIXELSHADER9_H

#include "ISexyShader.h"
#include <d3d9.h>

namespace Sexy
{
class SexyPixelShaderData9 : public ISexyPixelShaderData
{
	IDirect3DPixelShader9*	mPixelShader;
public:
	SexyPixelShaderData9();
	virtual ~SexyPixelShaderData9(void);	

	friend class D3D9Interface;
};
}

#endif // #ifndef SEXYPIXELSHADER9_H
