#pragma once
#include <d3d10.h>
#include <dinput.h>
#include <string>
#include <vector>

#include "Texture.h"
#include "KeyEventHandler.h"
#include "Camera.h"
#include "Scene.h"

using namespace std;

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

class Game
{
private:

	static Game* instance;

	HINSTANCE hInstance;
	HWND hwnd;
	

	int backbufferWidth = 0;
	int backbufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			

	ID3DX10Sprite* spriteHandler = NULL;
	ID3D10SamplerState* pPointSamplerState;

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;
	LPCAMERA camera;

	vector<Scene> scenes;
	int currentScene = 0;

public:

	void InitDirect3D(HWND hwnd,HINSTANCE hInstance);
	void InitScene(vector<string> scenelink);
	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void SetPointSamplerState();

	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	LPCAMERA GetCamera() { return camera; }
	Scene GetCurrentScene() { return scenes[currentScene]; }
	void SwitchScene(int sceneIndex) { currentScene = sceneIndex; }

	void Draw(float x, float y, LPTEXTURE tex, float scaleX = 1, float scaleY = 1, int flipHorizontal = 0, RECT* rect = NULL);

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }	
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteHandler; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };

	int GetBackBufferWidth() { return backbufferWidth; }
	int GetBackBufferHeight() { return backbufferHeight; }

	static Game* GetInstance();

	~Game();
};