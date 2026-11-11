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
* Description: WinRT DX11 Driver
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

#ifndef __WINRT_GRAPHICS_DRIVER__
#define __WINRT_GRAPHICS_DRIVER__ 

#include "Mesh.h"
#include "IGraphicsDriver.h"
#include "NativeDisplay.h"
#include "GraphicsMetrics.h"
#include "TriVertex.h"
#include <d3d11_1.h>

#include <agile.h>

#include "ResStreamsFormat.h"
#include "drivers/graphics/Dx11/Dx11RenderDevice.h"
#include "drivers/graphics/BaseRenderDevice.h"
#include "PakLib/PakInterface.h"

namespace Sexy
{

class SexyAppBase;
class WinRTAppDriver;
class Dx11RenderDevice;
class Dx11GraphicsDriver;
struct SexyVertex2DList;


//****************************************************************************************
//************************************************************************** Dx11Texture *
//****************************************************************************************
class Dx11Texture
{
public:
	Dx11Texture()
	{
		m_pTexture = nullptr;
		m_pTextureView = nullptr;
		m_nLockedRefCount= 0;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTextureView;

	void	LockBits(Dx11GraphicsDriver *pDriver, int *nPitch, void **pBits);
	void	UnlockBits(Dx11GraphicsDriver *pDriver);  

private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pStagingTexture;
	D3D11_MAPPED_SUBRESOURCE m_aMappedResource;
	int m_nLockedRefCount;
};


//****************************************************************************************
//********************************************************************* Dx11VertexBuffer *
//****************************************************************************************
class Dx11VertexBuffer
{
public:
	Dx11VertexBuffer(int nSize, int nStride, Dx11GraphicsDriver *pDriver); 
	bool AddVerts(const void *pVertData, int nVertCount, int &nVertIndex);

	int	 	m_nIndex;
	int		m_nSize;
	UINT 	m_nStride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	Dx11GraphicsDriver *m_pDriver;
};


//****************************************************************************************
//********************************************************************* Dx11VertexShader *
//****************************************************************************************
class Dx11VertexShader
{
public:
	Dx11VertexShader(const void *pBytecode, uint32 nBytecodeLength, Dx11GraphicsDriver *pDriver);
	void SetVertexDecl(ulong theFVF);
	ID3D11VertexShader *GetDxShader() { return m_pShader.Get(); };

private:
	typedef std::pair<uint32, Microsoft::WRL::ComPtr<ID3D11InputLayout>> FVFMapping;
	typedef std::vector<FVFMapping> VertexDeclList;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_pShader;
	const void 		*m_pBytecode;
	uint32 			m_nBytecodeLength;
	ulong 			m_nCurFVF;
	VertexDeclList 	m_aVertexDecls;
	Dx11GraphicsDriver *m_pDriver;
};


//****************************************************************************************
//******************************************************************* Dx11GraphicsDriver *
//****************************************************************************************
class Dx11GraphicsDriver : public IGraphicsDriver, protected NativeDisplay
{
public:
	static const int SHADER_CONSTANT_BUFFER_SIZE = 256;	// DX11 gives us 16 sets of 4096 of these
	static const int MAX_TEXTURE_STAGES = 8;			
	static const int VERTEX_BUFFER_SIZE = 32768;

	Dx11RenderDevice	*m_pRenderDevice;
	
	Dx11GraphicsDriver(WinRTAppDriver *pAppDriver,SexyAppBase *pSexyBase);
	virtual ~Dx11GraphicsDriver();

	bool					Is3D()				{ return true;	}

	int						GetVersion();

	virtual ulong			GetRenderModeFlags();
	virtual void			SetRenderModeFlags(ulong nFlags);

	virtual ERenderMode		GetRenderMode();
	virtual void			SetRenderMode(ERenderMode inRenderMode);

	virtual std::string		GetRenderModeString(ERenderMode inRenderMode, ulong inRenderModeFlags, bool inIgnoreMode=false, bool inIgnoreFlags=false);

	virtual void			AddDeviceImage(DeviceImage* theDDImage);
	virtual void			RemoveDeviceImage(DeviceImage* theDDImage);
	
