#include "game.h"
#include "MyUtility.h"
#include "SoundManager.h"

#include <fstream>
#include <sstream>

Game* Game::instance = NULL;

void Game::InitDirect3D(HWND hwnd,HINSTANCE hInstance)
{
	this->hwnd = hwnd;
	this->hInstance = hInstance;

	// Get client area for backbuffer
	RECT rect;
	GetClientRect(hwnd, &rect);

	backbufferWidth = rect.right;
	backbufferHeight = rect.bottom;
	camera->Init(backbufferWidth, backbufferHeight);
;
	// Create & clear the DXGI_SWAP_CHAIN_DESC structure
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Fill in the needed values
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = backbufferWidth;
	swapChainDesc.BufferDesc.Height = backbufferHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// Create the D3D device and the swap chain
	HRESULT hr = D3D10CreateDeviceAndSwapChain(NULL,
		D3D10_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		D3D10_SDK_VERSION,
		&swapChainDesc,
		&pSwapChain,
		&pD3DDevice);

	if (hr != S_OK)
		return;

	// Get backbuffer to set render target view
	ID3D10Texture2D* pBackbuffer;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackbuffer);

	if (hr != S_OK)
		return;
	
	// Create render target view
	hr = pD3DDevice->CreateRenderTargetView(pBackbuffer, NULL, &pRenderTargetView);
	pBackbuffer->Release();

	if (hr != S_OK)
		return;

	// Set the render target
	pD3DDevice->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// Create and set viewport
	D3D10_VIEWPORT vp;

	vp.Width = backbufferWidth;
	vp.Height = backbufferHeight;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MaxDepth = 1.0f;
	vp.MinDepth = 0.0f;

	pD3DDevice->RSSetViewports(1, &vp);

	D3D10_SAMPLER_DESC desc;
	desc.Filter = D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	desc.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D10_TEXTURE_ADDRESS_CLAMP;
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = 1;
	desc.ComparisonFunc = D3D10_COMPARISON_NEVER;
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 1.0f;
	desc.BorderColor[2] = 1.0f;
	desc.BorderColor[3] = 1.0f;
	desc.MinLOD = -FLT_MAX;
	desc.MaxLOD = FLT_MAX;

	pD3DDevice->CreateSamplerState(&desc, &this->pPointSamplerState);

	// Create sprite handler
	hr = D3DX10CreateSprite(pD3DDevice, 0, &spriteHandler);

	if (hr != S_OK)
		return;

	D3DXMATRIX matProjection;

	// Create the projection matrix using the values in the viewport
	D3DXMatrixOrthoOffCenterLH(&matProjection,
		(float)vp.TopLeftX,
		(float)vp.Width,
		(float)vp.TopLeftY,
		(float)vp.Height,
		0.1f,
		10);

	hr = spriteHandler->SetProjectionTransform(&matProjection);

	// Initialize the blend state for alpha drawing
	D3D10_BLEND_DESC StateDesc;
	ZeroMemory(&StateDesc, sizeof(D3D10_BLEND_DESC));
	
	StateDesc.AlphaToCoverageEnable = FALSE;
	StateDesc.BlendEnable[0] = TRUE;
	StateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
	StateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
	StateDesc.BlendOp = D3D10_BLEND_OP_ADD;
	StateDesc.SrcBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.DestBlendAlpha = D3D10_BLEND_ZERO;
	StateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
	StateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
	pD3DDevice->CreateBlendState(&StateDesc, &this->pBlendStateAlpha);

	hr = DirectSoundCreate8(NULL, &directSoundDevice, NULL);

	// Set DirectSound cooperative level
	if(directSoundDevice != NULL)
	{
		hr = directSoundDevice->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
		// Check the return code
		if FAILED(hr) return;
	}	
}

