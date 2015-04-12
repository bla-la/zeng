#ifndef __RENDER_H__
#define __RENDER_H__
#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>

class Render {
private:
	ID3D11Device * device_;  //DX Device
	ID3D11DeviceContext * context_; //DX Context
	IDXGISwapChain * swapChain_; //DX Swap chain
	D3D_FEATURE_LEVEL  featureLevel_; //DX Feature level
	D3D_DRIVER_TYPE driverType_; //DX Device type
	ID3D11RenderTargetView * backBufferView_; //DX view
	ID3D11Texture2D * backBufferTexture_; //DX view texture
	D3D11_VIEWPORT viewport_; //Viewport settiongs
	float clearColor_[4];
public:

	Render();
	~Render();
	int init(HWND hwnd);
	int clear();
	int setClearColor(float r,float g,float b,float a);
};

#endif