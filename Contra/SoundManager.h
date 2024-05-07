#pragma once
#include <map>
#include <string>
#include <dsound.h>
#include <windows.h>

using namespace std;

class SoundManager
{
private:
	static SoundManager* instance;
	map<int, string> soundLinks;
	map<int, LPDIRECTSOUNDBUFFER> soundPlaying;
public:
	static SoundManager* GetInstance();
	void AddSound(int ID, string soundLink);
	HRESULT Play(int ID, bool loop = false);
	void Stop(int ID);
	void SetVolume(int ID, int level);
	bool IsPlaying(int ID);
	void Update();
};