LPTEXTURE Game::LoadTexture(LPCWSTR texturePath)
{
	ID3D10Resource* pD3D10Resource = NULL;
	ID3D10Texture2D* tex = NULL;

	// Retrieve image information first 
	D3DX10_IMAGE_INFO imageInfo;
	HRESULT hr = D3DX10GetImageInfoFromFile(texturePath, NULL, &imageInfo, NULL);
	if (FAILED(hr))
	{
		//DebugOut((wchar_t*)L"[ERROR] D3DX10GetImageInfoFromFile failed for  file: %s with error: %d\n", texturePath, hr);
		return NULL;
	}

	D3DX10_IMAGE_LOAD_INFO info;
	ZeroMemory(&info, sizeof(D3DX10_IMAGE_LOAD_INFO));
	info.Width = imageInfo.Width;
	info.Height = imageInfo.Height;
	info.Depth = imageInfo.Depth;
	info.FirstMipLevel = 0;
	info.MipLevels = 1;
	info.Usage = D3D10_USAGE_DEFAULT;
	info.BindFlags = D3DX10_DEFAULT;
	info.CpuAccessFlags = D3DX10_DEFAULT;
	info.MiscFlags = D3DX10_DEFAULT;
	info.Format = imageInfo.Format;
	info.Filter = D3DX10_FILTER_NONE;
	info.MipFilter = D3DX10_DEFAULT;
	info.pSrcInfo = &imageInfo;

	// Loads the texture into a temporary ID3D10Resource object
	hr = D3DX10CreateTextureFromFile(pD3DDevice,
		texturePath,
		&info,
		NULL,
		&pD3D10Resource,
		NULL);

	// Make sure the texture was loaded successfully
	if (FAILED(hr))
	{
		//DebugOut((wchar_t*)L"[ERROR] Failed to load texture file: %s with error: %d\n", texturePath, hr);
		return NULL;
	}

	// Translates the ID3D10Resource object into a ID3D10Texture2D object
	pD3D10Resource->QueryInterface(__uuidof(ID3D10Texture2D), (LPVOID*)&tex);
	pD3D10Resource->Release();

	if (!tex) {
		//DebugOut((wchar_t*)L"[ERROR] Failed to convert from ID3D10Resource to ID3D10Texture2D \n");
		return NULL;
	}

	//
	// Create the Share Resource View for this texture 
	// 	   
	// Get the texture details
	D3D10_TEXTURE2D_DESC desc;
	tex->GetDesc(&desc);

	// Create a shader resource view of the texture
	D3D10_SHADER_RESOURCE_VIEW_DESC SRVDesc;

	// Clear out the shader resource view description structure
	ZeroMemory(&SRVDesc, sizeof(SRVDesc));

	// Set the texture format
	SRVDesc.Format = desc.Format;

	// Set the type of resource
	SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	SRVDesc.Texture2D.MipLevels = desc.MipLevels;

	ID3D10ShaderResourceView* gSpriteTextureRV = NULL;

	pD3DDevice->CreateShaderResourceView(tex, &SRVDesc, &gSpriteTextureRV);

	//DebugOut(L"[INFO] Texture loaded Ok from file: %s \n", texturePath);

	return new Texture(tex, gSpriteTextureRV);
}

void Game::InitMenu()
{
	ifstream menuFile(MENU_PATH);

	if (!menuFile.is_open())
		return;

	string line;

	while (getline(menuFile, line))
	{
		stringstream ss(line);
		
		float menuX, menuY;
		int option, optionHeight, backgroundID;

		ss >> menuX;
		ss >> menuY;
		ss >> option;
		ss >> optionHeight;
		ss >> backgroundID;

		LPMENU menu = new Menu(menuX, menuY, option, optionHeight,backgroundID);
		menus.push_back(menu);
	}

	menuFile.close();
}

void Game :: InitScene()
{
	ifstream sceneFile(SCENE_PATH);

	if (!sceneFile.is_open())
		return;

	string line;

	while (getline(sceneFile, line))
	{
		LPSCENE scene = new Scene(MyUtility::ConvertStringToLPWSTR(line));
		scenes.push_back(scene);
	}

	sceneFile.close();
}

