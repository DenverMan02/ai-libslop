#ifndef SEXYVERTEXSHADER9_H
#define SEXYVERTEXSHADER9_H

#include "ISexyShader.h"
#include <d3d9.h>

namespace Sexy
{
class D3DInterface;
class SexyVertexShaderData9 : public ISexyVertexShaderData
{
	IDirect3DVertexShader9*	mVertexShader;
public:
	SexyVertexShaderData9();
	virtual ~SexyVertexShaderData9(void);	
	
	friend class D3D9Interface;
};
} // namespace Sexy

#endif // #ifndef SEXYVERTEXSHADER9_H
