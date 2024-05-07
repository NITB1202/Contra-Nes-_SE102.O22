#pragma once
#include <d3d10.h>
#include <dinput.h>
#include <vector>
#include <dsound.h>

#include "Texture.h"
#include "KeyEventHandler.h"
#include "Camera.h"
#include "Scene.h"
#include "Player.h"
#include "Menu.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

#define BACKGROUND_COLOR D3DXCOLOR(0, 0, 0, 1)

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
	ID3D10SamplerState* pPointSamplerState = NULL;

	LPDIRECTINPUT8 di = NULL;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv = NULL;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPDIRECTSOUND8 directSoundDevice = NULL; // variable that will hold the created DirectSound device

	vector<LPSCENE> scenes;
	vector<LPMENU> menus;

	int currentScene = 0;
	int currentMenu = INTRO_MENU;

	LPPLAYER player;
	LPCAMERA camera;
	LPKEYEVENTHANDLER keyHandler;

public:

	bool showMenu = true;

	Game()
	{
		player = Player::GetInstance();
		camera = Camera::GetInstance();
		keyHandler = NULL;
	}
	void InitDirect3D(HWND hwnd,HINSTANCE hInstance);
	void InitScene();
	void InitMenu();

	// Keyboard related functions 
	void InitKeyboard();
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPTEXTURE LoadTexture(LPCWSTR texturePath);
	LPSCENE GetCurrentScene() { return scenes[currentScene]; }
	void SetCurrentMenu(int id) { 
		currentMenu = id;
		menus[currentMenu]->Reset();
	}
	void SwitchScene(int sceneID) { currentScene = sceneID; }
	LPMENU GetCurrentMenu() { return menus[currentMenu]; }

	void ClearBackGround() { pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR); }
	void Draw(float x, float y, LPTEXTURE tex, float scaleX = 1, float scaleY = 1, int flipHorizontal = 0, RECT* rect = NULL);
	void DrawInScreenCoord(float x, float y, LPTEXTURE tex, float scaleX = 1, float scaleY = 1, int flipHorizontal = 0, RECT* rect = NULL);

	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }	
	ID3DX10Sprite* GetSpriteHandler() { return this->spriteHandler; }
	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };
	LPDIRECTSOUND8 GetDirectSoundDevice() { return directSoundDevice; }

	int GetBackBufferWidth() { return backbufferWidth; }
	int GetBackBufferHeight() { return backbufferHeight; }

	void Update(DWORD dt);
	void Render();

	static Game* GetInstance();

	~Game();
};