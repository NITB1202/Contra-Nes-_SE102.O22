#include <windows.h>
#include <d3dx10.h>
#include "Runman.h"
#include "Player.h"
#include "Game.h"
#include "AnimationLib.h"

#define WINDOW_TITLE L"Contra"
#define WINDOW_CLASS_NAME L"MainWindow"
#define WINDOW_ICON_PATH L"contra_icon.ico"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAX_FRAME_RATE 60
#define BACKGROUND_COLOR D3DXCOLOR(0,0,0,1) //BLACK

Runman* runman;
Player* player;
KeyEventHandler* keyHandler;

#define RUNMAN_START_X 300.0f
#define RUNMAN_START_Y 100.0f

HWND CreateGameWindow(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
void LoadResource();
int GameRun();
void Render();
void Update(DWORD dt);

#define PLAYER_START_X 50
#define PLAYER_START_Y 200

vector<LPGAMEOBJECT> gameObject;

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

void LoadResource()
{
	Game* game = Game::GetInstance();
	runman = new Runman(RUNMAN_START_X, RUNMAN_START_Y, -RUNMAN_START_VX, RUNMAN_START_VY);
	player = new Player(PLAYER_START_X, PLAYER_START_Y, PLAYER_START_VX, PLAYER_START_VY);

	LPTEXTURE tex;
	AnimationLib* aniLib = AnimationLib::GetInstance();

	tex = game->LoadTexture(TEXTURE_PATH_RUNMAN_RIGHT);
	aniLib->AddAnimation(RUNMAN_RUN_RIGHT_ANIMATION, Animation(tex, RUNMAN_SPRITE_WIDTH, RUNMAN_SPRITE_HEIGHT, 2, 2));
	
	tex= game->LoadTexture(TEXTURE_PATH_PLAYER_RUN_RIGHT);
	aniLib->AddAnimation(PLAYER_RUN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_TOP_RIGHT);
	aniLib->AddAnimation(PLAYER_TOP_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_DOWN_RIGHT);
	aniLib->AddAnimation(PLAYER_DOWN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_FACE_RIGHT_IDLE);
	aniLib->AddAnimation(PLAYER_IDLE_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_GUN_UP);
	aniLib->AddAnimation(PLAYER_GUN_UP, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_GUN_UP_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_LAY_DOWN);
	aniLib->AddAnimation(PLAYER_LAY_DOWN_ANIMATION, Animation(tex, PLAYER_LAY_DOWN_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_JUMP_UP);
	aniLib->AddAnimation(PLAYER_JUMP_UP, Animation(tex, PLAYER_JUMP_WIDTH, PLAYER_JUMP_HEIGHT, 2, 2));

	player->SetState(PLAYER_IDLE_RIGHT);

	gameObject.push_back(runman);
	gameObject.push_back(player);
}

void Update(DWORD dt)
{
	for (int i = 0; i < gameObject.size(); i++)
		gameObject[i]->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	Game* game = Game::GetInstance();

	ID3D10Device* pD3DDevice = game->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = game->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = game->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = game->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(game->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		for (int i = 0; i < gameObject.size(); i++)
			gameObject[i]->Render();

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
			Game::GetInstance()->ProcessKeyboard();
			Update((DWORD)dt);
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

	Game* game = Game::GetInstance();
	game->InitDirect3D(hwnd, hInstance);
	keyHandler = new KeyEventHandler();
	game->InitKeyboard(keyHandler);
	
	LoadResource();
	
	GameRun();

	return 0;
}
