#include <Render.h>



Render::Render()
{
	device_ = NULL;
	context_ = NULL;
	swapChain_ = NULL;
	backBufferView_ = NULL;
	backBufferTexture_ = NULL;

}

Render::~Render()
{
	if (backBufferView_)
		backBufferView_->Release();
	if (swapChain_)
		swapChain_->Release();
	if (context_)
		context_->Release();
	if (device_)
		device_->Release();
}


int Render::init(HWND hwnd)
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL featureLevel[] = {
		D3D_FEATURE_LEVEL_11_0
	};


	unsigned int totalFeatureLevel = ARRAYSIZE(featureLevel);

	RECT dimensions;
	GetClientRect(hwnd, &dimensions);
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;


	HRESULT hresult;
	unsigned int devices = 0;
	unsigned int creationFlags = 0;



	for (devices = 0; devices < totalDriverTypes; devices++){
		hresult = D3D11CreateDeviceAndSwapChain(0,
			driverTypes[devices],
			0,
			creationFlags,
			featureLevel,
			totalFeatureLevel,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&swapChain_, &device_, &featureLevel_, &context_);
		if (SUCCEEDED(hresult)){
			driverType_ = driverTypes[devices];
			break;
		}
	}

	if (FAILED(hresult)){
		DXTRACE_MSG("Failed to create device");
		return 1;
	}

	hresult = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBufferTexture_);
	if (FAILED(hresult)){
		DXTRACE_MSG("Failed to get DX swap chain buffer");
		return 1;
	}

	hresult = device_->CreateRenderTargetView(backBufferTexture_, 0, &backBufferView_);
	if (FAILED(hresult)){
		DXTRACE_MSG("Failed to create DX target render");
		return 1;
	}

	backBufferTexture_->Release();

	context_->OMSetRenderTargets(1, &backBufferView_, 0);


	viewport_.Width = width;
	viewport_.Height = height;
	viewport_.MinDepth = 0.0f;
	viewport_.MaxDepth = 1.0f;
	viewport_.TopLeftX = 0.0f;
	viewport_.TopLeftY = 0.0f;

	context_->RSSetViewports(1, &viewport_);

	return 0;

}




int Render::clear()
{
	context_->ClearRenderTargetView(backBufferView_, clearColor_);
	swapChain_->Present(0, 0);

	return 0;
}


int Render::setClearColor(float r, float g, float b, float a)
{
	clearColor_[0] = r;
	clearColor_[1] = g;
	clearColor_[2] = b;
	clearColor_[3] = a;

	return 0;
}