	virtual void			Remove3DData(MemoryImage* theImage); 
			 
	virtual DeviceImage*	GetScreenImage();
			
	virtual void			WindowResize(int theWidth, int theHeight);	
	
	virtual bool			Redraw(Rect* theClipRect = NULL);		
	
	virtual void			RemapMouse(int& theX, int& theY);
	
	virtual bool			SetCursorImage(Image* theImage);
	
	virtual void			SetCursorPos(int theCursorX, int theCursorY);
	
	virtual void			RemoveShader(const void* theShader);
	
	virtual RenderEffectDefinition*	CreateRenderEffectDefinition(ulong theDataLen, const void* theData, const char* theSrc);
	
	virtual DeviceSurface	*CreateDeviceSurface();
	
	virtual NativeDisplay	*GetNativeDisplayInfo();
	
	virtual RenderDevice	*GetRenderDevice()		{ return (RenderDevice*)m_pRenderDevice; };
	virtual RenderDevice3D	*GetRenderDevice3D()   	{ return (RenderDevice3D*)m_pRenderDevice; }; 
		
	virtual Ratio			GetAspectRatio()		{ return m_aAspect; }
	virtual int				GetDisplayWidth()		{ return m_nDisplayWidth; }
	virtual	int				GetDisplayHeight()		{ return m_nDisplayHeight; }
	
	virtual CritSect&		GetCritSect();
	
	virtual Mesh*			LoadMesh(const std::string& thePath, MeshListener* theListener = NULL);

	virtual void			AddMesh(Mesh* theMesh) {};
	virtual void			RemoveMesh(Mesh* theMesh) {};
	
#ifndef RELEASEFINAL
		virtual GraphicsMetrics& GetMetrics();
#endif
	bool 	Init();
	void 	CreateWindowSizeDependentResources();

	DeviceImage*	GetImageFromResStream(const std::string& theFileName, void* theTextureBacking,ResStreamFileGPULocationInfo* locationInfo);
	DeviceImage		*GetOptimizedImage(const std::string& theFileName, bool commitBits, bool allowTriReps);

	void 	UpdateVertexShaderConstantBuffer(uint32 nIdx, SexyVector4 *pInput);
	void 	UpdatePixelShaderConstantBuffer(uint32 nIdx, SexyVector4 *pInput);

	void 	DrawVertices(const void *pVertData, int nVertCount, int nStride);
	void 	FrameBegin();

	void	CreateBackBuffer(int nWidth, int nHeight);
	void 	SetRenderTarget(int nNumTargets, ID3D11RenderTargetView *pCurRenderView, ID3D11DepthStencilView *pCurDepthView);

	ID3D11Device1			*GetDxDevice()			 	   	{ return m_pD3DDevice.Get(); };
	ID3D11DeviceContext1 	*GetDxContext()			   		{ return m_pD3DContext.Get(); };
	Dx11VertexShader  		*GetVertexShader()				{ return m_pCurVertexShader; }
	ID3D11PixelShader 		*GetPixelShader()				{ return m_pCurPixelShader; }
	Dx11VertexShader 		*GetDefaultVertexShader()		{ return m_pDefaultVertexShader; };
	ID3D11PixelShader  		*GetDefaultPixelShader()		{ return m_pDefaultPixelShader.Get(); }; 
	ID3D11PixelShader  		*GetDefaultPixelShaderNoTex()	{ return m_pDefaultPixelShaderNoTex.Get(); }; 

	ID3D11RenderTargetView 	*GetDefaultRenderTarget();
	ID3D11DepthStencilView 	*GetDefaultDepthStencil();

	void 	SetVertexShader(Dx11VertexShader *pShader);
	void 	SetPixelShader(ID3D11PixelShader *pShader);
	void 	SetSamplerState(uint32 nStage, D3D11_SAMPLER_DESC *pSamplerDesc);
	void 	SetBlendState(D3D11_BLEND_DESC *pBlendDesc);
	void 	SetPrimitiveType(Graphics3D::EPrimitiveType ePrimType);
	void	SetTexture(int nStage, Dx11Texture *pTexture);

