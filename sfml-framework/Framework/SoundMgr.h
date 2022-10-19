#pragma once
#include "../3rd/SingleTon.h"
#include <SFML/Audio.hpp>
#include <list>

using namespace std;
using namespace sf;

class SoundMgr : public Singleton<SoundMgr>
{
private:
	list<Sound*> playing;
	list<Sound*> waiting;
	float volume;
public:
	const int TotalChannels;
	SoundMgr();
	~SoundMgr();
	void Init();
	void Release();
	void Play(string id, bool loop = false);
	void StopAll();
	void Update();
};

#define SOUND_MGR (SoundMgr::GetInstance())