void Game::DrawInScreenCoord(float x, float y, LPTEXTURE tex, float scaleX, float scaleY, int flipHorizontal, RECT* rect)
{

	//Change draw start point to top-left
	if (rect == NULL)
	{
		x += tex->getWidth() / 2;
		y += tex->getHeight() / 2;
	}
	else
	{
		x += ((rect->right - rect->left) / 2);
		y += ((rect->bottom - rect->top) / 2);
	}

	if (tex == NULL) return;

	int spriteWidth = 0;
	int spriteHeight = 0;

	D3DX10_SPRITE sprite;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	if (rect == NULL)
	{
		spriteWidth = tex->getWidth();
		spriteHeight = tex->getHeight();

		// top-left location in U,V coords
		sprite.TexCoord.x = 0;
		sprite.TexCoord.y = 0;

		// Determine the texture size in U,V coords
		sprite.TexSize.x = 1;
		sprite.TexSize.y = 1;

	}
	else
	{
		sprite.TexCoord.x = rect->left / (float)tex->getWidth();
		sprite.TexCoord.y = rect->top / (float)tex->getHeight();

		spriteWidth = rect->right - rect->left;
		spriteHeight = rect->bottom - rect->top;

		sprite.TexSize.x = spriteWidth / (float)tex->getWidth();
		sprite.TexSize.y = spriteHeight / (float)tex->getHeight();
	}


	if (flipHorizontal)
	{
		sprite.TexCoord.x = sprite.TexCoord.x + sprite.TexSize.x;
		sprite.TexSize.x = -sprite.TexSize.x;
	}

	// Set the texture index. Single textures will use 0
	sprite.TextureIndex = 0;

	// The color to apply to this sprite, full color applies white.
	sprite.ColorModulate = D3DXCOLOR(1, 1, 1, 1);
	//
	// Build the rendering matrix based on sprite location 
	//

	// The translation matrix to be created
	D3DXMATRIX matTranslation;

	// Create the translation matrix(ma tran dich chuyen)
	D3DXMatrixTranslation(&matTranslation, x, (backbufferHeight - y), 0.1f);

	// Scale the sprite to its correct width and height because by default, DirectX draws it with width = height = 1.0f 
	D3DXMATRIX matScaling;	//ma tran ti le
	D3DXMatrixScaling(&matScaling, (FLOAT)spriteWidth * scaleX, (FLOAT)spriteHeight * scaleY, 0.0f);

	// Setting the sprite’s position and size
	sprite.matWorld = (matScaling * matTranslation);

	spriteHandler->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

void Game::Draw(float x, float y, LPTEXTURE tex, float scaleX, float scaleY, int flipHorizontal, RECT* rect)
{
	//Change world coordination to screen coordination
	int onscreenX = x - camera->getX();
	int onscreenY = camera->getY() - y;

	DrawInScreenCoord(onscreenX, onscreenY, tex, scaleX, scaleY, flipHorizontal, rect);
}

int Game::IsKeyDown(int KeyCode)
{
	return (keyStates[KeyCode] & 0x80) > 0;
}

void Game::InitKeyboard()
{
	HRESULT hr = DirectInput8Create(this->hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&di, NULL);
	if (hr != DI_OK)
		return;

	hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	if (hr != DI_OK)
		return;

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = didv->SetDataFormat(&c_dfDIKeyboard);

	hr = didv->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	hr = didv->Acquire();
	if (hr != DI_OK)
		return;

	keyHandler = new KeyEventHandler();
}

void Game::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = didv->Acquire();
			if (h != DI_OK)
				return;
		}
		else
		{
			//DebugOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
		return;

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}
void Game::Update(DWORD dt)
{
	if (showMenu)
		menus[currentMenu]->Update(dt);
	else
	{
		scenes[currentScene]->Update(dt);
		player->Update(dt);
		camera->Update(dt);
	}
	SoundManager::GetInstance()->Update();
}

void Game::Render()
{
	if (showMenu)
		menus[currentMenu]->Render();
	else
	{
		scenes[currentScene]->Render();
		if (player->GetHp() > 0) player->Render();
	}
}

Game* Game::GetInstance()
{
	if (instance == NULL)
		instance = new Game();
	return instance;
}

Game::~Game()
{
	pBlendStateAlpha->Release();
	spriteHandler->Release();
	pRenderTargetView->Release();
	pSwapChain->Release();
	pD3DDevice->Release();
	directSoundDevice->Release();
}