	void	 AddVertexBuffer(int nSize, int nStride, int theFVF);
	void	 SetVertexBuffer(int theFVF);

protected:
	friend class		WinRTAppDriver;

	typedef std::pair<uint32, Dx11VertexBuffer*> VertexBufferMapping;
	typedef std::vector<VertexBufferMapping> VertexBufferList;

	void				MakeSysCursor();
	
	ERenderMode			m_eRenderMode;
	ulong				m_nRenderModeFlags;
#ifndef RELEASEFINAL
	GraphicsMetrics		m_aGraphicsMetrics;
#endif
	WinRTAppDriver*		m_pAppDriver;
	SexyAppBase*		m_pApp;
	
	int					m_nWidth;
	int					m_nHeight;
	Ratio				m_aAspect;
	int					m_nDesktopWidth;
	int					m_nDesktopHeight;
	Ratio				m_aDesktopAspect;
	int					m_nDisplayWidth;
	int					m_nDisplayHeight;
	Ratio				m_aDisplayAspect;
	bool				m_bIsWidescreen;
	
	int					m_nCursorX;
	int					m_nCursorY;

	CritSect			m_aCritSect;
	Rect				m_aPresentationRect;
	
	HRenderContext		m_aCurrentContext;
	
	DeviceImage*		m_pScreenImage;
	DeviceImage*		m_pDefaultCursor;

	VertexBufferList   	m_aVertexBufferList;
	Dx11VertexBuffer	*m_pCurVertexBuffer;

	#if defined(HOST_WINRTDESKTOP) || defined(HOST_WINRTPHONE)
	Platform::Agile<Windows::UI::Core::CoreWindow>  m_pWindow;
	#else
	Windows::UI::Core::CoreWindow^ m_pWindow;
	#endif
		
	Windows::Foundation::Rect	m_aWindowBounds;
	Windows::Foundation::Size 	m_aRenderTargetSize;
	D3D_FEATURE_LEVEL			m_eFeatureLevel;

	SexyVector4			*m_pPixelShaderConstantBufferData;
	SexyVector4			*m_pVertexShaderConstantBufferData;

	Dx11VertexShader	*m_pCurVertexShader;
	ID3D11PixelShader  	*m_pCurPixelShader;

	Microsoft::WRL::ComPtr<ID3D11Device1>           m_pD3DDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_pD3DContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_pSwapChain;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthStencilView;

	Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pDoubleBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pDoubleBufferShaderResourceView;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> 	m_pDoubleBufferRenderView;

	Dx11VertexShader	*m_pDefaultVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> 		m_pDefaultPixelShaderNoTex;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> 		m_pDefaultPixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer> 			m_pPixelShaderConstantBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> 			m_pVertexShaderConstantBuffer;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> 		m_pSamplerState[MAX_TEXTURE_STAGES];
	Microsoft::WRL::ComPtr<ID3D11BlendState>		m_pBlendState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState2D;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_pDepthStencilState3D;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	m_pRasterizerState; 
};


struct Dx11ExtraRenderDataInfo
{
	Dx11ExtraRenderDataInfo()
	{
// 		m_pRenderSurface = nullptr;
// 		m_pRenderView = nullptr;
// 		m_pDepthSurface = nullptr;
// 		m_pDepthView = nullptr;
// 		m_pRenderShaderResourceView = nullptr;

		mDirty		= false;
		mNumTiles	= 0;
		mResolvedTo	= false;
		mPFile = NULL;
		mFromRSB	= false;
   	}
									
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			 m_pRenderSurface;				
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> 	 m_pRenderView;                 
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pRenderShaderResourceView;   
	Microsoft::WRL::ComPtr<ID3D11Texture2D>			m_pDepthSurface;                
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_pDepthView;
	
	//the surfaces have to be resolved into textures, the dirty flag
	// will keep track of if anything has to be resolved
	bool				mDirty;
	
	int					mNumTiles;
	bool				mResolvedTo;
	PFILE*				mPFile;
	bool				mFromRSB;
};

};

//************************************************************************ End of Source *
#endif
