#include "SoundManager.h"
#include "Game.h"
#include <iostream>
#include <fstream>

SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::GetInstance()
{
    if (instance == NULL)
        instance = new SoundManager();
    return instance;
}

void SoundManager::AddSound(int ID, string soundLink)
{
	soundLinks.insert({ ID,soundLink });
}

void SoundManager::Stop(int ID)
{
    LPDIRECTSOUNDBUFFER buffer = soundPlaying[ID];
    buffer->Stop();
    buffer->Release();
}

void SoundManager::SetVolume(int ID, int level)
{
	try
	{
		LPDIRECTSOUNDBUFFER buffer = soundPlaying[ID];
		buffer->SetVolume(level);
	}
	catch(exception e)
	{
		return;
	}
}

HRESULT SoundManager::Play(int ID, bool loop)
{
	// Check if the sound is on playlist
	for (auto it = soundPlaying.begin(); it != soundPlaying.end(); it++)
		if (it->first == ID)
			return E_FAIL;

    string soundLink = soundLinks[ID];

    // Open the file
    ifstream file(soundLink, ios::binary);
    if (!file) {
        cerr << "Failed to open file: " << endl;
        return E_FAIL;
    }

    // Read the WAV header
    char header[44];
    file.read(header, sizeof(header));
    if (!file) {
        cerr << "Failed to read WAV header";
        return E_FAIL;
    }

    // Check if it's a valid WAV file
    if (memcmp(header, "RIFF", 4) != 0 || memcmp(header + 8, "WAVEfmt ", 8) != 0) {
        cerr << "Invalid WAV file format" << std::endl;
        return E_FAIL;
    }

    // Extract WAV format information
    WAVEFORMATEX wfx;
    memcpy(&wfx, header + 20, sizeof(WAVEFORMATEX));

    DWORD fileSize = 0;
    file.seekg(0, ios::end);
    fileSize = static_cast<DWORD>(file.tellg());
    file.seekg(44, ios::beg); // Skip the header
    DWORD dataChunkSize = fileSize - 44; // Total size of audio data

    // Create the sound buffer
    DSBUFFERDESC dsbd;
    ZeroMemory(&dsbd, sizeof(dsbd));
    dsbd.dwSize = sizeof(dsbd);
    dsbd.dwFlags = DSBCAPS_CTRLVOLUME;
    dsbd.dwBufferBytes = dataChunkSize; // Load enough data for 2 seconds
    dsbd.lpwfxFormat = &wfx;

    LPDIRECTSOUNDBUFFER buffer;

    HRESULT hr = Game::GetInstance()->GetDirectSoundDevice()->CreateSoundBuffer(&dsbd, &buffer, NULL);
    if (FAILED(hr)) {
        cerr << "Failed to create sound buffer";
        return hr;
    }

    // Lock the buffer to write data
    LPVOID pAudio1, pAudio2;
    DWORD dwBytes1, dwBytes2;
    hr = buffer->Lock(0, dsbd.dwBufferBytes, &pAudio1, &dwBytes1, &pAudio2, &dwBytes2, 0);
    if (FAILED(hr)) {
        cerr << "Failed to lock sound buffer";
        buffer->Release();
        return hr;
    }

    // Read the audio data from the file
    file.read(static_cast<char*>(pAudio1), dwBytes1);
    if (!file) {
        cerr << "Failed to read audio data";
        buffer->Unlock(pAudio1, dwBytes1, pAudio2, dwBytes2);
        buffer->Release();
        return E_FAIL;
    }
    if (pAudio2 != nullptr) {
        file.read(static_cast<char*>(pAudio2), dwBytes2);
        if (!file) {
            cerr << "Failed to read audio data";
            buffer->Unlock(pAudio1, dwBytes1, pAudio2, dwBytes2);
            buffer->Release();
            return E_FAIL;
        }
    }

    // Unlock the buffer
    hr = buffer->Unlock(pAudio1, dwBytes1, pAudio2, dwBytes2);
    if (FAILED(hr)) {
        cerr << "Failed to unlock sound buffer";
        buffer->Release();
        return hr;
    }

    if (loop)
        buffer->Play(0, 0, DSBPLAY_LOOPING);
    else
        buffer->Play(0, 0, 0);

    soundPlaying.insert({ ID,buffer });

    return S_OK;
}

bool SoundManager::IsPlaying(int ID)
{
    DWORD dwStatus;
    LPDIRECTSOUNDBUFFER buffer = soundPlaying[ID];
    if (buffer == NULL)
        return false;

    if (FAILED(buffer->GetStatus(&dwStatus))) {
        // Handle error
        return false;
    }

    return (dwStatus & DSBSTATUS_PLAYING) != 0;
    
}

void SoundManager::Update()
{
    for (auto it = soundPlaying.begin(); it != soundPlaying.end();)
    {
        if (!IsPlaying(it->first))
        {
            Stop(it->first);
            it = soundPlaying.erase(it);
        }
        else
            ++it;
    }
}