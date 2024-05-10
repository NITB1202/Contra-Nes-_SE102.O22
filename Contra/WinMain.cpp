#include <windows.h>
#include <d3dx10.h>
#include "Resource.h"
#include "Game.h"
#include "Player.h"

#define WINDOW_TITLE L"Contra"
#define WINDOW_CLASS_NAME L"MainWindow"
#define WINDOW_ICON_PATH L"contra_icon.ico"

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 440
#define MAX_FRAME_RATE 120

HWND CreateGameWindow(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
void LoadResource();
int GameRun();
void Render();
void Update(DWORD dt);

Game* game = Game::GetInstance();

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void Update(DWORD dt)
{
	game->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	ID3D10Device* pD3DDevice = game->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = game->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = game->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = game->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(game->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		game->Render();
		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance,int screenWidth,int screenHeight, int nCmdShow)
{
	WNDCLASSEX wc;
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.lpszMenuName = NULL;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HMONITOR hMonitor = MonitorFromPoint({ 0, 0 }, MONITOR_DEFAULTTOPRIMARY);

	// Get monitor info
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfo(hMonitor, &monitorInfo);

	int monitorWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	int monitorHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

	int window_x = (monitorWidth - screenWidth) / 2;
	int window_y = (monitorHeight - screenHeight) / 2;


	HWND hwnd = CreateWindow(
		WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		window_x,
		window_y,
		screenWidth,
		screenHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
		return 0;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	return hwnd;
}

int GameRun()
{
	MSG msg;
	bool done = false;

	// Get the time before start game loop
	ULONGLONG frameStart = GetTickCount64(); // the function return the number of milliseconds that have elapsed since the system was started
	// Accurate delta time (1000ms = 1s)
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) 
				done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			game->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	HWND hwnd = CreateGameWindow(hInstance, SCREEN_WIDTH, SCREEN_HEIGHT, nCmdShow);

	if (hwnd == 0) 
		return 0;

	game->InitDirect3D(hwnd, hInstance);
	game->InitKeyboard();
	
	LoadResource();

	game->InitScene();
	game->InitMenu();
	game->SetCurrentMenu(INTRO_MENU);
	
	GameRun();

	return 0;
}
